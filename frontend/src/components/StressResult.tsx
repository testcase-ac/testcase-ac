import { ChevronDown, Clipboard, ClipboardCheck } from "lucide-react";
import { useEffect, useRef, useState, type ReactNode } from "react";

import { sourceFileUrl } from "../github";
import { cn } from "@/lib/utils";
import { useI18n, type TranslationKey } from "../lib/i18n";
import type {
  AttemptedCase,
  Counterexample,
  ExecutionFailedCase,
  StressResponse,
  TextWithMetadata,
  Verdict,
} from "../types";
import { Card, CardContent } from "./ui/card";

const STATUS_KEY: Record<StressResponse["status"], TranslationKey> = {
  found: "stress.status.found",
  not_found: "stress.status.not_found",
  compile_error: "stress.status.compile_error",
  runtime_error: "stress.status.runtime_error",
  invalid_problem: "stress.status.invalid_problem",
  rate_limited: "stress.status.rate_limited",
  internal_error: "stress.status.internal_error",
};

export default function StressResultView({
  result,
  problemType,
  externalId,
  showSourceLinks = true,
}: {
  result: StressResponse;
  problemType: string;
  externalId: string;
  showSourceLinks?: boolean;
}) {
  const { t } = useI18n();
  const label = STATUS_KEY[result.status] ? t(STATUS_KEY[result.status]) : result.status;
  const wrongCases = result.wrongCases ?? [];
  const executionFailedCases = result.executionFailedCases ?? [];
  const totalCases = result.totalCases ?? 0;
  const correctCasesCount = result.correctCasesCount ?? result.totalAttempted ?? 0;
  const wrongCasesCount = result.wrongCasesCount ?? wrongCases.length;
  const executionFailedCasesCount =
    result.executionFailedCasesCount ?? executionFailedCases.length;
  const showCounts = result.status === "found" || result.status === "not_found";
  const showSamples = result.status === "found" && (wrongCases.length > 0 || executionFailedCases.length > 0);
  const formattedRuntimeSeconds = formatRuntimeSeconds(result.runtimeSeconds);
  const runtimeText = formattedRuntimeSeconds
    ? t("stress.runtime", { seconds: formattedRuntimeSeconds })
    : null;
  const resultRef = useRef<HTMLDivElement | null>(null);

  useEffect(() => {
    if (result.status !== "found") return;
    resultRef.current?.scrollIntoView({
      behavior: "smooth",
      block: "start",
    });
  }, [result.requestId, result.status]);

  return (
    <Card ref={resultRef} className="scroll-mt-6">
      <CardContent className="space-y-4 p-4">
        <div className="flex flex-wrap items-baseline justify-between gap-2">
          <strong className={cn("text-lg", statusClass(result.status))}>{label}</strong>
          <div className="flex flex-wrap items-center gap-2 font-mono text-xs text-muted-foreground">
            {runtimeText && <span>{runtimeText}</span>}
            <span>{result.requestId}</span>
          </div>
        </div>
        {result.errorMessage && (
          <pre className="overflow-x-auto whitespace-pre-wrap rounded-md border bg-background p-3 font-mono text-sm text-destructive">
            {result.errorMessage}
          </pre>
        )}
        {showCounts && (
          <StressSummary
            totalCases={totalCases}
            correctCasesCount={correctCasesCount}
            wrongCasesCount={wrongCasesCount}
            executionFailedCasesCount={executionFailedCasesCount}
          />
        )}
        {showSamples && (
          <p className="text-sm text-muted-foreground">{t("stress.samples.note")}</p>
        )}
        {wrongCases.length > 0 && (
          <CaseGroup
            title={t("stress.section.wrongCases", {
              total: wrongCasesCount,
            })}
          >
            {wrongCases.map((counterexample, index) => (
              <div
                key={`${counterexample.generatedBy.stage}:${counterexample.generatedBy.id}:${counterexample.generatedBy.seed ?? "noseed"}:${index}`}
                className="scroll-mt-6"
              >
                <CounterexampleView
                  ce={counterexample}
                  index={index}
                  problemType={problemType}
                  externalId={externalId}
                  showSourceLinks={showSourceLinks}
                />
              </div>
            ))}
          </CaseGroup>
        )}
        {executionFailedCases.length > 0 && (
          <CaseGroup
            title={t("stress.section.executionFailedCases", {
              total: executionFailedCasesCount,
            })}
          >
            {executionFailedCases.map((executionFailedCase, index) => (
              <div
                key={`${executionFailedCase.generatedBy.stage}:${executionFailedCase.generatedBy.id}:${executionFailedCase.generatedBy.seed ?? "noseed"}:${index}`}
                className="scroll-mt-6"
              >
                <ExecutionFailedCaseView
                  ce={executionFailedCase}
                  index={index}
                  problemType={problemType}
                  externalId={externalId}
                  showSourceLinks={showSourceLinks}
                />
              </div>
            ))}
          </CaseGroup>
        )}
        {result.status === "not_found" && (
          <p className="text-base leading-7 text-muted-foreground">{t("stress.notFoundDetail")}</p>
        )}
        {(result.status === "found" || result.status === "not_found") && (
          <AttemptedCasesSection
            cases={result.attemptedCases ?? []}
            total={correctCasesCount}
            status={result.status}
            problemType={problemType}
            externalId={externalId}
            showSourceLinks={showSourceLinks}
          />
        )}
      </CardContent>
    </Card>
  );
}

function statusClass(status: StressResponse["status"]): string {
  if (status === "found") return "text-destructive";
  if (status === "not_found") return "text-emerald-600 dark:text-emerald-400";
  return "text-foreground";
}

function StressSummary({
  totalCases,
  correctCasesCount,
  wrongCasesCount,
  executionFailedCasesCount,
}: {
  totalCases: number;
  correctCasesCount: number;
  wrongCasesCount: number;
  executionFailedCasesCount: number;
}) {
  const { t } = useI18n();
  const items = [
    { label: t("stress.summary.totalCases"), value: totalCases },
    { label: t("stress.summary.correctCases"), value: correctCasesCount },
    { label: t("stress.summary.wrongCases"), value: wrongCasesCount },
    { label: t("stress.summary.executionFailedCases"), value: executionFailedCasesCount },
  ];

  return (
    <div className="grid gap-3 sm:grid-cols-2 xl:grid-cols-4">
      {items.map((item) => (
        <div key={item.label} className="rounded-md border bg-muted/20 px-4 py-3">
          <div className="text-xs uppercase tracking-wide text-muted-foreground">{item.label}</div>
          <div className="mt-1 font-mono text-2xl font-semibold">{item.value}</div>
        </div>
      ))}
    </div>
  );
}

function CaseGroup({ title, children }: { title: string; children: ReactNode }) {
  return (
    <section className="space-y-3">
      <h3 className="text-sm font-semibold text-muted-foreground">{title}</h3>
      <div className="space-y-3">{children}</div>
    </section>
  );
}

function CounterexampleView({
  ce,
  index,
  problemType,
  externalId,
  showSourceLinks,
}: {
  ce: Counterexample;
  index: number;
  problemType: string;
  externalId: string;
  showSourceLinks: boolean;
}) {
  const { t } = useI18n();
  const { id, seed } = ce.generatedBy;
  const url = showSourceLinks ? sourceFileUrl(problemType, externalId, id) : null;
  const verdict = ce.verdict && ce.verdict !== "WA" ? ce.verdict : null;

  return (
    <div className="overflow-hidden rounded-md border">
      <div className="flex flex-wrap items-baseline gap-2 border-b bg-muted/30 px-4 py-2.5">
        <span className="text-base font-semibold">
          {t("stress.counterexample.number", { n: index + 1 })}
        </span>
        {verdict && <VerdictPill verdict={verdict} />}
        <span className="text-base text-muted-foreground">-</span>
        {url ? (
          <a
            href={url}
            target="_blank"
            rel="noreferrer"
            className="font-mono text-base text-foreground hover:underline"
          >
            {id}
          </a>
        ) : (
          <span className="font-mono text-base">{id}</span>
        )}
        {seed && (
          <span className="font-mono text-sm text-muted-foreground">
            ({t("stress.seed")}: {seed})
          </span>
        )}
      </div>
      <div className="space-y-3 p-3">
        <TextBlock title={t("stress.label.input")} tt={ce.testcase} />
        <div className="grid items-start gap-3 md:grid-cols-2">
          <TextBlock title={t("stress.label.yourOutput")} tt={ce.targetOutput} />
          <TextBlock title={t("stress.label.correctOutput")} tt={ce.correctOutput} />
        </div>
        {ce.stderr && ce.stderr.text && (
          <TextBlock title={t("stress.label.stderr")} tt={ce.stderr} />
        )}
      </div>
    </div>
  );
}

function ExecutionFailedCaseView({
  ce,
  index,
  problemType,
  externalId,
  showSourceLinks,
}: {
  ce: ExecutionFailedCase;
  index: number;
  problemType: string;
  externalId: string;
  showSourceLinks: boolean;
}) {
  const { t } = useI18n();
  const { id, seed } = ce.generatedBy;
  const url = showSourceLinks ? sourceFileUrl(problemType, externalId, id) : null;

  return (
    <div className="overflow-hidden rounded-md border">
      <div className="flex flex-wrap items-baseline gap-2 border-b bg-muted/30 px-4 py-2.5">
        <span className="text-base font-semibold">
          {t("stress.executionFailed.number", { n: index + 1 })}
        </span>
        <VerdictPill verdict={ce.reason} />
        <span className="text-base text-muted-foreground">-</span>
        {url ? (
          <a
            href={url}
            target="_blank"
            rel="noreferrer"
            className="font-mono text-base text-foreground hover:underline"
          >
            {id}
          </a>
        ) : (
          <span className="font-mono text-base">{id}</span>
        )}
        {seed && (
          <span className="font-mono text-sm text-muted-foreground">
            ({t("stress.seed")}: {seed})
          </span>
        )}
      </div>
      <div className="space-y-3 p-3">
        <TextBlock title={t("stress.label.input")} tt={ce.testcase} />
        <div className="grid items-start gap-3 md:grid-cols-2">
          <TextBlock
            title={t("stress.label.failureReason")}
            tt={plainText(formatFailureReason(ce.reason, ce.timeSeconds, t))}
          />
          <TextBlock title={t("stress.label.correctOutput")} tt={ce.correctOutput} />
        </div>
        {ce.stderr && ce.stderr.text && (
          <TextBlock title={t("stress.label.stderr")} tt={ce.stderr} />
        )}
      </div>
    </div>
  );
}

function VerdictPill({ verdict }: { verdict: Verdict }) {
  return (
    <span className="inline-flex items-center rounded-full border border-destructive/40 bg-destructive/10 px-2 py-0.5 font-mono text-xs font-semibold uppercase text-destructive">
      {verdict}
    </span>
  );
}

function formatFailureReason(
  reason: Verdict,
  timeSeconds: number,
  t: (key: TranslationKey, values?: Record<string, string | number>) => string,
): string {
  if (reason === "TLE" && timeSeconds > 0) {
    return `${reason} (${timeSeconds.toFixed(3)}s)`;
  }
  if (reason === "OLE") {
    return t("stress.verdict.OLE");
  }
  return reason;
}

function formatRuntimeSeconds(timeSeconds: number | null | undefined): string | null {
  if (typeof timeSeconds !== "number" || !Number.isFinite(timeSeconds)) return null;
  return timeSeconds.toFixed(3);
}

function AttemptedCasesSection({
  cases,
  total,
  status,
  problemType,
  externalId,
  showSourceLinks,
}: {
  cases: AttemptedCase[];
  total: number;
  status: "found" | "not_found";
  problemType: string;
  externalId: string;
  showSourceLinks: boolean;
}) {
  const { t } = useI18n();
  const [open, setOpen] = useState(false);
  if (total === 0 && cases.length === 0) return null;

  const titleKey = status === "found" ? "stress.attempted.found" : "stress.attempted.notFound";
  if (cases.length === 0) {
    return (
      <div className="rounded-md border bg-muted/20 px-4 py-3">
        <p className="text-sm font-medium">{t(titleKey, { n: total })}</p>
        <p className="mt-1 text-sm text-muted-foreground">
          {t("stress.attempted.unavailable")}
        </p>
      </div>
    );
  }

  return (
    <div className="rounded-md border bg-muted/20">
      <button
        type="button"
        onClick={() => setOpen(!open)}
        className="flex w-full items-center justify-between gap-3 px-4 py-3 text-left"
        aria-expanded={open}
      >
        <span className="text-sm font-medium">
          {t(titleKey, { n: total })}
        </span>
        <ChevronDown
          className={cn(
            "h-4 w-4 shrink-0 text-muted-foreground transition-transform",
            open && "rotate-180",
          )}
        />
      </button>
      {open && (
        <ul className="divide-y border-t font-mono text-sm">
          {cases.map((c, i) => (
            <AttemptedRow
              key={`${c.stage}:${c.id}:${c.seed ?? ""}:${i}`}
              attempted={c}
              problemType={problemType}
              externalId={externalId}
              showSourceLinks={showSourceLinks}
            />
          ))}
        </ul>
      )}
    </div>
  );
}

function AttemptedRow({
  attempted,
  problemType,
  externalId,
  showSourceLinks,
}: {
  attempted: AttemptedCase;
  problemType: string;
  externalId: string;
  showSourceLinks: boolean;
}) {
  const { t } = useI18n();
  const url = showSourceLinks ? sourceFileUrl(problemType, externalId, attempted.id) : null;
  return (
    <li className="flex flex-wrap items-baseline gap-x-3 gap-y-1 px-4 py-2">
      {url ? (
        <a href={url} target="_blank" rel="noreferrer" className="text-foreground hover:underline">
          {attempted.id}
        </a>
      ) : (
        <span className="text-foreground">{attempted.id}</span>
      )}
      {attempted.seed && (
        <span className="text-xs text-muted-foreground">
          {t("stress.seed")}: {attempted.seed}
        </span>
      )}
    </li>
  );
}

function TextBlock({ title, tt }: { title: string; tt: TextWithMetadata }) {
  const { t } = useI18n();
  const truncatedLabel = formatTruncatedLabel(tt, t);
  return (
    <div className="rounded-md border bg-background">
      <div className="flex items-center justify-between gap-2 border-b px-3 py-2">
        <span className="text-sm font-medium text-muted-foreground">{title}</span>
        <CopyButton content={tt.text} />
      </div>
      <pre className="max-h-72 overflow-x-auto whitespace-pre px-3 py-2 font-mono text-[15px] leading-5">{tt.text ? tt.text : <em className="text-muted-foreground">{t("stress.empty")}</em>}</pre>
      {truncatedLabel && (
        <div className="border-t px-3 py-1 text-xs text-muted-foreground">
          {truncatedLabel}
        </div>
      )}
    </div>
  );
}

function plainText(text: string): TextWithMetadata {
  return {
    text,
    metadata: {
      characterCount: text.length,
      lineCount: countLines(text),
      truncated: false,
    },
  };
}

function countLines(text: string): number {
  if (!text) return 0;
  return text.endsWith("\n") ? text.split("\n").length - 1 : text.split("\n").length;
}

function formatTruncatedLabel(
  tt: TextWithMetadata,
  t: (key: TranslationKey, values?: Record<string, string | number>) => string,
): string | null {
  const metadata = tt.metadata;
  if (!metadata.truncated) return null;
  if (metadata.truncatedBy === "line") {
    return t("stress.truncated.line", {
      line: metadata.truncatedAtLine ?? 0,
      lines: metadata.lineCount,
      characters: metadata.characterCount,
    });
  }
  return t("stress.truncated.character", {
    at: metadata.truncatedAtCharacter ?? tt.text.length,
    lines: metadata.lineCount,
    characters: metadata.characterCount,
  });
}

function CopyButton({ content }: { content: string }): ReactNode {
  const { t } = useI18n();
  const [copied, setCopied] = useState(false);
  const timer = useRef<number | null>(null);

  useEffect(() => {
    return () => {
      if (timer.current) window.clearTimeout(timer.current);
    };
  }, []);

  async function handleCopy() {
    try {
      await navigator.clipboard.writeText(content);
      setCopied(true);
      if (timer.current) window.clearTimeout(timer.current);
      timer.current = window.setTimeout(() => setCopied(false), 1500);
    } catch (error) {
      console.error("Copy error:", error);
    }
  }

  return (
    <button
      type="button"
      onClick={handleCopy}
      className="inline-flex h-6 w-6 items-center justify-center rounded text-muted-foreground transition-colors hover:bg-accent hover:text-foreground"
      aria-label={copied ? t("stress.copied") : t("stress.copy")}
      title={copied ? t("stress.copied") : t("stress.copy")}
    >
      {copied ? <ClipboardCheck className="h-3.5 w-3.5" /> : <Clipboard className="h-3.5 w-3.5" />}
    </button>
  );
}
