package main

import (
	"context"
	"fmt"
	"log/slog"
	"math/rand"
	"sort"
	"strings"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executor"
)

const (
	maxWallTimeSeconds          = 90
	maxGeneratorExecutionErrors = 10
	defaultIterations           = 100
	caseLimitInResponse         = 3
)

type compiledProgram = executor.CompiledProgram

type compiledCaseProvider struct {
	contracts.CaseProvider
	Program *executor.CompiledProgram
}

type targetRun struct {
	Verdict       contracts.Verdict
	TargetOutput  string
	CheckerOutput string
	Stderr        string
	Time          float64
}

type stressIteration struct {
	Testcase      string
	GeneratedBy   contracts.GeneratedBy
	CorrectOutput string
	TargetRun     targetRun
}

type eventRecorder struct {
	events    []contracts.EventRecord
	startTime time.Time
}

func newEventRecorder() *eventRecorder {
	r := &eventRecorder{startTime: time.Now()}
	r.record("start_event_recorder", "")
	return r
}

func (r *eventRecorder) record(eventType, value string) {
	r.events = append(r.events, contracts.EventRecord{
		ID:             len(r.events) + 1,
		Type:           eventType,
		Value:          value,
		ElapsedSeconds: roundSeconds(time.Since(r.startTime)),
	})
}

func (r *eventRecorder) response() []contracts.EventRecord {
	r.record("end_event_recorder", "")
	return r.events
}

func operationStress(event contracts.StressEvent) (contracts.StressResult, error) {
	normalized := normalizeStressEvent(event)
	events := newEventRecorder()
	startTime := time.Now()

	if normalized.TargetCode == "" || normalized.CorrectCode == "" {
		return contracts.StressResult{}, NewResponseError(contracts.ErrorTypeMissingSourceCode, nil)
	}
	if len(normalized.CaseProviders) == 0 {
		return contracts.StressResult{}, NewResponseError(
			contracts.ErrorTypeMissingSourceCode,
			map[string]any{"message": "No case providers specified"},
		)
	}

	slog.Info("compile_start", "phase", "target")
	events.record("target_compile_start", "")
	targetProgram, err := compileAndGetProgram(
		normalized.TargetCode,
		normalized.TargetCodeLang,
		executor.Limits{TimeSeconds: normalized.TargetTimeLimit, MemoryMB: normalized.TargetMemoryLimit},
		contracts.ErrorTypeTargetCompilationFailed,
	)
	if err != nil {
		return contracts.StressResult{}, err
	}
	events.record("target_compile_done", "")

	slog.Info("compile_start", "phase", "correct")
	events.record("correct_compile_start", "")
	correctProgram, err := compileAndGetProgram(
		normalized.CorrectCode,
		normalized.CorrectCodeLang,
		executor.Limits{TimeSeconds: normalized.CorrectTimeLimit, MemoryMB: normalized.CorrectMemoryLimit},
		contracts.ErrorTypeCorrectCompilationFailed,
	)
	if err != nil {
		return contracts.StressResult{}, err
	}
	events.record("correct_compile_done", "")

	var checkerProgram *executor.CompiledProgram
	if normalized.CheckerCode != "" {
		slog.Info("compile_start", "phase", "checker")
		events.record("checker_compile_start", "")
		checkerProgram, err = compileAndGetProgram(
			normalized.CheckerCode,
			contracts.LanguageCpp23,
			executor.Limits{TimeSeconds: 2, MemoryMB: 1024},
			contracts.ErrorTypeCheckerCompilationFailed,
		)
		if err != nil {
			return contracts.StressResult{}, err
		}
		events.record("checker_compile_done", "")
	}

	providers, err := compileCaseProviders(normalized.CaseProviders, events)
	if err != nil {
		return contracts.StressResult{}, err
	}

	wrongCases, executionFailedCases, correctCases, err := runStressLoop(
		normalized.Iterations,
		startTime,
		*targetProgram,
		*correctProgram,
		checkerProgram,
		providers,
		events,
	)
	if err != nil {
		return contracts.StressResult{}, err
	}

	response := buildStressResponse(wrongCases, executionFailedCases, correctCases, checkerProgram != nil)
	response.RequestID = normalized.RequestID
	response.Events = events.response()
	return response, nil
}

func normalizeStressEvent(event contracts.StressEvent) contracts.StressEvent {
	if event.Operation == "" {
		event.Operation = contracts.OperationStress
	}
	if event.TargetCodeLang == "" {
		event.TargetCodeLang = contracts.LanguageCpp23
	}
	if event.CorrectCodeLang == "" {
		event.CorrectCodeLang = contracts.LanguageCpp23
	}
	if event.TargetTimeLimit == 0 {
		event.TargetTimeLimit = 2
	}
	if event.CorrectTimeLimit == 0 {
		event.CorrectTimeLimit = 2
	}
	if event.TargetMemoryLimit == 0 {
		event.TargetMemoryLimit = 1024
	}
	if event.CorrectMemoryLimit == 0 {
		event.CorrectMemoryLimit = 1024
	}
	if event.Iterations == 0 {
		event.Iterations = defaultIterations
	}
	return event
}

func compileCaseProviders(caseProviders []contracts.CaseProvider, events *eventRecorder) ([]compiledCaseProvider, error) {
	out := make([]compiledCaseProvider, 0, len(caseProviders))
	for _, provider := range caseProviders {
		compiled := compiledCaseProvider{
			CaseProvider: provider,
		}
		switch provider.Type {
		case contracts.CaseProviderText:
		case contracts.CaseProviderGenerator, contracts.CaseProviderSinglegen:
			events.record(string(provider.Type)+"_compile_start", provider.ID)
			program, err := compileAndGetProgram(
				provider.Code,
				provider.Language,
				executor.Limits{TimeSeconds: 2, MemoryMB: 1024},
				contracts.ErrorTypeGeneratorCompilationFailed,
			)
			if err != nil {
				return nil, err
			}
			compiled.Program = program
			events.record(string(provider.Type)+"_compile_done", provider.ID)
		default:
			return nil, NewResponseError(
				contracts.ErrorTypeInternalServerError,
				map[string]any{"message": "Unknown case provider type: " + string(provider.Type)},
			)
		}
		out = append(out, compiled)
	}
	return out, nil
}

func (p compiledCaseProvider) Generate(randomSeed int) (string, contracts.GeneratedBy, *executionResult, error) {
	switch p.Type {
	case contracts.CaseProviderText:
		return executor.CleanStdout(p.Content, "always"), contracts.GeneratedBy{
			Stage: p.Type,
			ID:    p.ID,
		}, nil, nil
	case contracts.CaseProviderGenerator, contracts.CaseProviderSinglegen:
		if p.Program == nil {
			return "", contracts.GeneratedBy{}, nil, NewResponseError(contracts.ErrorTypeInternalServerError, map[string]any{"message": "Missing compiled case provider program"})
		}
		args := []string{}
		generatedBy := contracts.GeneratedBy{Stage: p.Type, ID: p.ID}
		if p.Type == contracts.CaseProviderGenerator {
			seed := itoa(randomSeed)
			args = []string{seed}
			generatedBy.Seed = stringPtr(seed)
		}
		execution := executor.Run(context.Background(), *p.Program, "", args, p.Program.Limits)
		if !execution.Success {
			return "", contracts.GeneratedBy{}, &execution, nil
		}
		return executor.CleanStdout(execution.Stdout, "always"), generatedBy, nil, nil
	default:
		return "", contracts.GeneratedBy{}, nil, NewResponseError(
			contracts.ErrorTypeInternalServerError,
			map[string]any{"message": "Unknown case provider type: " + string(p.Type)},
		)
	}
}

func runStressLoop(
	iterations int,
	startTime time.Time,
	targetCode compiledProgram,
	correctCode compiledProgram,
	checkerCode *compiledProgram,
	caseProviders []compiledCaseProvider,
	events *eventRecorder,
) ([]stressIteration, []stressIteration, []stressIteration, error) {
	oneShotQueue := []compiledCaseProvider{}
	generators := []compiledCaseProvider{}
	for _, provider := range caseProviders {
		if provider.Type == contracts.CaseProviderGenerator {
			generators = append(generators, provider)
		} else {
			oneShotQueue = append(oneShotQueue, provider)
		}
	}
	generatorWeights := make([]float64, len(generators))
	for i := range generatorWeights {
		generatorWeights[i] = 1.0
	}

	random := rand.New(rand.NewSource(time.Now().UnixNano()))
	wrongCases := []stressIteration{}
	executionFailedCases := []stressIteration{}
	correctCases := []stressIteration{}
	generatorExecutionErrors := []error{}

	for iteration := 0; iteration < iterations; iteration++ {
		events.record("iteration_start", itoa(iteration))
		if time.Since(startTime) > maxWallTimeSeconds*time.Second {
			slog.Info("stress_loop_exit", "reason", "wall_time_limit", "iteration", iteration, "max_wall_time_seconds", maxWallTimeSeconds)
			break
		}
		if iteration > 0 && iteration%10 == 0 && len(correctCases) < iteration/10 {
			slog.Info("stress_loop_exit", "reason", "correct_rate_too_low", "iteration", iteration, "correct_cases", len(correctCases))
			break
		}
		if len(generatorExecutionErrors) >= maxGeneratorExecutionErrors {
			return nil, nil, nil, generatorExecutionErrors[len(generatorExecutionErrors)-1]
		}

		selectedGeneratorIndex := -1
		var provider compiledCaseProvider
		if len(oneShotQueue) > 0 {
			provider = oneShotQueue[0]
			oneShotQueue = oneShotQueue[1:]
		} else if len(generators) > 0 {
			selectedGeneratorIndex = weightedChoice(random, generatorWeights)
			provider = generators[selectedGeneratorIndex]
		} else {
			break
		}

		randomSeed := random.Intn(1_000_000_000)
		iterationResult, err := stressTestIteration(targetCode, correctCode, checkerCode, provider, randomSeed)
		if err != nil {
			if responseErr, ok := err.(*ResponseError); ok && responseErr.errorType == contracts.ErrorTypeGeneratorExecutionFailed {
				slog.Warn("generator_execution_failed", "iteration", iteration, "error_type", responseErr.errorType)
				generatorExecutionErrors = append(generatorExecutionErrors, err)
				if selectedGeneratorIndex >= 0 {
					generatorWeights[selectedGeneratorIndex] *= 0.1
				}
				continue
			}
			return nil, nil, nil, err
		}

		switch iterationResult.TargetRun.Verdict {
		case contracts.VerdictAccepted:
			correctCases = append(correctCases, iterationResult)
		case contracts.VerdictWrongAnswer:
			wrongCases = append(wrongCases, iterationResult)
		default:
			executionFailedCases = append(executionFailedCases, iterationResult)
		}

		if selectedGeneratorIndex >= 0 {
			cur := generatorWeights[selectedGeneratorIndex]
			if iterationResult.TargetRun.Verdict == contracts.VerdictAccepted {
				if 0.98*cur > 0.5 {
					generatorWeights[selectedGeneratorIndex] = 0.98 * cur
				} else {
					generatorWeights[selectedGeneratorIndex] = 0.5
				}
			} else {
				if 1.1*cur < 2.0 {
					generatorWeights[selectedGeneratorIndex] = 1.1 * cur
				} else {
					generatorWeights[selectedGeneratorIndex] = 2.0
				}
			}
		}
	}

	return wrongCases, executionFailedCases, correctCases, nil
}

func buildStressResponse(wrongCases, executionFailedCases, correctCases []stressIteration, useChecker bool) contracts.StressResult {
	totalCases := len(wrongCases) + len(executionFailedCases) + len(correctCases)
	wrongCount := len(wrongCases)
	failedCount := len(executionFailedCases)
	correctCount := len(correctCases)

	wrongSamples := dedupAndSort(wrongCases)
	if len(wrongSamples) > caseLimitInResponse {
		wrongSamples = wrongSamples[:caseLimitInResponse]
	}
	failedSamples := dedupAndSort(executionFailedCases)
	if len(failedSamples) > caseLimitInResponse {
		failedSamples = failedSamples[:caseLimitInResponse]
	}

	result := contracts.StressResult{
		Error:                     false,
		WrongCases:                make([]contracts.Counterexample, 0, len(wrongSamples)),
		ExecutionFailedCases:      make([]contracts.ExecutionFailedCase, 0, len(failedSamples)),
		CorrectCases:              make([]contracts.CorrectCase, 0, len(correctCases)),
		TotalCases:                totalCases,
		WrongCasesCount:           wrongCount,
		ExecutionFailedCasesCount: failedCount,
		CorrectCasesCount:         correctCount,
	}
	for _, item := range wrongSamples {
		counterexample := contracts.Counterexample{
			Testcase:      textWithMetadata(item.Testcase, 1000, 40),
			GeneratedBy:   item.GeneratedBy,
			TargetOutput:  textWithMetadata(item.TargetRun.TargetOutput, 1000, 40),
			CorrectOutput: textWithMetadata(item.CorrectOutput, 1000, 40),
			Verdict:       verdictPtr(item.TargetRun.Verdict),
			Stderr:        textWithMetadataPtr(item.TargetRun.Stderr),
		}
		if useChecker {
			counterexample.CheckerOutput = textWithMetadataPtr(item.TargetRun.CheckerOutput)
		}
		result.WrongCases = append(result.WrongCases, counterexample)
	}
	for _, item := range failedSamples {
		result.ExecutionFailedCases = append(result.ExecutionFailedCases, contracts.ExecutionFailedCase{
			Testcase:      textWithMetadata(item.Testcase, 1000, 40),
			GeneratedBy:   item.GeneratedBy,
			CorrectOutput: textWithMetadata(item.CorrectOutput, 1000, 40),
			Reason:        item.TargetRun.Verdict,
			Stderr:        textWithMetadataPtr(item.TargetRun.Stderr),
			TimeSeconds:   item.TargetRun.Time,
		})
	}
	for _, item := range correctCases {
		result.CorrectCases = append(result.CorrectCases, contracts.CorrectCase{GeneratedBy: item.GeneratedBy})
	}
	return result
}

func dedupAndSort(items []stressIteration) []stressIteration {
	byTestcase := make(map[string]stressIteration, len(items))
	order := []string{}
	for _, item := range items {
		key := cleanStdout(item.Testcase, "no")
		if _, exists := byTestcase[key]; !exists {
			byTestcase[key] = item
			order = append(order, key)
		}
	}
	out := make([]stressIteration, 0, len(order))
	for _, key := range order {
		out = append(out, byTestcase[key])
	}
	sort.Slice(out, func(i, j int) bool {
		a := out[i]
		b := out[j]
		aScore := len(a.Testcase) + strings.Count(a.TargetRun.TargetOutput, "\n") + strings.Count(a.CorrectOutput, "\n")
		bScore := len(b.Testcase) + strings.Count(b.TargetRun.TargetOutput, "\n") + strings.Count(b.CorrectOutput, "\n")
		if aScore != bScore {
			return aScore < bScore
		}
		return compareIntSlices(intInFirstLine(firstNRunes(a.Testcase, 100)), intInFirstLine(firstNRunes(b.Testcase, 100)))
	})
	return out
}

func compareIntSlices(a, b []int) bool {
	for i := 0; i < len(a) && i < len(b); i++ {
		if a[i] != b[i] {
			return a[i] < b[i]
		}
	}
	return len(a) < len(b)
}

func weightedChoice(random *rand.Rand, weights []float64) int {
	total := 0.0
	for _, weight := range weights {
		total += weight
	}
	target := random.Float64() * total
	running := 0.0
	for i, weight := range weights {
		running += weight
		if target <= running {
			return i
		}
	}
	return len(weights) - 1
}

func textWithMetadataPtr(s string) *contracts.TextWithMetadata {
	if s == "" {
		return nil
	}
	value := textWithMetadata(s, 1000, 40)
	return &value
}

func verdictPtr(value contracts.Verdict) *contracts.Verdict {
	return &value
}

func itoa(value int) string {
	return fmt.Sprintf("%d", value)
}
