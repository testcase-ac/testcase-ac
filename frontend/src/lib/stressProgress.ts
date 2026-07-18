import type { StressProgress } from "../types";

export type DisplayedStressProgress = { stage: "preparing" | "completed" } | StressProgress;

export function recordCompileProgress(
  previous: StressProgress[],
  next: { stage: "preparing" } | StressProgress,
): StressProgress[] {
  if (next.stage !== "compiling") return previous;
  if (
    previous.some(
      (item) => item.source === next.source && item.sourceId === next.sourceId,
    )
  ) {
    return previous;
  }
  return [...previous, next];
}
