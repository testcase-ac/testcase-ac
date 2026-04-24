#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
cd "$ROOT"

stage() {
  printf '\n[e2e] %s\n' "$1"
}

require_command() {
  if ! command -v "$1" >/dev/null 2>&1; then
    echo "[e2e] missing required command: $1" >&2
    exit 1
  fi
}

find_available_port() {
  local start="$1"
  node - "$start" <<'NODE'
import net from "node:net";
const start = Number(process.argv[2]);

function canListen(port) {
  return new Promise((resolve) => {
    const server = net.createServer();
    server.once("error", () => resolve(false));
    server.once("listening", () => server.close(() => resolve(true)));
    server.listen(port, "127.0.0.1");
  });
}

for (let port = start; port < start + 200; port += 1) {
  if (await canListen(port)) {
    console.log(port);
    process.exit(0);
  }
}
process.exit(1);
NODE
}

wait_for_url() {
  local label="$1"
  local url="$2"
  local timeout_seconds="$3"
  node - "$label" "$url" "$timeout_seconds" <<'NODE'
const [label, url, timeoutSecondsRaw] = process.argv.slice(2);
const deadline = Date.now() + Number(timeoutSecondsRaw) * 1000;

while (Date.now() < deadline) {
  try {
    const response = await fetch(url);
    if (response.ok) {
      process.exit(0);
    }
  } catch {
    // Keep polling until timeout.
  }
  await new Promise((resolve) => setTimeout(resolve, 1000));
}

console.error(`[e2e] timed out waiting for ${label}: ${url}`);
process.exit(1);
NODE
}

require_command docker
require_command go
require_command node
require_command npm

FRONTEND_PORT="${FRONTEND_PORT:-$(find_available_port 5173)}"
BACKEND_PORT="${BACKEND_PORT:-$(find_available_port 18000)}"
STRESSER_PORT="${STRESSER_PORT:-$(find_available_port 19000)}"
STRESSER_NAME="${STRESSER_NAME:-otac-e2e-stresser-$$}"
E2E_TESTCASE_ROOT="$ROOT/tests/e2e_testcase"
LOG_DIR="$(mktemp -d "${TMPDIR:-/tmp}/otac-e2e.XXXXXX")"
DEV_LOG="$LOG_DIR/dev.log"
DEV_PID=""

cleanup() {
  local status=$?
  if [ -n "$DEV_PID" ] && kill -0 "$DEV_PID" >/dev/null 2>&1; then
    stage "stopping dev stack"
    kill "$DEV_PID" >/dev/null 2>&1 || true
    wait "$DEV_PID" >/dev/null 2>&1 || true
  fi
  docker rm -f "$STRESSER_NAME" >/dev/null 2>&1 || true
  if [ "$status" -ne 0 ]; then
    echo
    echo "[e2e] failed; dev log tail ($DEV_LOG):" >&2
    tail -200 "$DEV_LOG" >&2 || true
  else
    echo
    echo "[e2e] logs: $DEV_LOG"
  fi
  exit "$status"
}
trap cleanup EXIT INT TERM

stage "install/check Playwright Chromium"
(cd frontend && npx playwright install chromium)

stage "start isolated dev stack"
echo "[e2e] frontend: http://127.0.0.1:$FRONTEND_PORT"
echo "[e2e] backend:  http://127.0.0.1:$BACKEND_PORT/api/health"
echo "[e2e] stresser: http://127.0.0.1:$STRESSER_PORT"
echo "[e2e] fixture:  $E2E_TESTCASE_ROOT/testcase"

env \
  FRONTEND_PORT="$FRONTEND_PORT" \
  BACKEND_PORT="$BACKEND_PORT" \
  STRESSER_PORT="$STRESSER_PORT" \
  STRESSER_NAME="$STRESSER_NAME" \
  TESTCASE_LOCAL_PATH="$E2E_TESTCASE_ROOT" \
  LOCAL_CORS_ALLOW_ORIGINS="http://127.0.0.1:$FRONTEND_PORT,http://localhost:$FRONTEND_PORT" \
  ./dev.sh >"$DEV_LOG" 2>&1 &
DEV_PID=$!

stage "wait for backend"
wait_for_url "backend" "http://127.0.0.1:$BACKEND_PORT/api/health" 180

stage "wait for frontend"
wait_for_url "frontend" "http://127.0.0.1:$FRONTEND_PORT" 120

stage "run browser smoke"
E2E_FRONTEND_URL="http://127.0.0.1:$FRONTEND_PORT" node tests/e2e/smoke.mjs
