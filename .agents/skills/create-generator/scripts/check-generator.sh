#!/usr/bin/env bash
set -euo pipefail

usage() {
  echo "usage: $0 testcase/<type>/<id> [generator-file] [runs]" >&2
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

generator_file="${1:-}"
runs="${2:-100}"

if [ -z "${generator_file}" ]; then
  candidates=()
  while IFS= read -r candidate; do
    candidates+=("${candidate}")
  done < <(cd "${REPO_ROOT}/${problem_rel}" && find . -maxdepth 1 -type f \( -name 'generator*.cpp' -o -name 'generator_*.cpp' \) | sed 's#^\./##' | sort)
  if [ "${#candidates[@]}" -ne 1 ]; then
    echo "expected exactly one generator*.cpp candidate, found ${#candidates[@]}; pass generator filename explicitly" >&2
    exit 2
  fi
  generator_file="${candidates[0]}"
fi

if ! [[ "${runs}" =~ ^[0-9]+$ ]] || [ "${runs}" -le 0 ]; then
  echo "runs must be a positive integer" >&2
  exit 2
fi

if [ ! -f "${REPO_ROOT}/${problem_rel}/${generator_file}" ]; then
  echo "missing ${problem_rel}/${generator_file}" >&2
  exit 2
fi

has_validator=0
if [ -f "${REPO_ROOT}/${problem_rel}/validator.cpp" ]; then
  has_validator=1
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

docker run --rm \
  --memory=1768m \
  --cpus=1 \
  --volume "${REPO_ROOT}:/workspace" \
  --workdir /workspace \
  --entrypoint /bin/bash \
  -e "PROBLEM_REL=${problem_rel}" \
  -e "GENERATOR_FILE=${generator_file}" \
  -e "RUNS=${runs}" \
  -e "HAS_VALIDATOR=${has_validator}" \
  "${IMAGE_NAME}" \
  -lc '
    set -euo pipefail
    g++ -std=c++23 -O2 -Wall -Wextra -I/opt/testlib "/workspace/${PROBLEM_REL}/${GENERATOR_FILE}" -o /tmp/generator-check
    if [ "${HAS_VALIDATOR}" = "1" ]; then
      g++ -std=c++23 -O2 -Wall -Wextra -I/opt/testlib "/workspace/${PROBLEM_REL}/validator.cpp" -o /tmp/validator-check
    fi

    rm -rf /tmp/generator-cases
    mkdir -p /tmp/generator-cases
    for ((seed = 0; seed < RUNS; ++seed)); do
      out="/tmp/generator-cases/case_${seed}.txt"
      /tmp/generator-check "${seed}" > "${out}"
      [ -s "${out}" ] || { echo "seed ${seed}: generator produced empty output" >&2; exit 1; }
      if [ "${HAS_VALIDATOR}" = "1" ]; then
        /tmp/validator-check < "${out}" || { echo "seed ${seed}: validator rejected generator output" >&2; exit 1; }
      fi
    done

    echo "generator ${GENERATOR_FILE} passed ${RUNS} run(s); validator: ${HAS_VALIDATOR}"
  '
