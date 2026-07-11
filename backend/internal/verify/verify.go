package verify

import (
	"context"
	"fmt"
	"hash/maphash"
	"strings"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executionlimits"
	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
	"github.com/testcase-ac/testcase-ac/backend/internal/util"
)

const (
	GeneratorRuns              = 100
	MinimumDistinctGeneratorIO = 3
	bytesPerMiB                = 1024 * 1024
	MaxFixedTestcaseBytes      = 2 * bytesPerMiB
	// BOJ 2170 has a valid max-size generated input of 23,000,008 bytes; keep this limit above that.
	MaxGeneratedTestcaseBytes  = 32 * bytesPerMiB
	MaxStressEventPayloadBytes = 5 * bytesPerMiB
	generatorTimeoutSeconds    = 2
	// BOJ 25687's max case checks two 30,890,896-byte outputs and measured about 3s in the Docker runtime.
	helperTimeoutSeconds = 5
	helperMemoryMB       = 1024
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
	StageRejected           Stage = "rejected"
)

type Finding struct {
	Severity      Severity `json:"severity"`
	Stage         Stage    `json:"stage"`
	Filename      string   `json:"filename,omitempty"`
	InputFilename string   `json:"inputFilename,omitempty"`
	Seed          *int     `json:"seed,omitempty"`
	Message       string   `json:"message"`
	Stdout        string   `json:"stdout,omitempty"`
	Stderr        string   `json:"stderr,omitempty"`
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

type outputFingerprint struct {
	hash uint64
	size int
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

// verifyProblemWithOptions runs the verifier lifecycle for one loaded problem.
func (v verifier) verifyProblemWithOptions(ctx context.Context, problem loader.Problem, options VerifyOptions) VerifyReport {
	options = options.normalized()
	start := time.Now()
	report := VerifyReport{ProblemType: problem.ProblemType, ExternalID: problem.ExternalID}
	addStaticFindings(&report, problem, options)

	compiled := v.compileAll(ctx, &report, problem, options)
	inputs := newInputVerifier(v, &report, problem, compiled, options)
	v.verifyInputs(ctx, &report, problem, compiled, options, &inputs)
	inputs.reportRejectedSolutionsAcceptedByAllCheckedInputs()

	report.RuntimeSeconds = util.RoundSeconds(time.Since(start))
	return report
}

func addStaticFindings(report *VerifyReport, problem loader.Problem, options VerifyOptions) {
	if options.Mode != VerifyModeValidateInputs && len(problem.CorrectCodes) == 0 {
		report.AddFinding(SeverityWarning, StageStatic, "", nil, "problem has no correct solution; skipping correct-solution checks", "", "")
	}
	if problem.OutputOnly {
		for _, file := range problem.IgnoredOutputOnlyFiles {
			report.AddFinding(SeverityError, StageStatic, file.Filename, nil, fmt.Sprintf("output-only problem must not include %s file", file.Role), "", "")
		}
	} else {
		if len(problem.Generators)+len(problem.Singlegens)+len(problem.Testcases) == 0 {
			report.AddFinding(SeverityError, StageStatic, "", nil, "problem has no case provider", "", "")
		}
		if problem.Validator == nil {
			report.AddFinding(SeverityError, StageStatic, "validator.cpp", nil, "problem has no validator", "", "")
		}
	}
	for _, testcase := range problem.Testcases {
		verifyTestcaseText(report, testcase.Filename, testcase.Content)
	}
	if options.Mode != VerifyModeValidateInputs {
		verifyAnswerFiles(report, problem.AnswerFiles)
		verifyStressPayloadSize(report, problem)
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
	// Build the list of source files needed for this verification mode.
	files := []loader.CodeFile{}
	if options.Mode != VerifyModeValidateInputs {
		files = append(files, problem.CorrectCodes...)
		files = append(files, problem.RejectedCodes...)
	}
	if problem.OutputOnly {
		if options.Mode != VerifyModeValidateInputs && problem.Checker != nil {
			files = append(files, *problem.Checker)
		}
	} else {
		files = append(files, problem.Generators...)
		files = append(files, problem.Singlegens...)
		if problem.Validator != nil {
			files = append(files, *problem.Validator)
		}
		if options.Mode != VerifyModeValidateInputs && problem.Checker != nil {
			files = append(files, *problem.Checker)
		}
	}

	// Compile the selected source files.
	out := compiledFiles{}
	for _, file := range files {
		result := v.compile(ctx, executor.Source{Code: file.Content, Language: file.Language})
		if !result.Success {
			report.AddFinding(SeverityError, StageCompile, file.Filename, nil, "compilation failed", result.Stdout, result.Stderr)
			continue
		}
		out[file.Filename] = result.Program
	}
	return out
}

// verifyInputs samples case-provider inputs before handing each one to inputVerifier.
func (v verifier) verifyInputs(ctx context.Context, report *VerifyReport, problem loader.Problem, compiled compiledFiles, options VerifyOptions, inputs *inputVerifier) {
	if problem.OutputOnly {
		inputs.verifyOutputOnly(ctx)
		return
	}
	if problem.Validator == nil {
		return
	}
	if compiled[problem.Validator.Filename] == nil {
		return
	}

	for _, testcase := range problem.Testcases {
		content := testcase.Content
		if validGeneratedSize(report, StageStatic, testcase.Filename, nil, content) {
			inputs.verify(ctx, testInput{Content: content, Filename: testcase.Filename})
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
		firstOut := first.Stdout
		if options.Mode != VerifyModeValidateInputs {
			v.sleep(time.Second)
			second := v.run(ctx, *program, "", nil, generatorLimits())
			if !second.Success {
				report.addExecution(StageSinglegen, singlegen.Filename, nil, "singlegen repeat execution failed", second)
				continue
			}
			secondOut := second.Stdout
			if firstOut != secondOut {
				report.AddFinding(SeverityError, StageSinglegen, singlegen.Filename, nil, "singlegen output changed between runs", first.Stdout, second.Stdout)
				continue
			}
		}
		if validGeneratedSize(report, StageSinglegen, singlegen.Filename, nil, firstOut) {
			inputs.verify(ctx, testInput{Content: firstOut, Filename: singlegen.Filename})
		}
	}
	for _, generator := range problem.Generators {
		program := compiled[generator.Filename]
		if program == nil {
			continue
		}
		fingerprintSeed := maphash.MakeSeed()
		seen := make(map[outputFingerprint]struct{}, GeneratorRuns)
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
			seen[fingerprintOutput(fingerprintSeed, output)] = struct{}{}
			s := seed
			inputs.verify(ctx, testInput{Content: output, Filename: generator.Filename, Seed: &s})
		}
		if options.Mode != VerifyModeValidateInputs && len(seen) < MinimumDistinctGeneratorIO {
			report.AddFinding(SeverityError, StageGenerator, generator.Filename, nil, fmt.Sprintf("generator produced %d distinct outputs across %d seeds; want at least %d", len(seen), GeneratorRuns, MinimumDistinctGeneratorIO), "", "")
		}
	}
}

func (v verifier) runGenerator(ctx context.Context, report *VerifyReport, filename string, program executor.CompiledProgram, seed int) (string, bool) {
	result := v.run(ctx, program, "", []string{fmt.Sprintf("%d", seed)}, generatorLimits())
	if !result.Success {
		report.addExecution(StageGenerator, filename, &seed, "generator execution failed", result)
		return "", false
	}
	output := result.Stdout
	if !validGeneratedSize(report, StageGenerator, filename, &seed, output) {
		return "", false
	}
	return output, true
}

func fingerprintOutput(seed maphash.Seed, output string) outputFingerprint {
	return outputFingerprint{hash: maphash.String(seed, output), size: len(output)}
}

func limitsFor(problem loader.Problem, language contracts.Language) executor.Limits {
	timeLimitMS := problem.TimeLimitMS
	if timeLimitMS <= 0 {
		timeLimitMS = 2000
	}
	memoryMB := problem.MemoryLimitMB
	if memoryMB <= 0 {
		memoryMB = 256
	}
	timeSeconds, memoryMB := executionlimits.Adjusted(problem.ProblemType, language, timeLimitMS, memoryMB)
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

// addExecution records a failure for an executed artifact without input-provider context.
func (report *VerifyReport) addExecution(stage Stage, filename string, seed *int, message string, result executor.ExecutionResult) {
	report.AddFinding(SeverityError, stage, filename, seed, fmt.Sprintf("%s: %s", message, result.Verdict), result.Stdout, result.Stderr)
}

// addInputExecution records a failure for an executed artifact on a specific case provider.
func (report *VerifyReport) addInputExecution(stage Stage, filename string, input testInput, message string, result executor.ExecutionResult) {
	report.addFinding(SeverityError, stage, filename, input.Filename, input.Seed, fmt.Sprintf("%s: %s", message, result.Verdict), result.Stdout, result.Stderr)
}

func (report *VerifyReport) AddFinding(severity Severity, stage Stage, filename string, seed *int, message, stdout, stderr string) {
	report.addFinding(severity, stage, filename, "", seed, message, stdout, stderr)
}

func (report *VerifyReport) addFinding(severity Severity, stage Stage, filename string, inputFilename string, seed *int, message, stdout, stderr string) {
	report.Findings = append(report.Findings, Finding{
		Severity:      severity,
		Stage:         stage,
		Filename:      filename,
		InputFilename: inputFilename,
		Seed:          cloneInt(seed),
		Message:       message,
		Stdout:        excerpt(stdout),
		Stderr:        excerpt(stderr),
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
