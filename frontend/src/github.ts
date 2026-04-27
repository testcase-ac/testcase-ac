const REPO_URL = import.meta.env.VITE_GITHUB_REPO_URL?.replace(/\/$/, "") ?? "";
const BRANCH = import.meta.env.VITE_GITHUB_REPO_BRANCH ?? "main";

function pathSegments(value: string): string {
  return value.split("/").map(encodeURIComponent).join("/");
}

export function sourceFileUrl(
  problemType: string,
  externalId: string,
  filename: string,
): string | null {
  if (!REPO_URL) return null;
  return `${REPO_URL}/blob/${BRANCH}/testcase/${encodeURIComponent(problemType)}/${pathSegments(externalId)}/${encodeURIComponent(filename)}`;
}

export function problemDirUrl(problemType: string, externalId: string): string | null {
  if (!REPO_URL) return null;
  return `${REPO_URL}/tree/${BRANCH}/testcase/${encodeURIComponent(problemType)}/${pathSegments(externalId)}`;
}
