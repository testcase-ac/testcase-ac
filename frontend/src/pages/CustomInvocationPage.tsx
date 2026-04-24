import { useMutation } from "@tanstack/react-query";
import { Plus, Trash2 } from "lucide-react";
import { useEffect, useState, type FormEvent } from "react";

import { ApiError, submitCustomStress } from "../api";
import CodeEditor from "../components/CodeEditor";
import StressResultView from "../components/StressResult";
import { Button } from "@/components/ui/button";
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card";
import { Input } from "@/components/ui/input";
import { Switch } from "@/components/ui/switch";
import { useI18n, type TranslationKey } from "../lib/i18n";
import { usePersistentSettings } from "../lib/persistentSettings";
import { defaultSource } from "../lib/sourceTemplates";
import { cn } from "../lib/utils";
import type { LanguageValue, StressRequest } from "../types";
import {
  isCppLanguageValue,
  ITERATIONS_DEFAULT,
  ITERATIONS_MAX,
  ITERATIONS_MIN,
  LANGUAGES,
  MEMORY_LIMIT_DEFAULT_MB,
  MEMORY_LIMIT_MAX_MB,
  MEMORY_LIMIT_MIN_MB,
  TIME_LIMIT_DEFAULT_MS,
  TIME_LIMIT_MAX_MS,
  TIME_LIMIT_MIN_MS,
} from "../types";

type GeneratorDraft = {
  id: string;
  language: LanguageValue;
  code: string;
};

type TextcaseDraft = {
  id: string;
  content: string;
};

function clampIterations(value: number): number {
  if (!Number.isFinite(value)) return ITERATIONS_DEFAULT;
  return Math.min(ITERATIONS_MAX, Math.max(ITERATIONS_MIN, Math.floor(value)));
}

function clampIntegerRange(value: number, fallback: number, min: number, max: number): number {
  if (!Number.isFinite(value)) return fallback;
  return Math.min(max, Math.max(min, Math.floor(value)));
}

export default function CustomInvocationPage() {
  const { t } = useI18n();
  const { lastManualLanguage, setLastManualLanguage, setLastManualCppLanguage } =
    usePersistentSettings();

  const [targetLanguage, setTargetLanguage] = useState<LanguageValue>(lastManualLanguage);
  const [targetSource, setTargetSource] = useState(() => defaultSource(lastManualLanguage));
  const [correctLanguage, setCorrectLanguage] = useState<LanguageValue>(lastManualLanguage);
  const [correctSource, setCorrectSource] = useState(() => defaultSource(lastManualLanguage));
  const [timeLimitMs, setTimeLimitMs] = useState(TIME_LIMIT_DEFAULT_MS);
  const [memoryLimitMb, setMemoryLimitMb] = useState(MEMORY_LIMIT_DEFAULT_MB);
  const [generators, setGenerators] = useState<GeneratorDraft[]>([]);
  const [textcases, setTextcases] = useState<TextcaseDraft[]>([]);
  const [useChecker, setUseChecker] = useState(false);
  const [checkerSource, setCheckerSource] = useState("");
  const [iterations, setIterations] = useState(ITERATIONS_DEFAULT);
  const [lastSubmittedRequest, setLastSubmittedRequest] = useState<string | null>(null);
  const [submitElapsedSeconds, setSubmitElapsedSeconds] = useState(0);
  const [nextGeneratorIndex, setNextGeneratorIndex] = useState(1);
  const [nextTextcaseIndex, setNextTextcaseIndex] = useState(1);

  const stressMutation = useMutation({
    mutationFn: (payload: StressRequest) => submitCustomStress(payload),
  });

  useEffect(() => {
    if (!stressMutation.isPending) {
      setSubmitElapsedSeconds(0);
      return;
    }
    const startedAt = Date.now();
    setSubmitElapsedSeconds(0);
    const timer = window.setInterval(() => {
      setSubmitElapsedSeconds(Math.floor((Date.now() - startedAt) / 1000));
    }, 1000);
    return () => window.clearInterval(timer);
  }, [stressMutation.isPending]);

  function handleLanguageChange(next: LanguageValue, setLanguage: (value: LanguageValue) => void) {
    setLastManualLanguage(next);
    if (isCppLanguageValue(next)) {
      setLastManualCppLanguage(next);
    }
    setLanguage(next);
  }

  function addGenerator() {
    const language = lastManualLanguage;
    setGenerators((current) => [
      ...current,
      {
        id: `generator_${nextGeneratorIndex}`,
        language,
        code: defaultSource(language),
      },
    ]);
    setNextGeneratorIndex((current) => current + 1);
  }

  function addTextcase() {
    setTextcases((current) => [
      ...current,
      {
        id: `testcase_${nextTextcaseIndex}.txt`,
        content: "",
      },
    ]);
    setNextTextcaseIndex((current) => current + 1);
  }

  function updateGenerator(index: number, patch: Partial<GeneratorDraft>) {
    setGenerators((current) =>
      current.map((generator, currentIndex) =>
        currentIndex === index ? { ...generator, ...patch } : generator,
      ),
    );
  }

  function updateTextcase(index: number, patch: Partial<TextcaseDraft>) {
    setTextcases((current) =>
      current.map((testcase, currentIndex) =>
        currentIndex === index ? { ...testcase, ...patch } : testcase,
      ),
    );
  }

  function removeGenerator(index: number) {
    setGenerators((current) => current.filter((_, currentIndex) => currentIndex !== index));
  }

  function removeTextcase(index: number) {
    setTextcases((current) => current.filter((_, currentIndex) => currentIndex !== index));
  }

  const providerCount = generators.length + textcases.length;
  const hasInvalidGenerators = generators.some(
    (generator) => !generator.id.trim() || !generator.code.trim(),
  );
  const hasInvalidTextcases = textcases.some((testcase) => !testcase.id.trim());
  const hasInvalidLimits =
    timeLimitMs < TIME_LIMIT_MIN_MS ||
    timeLimitMs > TIME_LIMIT_MAX_MS ||
    memoryLimitMb < MEMORY_LIMIT_MIN_MB ||
    memoryLimitMb > MEMORY_LIMIT_MAX_MB;
  const payload = buildCustomStressRequest({
    targetSource,
    targetLanguage,
    correctSource,
    correctLanguage,
    timeLimitMs,
    memoryLimitMb,
    generators,
    textcases,
    useChecker,
    checkerSource,
    iterations,
  });
  const currentRequest = JSON.stringify(payload);
  const showLatestResponse = currentRequest === lastSubmittedRequest;
  const submitError = showLatestResponse ? formatSubmitError(stressMutation.error, t) : null;
  const result = showLatestResponse ? stressMutation.data ?? null : null;
  const submitDisabled =
    !targetSource.trim() ||
    !correctSource.trim() ||
    providerCount === 0 ||
    hasInvalidGenerators ||
    hasInvalidTextcases ||
    hasInvalidLimits ||
    (useChecker && !checkerSource.trim()) ||
    stressMutation.isPending;

  function onSubmit(event: FormEvent) {
    event.preventDefault();
    stressMutation.reset();
    setLastSubmittedRequest(currentRequest);
    stressMutation.mutate(payload);
  }

  return (
    <section className="space-y-6">
      <header className="space-y-2">
        <h1 className="text-3xl font-semibold">{t("custom.title")}</h1>
        <p className="max-w-4xl text-muted-foreground">{t("custom.subtitle")}</p>
      </header>

      <Card>
        <CardHeader>
          <CardTitle className="text-lg">{t("custom.limits.title")}</CardTitle>
          <CardDescription>{t("custom.limits.subtitle")}</CardDescription>
        </CardHeader>
        <CardContent className="flex flex-wrap gap-x-12 gap-y-5">
          <NumberField
            id="custom-time-limit"
            label={t("custom.limits.time")}
            hint={t("custom.limits.timeHint", { max: TIME_LIMIT_MAX_MS })}
            value={timeLimitMs}
            onChange={setTimeLimitMs}
            onBlur={() =>
              setTimeLimitMs((current) =>
                clampIntegerRange(current, TIME_LIMIT_DEFAULT_MS, TIME_LIMIT_MIN_MS, TIME_LIMIT_MAX_MS),
              )
            }
            min={TIME_LIMIT_MIN_MS}
            max={TIME_LIMIT_MAX_MS}
          />
          <NumberField
            id="custom-memory-limit"
            label={t("custom.limits.memory")}
            hint={t("custom.limits.memoryHint", { max: MEMORY_LIMIT_MAX_MB })}
            value={memoryLimitMb}
            onChange={setMemoryLimitMb}
            onBlur={() =>
              setMemoryLimitMb((current) =>
                clampIntegerRange(
                  current,
                  MEMORY_LIMIT_DEFAULT_MB,
                  MEMORY_LIMIT_MIN_MB,
                  MEMORY_LIMIT_MAX_MB,
                ),
              )
            }
            min={MEMORY_LIMIT_MIN_MB}
            max={MEMORY_LIMIT_MAX_MB}
          />
        </CardContent>
      </Card>

      <Card>
        <CardHeader>
          <CardTitle className="text-lg">{t("custom.target.title")}</CardTitle>
          <CardDescription>{t("custom.target.subtitle")}</CardDescription>
        </CardHeader>
        <CardContent className="space-y-4">
          <LanguageField
            id="custom-target-language"
            value={targetLanguage}
            onChange={(value) => handleLanguageChange(value, setTargetLanguage)}
          />
          <CodeEditor value={targetSource} onChange={setTargetSource} language={targetLanguage} />
        </CardContent>
      </Card>

      <Card>
        <CardHeader>
          <CardTitle className="text-lg">{t("custom.correct.title")}</CardTitle>
          <CardDescription>{t("custom.correct.subtitle")}</CardDescription>
        </CardHeader>
        <CardContent className="space-y-4">
          <LanguageField
            id="custom-correct-language"
            value={correctLanguage}
            onChange={(value) => handleLanguageChange(value, setCorrectLanguage)}
          />
          <CodeEditor value={correctSource} onChange={setCorrectSource} language={correctLanguage} />
        </CardContent>
      </Card>

      <Card>
        <CardHeader>
          <div className="flex flex-wrap items-center justify-between gap-3">
            <div className="space-y-1">
              <CardTitle className="text-lg">{t("custom.generators.title")}</CardTitle>
              <CardDescription>{t("custom.generators.subtitle")}</CardDescription>
            </div>
            <Button type="button" variant="outline" size="sm" onClick={addGenerator}>
              <Plus className="mr-2 h-4 w-4" />
              {t("custom.generators.add")}
            </Button>
          </div>
        </CardHeader>
        <CardContent className="space-y-4">
          {generators.length === 0 ? (
            <p className="text-sm text-muted-foreground">{t("custom.generators.empty")}</p>
          ) : (
            generators.map((generator, index) => (
              <div key={`${generator.id}:${index}`} className="space-y-4 rounded-lg border p-4">
                <div className="grid gap-3 md:grid-cols-[minmax(14rem,32rem)_max-content_auto] md:items-end">
                  <div className="space-y-2">
                    <label htmlFor={`generator-id-${index}`} className="text-sm font-medium">
                      {t("custom.material.id")}
                    </label>
                    <Input
                      id={`generator-id-${index}`}
                      value={generator.id}
                      onChange={(event) => updateGenerator(index, { id: event.target.value })}
                    />
                  </div>
                  <LanguageField
                    id={`generator-language-${index}`}
                    value={generator.language}
                    onChange={(value) => {
                      handleLanguageChange(value, () => undefined);
                      updateGenerator(index, { language: value });
                    }}
                  />
                  <div className="flex items-end">
                    <Button type="button" variant="outline" size="sm" onClick={() => removeGenerator(index)}>
                      <Trash2 className="mr-2 h-4 w-4" />
                      {t("custom.material.remove")}
                    </Button>
                  </div>
                </div>
                <CodeEditor
                  value={generator.code}
                  onChange={(value) => updateGenerator(index, { code: value })}
                  language={generator.language}
                  height="240px"
                />
              </div>
            ))
          )}
        </CardContent>
      </Card>

      <Card>
        <CardHeader>
          <div className="flex flex-wrap items-center justify-between gap-3">
            <div className="space-y-1">
              <CardTitle className="text-lg">{t("custom.testcases.title")}</CardTitle>
              <CardDescription>{t("custom.testcases.subtitle")}</CardDescription>
            </div>
            <Button type="button" variant="outline" size="sm" onClick={addTextcase}>
              <Plus className="mr-2 h-4 w-4" />
              {t("custom.testcases.add")}
            </Button>
          </div>
        </CardHeader>
        <CardContent className="space-y-4">
          {textcases.length === 0 ? (
            <p className="text-sm text-muted-foreground">{t("custom.testcases.empty")}</p>
          ) : (
            textcases.map((testcase, index) => (
              <div key={`${testcase.id}:${index}`} className="space-y-4 rounded-lg border p-4">
                <div className="flex flex-wrap items-end gap-3">
                  <div className="min-w-0 flex-1 space-y-2">
                    <label htmlFor={`testcase-id-${index}`} className="text-sm font-medium">
                      {t("custom.material.id")}
                    </label>
                    <Input
                      id={`testcase-id-${index}`}
                      value={testcase.id}
                      onChange={(event) => updateTextcase(index, { id: event.target.value })}
                    />
                  </div>
                  <Button type="button" variant="outline" size="sm" onClick={() => removeTextcase(index)}>
                    <Trash2 className="mr-2 h-4 w-4" />
                    {t("custom.material.remove")}
                  </Button>
                </div>
                <div className="space-y-2">
                  <label htmlFor={`testcase-content-${index}`} className="text-sm font-medium">
                    {t("custom.testcases.content")}
                  </label>
                  <textarea
                    id={`testcase-content-${index}`}
                    value={testcase.content}
                    onChange={(event) => updateTextcase(index, { content: event.target.value })}
                    rows={8}
                    className="min-h-40 w-full rounded-md border border-input bg-background px-3 py-2 font-mono text-sm text-foreground focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring focus-visible:ring-offset-2"
                  />
                </div>
              </div>
            ))
          )}
        </CardContent>
      </Card>

      <Card>
        <CardHeader>
          <CardTitle className="text-lg">{t("custom.checker.title")}</CardTitle>
          <CardDescription>{t("custom.checker.subtitle")}</CardDescription>
        </CardHeader>
        <CardContent className="space-y-4">
          <label className="flex items-center gap-2 text-sm font-medium">
            <Switch checked={useChecker} onCheckedChange={setUseChecker} />
            <span>{t("custom.checker.use")}</span>
          </label>
          {useChecker && (
            <>
              <p className="text-sm text-muted-foreground">{t("custom.checker.hint")}</p>
              <CodeEditor value={checkerSource} onChange={setCheckerSource} language="cpp23" height="260px" />
            </>
          )}
        </CardContent>
      </Card>

      <Card>
        <CardHeader>
          <CardTitle className="text-lg">{t("custom.run.title")}</CardTitle>
        </CardHeader>
        <CardContent>
          <form className="space-y-4" onSubmit={onSubmit}>
            <NumberField
              id="custom-iterations"
              label={t("problem.iterations.label")}
              hint={t("problem.iterations.hint", { min: ITERATIONS_MIN, max: ITERATIONS_MAX })}
              value={iterations}
              onChange={setIterations}
              onBlur={() => setIterations((current) => clampIterations(current))}
              layout="stacked"
            />

            {providerCount === 0 && (
              <p className="text-sm font-medium text-destructive">
                {t("custom.providers.required")}
              </p>
            )}
            {(hasInvalidGenerators ||
              hasInvalidTextcases ||
              hasInvalidLimits ||
              (useChecker && !checkerSource.trim())) && (
              <p className="text-sm font-medium text-destructive">
                {t("custom.providers.invalid")}
              </p>
            )}

            <div className="flex justify-end">
              <Button
                type="submit"
                disabled={submitDisabled}
                className={cn(
                  stressMutation.isPending &&
                    "disabled:opacity-100 dark:disabled:bg-primary dark:disabled:text-primary-foreground",
                )}
              >
                {stressMutation.isPending
                  ? t("problem.submittingWithElapsed", { seconds: submitElapsedSeconds })
                  : t("custom.run.submit")}
              </Button>
            </div>
          </form>
        </CardContent>
      </Card>

      {submitError && <p className="text-sm font-medium text-destructive">{submitError}</p>}
      {result && (
        <StressResultView result={result} problemType="" externalId="" showSourceLinks={false} />
      )}
    </section>
  );
}

function buildCustomStressRequest({
  targetSource,
  targetLanguage,
  correctSource,
  correctLanguage,
  timeLimitMs,
  memoryLimitMb,
  generators,
  textcases,
  useChecker,
  checkerSource,
  iterations,
}: {
  targetSource: string;
  targetLanguage: LanguageValue;
  correctSource: string;
  correctLanguage: LanguageValue;
  timeLimitMs: number;
  memoryLimitMb: number;
  generators: GeneratorDraft[];
  textcases: TextcaseDraft[];
  useChecker: boolean;
  checkerSource: string;
  iterations: number;
}): StressRequest {
  return {
    targetCode: targetSource,
    targetCodeLang: targetLanguage,
    timeLimitMs: clampIntegerRange(
      timeLimitMs,
      TIME_LIMIT_DEFAULT_MS,
      TIME_LIMIT_MIN_MS,
      TIME_LIMIT_MAX_MS,
    ),
    memoryLimitMb: clampIntegerRange(
      memoryLimitMb,
      MEMORY_LIMIT_DEFAULT_MB,
      MEMORY_LIMIT_MIN_MB,
      MEMORY_LIMIT_MAX_MB,
    ),
    correctCode: correctSource,
    correctCodeLang: correctLanguage,
    checkerCode: useChecker ? checkerSource : "",
    generatorSources: generators.map((generator) => ({
      id: generator.id,
      code: generator.code,
      language: generator.language,
    })),
    textTestcases: textcases.map((testcase) => ({
      id: testcase.id,
      content: testcase.content,
    })),
    iterations: clampIterations(iterations),
  };
}

function LanguageField({
  id,
  value,
  onChange,
}: {
  id: string;
  value: LanguageValue;
  onChange: (value: LanguageValue) => void;
}) {
  const { t } = useI18n();

  return (
    <div className="space-y-2">
      <label htmlFor={id} className="text-sm font-medium">
        {t("problem.language")}
      </label>
      <select
        id={id}
        value={value}
        onChange={(event) => onChange(event.target.value as LanguageValue)}
        className="h-10 rounded-md border border-input bg-background px-3 py-2 text-sm text-foreground focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring focus-visible:ring-offset-2"
      >
        {LANGUAGES.map((language) => (
          <option key={language.value} value={language.value}>
            {language.label}
          </option>
        ))}
      </select>
    </div>
  );
}

function NumberField({
  id,
  label,
  hint,
  value,
  onChange,
  onBlur,
  min = 1,
  max,
  layout = "inline",
}: {
  id: string;
  label: string;
  hint?: string;
  value: number;
  onChange: (value: number) => void;
  onBlur: () => void;
  min?: number;
  max?: number;
  layout?: "inline" | "stacked";
}) {
  const stacked = layout === "stacked";

  return (
    <div
      className={cn(
        "grid gap-2",
        stacked
          ? "justify-start"
          : "sm:w-max sm:max-w-full sm:grid-cols-[max-content_max-content] sm:items-center sm:gap-x-3",
      )}
    >
      <label htmlFor={id} className={cn("text-sm font-medium", !stacked && "sm:text-right")}>
        {label}
      </label>
      <input
        id={id}
        type="number"
        min={min}
        max={max}
        step={1}
        value={value}
        onChange={(event) => {
          const next = Number(event.target.value);
          onChange(Number.isFinite(next) ? next : 0);
        }}
        onBlur={onBlur}
        className="h-10 w-full rounded-md border border-input bg-background px-3 py-2 text-sm text-foreground focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring focus-visible:ring-offset-2 sm:w-40"
      />
      {hint && (
        <p className={cn("text-sm text-muted-foreground", !stacked && "sm:col-span-2 sm:whitespace-nowrap")}>
          {hint}
        </p>
      )}
    </div>
  );
}

function formatSubmitError(
  error: Error | null,
  t: (key: TranslationKey, values?: Record<string, string | number>) => string,
): string | null {
  if (!error) return null;
  if (error instanceof ApiError && error.status === 429) {
    return t("problem.rateLimited", { message: error.message });
  }
  return error.message || t("problem.unknownError");
}
