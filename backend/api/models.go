package main

import (
	"strings"

	"github.com/testcase-ac/testcase-ac/backend/contracts"
)

var (
	supportedTargetCodeLangDetail  = supportedLanguageDetail("targetCodeLang")
	supportedCorrectCodeLangDetail = supportedLanguageDetail("correctCodeLang")
)

const (
	minCustomTimeLimitMS   = 1
	maxCustomTimeLimitMS   = 10000
	minCustomMemoryLimitMB = 1
	maxCustomMemoryLimitMB = 1024
)

type InlineCodeInput struct {
	ID       string             `json:"id"`
	Code     string             `json:"code"`
	Language contracts.Language `json:"language"`
}

type InlineTextcaseInput struct {
	ID      string `json:"id"`
	Content string `json:"content"`
}

type TextWithMetadata = contracts.TextWithMetadata
type GeneratedBy = contracts.GeneratedBy
type Counterexample = contracts.Counterexample
type ExecutionFailedCase = contracts.ExecutionFailedCase
type AttemptedCase = contracts.GeneratedBy
type StressStatus = contracts.StressStatus

type StressRequest struct {
	TargetCode          string                `json:"targetCode" validate:"required,min=1"`
	TargetCodeLang      contracts.Language    `json:"targetCodeLang" validate:"omitempty,oneof=cpp23 cpp20 cpp17 cpp14 c11 c99 python3 java nodejs pypy3 golang kotlin rust2021 csharp"`
	TimeLimitMS         *int                  `json:"timeLimitMs" validate:"omitempty,min=1,max=10000"`
	MemoryLimitMB       *int                  `json:"memoryLimitMb" validate:"omitempty,min=1,max=1024"`
	CorrectCodeFilename *string               `json:"correctCodeFilename"`
	CorrectCode         string                `json:"correctCode" validate:"omitempty,min=1"`
	CorrectCodeLang     contracts.Language    `json:"correctCodeLang" validate:"omitempty,oneof=cpp23 cpp20 cpp17 cpp14 c11 c99 python3 java nodejs pypy3 golang kotlin rust2021 csharp"`
	CheckerCode         *string               `json:"checkerCode"`
	GeneratorFilenames  []string              `json:"generatorFilenames" validate:"omitempty,dive,min=1"`
	GeneratorSources    []InlineCodeInput     `json:"generatorSources"`
	SinglegenFilenames  []string              `json:"singlegenFilenames" validate:"omitempty,dive,min=1"`
	TestcaseFilenames   []string              `json:"testcaseFilenames" validate:"omitempty,dive,min=1"`
	TextTestcases       []InlineTextcaseInput `json:"textTestcases"`
	Iterations          *int                  `json:"iterations" validate:"omitempty,min=1,max=500"`
}

func (r StressRequest) iterationsValue() int {
	if r.Iterations == nil {
		return 100
	}
	return *r.Iterations
}

func (r StressRequest) targetLangValue() contracts.Language {
	if r.TargetCodeLang == "" {
		return contracts.LanguageCpp23
	}
	return r.TargetCodeLang
}

func (r StressRequest) correctLangValue() contracts.Language {
	if r.CorrectCodeLang == "" {
		return contracts.LanguageCpp23
	}
	return r.CorrectCodeLang
}

func isSupportedLanguage(value contracts.Language) bool {
	return contracts.IsSupportedLanguage(value)
}

func supportedLanguageDetail(fieldName string) string {
	values := make([]string, 0, len(contracts.SupportedLanguageList))
	for _, language := range contracts.SupportedLanguageList {
		values = append(values, string(language))
	}
	return fieldName + " must be one of " + strings.Join(values, ", ")
}

type StressResponse struct {
	RequestID                 string                `json:"requestId"`
	RuntimeSeconds            float64               `json:"runtimeSeconds"`
	Status                    StressStatus          `json:"status"`
	WrongCases                []Counterexample      `json:"wrongCases"`
	ExecutionFailedCases      []ExecutionFailedCase `json:"executionFailedCases"`
	Counterexamples           []Counterexample      `json:"counterexamples"`
	Counterexample            *Counterexample       `json:"counterexample"`
	ErrorMessage              *string               `json:"errorMessage"`
	AttemptedCases            []AttemptedCase       `json:"attemptedCases"`
	TotalCases                int                   `json:"totalCases"`
	TotalAttempted            int                   `json:"totalAttempted"`
	WrongCasesCount           int                   `json:"wrongCasesCount"`
	ExecutionFailedCasesCount int                   `json:"executionFailedCasesCount"`
	CorrectCasesCount         int                   `json:"correctCasesCount"`
}

type CodeInfo struct {
	Filename   string             `json:"filename"`
	Language   contracts.Language `json:"language"`
	AuthorName *string            `json:"authorName"`
}

type TestcaseInfo struct {
	Filename   string  `json:"filename"`
	AuthorName *string `json:"authorName"`
}

type ProblemSummary struct {
	ProblemType string  `json:"problemType"`
	ExternalID  string  `json:"externalId"`
	Title       *string `json:"title"`
}

type ProblemList struct {
	Problems   []ProblemSummary `json:"problems"`
	NextCursor *string          `json:"nextCursor"`
	Total      int              `json:"total"`
}

type ProblemDetail struct {
	ProblemType    string         `json:"problemType"`
	ExternalID     string         `json:"externalId"`
	Title          *string        `json:"title"`
	ExternalLink   *string        `json:"externalLink"`
	TimeLimitMS    int            `json:"timeLimitMs"`
	MemoryLimitMB  int            `json:"memoryLimitMb"`
	Description    *string        `json:"description"`
	IsSpecialJudge bool           `json:"isSpecialJudge"`
	CorrectCodes   []CodeInfo     `json:"correctCodes"`
	Generators     []CodeInfo     `json:"generators"`
	Singlegens     []CodeInfo     `json:"singlegens"`
	Validator      *CodeInfo      `json:"validator"`
	Checker        *CodeInfo      `json:"checker"`
	Testcases      []TestcaseInfo `json:"testcases"`
}

type HealthResponse struct {
	Status         string `json:"status"`
	ProblemsLoaded int    `json:"problemsLoaded"`
}

type errorResponse struct {
	Detail string `json:"detail"`
}
