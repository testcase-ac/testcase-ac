# 프론트엔드

한국어 | [English](README.en.md)

문제를 탐색하고 코드를 제출해 백엔드 stresser API로 보내는 Vite + React
싱글 페이지 앱입니다.

## 로컬 개발

```bash
cp .env.example .env
npm install
npm run dev
```

기본적으로 앱은 <http://localhost:5173>에서 실행되며, `VITE_API_BASE_URL`의
백엔드를 호출합니다.

## 설정

- `VITE_API_BASE_URL`: 백엔드 API origin입니다. 예: `http://localhost:8000`.
- `VITE_GITHUB_REPO_URL`: "view on GitHub" 소스 링크에 사용할 저장소입니다.
- `VITE_GITHUB_REPO_BRANCH`: 해당 소스 링크에 사용할 브랜치입니다.

전체 로컬 스택은 저장소 루트의 `./dev.sh` 사용을 권장합니다. 이 스크립트는
프론트엔드, 백엔드, 로컬 stresser를 서로 맞는 포트로 실행합니다.

## 명령어

```bash
npm run dev
npm run build
npm run preview
npm run typecheck
npm run test
```

## GitHub Pages

GitHub Pages처럼 하위 경로에 빌드할 때는 `VITE_BASE_PATH`를 설정하세요.

```bash
VITE_BASE_PATH=/testcase-ac/ \
VITE_API_BASE_URL=https://api.your-host.example.com \
VITE_GITHUB_REPO_URL=https://github.com/testcase-ac/testcase-ac \
  npm run build
```

`dist/`를 Pages 브랜치나 artifact로 게시하세요. 빌드 스크립트는 클라이언트
사이드 라우팅을 위해 Pages 호환 `404.html`도 작성합니다.
