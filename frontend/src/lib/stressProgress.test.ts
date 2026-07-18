import { describe, expect, it } from "vitest";

import { recordCompileProgress } from "./stressProgress";

describe("recordCompileProgress", () => {
  it("retains each compiled source once as later stages arrive", () => {
    const target = { stage: "compiling", source: "target" } as const;
    const correct = { stage: "compiling", source: "correct" } as const;

    const afterTarget = recordCompileProgress([], target);
    expect(recordCompileProgress(afterTarget, target)).toBe(afterTarget);

    const afterCorrect = recordCompileProgress(afterTarget, correct);
    expect(afterCorrect).toEqual([target, correct]);
    expect(
      recordCompileProgress(afterCorrect, {
        stage: "stress_running",
        completedIterations: 1,
      }),
    ).toBe(afterCorrect);
  });
});
