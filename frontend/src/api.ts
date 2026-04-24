import type {
  HealthResponse,
  ProblemDetail,
  ProblemList,
  StressRequest,
  StressResponse,
} from "./types";

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
    let detail: string | undefined;
    try {
      const body = await res.json();
      detail = typeof body?.detail === "string" ? body.detail : JSON.stringify(body);
    } catch {
      detail = await res.text();
    }
    throw new ApiError(res.status, detail || res.statusText);
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
): Promise<StressResponse> {
  return request<StressResponse>(
    `/api/problems/${encodeURIComponent(problemType)}/${encodeURIComponent(externalId)}/stress`,
    {
      method: "POST",
      body: JSON.stringify(payload),
    },
  );
}

export function submitCustomStress(payload: StressRequest): Promise<StressResponse> {
  return request<StressResponse>("/api/custom-invocation/stress", {
    method: "POST",
    body: JSON.stringify(payload),
  });
}
