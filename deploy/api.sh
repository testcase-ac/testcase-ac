#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

# Shared local helpers used by both the regular deploy path and the temporary
# bootstrap/provisioning blocks below.

require_command() {
  if ! command -v "$1" >/dev/null 2>&1; then
    echo "Missing required command: $1" >&2
    exit 1
  fi
}

default_cors_allow_origins() {
  local origins=()
  local IFS=,
  local port
  for port in 5173 5174 5175 5176 5177 5178 5179; do
    origins+=("http://localhost:${port}" "http://127.0.0.1:${port}")
  done
  origins+=("https://testcase-ac.github.io" "https://next.testcase.ac" "https://testcase.ac")
  printf '%s' "${origins[*]}"
}

render_backend_env() {
  cat <<EOF
TESTCASE_LOCAL_PATH=${DEPLOY_APP_DIR}
AUTHOR_INDEX_PATH=${DEPLOY_APP_DIR}/testcase/.author-index.json
STRESSER_MODE=lambda
STRESSER_LAMBDA_FUNCTION_NAME=${STRESSER_LAMBDA_FUNCTION_NAME}
AWS_REGION=${DEPLOY_AWS_REGION}
RATE_LIMIT_MAX=${DEPLOY_RATE_LIMIT_MAX}
RATE_LIMIT_WINDOW_S=${DEPLOY_RATE_LIMIT_WINDOW_S}
CORS_ALLOW_ORIGINS=${DEPLOY_CORS_ALLOW_ORIGINS}
STATS_DB_PATH=${DEPLOY_STATS_DB_PATH}
EOF
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
EnvironmentFile=${DEPLOY_AWS_ENV_PATH}
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
StateDirectory=testcase-ac

[Install]
WantedBy=multi-user.target
EOF
}

render_stats_reconcile_unit() {
  cat <<EOF
[Unit]
Description=testcase.ac execution statistics reconciliation
After=systemd-journald.service

[Service]
Type=oneshot
User=${DEPLOY_APP_USER}
Group=${DEPLOY_APP_USER}
SupplementaryGroups=systemd-journal
WorkingDirectory=${DEPLOY_APP_DIR}/backend
Environment=STATS_DB_PATH=${DEPLOY_STATS_DB_PATH}
ExecStart=${DEPLOY_APP_DIR}/backend/${DEPLOY_BINARY_NAME} reconcile-stats
NoNewPrivileges=true
PrivateTmp=true
ProtectHome=true
ProtectSystem=full
RestrictSUIDSGID=true
StateDirectory=testcase-ac
EOF
}

render_stats_reconcile_timer() {
  cat <<EOF
[Unit]
Description=Reconcile testcase.ac execution statistics every minute

[Timer]
OnBootSec=1min
OnUnitActiveSec=1min
AccuracySec=10s
Persistent=true
Unit=${DEPLOY_STATS_RECONCILE_SERVICE}

[Install]
WantedBy=timers.target
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

# Performs the blue/green switch on the initialized production host.
remote_deploy_script() {
  cat <<'EOF'
set -euo pipefail

APP_DIR="/srv/testcase-ac"
APP_USER="testcase-ac"
ENV_PREFIX="/etc/testcase-ac/backend.env"
AWS_ENV_PATH="/etc/testcase-ac/backend-aws.env"
SERVICE_NAME="testcase-ac-backend"
CADDY_SNIPPET="/etc/caddy/Caddyfile.d/testcase-ac-api.caddy"
BINARY_NAME="testcase-ac-backend"
STATS_RECONCILE_SERVICE="testcase-ac-stats-reconcile.service"
STATS_RECONCILE_TIMER="testcase-ac-stats-reconcile.timer"
BLUE_PORT="8000"
GREEN_PORT="8001"
ACTIVE_SLOT_PATH="/srv/testcase-ac/.active-api-slot"
STAGING_DIR="/tmp/testcase-ac-deploy"
INCOMING_TESTCASE_DIR="${STAGING_DIR}/testcase"

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
  local slot
  slot="$(sudo cat "${ACTIVE_SLOT_PATH}")"
  case "${slot}" in
    blue|green)
      printf '%s\n' "${slot}"
      ;;
    *)
      echo "Invalid active API slot: ${slot}" >&2
      return 1
      ;;
  esac
}

sudo grep -q '^AWS_ACCESS_KEY_ID=.' "${AWS_ENV_PATH}"
sudo grep -q '^AWS_SECRET_ACCESS_KEY=.' "${AWS_ENV_PATH}"

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
sudo install -o root -g root -m 0644 \
  "${STAGING_DIR}/${STATS_RECONCILE_SERVICE}" \
  "/etc/systemd/system/${STATS_RECONCILE_SERVICE}"
sudo install -o root -g root -m 0644 \
  "${STAGING_DIR}/${STATS_RECONCILE_TIMER}" \
  "/etc/systemd/system/${STATS_RECONCILE_TIMER}"
sudo install -o "${APP_USER}" -g "${APP_USER}" -m 0755 "${STAGING_DIR}/${BINARY_NAME}" "${APP_DIR}/backend/${BINARY_NAME}"
sudo rm -rf "${APP_DIR}/backend/.venv" "${APP_DIR}/backend/app"
sudo chown -R "${APP_USER}:${APP_USER}" "${APP_DIR}"

sudo systemctl daemon-reload
sudo systemctl enable "${STATS_RECONCILE_TIMER}"

sudo systemctl enable "${inactive_service}"
sudo systemctl restart "${inactive_service}"

health_url="http://127.0.0.1:${inactive_port}/api/health"
health_ok=0
for _attempt in $(seq 1 60); do
  if curl --fail --silent --connect-timeout 2 --max-time 5 "${health_url}" >/dev/null; then
    health_ok=1
    break
  fi
  if [[ $(( _attempt % 5 )) -eq 0 ]]; then
    printf 'Waiting for %s health check (%s/60)\n' "${inactive_service}" "${_attempt}"
  fi
  sleep 2
done

if [[ "${health_ok}" -ne 1 ]]; then
  printf 'Health check failed for %s at %s\n' "${inactive_service}" "${health_url}" >&2
  sudo systemctl --no-pager --full status "${inactive_service}" >&2 || true
  sudo journalctl -u "${inactive_service}" -n 80 --no-pager >&2 || true
  exit 1
fi

sudo install -o root -g root -m 0644 "${STAGING_DIR}/testcase-ac-api-${inactive_slot}.caddy" "${CADDY_SNIPPET}"
sudo systemctl reload caddy
printf '%s\n' "${inactive_slot}" | sudo tee "${ACTIVE_SLOT_PATH}" >/dev/null

sudo systemctl disable --now "${active_service}" >/dev/null 2>&1 || true
sudo systemctl start "${STATS_RECONCILE_TIMER}"

rm -rf "${STAGING_DIR}"
EOF
}

require_command ssh
require_command rsync
require_command mktemp
require_command go

# REGULAR DEPLOY CONFIGURATION
# The production host layout is fixed; only connection and AWS identifiers vary.
DEPLOY_HOST="${DEPLOY_HOST:-testcase-ac-api}"
API_DOMAIN="api.testcase.ac"
DEPLOY_APP_USER="testcase-ac"
DEPLOY_APP_DIR="/srv/testcase-ac"
DEPLOY_ENV_PREFIX="/etc/testcase-ac/backend.env"
DEPLOY_AWS_ENV_PATH="/etc/testcase-ac/backend-aws.env"
DEPLOY_SERVICE_NAME="testcase-ac-backend"
DEPLOY_BINARY_NAME="testcase-ac-backend"
DEPLOY_BLUE_PORT="8000"
DEPLOY_GREEN_PORT="8001"
DEPLOY_SHUTDOWN_TIMEOUT_SEC="190s"
DEPLOY_STATS_DB_PATH="/var/lib/testcase-ac/execution-stats.db"
DEPLOY_STATS_RECONCILE_SERVICE="testcase-ac-stats-reconcile.service"
DEPLOY_STATS_RECONCILE_TIMER="testcase-ac-stats-reconcile.timer"
DEPLOY_AWS_REGION="${DEPLOY_AWS_REGION:-ap-northeast-2}"
DEPLOY_RATE_LIMIT_MAX="5"
DEPLOY_RATE_LIMIT_WINDOW_S="10"
DEPLOY_CORS_ALLOW_ORIGINS="$(default_cors_allow_origins)"
DEPLOY_SSH_TARGET="ubuntu@${DEPLOY_HOST}"
REMOTE_STAGING_DIR="/tmp/testcase-ac-deploy"
SSH_ARGS=(-p 22 -o BatchMode=yes)
SSH_RSH="ssh ${SSH_ARGS[*]}"
STRESSER_LAMBDA_FUNCTION_NAME="${STRESSER_LAMBDA_FUNCTION_NAME:-testcase-ac-stresser}"

# REGULAR DEPLOY SECTION
# Build local artifacts, upload them to a staging directory, and ask the remote
# script above to perform the blue/green switch.

TMP_DIR="$(mktemp -d)"
cleanup() {
  rm -rf "${TMP_DIR}"
}
trap cleanup EXIT

echo "==> Building backend binary (linux/amd64)"
BINARY_PATH="${TMP_DIR}/${DEPLOY_BINARY_NAME}"
(
  cd "${REPO_ROOT}/backend"
  CGO_ENABLED=0 GOOS=linux GOARCH=amd64 \
    go build -o "${BINARY_PATH}" ./api
)

echo "==> Building testcase author index"
AUTHOR_INDEX_PATH="${TMP_DIR}/author-index.json"
(
  cd "${REPO_ROOT}/backend"
  go run ./cmd/build-author-index \
    -repo-root "${REPO_ROOT}" \
    -output "${AUTHOR_INDEX_PATH}"
)

ENV_FILE="${TMP_DIR}/backend.env"
SERVICE_FILE_BLUE="${TMP_DIR}/${DEPLOY_SERVICE_NAME}-blue.service"
SERVICE_FILE_GREEN="${TMP_DIR}/${DEPLOY_SERVICE_NAME}-green.service"
CADDY_FILE_BLUE="${TMP_DIR}/testcase-ac-api-blue.caddy"
CADDY_FILE_GREEN="${TMP_DIR}/testcase-ac-api-green.caddy"
STATS_RECONCILE_SERVICE_FILE="${TMP_DIR}/${DEPLOY_STATS_RECONCILE_SERVICE}"
STATS_RECONCILE_TIMER_FILE="${TMP_DIR}/${DEPLOY_STATS_RECONCILE_TIMER}"
render_backend_env > "${ENV_FILE}"
chmod 0600 "${ENV_FILE}"
render_service_unit blue > "${SERVICE_FILE_BLUE}"
render_service_unit green > "${SERVICE_FILE_GREEN}"
render_caddy_snippet "${DEPLOY_BLUE_PORT}" > "${CADDY_FILE_BLUE}"
render_caddy_snippet "${DEPLOY_GREEN_PORT}" > "${CADDY_FILE_GREEN}"
render_stats_reconcile_unit > "${STATS_RECONCILE_SERVICE_FILE}"
render_stats_reconcile_timer > "${STATS_RECONCILE_TIMER_FILE}"

echo "==> Preparing remote staging directory"
ssh "${SSH_ARGS[@]}" "${DEPLOY_SSH_TARGET}" \
  "rm -rf -- /tmp/testcase-ac-deploy && install -d -m 0700 /tmp/testcase-ac-deploy/testcase"

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
  "${STATS_RECONCILE_SERVICE_FILE}" \
  "${STATS_RECONCILE_TIMER_FILE}" \
  "${BINARY_PATH}" \
  "${AUTHOR_INDEX_PATH}" \
  "${DEPLOY_SSH_TARGET}:${REMOTE_STAGING_DIR}/"

echo "==> Provisioning remote host"
ssh "${SSH_ARGS[@]}" "${DEPLOY_SSH_TARGET}" /bin/bash -s <<EOF
$(remote_deploy_script)
EOF

echo "==> Deployment complete"
echo "API health: https://${API_DOMAIN}/api/health"
