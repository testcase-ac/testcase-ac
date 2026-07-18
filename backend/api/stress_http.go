package main

// This file handles HTTP parsing and response encoding for normal and custom
// stress requests. Stress orchestration remains in stress_service.go.

import (
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"log/slog"
	"net/http"
	"strings"

	"github.com/go-playground/validator/v10"
	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

const (
	maxStressRequestBodyBytes    = 2 << 20
	maxStressRequestBodyBytesMsg = "Request body must be at most 2 MiB"
	stressStreamContentType      = "application/x-ndjson"
)

type stressHTTPStreamRecord struct {
	Type     string                    `json:"type"`
	Progress *contracts.StressProgress `json:"progress,omitempty"`
	Result   *StressResponse           `json:"result,omitempty"`
}

func (a *App) handleStress(w http.ResponseWriter, r *http.Request) {
	problem, ok := a.lookupProblem(w, r)
	if !ok {
		return
	}
	if !a.checkRateLimit(w, r) {
		return
	}
	payload, ok := a.decodeStressRequest(w, r)
	if !ok {
		return
	}

	requestID := requestIDFromContext(r.Context())
	if acceptsStressStream(r) {
		a.handleStressStream(w, r, problem, payload, requestID)
		return
	}
	response, statusCode, detail, ok := runProblemStress(r.Context(), problem, payload, requestID, a.stresser, a.stats, nil)
	if !ok {
		writeError(w, statusCode, detail)
		return
	}
	writeJSON(w, http.StatusOK, response)
}

func (a *App) handleStressStream(w http.ResponseWriter, r *http.Request, problem Problem, payload StressRequest, requestID string) {
	w.Header().Set("Content-Type", stressStreamContentType)
	w.Header().Add("Vary", "Accept")
	encoder := json.NewEncoder(w)
	writeRecord := func(record stressHTTPStreamRecord) error {
		if !responseStarted(w) {
			w.WriteHeader(http.StatusOK)
		}
		if err := encoder.Encode(record); err != nil {
			return err
		}
		return http.NewResponseController(w).Flush()
	}

	response, statusCode, detail, ok := runProblemStress(
		r.Context(),
		problem,
		payload,
		requestID,
		a.stresser,
		a.stats,
		func(progress contracts.StressProgress) error {
			return writeRecord(stressHTTPStreamRecord{Type: "progress", Progress: &progress})
		},
	)
	if !ok {
		if responseStarted(w) {
			slog.Warn("stress_stream_failed", "request_id", requestID, "detail", detail)
			return
		}
		writeError(w, statusCode, detail)
		return
	}
	if err := writeRecord(stressHTTPStreamRecord{Type: "result", Result: &response}); err != nil {
		slog.Warn("stress_stream_failed", "request_id", requestID, "err", err)
	}
}

func (a *App) handleCustomStress(w http.ResponseWriter, r *http.Request) {
	if !a.checkRateLimit(w, r) {
		return
	}
	payload, ok := a.decodeStressRequest(w, r)
	if !ok {
		return
	}

	requestID := requestIDFromContext(r.Context())
	response, statusCode, detail, ok := RunCustomStress(r.Context(), payload, requestID, a.stresser)
	if !ok {
		writeError(w, statusCode, detail)
		return
	}
	writeJSON(w, http.StatusOK, response)
}

func acceptsStressStream(r *http.Request) bool {
	for value := range strings.SplitSeq(r.Header.Get("Accept"), ",") {
		mediaType, _, _ := strings.Cut(strings.TrimSpace(value), ";")
		if strings.TrimSpace(mediaType) == stressStreamContentType {
			return true
		}
	}
	return false
}

func (a *App) checkRateLimit(w http.ResponseWriter, r *http.Request) bool {
	clientKey := rateLimitClientKey(r)
	if !a.rateLimiter.Check(clientKey) {
		writeError(w, http.StatusTooManyRequests, fmt.Sprintf("Rate limit exceeded: %d submissions per %gs", a.rateLimiter.maxRequests, a.settings.RateLimitWindowS))
		return false
	}
	return true
}

func (a *App) decodeStressRequest(w http.ResponseWriter, r *http.Request) (StressRequest, bool) {
	var payload StressRequest
	decoder := json.NewDecoder(http.MaxBytesReader(w, r.Body, maxStressRequestBodyBytes))
	if err := decoder.Decode(&payload); err != nil {
		if isRequestBodyTooLarge(err) {
			writeError(w, http.StatusRequestEntityTooLarge, maxStressRequestBodyBytesMsg)
			return StressRequest{}, false
		}
		writeError(w, http.StatusBadRequest, "Invalid JSON body")
		return StressRequest{}, false
	}
	if err := a.validate.Struct(payload); err != nil {
		writeError(w, http.StatusUnprocessableEntity, validationDetail(err))
		return StressRequest{}, false
	}
	if len(payload.TargetCode) > contracts.MaxSubmittedCodeBytes {
		writeError(w, http.StatusUnprocessableEntity, fmt.Sprintf("targetCode must be at most %d bytes", contracts.MaxSubmittedCodeBytes))
		return StressRequest{}, false
	}
	if err := decoder.Decode(&struct{}{}); err != io.EOF {
		if isRequestBodyTooLarge(err) {
			writeError(w, http.StatusRequestEntityTooLarge, maxStressRequestBodyBytesMsg)
			return StressRequest{}, false
		}
		writeError(w, http.StatusBadRequest, "Invalid JSON body")
		return StressRequest{}, false
	}
	return payload, true
}

func isRequestBodyTooLarge(err error) bool {
	var maxBytesErr *http.MaxBytesError
	return errors.As(err, &maxBytesErr)
}

func validationDetail(err error) string {
	validationErrs, ok := err.(validator.ValidationErrors)
	if !ok || len(validationErrs) == 0 {
		return "Invalid request body"
	}

	fieldErr := validationErrs[0]
	fieldName := fieldErr.Field()
	namespace := fieldErr.Namespace()

	switch {
	case fieldName == "TargetCode":
		return "targetCode is required"
	case fieldName == "CorrectCode":
		return "correctCode must not be empty"
	case fieldName == "TimeLimitMS":
		return fmt.Sprintf("timeLimitMs must be between %d and %d", minCustomTimeLimitMS, maxCustomTimeLimitMS)
	case fieldName == "MemoryLimitMB":
		return fmt.Sprintf("memoryLimitMb must be between %d and %d", minCustomMemoryLimitMB, maxCustomMemoryLimitMB)
	case fieldName == "Iterations":
		return "iterations must be between 1 and 500"
	case fieldName == "TotalRuntimeLimitSeconds":
		return fmt.Sprintf("totalRuntimeLimitSeconds must be between %d and %d", contracts.MinTotalRuntimeLimitSeconds, contracts.MaxTotalRuntimeLimitSeconds)
	case fieldName == "TargetCodeLang":
		return supportedTargetCodeLangDetail
	case fieldName == "CorrectCodeLang":
		return supportedCorrectCodeLangDetail
	case strings.Contains(namespace, "GeneratorFilenames"):
		return "generatorFilenames must not contain empty filenames"
	case strings.Contains(namespace, "SinglegenFilenames"):
		return "singlegenFilenames must not contain empty filenames"
	case strings.Contains(namespace, "TestcaseFilenames"):
		return "testcaseFilenames must not contain empty filenames"
	default:
		return "Invalid request body"
	}
}
