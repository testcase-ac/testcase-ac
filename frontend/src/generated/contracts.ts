// Code generated from backend/contracts. DO NOT EDIT.

export const ERROR_TYPE_VALUES = [
  "MissingSourceCode",
  "TargetCompilationFailed",
  "GeneratorCompilationFailed",
  "CorrectCompilationFailed",
  "CheckerCompilationFailed",
  "TargetExecutionFailed",
  "GeneratorExecutionFailed",
  "CorrectExecutionFailed",
  "CheckerExecutionFailed",
  "InvalidOperation",
  "InvalidLanguage",
  "InternalServerError",
] as const;

export type ErrorType = (typeof ERROR_TYPE_VALUES)[number];

export const LANGUAGE_VALUES = [
  "cpp23",
  "cpp20",
  "cpp17",
  "cpp14",
  "c11",
  "c99",
  "python3",
  "java",
  "nodejs",
  "pypy3",
  "golang",
  "kotlin",
  "rust2021",
  "csharp",
] as const;

export type Language = (typeof LANGUAGE_VALUES)[number];

export const OPERATION_VALUES = [
  "stress",
] as const;

export type Operation = (typeof OPERATION_VALUES)[number];

export const CASE_PROVIDER_TYPE_VALUES = [
  "text",
  "generator",
  "singlegen",
] as const;

export type CaseProviderType = (typeof CASE_PROVIDER_TYPE_VALUES)[number];

export const VERDICT_VALUES = [
  "AC",
  "WA",
  "RTE",
  "TLE",
  "MLE",
  "OLE",
  "InternalError",
] as const;

export type Verdict = (typeof VERDICT_VALUES)[number];

export const TRUNCATION_KIND_VALUES = [
  "character",
  "line",
] as const;

export type TruncationKind = (typeof TRUNCATION_KIND_VALUES)[number];

export const STRESS_STATUS_VALUES = [
  "found",
  "not_found",
  "compile_error",
  "runtime_error",
  "invalid_problem",
  "rate_limited",
  "internal_error",
] as const;

export type StressStatus = (typeof STRESS_STATUS_VALUES)[number];

export interface CaseProvider {
  type: CaseProviderType;
  id: string;
  content?: string;
  code?: string;
  language?: Language;
}

export interface StressEvent {
  operation: Operation;
  requestId?: string;
  targetCode: string;
  targetCodeLang: Language;
  correctCode: string;
  correctCodeLang: Language;
  checkerCode?: string;
  targetTimeLimit: number;
  targetMemoryLimit: number;
  correctTimeLimit: number;
  correctMemoryLimit: number;
  iterations: number;
  caseProviders: CaseProvider[];
}

export interface OutputTextMetadata {
  characterCount: number;
  lineCount: number;
  truncated: boolean;
  truncatedBy?: TruncationKind | null;
  truncatedAtCharacter?: number | null;
  truncatedAtLine?: number | null;
}

export interface TextWithMetadata {
  text: string;
  metadata: OutputTextMetadata;
}

export interface GeneratedBy {
  stage: CaseProviderType;
  id: string;
  seed?: string | null;
}

export interface Counterexample {
  testcase: TextWithMetadata;
  generatedBy: GeneratedBy;
  targetOutput: TextWithMetadata;
  correctOutput: TextWithMetadata;
  checkerOutput?: TextWithMetadata | null;
  verdict?: Verdict | null;
  stderr?: TextWithMetadata | null;
}

export interface ExecutionFailedCase {
  testcase: TextWithMetadata;
  generatedBy: GeneratedBy;
  correctOutput: TextWithMetadata;
  reason: Verdict;
  stderr?: TextWithMetadata | null;
  timeSeconds: number;
}

export interface CorrectCase {
  generatedBy: GeneratedBy;
}

export interface EventRecord {
  id: number;
  type: string;
  value: string;
  elapsedSeconds: number;
}

export interface StressResult {
  requestId?: string;
  runtimeSeconds: number;
  error: boolean;
  errorType?: ErrorType;
  message?: string;
  wrongCases?: Counterexample[];
  executionFailedCases?: ExecutionFailedCase[];
  correctCases?: CorrectCase[];
  totalCases?: number;
  wrongCasesCount?: number;
  executionFailedCasesCount?: number;
  correctCasesCount?: number;
  events?: EventRecord[];
}

