import { Link, isRouteErrorResponse, useRouteError } from "react-router-dom";

import { useI18n } from "../lib/i18n";

function formatRouteError(error: unknown): string {
  if (isRouteErrorResponse(error)) {
    const detail = typeof error.data === "string" ? error.data : JSON.stringify(error.data, null, 2);
    return [
      `status: ${error.status}`,
      `statusText: ${error.statusText}`,
      detail ? `data: ${detail}` : null,
    ]
      .filter(Boolean)
      .join("\n");
  }

  if (error instanceof Error) {
    return [error.name, error.message, error.stack].filter(Boolean).join("\n\n");
  }

  try {
    return JSON.stringify(error, null, 2);
  } catch {
    return String(error);
  }
}

export default function RouteErrorBoundary() {
  const error = useRouteError();
  const { t } = useI18n();
  const detail = formatRouteError(error);

  return (
    <div className="space-y-4 rounded-lg border bg-card p-6 shadow-sm">
      <div className="space-y-1">
        <h1 className="text-2xl font-semibold">{t("errorBoundary.title")}</h1>
        <p className="text-sm text-muted-foreground">{t("errorBoundary.subtitle")}</p>
      </div>
      <div className="flex gap-3">
        <Link to="/" className="text-sm font-medium text-foreground underline underline-offset-4">
          {t("errorBoundary.home")}
        </Link>
      </div>
      <pre className="overflow-x-auto whitespace-pre-wrap rounded-md border bg-background p-4 font-mono text-sm">
        {detail}
      </pre>
    </div>
  );
}
