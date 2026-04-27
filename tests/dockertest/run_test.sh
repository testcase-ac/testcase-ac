#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
IMAGE_NAME="testcase-ac-dockertest"
CONTAINER_NAME="testcase-ac-dockertest-$$"
DOCKERFILE_PATH="${REPO_ROOT}/deploy/stresser.Dockerfile"

if ! command -v docker >/dev/null 2>&1; then
    echo "docker is not installed" >&2
    exit 1
fi

if ! docker info >/dev/null 2>&1; then
    echo "docker daemon is not running" >&2
    exit 1
fi

cd "${REPO_ROOT}"

if [ "${DOCKERTEST_SKIP_BUILD:-0}" = "1" ]; then
    echo "Using existing Linux runtime test image (${IMAGE_NAME})..."
else
    echo "Building Linux runtime test image..."
    docker build -f "${DOCKERFILE_PATH}" -t "${IMAGE_NAME}" .
fi

TEST_CMD=(test ./stresser ./internal/verify)
if [ "$#" -gt 0 ]; then
    TEST_CMD=(test "$@")
fi

echo "Running Go tests in Linux runtime container..."
docker run --rm \
    --name "${CONTAINER_NAME}" \
    --memory=1768m \
    --cpus=1 \
    --volume "${REPO_ROOT}:/workspace" \
    --workdir /workspace/backend \
    --entrypoint /usr/local/go/bin/go \
    "${IMAGE_NAME}" \
    "${TEST_CMD[@]}"
