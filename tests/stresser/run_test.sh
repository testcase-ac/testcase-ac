#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
IMAGE_NAME="testcase-ac-stresser-test"
CONTAINER_NAME="testcase-ac-stresser-test-container"
DOCKERFILE_PATH="${REPO_ROOT}/deploy/stresser.Dockerfile"

cleanup() {
    if docker ps -a --format '{{.Names}}' | grep -qx "${CONTAINER_NAME}"; then
        docker rm -f "${CONTAINER_NAME}" >/dev/null 2>&1 || true
    fi
}

trap cleanup EXIT

if ! command -v docker >/dev/null 2>&1; then
    echo "docker is not installed" >&2
    exit 1
fi

if ! docker info >/dev/null 2>&1; then
    echo "docker daemon is not running" >&2
    exit 1
fi

cd "${REPO_ROOT}"

echo "Building Linux stresser test image..."
docker build -f "${DOCKERFILE_PATH}" -t "${IMAGE_NAME}" .

TEST_CMD=(test ./stresser)
if [ "$#" -gt 0 ]; then
    TEST_CMD+=("$@")
fi

echo "Running stresser tests in Linux container..."
docker run \
    --name "${CONTAINER_NAME}" \
    --memory=1768m \
    --cpus=1 \
    --volume "${REPO_ROOT}:/workspace" \
    --workdir /workspace/backend \
    --entrypoint /usr/local/go/bin/go \
    "${IMAGE_NAME}" \
    "${TEST_CMD[@]}"
