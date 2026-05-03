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

	if report.Status != StatusFailed {
		t.Fatalf("status = %s, want %s", report.Status, StatusFailed)
	}
	if !hasFinding(report, SeverityError, StageStatic, "validator.cpp") {
		t.Fatalf("expected missing validator finding, got %+v", report.Findings)
	}
}

func TestSamplePipelineIsSerial(t *testing.T) {
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

	if report.Status != StatusOK {
		t.Fatalf("status = %s, findings = %+v", report.Status, report.Findings)
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

func TestValidatorRejectStopsSample(t *testing.T) {
	fake := newFakeExecutor()
	fake.runResults["validator.cpp"] = []executor.ExecutionResult{
		{Success: false, Verdict: contracts.VerdictWrongAnswer, ReturnCode: 1},
		{Success: true, Verdict: contracts.VerdictAccepted, ReturnCode: 0},
	}
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

	if report.Status != StatusFailed {
		t.Fatalf("status = %s, want %s", report.Status, StatusFailed)
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
	fake.runResults["correct_a.py"] = []executor.ExecutionResult{
		{Success: false, Verdict: contracts.VerdictRuntimeError, ReturnCode: 1},
	}
	problem := fakeProblem(
		[]string{"correct_a.py", "correct_b.py", "correct_c.py"},
		&loader.CodeFile{Filename: "validator.cpp", Language: contracts.LanguageCpp23},
		[]loader.TestcaseFile{{Filename: "testcase_1.txt", Content: "1\n"}},
		true,
	)

	report := fakeVerifier(fake).verifyProblem(context.Background(), problem)

	if report.Status != StatusFailed {
		t.Fatalf("status = %s, want %s", report.Status, StatusFailed)
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

	if report.Status != StatusOK {
		t.Fatalf("status = %s, findings = %+v", report.Status, report.Findings)
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

	if report.Status != StatusOK {
		t.Fatalf("status = %s, findings = %+v", report.Status, report.Findings)
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

func fakeProblem(corrects []string, validator *loader.CodeFile, testcases []loader.TestcaseFile, withChecker bool) loader.Problem {
	problem := loader.Problem{
		ProblemType:   "boj",
		ExternalID:    "1",
		Title:         "Fake",
		TimeLimitMS:   2000,
		MemoryLimitMB: 256,
		Validator:     validator,
		Testcases:     testcases,
	}
	for _, filename := range corrects {
		problem.CorrectCodes = append(problem.CorrectCodes, loader.CodeFile{
			Filename: filename,
			Language: contracts.LanguagePython3,
		})
	}
	if withChecker {
		problem.Checker = &loader.CodeFile{Filename: "checker.cpp", Language: contracts.LanguageCpp23}
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
	runResults     map[string][]executor.ExecutionResult
	checkerResults []executor.ExecutionResult
	calls          []string
	checkerCalls   []string
}

func newFakeExecutor() *fakeExecutor {
	return &fakeExecutor{runResults: map[string][]executor.ExecutionResult{}}
}

func (f *fakeExecutor) Compile(_ context.Context, source executor.Source) executor.CompileResult {
	program := &executor.CompiledProgram{
		Dir:      source.Label,
		Label:    source.Label,
		Language: source.Language,
		Limits:   source.Limits,
	}
	return executor.CompileResult{Success: true, Program: program}
}

func (f *fakeExecutor) Run(_ context.Context, program executor.CompiledProgram, input string, args []string, _ executor.Limits) executor.ExecutionResult {
	call := fmt.Sprintf("run %s input=%s", program.Label, cleanCallInput(input))
	if len(args) > 0 {
		call += " args=" + strings.Join(args, ",")
	}
	f.calls = append(f.calls, call)

	if queued := f.runResults[program.Label]; len(queued) > 0 {
		result := queued[0]
		f.runResults[program.Label] = queued[1:]
		return result
	}
	return executor.ExecutionResult{
		Success:    true,
		Verdict:    contracts.VerdictAccepted,
		ReturnCode: 0,
		Stdout:     program.Label + "\n",
	}
}

func (f *fakeExecutor) RunChecker(_ context.Context, _ executor.CompiledProgram, input, participant, jury string, _ executor.Limits) executor.ExecutionResult {
	call := fmt.Sprintf(
		"checker input=%s participant=%s jury=%s",
		cleanCallInput(input),
		cleanCallInput(participant),
		cleanCallInput(jury),
	)
	f.calls = append(f.calls, call)
	f.checkerCalls = append(f.checkerCalls, call)

	if len(f.checkerResults) > 0 {
		result := f.checkerResults[0]
		f.checkerResults = f.checkerResults[1:]
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
