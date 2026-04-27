#!/usr/bin/env bash
set -euo pipefail

usage() {
  echo "usage: $0 testcase/<type>/<id> [sample-file ...]" >&2
}

if [ "$#" -lt 1 ]; then
  usage
  exit 2
fi

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../../../.." && pwd)"
IMAGE_NAME="${TESTCASE_AC_DOCKER_IMAGE:-testcase-ac-dockertest}"
DOCKERFILE_PATH="${REPO_ROOT}/deploy/stresser.Dockerfile"

abs_problem_dir="$(cd "$1" && pwd -P)"
case "${abs_problem_dir}" in
  "${REPO_ROOT}"/*) problem_rel="${abs_problem_dir#"${REPO_ROOT}/"}" ;;
  *) echo "problem directory must be inside ${REPO_ROOT}" >&2; exit 2 ;;
esac
shift

if [ ! -f "${REPO_ROOT}/${problem_rel}/validator.cpp" ]; then
  echo "missing ${problem_rel}/validator.cpp" >&2
  exit 2
fi

sample_rels=()
if [ "$#" -gt 0 ]; then
  for sample in "$@"; do
    abs_sample="$(cd "$(dirname "$sample")" && pwd -P)/$(basename "$sample")"
    case "${abs_sample}" in
      "${REPO_ROOT}"/*) sample_rels+=("${abs_sample#"${REPO_ROOT}/"}") ;;
      *) echo "sample file must be inside ${REPO_ROOT}: ${sample}" >&2; exit 2 ;;
    esac
  done
else
  while IFS= read -r sample; do
    sample_rels+=("${sample}")
  done < <(cd "${REPO_ROOT}" && find "${problem_rel}" -maxdepth 1 -type f -name 'testcase_*.txt' | sort)
fi

if [ "${#sample_rels[@]}" -eq 0 ]; then
  echo "no sample files supplied and no testcase_*.txt files found; create 2-3 valid sample files and pass them explicitly" >&2
  exit 2
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
if [ "${DOCKERTEST_SKIP_BUILD:-0}" = "1" ]; then
  echo "Using existing Linux runtime test image (${IMAGE_NAME})..."
else
  echo "Building Linux runtime test image..."
  docker build -f "${DOCKERFILE_PATH}" -t "${IMAGE_NAME}" .
fi

samples_blob="$(printf '%s\n' "${sample_rels[@]}")"
docker run --rm \
  --memory=1768m \
  --cpus=1 \
  --volume "${REPO_ROOT}:/workspace" \
  --workdir /workspace \
  --entrypoint /bin/bash \
  -e "PROBLEM_REL=${problem_rel}" \
  -e "SAMPLES_BLOB=${samples_blob}" \
  "${IMAGE_NAME}" \
  -lc '
    set -euo pipefail
    g++ -std=c++23 -O2 -Wall -Wextra -I/opt/testlib "/workspace/${PROBLEM_REL}/validator.cpp" -o /tmp/validator-check
    while IFS= read -r sample; do
      [ -n "$sample" ] || continue
      echo "validating ${sample}"
      /tmp/validator-check < "/workspace/${sample}"
    done <<< "${SAMPLES_BLOB}"
  '
