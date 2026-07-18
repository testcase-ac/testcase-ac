package main

// This file translates API stress requests into stresser events, records
// execution statistics, and maps stresser results back into API responses.

import (
	"context"
	"encoding/json"
	"errors"
	"fmt"
	"log/slog"
	"net/http"
	"slices"
	"strings"
	"time"

	"github.com/testcase-ac/testcase-ac/backend/api/stresser"
	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/executionlimits"
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
	contracts.ErrorTypeCompilationTimedOut:        contracts.StressStatusCompileTimeout,
	contracts.ErrorTypeInternalServerError:        contracts.StressStatusInternalError,
}

const (
	statusClientClosedRequest = 499
	clientClosedRequestDetail = "Client closed request."
)

type caseProviderPlan struct {
	Providers  []contracts.CaseProvider
	Iterations int
}

func buildProblemStressEvent(problem Problem, request StressRequest, requestID string) (contracts.StressEvent, int, string, bool) {
	if problem.OutputOnly && hasOutputOnlyProviderInput(request) {
		return contracts.StressEvent{}, http.StatusBadRequest, "Output-only problems do not accept testcase, generator, or single generator selections", false
	}
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
	providerPlan, statusCode, detail, ok := buildCaseProviderPlan(problem, request)
	if !ok {
		return contracts.StressEvent{}, statusCode, detail, false
	}

	targetLang := request.targetLangValue()
	targetTimeLimitS, targetMemoryLimitMB := executionlimits.Adjusted(problem.ProblemType, targetLang, problem.TimeLimitMS, problem.MemoryLimitMB)
	correctTimeLimitS, correctMemoryLimitMB := executionlimits.Adjusted(problem.ProblemType, referenceLang, problem.TimeLimitMS, problem.MemoryLimitMB)
	return contracts.StressEvent{
		Operation:                contracts.OperationStress,
		RequestID:                requestID,
		TargetCode:               request.TargetCode,
		TargetCodeLang:           targetLang,
		CorrectCode:              referenceCode,
		CorrectCodeLang:          referenceLang,
		CheckerCode:              checkerCode,
		TargetTimeLimit:          targetTimeLimitS,
		TargetMemoryLimit:        targetMemoryLimitMB,
		CorrectTimeLimit:         correctTimeLimitS,
		CorrectMemoryLimit:       correctMemoryLimitMB,
		Iterations:               providerPlan.Iterations,
		TotalRuntimeLimitSeconds: request.totalRuntimeLimitSecondsValue(),
		CaseProviders:            providerPlan.Providers,
	}, 0, "", true
}

func buildCaseProviderPlan(problem Problem, request StressRequest) (caseProviderPlan, int, string, bool) {
	if problem.OutputOnly {
		return caseProviderPlan{
			Providers: []contracts.CaseProvider{{
				Type:    contracts.CaseProviderText,
				ID:      contracts.OutputOnlyEmptyInputID,
				Content: "",
			}},
			Iterations: 1,
		}, 0, "", true
	}

	caseProviders, ok, detail := resolveCaseProviders(problem, request)
	if !ok {
		return caseProviderPlan{}, http.StatusUnprocessableEntity, detail, false
	}
	selectedSinglegens, ok, detail := selectByFilename(problem.Singlegens, request.SinglegenFilenames, "single generators")
	if !ok {
		return caseProviderPlan{}, http.StatusUnprocessableEntity, detail, false
	}

	caseProviders = append(caseProviders, buildSinglegenProviders(selectedSinglegens)...)
	if len(caseProviders) == 0 {
		return caseProviderPlan{}, http.StatusUnprocessableEntity, "At least one testcase, generator, or single generator must be selected", false
	}
	return caseProviderPlan{Providers: caseProviders, Iterations: request.iterationsValue()}, 0, "", true
}

func hasOutputOnlyProviderInput(request StressRequest) bool {
	return len(request.GeneratorFilenames) > 0 ||
		len(request.SinglegenFilenames) > 0 ||
		len(request.TestcaseFilenames) > 0 ||
		len(request.GeneratorSources) > 0 ||
		len(request.TextTestcases) > 0
}

func buildCustomStressEvent(request StressRequest, requestID string) (contracts.StressEvent, int, string, bool) {
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
		Operation:                contracts.OperationStress,
		RequestID:                requestID,
		TargetCode:               request.TargetCode,
		TargetCodeLang:           request.targetLangValue(),
		CorrectCode:              request.CorrectCode,
		CorrectCodeLang:          request.correctLangValue(),
		CheckerCode:              checkerCode,
		TargetTimeLimit:          timeLimitSeconds,
		TargetMemoryLimit:        memoryLimitMB,
		CorrectTimeLimit:         timeLimitSeconds,
		CorrectMemoryLimit:       memoryLimitMB,
		Iterations:               request.iterationsValue(),
		TotalRuntimeLimitSeconds: request.totalRuntimeLimitSecondsValue(),
		CaseProviders:            caseProviders,
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

func runProblemStress(ctx context.Context, problem Problem, request StressRequest, requestID string, client stresser.Client, stats *StatsStore, progress stresser.ProgressCallback) (StressResponse, int, string, bool) {
	event, statusCode, detail, ok := buildProblemStressEvent(problem, request, requestID)
	if !ok {
		return StressResponse{}, statusCode, detail, false
	}
	dispatch := statsDispatchForEvent(problem, event, time.Now().UTC())
	return invokeStressEvent(
		ctx,
		event,
		client,
		stats,
		&dispatch,
		progress,
	)
}

func RunCustomStress(ctx context.Context, request StressRequest, requestID string, client stresser.Client) (StressResponse, int, string, bool) {
	event, statusCode, detail, ok := buildCustomStressEvent(request, requestID)
	if !ok {
		return StressResponse{}, statusCode, detail, false
	}
	return invokeStressEvent(ctx, event, client, nil, nil, nil)
}

func invokeStressEvent(ctx context.Context, event contracts.StressEvent, client stresser.Client, stats *StatsStore, dispatch *StatsDispatch, progress stresser.ProgressCallback) (StressResponse, int, string, bool) {
	logAttrs := []any{
		"request_id", event.RequestID,
		"case_providers", len(event.CaseProviders),
		"iterations", event.Iterations,
		"total_runtime_limit_seconds", event.TotalRuntimeLimitSeconds,
	}
	if dispatch != nil {
		logAttrs = append(logAttrs,
			"problem_type", dispatch.ProblemType,
			"external_id", dispatch.ExternalID,
			"target_language", *dispatch.TargetLanguage,
			"text_provider_count", *dispatch.TextProviderCount,
			"generator_provider_count", *dispatch.GeneratorProviderCount,
			"singlegen_provider_count", *dispatch.SinglegenProviderCount,
			"checker_used", *dispatch.CheckerUsed,
		)
	} else {
		logAttrs = append(logAttrs, "custom_invocation", true)
	}
	slog.Info(
		"stress_dispatch",
		logAttrs...,
	)
	if stats != nil && dispatch != nil {
		statsWrite(func(writeCtx context.Context) error { return stats.RecordDispatch(writeCtx, *dispatch) })
	}
	event.StreamProgress = progress != nil
	stresserResp, err := client.Invoke(ctx, event, progress)
	if err != nil {
		if errors.Is(err, context.Canceled) || errors.Is(ctx.Err(), context.Canceled) {
			slog.Info("stress_request_canceled", "request_id", event.RequestID)
			if dispatch != nil {
				recordStatsTerminal(stats, StatsTerminal{RequestID: event.RequestID, TerminalAt: time.Now().UTC(), Outcome: "canceled"})
			}
			return StressResponse{}, statusClientClosedRequest, clientClosedRequestDetail, false
		}
		if dispatch != nil {
			recordStatsTerminal(stats, StatsTerminal{RequestID: event.RequestID, TerminalAt: time.Now().UTC(), Outcome: "invoke_failed"})
		}
		var invokeErr *stresser.InvokeError
		if ok := errors.As(err, &invokeErr); ok {
			return StressResponse{}, invokeErr.StatusCode, invokeErr.Detail, false
		}
		return StressResponse{}, http.StatusServiceUnavailable, "Stresser is unavailable, try again shortly.", false
	}
	response := transformStresserResponse(stresserResp, event.RequestID)
	status := string(response.Status)
	runtimeSeconds := stresserResp.RuntimeSeconds
	totalCases := stresserResp.TotalCases
	wrongCases := stresserResp.WrongCasesCount
	executionFailedCases := stresserResp.ExecutionFailedCasesCount
	terminal := StatsTerminal{
		RequestID: event.RequestID, TerminalAt: time.Now().UTC(), Outcome: "completed",
		StressStatus: &status, RuntimeSeconds: &runtimeSeconds, TotalCases: &totalCases,
		WrongCases: &wrongCases, ExecutionFailedCases: &executionFailedCases,
	}
	if stresserResp.ErrorType != "" {
		errorType := string(stresserResp.ErrorType)
		terminal.ErrorType = &errorType
	}
	if dispatch != nil {
		recordStatsTerminal(stats, terminal)
	}
	return response, 0, "", true
}

func statsDispatchForEvent(problem Problem, event contracts.StressEvent, at time.Time) StatsDispatch {
	textCount, generatorCount, singlegenCount := 0, 0, 0
	for _, provider := range event.CaseProviders {
		switch provider.Type {
		case contracts.CaseProviderText:
			textCount++
		case contracts.CaseProviderGenerator:
			generatorCount++
		case contracts.CaseProviderSinglegen:
			singlegenCount++
		}
	}
	targetLanguage := string(event.TargetCodeLang)
	iterations := event.Iterations
	checkerUsed := event.CheckerCode != ""
	return StatsDispatch{
		RequestID: event.RequestID, ProblemType: problem.ProblemType, ExternalID: problem.ExternalID,
		DispatchedAt: at, TargetLanguage: &targetLanguage, Iterations: &iterations,
		TextProviderCount: &textCount, GeneratorProviderCount: &generatorCount,
		SinglegenProviderCount: &singlegenCount, CheckerUsed: &checkerUsed,
	}
}

func recordStatsTerminal(stats *StatsStore, terminal StatsTerminal) {
	attrs := []any{"request_id", terminal.RequestID, "outcome", terminal.Outcome}
	if terminal.StressStatus != nil {
		attrs = append(attrs,
			"stress_status", *terminal.StressStatus,
			"runtime_seconds", *terminal.RuntimeSeconds,
			"total_cases", *terminal.TotalCases,
			"wrong_cases", *terminal.WrongCases,
			"execution_failed_cases", *terminal.ExecutionFailedCases,
		)
	}
	if terminal.ErrorType != nil {
		attrs = append(attrs, "error_type", *terminal.ErrorType)
	}
	slog.Info("stress_terminal", attrs...)
	if stats != nil {
		statsWrite(func(writeCtx context.Context) error { return stats.RecordTerminal(writeCtx, terminal) })
	}
}

func statsWrite(write func(context.Context) error) {
	ctx, cancel := context.WithTimeout(context.Background(), 250*time.Millisecond)
	defer cancel()
	if err := write(ctx); err != nil {
		slog.Warn("stats_write_failed", "err", err)
	}
}

func transformStresserResponse(stresserResp contracts.StressResult, requestID string) StressResponse {
	response := StressResponse{
		RequestID:            requestID,
		RuntimeSeconds:       stresserResp.RuntimeSeconds,
		WrongCases:           []Counterexample{},
		ExecutionFailedCases: []ExecutionFailedCase{},
		Counterexamples:      []Counterexample{},
		AttemptedCases:       []AttemptedCase{},
	}

	if stresserResp.Error {
		response.Status = errorTypeToStatus[stresserResp.ErrorType]
		if response.Status == "" {
			response.Status = contracts.StressStatusInternalError
		}
		errText := extractErrorText(stresserResp.Message)
		response.ErrorMessage = &errText
		return response
	}

	response.AttemptedCases = make([]AttemptedCase, 0, len(stresserResp.CorrectCases))
	for _, correctCase := range stresserResp.CorrectCases {
		response.AttemptedCases = append(response.AttemptedCases, correctCase.GeneratedBy)
	}
	response.TotalCases = stresserResp.TotalCases
	response.TotalAttempted = stresserResp.CorrectCasesCount
	response.WrongCasesCount = stresserResp.WrongCasesCount
	response.ExecutionFailedCasesCount = stresserResp.ExecutionFailedCasesCount
	response.CorrectCasesCount = stresserResp.CorrectCasesCount

	if len(stresserResp.WrongCases) > 0 || len(stresserResp.ExecutionFailedCases) > 0 {
		response.Status = contracts.StressStatusFound
		response.WrongCases = slices.Clone(stresserResp.WrongCases)
		response.ExecutionFailedCases = slices.Clone(stresserResp.ExecutionFailedCases)
		response.Counterexamples = slices.Clone(response.WrongCases)
		if len(response.Counterexamples) > 0 {
			response.Counterexample = &response.Counterexamples[0]
		}
		return response
	}

	response.Status = contracts.StressStatusNotFound
	return response
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
