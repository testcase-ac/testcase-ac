package verify

import (
	"encoding/json"
	"fmt"
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
	"github.com/testcase-ac/testcase-ac/backend/internal/loader"
)

const payloadEstimateRequestID = "req_0000000000000000000"

// verifyStressPayloadSize checks that default-selected problem materials can fit
// in the API-to-stresser event after reserving space for a submitted solution.
func verifyStressPayloadSize(report *VerifyReport, problem loader.Problem) {
	if len(problem.CorrectCodes) == 0 {
		return
	}

	correctCode, correctLang := largestCorrectCode(problem.CorrectCodes)
	event := contracts.StressEvent{
		Operation:                contracts.OperationStress,
		RequestID:                payloadEstimateRequestID,
		TargetCode:               strings.Repeat("x", contracts.MaxSubmittedCodeBytes),
		TargetCodeLang:           contracts.LanguageCpp23,
		CorrectCode:              correctCode,
		CorrectCodeLang:          correctLang,
		CheckerCode:              contentOrEmpty(problem.Checker),
		TargetTimeLimit:          float64(problem.TimeLimitMS) / 1000.0,
		TargetMemoryLimit:        problem.MemoryLimitMB,
		CorrectTimeLimit:         float64(problem.TimeLimitMS) / 1000.0,
		CorrectMemoryLimit:       problem.MemoryLimitMB,
		Iterations:               GeneratorRuns,
		TotalRuntimeLimitSeconds: contracts.DefaultTotalRuntimeLimitSeconds,
		CaseProviders:            payloadEstimateProviders(problem),
	}
	// Marshal the same contract the API sends to Lambda so the check tracks
	// JSON escaping, omitempty fields, and future StressEvent shape changes.
	payload, _ := json.Marshal(event)
	if len(payload) <= MaxStressEventPayloadBytes {
		return
	}

	report.AddFinding(
		SeverityError,
		StageStatic,
		"",
		nil,
		fmt.Sprintf(
			"stress event payload estimate exceeds %d bytes: estimated %d bytes with all default-selected providers and %d bytes reserved for submitted code",
			MaxStressEventPayloadBytes,
			len(payload),
			contracts.MaxSubmittedCodeBytes,
		),
		"",
		"",
	)
}

func largestCorrectCode(codes []loader.CodeFile) (string, contracts.Language) {
	var largest loader.CodeFile
	for _, code := range codes {
		if len(code.Content) > len(largest.Content) {
			largest = code
		}
	}
	return largest.Content, largest.Language
}

func contentOrEmpty(file *loader.CodeFile) string {
	if file == nil {
		return ""
	}
	return file.Content
}

func payloadEstimateProviders(problem loader.Problem) []contracts.CaseProvider {
	providers := make([]contracts.CaseProvider, 0, len(problem.Testcases)+len(problem.Generators)+len(problem.Singlegens))
	for _, testcase := range problem.Testcases {
		providers = append(providers, contracts.CaseProvider{
			Type:    contracts.CaseProviderText,
			ID:      testcase.Filename,
			Content: testcase.Content,
		})
	}
	for _, generator := range problem.Generators {
		providers = append(providers, contracts.CaseProvider{
			Type:     contracts.CaseProviderGenerator,
			ID:       generator.Filename,
			Code:     generator.Content,
			Language: generator.Language,
		})
	}
	for _, singlegen := range problem.Singlegens {
		providers = append(providers, contracts.CaseProvider{
			Type:     contracts.CaseProviderSinglegen,
			ID:       singlegen.Filename,
			Code:     singlegen.Content,
			Language: singlegen.Language,
		})
	}
	return providers
}
