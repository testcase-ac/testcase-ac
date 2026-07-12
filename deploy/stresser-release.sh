#!/usr/bin/env bash
set -euo pipefail

# Publishes one tested local image and points the existing production Lambda at it.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"

require_command() {
  if ! command -v "$1" >/dev/null 2>&1; then
    echo "Missing required command: $1" >&2
    exit 1
  fi
}

wait_for_lambda_update() {
  local attempt
  local status

  for ((attempt = 1; attempt <= 150; attempt++)); do
    status="$(aws lambda get-function \
      --region "${STRESSER_AWS_REGION}" \
      --function-name "${STRESSER_FUNCTION_NAME}" \
      --query 'Configuration.LastUpdateStatus' \
      --output text)"

    case "${status}" in
      Successful)
        return 0
        ;;
      Failed)
        echo "Lambda update failed" >&2
        aws lambda get-function \
          --region "${STRESSER_AWS_REGION}" \
          --function-name "${STRESSER_FUNCTION_NAME}" \
          --query 'Configuration.[LastUpdateStatusReason,StateReason]' \
          --output table >&2 || true
        return 1
        ;;
    esac

    sleep 2
  done

  echo "Timed out waiting for Lambda update" >&2
  return 1
}

require_command aws
require_command docker
require_command git

STRESSER_AWS_REGION="${STRESSER_AWS_REGION:-ap-northeast-2}"
STRESSER_ECR_REPOSITORY_NAME="${STRESSER_ECR_REPOSITORY_NAME:-testcase-ac-stresser}"
STRESSER_FUNCTION_NAME="${STRESSER_FUNCTION_NAME:-testcase-ac-stresser}"
STRESSER_IMAGE_TAG="${STRESSER_IMAGE_TAG:-$(git -C "${REPO_ROOT}" rev-parse HEAD)}"
STRESSER_LOCAL_IMAGE="${STRESSER_LOCAL_IMAGE:-testcase-ac-stresser:${STRESSER_IMAGE_TAG}}"

if ! docker image inspect "${STRESSER_LOCAL_IMAGE}" >/dev/null; then
  echo "Tested local image not found: ${STRESSER_LOCAL_IMAGE}" >&2
  exit 1
fi

ECR_REPOSITORY_URL="$(aws ecr describe-repositories \
  --region "${STRESSER_AWS_REGION}" \
  --repository-names "${STRESSER_ECR_REPOSITORY_NAME}" \
  --query 'repositories[0].repositoryUri' \
  --output text)"
if [[ -z "${ECR_REPOSITORY_URL}" || "${ECR_REPOSITORY_URL}" == "None" ]]; then
  echo "Could not resolve ECR repository: ${STRESSER_ECR_REPOSITORY_NAME}" >&2
  exit 1
fi

IMAGE_URI="${ECR_REPOSITORY_URL}:${STRESSER_IMAGE_TAG}"
ECR_REGISTRY_HOST="${ECR_REPOSITORY_URL%%/*}"

echo "==> Logging in to ECR ${ECR_REGISTRY_HOST}"
aws ecr get-login-password --region "${STRESSER_AWS_REGION}" \
  | docker login --username AWS --password-stdin "${ECR_REGISTRY_HOST}"

echo "==> Pushing tested image ${IMAGE_URI}"
docker tag "${STRESSER_LOCAL_IMAGE}" "${IMAGE_URI}"
docker push "${IMAGE_URI}"

echo "==> Updating Lambda ${STRESSER_FUNCTION_NAME}"
aws lambda update-function-code \
  --region "${STRESSER_AWS_REGION}" \
  --function-name "${STRESSER_FUNCTION_NAME}" \
  --image-uri "${IMAGE_URI}" \
  --output json >/dev/null

wait_for_lambda_update

DEPLOYED_IMAGE_URI="$(aws lambda get-function \
  --region "${STRESSER_AWS_REGION}" \
  --function-name "${STRESSER_FUNCTION_NAME}" \
  --query 'Code.ImageUri' \
  --output text)"
if [[ "${DEPLOYED_IMAGE_URI}" != "${IMAGE_URI}" ]]; then
  echo "Lambda image mismatch: expected ${IMAGE_URI}, got ${DEPLOYED_IMAGE_URI}" >&2
  exit 1
fi

echo "==> Stresser deployed"
echo "Function name: ${STRESSER_FUNCTION_NAME}"
echo "Image URI: ${IMAGE_URI}"
