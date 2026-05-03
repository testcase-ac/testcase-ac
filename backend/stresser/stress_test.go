package main

import (
	"context"
	"fmt"
	"math/rand"
	"strconv"
	"strings"
	"testing"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
	"github.com/testcase-ac/testcase-ac/backend/internal/util"
)

func textProvider(id, content string) contracts.CaseProvider {
	return contracts.CaseProvider{
		Type:    contracts.CaseProviderText,
		ID:      id,
		Content: content,
	}
}

func generatorProvider(id string, code string) contracts.CaseProvider {
	return contracts.CaseProvider{
		Type:     contracts.CaseProviderGenerator,
		ID:       id,
		Code:     code,
		Language: contracts.LanguageCpp23,
	}
}

func singlegenProvider(id string, code string) contracts.CaseProvider {
	return contracts.CaseProvider{
		Type:     contracts.CaseProviderSinglegen,
		ID:       id,
		Code:     code,
		Language: contracts.LanguageCpp23,
	}
}

func TestOperationStressSmoke(t *testing.T) {
	result, err := fakeStresser(newFakeRuntime()).operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         "sum",
		TargetCodeLang:     contracts.LanguageCpp23,
		CorrectCode:        "sum",
		CorrectCodeLang:    contracts.LanguageCpp23,
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         1,
		CaseProviders: []contracts.CaseProvider{
			singlegenProvider("sg-1", "case:1 2"),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 1 {
		t.Fatalf("TotalCases = %d, want 1", result.TotalCases)
	}
	if result.CorrectCasesCount != 1 {
		t.Fatalf("CorrectCasesCount = %d, want 1", result.CorrectCasesCount)
	}
	if result.WrongCasesCount != 0 {
		t.Fatalf("WrongCasesCount = %d, want 0", result.WrongCasesCount)
	}
	if result.ExecutionFailedCasesCount != 0 {
		t.Fatalf("ExecutionFailedCasesCount = %d, want 0", result.ExecutionFailedCasesCount)
	}
}

func TestOperationStressFindsCounterexample(t *testing.T) {
	result, err := fakeStresser(newFakeRuntime()).operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         "buggy-three",
		TargetCodeLang:     contracts.LanguageCpp23,
		CorrectCode:        "sum",
		CorrectCodeLang:    contracts.LanguageCpp23,
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         4,
		CaseProviders: []contracts.CaseProvider{
			textProvider("tc-1", "1 2"),
			textProvider("tc-2", "1 1"),
			textProvider("tc-3", "3 7"),
			textProvider("tc-4", "10 9"),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 4 {
		t.Fatalf("TotalCases = %d, want 4", result.TotalCases)
	}
	if result.WrongCasesCount == 0 {
		t.Fatalf("WrongCasesCount = 0, want > 0")
	}
	if len(result.WrongCases) == 0 {
		t.Fatalf("WrongCases was empty")
	}
}

func TestOperationStressSurfaceRuntimeErrorVerdict(t *testing.T) {
	result, err := fakeStresser(newFakeRuntime()).operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         "rte",
		TargetCodeLang:     contracts.LanguageCpp23,
		CorrectCode:        "sum",
		CorrectCodeLang:    contracts.LanguageCpp23,
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         3,
		CaseProviders: []contracts.CaseProvider{
			generatorProvider("gen-rte", "case:1 2"),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 3 {
		t.Fatalf("TotalCases = %d, want 3", result.TotalCases)
	}
	if result.WrongCasesCount != 0 {
		t.Fatalf("WrongCasesCount = %d, want 0", result.WrongCasesCount)
	}
	if result.ExecutionFailedCasesCount != 3 {
		t.Fatalf("ExecutionFailedCasesCount = %d, want 3", result.ExecutionFailedCasesCount)
	}
	if len(result.ExecutionFailedCases) == 0 {
		t.Fatalf("ExecutionFailedCases was empty")
	}
	for _, failedCase := range result.ExecutionFailedCases {
		if failedCase.Reason != contracts.VerdictRuntimeError {
			t.Fatalf("execution failed reason = %q, want RTE", failedCase.Reason)
		}
		if failedCase.Stderr == nil || failedCase.Stderr.Text == "" {
			t.Fatalf("expected stderr for runtime error failure: %+v", failedCase)
		}
	}
}

func TestOperationStressCheckerMismatch(t *testing.T) {
	result, err := fakeStresser(newFakeRuntime()).operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         "wrong-output",
		TargetCodeLang:     contracts.LanguageCpp23,
		CorrectCode:        "sum",
		CorrectCodeLang:    contracts.LanguageCpp23,
		CheckerCode:        "checker",
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         3,
		CaseProviders: []contracts.CaseProvider{
			generatorProvider("gen-checker", "case:3 7"),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 3 {
		t.Fatalf("TotalCases = %d, want 3", result.TotalCases)
	}
	if result.WrongCasesCount != 3 {
		t.Fatalf("WrongCasesCount = %d, want 3", result.WrongCasesCount)
	}
	foundCheckerOutput := false
	for _, wrongCase := range result.WrongCases {
		if wrongCase.Stderr != nil {
			t.Fatalf("wrong case stderr = %+v, want empty submitted-code stderr", wrongCase.Stderr)
		}
		if wrongCase.CheckerOutput != nil && wrongCase.CheckerOutput.Text != "" {
			foundCheckerOutput = true
			break
		}
	}
	if !foundCheckerOutput {
		t.Fatalf("expected checker output in at least one counterexample: %+v", result.WrongCases)
	}
}

func TestOperationStressDetectsNullCharacterDifference(t *testing.T) {
	result, err := fakeStresser(newFakeRuntime()).operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         "null-sum",
		TargetCodeLang:     contracts.LanguageCpp23,
		CorrectCode:        "sum",
		CorrectCodeLang:    contracts.LanguageCpp23,
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         3,
		CaseProviders: []contracts.CaseProvider{
			generatorProvider("gen-null", "case:3 7"),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 3 {
		t.Fatalf("TotalCases = %d, want 3", result.TotalCases)
	}
	if result.WrongCasesCount != 3 {
		t.Fatalf("WrongCasesCount = %d, want 3", result.WrongCasesCount)
	}
	for _, wrongCase := range result.WrongCases {
		if wrongCase.Verdict == nil || *wrongCase.Verdict != contracts.VerdictWrongAnswer {
			t.Fatalf("counterexample verdict = %v, want WA", wrongCase.Verdict)
		}
	}
}

func TestOperationStressUsesMultipleGenerators(t *testing.T) {
	result, err := fakeStresser(newFakeRuntime()).operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         "wrong-one",
		TargetCodeLang:     contracts.LanguageCpp23,
		CorrectCode:        "sum",
		CorrectCodeLang:    contracts.LanguageCpp23,
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         40,
		CaseProviders: []contracts.CaseProvider{
			generatorProvider("gen-1", "case:1 1"),
			generatorProvider("gen-2", "case:2 2"),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases != 40 {
		t.Fatalf("TotalCases = %d, want 40", result.TotalCases)
	}
	if result.WrongCasesCount == 0 {
		t.Fatalf("WrongCasesCount = 0, want > 0")
	}
	if result.CorrectCasesCount == 0 {
		t.Fatalf("CorrectCasesCount = 0, want > 0")
	}
}

func TestOperationStressSkipsFailingGenerator(t *testing.T) {
	result, err := fakeStresser(newFakeRuntime()).operationStress(contracts.StressEvent{
		Operation:          contracts.OperationStress,
		TargetCode:         "sum",
		TargetCodeLang:     contracts.LanguageCpp23,
		CorrectCode:        "sum",
		CorrectCodeLang:    contracts.LanguageCpp23,
		TargetTimeLimit:    2,
		TargetMemoryLimit:  256,
		CorrectTimeLimit:   2,
		CorrectMemoryLimit: 256,
		Iterations:         50,
		CaseProviders: []contracts.CaseProvider{
			generatorProvider("gen-bad", "fail-generator"),
			generatorProvider("gen-good", "case:2 2"),
		},
	})
	if err != nil {
		t.Fatalf("operationStress() error = %v", err)
	}
	if result.Error {
		t.Fatalf("operationStress() returned error result: %+v", result)
	}
	if result.TotalCases >= 50 {
		t.Fatalf("TotalCases = %d, want < 50 to reflect skipped failing generator iterations", result.TotalCases)
	}
	if result.TotalCases < 40 {
		t.Fatalf("TotalCases = %d, want >= 40 so the healthy generator still dominates after failures", result.TotalCases)
	}
	if result.WrongCasesCount != 0 {
		t.Fatalf("WrongCasesCount = %d, want 0", result.WrongCasesCount)
	}
	if result.CorrectCasesCount != result.TotalCases {
		t.Fatalf("CorrectCasesCount = %d, want %d", result.CorrectCasesCount, result.TotalCases)
	}
}

func TestBuildStressResponseDedupsAndLimitsReturnedFailures(t *testing.T) {
	wrongCases := []stressIteration{
		{
			Testcase:      "9 9\n",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g3"},
			CorrectOutput: "18\n",
			TargetRun: targetRun{
				Verdict:      contracts.VerdictWrongAnswer,
				TargetOutput: "0\n",
			},
		},
		{
			Testcase:      "1 1\n",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g1"},
			CorrectOutput: "2\n",
			TargetRun: targetRun{
				Verdict:      contracts.VerdictWrongAnswer,
				TargetOutput: "0\n",
			},
		},
		{
			Testcase:      "1 1",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g1-dup"},
			CorrectOutput: "2\n",
			TargetRun: targetRun{
				Verdict:      contracts.VerdictWrongAnswer,
				TargetOutput: "1\n",
			},
		},
	}
	executionFailedCases := []stressIteration{
		{
			Testcase:      "2 2\n",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g2"},
			CorrectOutput: "4\n",
			TargetRun: targetRun{
				Verdict:      contracts.VerdictRuntimeError,
				TargetOutput: "",
				Stderr:       "boom",
			},
		},
		{
			Testcase:      "3 3\n",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g4"},
			CorrectOutput: "6\n",
			TargetRun: targetRun{
				Verdict:      contracts.VerdictTimeLimit,
				TargetOutput: "",
			},
		},
	}
	correctCases := []stressIteration{
		{
			Testcase:    "4 4\n",
			GeneratedBy: contracts.GeneratedBy{Stage: contracts.CaseProviderGenerator, ID: "g5"},
		},
	}

	result := buildStressResponse(wrongCases, executionFailedCases, correctCases, false)
	if result.TotalCases != 6 {
		t.Fatalf("TotalCases = %d, want 6", result.TotalCases)
	}
	if result.WrongCasesCount != 3 {
		t.Fatalf("WrongCasesCount = %d, want 3", result.WrongCasesCount)
	}
	if result.ExecutionFailedCasesCount != 2 {
		t.Fatalf("ExecutionFailedCasesCount = %d, want 2", result.ExecutionFailedCasesCount)
	}
	if result.CorrectCasesCount != 1 {
		t.Fatalf("CorrectCasesCount = %d, want 1", result.CorrectCasesCount)
	}
	if len(result.WrongCases) != 2 {
		t.Fatalf("len(WrongCases) = %d, want 2", len(result.WrongCases))
	}
	if len(result.ExecutionFailedCases) != 2 {
		t.Fatalf("len(ExecutionFailedCases) = %d, want 2", len(result.ExecutionFailedCases))
	}

	gotWrongTestcases := []string{
		result.WrongCases[0].Testcase.Text,
		result.WrongCases[1].Testcase.Text,
	}
	wantWrongTestcases := []string{"1 1\n", "9 9\n"}
	for i := range wantWrongTestcases {
		if gotWrongTestcases[i] != wantWrongTestcases[i] {
			t.Fatalf("WrongCases[%d].Testcase.Text = %q, want %q", i, gotWrongTestcases[i], wantWrongTestcases[i])
		}
	}

	gotFailedTestcases := []string{
		result.ExecutionFailedCases[0].Testcase.Text,
		result.ExecutionFailedCases[1].Testcase.Text,
	}
	wantFailedTestcases := []string{"2 2\n", "3 3\n"}
	for i := range wantFailedTestcases {
		if gotFailedTestcases[i] != wantFailedTestcases[i] {
			t.Fatalf("ExecutionFailedCases[%d].Testcase.Text = %q, want %q", i, gotFailedTestcases[i], wantFailedTestcases[i])
		}
	}
}

func TestBuildStressResponseCleansReturnedStdout(t *testing.T) {
	wrongCases := []stressIteration{
		{
			Testcase:      "1 2\n",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderText, ID: "tc"},
			CorrectOutput: "3  \n\n",
			TargetRun: targetRun{
				Verdict:       contracts.VerdictWrongAnswer,
				TargetOutput:  "4\t \n\n",
				CheckerOutput: "expected 3  \n",
			},
		},
	}
	executionFailedCases := []stressIteration{
		{
			Testcase:      "2 2\n",
			GeneratedBy:   contracts.GeneratedBy{Stage: contracts.CaseProviderText, ID: "tc-fail"},
			CorrectOutput: "4  \n\n",
			TargetRun: targetRun{
				Verdict: contracts.VerdictRuntimeError,
				Stderr:  "boom  \n\n",
			},
		},
	}

	result := buildStressResponse(wrongCases, executionFailedCases, nil, true)
	if got := result.WrongCases[0].TargetOutput.Text; got != "4" {
		t.Fatalf("TargetOutput.Text = %q, want %q", got, "4")
	}
	if got := result.WrongCases[0].CorrectOutput.Text; got != "3" {
		t.Fatalf("CorrectOutput.Text = %q, want %q", got, "3")
	}
	if result.WrongCases[0].CheckerOutput == nil {
		t.Fatalf("CheckerOutput = nil, want output")
	}
	if got := result.WrongCases[0].CheckerOutput.Text; got != "expected 3" {
		t.Fatalf("CheckerOutput.Text = %q, want %q", got, "expected 3")
	}
	if got := result.ExecutionFailedCases[0].CorrectOutput.Text; got != "4" {
		t.Fatalf("ExecutionFailed CorrectOutput.Text = %q, want %q", got, "4")
	}
	if got := result.ExecutionFailedCases[0].Stderr.Text; got != "boom  \n\n" {
		t.Fatalf("Stderr.Text = %q, want raw stderr", got)
	}
}

type fakeRuntime struct {
	compileFailures map[string]executor.CompileResult
}

func newFakeRuntime() *fakeRuntime {
	return &fakeRuntime{compileFailures: map[string]executor.CompileResult{}}
}

func fakeStresser(fake *fakeRuntime) stresser {
	return stresser{
		compile:    fake.compile,
		run:        fake.run,
		runChecker: fake.runChecker,
		newRandom: func() *rand.Rand {
			return rand.New(rand.NewSource(1))
		},
	}
}

func (f *fakeRuntime) compile(_ context.Context, source executor.Source) executor.CompileResult {
	if result, ok := f.compileFailures[source.Code]; ok {
		return result
	}
	program := &executor.CompiledProgram{
		Dir:      source.Code,
		Label:    source.Code,
		Language: source.Language,
		Limits:   source.Limits,
	}
	return executor.CompileResult{Success: true, Program: program}
}

func (f *fakeRuntime) run(_ context.Context, program executor.CompiledProgram, input string, args []string, _ executor.Limits) executor.ExecutionResult {
	switch program.Label {
	case "sum":
		return accepted(sumOutput(input))
	case "buggy-three":
		a, b := firstTwoInts(input)
		if a == 3 {
			return accepted(fmt.Sprintf("%d\n", a-b))
		}
		return accepted(fmt.Sprintf("%d\n", a+b))
	case "rte":
		return executor.ExecutionResult{Success: false, Verdict: contracts.VerdictRuntimeError, ReturnCode: 1, Stderr: "boom"}
	case "wrong-output":
		return accepted("0\n")
	case "null-sum":
		return accepted(strings.TrimSpace(sumOutput(input)) + "\x00")
	case "wrong-one":
		a, b := firstTwoInts(input)
		if a == 1 {
			return accepted(fmt.Sprintf("%d\n", a+b-1))
		}
		return accepted(fmt.Sprintf("%d\n", a+b))
	case "fail-generator":
		return executor.ExecutionResult{Success: false, Verdict: contracts.VerdictRuntimeError, ReturnCode: 1, Stderr: "generator failed"}
	}
	if content, ok := strings.CutPrefix(program.Label, "case:"); ok {
		if len(args) > 0 && args[0] == "" {
			return executor.ExecutionResult{Success: false, Verdict: contracts.VerdictInternalError, ReturnCode: -100}
		}
		return accepted(content + "\n")
	}
	return accepted(program.Label + "\n")
}

func (f *fakeRuntime) runChecker(_ context.Context, _ executor.CompiledProgram, input, participant, jury string, _ executor.Limits) executor.ExecutionResult {
	if util.CompareOutput(participant, jury) {
		return executor.ExecutionResult{Success: true, Verdict: contracts.VerdictAccepted, ReturnCode: 0}
	}
	return executor.ExecutionResult{
		Success:    true,
		Verdict:    contracts.VerdictWrongAnswer,
		ReturnCode: 1,
		Stdout:     fmt.Sprintf("expected %s got %s on %s", strings.TrimSpace(jury), strings.TrimSpace(participant), strings.TrimSpace(input)),
	}
}

func accepted(stdout string) executor.ExecutionResult {
	return executor.ExecutionResult{Success: true, Verdict: contracts.VerdictAccepted, ReturnCode: 0, Stdout: stdout}
}

func sumOutput(input string) string {
	a, b := firstTwoInts(input)
	return fmt.Sprintf("%d\n", a+b)
}

func firstTwoInts(input string) (int, int) {
	fields := strings.Fields(input)
	if len(fields) < 2 {
		return 0, 0
	}
	a, _ := strconv.Atoi(fields[0])
	b, _ := strconv.Atoi(fields[1])
	return a, b
}
