package verify

import (
	"context"
	"fmt"
	"slices"
	"strings"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
)

const (
	GeneratorRuns              = 100
	MinimumDistinctGeneratorIO = 3
	bytesPerMiB                = 1024 * 1024
	MaxGeneratedTestcaseBytes  = 16 * bytesPerMiB
	generatorTimeoutSeconds    = 2
	helperTimeoutSeconds       = 2
	helperMemoryMB             = 1024
)

type Severity string

const (
	SeverityError   Severity = "error"
	SeverityWarning Severity = "warning"
)

type Stage string

const (
	StageStatic             Stage = "static"
	StageCompile            Stage = "compile"
	StageGenerator          Stage = "generator"
	StageSinglegen          Stage = "singlegen"
	StageValidator          Stage = "validator"
	StageChecker            Stage = "checker"
	StageCorrectConsistency Stage = "correct-consistency"
)

type Finding struct {
	Severity Severity `json:"severity"`
	Stage    Stage    `json:"stage"`
	Filename string   `json:"filename,omitempty"`
	Seed     *int     `json:"seed,omitempty"`
	Message  string   `json:"message"`
	Stdout   string   `json:"stdout,omitempty"`
	Stderr   string   `json:"stderr,omitempty"`
}

type Status string

const (
	StatusOK     Status = "ok"
	StatusFailed Status = "failed"
)

type VerifyReport struct {
	ProblemPath       string    `json:"problemPath,omitempty"`
	ProblemType       string    `json:"problemType,omitempty"`
	ExternalID        string    `json:"externalId,omitempty"`
	Status            Status    `json:"status"`
	Findings          []Finding `json:"findings"`
	SampledCasesCount int       `json:"sampledCasesCount"`
	RuntimeSeconds    float64   `json:"runtimeSeconds"`
}

type sample struct {
	Content  string
	Filename string
	Seed     *int
}

type compiledFiles map[string]*executor.CompiledProgram

type verifier struct {
	compile    func(context.Context, executor.Source) executor.CompileResult
	run        func(context.Context, executor.CompiledProgram, string, []string, executor.Limits) executor.ExecutionResult
	runChecker func(context.Context, executor.CompiledProgram, string, string, string, executor.Limits) executor.ExecutionResult
	sleep      func(time.Duration)
}

func VerifyProblem(ctx context.Context, problem loader.Problem) VerifyReport {
	return newVerifier().verifyProblem(ctx, problem)
}

func newVerifier() verifier {
	return verifier{
		compile:    executor.Compile,
		run:        executor.Run,
		runChecker: executor.RunChecker,
		sleep:      time.Sleep,
	}
}

func (v verifier) verifyProblem(ctx context.Context, problem loader.Problem) VerifyReport {
	start := time.Now()
	report := VerifyReport{ProblemType: problem.ProblemType, ExternalID: problem.ExternalID, Status: StatusOK}
	addStaticFindings(&report, problem)

	compiled := v.compileAll(ctx, &report, problem)
	v.verifySamples(ctx, &report, problem, compiled)

	if hasErrors(report.Findings) {
		report.Status = StatusFailed
	}
	report.RuntimeSeconds = executor.RoundSeconds(time.Since(start))
	return report
}

func addStaticFindings(report *VerifyReport, problem loader.Problem) {
	if len(problem.CorrectCodes) == 0 {
		add(report, SeverityWarning, StageStatic, "", nil, "problem has no correct solution; skipping correct-solution checks", "", "")
	}
	if len(problem.Generators)+len(problem.Singlegens)+len(problem.Testcases) == 0 {
		add(report, SeverityError, StageStatic, "", nil, "problem has no testcase provider", "", "")
	}
	if problem.Validator == nil {
		add(report, SeverityError, StageStatic, "validator.cpp", nil, "problem has no validator", "", "")
	}
	for _, testcase := range problem.Testcases {
		verifyTestcaseText(report, testcase.Filename, testcase.Content)
	}
	for _, name := range problem.UnknownFiles {
		add(report, SeverityError, StageStatic, name, nil, "unrecognized problem file", "", "")
	}
}

func verifyTestcaseText(report *VerifyReport, filename, content string) {
	if len(content) > MaxGeneratedTestcaseBytes {
		add(report, SeverityError, StageStatic, filename, nil, fmt.Sprintf("testcase exceeds %d bytes", MaxGeneratedTestcaseBytes), "", "")
	}
}

func (v verifier) compileAll(ctx context.Context, report *VerifyReport, problem loader.Problem) compiledFiles {
	out := compiledFiles{}
	for _, file := range allSourceFiles(problem) {
		limits := limitsFor(problem, file.Language)
		if loader.IsRoleFile(file.Filename, "generator") || loader.IsRoleFile(file.Filename, "singlegen") {
			limits = generatorLimits()
		}
		if file.Filename == "validator.cpp" || file.Filename == "checker.cpp" {
			limits = helperLimits()
		}
		result := v.compile(ctx, executor.Source{Label: file.Filename, Code: file.Content, Language: file.Language, Limits: limits})
		if !result.Success {
			add(report, SeverityError, StageCompile, file.Filename, nil, "compilation failed", result.Stdout, result.Stderr)
			continue
		}
		out[file.Filename] = result.Program
	}
	return out
}

func allSourceFiles(problem loader.Problem) []loader.CodeFile {
	out := []loader.CodeFile{}
	out = append(out, problem.CorrectCodes...)
	out = append(out, problem.Generators...)
	out = append(out, problem.Singlegens...)
	if problem.Validator != nil {
		out = append(out, *problem.Validator)
	}
	if problem.Checker != nil {
		out = append(out, *problem.Checker)
	}
	return out
}

func (v verifier) verifySamples(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles) {
	if problem.Validator == nil {
		return
	}
	validator := compiled[problem.Validator.Filename]
	if validator == nil {
		return
	}
	var checker *executor.CompiledProgram
	if problem.Checker != nil {
		checker = compiled[problem.Checker.Filename]
	}

	for _, testcase := range problem.Testcases {
		content := executor.CleanStdout(testcase.Content, "always")
		if validGeneratedSize(report, StageStatic, testcase.Filename, nil, content) {
			report.SampledCasesCount++
			v.verifySample(ctx, report, problem, compiled, *validator, checker, sample{Content: content, Filename: testcase.Filename})
		}
	}
	for _, singlegen := range problem.Singlegens {
		program := compiled[singlegen.Filename]
		if program == nil {
			continue
		}
		first := v.run(ctx, *program, "", nil, generatorLimits())
		if !first.Success {
			addExecution(report, StageSinglegen, singlegen.Filename, nil, "singlegen execution failed", first)
			continue
		}
		v.sleep(time.Second)
		second := v.run(ctx, *program, "", nil, generatorLimits())
		if !second.Success {
			addExecution(report, StageSinglegen, singlegen.Filename, nil, "singlegen repeat execution failed", second)
			continue
		}
		firstOut := executor.CleanStdout(first.Stdout, "always")
		secondOut := executor.CleanStdout(second.Stdout, "always")
		if firstOut != secondOut {
			add(report, SeverityError, StageSinglegen, singlegen.Filename, nil, "singlegen output changed between runs", first.Stdout, second.Stdout)
			continue
		}
		if validGeneratedSize(report, StageSinglegen, singlegen.Filename, nil, firstOut) {
			report.SampledCasesCount++
			v.verifySample(ctx, report, problem, compiled, *validator, checker, sample{Content: firstOut, Filename: singlegen.Filename})
		}
	}
	for _, generator := range problem.Generators {
		program := compiled[generator.Filename]
		if program == nil {
			continue
		}
		seen := map[string]struct{}{}
		var firstSeedOutput string
		for seed := 0; seed < GeneratorRuns; seed++ {
			output, ok := v.runGenerator(ctx, report, generator.Filename, *program, seed)
			if !ok {
				continue
			}
			if seed == 0 {
				firstSeedOutput = output
				repeat, repeatOK := v.runGenerator(ctx, report, generator.Filename, *program, seed)
				if repeatOK && repeat != firstSeedOutput {
					add(report, SeverityError, StageGenerator, generator.Filename, &seed, "generator output changed for the same seed", firstSeedOutput, repeat)
				}
			}
			seen[output] = struct{}{}
			s := seed
			report.SampledCasesCount++
			v.verifySample(ctx, report, problem, compiled, *validator, checker, sample{Content: output, Filename: generator.Filename, Seed: &s})
		}
		if len(seen) < MinimumDistinctGeneratorIO {
			add(report, SeverityError, StageGenerator, generator.Filename, nil, fmt.Sprintf("generator produced %d distinct outputs across %d seeds; want at least %d", len(seen), GeneratorRuns, MinimumDistinctGeneratorIO), "", "")
		}
	}
}

func (v verifier) runGenerator(ctx context.Context, report *VerifyReport, filename string, program executor.CompiledProgram, seed int) (string, bool) {
	result := v.run(ctx, program, "", []string{fmt.Sprintf("%d", seed)}, generatorLimits())
	if !result.Success {
		addExecution(report, StageGenerator, filename, &seed, "generator execution failed", result)
		return "", false
	}
	output := executor.CleanStdout(result.Stdout, "always")
	if !validGeneratedSize(report, StageGenerator, filename, &seed, output) {
		return "", false
	}
	return output, true
}

func (v verifier) verifySample(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles, validator executor.CompiledProgram, checker *executor.CompiledProgram, s sample) {
	result := v.run(ctx, validator, s.Content, nil, helperLimits())
	if !result.Success || result.ReturnCode != 0 {
		addExecution(report, StageValidator, s.Filename, s.Seed, "validator rejected testcase", result)
		return
	}
	if len(problem.CorrectCodes) == 0 {
		return
	}

	var jury string
	primaryOK := false
	primary := compiled[problem.CorrectCodes[0].Filename]
	if primary != nil {
		primaryRun := v.run(ctx, *primary, s.Content, nil, primary.Limits)
		if !primaryRun.Success {
			addExecution(report, StageCorrectConsistency, problem.CorrectCodes[0].Filename, s.Seed, "correct solution failed on sampled testcase", primaryRun)
		} else {
			jury = executor.CleanStdout(primaryRun.Stdout, "no")
			primaryOK = true
		}
	}

	if primaryOK && checker != nil {
		result := v.runChecker(ctx, *checker, s.Content, jury, jury, helperLimits())
		if !result.Success || result.Verdict != contracts.VerdictAccepted {
			addExecution(report, StageChecker, problem.Checker.Filename, s.Seed, "checker rejected identical participant and jury output", result)
		}
	}

	for i := 1; i < len(problem.CorrectCodes); i++ {
		correct := problem.CorrectCodes[i]
		program := compiled[correct.Filename]
		if program == nil {
			continue
		}
		result := v.run(ctx, *program, s.Content, nil, program.Limits)
		if !result.Success {
			addExecution(report, StageCorrectConsistency, correct.Filename, s.Seed, "correct solution failed on sampled testcase", result)
			continue
		}
		if !primaryOK {
			continue
		}
		output := executor.CleanStdout(result.Stdout, "no")
		if checker != nil {
			result := v.runChecker(ctx, *checker, s.Content, output, jury, helperLimits())
			if !result.Success || result.Verdict != contracts.VerdictAccepted {
				addExecution(report, StageCorrectConsistency, correct.Filename, s.Seed, "correct solution output was rejected by checker", result)
			}
		} else if !executor.CompareOutput(output, jury) {
			add(report, SeverityError, StageCorrectConsistency, correct.Filename, s.Seed, "correct solution output differs from primary correct solution", output, jury)
		}
	}
}

func limitsFor(problem loader.Problem, language contracts.Language) executor.Limits {
	timeSeconds := float64(problem.TimeLimitMS) / 1000.0
	if timeSeconds <= 0 {
		timeSeconds = 2
	}
	memoryMB := problem.MemoryLimitMB
	if memoryMB <= 0 {
		memoryMB = 256
	}
	return executor.Limits{TimeSeconds: timeSeconds, MemoryMB: memoryMB}
}

func generatorLimits() executor.Limits {
	return executor.Limits{TimeSeconds: generatorTimeoutSeconds, MemoryMB: helperMemoryMB, StdoutBytes: MaxGeneratedTestcaseBytes, StderrBytes: executor.MaxRunStderrBytes}
}

func helperLimits() executor.Limits {
	return executor.Limits{TimeSeconds: helperTimeoutSeconds, MemoryMB: helperMemoryMB}
}

func validGeneratedSize(report *VerifyReport, stage Stage, filename string, seed *int, output string) bool {
	if len(output) > MaxGeneratedTestcaseBytes {
		add(report, SeverityError, stage, filename, seed, fmt.Sprintf("generated testcase exceeds %d bytes", MaxGeneratedTestcaseBytes), "", "")
		return false
	}
	return true
}

func addExecution(report *VerifyReport, stage Stage, filename string, seed *int, message string, result executor.ExecutionResult) {
	add(report, SeverityError, stage, filename, seed, fmt.Sprintf("%s: %s", message, result.Verdict), result.Stdout, result.Stderr)
}

func add(report *VerifyReport, severity Severity, stage Stage, filename string, seed *int, message, stdout, stderr string) {
	report.Findings = append(report.Findings, Finding{
		Severity: severity,
		Stage:    stage,
		Filename: filename,
		Seed:     cloneInt(seed),
		Message:  message,
		Stdout:   excerpt(stdout),
		Stderr:   excerpt(stderr),
	})
}

func cloneInt(value *int) *int {
	if value == nil {
		return nil
	}
	out := *value
	return &out
}

func excerpt(value string) string {
	value = strings.TrimSpace(value)
	if len(value) <= 2000 {
		return value
	}
	return value[:2000] + "...(truncated)"
}

func hasErrors(findings []Finding) bool {
	return slices.ContainsFunc(findings, func(f Finding) bool {
		return f.Severity == SeverityError
	})
}
