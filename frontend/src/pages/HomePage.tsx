import { keepPreviousData, useQuery } from "@tanstack/react-query";
import { ChevronRight, Search } from "lucide-react";
import { useState } from "react";
import { Link } from "react-router-dom";

import { Badge } from "@/components/ui/badge";
import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { listProblems } from "../api";
import { useI18n } from "../lib/i18n";
import { problemHref } from "../lib/problemLinks";

const PAGE_SIZE = 50;

export default function HomePage() {
  const { t } = useI18n();
  const [query, setQuery] = useState("");
  const [pageIndex, setPageIndex] = useState(0);
  const [pageCursors, setPageCursors] = useState<string[]>([""]);
  const currentCursor = pageCursors[pageIndex] ?? "";
  const problemsQuery = useQuery({
    queryKey: ["problems", { query, cursor: currentCursor, limit: PAGE_SIZE }],
    queryFn: () => listProblems({ q: query, limit: PAGE_SIZE, cursor: currentCursor }),
    placeholderData: keepPreviousData,
  });
  const problems = problemsQuery.data?.problems ?? [];
  const problemTypes = problemsQuery.data?.problemTypes ?? [];
  const nextCursor = problemsQuery.data?.nextCursor ?? null;
  const totalProblems = problemsQuery.data?.total ?? null;
  const loading = problemsQuery.isPending || problemsQuery.isPlaceholderData;
  const error = problemsQuery.error instanceof Error ? problemsQuery.error.message : null;

  function onQueryChange(value: string) {
    setQuery(value);
    setPageIndex(0);
    setPageCursors([""]);
  }

  function goToPreviousPage() {
    setPageIndex((value) => Math.max(0, value - 1));
  }

  function goToNextPage() {
    if (!nextCursor) return;
    setPageCursors((value) => {
      const next = value.slice(0, pageIndex + 1);
      next[pageIndex + 1] = nextCursor;
      return next;
    });
    setPageIndex((value) => value + 1);
  }

  return (
    <section className="space-y-6">
      <div className="space-y-2">
        <h1 className="text-3xl font-semibold">{t("home.title")}</h1>
        <p className="max-w-3xl text-muted-foreground">{t("home.subtitle")}</p>
        <Button asChild variant="secondary" size="sm">
          <Link to="/problems/boj/1000">{t("home.example.boj1000")}</Link>
        </Button>
      </div>
      <div className="flex flex-wrap items-center justify-between gap-3 border-y py-3">
        <div>
          <div className="text-sm font-medium">{t("home.custom.title")}</div>
          <p className="text-sm text-muted-foreground">{t("home.custom.subtitle")}</p>
        </div>
        <Button asChild variant="secondary" size="sm">
          <Link to="/custom-invocation">{t("home.custom.link")}</Link>
        </Button>
      </div>
      {!loading && !error && problemTypes.length > 0 && (
        <div className="space-y-3">
          <h2 className="text-lg font-semibold">{t("home.problemTypes")}</h2>
          <div className="grid gap-2 sm:grid-cols-2 lg:grid-cols-3">
            {problemTypes.map((problemType) => (
              <Link
                key={problemType.problemType}
                to={`/${problemType.problemType}`}
                className="flex items-center justify-between rounded-md border bg-card px-4 py-3 text-card-foreground transition-colors hover:border-primary hover:no-underline"
              >
                <span className="min-w-0">
                  <span className="block truncate font-medium">
                    {problemType.label || problemType.problemType}
                  </span>
                  <span className="text-sm text-muted-foreground">
                    {t("home.problemType.count", { count: problemType.total })}
                  </span>
                </span>
                <ChevronRight className="size-4 shrink-0 text-muted-foreground" />
              </Link>
            ))}
          </div>
        </div>
      )}
      <div className="relative">
        <Search
          aria-hidden="true"
          className="pointer-events-none absolute left-3 top-1/2 size-4 -translate-y-1/2 text-muted-foreground"
        />
        <Input
          type="search"
          className="pl-9"
          placeholder={t("home.search.placeholder")}
          value={query}
          onChange={(e) => onQueryChange(e.target.value)}
        />
      </div>
      {loading && <p className="text-sm text-muted-foreground">{t("home.state.loading")}</p>}
      {error && <p className="text-sm font-medium text-destructive">{error}</p>}
      {!loading && !error && problems.length === 0 && (
        <p className="text-sm text-muted-foreground">{t("home.state.empty")}</p>
      )}
      {!error && (
        <PaginationControls
          pageIndex={pageIndex}
          shown={problems.length}
          total={totalProblems}
          loading={loading}
          canPrevious={pageIndex > 0}
          canNext={Boolean(nextCursor)}
          onPrevious={goToPreviousPage}
          onNext={goToNextPage}
        />
      )}
      <ul className="space-y-2">
        {problems.map((p) => (
          <li key={`${p.problemType}/${p.externalId}`}>
            <Link
              to={problemHref(p)}
              aria-label={`${p.problemType} ${p.externalId} ${p.title ?? t("home.untitled")}`}
              className="grid grid-cols-[52px_72px_minmax(0,1fr)] items-center gap-2 rounded-md border bg-card p-3 text-card-foreground transition-colors hover:border-primary hover:no-underline sm:grid-cols-[84px_96px_1fr] sm:p-4"
            >
              <Badge variant="secondary" className="w-fit lowercase">
                {p.problemType}
              </Badge>
              <span className="font-mono text-sm text-muted-foreground">{p.externalId}</span>
              <span className="min-w-0 truncate font-medium">{p.title ?? t("home.untitled")}</span>
            </Link>
          </li>
        ))}
      </ul>
      {!error && problems.length > 0 && (
        <PaginationControls
          pageIndex={pageIndex}
          shown={problems.length}
          total={totalProblems}
          loading={loading}
          canPrevious={pageIndex > 0}
          canNext={Boolean(nextCursor)}
          onPrevious={goToPreviousPage}
          onNext={goToNextPage}
        />
      )}
    </section>
  );
}

function PaginationControls({
  pageIndex,
  shown,
  total,
  loading,
  canPrevious,
  canNext,
  onPrevious,
  onNext,
}: {
  pageIndex: number;
  shown?: number;
  total?: number | null;
  loading: boolean;
  canPrevious: boolean;
  canNext: boolean;
  onPrevious: () => void;
  onNext: () => void;
}) {
  const { t } = useI18n();
  return (
    <div className="flex flex-wrap items-center justify-between gap-3">
      <span className="text-sm text-muted-foreground">
        {t("pagination.page", { page: pageIndex + 1 })}
        {shown && shown > 0 && total !== null && total !== undefined
          ? ` · ${t("pagination.shown", { count: shown, total })}`
          : ""}
      </span>
      <div className="flex gap-2">
        <Button
          type="button"
          variant="outline"
          size="sm"
          className="w-24"
          onClick={onPrevious}
          disabled={loading || !canPrevious}
        >
          {t("pagination.previous")}
        </Button>
        <Button
          type="button"
          variant="outline"
          size="sm"
          className="w-24"
          onClick={onNext}
          disabled={loading || !canNext}
        >
          {t("pagination.next")}
        </Button>
      </div>
    </div>
  );
}
