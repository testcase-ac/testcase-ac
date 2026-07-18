import { afterEach, describe, expect, it, vi } from "vitest";

import { submitStress } from "./api";
import type { StressProgress, StressRequest } from "./types";

const request: StressRequest = {
  targetCode: "int main() {}",
  targetCodeLang: "cpp23",
};

function streamResponse(chunks: Uint8Array[]): Response {
  return new Response(
    new ReadableStream({
      start(controller) {
        for (const chunk of chunks) controller.enqueue(chunk);
        controller.close();
      },
    }),
    { status: 200, headers: { "Content-Type": "application/x-ndjson" } },
  );
}

afterEach(() => {
  vi.unstubAllGlobals();
});

describe("stress progress stream", () => {
  it("preserves split UTF-8 and JSON records across network chunks", async () => {
    const text =
      `${JSON.stringify({ type: "progress", progress: { stage: "compiling", source: "singlegen", sourceId: "한글.cpp" } })}\n` +
      `${JSON.stringify({ type: "result", result: { requestId: "request-1", runtimeSeconds: 1, status: "not_found" } })}\n`;
    const bytes = new TextEncoder().encode(text);
    const koreanStart = text.indexOf("한");
    const split = new TextEncoder().encode(text.slice(0, koreanStart)).length + 1;
    vi.stubGlobal("fetch", vi.fn(async () => streamResponse([bytes.slice(0, split), bytes.slice(split)])));

    const progress: StressProgress[] = [];
    const result = await submitStress("boj", "1000", request, (update) => progress.push(update));

    expect(progress).toEqual([{ stage: "compiling", source: "singlegen", sourceId: "한글.cpp" }]);
    expect(result).toMatchObject({ requestId: "request-1", status: "not_found" });
  });

  it("forwards Finalizing without delaying the final result", async () => {
    const payload = new TextEncoder().encode(
      `${JSON.stringify({ type: "progress", progress: { stage: "finalizing" } })}\n` +
        `${JSON.stringify({ type: "result", result: { requestId: "request-2", runtimeSeconds: 1, status: "not_found" } })}\n`,
    );
    vi.stubGlobal("fetch", vi.fn(async () => streamResponse([payload])));
    vi.stubGlobal("document", { visibilityState: "visible" });
    const requestAnimationFrame = vi.fn(() => {
      throw new Error("the API layer must not wait for a browser paint");
    });
    vi.stubGlobal("requestAnimationFrame", requestAnimationFrame);

    const events: string[] = [];
    const result = await submitStress("boj", "1000", request, (update) => {
      events.push(update.stage);
    });
    events.push("resolved");

    expect(events).toEqual(["finalizing", "resolved"]);
    expect(result).toMatchObject({ requestId: "request-2" });
    expect(requestAnimationFrame).not.toHaveBeenCalled();
  });
});
