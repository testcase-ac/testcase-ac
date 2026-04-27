import fs from "node:fs";

const reportPath = process.argv[2];
if (!reportPath) {
  console.error("usage: node tests/verify/write_summary.mjs <report.json>");
  process.exit(2);
}

const raw = fs.readFileSync(reportPath, "utf8");
const parsed = JSON.parse(raw);
const reports = Array.isArray(parsed) ? parsed : [parsed];

const ok = reports.filter((report) => report.status === "ok").length;
const failed = reports.filter((report) => report.status !== "ok").length;
const findings = reports.reduce((sum, report) => sum + (report.findings?.length ?? 0), 0);

const lines = [
  "## Problem Verification",
  "",
  `Verified ${reports.length} problem${reports.length === 1 ? "" : "s"}: ${ok} succeeded, ${failed} failed.`,
  "",
  "| Problem | Status | Samples | Findings |",
  "| --- | --- | ---: | ---: |",
];

for (const report of reports) {
  const problem = report.problemPath ?? `${report.problemType ?? ""}/${report.externalId ?? ""}`;
  lines.push(`| ${escapeMarkdown(problem)} | ${report.status} | ${report.sampledCasesCount ?? 0} | ${report.findings?.length ?? 0} |`);
}

if (findings > 0) {
  lines.push("", "### Findings", "");
  for (const report of reports) {
    for (const finding of report.findings ?? []) {
      const problem = report.problemPath ?? `${report.problemType ?? ""}/${report.externalId ?? ""}`;
      const location = finding.filename || "(problem)";
      const seed = finding.seed === undefined ? "" : ` seed=${finding.seed}`;
      lines.push(`- **${escapeMarkdown(problem)}** ${finding.severity}/${finding.stage} ${escapeMarkdown(location)}${seed}: ${escapeMarkdown(finding.message)}`);
    }
  }
}

const markdown = `${lines.join("\n")}\n`;
console.log(markdown);

const summaryPath = process.env.GITHUB_STEP_SUMMARY;
if (summaryPath) {
  fs.appendFileSync(summaryPath, markdown);
}

function escapeMarkdown(value) {
  return String(value).replaceAll("|", "\\|").replaceAll("\n", " ");
}
