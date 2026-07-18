import { renderToStaticMarkup } from "react-dom/server";
import { describe, expect, it } from "vitest";

import { SubmissionProgress } from "./SubmissionProgress";

describe("submission progress", () => {
  it("renders an unboxed completed state", () => {
    const html = renderToStaticMarkup(
      <SubmissionProgress
        progress={{ stage: "completed" }}
        compileProgress={[]}
        problem={{ checker: null }}
        selectedCorrectCode={null}
        t={(key) => key}
      />,
    );

    expect(html).toContain('data-stress-progress="completed"');
    expect(html).toContain("problem.progress.compileComplete");
    expect(html).not.toContain("problem.progress.compilingTitle");
    expect(html).toContain("problem.progress.stressDone");
    expect(html).toContain('class="w-full max-w-xs text-xs"');
    expect(html).not.toContain("animate-spin");
  });
});
