import { useQuery } from "@tanstack/react-query";
import { Link } from "react-router-dom";

import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { getStats } from "../api";
import { useI18n, type Locale } from "../lib/i18n";
import { problemHref } from "../lib/problemLinks";
import type { StatsBucket, StatsResponse } from "../types";

export default function StatsPage() {
  const { locale, t } = useI18n();
  const query = useQuery({ queryKey: ["stats"], queryFn: getStats });

  if (query.isPending) {
    return <p className="text-sm text-muted-foreground">{t("stats.loading")}</p>;
  }
  if (!query.data) {
    return <StatsUnavailable title={t("stats.title")} message={t("stats.unavailable")} />;
  }

  return <StatsContent stats={query.data} locale={locale} />;
}

export function StatsUnavailable({ title, message }: { title: string; message: string }) {
  return (
    <section className="space-y-2">
      <h1 className="text-3xl font-semibold">{title}</h1>
      <p className="text-sm text-muted-foreground">{message}</p>
    </section>
  );
}

function StatsContent({ stats, locale }: { stats: StatsResponse; locale: Locale }) {
  const { t } = useI18n();
  return (
    <section className="space-y-6">
      <header className="space-y-2">
        <h1 className="text-3xl font-semibold">{t("stats.title")}</h1>
        <p className="text-muted-foreground">{t("stats.lastSevenDays")}</p>
        <p className="text-4xl font-semibold tabular-nums">{stats.total.toLocaleString()}</p>
      </header>

      <Card>
        <CardContent className="pt-6">
          <HourlyChart
            buckets={stats.buckets}
            label={t("stats.chartLabel")}
            countLabel={t("stats.executions")}
            locale={locale}
          />
        </CardContent>
      </Card>

      <Card>
        <CardHeader>
          <CardTitle className="text-lg">{t("stats.topProblems")}</CardTitle>
        </CardHeader>
        <CardContent>
          {stats.topProblems.length === 0 ? (
            <p className="text-sm text-muted-foreground">{t("stats.noExecutions")}</p>
          ) : (
            <div className="overflow-x-auto">
              <table className="w-full text-left text-sm">
                <thead className="border-b text-muted-foreground">
                  <tr>
                    <th className="px-2 py-2 font-medium">{t("stats.rank")}</th>
                    <th className="px-2 py-2 font-medium">{t("stats.problem")}</th>
                    <th className="px-2 py-2 text-right font-medium">{t("stats.executions")}</th>
                  </tr>
                </thead>
                <tbody>
                  {stats.topProblems.map((problem, index) => (
                    <tr key={`${problem.problemType}/${problem.externalId}`} className="border-b last:border-0">
                      <td className="px-2 py-2 tabular-nums">{index + 1}</td>
                      <td className="px-2 py-2">
                        <Link
                          to={problemHref(problem)}
                          className="inline-flex flex-wrap items-baseline gap-x-2"
                        >
                          <span
                            data-problem-slug=""
                            className="font-mono text-xs text-muted-foreground"
                          >
                            {problem.problemType}/{problem.externalId}
                          </span>
                          {problem.title ? (
                            <span data-problem-title="" className="font-medium text-foreground">
                              {problem.title}
                            </span>
                          ) : null}
                        </Link>
                      </td>
                      <td className="px-2 py-2 text-right tabular-nums">
                        {problem.count.toLocaleString()}
                      </td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
          )}
        </CardContent>
      </Card>

    </section>
  );
}

export function HourlyChart({
  buckets,
  label,
  countLabel,
  locale,
}: {
  buckets: StatsBucket[];
  label: string;
  countLabel: string;
  locale: Locale;
}) {
  const maximum = Math.max(1, ...buckets.map((bucket) => bucket.count));
  const formatter = bucketTimeFormatter(locale);
  const numberFormatter = new Intl.NumberFormat(locale === "ko" ? "ko-KR" : "en-US");
  return (
    <figure aria-label={label}>
      <div
        className="grid h-48 items-end gap-px border-b border-l px-1 pt-2"
        style={{ gridTemplateColumns: `repeat(${buckets.length}, minmax(0, 1fr))` }}
      >
        {buckets.map((bucket, index) => {
          const start = new Date(bucket.startUtc);
          const end = new Date(start.getTime() + 60 * 60 * 1000);
          const tooltip = `${formatter.format(start)} – ${formatter.format(end)} · ${countLabel}: ${numberFormatter.format(bucket.count)}`;
          const tooltipPosition =
            index === 0
              ? "left-0"
              : index === buckets.length - 1
                ? "right-0"
                : "left-1/2 -translate-x-1/2";
          return (
            <span
              key={bucket.startUtc}
              data-stat-bar=""
              role="img"
              tabIndex={0}
              aria-label={tooltip}
              className={`group relative min-h-px focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-ring ${index === buckets.length - 1 ? "bg-primary/40" : "bg-primary"}`}
              style={{ height: `${(bucket.count / maximum) * 100}%` }}
            >
              <span
                data-stat-tooltip=""
                role="tooltip"
                className={`pointer-events-none absolute bottom-full z-10 mb-2 hidden w-max max-w-64 rounded-md border bg-popover px-2 py-1 text-xs font-normal text-popover-foreground opacity-100 shadow-md group-hover:block group-focus-visible:block ${tooltipPosition}`}
              >
                {tooltip}
              </span>
            </span>
          );
        })}
      </div>
      {buckets.length > 0 && (
        <figcaption className="mt-2 flex justify-between text-xs text-muted-foreground">
          <time dateTime={buckets[0].startUtc}>{formatter.format(new Date(buckets[0].startUtc))}</time>
          <time dateTime={buckets.at(-1)?.startUtc}>
            {formatter.format(new Date(buckets.at(-1)?.startUtc ?? ""))}
          </time>
        </figcaption>
      )}
    </figure>
  );
}

function bucketTimeFormatter(locale: Locale) {
  return new Intl.DateTimeFormat(locale === "ko" ? "ko-KR" : "en-US", {
    dateStyle: "short",
    timeStyle: "short",
    hourCycle: "h23",
  });
}
