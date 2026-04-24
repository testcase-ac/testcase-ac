package main

import (
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

func TestAdjustedExecutionLimitsAppliesBojLanguagePolicies(t *testing.T) {
	tests := []struct {
		name         string
		lang         contracts.Language
		timeLimitMS  int
		memoryLimit  int
		wantTimeS    float64
		wantMemoryMB int
	}{
		{name: "nodejs", lang: "nodejs", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 8, wantMemoryMB: 256},
		{name: "csharp", lang: "csharp", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 5, wantMemoryMB: 272},
		{name: "python3", lang: "python3", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 8, wantMemoryMB: 288},
		{name: "pypy3", lang: "pypy3", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 8, wantMemoryMB: 384},
		{name: "golang", lang: "golang", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 4, wantMemoryMB: 640},
		{name: "rust2021", lang: "rust2021", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 2, wantMemoryMB: 144},
		{name: "cpp23 default", lang: "cpp23", timeLimitMS: 2000, memoryLimit: 128, wantTimeS: 2, wantMemoryMB: 128},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			gotTimeS, gotMemoryMB := adjustedExecutionLimits("boj", tt.lang, tt.timeLimitMS, tt.memoryLimit)
			if gotTimeS != tt.wantTimeS {
				t.Fatalf("adjustedExecutionLimits() time = %.3f, want %.3f", gotTimeS, tt.wantTimeS)
			}
			if gotMemoryMB != tt.wantMemoryMB {
				t.Fatalf("adjustedExecutionLimits() memory = %d, want %d", gotMemoryMB, tt.wantMemoryMB)
			}
		})
	}
}

func TestAdjustedExecutionLimitsLeavesNonBojLimitsUntouched(t *testing.T) {
	gotTimeS, gotMemoryMB := adjustedExecutionLimits("cf", contracts.LanguageNodeJS, 2000, 128)
	if gotTimeS != 2 {
		t.Fatalf("adjustedExecutionLimits() time = %.3f, want 2", gotTimeS)
	}
	if gotMemoryMB != 128 {
		t.Fatalf("adjustedExecutionLimits() memory = %d, want 128", gotMemoryMB)
	}
}

func TestBuildStresserEventAppliesAdjustedLimitsPerLanguage(t *testing.T) {
	iterations := 1
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
			TargetCode:          "console.log(0)",
			TargetCodeLang:      "nodejs",
			CorrectCodeFilename: stringPtr("correct.py"),
			TestcaseFilenames:   []string{"sample.txt"},
			Iterations:          &iterations,
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

func TestBuildCustomStresserEventUsesExplicitLimits(t *testing.T) {
	timeLimitMS := 3500
	memoryLimitMB := 768
	iterations := 9
	checkerCode := "#include <bits/stdc++.h>\nint main(){return 0;}\n"

	event, statusCode, detail, ok := BuildCustomStresserEvent(
		StressRequest{
			TargetCode:      "target",
			TargetCodeLang:  "golang",
			TimeLimitMS:     &timeLimitMS,
			MemoryLimitMB:   &memoryLimitMB,
			CorrectCode:     "correct",
			CorrectCodeLang: "python3",
			CheckerCode:     &checkerCode,
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
}
