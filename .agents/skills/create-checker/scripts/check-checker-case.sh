#!/usr/bin/env bash
set -euo pipefail

usage() {
  echo "usage: $0 testcase/<type>/<id> <accepted|rejected|wrong-answer|presentation-error|fail> <input-file> <participant-file> <jury-file>" >&2
}

if [ "$#" -ne 5 ]; then
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

expected="$1"
shift

case "${expected}" in
  accepted|ok|_ok) want="0" ;;
  wrong-answer|wa|_wa) want="1" ;;
  presentation-error|pe|_pe) want="2" ;;
  fail|_fail) want="3" ;;
  rejected) want="rejected" ;;
  *) echo "unknown expected verdict: ${expected}" >&2; usage; exit 2 ;;
esac

checker_file="${REPO_ROOT}/${problem_rel}/checker.cpp"
if [ ! -f "${checker_file}" ]; then
  echo "missing ${problem_rel}/checker.cpp" >&2
  exit 2
fi

for file in "$@"; do
  if [ ! -f "${file}" ]; then
    echo "missing case file: ${file}" >&2
    exit 2
  fi
done

case_dir="$(mktemp -d /tmp/check-checker-case.XXXXXX)"
cleanup() {
  rm -rf "${case_dir}"
}
trap cleanup EXIT

cp "$1" "${case_dir}/input.txt"
cp "$2" "${case_dir}/participant.txt"
cp "$3" "${case_dir}/jury.txt"

checker_timeout_seconds="${CHECKER_RUN_TIMEOUT_SECONDS:-5}"
if ! [[ "${checker_timeout_seconds}" =~ ^[0-9]+$ ]] || [ "${checker_timeout_seconds}" -le 0 ]; then
  echo "CHECKER_RUN_TIMEOUT_SECONDS must be a positive integer" >&2
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

status_name() {
  case "$1" in
    0) echo "accepted" ;;
    1) echo "wrong-answer" ;;
    2) echo "presentation-error" ;;
    3) echo "fail" ;;
    124) echo "timeout" ;;
    *) echo "exit-$1" ;;
  esac
}

set +e
docker run --rm \
  --memory=1768m \
  --cpus=1 \
  --volume "${REPO_ROOT}:/workspace" \
  --volume "${case_dir}:/checker-case" \
  --workdir /workspace \
  --entrypoint /bin/bash \
  -e "PROBLEM_REL=${problem_rel}" \
  -e "CHECKER_RUN_TIMEOUT_SECONDS=${checker_timeout_seconds}" \
  "${IMAGE_NAME}" \
  -lc '
    set -euo pipefail
    g++ -std=c++23 -O2 -Wall -Wextra -Wno-type-limits -I/opt/testlib -I/opt/boost \
      "/workspace/${PROBLEM_REL}/checker.cpp" -o /tmp/checker-case
    timeout "${CHECKER_RUN_TIMEOUT_SECONDS}" /tmp/checker-case \
      /checker-case/input.txt /checker-case/participant.txt /checker-case/jury.txt /checker-case/result.txt \
      > /checker-case/stdout.txt 2> /checker-case/stderr.txt
  '
got=$?
set -e

if [ "${want}" = "rejected" ]; then
  if [ "${got}" -ne 1 ] && [ "${got}" -ne 2 ]; then
    echo "checker case: expected rejected, got $(status_name "${got}")" >&2
    [ -s "${case_dir}/result.txt" ] && sed "s/^/  result: /" "${case_dir}/result.txt" >&2
    [ -s "${case_dir}/stdout.txt" ] && sed "s/^/  stdout: /" "${case_dir}/stdout.txt" >&2
    [ -s "${case_dir}/stderr.txt" ] && sed "s/^/  stderr: /" "${case_dir}/stderr.txt" >&2
    exit 1
  fi
elif [ "${got}" -ne "${want}" ]; then
  echo "checker case: expected $(status_name "${want}"), got $(status_name "${got}")" >&2
  [ -s "${case_dir}/result.txt" ] && sed "s/^/  result: /" "${case_dir}/result.txt" >&2
  [ -s "${case_dir}/stdout.txt" ] && sed "s/^/  stdout: /" "${case_dir}/stdout.txt" >&2
  [ -s "${case_dir}/stderr.txt" ] && sed "s/^/  stderr: /" "${case_dir}/stderr.txt" >&2
  exit 1
fi

echo "checker case passed: expected ${expected}, got $(status_name "${got}")"
