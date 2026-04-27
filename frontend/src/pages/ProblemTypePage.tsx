import { keepPreviousData, useQuery } from "@tanstack/react-query";
import { ChevronRight } from "lucide-react";
import { Suspense, lazy } from "react";
import { Link, useParams } from "react-router-dom";

import { Badge } from "@/components/ui/badge";
import { listProblems } from "../api";
import { useI18n } from "../lib/i18n";
import { problemHref } from "../lib/problemLinks";
import {
  compareProblems,
  compareSegment,
  pageTitle,
  problemTypeLabel,
  segmentLabel,
} from "../lib/typeMetadata";
import type { ProblemSummary, TypeMetadata } from "../types";

const PAGE_SIZE = 500;
const ProblemWorkspace = lazy(() =>
  import("./ProblemPage").then((module) => ({ default: module.ProblemWorkspace })),
);

export default function ProblemTypePage() {
  const { problemType = "" } = useParams();
  const currentPath = normalizePath(useParams()["*"] ?? "");
  return <ProblemTypeBrowser problemType={problemType} currentPath={currentPath} />;
}

function ProblemTypeBrowser({ problemType, currentPath }: { problemType: string; currentPath: string }) {
  const { t } = useI18n();
  const segments = currentPath ? currentPath.split("/") : [];
  const problemsQuery = useQuery({
    queryKey: ["problems", { problemType, limit: PAGE_SIZE }],
    queryFn: () => listProblems({ problemType, limit: PAGE_SIZE }),
    enabled: Boolean(problemType),
    placeholderData: keepPreviousData,
  });
  const problems = problemsQuery.data?.problems ?? [];
  const totalProblems = problemsQuery.data?.total ?? null;
  const typeMetadata = problemsQuery.data?.typeMetadata;
  const loading = problemsQuery.isPending || problemsQuery.isPlaceholderData;
  const error = problemsQuery.error instanceof Error ? problemsQuery.error.message : null;
  const exactProblem = currentPath
    ? problems.find((problem) => problem.externalId === currentPath)
    : null;

  if (!loading && !error && exactProblem) {
    return (
      <Suspense fallback={<p className="text-sm text-muted-foreground">{t("problem.loading")}</p>}>
        <ProblemWorkspace problemType={problemType} externalId={currentPath} typeMetadata={typeMetadata} />
      </Suspense>
    );
  }

  const scopedProblems = problems
    .filter((problem) => isInScope(problem.externalId, currentPath))
    .sort((a, b) => compareProblems(typeMetadata, a, b));
  const childSegments = immediateCategoryChildren(typeMetadata, scopedProblems, currentPath, segments.length);
  const problemCount = currentPath ? scopedProblems.length : totalProblems ?? scopedProblems.length;

  return (
    <section className="space-y-6">
      <div className="space-y-2">
        <nav className="flex flex-wrap items-center gap-1 text-sm text-muted-foreground">
          <Link to={`/${problemType}`} className="font-medium text-foreground">
            {problemTypeLabel(problemType, typeMetadata)}
          </Link>
          {segments.map((segment, index) => {
            const href = `/${problemType}/${segments.slice(0, index + 1).join("/")}`;
            return (
              <span key={href} className="flex items-center gap-1">
                <ChevronRight className="size-4" />
                <Link to={href}>{segmentLabel(typeMetadata, segment, index)}</Link>
              </span>
            );
          })}
        </nav>
        <h1 className="text-3xl font-semibold">{pageTitle(problemType, segments, typeMetadata)}</h1>
      </div>

      {loading && <p className="text-sm text-muted-foreground">{t("home.state.loading")}</p>}
      {error && <p className="text-sm font-medium text-destructive">{error}</p>}

      {!loading && !error && childSegments.length > 0 && (
        <div className="space-y-3">
          <h2 className="text-lg font-semibold">{t("catalog.categories")}</h2>
          <div className="grid gap-2 sm:grid-cols-2 lg:grid-cols-3">
            {childSegments.map((segment) => {
              const href = `/${problemType}/${[...segments, segment].join("/")}`;
              return (
                <Link
                  key={href}
                  to={href}
                  className="flex items-center justify-between rounded-md border bg-card px-4 py-3 text-card-foreground transition-colors hover:border-primary hover:no-underline"
                >
                  <span className="font-medium">
                    {segmentLabel(typeMetadata, segment, segments.length)}
                  </span>
                  <ChevronRight className="size-4 text-muted-foreground" />
                </Link>
              );
            })}
          </div>
        </div>
      )}

      {!loading && !error && (
        <div className="space-y-3">
          <h2 className="text-lg font-semibold">
            {t("catalog.problems", { count: problemCount })}
          </h2>
          {scopedProblems.length === 0 ? (
            <p className="text-sm text-muted-foreground">{t("home.state.empty")}</p>
          ) : (
            <ul className="space-y-2">
              {scopedProblems.map((problem) => (
                <li key={problem.externalId}>
                  <Link
                    to={problemHref(problem)}
                    className="grid grid-cols-[minmax(92px,auto)_minmax(0,1fr)] items-center gap-3 rounded-md border bg-card p-3 text-card-foreground transition-colors hover:border-primary hover:no-underline sm:grid-cols-[150px_1fr]"
                  >
                    <Badge variant="secondary" className="w-fit font-mono">
                      {problem.externalId}
                    </Badge>
                    <span className="min-w-0 truncate font-medium">
                      {problem.title ?? t("home.untitled")}
                    </span>
                  </Link>
                </li>
              ))}
            </ul>
          )}
        </div>
      )}
    </section>
  );
}

function normalizePath(path: string): string {
  return path.split("/").filter(Boolean).join("/");
}

function isInScope(externalId: string, currentPath: string): boolean {
  if (!currentPath) return true;
  return externalId === currentPath || externalId.startsWith(`${currentPath}/`);
}

function immediateCategoryChildren(
  typeMetadata: TypeMetadata | undefined,
  problems: ProblemSummary[],
  currentPath: string,
  depth: number,
): string[] {
  const children = new Set<string>();
  const problemIDs = new Set(problems.map((problem) => problem.externalId));
  for (const problem of problems) {
    const segments = problem.externalId.split("/");
    if (segments.length > depth) {
      const childSegment = segments[depth];
      const childPath = currentPath ? `${currentPath}/${childSegment}` : childSegment;
      if (!problemIDs.has(childPath)) {
        children.add(childSegment);
      }
    }
  }
  return [...children].sort((a, b) => compareSegment(typeMetadata, a, b, depth));
}
