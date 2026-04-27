import {
  LANGUAGE_VALUES,
  type Counterexample,
  type ExecutionFailedCase,
  type GeneratedBy,
  type Language,
  type StressStatus,
} from "./generated/contracts";

export type {
  CaseProvider,
  CaseProviderType,
  Counterexample,
  CorrectCase,
  ErrorType,
  EventRecord,
  ExecutionFailedCase,
  GeneratedBy,
  Language,
  Operation,
  OutputTextMetadata,
  StressResult,
  StressStatus,
  TextWithMetadata,
  TruncationKind,
  Verdict,
} from "./generated/contracts";

export {
  CASE_PROVIDER_TYPE_VALUES,
  ERROR_TYPE_VALUES,
  LANGUAGE_VALUES,
  OPERATION_VALUES,
  STRESS_STATUS_VALUES,
  TRUNCATION_KIND_VALUES,
  VERDICT_VALUES,
} from "./generated/contracts";

export type LanguageValue = Language;
export type AttemptedCase = GeneratedBy;

// Backend API response shapes that are not yet generated from backend/api.

export interface CodeInfo {
  filename: string;
  language: LanguageValue;
  authorName?: string | null;
}

export interface TestcaseInfo {
  filename: string;
  authorName?: string | null;
}

export interface ProblemSummary {
  problemType: string;
  externalId: string;
  title: string | null;
}

export interface ProblemTypeSummary {
  problemType: string;
  label: string | null;
  total: number;
}

export interface TypeMetadataSegmentLabel {
  value: string;
  label: string;
}

export interface TypeMetadataSegment {
  label?: string;
  labels?: TypeMetadataSegmentLabel[];
}

export interface TypeMetadata {
  label?: string;
  segments?: TypeMetadataSegment[];
}

export interface ProblemList {
  problems: ProblemSummary[];
  problemTypes: ProblemTypeSummary[];
  nextCursor: string | null;
  total: number;
  typeMetadata?: TypeMetadata;
}

export interface ProblemDetail {
  problemType: string;
  externalId: string;
  title: string | null;
  externalLink: string | null;
  timeLimitMs: number;
  memoryLimitMb: number;
  description: string | null;
  isSpecialJudge: boolean;
  correctCodes: CodeInfo[];
  generators: CodeInfo[];
  singlegens: CodeInfo[];
  validator: CodeInfo | null;
  checker: CodeInfo | null;
  testcases: TestcaseInfo[];
}

export interface HealthResponse {
  status: string;
  problemsLoaded: number;
}

export interface StressResponse {
  requestId: string;
  runtimeSeconds: number;
  status: StressStatus;
  wrongCases?: Counterexample[];
  executionFailedCases?: ExecutionFailedCase[];
  counterexamples?: Counterexample[];
  counterexample?: Counterexample | null;
  errorMessage?: string | null;
  attemptedCases?: AttemptedCase[];
  totalCases?: number;
  totalAttempted?: number;
  wrongCasesCount?: number;
  executionFailedCasesCount?: number;
  correctCasesCount?: number;
}

export interface InlineCodeInput {
  id: string;
  code: string;
  language: LanguageValue;
}

export interface InlineTextcaseInput {
  id: string;
  content: string;
}

export const ITERATIONS_MIN = 1;
export const ITERATIONS_MAX = 500;
export const ITERATIONS_DEFAULT = 100;
export const TIME_LIMIT_MIN_MS = 1;
export const TIME_LIMIT_MAX_MS = 10000;
export const TIME_LIMIT_DEFAULT_MS = 2000;
export const MEMORY_LIMIT_MIN_MB = 1;
export const MEMORY_LIMIT_MAX_MB = 1024;
export const MEMORY_LIMIT_DEFAULT_MB = 512;

export interface StressRequest {
  targetCode: string;
  targetCodeLang: LanguageValue;
  timeLimitMs?: number;
  memoryLimitMb?: number;
  correctCodeFilename?: string;
  correctCode?: string;
  correctCodeLang?: LanguageValue;
  checkerCode?: string;
  generatorFilenames?: string[];
  generatorSources?: InlineCodeInput[];
  singlegenFilenames?: string[];
  testcaseFilenames?: string[];
  textTestcases?: InlineTextcaseInput[];
  iterations?: number;
}

const LANGUAGE_LABELS = {
  cpp23: "C++23",
  cpp20: "C++20",
  cpp17: "C++17",
  cpp14: "C++14",
  c11: "C11",
  c99: "C99",
  python3: "Python 3",
  java: "Java",
  nodejs: "Node.js",
  pypy3: "PyPy 3",
  golang: "Go",
  kotlin: "Kotlin",
  rust2021: "Rust 2021",
  csharp: "C#",
} satisfies Record<LanguageValue, string>;

export const LANGUAGES = LANGUAGE_VALUES.map((value) => ({
  value,
  label: LANGUAGE_LABELS[value],
}));

export const CPP_LANGUAGE_VALUES = ["cpp23", "cpp20", "cpp17", "cpp14"] as const satisfies readonly LanguageValue[];
export type CppLanguageValue = (typeof CPP_LANGUAGE_VALUES)[number];

const languageValues = new Set<string>(LANGUAGE_VALUES);
const cppLanguageValues = new Set<string>(CPP_LANGUAGE_VALUES);

export function isLanguageValue(value: string): value is LanguageValue {
  return languageValues.has(value);
}

export function isCppLanguageValue(value: string): value is CppLanguageValue {
  return cppLanguageValues.has(value);
}
