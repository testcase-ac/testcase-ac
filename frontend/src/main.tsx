import React, { Suspense, lazy } from "react";
import ReactDOM from "react-dom/client";
import { QueryClient, QueryClientProvider } from "@tanstack/react-query";
import { Navigate, RouterProvider, createBrowserRouter, useLocation, useParams } from "react-router-dom";

import App from "./App";
import RouteErrorBoundary from "./components/RouteErrorBoundary";
import HomePage from "./pages/HomePage";
import { ThemeProvider } from "./lib/theme";
import { I18nProvider, useI18n } from "./lib/i18n";
import { PersistentSettingsProvider } from "./lib/persistentSettings";
import "./index.css";

// ProblemPage pulls in CodeMirror; keep it out of the landing chunk.
const ProblemPage = lazy(() => import("./pages/ProblemPage"));
const CustomInvocationPage = lazy(() => import("./pages/CustomInvocationPage"));
const ProblemTypePage = lazy(() => import("./pages/ProblemTypePage"));

function EditorFallback() {
  const { t } = useI18n();
  return <p className="text-sm text-muted-foreground">{t("problem.editorFallback")}</p>;
}

function LegacyProblemRedirect() {
  const { externalId = "" } = useParams();
  const location = useLocation();
  return (
    <Navigate
      replace
      to={{
        pathname: `/problems/boj/${externalId}`,
        search: location.search,
        hash: location.hash,
      }}
    />
  );
}

const queryClient = new QueryClient({
  defaultOptions: {
    queries: {
      staleTime: 30_000,
      retry: 1,
    },
  },
});

const router = createBrowserRouter(
  [
    {
      path: "/",
      element: <App />,
      errorElement: <RouteErrorBoundary />,
      children: [
        { index: true, element: <HomePage /> },
        {
          path: "custom-invocation",
          element: (
            <Suspense fallback={<EditorFallback />}>
              <CustomInvocationPage />
            </Suspense>
          ),
        },
        {
          path: ":problemType/*",
          element: (
            <Suspense fallback={<EditorFallback />}>
              <ProblemTypePage />
            </Suspense>
          ),
        },
        { path: "problems/:externalId", element: <LegacyProblemRedirect /> },
        {
          path: "problems/:problemType/:externalId",
          element: (
            <Suspense fallback={<EditorFallback />}>
              <ProblemPage />
            </Suspense>
          ),
        },
      ],
    },
  ],
  { basename: import.meta.env.BASE_URL.replace(/\/$/, "") || "/" },
);

ReactDOM.createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
    <PersistentSettingsProvider>
      <ThemeProvider>
        <I18nProvider>
          <QueryClientProvider client={queryClient}>
            <RouterProvider router={router} />
          </QueryClientProvider>
        </I18nProvider>
      </ThemeProvider>
    </PersistentSettingsProvider>
  </React.StrictMode>,
);
