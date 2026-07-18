import type {
  HealthResponse,
  ProblemDetail,
  ProblemList,
  StressRequest,
  StressResponse,
  StressProgress,
  StatsResponse,
} from "./types";
import {
  STRESS_PROGRESS_SOURCE_VALUES,
  STRESS_PROGRESS_STAGE_VALUES,
} from "./generated/contracts";

const configuredApiBase = import.meta.env.VITE_API_BASE_URL?.trim();

if (!configuredApiBase && import.meta.env.PROD) {
  throw new Error("VITE_API_BASE_URL is required for production builds");
}

const API_BASE = (configuredApiBase || "http://localhost:8000").replace(/\/$/, "");

async function request<T>(path: string, init?: RequestInit): Promise<T> {
  const res = await fetch(`${API_BASE}${path}`, {
    ...init,
    headers: {
      "Content-Type": "application/json",
      ...(init?.headers ?? {}),
    },
  });
  if (!res.ok) {
    throw await responseError(res);
  }
  return (await res.json()) as T;
}

export class ApiError extends Error {
  constructor(public status: number, message: string) {
    super(message);
    this.name = "ApiError";
  }
}

export function getHealth(): Promise<HealthResponse> {
  return request<HealthResponse>("/api/health");
}

export function getStats(): Promise<StatsResponse> {
  return request<StatsResponse>("/api/stats");
}

export function listProblems(
  params: { q?: string; problemType?: string; limit?: number; cursor?: string } = {},
): Promise<ProblemList> {
  const qs = new URLSearchParams();
  if (params.q) qs.set("q", params.q);
  if (params.problemType) qs.set("problemType", params.problemType);
  if (params.limit) qs.set("limit", String(params.limit));
  if (params.cursor) qs.set("cursor", params.cursor);
  const suffix = qs.toString() ? `?${qs.toString()}` : "";
  return request<ProblemList>(`/api/problems${suffix}`);
}

export function getProblem(problemType: string, externalId: string): Promise<ProblemDetail> {
  return request<ProblemDetail>(
    `/api/problems/${encodeURIComponent(problemType)}/${encodeURIComponent(externalId)}`,
  );
}

export function submitStress(
  problemType: string,
  externalId: string,
  payload: StressRequest,
  onProgress: (progress: StressProgress) => void,
  signal?: AbortSignal,
): Promise<StressResponse> {
  return requestStressStream(
    `/api/problems/${encodeURIComponent(problemType)}/${encodeURIComponent(externalId)}/stress`,
    payload,
    onProgress,
    signal,
  );
}

export function submitCustomStress(payload: StressRequest): Promise<StressResponse> {
  return request<StressResponse>("/api/custom-invocation/stress", {
    method: "POST",
    body: JSON.stringify(payload),
  });
}

const progressStages = new Set<string>(STRESS_PROGRESS_STAGE_VALUES);
const progressSources = new Set<string>(STRESS_PROGRESS_SOURCE_VALUES);

async function requestStressStream(
  path: string,
  payload: StressRequest,
  onProgress: (progress: StressProgress) => void,
  signal?: AbortSignal,
): Promise<StressResponse> {
  const res = await fetch(`${API_BASE}${path}`, {
    method: "POST",
    body: JSON.stringify(payload),
    signal,
    headers: {
      Accept: "application/x-ndjson",
      "Content-Type": "application/json",
    },
  });
  if (!res.ok) throw await responseError(res);
  if (!res.body) throw new Error("The server returned no response body.");

  const reader = res.body.getReader();
  const decoder = new TextDecoder();
  let pending = "";
  let result: StressResponse | null = null;

  const readLine = (line: string) => {
    if (!line.trim()) return;
    if (result) throw new Error("The server returned data after the final result.");
    const record = JSON.parse(line) as {
      type?: unknown;
      progress?: unknown;
      result?: unknown;
    };
    if (record.type === "progress") {
      const progress = validProgress(record.progress);
      if (!progress) return;
      onProgress(progress);
      return;
    }
    if (record.type === "result" && record.result && typeof record.result === "object") {
      result = record.result as StressResponse;
      return;
    }
    throw new Error("The server returned an invalid progress response.");
  };

  for (;;) {
    const { done, value } = await reader.read();
    pending += done ? decoder.decode() : decoder.decode(value, { stream: true });
    let newline = pending.indexOf("\n");
    while (newline >= 0) {
      readLine(pending.slice(0, newline));
      pending = pending.slice(newline + 1);
      newline = pending.indexOf("\n");
    }
    if (done) break;
  }
  readLine(pending);
  if (!result) throw new Error("The server response ended before the final result.");
  return result;
}

function validProgress(value: unknown): StressProgress | null {
  if (!value || typeof value !== "object") return null;
  const candidate = value as Record<string, unknown>;
  if (typeof candidate.stage !== "string" || !progressStages.has(candidate.stage)) return null;
  if (
    candidate.source !== undefined &&
    (typeof candidate.source !== "string" || !progressSources.has(candidate.source))
  ) {
    return null;
  }
  if (candidate.sourceId !== undefined && typeof candidate.sourceId !== "string") return null;
  if (
    candidate.completedIterations !== undefined &&
    candidate.completedIterations !== null &&
    (!Number.isInteger(candidate.completedIterations) || Number(candidate.completedIterations) < 0)
  ) {
    return null;
  }
  return candidate as unknown as StressProgress;
}

async function responseError(res: Response): Promise<ApiError> {
  const text = await res.text();
  let detail = text;
  try {
    const body = JSON.parse(text);
    detail = typeof body?.detail === "string" ? body.detail : JSON.stringify(body);
  } catch {}
  return new ApiError(res.status, detail || res.statusText);
}
