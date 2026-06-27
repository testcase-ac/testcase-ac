#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
IMAGE_NAME="${RUNTIME_IMAGE:-testcase-ac-runtime:local}"
DOCKERFILE_PATH="${REPO_ROOT}/deploy/stresser.Dockerfile"

# shellcheck source=../../deploy/util/runtime_image.sh
source "${REPO_ROOT}/deploy/util/runtime_image.sh"

if [ "$#" -lt 1 ]; then
    echo "usage: $0 [--validate-inputs] testcase/<type>/<id> [testcase/<type>/<id> ...]" >&2
    exit 2
fi

VERIFY_FLAGS=()
while [ "$#" -gt 0 ]; do
    case "$1" in
        --validate-inputs)
            VERIFY_FLAGS+=("$1")
            shift
            ;;
        --)
            shift
            break
            ;;
        -*)
            echo "unknown option: $1" >&2
            exit 2
            ;;
        *)
            break
            ;;
    esac
done

if [ "$#" -lt 1 ]; then
    echo "usage: $0 [--validate-inputs] testcase/<type>/<id> [testcase/<type>/<id> ...]" >&2
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

ensure_runtime_image "${REPO_ROOT}" "${IMAGE_NAME}" "${DOCKERFILE_PATH}" "${DOCKERTEST_FORCE_BUILD:-0}"

echo "Verifying ${#PROBLEM_ARGS[@]} problem directory/directories..."
VERIFY_CMD=(run ./cmd/verify)
if [ "${#VERIFY_FLAGS[@]}" -gt 0 ]; then
    VERIFY_CMD+=("${VERIFY_FLAGS[@]}")
fi
if [ -n "${VERIFY_REPORT_JSON:-}" ]; then
    VERIFY_CMD+=(--json)
fi
VERIFY_CMD+=("${PROBLEM_ARGS[@]}")

if [ -n "${VERIFY_REPORT_JSON:-}" ]; then
    docker run --rm \
        --memory=1768m \
        --cpus=1 \
        --volume "${REPO_ROOT}:/workspace" \
        --workdir /workspace/backend \
        --entrypoint /usr/local/go/bin/go \
        "${IMAGE_NAME}" \
        "${VERIFY_CMD[@]}" | tee "${VERIFY_REPORT_JSON}"
    exit "${PIPESTATUS[0]}"
fi

docker run --rm \
    --memory=1768m \
    --cpus=1 \
    --volume "${REPO_ROOT}:/workspace" \
    --workdir /workspace/backend \
    --entrypoint /usr/local/go/bin/go \
    "${IMAGE_NAME}" \
    "${VERIFY_CMD[@]}"
