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
	for _, finding := range report.Findings {
		if finding.Severity == severity && finding.Stage == stage && finding.Filename == filename {
			return true
		}
	}
	return false
}
