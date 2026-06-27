package verify

import (
	"context"
	"fmt"
	"reflect"
	"strings"
	"testing"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
)

func TestMissingValidatorFails(t *testing.T) {
	problem := fakeProblem(
		[]string{"correct_main.py"},
		nil,
		[]loader.TestcaseFile{{Filename: "testcase_1.txt", Content: "1\n"}},
		false,
	)

	report := fakeVerifier(newFakeExecutor()).verifyProblem(context.Background(), problem)

	if !report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = false, want true")
	}
	if !hasFinding(report, SeverityError, StageStatic, "validator.cpp") {
		t.Fatalf("expected missing validator finding, got %+v", report.Findings)
	}
}

func TestWarningFindingDoesNotMarkReportFailed(t *testing.T) {
	problem := fakeProblem(
		nil,
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "testcase_1.txt", Content: "1\n"}},
		false,
	)

	report := fakeVerifier(newFakeExecutor()).verifyProblem(context.Background(), problem)

	if report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = true, findings = %+v", report.Findings)
	}
	if !hasFinding(report, SeverityWarning, StageStatic, "") {
		t.Fatalf("expected no-correct warning finding, got %+v", report.Findings)
	}
}

func TestLocalValidatorInspectionArtifactsDoNotFailStaticVerification(t *testing.T) {
	problem := fakeProblem(
		[]string{"correct_main.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "testcase_1.txt", Content: "1\n"}},
		false,
	)
	problem.UnknownFiles = []string{
		"validator_inspection_summary.txt",
		"testcase_validator_inspection_case.txt",
		"notes.txt",
	}

	report := fakeVerifier(newFakeExecutor()).verifyProblem(context.Background(), problem)

	if !hasFinding(report, SeverityError, StageStatic, "notes.txt") {
		t.Fatalf("expected unrelated unknown file finding, got %+v", report.Findings)
	}
	if hasFinding(report, SeverityError, StageStatic, "validator_inspection_summary.txt") {
		t.Fatalf("inspection summary should be ignored, got %+v", report.Findings)
	}
	if hasFinding(report, SeverityError, StageStatic, "testcase_validator_inspection_case.txt") {
		t.Fatalf("inspection testcase should be ignored, got %+v", report.Findings)
	}
}

func TestOutputOnlyIgnoredMaterialsFailStatically(t *testing.T) {
	problem := loader.Problem{
		ProblemType:   "boj",
		ExternalID:    "1",
		Title:         "Fake",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		OutputOnly:    true,
		CorrectCodes: []loader.CodeFile{{
			Filename: "correct_main.py",
			Content:  "correct_main.py",
			Language: contracts.LanguagePython3,
		}},
		IgnoredOutputOnlyFiles: []loader.IgnoredOutputOnlyFile{
			{Filename: "validator.cpp", Role: "validator"},
			{Filename: "testcase_1.in", Role: "testcase"},
			{Filename: "testcase_1.out", Role: "answer"},
		},
	}

	report := fakeVerifier(newFakeExecutor()).verifyProblem(context.Background(), problem)

	for _, filename := range []string{"validator.cpp", "testcase_1.in", "testcase_1.out"} {
		if !hasFinding(report, SeverityError, StageStatic, filename) {
			t.Fatalf("expected output-only ignored file finding for %s, got %+v", filename, report.Findings)
		}
	}
}

func TestOutputOnlyFullModeRunsCorrectsOnceWithEmptyInput(t *testing.T) {
	fake := newFakeExecutor()
	problem := loader.Problem{
		ProblemType:   "boj",
		ExternalID:    "1",
		Title:         "Fake",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		OutputOnly:    true,
		CorrectCodes: []loader.CodeFile{
			{Filename: "correct_a.py", Content: "correct_a.py", Language: contracts.LanguagePython3},
			{Filename: "correct_b.py", Content: "correct_b.py", Language: contracts.LanguagePython3},
		},
		Checker: &loader.CodeFile{Filename: "checker.cpp", Content: "checker.cpp", Language: contracts.LanguageCpp23},
	}

	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	if report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = true, findings = %+v", report.Findings)
	}
	if report.SampledCasesCount != 1 {
		t.Fatalf("SampledCasesCount = %d, want 1", report.SampledCasesCount)
	}
	want := []string{
		"run correct_a.py input=",
		"checker input= participant=correct_a.py jury=correct_a.py",
		"run correct_b.py input=",
		"checker input= participant=correct_b.py jury=correct_a.py",
	}
	if !reflect.DeepEqual(fake.calls, want) {
		t.Fatalf("calls:\n%s\nwant:\n%s", strings.Join(fake.calls, "\n"), strings.Join(want, "\n"))
	}
}

func TestOutputOnlyValidateInputsModeSkipsRuntime(t *testing.T) {
	fake := newFakeExecutor()
	problem := loader.Problem{
		ProblemType:   "boj",
		ExternalID:    "1",
		Title:         "Fake",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		OutputOnly:    true,
		CorrectCodes: []loader.CodeFile{{
			Filename: "correct_main.py",
			Content:  "correct_main.py",
			Language: contracts.LanguagePython3,
		}},
	}

	report := fakeVerifier(fake).verifyProblemWithOptions(context.Background(), problem, VerifyOptions{Mode: VerifyModeValidateInputs})

	if report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = true, findings = %+v", report.Findings)
	}
	if report.SampledCasesCount != 0 {
		t.Fatalf("SampledCasesCount = %d, want 0", report.SampledCasesCount)
	}
	if len(fake.calls) != 0 {
		t.Fatalf("calls:\n%s\nwant none", strings.Join(fake.calls, "\n"))
	}
}

func TestInputPipelineIsSerial(t *testing.T) {
	fake := newFakeExecutor()
	problem := fakeProblem(
		[]string{"correct_a.py", "correct_b.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{
			{Filename: "testcase_1.txt", Content: "1\n"},
			{Filename: "testcase_2.txt", Content: "2\n"},
		},
		true,
	)

	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	if report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = true, findings = %+v", report.Findings)
	}
	want := []string{
		"run validator.cpp input=1",
		"run correct_a.py input=1",
		"checker input=1 participant=correct_a.py jury=correct_a.py",
		"run correct_b.py input=1",
		"checker input=1 participant=correct_b.py jury=correct_a.py",
		"run validator.cpp input=2",
		"run correct_a.py input=2",
		"checker input=2 participant=correct_a.py jury=correct_a.py",
		"run correct_b.py input=2",
		"checker input=2 participant=correct_b.py jury=correct_a.py",
	}
	if !reflect.DeepEqual(fake.calls, want) {
		t.Fatalf("calls:\n%s\nwant:\n%s", strings.Join(fake.calls, "\n"), strings.Join(want, "\n"))
	}
}

func TestValidatorRejectStopsInput(t *testing.T) {
	fake := newFakeExecutor()
	fake.setRunResult("validator.cpp", "bad", nil, executor.ExecutionResult{Success: false, Verdict: contracts.VerdictWrongAnswer, ReturnCode: 1})
	fake.setSuccessfulRunResult("validator.cpp", "good", nil, "")
	problem := fakeProblem(
		[]string{"correct_a.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{
			{Filename: "testcase_bad.txt", Content: "bad\n"},
			{Filename: "testcase_good.txt", Content: "good\n"},
		},
		true,
	)

	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	if !report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = false, want true")
	}
	want := []string{
		"run validator.cpp input=bad",
		"run validator.cpp input=good",
		"run correct_a.py input=good",
		"checker input=good participant=correct_a.py jury=correct_a.py",
	}
	if !reflect.DeepEqual(fake.calls, want) {
		t.Fatalf("calls:\n%s\nwant:\n%s", strings.Join(fake.calls, "\n"), strings.Join(want, "\n"))
	}
}

func TestValidateInputsModeSkipsCorrectAndCheckerAfterValidatorAccepts(t *testing.T) {
	fake := newFakeExecutor()
	problem := fakeProblem(
		[]string{"correct_a.py", "correct_b.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "testcase_1.txt", Content: "1\n"}},
		true,
	)

	report := fakeVerifier(fake).verifyProblemWithOptions(context.Background(), problem, VerifyOptions{Mode: VerifyModeValidateInputs})

	if report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = true, findings = %+v", report.Findings)
	}
	want := []string{
		"run validator.cpp input=1",
	}
	if !reflect.DeepEqual(fake.calls, want) {
		t.Fatalf("calls:\n%s\nwant:\n%s", strings.Join(fake.calls, "\n"), strings.Join(want, "\n"))
	}
}

func TestValidateInputsModeRunsGeneratorsWithoutDiversityGate(t *testing.T) {
	fake := newFakeExecutor()
	fake.setSuccessfulRunResult("generator_a.py", "", []string{"0"}, "7\n")
	fake.setSuccessfulRunResult("generator_a.py", "", []string{"1"}, "7\n")
	problem := fakeProblem(
		[]string{"correct_a.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		nil,
		false,
	)
	problem.Generators = []loader.CodeFile{{Filename: "generator_a.py", Language: contracts.LanguagePython3, Content: "generator_a.py"}}

	report := fakeVerifier(fake).verifyProblemWithOptions(context.Background(), problem, VerifyOptions{Mode: VerifyModeValidateInputs})

	if report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = true, findings = %+v", report.Findings)
	}
	wantPrefix := []string{
		"run generator_a.py input= args=0",
		"run validator.cpp input=7",
		"run generator_a.py input= args=1",
		"run validator.cpp input=7",
	}
	if len(fake.calls) < len(wantPrefix) || !reflect.DeepEqual(fake.calls[:len(wantPrefix)], wantPrefix) {
		t.Fatalf("calls prefix:\n%s\nwant:\n%s", strings.Join(fake.calls[:min(len(fake.calls), len(wantPrefix))], "\n"), strings.Join(wantPrefix, "\n"))
	}
}

func TestValidateInputsModeRunsSinglegenOnce(t *testing.T) {
	fake := newFakeExecutor()
	fake.setSuccessfulRunResult("singlegen_a.py", "", nil, "7\n")
	problem := fakeProblem(
		[]string{"correct_a.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		nil,
		false,
	)
	problem.Singlegens = []loader.CodeFile{{Filename: "singlegen_a.py", Language: contracts.LanguagePython3, Content: "singlegen_a.py"}}

	report := fakeVerifier(fake).verifyProblemWithOptions(context.Background(), problem, VerifyOptions{Mode: VerifyModeValidateInputs})

	if report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = true, findings = %+v", report.Findings)
	}
	want := []string{
		"run singlegen_a.py input=",
		"run validator.cpp input=7",
	}
	if !reflect.DeepEqual(fake.calls, want) {
		t.Fatalf("calls:\n%s\nwant:\n%s", strings.Join(fake.calls, "\n"), strings.Join(want, "\n"))
	}
}

func TestValidateInputsModeSkipsOutputJudgingStaticChecks(t *testing.T) {
	problem := fakeProblem(
		nil,
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "testcase_1.in", Content: "1\n"}},
		false,
	)
	problem.AnswerFiles = []loader.AnswerFile{
		{Filename: "first.out", Content: "1\n", TargetProviderFilename: "testcase_1.in"},
		{Filename: "second.out", Content: "1\n", TargetProviderFilename: "testcase_1.in"},
	}

	report := fakeVerifier(newFakeExecutor()).verifyProblemWithOptions(context.Background(), problem, VerifyOptions{Mode: VerifyModeValidateInputs})

	if report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = true, findings = %+v", report.Findings)
	}
	if len(report.Findings) != 0 {
		t.Fatalf("findings = %+v, want none", report.Findings)
	}
}

func TestPrimaryCorrectFailureStillRunsRemainingCorrects(t *testing.T) {
	fake := newFakeExecutor()
	fake.setRunResult("correct_a.py", "1", nil, executor.ExecutionResult{Success: false, Verdict: contracts.VerdictRuntimeError, ReturnCode: 1})
	problem := fakeProblem(
		[]string{"correct_a.py", "correct_b.py", "correct_c.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "testcase_1.txt", Content: "1\n"}},
		true,
	)

	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	if !report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = false, want true")
	}
	want := []string{
		"run validator.cpp input=1",
		"run correct_a.py input=1",
		"run correct_b.py input=1",
		"run correct_c.py input=1",
	}
	if !reflect.DeepEqual(fake.calls, want) {
		t.Fatalf("calls:\n%s\nwant:\n%s", strings.Join(fake.calls, "\n"), strings.Join(want, "\n"))
	}
	if len(fake.checkerCalls) != 0 {
		t.Fatalf("checker calls:\n%s\nwant none", strings.Join(fake.checkerCalls, "\n"))
	}
}

func TestSingleCorrectStillRunsAndCheckerSmokeRuns(t *testing.T) {
	fake := newFakeExecutor()
	problem := fakeProblem(
		[]string{"correct_only.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "testcase_1.txt", Content: "1\n"}},
		true,
	)

	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	if report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = true, findings = %+v", report.Findings)
	}
	want := []string{
		"run validator.cpp input=1",
		"run correct_only.py input=1",
		"checker input=1 participant=correct_only.py jury=correct_only.py",
	}
	if !reflect.DeepEqual(fake.calls, want) {
		t.Fatalf("calls:\n%s\nwant:\n%s", strings.Join(fake.calls, "\n"), strings.Join(want, "\n"))
	}
}

func TestCorrectConsistencyUsesPrimaryAgainstOthers(t *testing.T) {
	fake := newFakeExecutor()
	problem := fakeProblem(
		[]string{"correct_a.py", "correct_b.py", "correct_c.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "testcase_1.txt", Content: "1\n"}},
		true,
	)

	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	if report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = true, findings = %+v", report.Findings)
	}
	want := []string{
		"checker input=1 participant=correct_a.py jury=correct_a.py",
		"checker input=1 participant=correct_b.py jury=correct_a.py",
		"checker input=1 participant=correct_c.py jury=correct_a.py",
	}
	if !reflect.DeepEqual(fake.checkerCalls, want) {
		t.Fatalf("checker calls:\n%s\nwant:\n%s", strings.Join(fake.checkerCalls, "\n"), strings.Join(want, "\n"))
	}
}

func TestCorrectFailureReportsFixedTestcaseProvider(t *testing.T) {
	// Given: a fixed testcase that makes the primary correct solution fail.
	fake := newFakeExecutor()
	fake.setRunResult("correct_a.py", "1", nil, executor.ExecutionResult{
		Success:    false,
		Verdict:    contracts.VerdictRuntimeError,
		ReturnCode: 1,
	})
	problem := fakeProblem(
		[]string{"correct_a.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "case_1.in", Content: "1\n"}},
		false,
	)

	// When: verification runs correct-consistency checks.
	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	// Then: the finding keeps the failing correct file and the input provider.
	finding, ok := findFinding(report, SeverityError, StageCorrectConsistency, "correct_a.py")
	if !ok {
		t.Fatalf("expected correct failure finding, got %+v", report.Findings)
	}
	if finding.InputFilename != "case_1.in" {
		t.Fatalf("InputFilename = %q, want %q", finding.InputFilename, "case_1.in")
	}
}

func TestCorrectFailureReportsGeneratorProviderAndSeed(t *testing.T) {
	// Given: one generated input makes the primary correct solution fail.
	fake := newFakeExecutor()
	fake.setSuccessfulRunResult("generator_a.py", "", []string{"7"}, "bad\n")
	fake.setRunResult("correct_a.py", "bad", nil, executor.ExecutionResult{
		Success:    false,
		Verdict:    contracts.VerdictRuntimeError,
		ReturnCode: 1,
	})
	problem := fakeProblem(
		[]string{"correct_a.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		nil,
		false,
	)
	problem.Generators = []loader.CodeFile{{Filename: "generator_a.py", Language: contracts.LanguagePython3, Content: "generator_a.py"}}

	// When: verification runs generator-backed correct-consistency checks.
	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	// Then: the finding keeps the failing correct file, generator provider, and seed.
	finding, ok := findFindingWithInput(report, SeverityError, StageCorrectConsistency, "correct_a.py", "generator_a.py")
	if !ok {
		t.Fatalf("expected generator-backed correct failure finding, got %+v", report.Findings)
	}
	if finding.Seed == nil || *finding.Seed != 7 {
		t.Fatalf("Seed = %v, want 7", finding.Seed)
	}
}

func TestAnswerFileMismatchFailsWithoutChecker(t *testing.T) {
	// Given: a testcase answer file whose expected text differs from the correct output.
	fake := newFakeExecutor()
	fake.setSuccessfulRunResult("correct_a.py", "1", nil, "actual\n")
	problem := fakeProblem(
		[]string{"correct_a.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{
			Filename: "testcase_1.in.txt",
			Content:  "1\n",
		}},
		false,
	)
	problem.AnswerFiles = []loader.AnswerFile{{Filename: "testcase_1.out.txt", Content: "expected\n", TargetProviderFilename: "testcase_1.in.txt"}}

	// When: verification runs without a checker.
	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	// Then: the answer mismatch is reported as a correct-consistency error.
	if !report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = false, want true")
	}
	if !hasFinding(report, SeverityError, StageCorrectConsistency, "correct_a.py") {
		t.Fatalf("expected answer mismatch finding, got %+v", report.Findings)
	}
}

func TestAnswerFileMismatchThroughCheckerFails(t *testing.T) {
	// Given: a checker-backed testcase answer file that rejects the correct output.
	fake := newFakeExecutor()
	fake.setSuccessfulRunResult("correct_a.py", "1", nil, "actual\n")
	fake.setCheckerResult("1", "actual", "expected", executor.ExecutionResult{
		Success:    true,
		Verdict:    contracts.VerdictWrongAnswer,
		ReturnCode: 0,
		Stdout:     "answer mismatch\n",
	})
	problem := fakeProblem(
		[]string{"correct_a.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{
			Filename: "testcase_1.in.txt",
			Content:  "1\n",
		}},
		true,
	)
	problem.AnswerFiles = []loader.AnswerFile{{Filename: "testcase_1.out.txt", Content: "expected\n", TargetProviderFilename: "testcase_1.in.txt"}}

	// When: verification runs with the checker.
	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	// Then: the verifier checks against the answer text and reports the checker rejection.
	if !report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = false, want true")
	}
	if !hasFinding(report, SeverityError, StageCorrectConsistency, "correct_a.py") {
		t.Fatalf("expected checker mismatch finding, got %+v", report.Findings)
	}
	want := []string{
		"checker input=1 participant=expected jury=expected",
		"checker input=1 participant=actual jury=expected",
	}
	if !reflect.DeepEqual(fake.checkerCalls, want) {
		t.Fatalf("checker calls:\n%s\nwant:\n%s", strings.Join(fake.checkerCalls, "\n"), strings.Join(want, "\n"))
	}
}

func TestSinglegenAnswerFileMismatchFails(t *testing.T) {
	// Given: a singlegen answer file whose expected text differs from the correct output.
	fake := newFakeExecutor()
	fake.setSuccessfulRunResult("singlegen_1.py", "", nil, "1\n")
	fake.setSuccessfulRunResult("correct_a.py", "1", nil, "actual\n")
	problem := fakeProblem(
		[]string{"correct_a.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		nil,
		false,
	)
	problem.Singlegens = []loader.CodeFile{{Filename: "singlegen_1.py", Language: contracts.LanguagePython3, Content: "singlegen_1.py"}}
	problem.AnswerFiles = []loader.AnswerFile{{Filename: "singlegen_1.py.out", Content: "expected\n", TargetProviderFilename: "singlegen_1.py"}}

	// When: verification runs the singlegen input.
	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	// Then: the singlegen answer mismatch is reported as a correct-consistency error.
	if !report.HasErrorFinding {
		t.Fatalf("HasErrorFinding = false, want true")
	}
	if !hasFinding(report, SeverityError, StageCorrectConsistency, "correct_a.py") {
		t.Fatalf("expected singlegen answer mismatch finding, got %+v", report.Findings)
	}
}

func TestDuplicateAnswerFilesForProviderFailsStatically(t *testing.T) {
	// Given: two answer files mapped to the same testcase provider.
	problem := fakeProblem(
		[]string{"correct_a.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "testcase_1.in.txt", Content: "1\n"}},
		false,
	)
	problem.AnswerFiles = []loader.AnswerFile{
		{Filename: "first.out.txt", Content: "1\n", TargetProviderFilename: "testcase_1.in.txt"},
		{Filename: "second.out.txt", Content: "1\n", TargetProviderFilename: "testcase_1.in.txt"},
	}

	// When: verification performs static checks.
	report := fakeVerifier(newFakeExecutor()).verifyProblem(context.Background(), problem)

	// Then: the duplicate provider mapping is reported before runtime judging matters.
	if !hasFinding(report, SeverityError, StageStatic, "second.out.txt") {
		t.Fatalf("expected duplicate answer static finding, got %+v", report.Findings)
	}
}

func TestLargeFixedTestcaseFileFailsStatically(t *testing.T) {
	// Given: a committed fixed testcase file larger than 8 KiB.
	problem := fakeProblem(
		[]string{"correct_a.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "testcase_large.txt", Content: strings.Repeat("1", 8*1024+1)}},
		false,
	)

	// When: verification performs static checks.
	report := fakeVerifier(newFakeExecutor()).verifyProblem(context.Background(), problem)

	// Then: the contributor sees the fixed-file limit and generator/singlegen guidance.
	finding, ok := findFinding(report, SeverityError, StageStatic, "testcase_large.txt")
	if !ok {
		t.Fatalf("expected fixed testcase size finding, got %+v", report.Findings)
	}
	for _, want := range []string{"8192 bytes", "generator_*", "singlegen_*"} {
		if !strings.Contains(finding.Message, want) {
			t.Fatalf("finding message = %q, want to contain %q", finding.Message, want)
		}
	}
}

func fakeProblem(corrects []string, validator *loader.CodeFile, testcases []loader.TestcaseFile, withChecker bool) loader.Problem {
	problem := loader.Problem{
		ProblemType:   "boj",
		ExternalID:    "1",
		Title:         "Fake",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		Testcases:     testcases,
	}
	if validator != nil {
		validatorCopy := *validator
		if validatorCopy.Content == "" {
			validatorCopy.Content = validatorCopy.Filename
		}
		problem.Validator = &validatorCopy
	}
	for _, filename := range corrects {
		problem.CorrectCodes = append(problem.CorrectCodes, loader.CodeFile{
			Filename: filename,
			Content:  filename,
			Language: contracts.LanguagePython3,
		})
	}
	if withChecker {
		problem.Checker = &loader.CodeFile{Filename: "checker.cpp", Content: "checker.cpp", Language: contracts.LanguageCpp23}
	}
	return problem
}

func fakeVerifier(fake *fakeExecutor) verifier {
	return verifier{
		compile:    fake.Compile,
		run:        fake.Run,
		runChecker: fake.RunChecker,
		sleep:      func(time.Duration) {},
	}
}

type fakeExecutor struct {
	runResultsByInput     map[runCall]executor.ExecutionResult
	checkerResultsByInput map[checkerCall]executor.ExecutionResult
	calls                 []string
	checkerCalls          []string
}

func newFakeExecutor() *fakeExecutor {
	return &fakeExecutor{
		runResultsByInput:     map[runCall]executor.ExecutionResult{},
		checkerResultsByInput: map[checkerCall]executor.ExecutionResult{},
	}
}

func (f *fakeExecutor) Compile(_ context.Context, source executor.Source) executor.CompileResult {
	program := &executor.CompiledProgram{
		Dir:      source.Code,
		Language: source.Language,
	}
	return executor.CompileResult{Success: true, Program: program}
}

func (f *fakeExecutor) Run(_ context.Context, program executor.CompiledProgram, input string, args []string, _ executor.Limits) executor.ExecutionResult {
	key := newRunCall(program.Dir, input, args)
	call := fmt.Sprintf("run %s input=%s", key.program, key.input)
	if len(args) > 0 {
		call += " args=" + strings.Join(args, ",")
	}
	f.calls = append(f.calls, call)

	if result, ok := f.runResultsByInput[key]; ok {
		return result
	}
	return executor.ExecutionResult{
		Success:    true,
		Verdict:    contracts.VerdictAccepted,
		ReturnCode: 0,
		Stdout:     program.Dir + "\n",
	}
}

type runCall struct {
	program string
	input   string
	argsKey string
}

func (f *fakeExecutor) setRunResult(program, input string, args []string, result executor.ExecutionResult) {
	f.runResultsByInput[newRunCall(program, input, args)] = result
}

func (f *fakeExecutor) setSuccessfulRunResult(program, input string, args []string, stdout string) {
	f.setRunResult(program, input, args, executor.ExecutionResult{
		Success:    true,
		Verdict:    contracts.VerdictAccepted,
		ReturnCode: 0,
		Stdout:     stdout,
	})
}

func newRunCall(program, input string, args []string) runCall {
	return runCall{
		program: program,
		input:   cleanCallInput(input),
		argsKey: strings.Join(args, "\x00"),
	}
}

type checkerCall struct {
	input       string
	participant string
	jury        string
}

func (f *fakeExecutor) setCheckerResult(input, participant, jury string, result executor.ExecutionResult) {
	f.checkerResultsByInput[checkerCall{
		input:       cleanCallInput(input),
		participant: cleanCallInput(participant),
		jury:        cleanCallInput(jury),
	}] = result
}

func (f *fakeExecutor) RunChecker(_ context.Context, _ executor.CompiledProgram, input, participant, jury string, _ executor.Limits) executor.ExecutionResult {
	key := checkerCall{
		input:       cleanCallInput(input),
		participant: cleanCallInput(participant),
		jury:        cleanCallInput(jury),
	}
	call := fmt.Sprintf(
		"checker input=%s participant=%s jury=%s",
		key.input,
		key.participant,
		key.jury,
	)
	f.calls = append(f.calls, call)
	f.checkerCalls = append(f.checkerCalls, call)

	if result, ok := f.checkerResultsByInput[key]; ok {
		return result
	}
	return executor.ExecutionResult{Success: true, Verdict: contracts.VerdictAccepted, ReturnCode: 0}
}

func cleanCallInput(value string) string {
	return strings.TrimSpace(value)
}

func hasFinding(report VerifyReport, severity Severity, stage Stage, filename string) bool {
	_, ok := findFinding(report, severity, stage, filename)
	return ok
}

func findFinding(report VerifyReport, severity Severity, stage Stage, filename string) (Finding, bool) {
	for _, finding := range report.Findings {
		if finding.Severity == severity && finding.Stage == stage && finding.Filename == filename {
			return finding, true
		}
	}
	return Finding{}, false
}

func findFindingWithInput(report VerifyReport, severity Severity, stage Stage, filename, inputFilename string) (Finding, bool) {
	for _, finding := range report.Findings {
		if finding.Severity == severity && finding.Stage == stage && finding.Filename == filename && finding.InputFilename == inputFilename {
			return finding, true
		}
	}
	return Finding{}, false
}
