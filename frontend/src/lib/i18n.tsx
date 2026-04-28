import {
  createContext,
  useCallback,
  useContext,
  useEffect,
  useMemo,
  type ReactNode,
} from "react";

import { usePersistentSettings, type Locale } from "./persistentSettings";

export type { Locale } from "./persistentSettings";

type TemplateValues = Record<string, string | number>;

interface I18nContextValue {
  locale: Locale;
  setLocale: (locale: Locale) => void;
  t: (key: TranslationKey, values?: TemplateValues) => string;
}

const I18nContext = createContext<I18nContextValue | null>(null);

const translations = {
  en: {
    "app.title": "testcase.ac",
    "app.footer.openSource": "Open source on",
    "app.footer.github": "GitHub",
    "errorBoundary.title": "Something went wrong",
    "errorBoundary.subtitle": "Full error log",
    "errorBoundary.home": "Back to home",
    "theme.toggle.toDark": "Switch to dark theme",
    "theme.toggle.toLight": "Switch to light theme",
    "language.toggle.label": "Language",
    "language.option.en": "English",
    "language.option.ko": "한국어",
    "home.title": "Problems",
    "home.subtitle":
      "Paste a wrong solution for a saved problem and find an input where it differs from the reference.",
    "home.example.boj1000": "Try Sample Problem: A+B",
    "home.custom.title": "Test without a saved problem",
    "home.custom.subtitle":
      "Paste your own reference solution, inputs, and limits.",
    "home.custom.link": "Custom Invocation",
    "home.problemTypes": "Problem Types",
    "home.problemType.count": "{count} problems ({runnable} runnable)",
    "home.search.placeholder": "Search by id, type, or title",
    "home.state.loading": "Loading...",
    "home.state.empty": "No problems match.",
    "home.untitled": "(untitled)",
    "home.runnable.yes": "Runnable",
    "home.runnable.no": "Not Runnable",
    "catalog.categories": "Categories",
    "catalog.problems": "Problems ({count})",
    "pagination.page": "Page {page}",
    "pagination.shown": "{count} of {total} shown",
    "pagination.previous": "Previous",
    "pagination.next": "Next",
    "problem.loadFailed": "Failed to load problem: {message}",
    "problem.back.button": "Back",
    "problem.externalLink": "Original Problem",
    "problem.viewOnGitHub": "view code on GitHub",
    "problem.time": "time {ms} ms",
    "problem.memory": "memory {mb} MB",
    "problem.trySolution": "Submit Code",
    "problem.language": "Language",
    "problem.languageAutodetect": "Use language autodetection",
    "problem.loading": "Loading...",
    "problem.submit": "Find counterexample",
    "problem.submitting": "Stressing...",
    "problem.submittingWithElapsed": "Stressing... ({seconds}s)",
    "problem.rateLimited": "Rate limited: {message}",
    "problem.unknownError": "Unknown error",
    "problem.editorFallback": "Loading editor...",
    "problem.materials.correct": "correct × {count}",
    "problem.materials.generators": "generators × {count}",
    "problem.materials.singlegens": "singlegens × {count}",
    "problem.materials.testcases": "testcases × {count}",
    "problem.materials.validator": "validator",
    "problem.materials.validatorEmpty": "validator × 0",
    "problem.materials.checker": "checker",
    "problem.materials.checkerEmpty": "checker × 0",
    "problem.advanced.title": "Stress Test Settings",
    "problem.advanced.show": "Choose reference code and inputs",
    "problem.advanced.hide": "Hide stress test settings",
    "problem.iterations.label": "Iterations",
    "problem.iterations.hint":
      "How many cases to run in total ({min}–{max}). Fixed testcases and single generators always run first.",
    "problem.summary.generators": "{count} generators",
    "problem.summary.singlegens": "{count} singlegens",
    "problem.summary.testcases": "{count} testcases",
    "problem.summary.iterations": "{count} iterations",
    "problem.summary.checker": "checker",
    "problem.summary.validator": "validator",
    "problem.summary.none": "nothing selected",
    "problem.option.correct": "Correct code",
    "problem.providers.generators": "Generators",
    "problem.providers.singlegens": "Single generators",
    "problem.providers.testcases": "Fixed testcases",
    "problem.providers.validator": "Validator",
    "problem.providers.checker": "Checker",
    "problem.providers.none": "Nothing available in this group.",
    "problem.providers.noneSelected":
      "At least one testcase or generator source must be selected.",
    "problem.reference.hint": "Reference only. Not used to judge.",
    "problem.correct.cannotDeselect":
      "At least one correct code must stay selected.",
    "problem.author.unknown": "unknown author",
    "problem.link.view": "View source",
    "custom.title": "Custom invocation",
    "custom.subtitle":
      "Run by directly specifying the target code, reference code, generators, checker, textcases, and execution limits.",
    "custom.limits.title": "Execution limits",
    "custom.limits.subtitle":
      "These limits are applied to both your submission and the reference code for this invocation.",
    "custom.limits.time": "Time limit (ms)",
    "custom.limits.timeHint": "Integer from 1 to {max}. Example: 2000",
    "custom.limits.memory": "Memory limit (MB)",
    "custom.limits.memoryHint": "Integer from 1 to {max}. Example: 512",
    "custom.target.title": "Target submission",
    "custom.target.subtitle": "This is the code you want to stress-test.",
    "custom.correct.title": "Correct code",
    "custom.correct.subtitle": "Paste the reference implementation you want to compare against.",
    "custom.generators.title": "Generators",
    "custom.generators.subtitle":
      "Add seeded generators if you want randomized coverage. Each generator receives the seed as its first command-line argument.",
    "custom.generators.add": "Add generator",
    "custom.generators.empty": "No custom generators added yet.",
    "custom.testcases.title": "Text testcases",
    "custom.testcases.subtitle":
      "Add any number of fixed plaintext testcases. They run before generator iterations.",
    "custom.testcases.add": "Add text testcase",
    "custom.testcases.empty": "No fixed text testcase added yet.",
    "custom.testcases.content": "Input",
    "custom.checker.title": "Checker",
    "custom.checker.subtitle":
      "Optional. Leave it off to use plain output comparison for this invocation.",
    "custom.checker.subtitleSpecialJudge":
      "This problem is marked as special judge. Turn this on and paste a custom checker if you want checker-based judging for this invocation.",
    "custom.checker.use": "Use custom checker",
    "custom.checker.hint":
      "Checker code is compiled as C++23 with testlib available, matching the repo checker path.",
    "custom.run.title": "Run custom invocation",
    "custom.run.submit": "Run custom invocation",
    "custom.material.id": "Identifier",
    "custom.material.remove": "Remove",
    "custom.providers.required":
      "Add at least one generator or text testcase before submitting.",
    "custom.providers.invalid":
      "Every generator needs both an identifier and source code, every testcase needs an identifier, execution limits must be in range, and the checker must not be empty when enabled.",
    "stress.status.found": "Counterexample found",
    "stress.status.not_found": "No counterexample found",
    "stress.status.compile_error": "Your code failed to compile",
    "stress.status.runtime_error": "Your code crashed",
    "stress.status.invalid_problem": "Problem data failed to run",
    "stress.status.rate_limited": "Rate limited",
    "stress.status.internal_error": "Internal error",
    "stress.runtime": "runtime {seconds}s",
    "stress.notFoundDetail":
      "Your code agreed with the reference on every generated input within the time budget. That's a passing result, though it doesn't prove correctness.",
    "stress.label.input": "Input",
    "stress.label.yourOutput": "Your output",
    "stress.label.correctOutput": "Correct output",
    "stress.label.stderr": "stderr",
    "stress.label.failureReason": "Failure reason",
    "stress.verdict.OLE": "Output limit exceeded (OLE)",
    "stress.counterexample.number": "Counterexample {n}",
    "stress.executionFailed.number": "Execution-failed sample {n}",
    "stress.seed": "seed",
    "stress.copy": "Copy",
    "stress.copied": "Copied",
    "stress.truncated.character":
      "Truncated by character at {at} of {characters} characters ({lines} lines total).",
    "stress.truncated.line":
      "Truncated by line at {line} of {lines} lines ({characters} characters total).",
    "stress.empty": "(empty)",
    "stress.summary.totalCases": "Total cases run",
    "stress.summary.correctCases": "Matched reference",
    "stress.summary.wrongCases": "Wrong output",
    "stress.summary.executionFailedCases": "Execution failed",
    "stress.samples.note":
      "Shown below: the shortest wrong-output and execution-failed samples returned for this run.",
    "stress.section.wrongCases": "Wrong samples ({total} total)",
    "stress.section.executionFailedCases":
      "Execution-failed samples ({total} total)",
    "stress.attempted.notFound": "Cases tried ({n})",
    "stress.attempted.found": "Other matched cases tried ({n})",
    "stress.attempted.empty": "No cases recorded.",
    "stress.attempted.unavailable":
      "Detailed matched-case history was not returned for this run.",
  },
  ko: {
    "app.title": "testcase.ac",
    "app.footer.openSource": "오픈소스",
    "app.footer.github": "GitHub",
    "errorBoundary.title": "문제가 발생했습니다",
    "errorBoundary.subtitle": "전체 오류 로그",
    "errorBoundary.home": "홈으로 돌아가기",
    "theme.toggle.toDark": "다크 테마로 전환",
    "theme.toggle.toLight": "라이트 테마로 전환",
    "language.toggle.label": "언어",
    "language.option.en": "English",
    "language.option.ko": "한국어",
    "home.title": "문제 목록",
    "home.subtitle":
      "등록된 문제에 대해 오답 코드를 붙여넣어 정답 풀이와 출력이 다른 입력을 찾아보세요.",
    "home.example.boj1000": "예시 문제로 테스트하기: A+B",
    "home.custom.title": "저장된 문제 없이 테스트하기",
    "home.custom.subtitle":
      "정답 코드, 입력, 실행 제한을 직접 넣어 실행합니다.",
    "home.custom.link": "커스텀 실행",
    "home.problemTypes": "문제 유형",
    "home.problemType.count": "문제 {count}개 ({runnable}개 실행 가능)",
    "home.search.placeholder": "번호, 유형, 제목으로 검색하세요",
    "home.state.loading": "불러오는 중...",
    "home.state.empty": "일치하는 문제가 없습니다.",
    "home.untitled": "(제목 없음)",
    "home.runnable.yes": "실행 가능",
    "home.runnable.no": "실행 불가",
    "catalog.categories": "분류",
    "catalog.problems": "문제 ({count})",
    "pagination.page": "{page} 페이지",
    "pagination.shown": "총 {total}개 중 {count}개 표시",
    "pagination.previous": "이전",
    "pagination.next": "다음",
    "problem.loadFailed": "문제를 불러오지 못했습니다: {message}",
    "problem.back.button": "뒤로",
    "problem.externalLink": "원본 문제",
    "problem.viewOnGitHub": "GitHub에서 코드 보기",
    "problem.time": "시간 {ms} ms",
    "problem.memory": "메모리 {mb} MB",
    "problem.trySolution": "코드 제출하기",
    "problem.language": "언어",
    "problem.languageAutodetect": "언어 자동 감지 사용",
    "problem.loading": "불러오는 중...",
    "problem.submit": "반례 찾기",
    "problem.submitting": "실행 중...",
    "problem.submittingWithElapsed": "실행 중... ({seconds}초)",
    "problem.rateLimited": "요청이 제한되었습니다: {message}",
    "problem.unknownError": "알 수 없는 오류",
    "problem.editorFallback": "에디터 불러오는 중...",
    "problem.materials.correct": "정답 × {count}",
    "problem.materials.generators": "제너레이터 × {count}",
    "problem.materials.singlegens": "단일 제너레이터 × {count}",
    "problem.materials.testcases": "테스트 케이스 × {count}",
    "problem.materials.validator": "밸리데이터",
    "problem.materials.validatorEmpty": "밸리데이터 × 0",
    "problem.materials.checker": "체커",
    "problem.materials.checkerEmpty": "체커 × 0",
    "problem.advanced.title": "스트레스 테스트 설정",
    "problem.advanced.show": "정답 코드와 입력 선택하기",
    "problem.advanced.hide": "스트레스 테스트 설정 숨기기",
    "problem.iterations.label": "시도 횟수",
    "problem.iterations.hint":
      "총 몇 개의 케이스를 시도할지 정합니다 ({min}–{max}). 고정 테스트케이스와 단일 제너레이터가 항상 먼저 실행됩니다.",
    "problem.summary.generators": "제너레이터 {count}개",
    "problem.summary.singlegens": "단일 제너레이터 {count}개",
    "problem.summary.testcases": "고정 테스트케이스 {count}개",
    "problem.summary.iterations": "{count}회 시도",
    "problem.summary.checker": "체커",
    "problem.summary.validator": "밸리데이터",
    "problem.summary.none": "선택된 항목 없음",
    "problem.option.correct": "정답 코드",
    "problem.providers.generators": "제너레이터",
    "problem.providers.singlegens": "단일 제너레이터",
    "problem.providers.testcases": "고정 테스트케이스",
    "problem.providers.validator": "밸리데이터",
    "problem.providers.checker": "체커",
    "problem.providers.none": "이 그룹에는 선택 가능한 항목이 없습니다.",
    "problem.providers.noneSelected":
      "테스트케이스 또는 제너레이터 계열 입력은 최소 하나가 선택되어 있어야 합니다.",
    "problem.reference.hint": "참고용입니다. 채점에는 사용되지 않습니다.",
    "problem.correct.cannotDeselect":
      "정답 코드는 최소 하나가 선택되어 있어야 합니다.",
    "problem.author.unknown": "작성자 미상",
    "problem.link.view": "소스 보기",
    "custom.title": "커스텀 실행",
    "custom.subtitle":
      "제출 코드, 정답 코드, 제너레이터, 체커, 텍스트 테스트케이스, 실행 제한을 모두 직접 지정해 실행합니다.",
    "custom.limits.title": "실행 제한",
    "custom.limits.subtitle":
      "이번 실행에서는 제출 코드와 정답 코드 모두 이 시간/메모리 제한을 사용합니다.",
    "custom.limits.time": "시간 제한 (ms)",
    "custom.limits.timeHint": "1부터 {max}까지의 정수를 입력하세요. 예: 2000",
    "custom.limits.memory": "메모리 제한 (MB)",
    "custom.limits.memoryHint": "1부터 {max}까지의 정수를 입력하세요. 예: 512",
    "custom.target.title": "제출 코드",
    "custom.target.subtitle": "스트레스 테스트할 대상 코드입니다.",
    "custom.correct.title": "정답 코드",
    "custom.correct.subtitle": "비교 기준이 될 정답 구현을 붙여넣으세요.",
    "custom.generators.title": "제너레이터",
    "custom.generators.subtitle":
      "랜덤 테스트를 원하면 시드 기반 제너레이터를 추가하세요. 각 제너레이터는 첫 번째 명령줄 인자로 시드를 받습니다.",
    "custom.generators.add": "제너레이터 추가",
    "custom.generators.empty": "추가된 커스텀 제너레이터가 없습니다.",
    "custom.testcases.title": "텍스트 테스트케이스",
    "custom.testcases.subtitle":
      "고정 입력을 원하는 만큼 추가할 수 있습니다. 제너레이터 반복보다 먼저 실행됩니다.",
    "custom.testcases.add": "텍스트 테스트케이스 추가",
    "custom.testcases.empty": "추가된 고정 텍스트 테스트케이스가 없습니다.",
    "custom.testcases.content": "입력",
    "custom.checker.title": "체커",
    "custom.checker.subtitle":
      "선택 사항입니다. 끄면 이번 실행에서는 일반 출력 비교를 사용합니다.",
    "custom.checker.subtitleSpecialJudge":
      "이 문제는 스페셜 저지 문제입니다. 이번 실행에서도 체커 판정을 쓰고 싶다면 켜고 커스텀 체커를 붙여넣으세요.",
    "custom.checker.use": "커스텀 체커 사용",
    "custom.checker.hint":
      "체커 코드는 저장소의 checker 경로와 동일하게 testlib가 포함된 C++23으로 컴파일됩니다.",
    "custom.run.title": "커스텀 실행하기",
    "custom.run.submit": "커스텀 실행",
    "custom.material.id": "식별자",
    "custom.material.remove": "삭제",
    "custom.providers.required":
      "제출 전에 제너레이터나 텍스트 테스트케이스를 최소 하나 추가하세요.",
    "custom.providers.invalid":
      "모든 제너레이터에는 식별자와 소스 코드가 필요하고, 모든 테스트케이스에는 식별자가 필요하며, 실행 제한은 허용 범위 안이어야 하고, 체커를 켠 경우 비워둘 수 없습니다.",
    "stress.status.found": "반례를 찾았습니다",
    "stress.status.not_found": "반례를 찾지 못했습니다",
    "stress.status.compile_error": "컴파일에 실패했습니다",
    "stress.status.runtime_error": "실행 중 오류가 발생했습니다",
    "stress.status.invalid_problem": "문제 데이터 실행에 실패했습니다",
    "stress.status.rate_limited": "요청이 제한되었습니다",
    "stress.status.internal_error": "내부 오류",
    "stress.runtime": "실행 시간 {seconds}초",
    "stress.notFoundDetail":
      "주어진 시간 안에 생성된 모든 입력에서 정답 풀이와 출력이 일치했습니다. 통과이지만 정확성을 증명하지는 않습니다.",
    "stress.label.input": "입력",
    "stress.label.yourOutput": "내 출력",
    "stress.label.correctOutput": "정답 출력",
    "stress.label.stderr": "stderr",
    "stress.label.failureReason": "실패 이유",
    "stress.verdict.OLE": "출력 초과 (OLE)",
    "stress.counterexample.number": "반례 {n}",
    "stress.executionFailed.number": "실행 실패 예시 {n}",
    "stress.seed": "시드",
    "stress.copy": "복사",
    "stress.copied": "복사됨",
    "stress.truncated.character":
      "전체 {characters}자, {lines}줄 중 {at}자에서 잘렸습니다.",
    "stress.truncated.line":
      "전체 {lines}줄, {characters}자 중 {line}줄에서 잘렸습니다.",
    "stress.empty": "(비어 있음)",
    "stress.summary.totalCases": "총 실행 케이스 수",
    "stress.summary.correctCases": "정답과 일치",
    "stress.summary.wrongCases": "오답 출력",
    "stress.summary.executionFailedCases": "실행 실패",
    "stress.samples.note":
      "아래에는 이번 실행에서 반환된 가장 짧은 오답/실행 실패 예시만 보여줍니다.",
    "stress.section.wrongCases": "오답 예시 (총 {total}개)",
    "stress.section.executionFailedCases":
      "실행 실패 예시 (총 {total}개)",
    "stress.attempted.notFound": "시도한 케이스들 ({n}개)",
    "stress.attempted.found": "기타 정답과 일치한 케이스들 ({n}개)",
    "stress.attempted.empty": "기록된 케이스가 없습니다.",
    "stress.attempted.unavailable":
      "이번 실행에서는 정답 일치 케이스의 상세 목록이 반환되지 않았습니다.",
  },
} as const;

export type TranslationKey = keyof (typeof translations)["en"];

function interpolate(template: string, values?: TemplateValues): string {
  if (!values) return template;
  return template.replace(/\{(\w+)\}/g, (_, key: string) => {
    const v = values[key];
    return v === undefined || v === null ? `{${key}}` : String(v);
  });
}

export function I18nProvider({ children }: { children: ReactNode }) {
  const { locale, setLocale } = usePersistentSettings();

  useEffect(() => {
    if (typeof document !== "undefined") {
      document.documentElement.lang = locale;
    }
  }, [locale]);

  const t = useCallback(
    (key: TranslationKey, values?: TemplateValues) => {
      const dict = translations[locale];
      const fallback = translations.en;
      const template = dict[key] ?? fallback[key] ?? key;
      return interpolate(template, values);
    },
    [locale],
  );

  const value = useMemo<I18nContextValue>(
    () => ({ locale, setLocale, t }),
    [locale, setLocale, t],
  );

  return <I18nContext.Provider value={value}>{children}</I18nContext.Provider>;
}

export function useI18n(): I18nContextValue {
  const ctx = useContext(I18nContext);
  if (!ctx) throw new Error("useI18n must be used inside I18nProvider");
  return ctx;
}
