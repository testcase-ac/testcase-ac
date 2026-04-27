package verify

import (
	"context"
	"fmt"
	"slices"
	"strings"
	"time"
	"unicode/utf8"

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

func VerifyProblem(ctx context.Context, problem loader.Problem) VerifyReport {
	start := time.Now()
	report := VerifyReport{ProblemType: problem.ProblemType, ExternalID: problem.ExternalID, Status: StatusOK}
	addStaticFindings(&report, problem)

	compiled := compileAll(ctx, &report, problem)
	samples := buildSamples(ctx, &report, problem, compiled)
	report.SampledCasesCount = len(samples)

	runProblemValidators(ctx, &report, problem, compiled, samples)
	runCheckerSmoke(ctx, &report, problem, compiled, samples)
	runCorrectConsistency(ctx, &report, problem, compiled, samples)

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
	for _, testcase := range problem.Testcases {
		verifyTestcaseText(report, testcase.Filename, testcase.Content)
	}
	for _, name := range problem.UnknownFiles {
		add(report, SeverityError, StageStatic, name, nil, "unrecognized problem file", "", "")
	}
}

func verifyTestcaseText(report *VerifyReport, filename, content string) {
	if !utf8.ValidString(content) {
		add(report, SeverityError, StageStatic, filename, nil, "testcase is not valid UTF-8", "", "")
	}
	if len(content) > MaxGeneratedTestcaseBytes {
		add(report, SeverityError, StageStatic, filename, nil, fmt.Sprintf("testcase exceeds %d bytes", MaxGeneratedTestcaseBytes), "", "")
	}
}

func compileAll(ctx context.Context, report *VerifyReport, problem loader.Problem) compiledFiles {
	out := compiledFiles{}
	for _, file := range allSourceFiles(problem) {
		limits := limitsFor(problem, file.Language)
		if loader.IsRoleFile(file.Filename, "generator") || loader.IsRoleFile(file.Filename, "singlegen") {
			limits = generatorLimits()
		}
		if file.Filename == "validator.cpp" || file.Filename == "checker.cpp" {
			limits = helperLimits()
		}
		result := executor.Compile(ctx, executor.Source{Label: file.Filename, Code: file.Content, Language: file.Language, Limits: limits})
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

func buildSamples(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles) []sample {
	samples := make([]sample, 0, len(problem.Testcases)+len(problem.Singlegens)+len(problem.Generators)*GeneratorRuns)
	for _, testcase := range problem.Testcases {
		content := executor.CleanStdout(testcase.Content, "always")
		if validGeneratedSize(report, StageStatic, testcase.Filename, nil, content) {
			samples = append(samples, sample{Content: content, Filename: testcase.Filename})
		}
	}
	for _, singlegen := range problem.Singlegens {
		program := compiled[singlegen.Filename]
		if program == nil {
			continue
		}
		first := executor.Run(ctx, *program, "", nil, generatorLimits())
		if !first.Success {
			addExecution(report, StageSinglegen, singlegen.Filename, nil, "singlegen execution failed", first)
			continue
		}
		time.Sleep(time.Second)
		second := executor.Run(ctx, *program, "", nil, generatorLimits())
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
			samples = append(samples, sample{Content: firstOut, Filename: singlegen.Filename})
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
			output, ok := runGenerator(ctx, report, generator.Filename, *program, seed)
			if !ok {
				continue
			}
			if seed == 0 {
				firstSeedOutput = output
				repeat, repeatOK := runGenerator(ctx, report, generator.Filename, *program, seed)
				if repeatOK && repeat != firstSeedOutput {
					add(report, SeverityError, StageGenerator, generator.Filename, &seed, "generator output changed for the same seed", firstSeedOutput, repeat)
				}
			}
			seen[output] = struct{}{}
			s := seed
			samples = append(samples, sample{Content: output, Filename: generator.Filename, Seed: &s})
		}
		if len(seen) < MinimumDistinctGeneratorIO {
			add(report, SeverityError, StageGenerator, generator.Filename, nil, fmt.Sprintf("generator produced %d distinct outputs across %d seeds; want at least %d", len(seen), GeneratorRuns, MinimumDistinctGeneratorIO), "", "")
		}
	}
	return samples
}

func runGenerator(ctx context.Context, report *VerifyReport, filename string, program executor.CompiledProgram, seed int) (string, bool) {
	result := executor.Run(ctx, program, "", []string{fmt.Sprintf("%d", seed)}, generatorLimits())
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

func runProblemValidators(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles, samples []sample) {
	if problem.Validator == nil {
		return
	}
	validator := compiled[problem.Validator.Filename]
	if validator == nil {
		return
	}
	for _, s := range samples {
		result := executor.RunValidator(ctx, *validator, s.Content, helperLimits())
		if !result.Success || result.ReturnCode != 0 {
			addExecution(report, StageValidator, s.Filename, s.Seed, "validator rejected testcase", result)
		}
	}
}

func runCheckerSmoke(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles, samples []sample) {
	if problem.Checker == nil || len(problem.CorrectCodes) == 0 {
		return
	}
	checker := compiled[problem.Checker.Filename]
	primary := compiled[problem.CorrectCodes[0].Filename]
	if checker == nil || primary == nil {
		return
	}
	for _, s := range samples {
		jury := executor.Run(ctx, *primary, s.Content, nil, primary.Limits)
		if !jury.Success {
			addExecution(report, StageChecker, problem.CorrectCodes[0].Filename, s.Seed, "primary correct solution failed while preparing checker smoke output", jury)
			continue
		}
		clean := executor.CleanStdout(jury.Stdout, "no")
		result := executor.RunChecker(ctx, *checker, s.Content, clean, clean, helperLimits())
		if !result.Success || result.Verdict != contracts.VerdictAccepted {
			addExecution(report, StageChecker, problem.Checker.Filename, s.Seed, "checker rejected identical participant and jury output", result)
		}
	}
}

func runCorrectConsistency(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles, samples []sample) {
	if len(problem.CorrectCodes) == 0 {
		return
	}
	checker := (*executor.CompiledProgram)(nil)
	if problem.Checker != nil {
		checker = compiled[problem.Checker.Filename]
	}
	for _, s := range samples {
		outputs := make([]string, len(problem.CorrectCodes))
		allOK := true
		for i, correct := range problem.CorrectCodes {
			program := compiled[correct.Filename]
			if program == nil {
				allOK = false
				continue
			}
			result := executor.Run(ctx, *program, s.Content, nil, program.Limits)
			if !result.Success {
				addExecution(report, StageCorrectConsistency, correct.Filename, s.Seed, "correct solution failed on sampled testcase", result)
				allOK = false
				continue
			}
			outputs[i] = executor.CleanStdout(result.Stdout, "no")
		}
		if !allOK {
			continue
		}
		jury := outputs[0]
		for i := 1; i < len(problem.CorrectCodes); i++ {
			correct := problem.CorrectCodes[i]
			if checker != nil {
				result := executor.RunChecker(ctx, *checker, s.Content, outputs[i], jury, helperLimits())
				if !result.Success || result.Verdict != contracts.VerdictAccepted {
					addExecution(report, StageCorrectConsistency, correct.Filename, s.Seed, "correct solution output was rejected by checker", result)
				}
			} else if !executor.CompareOutput(outputs[i], jury) {
				add(report, SeverityError, StageCorrectConsistency, correct.Filename, s.Seed, "correct solution output differs from primary correct solution", outputs[i], jury)
			}
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
	if !utf8.ValidString(output) {
		add(report, SeverityError, stage, filename, seed, "generated testcase is not valid UTF-8", "", "")
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
