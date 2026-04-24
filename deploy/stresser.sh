#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
TERRAFORM_DIR="${REPO_ROOT}/deploy/terraform/stresser"
DOCKERFILE_PATH="${REPO_ROOT}/deploy/stresser.Dockerfile"

require_command() {
  if ! command -v "$1" >/dev/null 2>&1; then
    echo "Missing required command: $1" >&2
    exit 1
  fi
}

resolve_arch_settings() {
  case "${STRESSER_LAMBDA_ARCHITECTURE}" in
    x86_64)
      DOCKER_PLATFORM="linux/amd64"
      GOARCH="amd64"
      ;;
    arm64)
      DOCKER_PLATFORM="linux/arm64"
      GOARCH="arm64"
      ;;
    *)
      echo "Invalid STRESSER_LAMBDA_ARCHITECTURE: ${STRESSER_LAMBDA_ARCHITECTURE}" >&2
      echo "Expected one of: x86_64, arm64" >&2
      exit 1
      ;;
  esac
}

tf() {
  terraform -chdir="${TERRAFORM_DIR}" "$@"
}

tf_output() {
  tf output -raw "$1"
}

tf_apply() {
  tf apply -auto-approve "${TF_VARS[@]}" "$@"
}

wait_for_lambda_update() {
  while true; do
    local status
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
        exit 1
        ;;
    esac

    sleep 2
  done
}

print_backend_env() {
  local access_key_id="$1"
  local iam_user_arn="$2"

  echo "==> Stresser deployed"
  echo "Function name: ${STRESSER_FUNCTION_NAME}"
  echo "Image URI: ${IMAGE_URI}"
  echo "Architecture: ${STRESSER_LAMBDA_ARCHITECTURE}"
  echo
  echo "Backend invoker IAM user: ${iam_user_arn}"
  echo
  echo "Backend environment:"
  echo "  STRESSER_MODE=lambda"
  echo "  STRESSER_LAMBDA_FUNCTION_NAME=${STRESSER_FUNCTION_NAME}"
  echo "  AWS_REGION=${STRESSER_AWS_REGION}"
  echo
  echo "Use these when running ./deploy/api.sh:"
  echo "  export DEPLOY_AWS_REGION=${STRESSER_AWS_REGION}"
  echo "  export DEPLOY_AWS_ACCESS_KEY_ID=${access_key_id}"
  echo "  export DEPLOY_AWS_SECRET_ACCESS_KEY=<redacted>"
  echo
  echo "Secret access key was not printed. Retrieve it with:"
  echo "  terraform -chdir=${TERRAFORM_DIR} output -raw secret_access_key"
}

require_command aws
require_command docker
require_command terraform

STRESSER_AWS_REGION="${STRESSER_AWS_REGION:-ap-northeast-2}"
STRESSER_ECR_REPOSITORY_NAME="${STRESSER_ECR_REPOSITORY_NAME:-testcase-ac-stresser}"
STRESSER_FUNCTION_NAME="${STRESSER_FUNCTION_NAME:-testcase-ac-stresser}"
STRESSER_MEMORY_MB="${STRESSER_MEMORY_MB:-1796}"
STRESSER_TIMEOUT_SECONDS="${STRESSER_TIMEOUT_SECONDS:-110}"
STRESSER_VPC_CIDR_BLOCK="${STRESSER_VPC_CIDR_BLOCK:-10.42.0.0/16}"
STRESSER_LAMBDA_ARCHITECTURE="${STRESSER_LAMBDA_ARCHITECTURE:-x86_64}"
STRESSER_INVOKER_IAM_USER_NAME="${STRESSER_INVOKER_IAM_USER_NAME:-testcase-ac-backend-invoker}"
STRESSER_IMAGE_TAG="${STRESSER_IMAGE_TAG:-$(git -C "${REPO_ROOT}" rev-parse --short=12 HEAD 2>/dev/null || date +%Y%m%d%H%M%S)}"

resolve_arch_settings

TF_VARS=(
  "-var=aws_region=${STRESSER_AWS_REGION}"
  "-var=ecr_repository_name=${STRESSER_ECR_REPOSITORY_NAME}"
  "-var=function_name=${STRESSER_FUNCTION_NAME}"
  "-var=image_tag=${STRESSER_IMAGE_TAG}"
  "-var=memory_mb=${STRESSER_MEMORY_MB}"
  "-var=timeout_seconds=${STRESSER_TIMEOUT_SECONDS}"
  "-var=vpc_cidr_block=${STRESSER_VPC_CIDR_BLOCK}"
  "-var=lambda_architecture=${STRESSER_LAMBDA_ARCHITECTURE}"
  "-var=iam_user_name=${STRESSER_INVOKER_IAM_USER_NAME}"
)

LOCAL_IMAGE_NAME="testcase-ac-stresser:${STRESSER_IMAGE_TAG}"

echo "==> Initializing Terraform"
tf init

echo "==> Provisioning ECR and Lambda prerequisites"
tf_apply \
  -target=aws_ecr_repository.stresser \
  -target=aws_iam_role.stresser_exec \
  -target=aws_iam_role_policy.stresser_runtime \
  -target=aws_cloudwatch_log_group.stresser

ECR_REPOSITORY_URL="$(tf_output ecr_repository_url)"
IMAGE_URI="${ECR_REPOSITORY_URL}:${STRESSER_IMAGE_TAG}"
ECR_REGISTRY_HOST="${ECR_REPOSITORY_URL%%/*}"

echo "==> Building stresser image ${IMAGE_URI}"
docker build \
  --platform "${DOCKER_PLATFORM}" \
  --provenance=false \
  --build-arg TARGETARCH="${GOARCH}" \
  -f "${DOCKERFILE_PATH}" \
  -t "${LOCAL_IMAGE_NAME}" \
  "${REPO_ROOT}"

echo "==> Logging in to ECR ${ECR_REGISTRY_HOST}"
aws ecr get-login-password --region "${STRESSER_AWS_REGION}" \
  | docker login --username AWS --password-stdin "${ECR_REGISTRY_HOST}"

echo "==> Pushing image ${IMAGE_URI}"
docker tag "${LOCAL_IMAGE_NAME}" "${IMAGE_URI}"
docker push "${IMAGE_URI}"

echo "==> Creating/updating Lambda infrastructure"
tf_apply

echo "==> Waiting for Lambda update to settle"
wait_for_lambda_update

ACCESS_KEY_ID="$(tf_output access_key_id)"
IAM_USER_ARN="$(tf_output iam_user_arn)"
print_backend_env "${ACCESS_KEY_ID}" "${IAM_USER_ARN}"
