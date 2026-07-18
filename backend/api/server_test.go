package main

import (
	"bytes"
	"context"
	"encoding/json"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func newTestApp(settings Settings, catalog map[[2]string]Problem, stresser StresserClient) *App {
	return NewAppWithTypeMetadata(settings, catalog, nil, stresser)
}

type fakeStresserClient struct {
	t            *testing.T
	wantTarget   contracts.Language
	wantCorrect  contracts.Language
	wantCaseLang contracts.Language
}

func (c *fakeStresserClient) Invoke(_ context.Context, event contracts.StressEvent) (contracts.StressResult, error) {
	if event.TargetCodeLang != c.wantTarget {
		c.t.Fatalf("TargetCodeLang = %q, want %q", event.TargetCodeLang, c.wantTarget)
	}
	if event.CorrectCodeLang != c.wantCorrect {
		c.t.Fatalf("CorrectCodeLang = %q, want %q", event.CorrectCodeLang, c.wantCorrect)
	}
	if len(event.CaseProviders) != 1 {
		c.t.Fatalf("len(CaseProviders) = %d, want 1", len(event.CaseProviders))
	}
	if event.CaseProviders[0].Language != c.wantCaseLang {
		c.t.Fatalf("CaseProviders[0].Language = %q, want %q", event.CaseProviders[0].Language, c.wantCaseLang)
	}
	return contracts.StressResult{
		RequestID:         event.RequestID,
		RuntimeSeconds:    2.345,
		Error:             false,
		CorrectCases:      []contracts.CorrectCase{{GeneratedBy: contracts.GeneratedBy{Stage: contracts.CaseProviderSinglegen, ID: "sg-1"}}},
		TotalCases:        1,
		CorrectCasesCount: 1,
	}, nil
}

type okStresserClient struct{}

func (c okStresserClient) Invoke(_ context.Context, event contracts.StressEvent) (contracts.StressResult, error) {
	return contracts.StressResult{
		RequestID:         event.RequestID,
		Error:             false,
		TotalCases:        1,
		CorrectCasesCount: 1,
	}, nil
}

type errorStresserClient struct {
	err error
}

func (c errorStresserClient) Invoke(_ context.Context, _ contracts.StressEvent) (contracts.StressResult, error) {
	return contracts.StressResult{}, c.err
}

type outputOnlyStresserClient struct {
	t *testing.T
}

func (c outputOnlyStresserClient) Invoke(_ context.Context, event contracts.StressEvent) (contracts.StressResult, error) {
	c.t.Helper()
	if event.Iterations != 1 {
		c.t.Fatalf("Iterations = %d, want 1", event.Iterations)
	}
	if len(event.CaseProviders) != 1 {
		c.t.Fatalf("len(CaseProviders) = %d, want 1", len(event.CaseProviders))
	}
	provider := event.CaseProviders[0]
	if provider.Type != contracts.CaseProviderText || provider.ID != contracts.OutputOnlyEmptyInputID || provider.Content != "" {
		c.t.Fatalf("CaseProviders[0] = %#v, want output-only empty text provider", provider)
	}
	return contracts.StressResult{
		RequestID:         event.RequestID,
		Error:             false,
		CorrectCases:      []contracts.CorrectCase{{GeneratedBy: contracts.GeneratedBy{Stage: provider.Type, ID: provider.ID}}},
		TotalCases:        1,
		CorrectCasesCount: 1,
	}, nil
}

func basicStressProblem() Problem {
	return Problem{
		ProblemType:   "boj",
		ExternalID:    "1000",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		CorrectCodes: []CodeFile{
			{Filename: "correct.cpp", Language: "cpp23", Content: "correct"},
		},
		Testcases: []TestcaseFile{
			{Filename: "sample.txt", Content: "1 2\n"},
		},
	}
}

func basicStressRequestBody(t *testing.T) []byte {
	t.Helper()

	iterations := 1
	body, err := json.Marshal(StressRequest{
		TargetCode:     "target",
		TargetCodeLang: "cpp23",
		Iterations:     &iterations,
	})
	if err != nil {
		t.Fatalf("json.Marshal() error = %v", err)
	}
	return body
}

func TestHandleStressOutputOnlyRunsEmptyStdin(t *testing.T) {
	problem := Problem{
		ProblemType:   "boj",
		ExternalID:    "2557",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		OutputOnly:    true,
		CorrectCodes: []CodeFile{
			{Filename: "correct.cpp", Language: contracts.LanguageCpp23, Content: "correct"},
		},
	}
	iterations := 25
	body, err := json.Marshal(StressRequest{
		TargetCode:         "target",
		TargetCodeLang:     contracts.LanguageCpp23,
		GeneratorFilenames: []string{},
		SinglegenFilenames: []string{},
		TestcaseFilenames:  []string{},
		Iterations:         &iterations,
	})
	if err != nil {
		t.Fatalf("json.Marshal() error = %v", err)
	}
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10},
		map[[2]string]Problem{{"boj", "2557"}: problem},
		outputOnlyStresserClient{t: t},
	)

	req := httptest.NewRequest(http.MethodPost, "/api/problems/boj/2557/stress", bytes.NewReader(body))
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)

	if rec.Code != http.StatusOK {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
	var response StressResponse
	if err := json.Unmarshal(rec.Body.Bytes(), &response); err != nil {
		t.Fatalf("json.Unmarshal() error = %v", err)
	}
	if response.CorrectCasesCount != 1 || len(response.AttemptedCases) != 1 {
		t.Fatalf("response = %+v, want one attempted output-only case", response)
	}
	if response.AttemptedCases[0].ID != contracts.OutputOnlyEmptyInputID {
		t.Fatalf("AttemptedCases[0].ID = %q, want %q", response.AttemptedCases[0].ID, contracts.OutputOnlyEmptyInputID)
	}
}

func TestHandleStressAcceptsSupportedTargetLanguages(t *testing.T) {
	for _, lang := range contracts.SupportedLanguageList {
		t.Run(string(lang), func(t *testing.T) {
			problem := Problem{
				ProblemType:   "boj",
				ExternalID:    "1000",
				TimeLimitMS:   2000,
				MemoryLimitMB: 256,
				CorrectCodes: []CodeFile{
					{Filename: "correct.any", Language: lang, Content: "correct"},
				},
				Singlegens: []CodeFile{
					{Filename: "singlegen.any", Language: lang, Content: "generator"},
				},
			}
			app := newTestApp(
				Settings{RateLimitMax: 100, RateLimitWindowS: 10},
				map[[2]string]Problem{{"boj", "1000"}: problem},
				&fakeStresserClient{t: t, wantTarget: lang, wantCorrect: lang, wantCaseLang: lang},
			)

			iterations := 1
			body, err := json.Marshal(StressRequest{
				TargetCode:     "target",
				TargetCodeLang: lang,
				Iterations:     &iterations,
			})
			if err != nil {
				t.Fatalf("json.Marshal() error = %v", err)
			}

			req := httptest.NewRequest(http.MethodPost, "/api/problems/boj/1000/stress", bytes.NewReader(body))
			rec := httptest.NewRecorder()
			app.Handler().ServeHTTP(rec, req)

			if rec.Code != http.StatusOK {
				t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
			}

			var response StressResponse
			if err := json.Unmarshal(rec.Body.Bytes(), &response); err != nil {
				t.Fatalf("json.Unmarshal() error = %v", err)
			}
			if response.Status != "not_found" {
				t.Fatalf("response.Status = %q, want %q", response.Status, "not_found")
			}
			if response.CorrectCasesCount != 1 {
				t.Fatalf("response.CorrectCasesCount = %d, want 1", response.CorrectCasesCount)
			}
			if response.RuntimeSeconds != 2.345 {
				t.Fatalf("response.RuntimeSeconds = %v, want 2.345", response.RuntimeSeconds)
			}
		})
	}
}

func TestHandleStressRejectsOversizedTargetCode(t *testing.T) {
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10},
		map[[2]string]Problem{{"boj", "1000"}: basicStressProblem()},
		okStresserClient{},
	)
	body, err := json.Marshal(StressRequest{
		TargetCode:     strings.Repeat("x", contracts.MaxSubmittedCodeBytes+1),
		TargetCodeLang: contracts.LanguageCpp23,
	})
	if err != nil {
		t.Fatalf("json.Marshal() error = %v", err)
	}

	req := httptest.NewRequest(http.MethodPost, "/api/problems/boj/1000/stress", bytes.NewReader(body))
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)

	if rec.Code != http.StatusUnprocessableEntity {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
	if !strings.Contains(rec.Body.String(), "targetCode must be at most 524288 bytes") {
		t.Fatalf("body = %s, want targetCode size limit error", rec.Body.String())
	}
}

func TestHandleStressReportsClientClosedWhenRequestContextCanceled(t *testing.T) {
	// Given: a valid stress request whose stresser invoke returns context.Canceled.
	problem := basicStressProblem()
	body := basicStressRequestBody(t)
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10},
		map[[2]string]Problem{{"boj", "1000"}: problem},
		errorStresserClient{err: context.Canceled},
	)
	req := httptest.NewRequest(http.MethodPost, "/api/problems/boj/1000/stress", bytes.NewReader(body))
	rec := httptest.NewRecorder()

	// When: the stress handler receives the cancellation from the stresser client.
	app.Handler().ServeHTTP(rec, req)

	// Then: the API reports client-closed request instead of stresser unavailable.
	if rec.Code != statusClientClosedRequest {
		t.Fatalf("status = %d, want %d; body = %s", rec.Code, statusClientClosedRequest, rec.Body.String())
	}

	var response errorResponse
	if err := json.Unmarshal(rec.Body.Bytes(), &response); err != nil {
		t.Fatalf("json.Unmarshal() error = %v", err)
	}
	if response.Detail != clientClosedRequestDetail {
		t.Fatalf("response.Detail = %q, want %q", response.Detail, clientClosedRequestDetail)
	}
}

func TestHandleStressKeepsStresserInvokeErrorWhenRequestContextActive(t *testing.T) {
	problem := basicStressProblem()
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10},
		map[[2]string]Problem{{"boj", "1000"}: problem},
		errorStresserClient{err: &StresserInvokeError{
			StatusCode: http.StatusServiceUnavailable,
			Detail:     "Stresser is unavailable, try again shortly.",
		}},
	)
	body := basicStressRequestBody(t)

	req := httptest.NewRequest(http.MethodPost, "/api/problems/boj/1000/stress", bytes.NewReader(body))
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)

	if rec.Code != http.StatusServiceUnavailable {
		t.Fatalf("status = %d, want %d; body = %s", rec.Code, http.StatusServiceUnavailable, rec.Body.String())
	}

	var response errorResponse
	if err := json.Unmarshal(rec.Body.Bytes(), &response); err != nil {
		t.Fatalf("json.Unmarshal() error = %v", err)
	}
	if response.Detail != "Stresser is unavailable, try again shortly." {
		t.Fatalf("response.Detail = %q, want stresser unavailable detail", response.Detail)
	}
}

func TestRateLimitUsesXForwardedFor(t *testing.T) {
	problem := Problem{
		ProblemType:   "boj",
		ExternalID:    "1000",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		CorrectCodes: []CodeFile{
			{Filename: "correct.cpp", Language: "cpp23", Content: "correct"},
		},
		Testcases: []TestcaseFile{
			{Filename: "sample.txt", Content: "1 2\n"},
		},
	}
	app := newTestApp(
		Settings{RateLimitMax: 1, RateLimitWindowS: 60},
		map[[2]string]Problem{{"boj", "1000"}: problem},
		okStresserClient{},
	)
	iterations := 1
	body, err := json.Marshal(StressRequest{
		TargetCode:     "target",
		TargetCodeLang: "cpp23",
		Iterations:     &iterations,
	})
	if err != nil {
		t.Fatalf("json.Marshal() error = %v", err)
	}

	first := httptest.NewRequest(http.MethodPost, "/api/problems/boj/1000/stress", bytes.NewReader(body))
	first.RemoteAddr = "127.0.0.1:10000"
	first.Header.Set("X-Forwarded-For", "203.0.113.10")
	firstRec := httptest.NewRecorder()
	app.Handler().ServeHTTP(firstRec, first)
	if firstRec.Code != http.StatusOK {
		t.Fatalf("first status = %d, body = %s", firstRec.Code, firstRec.Body.String())
	}

	second := httptest.NewRequest(http.MethodPost, "/api/problems/boj/1000/stress", bytes.NewReader(body))
	second.RemoteAddr = "127.0.0.1:10001"
	second.Header.Set("X-Forwarded-For", "203.0.113.10")
	secondRec := httptest.NewRecorder()
	app.Handler().ServeHTTP(secondRec, second)
	if secondRec.Code != http.StatusTooManyRequests {
		t.Fatalf("second status = %d, want %d; body = %s", secondRec.Code, http.StatusTooManyRequests, secondRec.Body.String())
	}

	third := httptest.NewRequest(http.MethodPost, "/api/problems/boj/1000/stress", bytes.NewReader(body))
	third.RemoteAddr = "127.0.0.1:10002"
	third.Header.Set("X-Forwarded-For", "203.0.113.11")
	thirdRec := httptest.NewRecorder()
	app.Handler().ServeHTTP(thirdRec, third)
	if thirdRec.Code != http.StatusOK {
		t.Fatalf("third status = %d, body = %s", thirdRec.Code, thirdRec.Body.String())
	}
}

func TestGetProblemAcceptsEscapedSlashExternalID(t *testing.T) {
	problem := Problem{
		ProblemType:   "koi",
		ExternalID:    "2020/1/elem/1",
		Title:         "박 터뜨리기",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		OutputOnly:    true,
	}
	app := newTestApp(
		Settings{RateLimitMax: 1, RateLimitWindowS: 60},
		map[[2]string]Problem{{"koi", "2020/1/elem/1"}: problem},
		okStresserClient{},
	)

	req := httptest.NewRequest(http.MethodGet, "/api/problems/koi/2020%2F1%2Felem%2F1", nil)
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)

	if rec.Code != http.StatusOK {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
	var response ProblemDetail
	if err := json.Unmarshal(rec.Body.Bytes(), &response); err != nil {
		t.Fatalf("json.Unmarshal() error = %v", err)
	}
	if response.ExternalID != "2020/1/elem/1" {
		t.Fatalf("ExternalID = %q, want nested id", response.ExternalID)
	}
	if !response.OutputOnly {
		t.Fatal("OutputOnly = false, want true")
	}
}

func TestListProblemsIncludesTypeMetadataWhenFiltered(t *testing.T) {
	problem := Problem{
		ProblemType:   "koi",
		ExternalID:    "2025/1/elem/1",
		Title:         "Test",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		CorrectCodes:  []CodeFile{{Filename: "correct.cpp", Language: contracts.LanguageCpp23}},
		Generators:    []CodeFile{{Filename: "generator.cpp", Language: contracts.LanguageCpp23}},
		Runnable:      true,
	}
	app := NewAppWithTypeMetadata(
		Settings{RateLimitMax: 1, RateLimitWindowS: 60},
		map[[2]string]Problem{{"koi", "2025/1/elem/1"}: problem},
		map[string]TypeMetadata{
			"koi": {
				Label: "KOI",
				Segments: []TypeMetadataSegment{
					{Label: "{}년"},
					{Label: "{}차대회"},
					{Labels: []TypeMetadataSegmentLabel{
						{Value: "elem", Label: "초등부"},
						{Value: "mid", Label: "중등부"},
						{Value: "high", Label: "고등부"},
					}},
					{Label: "{}번"},
				},
			},
		},
		okStresserClient{},
	)

	req := httptest.NewRequest(http.MethodGet, "/api/problems?problemType=koi", nil)
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)

	if rec.Code != http.StatusOK {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
	var response ProblemList
	if err := json.Unmarshal(rec.Body.Bytes(), &response); err != nil {
		t.Fatalf("json.Unmarshal() error = %v", err)
	}
	if response.TypeMetadata == nil {
		t.Fatal("TypeMetadata = nil, want metadata")
	}
	labels := response.TypeMetadata.Segments[2].Labels
	if len(labels) != 3 || labels[0].Value != "elem" || labels[1].Value != "mid" || labels[2].Value != "high" {
		t.Fatalf("labels = %#v, want elem/mid/high order", labels)
	}
	if len(response.ProblemTypes) != 1 {
		t.Fatalf("ProblemTypes = %#v, want one type", response.ProblemTypes)
	}
	if response.ProblemTypes[0].ProblemType != "koi" || response.ProblemTypes[0].Label == nil || *response.ProblemTypes[0].Label != "KOI" || response.ProblemTypes[0].Total != 1 || response.ProblemTypes[0].Runnable != 1 {
		t.Fatalf("ProblemTypes[0] = %#v, want KOI summary", response.ProblemTypes[0])
	}
	if len(response.Problems) != 1 || !response.Problems[0].Runnable {
		t.Fatalf("Problems = %#v, want runnable problem summary", response.Problems)
	}
}

func TestValidationDetailListsSupportedTargetLanguages(t *testing.T) {
	want := "targetCodeLang must be one of cpp23, cpp20, cpp17, cpp14, c11, c99, python3, java, nodejs, pypy3, golang, kotlin, rust2021, csharp"
	if got := supportedTargetCodeLangDetail; got != want {
		t.Fatalf("supportedTargetCodeLangDetail = %q, want %q", got, want)
	}
	for _, language := range contracts.SupportedLanguageList {
		if !strings.Contains(supportedTargetCodeLangDetail, string(language)) {
			t.Fatalf("supportedTargetCodeLangDetail missing language %q", language)
		}
	}
}

type inlineMaterialsStresserClient struct {
	t *testing.T
}

func (c *inlineMaterialsStresserClient) Invoke(_ context.Context, event contracts.StressEvent) (contracts.StressResult, error) {
	if event.CorrectCode != "inline-correct" {
		c.t.Fatalf("CorrectCode = %q, want inline-correct", event.CorrectCode)
	}
	if event.CorrectCodeLang != "python3" {
		c.t.Fatalf("CorrectCodeLang = %q, want python3", event.CorrectCodeLang)
	}
	if event.CheckerCode != "" {
		c.t.Fatalf("CheckerCode = %q, want empty override", event.CheckerCode)
	}
	if len(event.CaseProviders) != 2 {
		c.t.Fatalf("len(CaseProviders) = %d, want 2", len(event.CaseProviders))
	}
	if event.CaseProviders[0].Type != contracts.CaseProviderText || event.CaseProviders[1].Type != contracts.CaseProviderGenerator {
		c.t.Fatalf("CaseProviders = %#v, want inline text + generator", event.CaseProviders)
	}
	return contracts.StressResult{
		RequestID:         event.RequestID,
		RuntimeSeconds:    1.234,
		Error:             false,
		CorrectCases:      []contracts.CorrectCase{{GeneratedBy: contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "generator_inline.py", Seed: new("7")}}},
		TotalCases:        1,
		CorrectCasesCount: 1,
	}, nil
}

func TestHandleStressAcceptsInlineCustomMaterials(t *testing.T) {
	problem := Problem{
		ProblemType:   "boj",
		ExternalID:    "1000",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		CorrectCodes: []CodeFile{
			{Filename: "correct.cpp", Language: "cpp23", Content: "repo-correct"},
		},
		Checker: &CodeFile{Filename: "checker.cpp", Language: "cpp23", Content: "repo-checker"},
	}
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10},
		map[[2]string]Problem{{"boj", "1000"}: problem},
		&inlineMaterialsStresserClient{t: t},
	)

	body, err := json.Marshal(StressRequest{
		TargetCode:         "target",
		TargetCodeLang:     "cpp23",
		CorrectCode:        "inline-correct",
		CorrectCodeLang:    "python3",
		CheckerCode:        new(""),
		GeneratorSources:   []InlineCodeInput{{ID: "generator_inline.py", Code: "print(0)", Language: "python3"}},
		TextTestcases:      []InlineTextcaseInput{{ID: "sample.txt", Content: "1 2\n"}},
		GeneratorFilenames: []string{},
		SinglegenFilenames: []string{},
		TestcaseFilenames:  []string{},
	})
	if err != nil {
		t.Fatalf("json.Marshal() error = %v", err)
	}

	req := httptest.NewRequest(http.MethodPost, "/api/problems/boj/1000/stress", bytes.NewReader(body))
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)

	if rec.Code != http.StatusOK {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
}

type customInvocationStresserClient struct {
	t *testing.T
}

func (c *customInvocationStresserClient) Invoke(_ context.Context, event contracts.StressEvent) (contracts.StressResult, error) {
	if event.TargetTimeLimit != 2.5 {
		c.t.Fatalf("TargetTimeLimit = %.3f, want 2.5", event.TargetTimeLimit)
	}
	if event.TargetMemoryLimit != 384 {
		c.t.Fatalf("TargetMemoryLimit = %d, want 384", event.TargetMemoryLimit)
	}
	if event.CorrectTimeLimit != 2.5 {
		c.t.Fatalf("CorrectTimeLimit = %.3f, want 2.5", event.CorrectTimeLimit)
	}
	if event.CorrectMemoryLimit != 384 {
		c.t.Fatalf("CorrectMemoryLimit = %d, want 384", event.CorrectMemoryLimit)
	}
	return contracts.StressResult{
		RequestID:         event.RequestID,
		RuntimeSeconds:    1.234,
		Error:             false,
		CorrectCases:      []contracts.CorrectCase{{GeneratedBy: contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "generator_inline.py", Seed: new("7")}}},
		TotalCases:        1,
		CorrectCasesCount: 1,
	}, nil
}

func TestHandleCustomStressAcceptsExplicitLimits(t *testing.T) {
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10},
		map[[2]string]Problem{},
		&customInvocationStresserClient{t: t},
	)

	timeLimitMS := 2500
	memoryLimitMB := 384
	body, err := json.Marshal(StressRequest{
		TargetCode:      "target",
		TargetCodeLang:  "cpp23",
		TimeLimitMS:     &timeLimitMS,
		MemoryLimitMB:   &memoryLimitMB,
		CorrectCode:     "inline-correct",
		CorrectCodeLang: "python3",
		CheckerCode:     new(""),
		GeneratorSources: []InlineCodeInput{
			{ID: "generator_inline.py", Code: "print(0)", Language: "python3"},
		},
		TextTestcases: []InlineTextcaseInput{
			{ID: "sample.txt", Content: "1 2\n"},
		},
	})
	if err != nil {
		t.Fatalf("json.Marshal() error = %v", err)
	}

	req := httptest.NewRequest(http.MethodPost, "/api/custom-invocation/stress", bytes.NewReader(body))
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)

	if rec.Code != http.StatusOK {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
}

func TestHandleCustomStressRejectsOversizedLimits(t *testing.T) {
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10},
		map[[2]string]Problem{},
		&customInvocationStresserClient{t: t},
	)

	timeLimitMS := maxCustomTimeLimitMS + 1
	memoryLimitMB := maxCustomMemoryLimitMB + 1
	body, err := json.Marshal(StressRequest{
		TargetCode:      "target",
		TargetCodeLang:  "cpp23",
		TimeLimitMS:     &timeLimitMS,
		MemoryLimitMB:   &memoryLimitMB,
		CorrectCode:     "inline-correct",
		CorrectCodeLang: "cpp23",
		TextTestcases:   []InlineTextcaseInput{{ID: "sample.txt", Content: "1 2\n"}},
	})
	if err != nil {
		t.Fatalf("json.Marshal() error = %v", err)
	}

	req := httptest.NewRequest(http.MethodPost, "/api/custom-invocation/stress", bytes.NewReader(body))
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)

	if rec.Code != http.StatusUnprocessableEntity {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
	if !strings.Contains(rec.Body.String(), "timeLimitMs must be between 1 and 10000") {
		t.Fatalf("body = %s, want timeLimitMs range error", rec.Body.String())
	}
}

func TestHandleCustomStressRejectsOversizedTotalRuntimeLimit(t *testing.T) {
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10},
		map[[2]string]Problem{},
		&customInvocationStresserClient{t: t},
	)

	timeLimitMS := 2500
	memoryLimitMB := 384
	totalRuntimeLimitSeconds := contracts.MaxTotalRuntimeLimitSeconds + 1
	body, err := json.Marshal(StressRequest{
		TargetCode:               "target",
		TargetCodeLang:           "cpp23",
		TimeLimitMS:              &timeLimitMS,
		MemoryLimitMB:            &memoryLimitMB,
		TotalRuntimeLimitSeconds: &totalRuntimeLimitSeconds,
		CorrectCode:              "inline-correct",
		CorrectCodeLang:          "cpp23",
		TextTestcases:            []InlineTextcaseInput{{ID: "sample.txt", Content: "1 2\n"}},
	})
	if err != nil {
		t.Fatalf("json.Marshal() error = %v", err)
	}

	req := httptest.NewRequest(http.MethodPost, "/api/custom-invocation/stress", bytes.NewReader(body))
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)

	if rec.Code != http.StatusUnprocessableEntity {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
	if !strings.Contains(rec.Body.String(), "totalRuntimeLimitSeconds must be between 1 and 90") {
		t.Fatalf("body = %s, want totalRuntimeLimitSeconds range error", rec.Body.String())
	}
}

func TestHandleCustomStressRejectsOversizedBody(t *testing.T) {
	app := newTestApp(
		Settings{RateLimitMax: 100, RateLimitWindowS: 10},
		map[[2]string]Problem{},
		&customInvocationStresserClient{t: t},
	)

	body := strings.NewReader(`{"targetCode":"` + strings.Repeat("x", maxStressRequestBodyBytes) + `"}`)
	req := httptest.NewRequest(http.MethodPost, "/api/custom-invocation/stress", body)
	rec := httptest.NewRecorder()
	app.Handler().ServeHTTP(rec, req)

	if rec.Code != http.StatusRequestEntityTooLarge {
		t.Fatalf("status = %d, body = %s", rec.Code, rec.Body.String())
	}
	if !strings.Contains(rec.Body.String(), maxStressRequestBodyBytesMsg) {
		t.Fatalf("body = %s, want request body limit error", rec.Body.String())
	}
}
