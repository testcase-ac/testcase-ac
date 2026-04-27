import type { ProblemSummary } from "../types";

export function problemHref(problem: Pick<ProblemSummary, "problemType" | "externalId">): string {
  if (problem.externalId.includes("/")) {
    return `/${problem.problemType}/${problem.externalId}`;
  }
  return `/problems/${problem.problemType}/${problem.externalId}`;
}
