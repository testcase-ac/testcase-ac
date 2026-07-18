import { renderToStaticMarkup } from "react-dom/server";
import { MemoryRouter } from "react-router-dom";
import { describe, expect, it, vi } from "vitest";

import StatsPage, { HourlyChart, StatsUnavailable } from "./StatsPage";

const buckets = Array.from({ length: 168 }, (_, index) => ({
  startUtc: new Date(Date.UTC(2026, 6, 11, index)).toISOString(),
  count: index === 167 ? 4 : index % 3,
}));

vi.mock("@tanstack/react-query", () => ({
  useQuery: () => ({
    isPending: false,
    data: {
      total: 4,
      buckets: buckets.slice(0, 1),
      topProblems: [{ problemType: "boj", externalId: "1000", title: "A+B", count: 4 }],
    },
  }),
}));

vi.mock("../lib/i18n", () => ({
  useI18n: () => ({
    locale: "en",
    t: (key: string) => (key === "stats.hourlyData" ? "Hourly data" : key),
  }),
}));

describe("execution statistics presentation", () => {
  it("exposes every bar's local-time interval and exact count", () => {
    const chart = renderToStaticMarkup(
      <HourlyChart
        buckets={buckets}
        label="Hourly executions"
        countLabel="Executions"
        locale="en"
      />,
    );
    expect(chart.match(/data-stat-bar=/g)).toHaveLength(168);
    expect(chart.match(/data-stat-tooltip=/g)).toHaveLength(168);
    expect(chart.match(/tabindex="0"/g)).toHaveLength(168);
    expect(chart).toContain("Executions: 4");
    expect(chart).toContain("height:100%");
    expect(chart.match(/<time/g)).toHaveLength(2);
  });

  it("uses a 24-hour clock in chart labels and tooltips", () => {
    const startUtc = new Date(2026, 6, 11, 3).toISOString();
    const chart = renderToStaticMarkup(
      <HourlyChart
        buckets={[{ startUtc, count: 1 }]}
        label="시간별 실행 횟수"
        countLabel="실행 횟수"
        locale="ko"
      />,
    );
    expect(chart).toContain("03:00");
    expect(chart).not.toMatch(/오전|오후/);
  });

  it("separates problem slugs from titles and omits hourly data", () => {
    const html = renderToStaticMarkup(
      <MemoryRouter>
        <StatsPage />
      </MemoryRouter>,
    );
    expect(html).toContain('data-problem-slug=""');
    expect(html).toContain('data-problem-title=""');
    expect(html).not.toContain("Hourly data");
  });

  it("renders the temporary-unavailability state", () => {
    const html = renderToStaticMarkup(
      <StatsUnavailable title="Statistics" message="Statistics are temporarily unavailable." />,
    );
    expect(html).toContain("Statistics are temporarily unavailable.");
  });
});
