import { Check, ChevronDown, LoaderCircle } from "lucide-react";

import type { TranslationKey } from "../lib/i18n";
import type { DisplayedStressProgress } from "../lib/stressProgress";
import type { ProblemDetail, StressProgress } from "../types";

function progressSourceLabel(
  progress: StressProgress,
  problem: Pick<ProblemDetail, "checker">,
  selectedCorrectCode: string | null,
  t: (key: TranslationKey, values?: Record<string, string | number>) => string,
): string {
  const unknown = t("problem.progress.source.unknown");
  switch (progress.source) {
    case "target":
      return t("problem.progress.source.target");
    case "correct":
      return selectedCorrectCode ?? unknown;
    case "checker":
      return problem.checker?.filename ?? unknown;
    case "generator":
    case "singlegen":
      return progress.sourceId ?? unknown;
    default:
      return unknown;
  }
}

function progressLabel(
  progress: DisplayedStressProgress,
  problem: Pick<ProblemDetail, "checker">,
  selectedCorrectCode: string | null,
  t: (key: TranslationKey, values?: Record<string, string | number>) => string,
): string {
  switch (progress.stage) {
    case "preparing":
      return t("problem.progress.preparing");
    case "compiling":
      return t("problem.progress.compiling", {
        source: progressSourceLabel(progress, problem, selectedCorrectCode, t),
      });
    case "stress_running":
      return t("problem.progress.running", {
        completed: progress.completedIterations ?? 0,
      });
    case "finalizing":
      return t("problem.progress.finalizing");
    case "completed":
      return t("problem.progress.stressDone");
  }
}

function progressAnnouncementLabel(
  progress: DisplayedStressProgress,
  problem: Pick<ProblemDetail, "checker">,
  selectedCorrectCode: string | null,
  t: (key: TranslationKey, values?: Record<string, string | number>) => string,
): string {
  if (progress.stage !== "stress_running") {
    return progressLabel(progress, problem, selectedCorrectCode, t);
  }

  const completedIterations = progress.completedIterations ?? 0;
  return progressLabel(
    { ...progress, completedIterations: Math.floor(completedIterations / 10) * 10 },
    problem,
    selectedCorrectCode,
    t,
  );
}

export function SubmissionProgress({
  progress,
  compileProgress,
  problem,
  selectedCorrectCode,
  t,
}: {
  progress: DisplayedStressProgress;
  compileProgress: StressProgress[];
  problem: Pick<ProblemDetail, "checker">;
  selectedCorrectCode: string | null;
  t: (key: TranslationKey, values?: Record<string, string | number>) => string;
}) {
  const compiling = progress.stage === "compiling";
  const compileList = (
    <ul className="mr-1.5 mt-1.5 space-y-1 border-r border-border/70 pr-4 text-right text-[11px] text-muted-foreground">
      {compileProgress.map((item, index) => {
        const current = compiling && index === compileProgress.length - 1;
        return (
          <li
            key={`${item.source ?? "unknown"}:${item.sourceId ?? ""}`}
            className="flex items-center justify-end gap-2"
          >
            <span>{progressSourceLabel(item, problem, selectedCorrectCode, t)}</span>
            {current ? (
              <LoaderCircle className="size-3 shrink-0 animate-spin text-primary" aria-hidden />
            ) : (
              <Check className="size-3 shrink-0 text-emerald-600 dark:text-emerald-400" aria-hidden />
            )}
          </li>
        );
      })}
    </ul>
  );

  return (
    <div className="w-full max-w-xs text-xs" data-stress-progress={progress.stage}>
      <div className="space-y-2">
        {progress.stage === "preparing" && (
          <div className="flex items-center justify-end gap-2 text-right text-muted-foreground">
            <span>{t("problem.progress.preparing")}</span>
            <LoaderCircle className="size-3.5 animate-spin text-primary" aria-hidden />
          </div>
        )}

        {compiling && (
          <div>
            <div className="flex items-center justify-end gap-2 text-right font-medium text-foreground">
              <span>{t("problem.progress.compilingTitle")}</span>
              <LoaderCircle className="size-3.5 animate-spin text-primary" aria-hidden />
            </div>
            {compileList}
          </div>
        )}

        {(progress.stage === "stress_running" ||
          progress.stage === "finalizing" ||
          progress.stage === "completed") &&
          (compileProgress.length > 0 ? (
            <details className="group">
              <summary className="flex cursor-pointer list-none items-center justify-end gap-2 text-right font-medium text-muted-foreground select-none [&::-webkit-details-marker]:hidden">
                <span>{t("problem.progress.compileComplete")}</span>
                <Check className="size-3.5 shrink-0 text-emerald-600 dark:text-emerald-400" aria-hidden />
                <ChevronDown className="size-3.5 transition-transform group-open:rotate-180" aria-hidden />
              </summary>
              {compileList}
            </details>
          ) : (
            <div className="flex items-center justify-end gap-2 text-right font-medium text-muted-foreground">
              <span>{t("problem.progress.compileComplete")}</span>
              <Check className="size-3.5 text-emerald-600 dark:text-emerald-400" aria-hidden />
            </div>
          ))}

        {progress.stage === "stress_running" && (
          <div className="flex items-center justify-end gap-2 text-right font-medium text-foreground">
            <span>
              {t("problem.progress.running", {
                completed: progress.completedIterations ?? 0,
              })}
            </span>
            <LoaderCircle className="size-3.5 animate-spin text-primary" aria-hidden />
          </div>
        )}

        {progress.stage === "finalizing" && (
          <>
            <div className="flex items-center justify-end gap-2 text-right font-medium text-muted-foreground">
              <span>{t("problem.progress.stressDone")}</span>
              <Check className="size-3.5 text-emerald-600 dark:text-emerald-400" aria-hidden />
            </div>
            <div className="flex items-center justify-end gap-2 text-right font-medium text-foreground">
              <span>{t("problem.progress.finalizing")}</span>
              <LoaderCircle className="size-3.5 animate-spin text-primary" aria-hidden />
            </div>
          </>
        )}

        {progress.stage === "completed" && (
          <div className="flex items-center justify-end gap-2 text-right font-medium text-muted-foreground">
            <span>{t("problem.progress.stressDone")}</span>
            <Check className="size-3.5 text-emerald-600 dark:text-emerald-400" aria-hidden />
          </div>
        )}
      </div>
      <p className="sr-only" role="status" aria-live="polite" aria-atomic="true">
        {progressAnnouncementLabel(progress, problem, selectedCorrectCode, t)}
      </p>
    </div>
  );
}
