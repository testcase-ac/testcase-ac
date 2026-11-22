package main

import (
	"bytes"
	"context"
	"encoding/json"
	"net/http"
	"net/http/httptest"
	"path/filepath"
	"slices"
	"strings"
	"testing"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/api/stresser"
	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

type submissionAuditTestClient struct{}

func (submissionAuditTestClient) Invoke(_ context.Context, event contracts.StressEvent, progress stresser.ProgressCallback) (contracts.StressResult, error) {
	if event.TargetCode == "compile-error" {
		return contracts.StressResult{Error: true, ErrorType: contracts.ErrorTypeTargetCompilationFailed}, nil
	}
	if progress == nil {
		return contracts.StressResult{TotalCases: 1, CorrectCasesCount: 1}, nil
	}
	if err := progress(contracts.StressProgress{Stage: contracts.StressProgressStageFinalizing}); err != nil {
		return contracts.StressResult{}, err
	}
	return contracts.StressResult{
		TotalCases:                7,
		WrongCasesCount:           1,
		ExecutionFailedCasesCount: 1,
		WrongCases: []contracts.Counterexample{{
			GeneratedBy: contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "generator_b.cpp", Seed: new("42")},
			Verdict:     new(contracts.VerdictWrongAnswer),
		}},
		ExecutionFailedCases: []contracts.ExecutionFailedCase{{
			GeneratedBy: contracts.GeneratedBy{Stage: contracts.CaseProviderText, ID: "sample.txt"},
			Reason:      contracts.VerdictTimeLimit,
		}},
	}, nil
}

func submitAuditTestRequest(t *testing.T, app *App, path string, payload StressRequest, stream bool) *httptest.ResponseRecorder {
	t.Helper()
	body, err := json.Marshal(payload)
	if err != nil {
		t.Fatal(err)
	}
	req := httptest.NewRequest(http.MethodPost, path, bytes.NewReader(body))
	if stream {
		req.Header.Set("Accept", stressStreamContentType)
	}
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)
	if rec.Code != http.StatusOK {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
	return rec
}

func TestSubmissionAuditRecordsBuiltInRuns(t *testing.T) {
	problem := basicStressProblem()
	problem.CorrectCodes = append(problem.CorrectCodes, CodeFile{Filename: "correct_other.cpp", Content: "other", Language: "cpp23"})
	problem.Generators = []CodeFile{
		{Filename: "generator_a.cpp", Content: "first generator", Language: "cpp23"},
		{Filename: "generator_b.cpp", Content: "second generator", Language: "cpp23"},
	}
	problem.Singlegens = []CodeFile{{Filename: "singlegen_max.cpp", Content: "single generator", Language: "cpp23"}}
	path := filepath.Join(t.TempDir(), "execution-stats.db")
	legacy, err := OpenStatsStore(path)
	if err != nil {
		t.Fatal(err)
	}
	t.Cleanup(func() { _ = legacy.Close() })
	if _, err := legacy.db.Exec("DROP TABLE submissions; PRAGMA user_version = 1"); err != nil {
		t.Fatal(err)
	}
	if err := legacy.RecordDispatch(t.Context(), StatsDispatch{
		RequestID: "existing", ProblemType: "boj", ExternalID: "1000", DispatchedAt: time.Now(),
	}); err != nil {
		t.Fatal(err)
	}
	if err := legacy.Close(); err != nil {
		t.Fatal(err)
	}

	settings := Settings{RateLimitMax: 100, RateLimitWindowS: 10, StatsDBPath: path, TestcaseRevision: "deployed-commit"}
	app := newTestApp(settings, map[[2]string]Problem{{"boj", "1000"}: problem}, submissionAuditTestClient{})
	if app.stats == nil {
		t.Fatal("stats store did not open")
	}
	t.Cleanup(func() { _ = app.stats.Close() })
	if total, err := app.stats.ProblemTotal(t.Context(), "boj", "1000"); err != nil || total != 1 {
		t.Fatalf("problem total after schema update = %d, want 1: %v", total, err)
	}

	const endpoint = "/api/problems/boj/1000/stress"
	const source = "//  Source formatting must be preserved.\r\n#include <cstdio>\n\n"
	defaultRun := submitAuditTestRequest(t, app, endpoint, StressRequest{TargetCode: source}, false)
	streamedRun := submitAuditTestRequest(t, app, endpoint, StressRequest{
		TargetCode:               source,
		TargetCodeLang:           contracts.LanguageCpp17,
		CorrectCodeFilename:      new("correct_other.cpp"),
		GeneratorFilenames:       []string{"generator_b.cpp"},
		Iterations:               new(5),
		TotalRuntimeLimitSeconds: new(12),
	}, true)
	if !strings.Contains(streamedRun.Body.String(), `"type":"result"`) {
		t.Fatalf("stream missing result: %s", streamedRun.Body.String())
	}

	for _, test := range []struct {
		requestID, status, reference, language string
		iterations, runtimeLimit, totalCases   int
		providers, samples                     string
	}{
		{defaultRun.Header().Get(requestIDHeader), "not_found", "correct.cpp", "cpp23", 100, 90, 1,
			`[{"kind":"text","id":"sample.txt"},{"kind":"generator","id":"generator_a.cpp"},{"kind":"generator","id":"generator_b.cpp"},{"kind":"singlegen","id":"singlegen_max.cpp"}]`, `[]`},
		{streamedRun.Header().Get(requestIDHeader), "found", "correct_other.cpp", "cpp17", 5, 12, 7,
			`[{"kind":"text","id":"sample.txt"},{"kind":"generator","id":"generator_b.cpp"},{"kind":"singlegen","id":"singlegen_max.cpp"}]`,
			`[{"stage":"generator","id":"generator_b.cpp","seed":"42","verdict":"WA"},{"stage":"text","id":"sample.txt","verdict":"TLE"}]`},
	} {
		var submittedAt, problemType, externalID, revision, language, target, reference, providers, status, samples string
		var iterations, runtimeLimit, totalCases int
		err := app.stats.db.QueryRow(`SELECT submitted_at_utc, problem_type, external_id, testcase_revision,
            target_language, target_source, reference_filename, providers_json, iterations, runtime_limit_seconds,
            status, total_cases, failure_samples_json FROM submissions WHERE request_id = ? AND EXISTS (
                SELECT 1 FROM executions WHERE executions.request_id = submissions.request_id AND stress_status = submissions.status
            )`, test.requestID).Scan(
			&submittedAt, &problemType, &externalID, &revision, &language, &target, &reference, &providers,
			&iterations, &runtimeLimit, &status, &totalCases, &samples,
		)
		if err != nil {
			t.Fatal(err)
		}
		if _, err := time.Parse(statsTimeLayout, submittedAt); err != nil {
			t.Fatal(err)
		}
		if got := []string{problemType, externalID, revision, language, target, reference, providers, status, samples}; !slices.Equal(got, []string{"boj", "1000", settings.TestcaseRevision, test.language, source, test.reference, test.providers, test.status, test.samples}) {
			t.Errorf("%s stored values = %q", test.status, got)
		}
		if iterations != test.iterations || runtimeLimit != test.runtimeLimit || totalCases != test.totalCases {
			t.Errorf("%s stored iterations = %d, runtime limit = %d, total cases = %d", test.status, iterations, runtimeLimit, totalCases)
		}
	}

	if _, err := app.stats.db.Exec(`CREATE TRIGGER reject_submission BEFORE INSERT ON submissions
        BEGIN SELECT RAISE(ABORT, 'audit write failed'); END`); err != nil {
		t.Fatal(err)
	}
	response := submitAuditTestRequest(t, app, endpoint, StressRequest{TargetCode: source}, false)
	if !strings.Contains(response.Body.String(), `"status":"not_found"`) {
		t.Fatalf("stress run failed when the audit write failed: %s", response.Body.String())
	}
	var status string
	if err := app.stats.db.QueryRow("SELECT stress_status FROM executions WHERE request_id = ?",
		response.Header().Get(requestIDHeader)).Scan(&status); err != nil || status != "not_found" {
		t.Fatalf("execution status after audit failure = %q, want not_found: %v", status, err)
	}
	var count int
	if err := app.stats.db.QueryRow("SELECT COUNT(*) FROM submissions").Scan(&count); err != nil || count != 2 {
		t.Fatalf("audit row count after audit failure = %d, want 2: %v", count, err)
	}
}

func TestSubmissionAuditRecordsCompileErrorsAndSkipsCustomRuns(t *testing.T) {
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10, StatsDBPath: filepath.Join(t.TempDir(), "execution-stats.db")},
		map[[2]string]Problem{{"boj", "1000"}: basicStressProblem()}, submissionAuditTestClient{},
	)
	if app.stats == nil {
		t.Fatal("stats store did not open")
	}
	t.Cleanup(func() { _ = app.stats.Close() })
	const endpoint = "/api/problems/boj/1000/stress"
	const source = "compile-error"
	compileError := submitAuditTestRequest(t, app, endpoint, StressRequest{TargetCode: source}, false)
	submitAuditTestRequest(t, app, endpoint, StressRequest{TargetCode: source, CorrectCode: "inline reference"}, false)
	submitAuditTestRequest(t, app, endpoint, StressRequest{TargetCode: "target", CorrectCode: "inline reference"}, false)
	submitAuditTestRequest(t, app, endpoint, StressRequest{TargetCode: "target", CheckerCode: new("inline checker")}, false)
	submitAuditTestRequest(t, app, endpoint, StressRequest{TargetCode: "target", TextTestcases: []InlineTextcaseInput{{ID: "inline", Content: "1 2\n"}}}, false)
	submitAuditTestRequest(t, app, endpoint, StressRequest{TargetCode: "target", GeneratorSources: []InlineCodeInput{{ID: "inline", Code: "inline generator", Language: "cpp23"}}}, false)
	submitAuditTestRequest(t, app, "/api/custom-invocation/stress", StressRequest{
		TargetCode: "target", CorrectCode: "inline reference", TimeLimitMS: new(1000), MemoryLimitMB: new(256),
		TextTestcases: []InlineTextcaseInput{{ID: "inline", Content: "1 2\n"}},
	}, false)

	var count int
	if err := app.stats.db.QueryRow("SELECT COUNT(*) FROM submissions").Scan(&count); err != nil {
		t.Fatal(err)
	}
	if count != 1 {
		t.Fatalf("stored %d submissions, want 1", count)
	}
	var target, language, status string
	err := app.stats.db.QueryRow("SELECT target_source, target_language, status FROM submissions WHERE request_id = ?",
		compileError.Header().Get(requestIDHeader)).Scan(&target, &language, &status)
	if err != nil || target != source || language != "cpp23" || status != "compile_error" {
		t.Fatalf("compile error audit = (%q, %q, %q), want (%q, cpp23, compile_error): %v", target, language, status, source, err)
	}
}
