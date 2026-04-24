#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"

MODE="${1:-default}"
FRONTEND_PORT="${FRONTEND_PORT:-5173}"
BACKEND_PORT="${BACKEND_PORT:-8000}"
STRESSER_PORT="${STRESSER_PORT:-9000}"
REMOTE_API_BASE_URL="${REMOTE_API_BASE_URL:-https://api.testcase.ac}"
STRESSER_IMAGE="${STRESSER_IMAGE:-testcase-ac-stresser:dev}"
STRESSER_NAME="${STRESSER_NAME:-otac-stresser}"
TESTCASE_LOCAL_PATH="${TESTCASE_LOCAL_PATH:-$ROOT}"
REBUILD_STRESSER_IMAGE="${REBUILD_STRESSER_IMAGE:-0}"
LOCAL_CORS_ALLOW_ORIGINS="${LOCAL_CORS_ALLOW_ORIGINS:-http://localhost:5173,http://127.0.0.1:5173,http://localhost:5174,http://127.0.0.1:5174,http://localhost:5175,http://127.0.0.1:5175,http://localhost:5176,http://127.0.0.1:5176,http://localhost:5177,http://127.0.0.1:5177,http://localhost:5178,http://127.0.0.1:5178,http://localhost:5179,http://127.0.0.1:5179}"

usage() {
  cat <<EOF
Usage:
  ./dev.sh                 Start frontend + backend + local stresser
  ./dev.sh default         Same as above
  ./dev.sh frontend        Start frontend only, pointed at ${REMOTE_API_BASE_URL}

Useful overrides:
  FRONTEND_PORT=5175
  BACKEND_PORT=8000
  STRESSER_PORT=9000
  TESTCASE_LOCAL_PATH=/absolute/path/to/repo-or-fixture
  REMOTE_API_BASE_URL=https://api.testcase.ac
  REBUILD_STRESSER_IMAGE=1
EOF
}

require_command() {
  if ! command -v "$1" >/dev/null 2>&1; then
    echo "error: missing required command: $1" >&2
    exit 1
  fi
}

find_available_port() {
  local port="$1"
  while ! node -e "const net=require('net'); const server=net.createServer(); server.once('error',()=>process.exit(1)); server.once('listening',()=>server.close(()=>process.exit(0))); server.listen(${port}, '127.0.0.1');"; do
    port=$((port + 1))
  done
  printf '%s' "$port"
}

pick_port() {
  local label="$1"
  local requested="$2"
  local resolved
  resolved="$(find_available_port "$requested")"
  if [ "$resolved" != "$requested" ]; then
    echo "[dev] $label port $requested is busy, using $resolved" >&2
  fi
  printf '%s' "$resolved"
}

ensure_frontend_deps() {
  if [ ! -d frontend/node_modules ]; then
    echo "[dev] installing frontend deps"
    (cd frontend && npm install --silent --no-fund --no-audit)
  fi
}

start_frontend() {
  local api_base="$1"
  echo "[dev] starting frontend on :$FRONTEND_PORT (api: $api_base)"
  (
    cd frontend
    exec env VITE_API_BASE_URL="$api_base" \
      npx vite --host 127.0.0.1 --port "$FRONTEND_PORT" 2>&1
  ) > >(sed -u 's/^/[frontend] /') &
  frontend_pid=$!
}

start_backend() {
  local stresser_endpoint="http://127.0.0.1:${STRESSER_PORT}/2015-03-31/functions/function/invocations"
  echo "[dev] starting backend on :$BACKEND_PORT"
  (
    cd backend
    exec env \
      TESTCASE_LOCAL_PATH="$TESTCASE_LOCAL_PATH" \
      STRESSER_MODE="local_docker" \
      STRESSER_LOCAL_ENDPOINT="$stresser_endpoint" \
      CORS_ALLOW_ORIGINS="$LOCAL_CORS_ALLOW_ORIGINS" \
      HTTP_ADDR="127.0.0.1:$BACKEND_PORT" \
      go run ./api 2>&1
  ) > >(sed -u 's/^/[backend]  /') &
  backend_pid=$!
}

ensure_stresser_image() {
  if [ "$REBUILD_STRESSER_IMAGE" = "1" ] || ! docker image inspect "$STRESSER_IMAGE" >/dev/null 2>&1; then
    echo "[dev] building stresser image ($STRESSER_IMAGE)"
    docker build -q -f deploy/stresser.Dockerfile -t "$STRESSER_IMAGE" . >/dev/null
  fi
}

start_stresser() {
  docker rm -f "$STRESSER_NAME" >/dev/null 2>&1 || true
  echo "[dev] starting stresser on :$STRESSER_PORT"
  docker run -d --rm --name "$STRESSER_NAME" \
    -p "$STRESSER_PORT:8080" "$STRESSER_IMAGE" >/dev/null
}

cleanup() {
  trap - EXIT INT TERM
  echo
  echo "[dev] stopping..."
  if [ "${stresser_started:-0}" = "1" ]; then
    docker stop "$STRESSER_NAME" >/dev/null 2>&1 || true
  fi
  if [ -n "${backend_pid:-}" ]; then
    kill "$backend_pid" 2>/dev/null || true
  fi
  if [ -n "${frontend_pid:-}" ]; then
    kill "$frontend_pid" 2>/dev/null || true
  fi
  wait 2>/dev/null || true
  echo "[dev] done."
}

case "$MODE" in
  -h|--help|help)
    usage
    exit 0
    ;;
  default|local|all)
    require_command docker
    require_command go
    require_command npm
    require_command node
    FRONTEND_PORT="$(pick_port frontend "$FRONTEND_PORT")"
    BACKEND_PORT="$(pick_port backend "$BACKEND_PORT")"
    STRESSER_PORT="$(pick_port stresser "$STRESSER_PORT")"
    ensure_frontend_deps
    ensure_stresser_image
    start_stresser
    stresser_started=1
    start_backend
    start_frontend "http://127.0.0.1:$BACKEND_PORT"
    ready_message=$(
      cat <<EOF

[dev] mode: default
      frontend  http://127.0.0.1:$FRONTEND_PORT
      backend   http://127.0.0.1:$BACKEND_PORT/api/health
      stresser  http://127.0.0.1:$STRESSER_PORT
      Ctrl-C to stop everything.

EOF
    )
    ;;
  frontend|fe)
    require_command npm
    require_command node
    FRONTEND_PORT="$(pick_port frontend "$FRONTEND_PORT")"
    ensure_frontend_deps
    start_frontend "$REMOTE_API_BASE_URL"
    ready_message=$(
      cat <<EOF

[dev] mode: frontend
      frontend  http://127.0.0.1:$FRONTEND_PORT
      api       $REMOTE_API_BASE_URL
      Ctrl-C to stop the frontend.

EOF
    )
    ;;
  *)
    echo "error: unknown mode: $MODE" >&2
    echo >&2
    usage >&2
    exit 1
    ;;
esac

trap cleanup EXIT INT TERM

printf "%s\n" "$ready_message"
wait
