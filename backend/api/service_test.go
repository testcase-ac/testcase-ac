package main

import (
	"net/http"
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func TestBuildStresserEventAppliesAdjustedLimitsPerLanguage(t *testing.T) {
	iterations := 1
	totalRuntimeLimitSeconds := 17
	event, statusCode, detail, ok := BuildStresserEvent(
		Problem{
			ProblemType:   "boj",
			ExternalID:    "1000",
			TimeLimitMS:   2000,
			MemoryLimitMB: 128,
			CorrectCodes: []CodeFile{
				{Filename: "correct.py", Language: "python3", Content: "print(0)"},
			},
			Testcases: []TestcaseFile{
				{Filename: "sample.txt", Content: "1 2\n"},
			},
		},
		StressRequest{
			TargetCode:               "console.log(0)",
			TargetCodeLang:           "nodejs",
			CorrectCodeFilename:      new("correct.py"),
			TestcaseFilenames:        []string{"sample.txt"},
			Iterations:               &iterations,
			TotalRuntimeLimitSeconds: &totalRuntimeLimitSeconds,
		},
		"req-test",
	)
	if !ok {
		t.Fatalf("BuildStresserEvent() failed: status=%d detail=%q", statusCode, detail)
	}
	if event.TargetTimeLimit != 8 {
		t.Fatalf("TargetTimeLimit = %.3f, want 8", event.TargetTimeLimit)
	}
	if event.TargetMemoryLimit != 256 {
		t.Fatalf("TargetMemoryLimit = %d, want 256", event.TargetMemoryLimit)
	}
	if event.CorrectTimeLimit != 8 {
		t.Fatalf("CorrectTimeLimit = %.3f, want 8", event.CorrectTimeLimit)
	}
	if event.CorrectMemoryLimit != 288 {
		t.Fatalf("CorrectMemoryLimit = %d, want 288", event.CorrectMemoryLimit)
	}
	if event.TotalRuntimeLimitSeconds != totalRuntimeLimitSeconds {
		t.Fatalf("TotalRuntimeLimitSeconds = %d, want %d", event.TotalRuntimeLimitSeconds, totalRuntimeLimitSeconds)
	}
}

func TestBuildStresserEventUsesInlineMaterialsWhenProvided(t *testing.T) {
	iterations := 7
	checkerCode := "#include <bits/stdc++.h>\nint main() { return 0; }\n"
	event, statusCode, detail, ok := BuildStresserEvent(
		Problem{
			ProblemType:   "boj",
			ExternalID:    "1000",
			TimeLimitMS:   2000,
			MemoryLimitMB: 128,
			CorrectCodes: []CodeFile{
				{Filename: "correct_repo.cpp", Language: "cpp23", Content: "repo-correct"},
			},
			Generators: []CodeFile{
				{Filename: "generator_repo.cpp", Language: "cpp23", Content: "repo-generator"},
			},
			Singlegens: []CodeFile{
				{Filename: "singlegen_repo.cpp", Language: "cpp23", Content: "repo-singlegen"},
			},
			Testcases: []TestcaseFile{
				{Filename: "testcase_repo.txt", Content: "1 2\n"},
			},
			Checker: &CodeFile{Filename: "checker.cpp", Language: "cpp23", Content: "repo-checker"},
		},
		StressRequest{
			TargetCode:         "target",
			TargetCodeLang:     "python3",
			CorrectCode:        "inline-correct",
			CorrectCodeLang:    "nodejs",
			CheckerCode:        &checkerCode,
			GeneratorFilenames: []string{},
			SinglegenFilenames: []string{},
			TestcaseFilenames:  []string{},
			GeneratorSources: []InlineCodeInput{
				{ID: "generator_inline.py", Code: "print(0)", Language: "python3"},
			},
			TextTestcases: []InlineTextcaseInput{
				{ID: "testcase_inline.txt", Content: "3 4\n"},
			},
			Iterations: &iterations,
		},
		"req-inline",
	)
	if !ok {
		t.Fatalf("BuildStresserEvent() failed: status=%d detail=%q", statusCode, detail)
	}
	if event.CorrectCode != "inline-correct" {
		t.Fatalf("CorrectCode = %q, want inline-correct", event.CorrectCode)
	}
	if event.CorrectCodeLang != "nodejs" {
		t.Fatalf("CorrectCodeLang = %q, want nodejs", event.CorrectCodeLang)
	}
	if event.CheckerCode != checkerCode {
		t.Fatalf("CheckerCode = %q, want inline override", event.CheckerCode)
	}
	if event.Iterations != iterations {
		t.Fatalf("Iterations = %d, want %d", event.Iterations, iterations)
	}
	if len(event.CaseProviders) != 2 {
		t.Fatalf("len(CaseProviders) = %d, want 2", len(event.CaseProviders))
	}
	if event.CaseProviders[0].Type != contracts.CaseProviderText || event.CaseProviders[0].ID != "testcase_inline.txt" {
		t.Fatalf("CaseProviders[0] = %#v, want inline text testcase", event.CaseProviders[0])
	}
	if event.CaseProviders[1].Type != contracts.CaseProviderGenerator || event.CaseProviders[1].ID != "generator_inline.py" {
		t.Fatalf("CaseProviders[1] = %#v, want inline generator", event.CaseProviders[1])
	}
	if event.TargetTimeLimit != 8 {
		t.Fatalf("TargetTimeLimit = %.3f, want 8", event.TargetTimeLimit)
	}
	if event.CorrectTimeLimit != 8 {
		t.Fatalf("CorrectTimeLimit = %.3f, want 8", event.CorrectTimeLimit)
	}
}

func TestBuildStresserEventOutputOnlyInjectsEmptyTextProvider(t *testing.T) {
	iterations := 37
	event, statusCode, detail, ok := BuildStresserEvent(
		Problem{
			ProblemType:   "boj",
			ExternalID:    "2557",
			TimeLimitMS:   2000,
			MemoryLimitMB: 128,
			OutputOnly:    true,
			CorrectCodes: []CodeFile{
				{Filename: "correct.cpp", Language: "cpp23", Content: "correct"},
			},
		},
		StressRequest{
			TargetCode:         "target",
			TargetCodeLang:     "cpp23",
			GeneratorFilenames: []string{},
			SinglegenFilenames: []string{},
			TestcaseFilenames:  []string{},
			GeneratorSources:   []InlineCodeInput{},
			TextTestcases:      []InlineTextcaseInput{},
			Iterations:         &iterations,
		},
		"req-output-only",
	)
	if !ok {
		t.Fatalf("BuildStresserEvent() failed: status=%d detail=%q", statusCode, detail)
	}
	if event.Iterations != 1 {
		t.Fatalf("Iterations = %d, want 1", event.Iterations)
	}
	if len(event.CaseProviders) != 1 {
		t.Fatalf("len(CaseProviders) = %d, want 1", len(event.CaseProviders))
	}
	provider := event.CaseProviders[0]
	if provider.Type != contracts.CaseProviderText || provider.ID != contracts.OutputOnlyEmptyInputID || provider.Content != "" {
		t.Fatalf("CaseProviders[0] = %#v, want empty text provider", provider)
	}
}

func TestBuildStresserEventOutputOnlyRejectsNonEmptyProviderInputs(t *testing.T) {
	nonEmptyGeneratorSource := []InlineCodeInput{{ID: "generator_inline.py", Code: "print(0)", Language: contracts.LanguagePython3}}
	nonEmptyTextTestcase := []InlineTextcaseInput{{ID: "sample.txt", Content: "1\n"}}
	tests := []struct {
		name    string
		request StressRequest
	}{
		{
			name:    "generator filename",
			request: StressRequest{GeneratorFilenames: []string{"generator.cpp"}},
		},
		{
			name:    "singlegen filename",
			request: StressRequest{SinglegenFilenames: []string{"singlegen.cpp"}},
		},
		{
			name:    "testcase filename",
			request: StressRequest{TestcaseFilenames: []string{"testcase.txt"}},
		},
		{
			name:    "inline generator",
			request: StressRequest{GeneratorSources: nonEmptyGeneratorSource},
		},
		{
			name:    "inline testcase",
			request: StressRequest{TextTestcases: nonEmptyTextTestcase},
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			tt.request.TargetCode = "target"
			tt.request.TargetCodeLang = "cpp23"
			_, statusCode, detail, ok := BuildStresserEvent(
				Problem{
					ProblemType:   "boj",
					ExternalID:    "2557",
					TimeLimitMS:   2000,
					MemoryLimitMB: 128,
					OutputOnly:    true,
					CorrectCodes: []CodeFile{
						{Filename: "correct.cpp", Language: "cpp23", Content: "correct"},
					},
				},
				tt.request,
				"req-output-only",
			)
			if ok {
				t.Fatal("BuildStresserEvent() succeeded, want failure")
			}
			if statusCode != http.StatusBadRequest {
				t.Fatalf("statusCode = %d, want %d; detail=%q", statusCode, http.StatusBadRequest, detail)
			}
		})
	}
}

func TestBuildCustomStresserEventUsesExplicitLimits(t *testing.T) {
	timeLimitMS := 3500
	memoryLimitMB := 768
	iterations := 9
	totalRuntimeLimitSeconds := 12
	checkerCode := "#include <bits/stdc++.h>\nint main(){return 0;}\n"

	event, statusCode, detail, ok := BuildCustomStresserEvent(
		StressRequest{
			TargetCode:               "target",
			TargetCodeLang:           "golang",
			TimeLimitMS:              &timeLimitMS,
			MemoryLimitMB:            &memoryLimitMB,
			CorrectCode:              "correct",
			CorrectCodeLang:          "python3",
			CheckerCode:              &checkerCode,
			TotalRuntimeLimitSeconds: &totalRuntimeLimitSeconds,
			GeneratorSources: []InlineCodeInput{
				{ID: "generator_inline.py", Code: "print(0)", Language: "python3"},
			},
			TextTestcases: []InlineTextcaseInput{
				{ID: "sample.txt", Content: "1 2\n"},
			},
			Iterations: &iterations,
		},
		"req-custom",
	)
	if !ok {
		t.Fatalf("BuildCustomStresserEvent() failed: status=%d detail=%q", statusCode, detail)
	}
	if event.TargetTimeLimit != 3.5 {
		t.Fatalf("TargetTimeLimit = %.3f, want 3.5", event.TargetTimeLimit)
	}
	if event.CorrectTimeLimit != 3.5 {
		t.Fatalf("CorrectTimeLimit = %.3f, want 3.5", event.CorrectTimeLimit)
	}
	if event.TargetMemoryLimit != 768 {
		t.Fatalf("TargetMemoryLimit = %d, want 768", event.TargetMemoryLimit)
	}
	if event.CorrectMemoryLimit != 768 {
		t.Fatalf("CorrectMemoryLimit = %d, want 768", event.CorrectMemoryLimit)
	}
	if event.CorrectCodeLang != "python3" {
		t.Fatalf("CorrectCodeLang = %q, want python3", event.CorrectCodeLang)
	}
	if len(event.CaseProviders) != 2 {
		t.Fatalf("len(CaseProviders) = %d, want 2", len(event.CaseProviders))
	}
	if event.Iterations != 9 {
		t.Fatalf("Iterations = %d, want 9", event.Iterations)
	}
	if event.TotalRuntimeLimitSeconds != totalRuntimeLimitSeconds {
		t.Fatalf("TotalRuntimeLimitSeconds = %d, want %d", event.TotalRuntimeLimitSeconds, totalRuntimeLimitSeconds)
	}
}

func TestTransformStresserResponseMapsCompilationTimeout(t *testing.T) {
	response := transformStresserResponse(contracts.StressResult{
		Error:     true,
		ErrorType: contracts.ErrorTypeCompilationTimedOut,
		Message:   `{"message":"Compilation did not finish before the total runtime limit."}`,
	}, "req-timeout")

	if response.Status != contracts.StressStatusCompileTimeout {
		t.Fatalf("Status = %q, want %q", response.Status, contracts.StressStatusCompileTimeout)
	}
	if response.ErrorMessage == nil || *response.ErrorMessage != "Compilation did not finish before the total runtime limit." {
		t.Fatalf("ErrorMessage = %v, want timeout detail", response.ErrorMessage)
	}
}
