#!/usr/bin/env bash
# shellcheck disable=SC2016 # Contract strings intentionally contain shell and GitHub expressions.
set -euo pipefail

# Guards the API deployment contract that keeps long-lived credentials out of GitHub Actions.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
WORKFLOW="${REPO_ROOT}/.github/workflows/deploy-api.yml"
DEPLOY_SCRIPT="${REPO_ROOT}/deploy/api.sh"

require_text() {
  local file="$1"
  local text="$2"
  if ! grep -Fq -- "${text}" "${file}"; then
    echo "Expected ${file} to contain: ${text}" >&2
    exit 1
  fi
}

reject_text() {
  local file="$1"
  local text="$2"
  if grep -Fq -- "${text}" "${file}"; then
    echo "Expected ${file} not to contain: ${text}" >&2
    exit 1
  fi
}

require_text "${WORKFLOW}" 'id-token: write'
require_text "${WORKFLOW}" 'aws-actions/configure-aws-credentials@v6'
require_text "${WORKFLOW}" 'role-to-assume: ${{ vars.API_DEPLOY_ROLE_ARN }}'
require_text "${WORKFLOW}" 'aws lightsail get-instance-access-details'
require_text "${WORKFLOW}" 'run: ./tests/deploy/api_oidc_deploy_test.sh'
reject_text "${WORKFLOW}" 'secrets.'

require_text "${DEPLOY_SCRIPT}" 'ensure_backend_aws_env'
require_text "${DEPLOY_SCRIPT}" 'EnvironmentFile=${DEPLOY_AWS_ENV_PATH}'
reject_text "${DEPLOY_SCRIPT}" 'resolve_from_terraform DEPLOY_AWS_ACCESS_KEY_ID'
reject_text "${DEPLOY_SCRIPT}" 'resolve_from_terraform DEPLOY_AWS_SECRET_ACCESS_KEY'
