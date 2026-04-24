package contracts

type ErrorType string

const (
	ErrorTypeMissingSourceCode          ErrorType = "MissingSourceCode"
	ErrorTypeTargetCompilationFailed    ErrorType = "TargetCompilationFailed"
	ErrorTypeGeneratorCompilationFailed ErrorType = "GeneratorCompilationFailed"
	ErrorTypeCorrectCompilationFailed   ErrorType = "CorrectCompilationFailed"
	ErrorTypeCheckerCompilationFailed   ErrorType = "CheckerCompilationFailed"
	ErrorTypeTargetExecutionFailed      ErrorType = "TargetExecutionFailed"
	ErrorTypeGeneratorExecutionFailed   ErrorType = "GeneratorExecutionFailed"
	ErrorTypeCorrectExecutionFailed     ErrorType = "CorrectExecutionFailed"
	ErrorTypeCheckerExecutionFailed     ErrorType = "CheckerExecutionFailed"
	ErrorTypeInvalidOperation           ErrorType = "InvalidOperation"
	ErrorTypeInvalidLanguage            ErrorType = "InvalidLanguage"
	ErrorTypeInternalServerError        ErrorType = "InternalServerError"
)

type Language string

const (
	LanguageCpp23    Language = "cpp23"
	LanguageCpp20    Language = "cpp20"
	LanguageCpp17    Language = "cpp17"
	LanguageCpp14    Language = "cpp14"
	LanguageC11      Language = "c11"
	LanguageC99      Language = "c99"
	LanguagePython3  Language = "python3"
	LanguageJava     Language = "java"
	LanguageNodeJS   Language = "nodejs"
	LanguagePyPy3    Language = "pypy3"
	LanguageGolang   Language = "golang"
	LanguageKotlin   Language = "kotlin"
	LanguageRust2021 Language = "rust2021"
	LanguageCSharp   Language = "csharp"
)

var SupportedLanguageList = []Language{
	LanguageCpp23,
	LanguageCpp20,
	LanguageCpp17,
	LanguageCpp14,
	LanguageC11,
	LanguageC99,
	LanguagePython3,
	LanguageJava,
	LanguageNodeJS,
	LanguagePyPy3,
	LanguageGolang,
	LanguageKotlin,
	LanguageRust2021,
	LanguageCSharp,
}

var SupportedLanguages = supportedLanguageSet(SupportedLanguageList)

func IsSupportedLanguage(value Language) bool {
	_, ok := SupportedLanguages[value]
	return ok
}

func supportedLanguageSet(languages []Language) map[Language]struct{} {
	out := make(map[Language]struct{}, len(languages))
	for _, language := range languages {
		out[language] = struct{}{}
	}
	return out
}

type Operation string

const OperationStress Operation = "stress"

type CaseProviderType string

const (
	CaseProviderText      CaseProviderType = "text"
	CaseProviderGenerator CaseProviderType = "generator"
	CaseProviderSinglegen CaseProviderType = "singlegen"
)

type Verdict string

const (
	VerdictAccepted      Verdict = "AC"
	VerdictWrongAnswer   Verdict = "WA"
	VerdictRuntimeError  Verdict = "RTE"
	VerdictTimeLimit     Verdict = "TLE"
	VerdictMemoryLimit   Verdict = "MLE"
	VerdictOutputLimit   Verdict = "OLE"
	VerdictInternalError Verdict = "InternalError"
)

type TruncationKind string

const (
	TruncationKindCharacter TruncationKind = "character"
	TruncationKindLine      TruncationKind = "line"
)

type StressStatus string

const (
	StressStatusFound          StressStatus = "found"
	StressStatusNotFound       StressStatus = "not_found"
	StressStatusCompileError   StressStatus = "compile_error"
	StressStatusRuntimeError   StressStatus = "runtime_error"
	StressStatusInvalidProblem StressStatus = "invalid_problem"
	StressStatusRateLimited    StressStatus = "rate_limited"
	StressStatusInternalError  StressStatus = "internal_error"
)

type CaseProvider struct {
	Type     CaseProviderType `json:"type"`
	ID       string           `json:"id"`
	Content  string           `json:"content,omitempty"`
	Code     string           `json:"code,omitempty"`
	Language Language         `json:"language,omitempty"`
}

type StressEvent struct {
	Operation          Operation      `json:"operation"`
	RequestID          string         `json:"requestId,omitempty"`
	TargetCode         string         `json:"targetCode"`
	TargetCodeLang     Language       `json:"targetCodeLang"`
	CorrectCode        string         `json:"correctCode"`
	CorrectCodeLang    Language       `json:"correctCodeLang"`
	CheckerCode        string         `json:"checkerCode,omitempty"`
	TargetTimeLimit    float64        `json:"targetTimeLimit"`
	TargetMemoryLimit  int            `json:"targetMemoryLimit"`
	CorrectTimeLimit   float64        `json:"correctTimeLimit"`
	CorrectMemoryLimit int            `json:"correctMemoryLimit"`
	Iterations         int            `json:"iterations"`
	CaseProviders      []CaseProvider `json:"caseProviders"`
}

type OutputTextMetadata struct {
	CharacterCount       int             `json:"characterCount"`
	LineCount            int             `json:"lineCount"`
	Truncated            bool            `json:"truncated"`
	TruncatedBy          *TruncationKind `json:"truncatedBy,omitempty"`
	TruncatedAtCharacter *int            `json:"truncatedAtCharacter,omitempty"`
	TruncatedAtLine      *int            `json:"truncatedAtLine,omitempty"`
}

type TextWithMetadata struct {
	Text     string             `json:"text"`
	Metadata OutputTextMetadata `json:"metadata"`
}

type GeneratedBy struct {
	Stage CaseProviderType `json:"stage"`
	ID    string           `json:"id"`
	Seed  *string          `json:"seed,omitempty"`
}

type Counterexample struct {
	Testcase      TextWithMetadata  `json:"testcase"`
	GeneratedBy   GeneratedBy       `json:"generatedBy"`
	TargetOutput  TextWithMetadata  `json:"targetOutput"`
	CorrectOutput TextWithMetadata  `json:"correctOutput"`
	CheckerOutput *TextWithMetadata `json:"checkerOutput,omitempty"`
	Verdict       *Verdict          `json:"verdict,omitempty"`
	Stderr        *TextWithMetadata `json:"stderr,omitempty"`
}

type ExecutionFailedCase struct {
	Testcase      TextWithMetadata  `json:"testcase"`
	GeneratedBy   GeneratedBy       `json:"generatedBy"`
	CorrectOutput TextWithMetadata  `json:"correctOutput"`
	Reason        Verdict           `json:"reason"`
	Stderr        *TextWithMetadata `json:"stderr,omitempty"`
	TimeSeconds   float64           `json:"timeSeconds"`
}

type CorrectCase struct {
	GeneratedBy GeneratedBy `json:"generatedBy"`
}

type EventRecord struct {
	ID             int     `json:"id"`
	Type           string  `json:"type"`
	Value          string  `json:"value"`
	ElapsedSeconds float64 `json:"elapsedSeconds"`
}

type StressResult struct {
	RequestID                 string                `json:"requestId,omitempty"`
	RuntimeSeconds            float64               `json:"runtimeSeconds"`
	Error                     bool                  `json:"error"`
	ErrorType                 ErrorType             `json:"errorType,omitempty"`
	Message                   string                `json:"message,omitempty"`
	WrongCases                []Counterexample      `json:"wrongCases,omitempty"`
	ExecutionFailedCases      []ExecutionFailedCase `json:"executionFailedCases,omitempty"`
	CorrectCases              []CorrectCase         `json:"correctCases,omitempty"`
	TotalCases                int                   `json:"totalCases,omitempty"`
	WrongCasesCount           int                   `json:"wrongCasesCount,omitempty"`
	ExecutionFailedCasesCount int                   `json:"executionFailedCasesCount,omitempty"`
	CorrectCasesCount         int                   `json:"correctCasesCount,omitempty"`
	Events                    []EventRecord         `json:"events,omitempty"`
}
