package main

import (
	"context"
	"encoding/json"
	"errors"
	"fmt"
	"log/slog"
	"net/http"
	"slices"
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

var errorTypeToStatus = map[contracts.ErrorType]StressStatus{
	contracts.ErrorTypeTargetCompilationFailed:    contracts.StressStatusCompileError,
	contracts.ErrorTypeTargetExecutionFailed:      contracts.StressStatusRuntimeError,
	contracts.ErrorTypeCorrectCompilationFailed:   contracts.StressStatusInvalidProblem,
	contracts.ErrorTypeCorrectExecutionFailed:     contracts.StressStatusInvalidProblem,
	contracts.ErrorTypeGeneratorCompilationFailed: contracts.StressStatusInvalidProblem,
	contracts.ErrorTypeGeneratorExecutionFailed:   contracts.StressStatusInvalidProblem,
	contracts.ErrorTypeCheckerCompilationFailed:   contracts.StressStatusInvalidProblem,
	contracts.ErrorTypeCheckerExecutionFailed:     contracts.StressStatusInvalidProblem,
	contracts.ErrorTypeMissingSourceCode:          contracts.StressStatusInvalidProblem,
	contracts.ErrorTypeInvalidLanguage:            contracts.StressStatusInvalidProblem,
	contracts.ErrorTypeInvalidOperation:           contracts.StressStatusInternalError,
	contracts.ErrorTypeInternalServerError:        contracts.StressStatusInternalError,
}

type executionLimitPolicy struct {
	timeMultiplier   int
	timeAdditionMS   int
	memoryMultiplier int
	memoryAdditionMB int
}

var bojExecutionLimitPolicies = map[contracts.Language]executionLimitPolicy{
	contracts.LanguagePython3:  {timeMultiplier: 3, timeAdditionMS: 2000, memoryMultiplier: 2, memoryAdditionMB: 32},
	contracts.LanguagePyPy3:    {timeMultiplier: 3, timeAdditionMS: 2000, memoryMultiplier: 2, memoryAdditionMB: 128},
	contracts.LanguageJava:     {timeMultiplier: 2, timeAdditionMS: 1000, memoryMultiplier: 2, memoryAdditionMB: 16},
	contracts.LanguageKotlin:   {timeMultiplier: 2, timeAdditionMS: 1000, memoryMultiplier: 2, memoryAdditionMB: 16},
	contracts.LanguageCSharp:   {timeMultiplier: 2, timeAdditionMS: 1000, memoryMultiplier: 2, memoryAdditionMB: 16},
	contracts.LanguageNodeJS:   {timeMultiplier: 3, timeAdditionMS: 2000, memoryMultiplier: 2, memoryAdditionMB: 0},
	contracts.LanguageGolang:   {timeMultiplier: 1, timeAdditionMS: 2000, memoryMultiplier: 1, memoryAdditionMB: 512},
	contracts.LanguageRust2021: {timeMultiplier: 1, timeAdditionMS: 0, memoryMultiplier: 1, memoryAdditionMB: 16},
}

func adjustedExecutionLimits(problemType string, language contracts.Language, timeLimitMS, memoryLimitMB int) (float64, int) {
	if problemType != "boj" {
		return float64(timeLimitMS) / 1000.0, memoryLimitMB
	}
	policy, ok := bojExecutionLimitPolicies[language]
	if !ok {
		return float64(timeLimitMS) / 1000.0, memoryLimitMB
	}
	adjustedTimeMS := timeLimitMS*policy.timeMultiplier + policy.timeAdditionMS
	adjustedMemoryMB := memoryLimitMB*policy.memoryMultiplier + policy.memoryAdditionMB
	return float64(adjustedTimeMS) / 1000.0, adjustedMemoryMB
}

func BuildStresserEvent(problem Problem, request StressRequest, requestID string) (contracts.StressEvent, int, string, bool) {
	if len(problem.CorrectCodes) == 0 {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, fmt.Sprintf("Problem %s/%s has no correct solution", problem.ProblemType, problem.ExternalID), false
	}

	referenceCode, referenceLang, ok, detail := resolveCorrectCode(problem, request)
	if !ok {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, detail, false
	}
	checkerCode := contentOrEmpty(problem.Checker)
	if request.CheckerCode != nil {
		checkerCode = *request.CheckerCode
	}
	caseProviders, ok, detail := resolveCaseProviders(problem, request)
	if !ok {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, detail, false
	}
	selectedSinglegens, ok, detail := selectByFilename(problem.Singlegens, request.SinglegenFilenames, "single generators")
	if !ok {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, detail, false
	}

	caseProviders = append(caseProviders, buildSinglegenProviders(selectedSinglegens)...)
	if len(caseProviders) == 0 {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, "At least one testcase, generator, or single generator must be selected", false
	}

	targetLang := request.targetLangValue()
	targetTimeLimitS, targetMemoryLimitMB := adjustedExecutionLimits(problem.ProblemType, targetLang, problem.TimeLimitMS, problem.MemoryLimitMB)
	correctTimeLimitS, correctMemoryLimitMB := adjustedExecutionLimits(problem.ProblemType, referenceLang, problem.TimeLimitMS, problem.MemoryLimitMB)
	return contracts.StressEvent{
		Operation:          contracts.OperationStress,
		RequestID:          requestID,
		TargetCode:         request.TargetCode,
		TargetCodeLang:     targetLang,
		CorrectCode:        referenceCode,
		CorrectCodeLang:    referenceLang,
		CheckerCode:        checkerCode,
		TargetTimeLimit:    targetTimeLimitS,
		TargetMemoryLimit:  targetMemoryLimitMB,
		CorrectTimeLimit:   correctTimeLimitS,
		CorrectMemoryLimit: correctMemoryLimitMB,
		Iterations:         request.iterationsValue(),
		CaseProviders:      caseProviders,
	}, 0, "", true
}

func BuildCustomStresserEvent(request StressRequest, requestID string) (contracts.StressEvent, int, string, bool) {
	if request.CorrectCode == "" {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, "correctCode is required for custom invocation", false
	}
	if request.TimeLimitMS == nil {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, "timeLimitMs is required for custom invocation", false
	}
	if request.MemoryLimitMB == nil {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, "memoryLimitMb is required for custom invocation", false
	}

	caseProviders := make([]contracts.CaseProvider, 0, len(request.TextTestcases)+len(request.GeneratorSources))

	textcaseProviders, ok, detail := buildInlineTextcaseProviders(request.TextTestcases)
	if !ok {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, detail, false
	}
	caseProviders = append(caseProviders, textcaseProviders...)

	generatorProviders, ok, detail := buildInlineGeneratorProviders(request.GeneratorSources)
	if !ok {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, detail, false
	}
	caseProviders = append(caseProviders, generatorProviders...)

	if len(caseProviders) == 0 {
		return contracts.StressEvent{}, http.StatusUnprocessableEntity, "At least one text testcase or generator is required for custom invocation", false
	}

	checkerCode := ""
	if request.CheckerCode != nil {
		checkerCode = *request.CheckerCode
	}
	timeLimitSeconds := float64(*request.TimeLimitMS) / 1000.0
	memoryLimitMB := *request.MemoryLimitMB
	return contracts.StressEvent{
		Operation:          contracts.OperationStress,
		RequestID:          requestID,
		TargetCode:         request.TargetCode,
		TargetCodeLang:     request.targetLangValue(),
		CorrectCode:        request.CorrectCode,
		CorrectCodeLang:    request.correctLangValue(),
		CheckerCode:        checkerCode,
		TargetTimeLimit:    timeLimitSeconds,
		TargetMemoryLimit:  memoryLimitMB,
		CorrectTimeLimit:   timeLimitSeconds,
		CorrectMemoryLimit: memoryLimitMB,
		Iterations:         request.iterationsValue(),
		CaseProviders:      caseProviders,
	}, 0, "", true
}

func resolveCorrectCode(problem Problem, request StressRequest) (string, contracts.Language, bool, string) {
	if request.CorrectCode != "" {
		return request.CorrectCode, request.correctLangValue(), true, ""
	}
	reference, ok, detail := selectSingleCode(problem.CorrectCodes, request.CorrectCodeFilename, "correct code")
	if !ok {
		return "", "", false, detail
	}
	return reference.Content, reference.Language, true, ""
}

func resolveCaseProviders(problem Problem, request StressRequest) ([]contracts.CaseProvider, bool, string) {
	caseProviders := make([]contracts.CaseProvider, 0, len(problem.Testcases)+len(problem.Generators))

	testcaseProviders, ok, detail := resolveTextcaseProviders(problem, request)
	if !ok {
		return nil, false, detail
	}
	caseProviders = append(caseProviders, testcaseProviders...)

	generatorProviders, ok, detail := resolveGeneratorProviders(problem, request)
	if !ok {
		return nil, false, detail
	}
	caseProviders = append(caseProviders, generatorProviders...)

	return caseProviders, true, ""
}

func resolveTextcaseProviders(problem Problem, request StressRequest) ([]contracts.CaseProvider, bool, string) {
	if request.TextTestcases != nil {
		return buildInlineTextcaseProviders(request.TextTestcases)
	}
	selectedTestcases, ok, detail := selectByFilename(problem.Testcases, request.TestcaseFilenames, "testcases")
	if !ok {
		return nil, false, detail
	}
	out := make([]contracts.CaseProvider, 0, len(selectedTestcases))
	for _, testcase := range selectedTestcases {
		out = append(out, contracts.CaseProvider{
			Type:    contracts.CaseProviderText,
			ID:      testcase.Filename,
			Content: testcase.Content,
		})
	}
	return out, true, ""
}

func resolveGeneratorProviders(problem Problem, request StressRequest) ([]contracts.CaseProvider, bool, string) {
	if request.GeneratorSources != nil {
		return buildInlineGeneratorProviders(request.GeneratorSources)
	}
	selectedGenerators, ok, detail := selectByFilename(problem.Generators, request.GeneratorFilenames, "generators")
	if !ok {
		return nil, false, detail
	}
	out := make([]contracts.CaseProvider, 0, len(selectedGenerators))
	for _, generator := range selectedGenerators {
		out = append(out, contracts.CaseProvider{
			Type:     contracts.CaseProviderGenerator,
			ID:       generator.Filename,
			Code:     generator.Content,
			Language: generator.Language,
		})
	}
	return out, true, ""
}

func buildInlineTextcaseProviders(inputs []InlineTextcaseInput) ([]contracts.CaseProvider, bool, string) {
	out := make([]contracts.CaseProvider, 0, len(inputs))
	for _, input := range inputs {
		if strings.TrimSpace(input.ID) == "" {
			return nil, false, "textTestcases entries require a non-empty id"
		}
		out = append(out, contracts.CaseProvider{
			Type:    contracts.CaseProviderText,
			ID:      input.ID,
			Content: input.Content,
		})
	}
	return out, true, ""
}

func buildInlineGeneratorProviders(inputs []InlineCodeInput) ([]contracts.CaseProvider, bool, string) {
	out := make([]contracts.CaseProvider, 0, len(inputs))
	for _, input := range inputs {
		if strings.TrimSpace(input.ID) == "" || strings.TrimSpace(input.Code) == "" {
			return nil, false, "generatorSources entries require non-empty id and code"
		}
		if !isSupportedLanguage(input.Language) {
			return nil, false, supportedTargetCodeLangDetail
		}
		out = append(out, contracts.CaseProvider{
			Type:     contracts.CaseProviderGenerator,
			ID:       input.ID,
			Code:     input.Code,
			Language: input.Language,
		})
	}
	return out, true, ""
}

func buildSinglegenProviders(inputs []CodeFile) []contracts.CaseProvider {
	out := make([]contracts.CaseProvider, 0, len(inputs))
	for _, singlegen := range inputs {
		out = append(out, contracts.CaseProvider{
			Type:     contracts.CaseProviderSinglegen,
			ID:       singlegen.Filename,
			Code:     singlegen.Content,
			Language: singlegen.Language,
		})
	}
	return out
}

func RunStress(ctx context.Context, problem Problem, request StressRequest, requestID string, stresser StresserClient) (StressResponse, int, string, bool) {
	event, statusCode, detail, ok := BuildStresserEvent(problem, request, requestID)
	if !ok {
		return StressResponse{}, statusCode, detail, false
	}
	return invokeStressEvent(
		ctx,
		event,
		requestID,
		stresser,
		"problem_type", problem.ProblemType,
		"external_id", problem.ExternalID,
	)
}

func RunCustomStress(ctx context.Context, request StressRequest, requestID string, stresser StresserClient) (StressResponse, int, string, bool) {
	event, statusCode, detail, ok := BuildCustomStresserEvent(request, requestID)
	if !ok {
		return StressResponse{}, statusCode, detail, false
	}
	return invokeStressEvent(ctx, event, requestID, stresser, "custom_invocation", true)
}

func invokeStressEvent(ctx context.Context, event contracts.StressEvent, requestID string, stresser StresserClient, attrs ...any) (StressResponse, int, string, bool) {
	logAttrs := []any{
		"request_id", requestID,
		"case_providers", len(event.CaseProviders),
		"iterations", event.Iterations,
	}
	logAttrs = append(logAttrs, attrs...)
	slog.Info(
		"stress_dispatch",
		logAttrs...,
	)
	stresserResp, err := stresser.Invoke(ctx, event)
	if err != nil {
		var invokeErr *StresserInvokeError
		if ok := errors.As(err, &invokeErr); ok {
			return StressResponse{}, invokeErr.StatusCode, invokeErr.Detail, false
		}
		return StressResponse{}, http.StatusServiceUnavailable, "Stresser is unavailable, try again shortly.", false
	}
	response := transformStresserResponse(stresserResp, requestID)
	return response, 0, "", true
}

func transformStresserResponse(stresserResp contracts.StressResult, requestID string) StressResponse {
	if stresserResp.Error {
		status := errorTypeToStatus[stresserResp.ErrorType]
		if status == "" {
			status = contracts.StressStatusInternalError
		}
		errText := extractErrorText(stresserResp.Message)
		return StressResponse{
			RequestID:                 requestID,
			RuntimeSeconds:            stresserResp.RuntimeSeconds,
			Status:                    status,
			WrongCases:                []Counterexample{},
			ExecutionFailedCases:      []ExecutionFailedCase{},
			Counterexamples:           []Counterexample{},
			ErrorMessage:              stringPtr(errText),
			AttemptedCases:            []AttemptedCase{},
			TotalCases:                0,
			TotalAttempted:            0,
			WrongCasesCount:           0,
			ExecutionFailedCasesCount: 0,
			CorrectCasesCount:         0,
		}
	}

	attemptedCases := make([]AttemptedCase, 0, len(stresserResp.CorrectCases))
	for _, correctCase := range stresserResp.CorrectCases {
		attemptedCases = append(attemptedCases, correctCase.GeneratedBy)
	}
	totalCases := stresserResp.TotalCases
	correctCasesCount := stresserResp.CorrectCasesCount
	wrongCases := slices.Clone(stresserResp.WrongCases)
	executionFailedCases := slices.Clone(stresserResp.ExecutionFailedCases)
	if len(wrongCases) > 0 || len(executionFailedCases) > 0 {
		counterexamples := slices.Clone(wrongCases)
		var first *Counterexample
		if len(counterexamples) > 0 {
			first = &counterexamples[0]
		}
		return StressResponse{
			RequestID:                 requestID,
			RuntimeSeconds:            stresserResp.RuntimeSeconds,
			Status:                    contracts.StressStatusFound,
			WrongCases:                wrongCases,
			ExecutionFailedCases:      executionFailedCases,
			Counterexamples:           counterexamples,
			Counterexample:            first,
			ErrorMessage:              nil,
			AttemptedCases:            attemptedCases,
			TotalCases:                totalCases,
			TotalAttempted:            correctCasesCount,
			WrongCasesCount:           stresserResp.WrongCasesCount,
			ExecutionFailedCasesCount: stresserResp.ExecutionFailedCasesCount,
			CorrectCasesCount:         correctCasesCount,
		}
	}
	return StressResponse{
		RequestID:                 requestID,
		RuntimeSeconds:            stresserResp.RuntimeSeconds,
		Status:                    contracts.StressStatusNotFound,
		WrongCases:                []Counterexample{},
		ExecutionFailedCases:      []ExecutionFailedCase{},
		Counterexamples:           []Counterexample{},
		Counterexample:            nil,
		ErrorMessage:              nil,
		AttemptedCases:            attemptedCases,
		TotalCases:                totalCases,
		TotalAttempted:            correctCasesCount,
		WrongCasesCount:           stresserResp.WrongCasesCount,
		ExecutionFailedCasesCount: stresserResp.ExecutionFailedCasesCount,
		CorrectCasesCount:         correctCasesCount,
	}
}

func selectSingleCode(available []CodeFile, requestedName *string, kindLabel string) (CodeFile, bool, string) {
	requestedNames := []string(nil)
	if requestedName != nil {
		requestedNames = []string{*requestedName}
	}
	selected, ok, detail := selectByFilename(available, requestedNames, kindLabel)
	if !ok {
		return CodeFile{}, false, detail
	}
	if len(selected) == 0 {
		return CodeFile{}, false, fmt.Sprintf("No %s available for this problem", kindLabel)
	}
	return selected[0], true, ""
}

type hasFilename interface {
	FilenameValue() string
}

func selectByFilename[T hasFilename](available []T, requestedNames []string, kindLabel string) ([]T, bool, string) {
	if requestedNames == nil {
		return slices.Clone(available), true, ""
	}
	byName := make(map[string]T, len(available))
	for _, item := range available {
		byName[item.FilenameValue()] = item
	}
	selected := make([]T, 0, len(requestedNames))
	missing := make([]string, 0)
	for _, name := range requestedNames {
		item, ok := byName[name]
		if !ok {
			missing = append(missing, name)
			continue
		}
		selected = append(selected, item)
	}
	if len(missing) > 0 {
		slices.Sort(missing)
		return nil, false, fmt.Sprintf("Unknown %s for this problem: %s", kindLabel, strings.Join(missing, ", "))
	}
	return selected, true, ""
}

func extractErrorText(rawMessage string) string {
	if rawMessage == "" {
		return ""
	}
	var parsed map[string]any
	if err := json.Unmarshal([]byte(rawMessage), &parsed); err != nil {
		return rawMessage
	}
	for _, key := range []string{"stderr", "message", "stdout"} {
		if value, ok := parsed[key].(string); ok && value != "" {
			return value
		}
	}
	return rawMessage
}

func contentOrEmpty(file *CodeFile) string {
	if file == nil {
		return ""
	}
	return file.Content
}
