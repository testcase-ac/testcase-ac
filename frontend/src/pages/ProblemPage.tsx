import { useMutation, useQuery } from "@tanstack/react-query";
import { Check, ChevronDown, ExternalLink } from "lucide-react";
import { useEffect, useRef, useState, type FormEvent, type ReactNode } from "react";
import { Link, useParams } from "react-router-dom";

import { Badge } from "@/components/ui/badge";
import { Button } from "@/components/ui/button";
import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Switch } from "@/components/ui/switch";
import { guessLanguage, resolveDetectedLanguage } from "@/lib/languageDetection";
import { useElapsedSeconds } from "@/lib/useElapsedSeconds";
import { usePersistentSettings } from "@/lib/persistentSettings";
import { defaultSource } from "@/lib/sourceTemplates";
import { cn } from "@/lib/utils";
import { ApiError, getProblem, submitStress } from "../api";
import CodeEditor from "../components/CodeEditor";
import LanguageField from "../components/LanguageField";
import StressResultView from "../components/StressResult";
import { problemDirUrl, sourceFileUrl } from "../github";
import { useI18n, type TranslationKey } from "../lib/i18n";
import { problemTypeLabel } from "../lib/typeMetadata";
import {
  isCppLanguageValue,
  type CodeInfo,
  type LanguageValue,
  type ProblemDetail,
  type StressRequest,
  type TestcaseInfo,
  type TypeMetadata,
} from "../types";
import {
  ITERATIONS_DEFAULT,
  ITERATIONS_MAX,
  ITERATIONS_MIN,
} from "../types";

const PROBLEM_1000_DEFAULT_CPP_SOURCE = `#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    if (a % 2 == 1 && b % 2 == 1) {
        a--; // bug
    }
    cout << a + b << endl;
    return 0;
}
`;

function isBoj1000(problemType: string, externalId: string): boolean {
  return problemType === "boj" && externalId === "1000";
}

function initialLanguageForProblem({
  problemType,
  externalId,
  lastManualLanguage,
  lastManualCppLanguage,
}: {
  problemType: string;
  externalId: string;
  lastManualLanguage: LanguageValue;
  lastManualCppLanguage: LanguageValue;
}): LanguageValue {
  if (isBoj1000(problemType, externalId)) {
    return lastManualCppLanguage;
  }
  return lastManualLanguage;
}

function initialSourceForProblem({
  problemType,
  externalId,
  language,
}: {
  problemType: string;
  externalId: string;
  language: LanguageValue;
}): string {
  if (isBoj1000(problemType, externalId) && isCppLanguageValue(language)) {
    return PROBLEM_1000_DEFAULT_CPP_SOURCE;
  }
  return defaultSource(language);
}

function isUsingAutoFilledSource({
  source,
  problemType,
  externalId,
  language,
}: {
  source: string;
  problemType: string;
  externalId: string;
  language: LanguageValue;
}): boolean {
  return source.trim() === initialSourceForProblem({ problemType, externalId, language }).trim();
}

function buildStressRequest({
  source,
  language,
  selectedCorrectCode,
  selectedGenerators,
  selectedSinglegens,
  selectedTestcases,
  iterations,
}: {
  source: string;
  language: LanguageValue;
  selectedCorrectCode: string | null;
  selectedGenerators: string[];
  selectedSinglegens: string[];
  selectedTestcases: string[];
  iterations: number;
}): StressRequest {
  return {
    targetCode: source,
    targetCodeLang: language,
    correctCodeFilename: selectedCorrectCode ?? undefined,
    generatorFilenames: selectedGenerators,
    singlegenFilenames: selectedSinglegens,
    testcaseFilenames: selectedTestcases,
    iterations,
  };
}

function clampIterations(value: number): number {
  if (!Number.isFinite(value)) return ITERATIONS_DEFAULT;
  return Math.min(ITERATIONS_MAX, Math.max(ITERATIONS_MIN, Math.floor(value)));
}

export default function ProblemPage() {
  const { problemType = "", externalId = "" } = useParams();

  return <ProblemWorkspace key={`${problemType}/${externalId}`} externalId={externalId} problemType={problemType} />;
}

export function ProblemWorkspace({
  problemType,
  externalId,
  typeMetadata,
}: {
  problemType: string;
  externalId: string;
  typeMetadata?: TypeMetadata;
}) {
  const { t } = useI18n();
  const {
    useLanguageAutodetect,
    setUseLanguageAutodetect,
    lastManualLanguage,
    lastManualCppLanguage,
    setLastManualLanguage,
    setLastManualCppLanguage,
  } = usePersistentSettings();
  const problemQuery = useQuery({
    queryKey: ["problem", problemType, externalId],
    queryFn: () => getProblem(problemType, externalId),
    enabled: Boolean(problemType && externalId),
  });

  const initialLanguage = initialLanguageForProblem({
    problemType,
    externalId,
    lastManualLanguage,
    lastManualCppLanguage,
  });
  const [language, setLanguage] = useState<LanguageValue>(initialLanguage);
  const [source, setSource] = useState(() =>
    initialSourceForProblem({ problemType, externalId, language: initialLanguage }),
  );
  const [advancedOpen, setAdvancedOpen] = useState(false);
  const [selectedCorrectCode, setSelectedCorrectCode] = useState<string | null>(null);
  const [selectedGenerators, setSelectedGenerators] = useState<string[]>([]);
  const [selectedSinglegens, setSelectedSinglegens] = useState<string[]>([]);
  const [selectedTestcases, setSelectedTestcases] = useState<string[]>([]);
  const [iterations, setIterations] = useState<number>(ITERATIONS_DEFAULT);
  const [lastSubmittedRequest, setLastSubmittedRequest] = useState<string | null>(null);
  const stressMutation = useMutation({
    mutationFn: (payload: StressRequest) => submitStress(problemType, externalId, payload),
  });
  const submitElapsedSeconds = useElapsedSeconds(stressMutation.isPending);

  useEffect(() => {
    if (!problemQuery.data) return;
    setSelectedCorrectCode(problemQuery.data.correctCodes[0]?.filename ?? null);
    setSelectedGenerators(problemQuery.data.generators.map((code) => code.filename));
    setSelectedSinglegens(problemQuery.data.singlegens.map((code) => code.filename));
    setSelectedTestcases(problemQuery.data.testcases.map((tc) => tc.filename));
  }, [problemQuery.data]);

  useEffect(() => {
    if (!useLanguageAutodetect) return;
    const guessedLanguage = guessLanguage(source);
    if (!guessedLanguage) return;
    const detectedLanguage = resolveDetectedLanguage(guessedLanguage, lastManualCppLanguage);
    if (detectedLanguage !== language) {
      setLanguage(detectedLanguage);
    }
  }, [language, lastManualCppLanguage, source, useLanguageAutodetect]);

  function handleManualLanguageChange(next: LanguageValue) {
    if (isUsingAutoFilledSource({ source, problemType, externalId, language })) {
      setSource(initialSourceForProblem({ problemType, externalId, language: next }));
    }
    setLastManualLanguage(next);
    if (isCppLanguageValue(next)) {
      setLastManualCppLanguage(next);
    }
    setLanguage(next);
  }

  function onSubmit(e: FormEvent) {
    e.preventDefault();
    const payload = buildStressRequest({
      source,
      language,
      selectedCorrectCode,
      selectedGenerators,
      selectedSinglegens,
      selectedTestcases,
      iterations: clampIterations(iterations),
    });
    stressMutation.reset();
    setLastSubmittedRequest(JSON.stringify(payload));
    stressMutation.mutate(payload);
  }

  const loadError = problemQuery.error instanceof Error ? problemQuery.error.message : null;
  if (loadError) {
    return (
      <section className="space-y-4">
        <p className="text-sm font-medium text-destructive">
          {t("problem.loadFailed", { message: loadError })}
        </p>
        <Button asChild variant="outline">
          <Link to="/">{t("problem.back.button")}</Link>
        </Button>
      </section>
    );
  }

  const problem = problemQuery.data ?? null;
  if (!problem) {
    return <p className="text-sm text-muted-foreground">{t("problem.loading")}</p>;
  }

  const submitting = stressMutation.isPending;
  const selectedProviderCount =
    selectedGenerators.length + selectedSinglegens.length + selectedTestcases.length;
  const repoDir = problemDirUrl(problem.problemType, problem.externalId);
  const currentRequest = JSON.stringify(
    buildStressRequest({
      source,
      language,
      selectedCorrectCode,
      selectedGenerators,
      selectedSinglegens,
      selectedTestcases,
      iterations: clampIterations(iterations),
    }),
  );
  const showLatestResponse = currentRequest === lastSubmittedRequest;
  const submitError = showLatestResponse ? formatSubmitError(stressMutation.error, t) : null;
  const result = showLatestResponse ? stressMutation.data ?? null : null;
  const submitLabel = submitting
    ? t("problem.submittingWithElapsed", { seconds: submitElapsedSeconds })
    : t("problem.submit");

  return (
    <section className="space-y-6">
      <header className="space-y-3">
        <h1 className="flex flex-wrap items-center gap-2 text-3xl font-semibold">
          <Badge variant="secondary">
            {problemTypeLabel(problem.problemType, typeMetadata)}
          </Badge>
          <span className="font-mono text-2xl text-muted-foreground">{problem.externalId}</span>
          {problem.title ? <span>{problem.title}</span> : null}
        </h1>
        <div className="flex flex-wrap gap-x-4 gap-y-2 text-sm text-muted-foreground">
          {problem.externalLink && (
            <a
              href={problem.externalLink}
              target="_blank"
              rel="noreferrer"
              className="inline-flex items-center gap-1.5 hover:text-foreground"
            >
              {t("problem.externalLink")}
              <ExternalLink className="h-3.5 w-3.5" aria-hidden />
            </a>
          )}
          {repoDir && (
            <a
              href={repoDir}
              target="_blank"
              rel="noreferrer"
              className="inline-flex items-center gap-1.5 hover:text-foreground"
            >
              {t("problem.viewOnGitHub")}
              <ExternalLink className="h-3.5 w-3.5" aria-hidden />
            </a>
          )}
          <span>{t("problem.time", { ms: problem.timeLimitMs })}</span>
          <span>{t("problem.memory", { mb: problem.memoryLimitMb })}</span>
        </div>
      </header>

      {problem.description && (
        <div className="whitespace-pre-wrap rounded-md border bg-muted/40 p-5 text-base leading-7">
          {problem.description}
        </div>
      )}

      <Card>
        <CardHeader>
          <CardTitle className="text-lg">{t("problem.trySolution")}</CardTitle>
        </CardHeader>
        <CardContent>
          <form className="space-y-4" onSubmit={onSubmit}>
            <div className="flex flex-wrap items-center gap-3">
              <LanguageField
                id="lang"
                value={language}
                onChange={handleManualLanguageChange}
                orientation="horizontal"
              />
              <label className="flex items-center gap-2 text-sm text-muted-foreground">
                <Switch
                  checked={useLanguageAutodetect}
                  onCheckedChange={setUseLanguageAutodetect}
                  aria-label={t("problem.languageAutodetect")}
                />
                <span>{t("problem.languageAutodetect")}</span>
              </label>
            </div>

            <CodeEditor value={source} onChange={setSource} language={language} />

            <AdvancedStressOptions
              problem={problem}
              open={advancedOpen}
              setOpen={setAdvancedOpen}
              selectedCorrectCode={selectedCorrectCode}
              setSelectedCorrectCode={setSelectedCorrectCode}
              selectedGenerators={selectedGenerators}
              setSelectedGenerators={setSelectedGenerators}
              selectedSinglegens={selectedSinglegens}
              setSelectedSinglegens={setSelectedSinglegens}
              selectedTestcases={selectedTestcases}
              setSelectedTestcases={setSelectedTestcases}
              iterations={iterations}
              setIterations={setIterations}
            />

            {selectedProviderCount === 0 && (
              <p className="text-sm font-medium text-destructive">
                {t("problem.providers.noneSelected")}
              </p>
            )}

            <div className="flex justify-end">
              <Button
                type="submit"
                disabled={submitting || !source.trim() || selectedProviderCount === 0 || !selectedCorrectCode}
                className={cn(
                  submitting &&
                    "disabled:opacity-100 dark:disabled:bg-primary dark:disabled:text-primary-foreground",
                )}
              >
                {submitLabel}
              </Button>
            </div>
          </form>
        </CardContent>
      </Card>

      {submitError && <p className="text-sm font-medium text-destructive">{submitError}</p>}
      {result && (
        <StressResultView
          result={result}
          problemType={problem.problemType}
          externalId={problem.externalId}
        />
      )}
    </section>
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

function AdvancedStressOptions({
  problem,
  open,
  setOpen,
  selectedCorrectCode,
  setSelectedCorrectCode,
  selectedGenerators,
  setSelectedGenerators,
  selectedSinglegens,
  setSelectedSinglegens,
  selectedTestcases,
  setSelectedTestcases,
  iterations,
  setIterations,
}: {
  problem: ProblemDetail;
  open: boolean;
  setOpen: (open: boolean) => void;
  selectedCorrectCode: string | null;
  setSelectedCorrectCode: (filename: string | null) => void;
  selectedGenerators: string[];
  setSelectedGenerators: (filenames: string[]) => void;
  selectedSinglegens: string[];
  setSelectedSinglegens: (filenames: string[]) => void;
  selectedTestcases: string[];
  setSelectedTestcases: (filenames: string[]) => void;
  iterations: number;
  setIterations: (n: number) => void;
}) {
  const { t } = useI18n();
  const summary = [
    t("problem.summary.iterations", { count: clampIterations(iterations) }),
    t("problem.summary.generators", { count: selectedGenerators.length }),
    t("problem.summary.singlegens", { count: selectedSinglegens.length }),
    t("problem.summary.testcases", { count: selectedTestcases.length }),
  ]
    .filter(Boolean)
    .join(" · ") || t("problem.summary.none");

  return (
    <div className="rounded-md border bg-muted/20">
      <button
        type="button"
        onClick={() => setOpen(!open)}
        className="flex w-full items-start justify-between gap-4 px-4 py-3 text-left"
        aria-expanded={open}
      >
        <div className="space-y-1">
          <div className="text-base font-medium">{t("problem.advanced.title")}</div>
          <div className="text-sm text-muted-foreground">{summary}</div>
        </div>
        <ChevronDown className={cn("mt-0.5 h-4 w-4 shrink-0 text-muted-foreground transition-transform", open && "rotate-180")} />
      </button>

      {open && (
        <div className="space-y-5 border-t px-4 py-4">
          <IterationsField value={iterations} onChange={setIterations} />

          <SelectableCodeGroup
            label={t("problem.option.correct")}
            codes={problem.correctCodes}
            selected={selectedCorrectCode}
            onSelect={setSelectedCorrectCode}
            problemType={problem.problemType}
            externalId={problem.externalId}
          />

          <SelectableFileGroup
            label={t("problem.providers.generators")}
            files={problem.generators}
            selected={selectedGenerators}
            onChange={setSelectedGenerators}
            problemType={problem.problemType}
            externalId={problem.externalId}
          />

          <SelectableFileGroup
            label={t("problem.providers.singlegens")}
            files={problem.singlegens}
            selected={selectedSinglegens}
            onChange={setSelectedSinglegens}
            problemType={problem.problemType}
            externalId={problem.externalId}
          />

          <SelectableTestcaseGroup
            label={t("problem.providers.testcases")}
            files={problem.testcases}
            selected={selectedTestcases}
            onChange={setSelectedTestcases}
            problemType={problem.problemType}
            externalId={problem.externalId}
          />

          {problem.isSpecialJudge && (
            <ReferenceFileGroup
              label={t("problem.providers.checker")}
              file={problem.checker}
              hint={t("problem.reference.checkerHint")}
              problemType={problem.problemType}
              externalId={problem.externalId}
            />
          )}

          <ReferenceFileGroup
            label={t("problem.providers.validator")}
            file={problem.validator}
            hint={t("problem.reference.validatorHint")}
            problemType={problem.problemType}
            externalId={problem.externalId}
          />
        </div>
      )}
    </div>
  );
}

function SelectableCodeGroup({
  label,
  codes,
  selected,
  onSelect,
  problemType,
  externalId,
}: {
  label: string;
  codes: CodeInfo[];
  selected: string | null;
  onSelect: (filename: string) => void;
  problemType: string;
  externalId: string;
}) {
  const { t } = useI18n();
  const [warning, setWarning] = useState(false);
  const warningTimer = useRef<number | null>(null);

  function handleClick(filename: string) {
    if (selected === filename) {
      setWarning(true);
      if (warningTimer.current) window.clearTimeout(warningTimer.current);
      warningTimer.current = window.setTimeout(() => setWarning(false), 3000);
      return;
    }
    setWarning(false);
    onSelect(filename);
  }

  useEffect(() => {
    return () => {
      if (warningTimer.current) window.clearTimeout(warningTimer.current);
    };
  }, []);

  return (
    <SelectionGroupShell label={label}>
      {codes.length === 0 ? (
        <p className="text-xs text-muted-foreground">{t("problem.providers.none")}</p>
      ) : (
        <>
          <FileChipGrid>
            {codes.map((code) => (
              <SelectableFileChip
                key={code.filename}
                filename={code.filename}
                authorName={code.authorName}
                selected={selected === code.filename}
                onClick={() => handleClick(code.filename)}
                url={sourceFileUrl(problemType, externalId, code.filename)}
              />
            ))}
          </FileChipGrid>
          {warning && (
            <p className="text-xs font-medium text-destructive">
              {t("problem.correct.cannotDeselect")}
            </p>
          )}
        </>
      )}
    </SelectionGroupShell>
  );
}

function SelectableFileGroup({
  label,
  files,
  selected,
  onChange,
  problemType,
  externalId,
}: {
  label: string;
  files: CodeInfo[];
  selected: string[];
  onChange: (filenames: string[]) => void;
  problemType: string;
  externalId: string;
}) {
  const { t } = useI18n();

  function toggle(filename: string) {
    onChange(
      selected.includes(filename)
        ? selected.filter((name) => name !== filename)
        : [...selected, filename],
    );
  }

  return (
    <SelectionGroupShell label={label}>
      {files.length === 0 ? (
        <p className="text-xs text-muted-foreground">{t("problem.providers.none")}</p>
      ) : (
        <FileChipGrid>
          {files.map((file) => (
            <SelectableFileChip
              key={file.filename}
              filename={file.filename}
              authorName={file.authorName}
              selected={selected.includes(file.filename)}
              onClick={() => toggle(file.filename)}
              url={sourceFileUrl(problemType, externalId, file.filename)}
            />
          ))}
        </FileChipGrid>
      )}
    </SelectionGroupShell>
  );
}

function SelectableTestcaseGroup({
  label,
  files,
  selected,
  onChange,
  problemType,
  externalId,
}: {
  label: string;
  files: TestcaseInfo[];
  selected: string[];
  onChange: (filenames: string[]) => void;
  problemType: string;
  externalId: string;
}) {
  const { t } = useI18n();

  function toggle(filename: string) {
    onChange(
      selected.includes(filename)
        ? selected.filter((name) => name !== filename)
        : [...selected, filename],
    );
  }

  return (
    <SelectionGroupShell label={label}>
      {files.length === 0 ? (
        <p className="text-xs text-muted-foreground">{t("problem.providers.none")}</p>
      ) : (
        <FileChipGrid>
          {files.map((file) => (
            <SelectableFileChip
              key={file.filename}
              filename={file.filename}
              authorName={file.authorName}
              selected={selected.includes(file.filename)}
              onClick={() => toggle(file.filename)}
              url={sourceFileUrl(problemType, externalId, file.filename)}
            />
          ))}
        </FileChipGrid>
      )}
    </SelectionGroupShell>
  );
}

function ReferenceFileGroup({
  label,
  file,
  hint,
  problemType,
  externalId,
}: {
  label: string;
  file: CodeInfo | null;
  hint: string;
  problemType: string;
  externalId: string;
}) {
  const { t } = useI18n();

  return (
    <SelectionGroupShell label={label} hint={hint}>
      {file ? (
        <FileChipGrid>
          <ReferenceFileChip
            filename={file.filename}
            authorName={file.authorName}
            url={sourceFileUrl(problemType, externalId, file.filename)}
          />
        </FileChipGrid>
      ) : (
        <p className="text-xs text-muted-foreground">{t("problem.providers.none")}</p>
      )}
    </SelectionGroupShell>
  );
}

function IterationsField({
  value,
  onChange,
}: {
  value: number;
  onChange: (n: number) => void;
}) {
  const { t } = useI18n();
  return (
    <SelectionGroupShell
      label={t("problem.iterations.label")}
      hint={t("problem.iterations.hint", { min: ITERATIONS_MIN, max: ITERATIONS_MAX })}
    >
      <input
        type="number"
        min={ITERATIONS_MIN}
        max={ITERATIONS_MAX}
        step={1}
        value={value}
        onChange={(e) => {
          const next = Number(e.target.value);
          onChange(Number.isFinite(next) ? next : ITERATIONS_DEFAULT);
        }}
        onBlur={() => onChange(clampIterations(value))}
        className="h-10 w-32 rounded-md border border-input bg-background px-3 py-2 text-sm text-foreground focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring focus-visible:ring-offset-2"
      />
    </SelectionGroupShell>
  );
}

function SelectionGroupShell({
  label,
  hint,
  children,
}: {
  label: string;
  hint?: string;
  children: ReactNode;
}) {
  return (
    <div className="space-y-2">
      <div className="flex items-baseline gap-2">
        <div className="text-xs font-medium uppercase tracking-wide text-muted-foreground">{label}</div>
        {hint && <div className="text-[11px] text-muted-foreground/80">{hint}</div>}
      </div>
      {children}
    </div>
  );
}

function FileChipGrid({ children }: { children: ReactNode }) {
  return <div className="grid gap-2 md:grid-cols-2 xl:grid-cols-3">{children}</div>;
}

function SelectableFileChip({
  filename,
  authorName,
  selected,
  onClick,
  url,
}: {
  filename: string;
  authorName?: string | null;
  selected: boolean;
  onClick: () => void;
  url: string | null;
}) {
  const { t } = useI18n();

  return (
    <div
      className={cn(
        "flex min-w-0 overflow-hidden rounded-md border transition-colors",
        selected
          ? "border-foreground bg-accent"
          : "border-border bg-background hover:border-foreground/40",
      )}
    >
      <button
        type="button"
        className="flex min-w-0 flex-1 items-center gap-3 px-3 py-2 text-left"
        onClick={onClick}
        aria-pressed={selected}
      >
        <span
          className={cn(
            "flex h-4 w-4 shrink-0 items-center justify-center rounded-sm border transition-colors",
            selected
              ? "border-foreground bg-foreground text-background"
              : "border-muted-foreground/50 bg-background",
          )}
          aria-hidden
        >
          {selected && <Check className="h-3 w-3" strokeWidth={3} />}
        </span>
        <span className="min-w-0 flex-1">
          <span className="block truncate font-mono text-xs">{filename}</span>
          <span className="block truncate text-[11px] text-muted-foreground">
            {authorName || t("problem.author.unknown")}
          </span>
        </span>
      </button>
      {url && (
        <a
          href={url}
          target="_blank"
          rel="noreferrer"
          className="flex items-center border-l px-3 text-muted-foreground transition-colors hover:text-foreground"
          aria-label={`${t("problem.link.view")}: ${filename}`}
          onClick={(event) => event.stopPropagation()}
        >
          <ExternalLink className="h-3.5 w-3.5" />
        </a>
      )}
    </div>
  );
}

function ReferenceFileChip({
  filename,
  authorName,
  url,
}: {
  filename: string;
  authorName?: string | null;
  url: string | null;
}) {
  const { t } = useI18n();

  return (
    <div className="flex min-w-0 overflow-hidden rounded-md border border-dashed border-border/70 bg-muted/30">
      <div className="min-w-0 flex-1 px-3 py-2">
        <div className="truncate font-mono text-xs text-muted-foreground">{filename}</div>
        <div className="truncate text-[11px] text-muted-foreground/80">
          {authorName || t("problem.author.unknown")}
        </div>
      </div>
      {url && (
        <a
          href={url}
          target="_blank"
          rel="noreferrer"
          className="flex items-center border-l border-border/70 px-3 text-muted-foreground transition-colors hover:text-foreground"
          aria-label={`${t("problem.link.view")}: ${filename}`}
        >
          <ExternalLink className="h-3.5 w-3.5" />
        </a>
      )}
    </div>
  );
}
