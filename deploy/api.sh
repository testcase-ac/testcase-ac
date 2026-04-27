#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
STRESSER_TERRAFORM_DIR="${REPO_ROOT}/deploy/terraform/stresser"

# Shared local helpers used by both the regular deploy path and the temporary
# bootstrap/provisioning blocks below.

require_command() {
  if ! command -v "$1" >/dev/null 2>&1; then
    echo "Missing required command: $1" >&2
    exit 1
  fi
}

require_env() {
  local name="$1"
  if [[ -z "${!name:-}" ]]; then
    echo "Missing required environment variable: $name" >&2
    exit 1
  fi
}

terraform_output() {
  local output_name="$1"
  require_command terraform
  terraform -chdir="${STRESSER_TERRAFORM_DIR}" output -raw "${output_name}"
}

set_default() {
  local name="$1"
  local value="$2"
  if [[ -z "${!name:-}" ]]; then
    printf -v "${name}" '%s' "${value}"
  fi
}

resolve_from_terraform() {
  local name="$1"
  local output_name="$2"
  local value
  if [[ -n "${!name:-}" ]]; then
    return 0
  fi
  if ! value="$(terraform_output "${output_name}")"; then
    echo "Missing required environment variable: ${name}" >&2
    echo "Also failed to resolve Terraform output '${output_name}' from ${STRESSER_TERRAFORM_DIR}" >&2
    exit 1
  fi
  printf -v "${name}" '%s' "${value}"
}

join_by() {
  local delimiter="$1"
  shift
  local first=1
  for item in "$@"; do
    if [[ $first -eq 0 ]]; then
      printf '%s' "$delimiter"
    fi
    printf '%s' "$item"
    first=0
  done
}

shell_quote() {
  local value="${1//\'/\'\\\'\'}"
  printf "'%s'" "${value}"
}

default_cors_allow_origins() {
  local origins=()
  local port
  for port in 5173 5174 5175 5176 5177 5178 5179; do
    origins+=("http://localhost:${port}" "http://127.0.0.1:${port}")
  done
  origins+=("https://testcase-ac.github.io" "https://next.testcase.ac" "https://testcase.ac")
  join_by "," "${origins[@]}"
}

render_backend_env() {
  cat <<EOF
TESTCASE_LOCAL_PATH=${DEPLOY_APP_DIR}
STRESSER_MODE=lambda
STRESSER_LAMBDA_FUNCTION_NAME=${STRESSER_LAMBDA_FUNCTION_NAME}
AWS_REGION=${DEPLOY_AWS_REGION}
RATE_LIMIT_MAX=${DEPLOY_RATE_LIMIT_MAX}
RATE_LIMIT_WINDOW_S=${DEPLOY_RATE_LIMIT_WINDOW_S}
CORS_ALLOW_ORIGINS=${DEPLOY_CORS_ALLOW_ORIGINS}
AWS_ACCESS_KEY_ID=${DEPLOY_AWS_ACCESS_KEY_ID}
AWS_SECRET_ACCESS_KEY=${DEPLOY_AWS_SECRET_ACCESS_KEY}
EOF

  if [[ -n "${DEPLOY_AWS_SESSION_TOKEN}" ]]; then
    printf 'AWS_SESSION_TOKEN=%s\n' "${DEPLOY_AWS_SESSION_TOKEN}"
  fi
}

render_service_unit() {
  local slot="$1"
  cat <<EOF
[Unit]
Description=testcase-ac backend (${slot})
After=network-online.target
Wants=network-online.target

[Service]
Type=simple
User=${DEPLOY_APP_USER}
Group=${DEPLOY_APP_USER}
WorkingDirectory=${DEPLOY_APP_DIR}/backend
EnvironmentFile=${DEPLOY_ENV_PREFIX}.${slot}
ExecStart=${DEPLOY_APP_DIR}/backend/${DEPLOY_BINARY_NAME}
Restart=always
RestartSec=5
TimeoutStopSec=${DEPLOY_SHUTDOWN_TIMEOUT_SEC}
NoNewPrivileges=true
PrivateTmp=true
ProtectHome=true
ProtectSystem=full
RestrictSUIDSGID=true

[Install]
WantedBy=multi-user.target
EOF
}

render_caddy_snippet() {
  local port="$1"
  cat <<EOF
${API_DOMAIN} {
    encode zstd gzip
    reverse_proxy 127.0.0.1:${port}
}
EOF
}

# BOOTSTRAP / PROVISIONING SECTION
#
# This heredoc still mixes one-time host setup with the blue/green deploy steps
# that run every release. It is intentionally labeled so it can later be split
# into a real bootstrap script plus a smaller remote deploy script.
#
# Bootstrap-only work in this script:
# - install OS packages such as curl, rsync, and caddy
# - create or normalize the system app user
# - create application, env, and Caddy config directories
# - remove legacy service/Caddy names
# - ensure the top-level Caddyfile imports Caddyfile.d snippets
# - install or refresh systemd service unit files
#
# Regular deploy work in this script:
# - choose the inactive blue/green slot
# - sync testcase data and author index
# - install the new backend binary and slot env files
# - restart and health-check the inactive slot
# - switch Caddy to the healthy slot
# - mark the active slot and stop the previous service
remote_provision_script() {
  cat <<'EOF'
set -euo pipefail

APP_DIR="${DEPLOY_APP_DIR}"
APP_USER="${DEPLOY_APP_USER}"
ENV_PREFIX="${DEPLOY_ENV_PREFIX}"
SERVICE_NAME="${DEPLOY_SERVICE_NAME}"
CADDY_SNIPPET="${DEPLOY_CADDY_SNIPPET}"
BINARY_NAME="${DEPLOY_BINARY_NAME}"
BLUE_PORT="${DEPLOY_BLUE_PORT}"
GREEN_PORT="${DEPLOY_GREEN_PORT}"
ACTIVE_SLOT_PATH="${DEPLOY_ACTIVE_SLOT_PATH}"
ACTIVE_SLOT_BASENAME="$(basename "${ACTIVE_SLOT_PATH}")"
STAGING_DIR="${REMOTE_STAGING_DIR}"
INCOMING_TESTCASE_DIR="${STAGING_DIR}/testcase"
LEGACY_SERVICE_NAME="open-testcase-ac-backend"
LEGACY_CADDY_SNIPPET="/etc/caddy/Caddyfile.d/open-testcase-ac-api.caddy"

slot_port() {
  case "$1" in
    blue) printf '%s\n' "${BLUE_PORT}" ;;
    green) printf '%s\n' "${GREEN_PORT}" ;;
    *) return 1 ;;
  esac
}

other_slot() {
  case "$1" in
    blue) printf 'green\n' ;;
    green) printf 'blue\n' ;;
    *) return 1 ;;
  esac
}

slot_service() {
  printf '%s-%s\n' "${SERVICE_NAME}" "$1"
}

read_active_slot() {
  local slot=""
  if [[ -f "${ACTIVE_SLOT_PATH}" ]]; then
    slot="$(sudo cat "${ACTIVE_SLOT_PATH}" 2>/dev/null || true)"
  fi
  case "${slot}" in
    blue|green)
      printf '%s\n' "${slot}"
      return 0
      ;;
  esac

  if [[ -f "${CADDY_SNIPPET}" ]] && sudo grep -qF "127.0.0.1:${GREEN_PORT}" "${CADDY_SNIPPET}"; then
    printf 'green\n'
    return 0
  fi
  printf 'blue\n'
}

sudo apt-get update
sudo apt-get install -y curl rsync caddy

sudo systemctl disable --now "${LEGACY_SERVICE_NAME}" >/dev/null 2>&1 || true
sudo rm -f "/etc/systemd/system/${LEGACY_SERVICE_NAME}.service" "${LEGACY_CADDY_SNIPPET}"

if ! id -u "${APP_USER}" >/dev/null 2>&1; then
  sudo useradd --system --create-home --shell /usr/sbin/nologin "${APP_USER}"
else
  sudo usermod --shell /usr/sbin/nologin "${APP_USER}"
fi

sudo mkdir -p "${APP_DIR}" "${APP_DIR}/backend" "${APP_DIR}/testcase" \
  "$(dirname "${ENV_PREFIX}")" "$(dirname "${CADDY_SNIPPET}")"
sudo find "${APP_DIR}" -mindepth 1 -maxdepth 1 \
  ! -name backend ! -name testcase ! -name "${ACTIVE_SLOT_BASENAME}" -exec rm -rf {} +

had_active_slot=0
if [[ -f "${ACTIVE_SLOT_PATH}" ]]; then
  had_active_slot=1
fi
active_slot="$(read_active_slot)"
inactive_slot="$(other_slot "${active_slot}")"
inactive_port="$(slot_port "${inactive_slot}")"
active_service="$(slot_service "${active_slot}")"
inactive_service="$(slot_service "${inactive_slot}")"

printf 'Deploying inactive API slot %s on port %s; current active slot is %s\n' \
  "${inactive_slot}" "${inactive_port}" "${active_slot}"

sudo rsync -a --delete "${INCOMING_TESTCASE_DIR}/" "${APP_DIR}/testcase/"
sudo install -o "${APP_USER}" -g "${APP_USER}" -m 0644 "${STAGING_DIR}/author-index.json" "${APP_DIR}/testcase/.author-index.json"
for slot in blue green; do
  slot_env="${ENV_PREFIX}.${slot}"
  slot_port_value="$(slot_port "${slot}")"
  sudo install -o root -g root -m 0600 "${STAGING_DIR}/backend.env" "${slot_env}"
  printf 'HTTP_ADDR=127.0.0.1:%s\n' "${slot_port_value}" | sudo tee -a "${slot_env}" >/dev/null
  sudo install -o root -g root -m 0644 \
    "${STAGING_DIR}/${SERVICE_NAME}-${slot}.service" \
    "/etc/systemd/system/${SERVICE_NAME}-${slot}.service"
done
sudo install -o "${APP_USER}" -g "${APP_USER}" -m 0755 "${STAGING_DIR}/${BINARY_NAME}" "${APP_DIR}/backend/${BINARY_NAME}"
sudo rm -rf "${APP_DIR}/backend/.venv" "${APP_DIR}/backend/app"
sudo chown -R "${APP_USER}:${APP_USER}" "${APP_DIR}"

if [[ ! -f /etc/caddy/Caddyfile ]]; then
  printf 'import /etc/caddy/Caddyfile.d/*\n' | sudo tee /etc/caddy/Caddyfile >/dev/null
elif ! sudo grep -qF 'import /etc/caddy/Caddyfile.d/*' /etc/caddy/Caddyfile; then
  printf '\nimport /etc/caddy/Caddyfile.d/*\n' | sudo tee -a /etc/caddy/Caddyfile >/dev/null
fi

sudo systemctl daemon-reload

if [[ "${inactive_slot}" == "blue" ]]; then
  sudo systemctl stop "${SERVICE_NAME}" >/dev/null 2>&1 || true
fi

sudo systemctl enable "${inactive_service}"
sudo systemctl restart "${inactive_service}"
sudo systemctl enable --now caddy

for _attempt in $(seq 1 20); do
  if curl --fail --silent "http://127.0.0.1:${inactive_port}/api/health" >/dev/null; then
    break
  fi
  sleep 1
done

curl --fail --silent "http://127.0.0.1:${inactive_port}/api/health" >/dev/null
sudo install -o root -g root -m 0644 "${STAGING_DIR}/testcase-ac-api-${inactive_slot}.caddy" "${CADDY_SNIPPET}"
sudo systemctl reload caddy
printf '%s\n' "${inactive_slot}" | sudo tee "${ACTIVE_SLOT_PATH}" >/dev/null

sudo systemctl disable --now "${active_service}" >/dev/null 2>&1 || true
if [[ "${had_active_slot}" -eq 1 ]]; then
  sudo systemctl disable --now "${SERVICE_NAME}" >/dev/null 2>&1 || true
else
  sudo systemctl disable "${SERVICE_NAME}" >/dev/null 2>&1 || true
  echo "Left legacy ${SERVICE_NAME} process running for this migration deploy; it will be stopped on the next blue/green deploy."
fi

rm -rf "${STAGING_DIR}"
EOF
}

require_command ssh
require_command rsync
require_command mktemp
require_command go
require_command git

# REGULAR DEPLOY CONFIGURATION
#
# Stresser/Lambda credentials are supplied by the caller, or resolved from
# Terraform outputs for local deploys that have the stresser Terraform state.
# ${DEPLOY_ENV_PREFIX} is a filename prefix; only ${DEPLOY_ENV_PREFIX}.blue
# and ${DEPLOY_ENV_PREFIX}.green are used as env files. The unsuffixed prefix
# path is intentionally not used as a source of truth.

set_default DEPLOY_HOST "testcase-ac-api"
set_default API_DOMAIN "api.testcase.ac"
DEPLOY_SSH_USER="${DEPLOY_SSH_USER:-ubuntu}"
DEPLOY_SSH_PORT="${DEPLOY_SSH_PORT:-22}"
DEPLOY_APP_USER="${DEPLOY_APP_USER:-testcase-ac}"
DEPLOY_APP_DIR="${DEPLOY_APP_DIR:-/srv/testcase-ac}"
DEPLOY_ENV_PREFIX="${DEPLOY_ENV_PREFIX:-${DEPLOY_ENV_PATH:-/etc/testcase-ac/backend.env}}"
DEPLOY_SERVICE_NAME="${DEPLOY_SERVICE_NAME:-testcase-ac-backend}"
DEPLOY_CADDY_SNIPPET="${DEPLOY_CADDY_SNIPPET:-/etc/caddy/Caddyfile.d/testcase-ac-api.caddy}"
DEPLOY_BINARY_NAME="${DEPLOY_BINARY_NAME:-testcase-ac-backend}"
DEPLOY_BLUE_PORT="${DEPLOY_BLUE_PORT:-8000}"
DEPLOY_GREEN_PORT="${DEPLOY_GREEN_PORT:-8001}"
DEPLOY_ACTIVE_SLOT_PATH="${DEPLOY_ACTIVE_SLOT_PATH:-${DEPLOY_APP_DIR}/.active-api-slot}"
DEPLOY_SHUTDOWN_TIMEOUT_SEC="${DEPLOY_SHUTDOWN_TIMEOUT_SEC:-190s}"
DEPLOY_GOOS="${DEPLOY_GOOS:-linux}"
DEPLOY_GOARCH="${DEPLOY_GOARCH:-amd64}"
DEPLOY_AWS_REGION="${DEPLOY_AWS_REGION:-ap-northeast-2}"
DEPLOY_AWS_SESSION_TOKEN="${DEPLOY_AWS_SESSION_TOKEN:-}"
DEPLOY_RATE_LIMIT_MAX="${DEPLOY_RATE_LIMIT_MAX:-5}"
DEPLOY_RATE_LIMIT_WINDOW_S="${DEPLOY_RATE_LIMIT_WINDOW_S:-10}"
DEPLOY_CORS_ALLOW_ORIGINS="${DEPLOY_CORS_ALLOW_ORIGINS:-$(default_cors_allow_origins)}"
DEPLOY_SSH_TARGET="${DEPLOY_SSH_USER}@${DEPLOY_HOST}"
REMOTE_STAGING_DIR="${REMOTE_STAGING_DIR:-/tmp/testcase-ac-deploy}"
SSH_ARGS=(-p "${DEPLOY_SSH_PORT}" -o BatchMode=yes)
SSH_RSH="ssh ${SSH_ARGS[*]}"

resolve_from_terraform STRESSER_LAMBDA_FUNCTION_NAME lambda_function_name
resolve_from_terraform DEPLOY_AWS_ACCESS_KEY_ID access_key_id
resolve_from_terraform DEPLOY_AWS_SECRET_ACCESS_KEY secret_access_key

require_env DEPLOY_HOST
require_env API_DOMAIN
require_env STRESSER_LAMBDA_FUNCTION_NAME
require_env DEPLOY_AWS_ACCESS_KEY_ID
require_env DEPLOY_AWS_SECRET_ACCESS_KEY
require_env DEPLOY_AWS_REGION

if [[ "${DEPLOY_BLUE_PORT}" == "${DEPLOY_GREEN_PORT}" ]]; then
  echo "DEPLOY_BLUE_PORT and DEPLOY_GREEN_PORT must be different" >&2
  exit 1
fi

# REGULAR DEPLOY SECTION
# Build local artifacts, upload them to a staging directory, and ask the remote
# script above to perform the blue/green switch.

TMP_DIR="$(mktemp -d)"
cleanup() {
  rm -rf "${TMP_DIR}"
}
trap cleanup EXIT

echo "==> Building backend binary (${DEPLOY_GOOS}/${DEPLOY_GOARCH})"
BINARY_PATH="${TMP_DIR}/${DEPLOY_BINARY_NAME}"
(
  cd "${REPO_ROOT}/backend"
  CGO_ENABLED=0 GOOS="${DEPLOY_GOOS}" GOARCH="${DEPLOY_GOARCH}" \
    go build -o "${BINARY_PATH}" ./api
)

echo "==> Building testcase author index"
AUTHOR_INDEX_PATH="${TMP_DIR}/author-index.json"
go run "${REPO_ROOT}/deploy/build-author-index.go" \
  -repo-root "${REPO_ROOT}" \
  -output "${AUTHOR_INDEX_PATH}"

ENV_FILE="${TMP_DIR}/backend.env"
SERVICE_FILE_BLUE="${TMP_DIR}/${DEPLOY_SERVICE_NAME}-blue.service"
SERVICE_FILE_GREEN="${TMP_DIR}/${DEPLOY_SERVICE_NAME}-green.service"
CADDY_FILE_BLUE="${TMP_DIR}/testcase-ac-api-blue.caddy"
CADDY_FILE_GREEN="${TMP_DIR}/testcase-ac-api-green.caddy"
render_backend_env > "${ENV_FILE}"
chmod 0600 "${ENV_FILE}"
render_service_unit blue > "${SERVICE_FILE_BLUE}"
render_service_unit green > "${SERVICE_FILE_GREEN}"
render_caddy_snippet "${DEPLOY_BLUE_PORT}" > "${CADDY_FILE_BLUE}"
render_caddy_snippet "${DEPLOY_GREEN_PORT}" > "${CADDY_FILE_GREEN}"

echo "==> Preparing remote staging directory"
REMOTE_STAGING_DIR_Q="$(shell_quote "${REMOTE_STAGING_DIR}")"
ssh "${SSH_ARGS[@]}" "${DEPLOY_SSH_TARGET}" "rm -rf -- ${REMOTE_STAGING_DIR_Q} && install -d -m 0700 ${REMOTE_STAGING_DIR_Q}/testcase"

echo "==> Syncing testcase data"
rsync -az --delete -e "${SSH_RSH}" \
  "${REPO_ROOT}/testcase/" "${DEPLOY_SSH_TARGET}:${REMOTE_STAGING_DIR}/testcase/"

echo "==> Uploading deploy assets"
rsync -az -e "${SSH_RSH}" \
  "${ENV_FILE}" \
  "${SERVICE_FILE_BLUE}" \
  "${SERVICE_FILE_GREEN}" \
  "${CADDY_FILE_BLUE}" \
  "${CADDY_FILE_GREEN}" \
  "${BINARY_PATH}" \
  "${AUTHOR_INDEX_PATH}" \
  "${DEPLOY_SSH_TARGET}:${REMOTE_STAGING_DIR}/"

echo "==> Provisioning remote host"
ssh "${SSH_ARGS[@]}" "${DEPLOY_SSH_TARGET}" \
  "DEPLOY_APP_DIR=$(shell_quote "${DEPLOY_APP_DIR}") \
   DEPLOY_APP_USER=$(shell_quote "${DEPLOY_APP_USER}") \
   DEPLOY_ENV_PREFIX=$(shell_quote "${DEPLOY_ENV_PREFIX}") \
   DEPLOY_SERVICE_NAME=$(shell_quote "${DEPLOY_SERVICE_NAME}") \
   DEPLOY_CADDY_SNIPPET=$(shell_quote "${DEPLOY_CADDY_SNIPPET}") \
   DEPLOY_BINARY_NAME=$(shell_quote "${DEPLOY_BINARY_NAME}") \
   DEPLOY_BLUE_PORT=$(shell_quote "${DEPLOY_BLUE_PORT}") \
   DEPLOY_GREEN_PORT=$(shell_quote "${DEPLOY_GREEN_PORT}") \
   DEPLOY_ACTIVE_SLOT_PATH=$(shell_quote "${DEPLOY_ACTIVE_SLOT_PATH}") \
   REMOTE_STAGING_DIR=$(shell_quote "${REMOTE_STAGING_DIR}") \
   /bin/bash -s" <<EOF
$(remote_provision_script)
EOF

echo "==> Deployment complete"
echo "API health: https://${API_DOMAIN}/api/health"
