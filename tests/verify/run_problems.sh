#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
IMAGE_NAME="testcase-ac-dockertest"
DOCKERFILE_PATH="${REPO_ROOT}/deploy/stresser.Dockerfile"

if [ "$#" -lt 1 ]; then
    echo "usage: $0 testcase/<type>/<id> [testcase/<type>/<id> ...]" >&2
    exit 2
fi

PROBLEM_ARGS=()
for problem_path in "$@"; do
    if [ ! -d "${REPO_ROOT}/${problem_path}" ]; then
        echo "Skipping deleted problem directory ${problem_path}." >&2
        continue
    fi
    PROBLEM_ARGS+=("../${problem_path}")
done

if [ "${#PROBLEM_ARGS[@]}" -eq 0 ]; then
    echo "No existing problem directories to verify."
    exit 0
fi

if ! command -v docker >/dev/null 2>&1; then
    echo "docker is not installed" >&2
    exit 1
fi

if ! docker info >/dev/null 2>&1; then
    echo "docker daemon is not running" >&2
    exit 1
fi

cd "${REPO_ROOT}"

echo "Building Linux runtime test image..."
docker build -f "${DOCKERFILE_PATH}" -t "${IMAGE_NAME}" .

echo "Verifying ${#PROBLEM_ARGS[@]} problem directory/directories..."
docker run --rm \
    --memory=1768m \
    --cpus=1 \
    --volume "${REPO_ROOT}:/workspace" \
    --workdir /workspace/backend \
    --entrypoint /usr/local/go/bin/go \
    "${IMAGE_NAME}" \
    run ./cmd/verify "${PROBLEM_ARGS[@]}"
