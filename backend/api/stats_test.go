package main

import (
	"bytes"
	"context"
	"encoding/json"
	"errors"
	"log/slog"
	"net/http"
	"net/http/httptest"
	"os"
	"path/filepath"
	"strconv"
	"strings"
	"testing"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func newTestStatsStore(t *testing.T) *StatsStore {
	t.Helper()
	store, err := OpenStatsStore(filepath.Join(t.TempDir(), "stats.db"))
	if err != nil {
		t.Fatal(err)
	}
	t.Cleanup(func() { _ = store.Close() })
	return store
}

func TestOpenStatsStoreDoesNotWriteAnExistingSchema(t *testing.T) {
	path := filepath.Join(t.TempDir(), "stats.db")
	store, err := OpenStatsStore(path)
	if err != nil {
		t.Fatal(err)
	}
	defer store.Close()

	ctx := context.Background()
	conn, err := store.db.Conn(ctx)
	if err != nil {
		t.Fatal(err)
	}
	defer conn.Close()
	if _, err := conn.ExecContext(ctx, "BEGIN IMMEDIATE"); err != nil {
		t.Fatal(err)
	}
	defer conn.ExecContext(ctx, "ROLLBACK")

	second, err := OpenStatsStore(path)
	if err != nil {
		t.Fatalf("OpenStatsStore() with an existing schema and active writer: %v", err)
	}
	defer second.Close()
}

func TestStatsStoreDispatchIsIdempotentAndTerminalDoesNotChangeCount(t *testing.T) {
	store := newTestStatsStore(t)
	ctx := context.Background()
	dispatchedAt := time.Date(2026, 7, 18, 1, 2, 3, 0, time.UTC)
	dispatch := StatsDispatch{
		RequestID: "req-1", ProblemType: "boj", ExternalID: "1000",
		DispatchedAt: dispatchedAt, TargetLanguage: new(string(contracts.LanguageCpp23)),
		Iterations: new(10), TextProviderCount: new(1), CheckerUsed: new(true),
	}
	if err := store.RecordDispatch(ctx, dispatch); err != nil {
		t.Fatal(err)
	}
	if err := store.RecordDispatch(ctx, dispatch); err != nil {
		t.Fatal(err)
	}
	if err := store.RecordTerminal(ctx, StatsTerminal{
		RequestID: "req-1", TerminalAt: dispatchedAt.Add(time.Second),
		Outcome: "invoke_failed",
	}); err != nil {
		t.Fatal(err)
	}

	total, err := store.ProblemTotal(ctx, "boj", "1000")
	if err != nil {
		t.Fatal(err)
	}
	if total != 1 {
		t.Fatalf("total = %d, want 1", total)
	}

	var targetLanguage, outcome string
	if err := store.db.QueryRowContext(ctx,
		`SELECT target_language, outcome FROM executions WHERE request_id = ?`, "req-1",
	).Scan(&targetLanguage, &outcome); err != nil {
		t.Fatal(err)
	}
	if targetLanguage != string(contracts.LanguageCpp23) {
		t.Fatalf("target_language = %q, want cpp23", targetLanguage)
	}
	if outcome != "invoke_failed" {
		t.Fatalf("outcome = %q, want invoke_failed", outcome)
	}
}

func TestStatsSnapshotUsesAligned168HourWindow(t *testing.T) {
	store := newTestStatsStore(t)
	ctx := context.Background()
	now := time.Date(2026, 7, 18, 12, 34, 56, 0, time.UTC)
	start := now.Truncate(time.Hour).Add(-167 * time.Hour)
	for _, dispatch := range []StatsDispatch{
		{RequestID: "before", ProblemType: "boj", ExternalID: "1", DispatchedAt: start.Add(-time.Nanosecond)},
		{RequestID: "first", ProblemType: "boj", ExternalID: "1", DispatchedAt: start},
		{RequestID: "current", ProblemType: "boj", ExternalID: "2", DispatchedAt: now},
		{RequestID: "future", ProblemType: "boj", ExternalID: "2", DispatchedAt: now.Add(time.Nanosecond)},
	} {
		if err := store.RecordDispatch(ctx, dispatch); err != nil {
			t.Fatal(err)
		}
	}

	snapshot, err := store.Snapshot(ctx, now)
	if err != nil {
		t.Fatal(err)
	}
	if len(snapshot.Buckets) != 168 {
		t.Fatalf("len(Buckets) = %d, want 168", len(snapshot.Buckets))
	}
	if snapshot.Total != 2 || snapshot.Buckets[0].Count != 1 || snapshot.Buckets[167].Count != 1 {
		t.Fatalf("snapshot = %+v, want two boundary executions", snapshot)
	}
	if !snapshot.Buckets[0].StartUTC.Equal(start) {
		t.Fatalf("first bucket = %s, want %s", snapshot.Buckets[0].StartUTC, start)
	}
	if snapshot.ProblemCounts[[2]string{"boj", "1"}] != 1 || snapshot.ProblemCounts[[2]string{"boj", "2"}] != 1 {
		t.Fatalf("ProblemCounts = %#v", snapshot.ProblemCounts)
	}
}

func TestReconcileJournalImportsLegacyDispatchAndRollsBackInvalidStream(t *testing.T) {
	store := newTestStatsStore(t)
	ctx := context.Background()
	legacy := journalLine(t, "cursor-1", time.Date(2026, 7, 17, 3, 0, 0, 0, time.UTC), map[string]any{
		"msg": "stress_dispatch", "request_id": "legacy", "problem_type": "boj", "external_id": "1000", "iterations": 100,
	})
	terminal := journalLine(t, "cursor-2", time.Date(2026, 7, 17, 3, 0, 1, 0, time.UTC), map[string]any{
		"msg": "stress_terminal", "request_id": "legacy", "outcome": "completed", "stress_status": "not_found", "total_cases": 4,
	})
	if err := store.reconcileJournal(ctx, bytes.NewReader(append(legacy, terminal...)), time.Date(2026, 7, 18, 0, 0, 0, 0, time.UTC), nil); err != nil {
		t.Fatal(err)
	}
	if err := store.reconcileJournal(ctx, bytes.NewReader(append(legacy, terminal...)), time.Date(2026, 7, 18, 0, 1, 0, 0, time.UTC), nil); err != nil {
		t.Fatal(err)
	}
	total, err := store.ProblemTotal(ctx, "boj", "1000")
	if err != nil || total != 1 {
		t.Fatalf("total = %d, err = %v, want 1", total, err)
	}
	state, err := store.ReconciliationState(ctx)
	if err != nil {
		t.Fatal(err)
	}
	if state.JournalCursor != "cursor-2" {
		t.Fatalf("cursor = %q, want cursor-2", state.JournalCursor)
	}
	var targetLanguage any
	if err := store.db.QueryRowContext(ctx,
		`SELECT target_language FROM executions WHERE request_id = ?`, "legacy",
	).Scan(&targetLanguage); err != nil {
		t.Fatal(err)
	}
	if targetLanguage != nil {
		t.Fatalf("target_language = %v, want nil for legacy event", targetLanguage)
	}

	bad := append(journalLine(t, "cursor-3", time.Now(), map[string]any{
		"msg": "stress_dispatch", "request_id": "rolled-back", "problem_type": "boj", "external_id": "2000",
	}), []byte("not-json\n")...)
	if err := store.reconcileJournal(ctx, bytes.NewReader(bad), time.Now(), nil); err == nil {
		t.Fatal("reconcileJournal() error = nil, want invalid stream error")
	}
	rolledBack, err := store.ProblemTotal(ctx, "boj", "2000")
	if err != nil || rolledBack != 0 {
		t.Fatalf("rolledBack total = %d, err = %v, want 0", rolledBack, err)
	}
}

func journalLine(t *testing.T, cursor string, at time.Time, message map[string]any) []byte {
	t.Helper()
	messageJSON, err := json.Marshal(message)
	if err != nil {
		t.Fatal(err)
	}
	line, err := json.Marshal(map[string]any{
		"__CURSOR":             cursor,
		"__REALTIME_TIMESTAMP": strconv.FormatInt(at.UnixMicro(), 10),
		"MESSAGE":              string(messageJSON),
	})
	if err != nil {
		t.Fatal(err)
	}
	return append(line, '\n')
}

func TestProblemDetailRemainsAvailableWithoutStats(t *testing.T) {
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10},
		map[[2]string]Problem{{"boj", "1000"}: basicStressProblem()},
		okStresserClient{},
	)
	req := httptest.NewRequest(http.MethodGet, "/api/problems/boj/1000", nil)
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)
	if rec.Code != http.StatusOK {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
	var problem ProblemDetail
	if err := json.Unmarshal(rec.Body.Bytes(), &problem); err != nil {
		t.Fatal(err)
	}
	if problem.TotalExecutionCount != nil {
		t.Fatalf("TotalExecutionCount = %v, want nil", problem.TotalExecutionCount)
	}
}

func TestStatsInitializationFailureDoesNotBreakAPI(t *testing.T) {
	blocked := filepath.Join(t.TempDir(), "not-a-directory")
	if err := os.WriteFile(blocked, []byte("x"), 0o644); err != nil {
		t.Fatal(err)
	}
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10, StatsDBPath: filepath.Join(blocked, "stats.db")},
		map[[2]string]Problem{{"boj", "1000"}: basicStressProblem()},
		okStresserClient{},
	)
	req := httptest.NewRequest(http.MethodGet, "/api/health", nil)
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)
	if rec.Code != http.StatusOK || app.stats != nil {
		t.Fatalf("health status = %d, stats = %v, want healthy API with stats disabled", rec.Code, app.stats)
	}
}

func TestProblemStressCountsCompletedCanceledAndInvokeFailed(t *testing.T) {
	for _, test := range []struct {
		name     string
		stresser StresserClient
	}{
		{name: "completed", stresser: okStresserClient{}},
		{name: "canceled", stresser: errorStresserClient{err: context.Canceled}},
		{name: "invoke failed", stresser: errorStresserClient{err: &StresserInvokeError{StatusCode: http.StatusServiceUnavailable, Detail: "unavailable"}}},
	} {
		t.Run(test.name, func(t *testing.T) {
			store := newTestStatsStore(t)
			app := newTestApp(
				Settings{RateLimitMax: 100, RateLimitWindowS: 10},
				map[[2]string]Problem{{"boj", "1000"}: basicStressProblem()},
				test.stresser,
			)
			app.stats = store
			req := httptest.NewRequest(http.MethodPost, "/api/problems/boj/1000/stress", bytes.NewReader(basicStressRequestBody(t)))
			rec := httptest.NewRecorder()
			app.Handler().ServeHTTP(rec, req)

			total, err := store.ProblemTotal(context.Background(), "boj", "1000")
			if err != nil {
				t.Fatal(err)
			}
			if total != 1 {
				t.Fatalf("total = %d, want 1; status = %d", total, rec.Code)
			}
		})
	}
}

func TestCustomStressDoesNotCount(t *testing.T) {
	store := newTestStatsStore(t)
	app := newTestApp(Settings{RateLimitMax: 100, RateLimitWindowS: 10}, nil, okStresserClient{})
	app.stats = store
	timeLimit, memoryLimit, iterations := 1000, 128, 1
	body, err := json.Marshal(StressRequest{
		TargetCode: "target", TargetCodeLang: contracts.LanguageCpp23,
		CorrectCode: "correct", CorrectCodeLang: contracts.LanguageCpp23,
		TimeLimitMS: &timeLimit, MemoryLimitMB: &memoryLimit, Iterations: &iterations,
		TextTestcases: []InlineTextcaseInput{{ID: "sample", Content: "1\n"}},
	})
	if err != nil {
		t.Fatal(err)
	}
	req := httptest.NewRequest(http.MethodPost, "/api/custom-invocation/stress", bytes.NewReader(body))
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)
	if rec.Code != http.StatusOK {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
	snapshot, err := store.Snapshot(context.Background(), time.Now().UTC())
	if err != nil || snapshot.Total != 0 {
		t.Fatalf("snapshot total = %d, err = %v, want 0", snapshot.Total, err)
	}
}

func TestProblemStatsEventsAreLoggedWithoutSQLite(t *testing.T) {
	var output bytes.Buffer
	original := slog.Default()
	slog.SetDefault(slog.New(slog.NewJSONHandler(&output, nil)))
	t.Cleanup(func() { slog.SetDefault(original) })

	_, _, _, ok := runProblemStress(
		context.Background(), basicStressProblem(),
		StressRequest{TargetCode: "target", TargetCodeLang: contracts.LanguageCpp23},
		"req-log", okStresserClient{}, nil,
	)
	if !ok {
		t.Fatal("runProblemStress() failed")
	}
	logs := output.String()
	for _, want := range []string{
		`"msg":"stress_dispatch"`,
		`"target_language":"cpp23"`,
		`"text_provider_count":1`,
		`"msg":"stress_terminal"`,
		`"outcome":"completed"`,
	} {
		if !strings.Contains(logs, want) {
			t.Fatalf("logs missing %s:\n%s", want, logs)
		}
	}
}

func TestOpenStatsStoreRejectsEmptyPath(t *testing.T) {
	_, err := OpenStatsStore("")
	if err == nil {
		t.Fatal("OpenStatsStore() error = nil")
	}
}

func TestReconcileModeRequiresStatsPath(t *testing.T) {
	err := runReconcileStats(context.Background(), Settings{})
	if err == nil || !errors.Is(err, errStatsDBPathRequired) {
		t.Fatalf("runReconcileStats() error = %v, want errStatsDBPathRequired", err)
	}
}
