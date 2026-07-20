package main

import (
	"context"
	"encoding/json"
	"fmt"
	"log/slog"
	"net"
	"net/http"
	"net/url"
	"strconv"
	"strings"
	"time"

	"github.com/go-chi/chi/v5"
	"github.com/go-playground/validator/v10"
	"github.com/testcase-ac/testcase-ac/backend/api/stresser"
)

const requestIDHeader = "X-Request-Id"

type contextKey string

const requestIDContextKey contextKey = "requestID"

type App struct {
	settings     Settings
	catalog      map[[2]string]Problem
	typeMetadata map[string]TypeMetadata
	stresser     stresser.Client
	rateLimiter  *RateLimiter
	validate     *validator.Validate
	stats        *StatsStore
}

func NewAppWithTypeMetadata(settings Settings, catalog map[[2]string]Problem, typeMetadata map[string]TypeMetadata, stressClient stresser.Client) *App {
	app := &App{
		settings:     settings,
		catalog:      catalog,
		typeMetadata: typeMetadata,
		stresser:     stressClient,
		rateLimiter:  NewRateLimiter(settings.RateLimitMax, settings.RateLimitWindowS),
		validate:     validator.New(validator.WithRequiredStructEnabled()),
	}
	if settings.StatsDBPath != "" {
		stats, err := OpenStatsStore(settings.StatsDBPath)
		if err != nil {
			slog.Error("stats_disabled", "err", err)
		} else {
			app.stats = stats
		}
	}
	return app
}

func (a *App) Handler() http.Handler {
	router := chi.NewRouter()
	router.Get("/api/health", a.handleHealth)
	router.Get("/api/problems", a.handleListProblems)
	router.Get("/api/stats", a.handleStats)
	router.Post("/api/custom-invocation/stress", a.handleCustomStress)
	router.Route("/api/problems/{problemType}/{externalId}", func(r chi.Router) {
		r.Get("/", a.handleGetProblem)
		r.Post("/stress", a.handleStress)
	})

	var handler http.Handler = router
	handler = a.recoverMiddleware(handler)
	handler = a.accessLogMiddleware(handler)
	handler = a.requestIDMiddleware(handler)
	handler = a.corsMiddleware(handler)
	return handler
}

func (a *App) handleHealth(w http.ResponseWriter, _ *http.Request) {
	writeJSON(w, http.StatusOK, HealthResponse{Status: "ok", ProblemsLoaded: len(a.catalog)})
}

func (a *App) handleListProblems(w http.ResponseWriter, r *http.Request) {
	query := strings.ToLower(strings.TrimSpace(r.URL.Query().Get("q")))
	problemTypeFilter := r.URL.Query().Get("problemType")
	limit := 50
	if rawLimit := r.URL.Query().Get("limit"); rawLimit != "" {
		parsed, err := strconv.Atoi(rawLimit)
		if err != nil || parsed < 1 || parsed > 500 {
			writeError(w, http.StatusUnprocessableEntity, "Invalid limit")
			return
		}
		limit = parsed
	}

	start := 0
	if cursor := r.URL.Query().Get("cursor"); cursor != "" {
		parsed, err := strconv.Atoi(cursor)
		if err != nil {
			writeError(w, http.StatusBadRequest, "Invalid cursor")
			return
		}
		if parsed > 0 {
			start = parsed
		}
	}

	items := make([]ProblemSummary, 0, len(a.catalog))
	for _, problem := range a.catalog {
		if problemTypeFilter != "" && problem.ProblemType != problemTypeFilter {
			continue
		}
		if query != "" {
			haystack := strings.ToLower(problem.ProblemType + "/" + problem.ExternalID + " " + problem.Title)
			if !strings.Contains(haystack, query) {
				continue
			}
		}
		items = append(items, ProblemSummary{
			ProblemType:  problem.ProblemType,
			ExternalID:   problem.ExternalID,
			Title:        nilIfEmpty(problem.Title),
			Runnable:     problem.Runnable,
			HasGenerator: len(problem.Generators) > 0,
			OutputOnly:   problem.OutputOnly,
		})
	}
	sortProblemSummaries(items)

	if start > len(items) {
		start = len(items)
	}
	end := min(start+limit, len(items))
	page := items[start:end]
	var nextCursor *string
	if end < len(items) {
		nextCursor = new(strconv.Itoa(end))
	}
	response := ProblemList{
		Problems:     page,
		ProblemTypes: a.problemTypeSummaries(),
		NextCursor:   nextCursor,
		Total:        len(items),
	}
	if problemTypeFilter != "" {
		if typeMeta, ok := a.typeMetadata[problemTypeFilter]; ok {
			response.TypeMetadata = &typeMeta
		}
	}
	writeJSON(w, http.StatusOK, response)
}

func (a *App) problemTypeSummaries() []ProblemTypeSummary {
	counts := make(map[string]int)
	runnableCounts := make(map[string]int)
	for _, problem := range a.catalog {
		counts[problem.ProblemType]++
		if problem.Runnable {
			runnableCounts[problem.ProblemType]++
		}
	}

	items := make([]ProblemTypeSummary, 0, len(counts))
	for problemType, total := range counts {
		label := ""
		if typeMeta, ok := a.typeMetadata[problemType]; ok {
			label = typeMeta.Label
		}
		items = append(items, ProblemTypeSummary{
			ProblemType: problemType,
			Label:       nilIfEmpty(label),
			Total:       total,
			Runnable:    runnableCounts[problemType],
		})
	}
	sortProblemTypeSummaries(items)
	return items
}

func (a *App) handleGetProblem(w http.ResponseWriter, r *http.Request) {
	problem, ok := a.lookupProblem(w, r)
	if !ok {
		return
	}
	detail := buildProblemDetail(problem)
	if a.stats != nil {
		total, err := a.stats.ProblemTotal(r.Context(), problem.ProblemType, problem.ExternalID)
		if err != nil {
			slog.Warn("stats_problem_total_failed", "problem_type", problem.ProblemType, "external_id", problem.ExternalID, "err", err)
		} else {
			detail.TotalExecutionCount = &total
		}
	}
	writeJSON(w, http.StatusOK, detail)
}

func (a *App) handleStats(w http.ResponseWriter, r *http.Request) {
	if a.stats == nil {
		writeError(w, http.StatusServiceUnavailable, "Statistics are temporarily unavailable")
		return
	}
	snapshot, err := a.stats.Snapshot(r.Context(), time.Now().UTC())
	if err != nil {
		slog.Warn("stats_snapshot_failed", "err", err)
		writeError(w, http.StatusServiceUnavailable, "Statistics are temporarily unavailable")
		return
	}
	writeJSON(w, http.StatusOK, StatsResponse{
		Total: snapshot.Total, Buckets: snapshot.Buckets,
		TopProblems: sortedTopProblems(snapshot, a.catalog),
	})
}

func (a *App) lookupProblem(w http.ResponseWriter, r *http.Request) (Problem, bool) {
	problemType := chi.URLParam(r, "problemType")
	externalID, err := url.PathUnescape(chi.URLParam(r, "externalId"))
	if err != nil {
		writeError(w, http.StatusBadRequest, "Invalid problem id")
		return Problem{}, false
	}
	problem, ok := a.catalog[[2]string{problemType, externalID}]
	if !ok {
		writeError(w, http.StatusNotFound, fmt.Sprintf("Problem not found: %s/%s", problemType, externalID))
		return Problem{}, false
	}
	return problem, true
}

func buildProblemDetail(problem Problem) ProblemDetail {
	return ProblemDetail{
		ProblemType:    problem.ProblemType,
		ExternalID:     problem.ExternalID,
		Title:          nilIfEmpty(problem.Title),
		ExternalLink:   nilIfEmpty(problem.ExternalLink),
		TimeLimitMS:    problem.TimeLimitMS,
		MemoryLimitMB:  problem.MemoryLimitMB,
		Description:    nilIfEmpty(problem.Description),
		IsSpecialJudge: problem.IsSpecialJudge,
		OutputOnly:     problem.OutputOnly,
		CorrectCodes:   mapCodeInfos(problem.CorrectCodes),
		Generators:     mapCodeInfos(problem.Generators),
		Singlegens:     mapCodeInfos(problem.Singlegens),
		Validator:      mapCodeInfo(problem.Validator),
		Checker:        mapCodeInfo(problem.Checker),
		Testcases:      mapTestcaseInfos(problem.Testcases),
	}
}

func mapCodeInfos(items []CodeFile) []CodeInfo {
	out := make([]CodeInfo, 0, len(items))
	for _, item := range items {
		out = append(out, CodeInfo{Filename: item.Filename, Language: item.Language, AuthorName: nilIfEmpty(item.AuthorName)})
	}
	return out
}

func mapCodeInfo(item *CodeFile) *CodeInfo {
	if item == nil {
		return nil
	}
	return &CodeInfo{Filename: item.Filename, Language: item.Language, AuthorName: nilIfEmpty(item.AuthorName)}
}

func mapTestcaseInfos(items []TestcaseFile) []TestcaseInfo {
	out := make([]TestcaseInfo, 0, len(items))
	for _, item := range items {
		out = append(out, TestcaseInfo{Filename: item.Filename, AuthorName: nilIfEmpty(item.AuthorName)})
	}
	return out
}

func (a *App) corsMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		origin := r.Header.Get("Origin")
		if OriginAllowed(a.settings, origin) {
			w.Header().Set("Access-Control-Allow-Origin", origin)
			w.Header().Set("Access-Control-Allow-Methods", "GET, POST")
			w.Header().Set("Access-Control-Allow-Headers", "Content-Type")
			w.Header().Set("Access-Control-Expose-Headers", requestIDHeader)
			w.Header().Set("Vary", "Origin")
		}
		if r.Method == http.MethodOptions {
			w.WriteHeader(http.StatusNoContent)
			return
		}
		next.ServeHTTP(w, r)
	})
}

func (a *App) requestIDMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		requestID := generateRequestID()
		w.Header().Set(requestIDHeader, requestID)
		ctx := context.WithValue(r.Context(), requestIDContextKey, requestID)
		next.ServeHTTP(w, r.WithContext(ctx))
	})
}

func (a *App) accessLogMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		requestID := requestIDFromContext(r.Context())
		start := time.Now()
		statusWriter := &responseRecorder{ResponseWriter: w, statusCode: http.StatusOK}
		remoteIP := clientIP(r)
		slog.Info(
			"request_start",
			"request_id", requestID,
			"method", r.Method,
			"path", r.URL.Path,
			"remote_ip", remoteIP,
			"user_agent", r.UserAgent(),
		)
		next.ServeHTTP(statusWriter, r)
		slog.Info(
			"request_done",
			"request_id", requestID,
			"method", r.Method,
			"path", r.URL.Path,
			"status", statusWriter.statusCode,
			"elapsed_ms", time.Since(start).Milliseconds(),
			"remote_ip", remoteIP,
			"user_agent", r.UserAgent(),
		)
	})
}

func (a *App) recoverMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		defer func() {
			if recovered := recover(); recovered != nil {
				slog.Error(
					"request_panic",
					"request_id", requestIDFromContext(r.Context()),
					"method", r.Method,
					"path", r.URL.Path,
					"panic", recovered,
				)
				if !responseStarted(w) {
					writeError(w, http.StatusInternalServerError, "Internal server error")
				}
			}
		}()
		next.ServeHTTP(w, r)
	})
}

type responseRecorder struct {
	http.ResponseWriter
	statusCode int
	// started reports whether the response status and headers have been sent.
	started bool
}

func (r *responseRecorder) WriteHeader(statusCode int) {
	if r.started {
		return
	}
	r.started = true
	r.statusCode = statusCode
	r.ResponseWriter.WriteHeader(statusCode)
}

func (r *responseRecorder) Write(payload []byte) (int, error) {
	if !r.started {
		r.WriteHeader(http.StatusOK)
	}
	return r.ResponseWriter.Write(payload)
}

func (r *responseRecorder) Unwrap() http.ResponseWriter {
	return r.ResponseWriter
}

func (r *responseRecorder) Started() bool {
	return r.started
}

func responseStarted(w http.ResponseWriter) bool {
	type startedResponse interface {
		Started() bool
	}
	state, ok := w.(startedResponse)
	return ok && state.Started()
}

func writeJSON(w http.ResponseWriter, statusCode int, payload any) {
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(statusCode)
	_ = json.NewEncoder(w).Encode(payload)
}

func writeError(w http.ResponseWriter, statusCode int, detail string) {
	writeJSON(w, statusCode, errorResponse{Detail: detail})
}

func generateRequestID() string {
	return fmt.Sprintf("req_%d", time.Now().UnixNano())
}

func requestIDFromContext(ctx context.Context) string {
	if value, ok := ctx.Value(requestIDContextKey).(string); ok {
		return value
	}
	return ""
}

func clientHost(r *http.Request) string {
	host, _, err := net.SplitHostPort(r.RemoteAddr)
	if err != nil {
		return r.RemoteAddr
	}
	return host
}

func forwardedClientIP(r *http.Request) string {
	if forwardedFor := r.Header.Get("X-Forwarded-For"); forwardedFor != "" {
		if first, _, ok := strings.Cut(forwardedFor, ","); ok {
			return strings.TrimSpace(first)
		}
		return strings.TrimSpace(forwardedFor)
	}
	return ""
}

func rateLimitClientKey(r *http.Request) string {
	if forwardedIP := forwardedClientIP(r); forwardedIP != "" {
		return forwardedIP
	}
	return clientHost(r)
}

func clientIP(r *http.Request) string {
	if forwardedIP := forwardedClientIP(r); forwardedIP != "" {
		return forwardedIP
	}
	if realIP := strings.TrimSpace(r.Header.Get("X-Real-IP")); realIP != "" {
		return realIP
	}
	return clientHost(r)
}

func nilIfEmpty(value string) *string {
	if strings.TrimSpace(value) == "" {
		return nil
	}
	return &value
}
