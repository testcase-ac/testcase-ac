package executionlimits

import "github.com/testcase-ac/testcase-ac/backend/contracts"

type policy struct {
	timeMultiplier   int
	timeAdditionMS   int
	memoryMultiplier int
	memoryAdditionMB int
}

var bojPolicies = map[contracts.Language]policy{
	contracts.LanguagePython3:  {timeMultiplier: 3, timeAdditionMS: 2000, memoryMultiplier: 2, memoryAdditionMB: 32},
	contracts.LanguagePyPy3:    {timeMultiplier: 3, timeAdditionMS: 2000, memoryMultiplier: 2, memoryAdditionMB: 128},
	contracts.LanguageJava:     {timeMultiplier: 2, timeAdditionMS: 1000, memoryMultiplier: 2, memoryAdditionMB: 16},
	contracts.LanguageKotlin:   {timeMultiplier: 2, timeAdditionMS: 1000, memoryMultiplier: 2, memoryAdditionMB: 16},
	contracts.LanguageCSharp:   {timeMultiplier: 2, timeAdditionMS: 1000, memoryMultiplier: 2, memoryAdditionMB: 16},
	contracts.LanguageNodeJS:   {timeMultiplier: 3, timeAdditionMS: 2000, memoryMultiplier: 2, memoryAdditionMB: 0},
	contracts.LanguageGolang:   {timeMultiplier: 1, timeAdditionMS: 2000, memoryMultiplier: 1, memoryAdditionMB: 512},
	contracts.LanguageRust2021: {timeMultiplier: 1, timeAdditionMS: 0, memoryMultiplier: 1, memoryAdditionMB: 16},
}

func Adjusted(problemType string, language contracts.Language, timeLimitMS, memoryLimitMB int) (float64, int) {
	if problemType != "boj" {
		return float64(timeLimitMS) / 1000.0, memoryLimitMB
	}
	policy, ok := bojPolicies[language]
	if !ok {
		return float64(timeLimitMS) / 1000.0, memoryLimitMB
	}
	adjustedTimeMS := timeLimitMS*policy.timeMultiplier + policy.timeAdditionMS
	adjustedMemoryMB := memoryLimitMB*policy.memoryMultiplier + policy.memoryAdditionMB
	return float64(adjustedTimeMS) / 1000.0, adjustedMemoryMB
}
