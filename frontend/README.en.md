# Frontend

[한국어](README.md) | English

Vite + React single-page app for browsing problems and submitting code to the
backend stresser API.

## Local Development

```bash
cp .env.example .env
npm install
npm run dev
```

By default this serves the app at <http://localhost:5173> and calls the backend
from `VITE_API_BASE_URL`.

## Configuration

- `VITE_API_BASE_URL`: backend API origin, for example `http://localhost:8000`.
- `VITE_GITHUB_REPO_URL`: repository used for "view on GitHub" source links.
- `VITE_GITHUB_REPO_BRANCH`: branch used for those source links.

For the full local stack, prefer the repo-root `./dev.sh`; it starts the
frontend, backend, and local stresser with matching ports.

## Commands

```bash
npm run dev
npm run build
npm run preview
npm run typecheck
npm run test
```

## GitHub Pages

Set `VITE_BASE_PATH` when building for a subpath such as GitHub Pages:

```bash
VITE_BASE_PATH=/testcase-ac/ \
VITE_API_BASE_URL=https://api.your-host.example.com \
VITE_GITHUB_REPO_URL=https://github.com/testcase-ac/testcase-ac \
  npm run build
```

Publish `dist/` to the Pages branch or artifact. The build script also writes a
Pages-compatible `404.html` for client-side routing.
