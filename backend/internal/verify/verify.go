package verify

import (
	"context"
	"fmt"
	"strings"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
	"github.com/testcase-ac/testcase-ac/backend/internal/util"
)

const (
	GeneratorRuns              = 100
	MinimumDistinctGeneratorIO = 3
	bytesPerMiB                = 1024 * 1024
	MaxFixedTestcaseBytes      = 8 * 1024
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

type VerifyReport struct {
	ProblemPath       string    `json:"problemPath,omitempty"`
	ProblemType       string    `json:"problemType,omitempty"`
	ExternalID        string    `json:"externalId,omitempty"`
	HasErrorFinding   bool      `json:"hasErrorFinding"`
	Findings          []Finding `json:"findings"`
	SampledCasesCount int       `json:"sampledCasesCount"`
	RuntimeSeconds    float64   `json:"runtimeSeconds"`
}

type VerifyMode string

const (
	VerifyModeFull           VerifyMode = "full"
	VerifyModeValidateInputs VerifyMode = "validate-inputs"
)

type VerifyOptions struct {
	Mode VerifyMode
}

type testInput struct {
	Content  string
	Filename string
	Seed     *int
	Answer   *loader.AnswerFile
}

type compiledFiles map[string]*executor.CompiledProgram

type verifier struct {
	compile    func(context.Context, executor.Source) executor.CompileResult
	run        func(context.Context, executor.CompiledProgram, string, []string, executor.Limits) executor.ExecutionResult
	runChecker func(context.Context, executor.CompiledProgram, string, string, string, executor.Limits) executor.ExecutionResult
	sleep      func(time.Duration)
}

func VerifyProblem(ctx context.Context, problem loader.Problem) VerifyReport {
	return VerifyProblemWithOptions(ctx, problem, VerifyOptions{})
}

func VerifyProblemWithOptions(ctx context.Context, problem loader.Problem, options VerifyOptions) VerifyReport {
	return newVerifier().verifyProblemWithOptions(ctx, problem, options.normalized())
}

func newVerifier() verifier {
	return verifier{
		compile:    executor.Compile,
		run:        executor.Run,
		runChecker: executor.RunChecker,
		sleep:      time.Sleep,
	}
}

func (options VerifyOptions) normalized() VerifyOptions {
	if options.Mode == "" {
		options.Mode = VerifyModeFull
	}
	return options
}

func (v verifier) verifyProblem(ctx context.Context, problem loader.Problem) VerifyReport {
	return v.verifyProblemWithOptions(ctx, problem, VerifyOptions{Mode: VerifyModeFull})
}

func (v verifier) verifyProblemWithOptions(ctx context.Context, problem loader.Problem, options VerifyOptions) VerifyReport {
	options = options.normalized()
	start := time.Now()
	report := VerifyReport{ProblemType: problem.ProblemType, ExternalID: problem.ExternalID}
	addStaticFindings(&report, problem, options)

	compiled := v.compileAll(ctx, &report, problem, options)
	v.verifyInputs(ctx, &report, problem, compiled, options)

	report.RuntimeSeconds = util.RoundSeconds(time.Since(start))
	return report
}

func addStaticFindings(report *VerifyReport, problem loader.Problem, options VerifyOptions) {
	if options.Mode != VerifyModeValidateInputs && len(problem.CorrectCodes) == 0 {
		report.AddFinding(SeverityWarning, StageStatic, "", nil, "problem has no correct solution; skipping correct-solution checks", "", "")
	}
	if len(problem.Generators)+len(problem.Singlegens)+len(problem.Testcases) == 0 {
		report.AddFinding(SeverityError, StageStatic, "", nil, "problem has no case provider", "", "")
	}
	if problem.Validator == nil {
		report.AddFinding(SeverityError, StageStatic, "validator.cpp", nil, "problem has no validator", "", "")
	}
	for _, testcase := range problem.Testcases {
		verifyTestcaseText(report, testcase.Filename, testcase.Content)
	}
	if options.Mode != VerifyModeValidateInputs {
		verifyAnswerFiles(report, problem.AnswerFiles)
	}
	for _, name := range problem.UnknownFiles {
		if isLocalValidatorInspectionArtifact(name) {
			continue
		}
		report.AddFinding(SeverityError, StageStatic, name, nil, "unrecognized problem file", "", "")
	}
}

func isLocalValidatorInspectionArtifact(name string) bool {
	return name == "validator_inspection_summary.txt" ||
		strings.HasPrefix(name, "testcase_validator_inspection_")
}

func verifyTestcaseText(report *VerifyReport, filename, content string) {
	if len(content) > MaxFixedTestcaseBytes {
		report.AddFinding(SeverityError, StageStatic, filename, nil, fmt.Sprintf("fixed testcase file exceeds %d bytes; use generator_* or singlegen_* for large testcases", MaxFixedTestcaseBytes), "", "")
	}
}

func verifyAnswerFiles(report *VerifyReport, answerFiles []loader.AnswerFile) {
	seenProviders := map[string]string{}
	for _, answer := range answerFiles {
		if len(answer.Content) > MaxGeneratedTestcaseBytes {
			report.AddFinding(SeverityError, StageStatic, answer.Filename, nil, fmt.Sprintf("answer file exceeds %d bytes", MaxGeneratedTestcaseBytes), "", "")
		}
		if previous, ok := seenProviders[answer.TargetProviderFilename]; ok {
			report.AddFinding(SeverityError, StageStatic, answer.Filename, nil, fmt.Sprintf("answer file duplicates provider %s already covered by %s", answer.TargetProviderFilename, previous), "", "")
			continue
		}
		seenProviders[answer.TargetProviderFilename] = answer.Filename
	}
}

func (v verifier) compileAll(ctx context.Context, report *VerifyReport, problem loader.Problem, options VerifyOptions) compiledFiles {
	out := compiledFiles{}
	for _, file := range sourceFilesForMode(problem, options.Mode) {
		result := v.compile(ctx, executor.Source{Code: file.Content, Language: file.Language})
		if !result.Success {
			report.AddFinding(SeverityError, StageCompile, file.Filename, nil, "compilation failed", result.Stdout, result.Stderr)
			continue
		}
		out[file.Filename] = result.Program
	}
	return out
}

func sourceFilesForMode(problem loader.Problem, mode VerifyMode) []loader.CodeFile {
	out := []loader.CodeFile{}
	if mode != VerifyModeValidateInputs {
		out = append(out, problem.CorrectCodes...)
	}
	out = append(out, problem.Generators...)
	out = append(out, problem.Singlegens...)
	if problem.Validator != nil {
		out = append(out, *problem.Validator)
	}
	if mode != VerifyModeValidateInputs && problem.Checker != nil {
		out = append(out, *problem.Checker)
	}
	return out
}

func (v verifier) verifyInputs(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles, options VerifyOptions) {
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
	answersByProvider := answerFilesByProvider(problem.AnswerFiles)

	for _, testcase := range problem.Testcases {
		content := util.CleanStdout(testcase.Content, "always")
		if validGeneratedSize(report, StageStatic, testcase.Filename, nil, content) {
			report.SampledCasesCount++
			v.verifyInput(ctx, report, problem, compiled, *validator, checker, testInput{Content: content, Filename: testcase.Filename, Answer: answersByProvider[testcase.Filename]}, options)
		}
	}
	for _, singlegen := range problem.Singlegens {
		program := compiled[singlegen.Filename]
		if program == nil {
			continue
		}
		first := v.run(ctx, *program, "", nil, generatorLimits())
		if !first.Success {
			report.addExecution(StageSinglegen, singlegen.Filename, nil, "singlegen execution failed", first)
			continue
		}
		firstOut := util.CleanStdout(first.Stdout, "always")
		if options.Mode != VerifyModeValidateInputs {
			v.sleep(time.Second)
			second := v.run(ctx, *program, "", nil, generatorLimits())
			if !second.Success {
				report.addExecution(StageSinglegen, singlegen.Filename, nil, "singlegen repeat execution failed", second)
				continue
			}
			secondOut := util.CleanStdout(second.Stdout, "always")
			if firstOut != secondOut {
				report.AddFinding(SeverityError, StageSinglegen, singlegen.Filename, nil, "singlegen output changed between runs", first.Stdout, second.Stdout)
				continue
			}
		}
		if validGeneratedSize(report, StageSinglegen, singlegen.Filename, nil, firstOut) {
			report.SampledCasesCount++
			v.verifyInput(ctx, report, problem, compiled, *validator, checker, testInput{Content: firstOut, Filename: singlegen.Filename, Answer: answersByProvider[singlegen.Filename]}, options)
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
			if options.Mode != VerifyModeValidateInputs && seed == 0 {
				firstSeedOutput = output
				repeat, repeatOK := v.runGenerator(ctx, report, generator.Filename, *program, seed)
				if repeatOK && repeat != firstSeedOutput {
					report.AddFinding(SeverityError, StageGenerator, generator.Filename, &seed, "generator output changed for the same seed", firstSeedOutput, repeat)
				}
			}
			seen[output] = struct{}{}
			s := seed
			report.SampledCasesCount++
			v.verifyInput(ctx, report, problem, compiled, *validator, checker, testInput{Content: output, Filename: generator.Filename, Seed: &s}, options)
		}
		if options.Mode != VerifyModeValidateInputs && len(seen) < MinimumDistinctGeneratorIO {
			report.AddFinding(SeverityError, StageGenerator, generator.Filename, nil, fmt.Sprintf("generator produced %d distinct outputs across %d seeds; want at least %d", len(seen), GeneratorRuns, MinimumDistinctGeneratorIO), "", "")
		}
	}
}

func answerFilesByProvider(answerFiles []loader.AnswerFile) map[string]*loader.AnswerFile {
	out := make(map[string]*loader.AnswerFile, len(answerFiles))
	for i := range answerFiles {
		answer := &answerFiles[i]
		out[answer.TargetProviderFilename] = answer
	}
	return out
}

func (v verifier) runGenerator(ctx context.Context, report *VerifyReport, filename string, program executor.CompiledProgram, seed int) (string, bool) {
	result := v.run(ctx, program, "", []string{fmt.Sprintf("%d", seed)}, generatorLimits())
	if !result.Success {
		report.addExecution(StageGenerator, filename, &seed, "generator execution failed", result)
		return "", false
	}
	output := util.CleanStdout(result.Stdout, "always")
	if !validGeneratedSize(report, StageGenerator, filename, &seed, output) {
		return "", false
	}
	return output, true
}

func (v verifier) verifyInput(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles, validator executor.CompiledProgram, checker *executor.CompiledProgram, input testInput, options VerifyOptions) {
	result := v.run(ctx, validator, input.Content, nil, helperLimits())
	if !result.Success || result.ReturnCode != 0 {
		report.addExecution(StageValidator, input.Filename, input.Seed, "validator rejected testcase", result)
		return
	}
	if options.Mode == VerifyModeValidateInputs {
		return
	}
	if len(problem.CorrectCodes) == 0 {
		return
	}
	if input.Answer != nil {
		v.verifyInputAgainstAnswerFile(ctx, report, problem, compiled, checker, input)
		return
	}

	v.verifyInputAgainstPrimaryCorrect(ctx, report, problem, compiled, checker, input)
}

func (v verifier) verifyInputAgainstAnswerFile(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles, checker *executor.CompiledProgram, input testInput) {
	jury := util.CleanStdout(input.Answer.Content, "no")
	if checker != nil {
		result := v.runChecker(ctx, *checker, input.Content, jury, jury, helperLimits())
		if !result.Success || result.Verdict != contracts.VerdictAccepted {
			report.addExecution(StageChecker, problem.Checker.Filename, input.Seed, fmt.Sprintf("checker rejected answer file %s against itself", input.Answer.Filename), result)
		}
	}

	for _, correct := range problem.CorrectCodes {
		program := compiled[correct.Filename]
		if program == nil {
			continue
		}
		result := v.run(ctx, *program, input.Content, nil, limitsFor(problem, correct.Language))
		if !result.Success {
			report.addExecution(StageCorrectConsistency, correct.Filename, input.Seed, "correct solution failed on test input", result)
			continue
		}
		output := util.CleanStdout(result.Stdout, "no")
		if checker != nil {
			result := v.runChecker(ctx, *checker, input.Content, output, jury, helperLimits())
			if !result.Success || result.Verdict != contracts.VerdictAccepted {
				report.addExecution(StageCorrectConsistency, correct.Filename, input.Seed, fmt.Sprintf("correct solution output was rejected by checker against answer file %s", input.Answer.Filename), result)
			}
		} else if !util.CompareOutput(output, jury) {
			report.AddFinding(SeverityError, StageCorrectConsistency, correct.Filename, input.Seed, fmt.Sprintf("correct solution output differs from answer file %s", input.Answer.Filename), output, jury)
		}
	}
}

func (v verifier) verifyInputAgainstPrimaryCorrect(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles, checker *executor.CompiledProgram, input testInput) {
	var jury string
	primaryOK := false
	primaryCode := problem.CorrectCodes[0]
	primary := compiled[primaryCode.Filename]
	if primary != nil {
		primaryRun := v.run(ctx, *primary, input.Content, nil, limitsFor(problem, primaryCode.Language))
		if !primaryRun.Success {
			report.addExecution(StageCorrectConsistency, primaryCode.Filename, input.Seed, "correct solution failed on test input", primaryRun)
		} else {
			jury = util.CleanStdout(primaryRun.Stdout, "no")
			primaryOK = true
		}
	}

	if primaryOK && checker != nil {
		result := v.runChecker(ctx, *checker, input.Content, jury, jury, helperLimits())
		if !result.Success || result.Verdict != contracts.VerdictAccepted {
			report.addExecution(StageChecker, problem.Checker.Filename, input.Seed, "checker rejected identical participant and jury output", result)
		}
	}

	for i := 1; i < len(problem.CorrectCodes); i++ {
		correct := problem.CorrectCodes[i]
		program := compiled[correct.Filename]
		if program == nil {
			continue
		}
		result := v.run(ctx, *program, input.Content, nil, limitsFor(problem, correct.Language))
		if !result.Success {
			report.addExecution(StageCorrectConsistency, correct.Filename, input.Seed, "correct solution failed on test input", result)
			continue
		}
		if !primaryOK {
			continue
		}
		output := util.CleanStdout(result.Stdout, "no")
		if checker != nil {
			result := v.runChecker(ctx, *checker, input.Content, output, jury, helperLimits())
			if !result.Success || result.Verdict != contracts.VerdictAccepted {
				report.addExecution(StageCorrectConsistency, correct.Filename, input.Seed, "correct solution output was rejected by checker", result)
			}
		} else if !util.CompareOutput(output, jury) {
			report.AddFinding(SeverityError, StageCorrectConsistency, correct.Filename, input.Seed, "correct solution output differs from primary correct solution", output, jury)
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
		report.AddFinding(SeverityError, stage, filename, seed, fmt.Sprintf("generated testcase exceeds %d bytes", MaxGeneratedTestcaseBytes), "", "")
		return false
	}
	return true
}

func (report *VerifyReport) addExecution(stage Stage, filename string, seed *int, message string, result executor.ExecutionResult) {
	report.AddFinding(SeverityError, stage, filename, seed, fmt.Sprintf("%s: %s", message, result.Verdict), result.Stdout, result.Stderr)
}

func (report *VerifyReport) AddFinding(severity Severity, stage Stage, filename string, seed *int, message, stdout, stderr string) {
	report.Findings = append(report.Findings, Finding{
		Severity: severity,
		Stage:    stage,
		Filename: filename,
		Seed:     cloneInt(seed),
		Message:  message,
		Stdout:   excerpt(stdout),
		Stderr:   excerpt(stderr),
	})
	if severity == SeverityError {
		report.HasErrorFinding = true
	}
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
