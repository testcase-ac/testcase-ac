/// <reference types="vite/client" />

interface ImportMetaEnv {
  readonly VITE_API_BASE_URL?: string;
  readonly VITE_GITHUB_REPO_URL?: string;
  readonly VITE_GITHUB_REPO_BRANCH?: string;
}

interface ImportMeta {
  readonly env: ImportMetaEnv;
}
