#!/usr/bin/env bash
set -euo pipefail

# Verifies that the stresser release path publishes one prebuilt image and updates only the configured Lambda.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "${SCRIPT_DIR}/../.." && pwd)"
TMP_DIR="$(mktemp -d)"
trap 'rm -rf "${TMP_DIR}"' EXIT

FAKE_BIN="${TMP_DIR}/bin"
CALLS_FILE="${TMP_DIR}/calls"
mkdir -p "${FAKE_BIN}"

cat > "${FAKE_BIN}/docker" <<'EOF'
#!/usr/bin/env bash
set -euo pipefail
printf 'docker %s\n' "$*" >> "${CALLS_FILE}"
if [[ "${1:-}" == "image" && "${2:-}" == "inspect" ]]; then
  exit 0
fi
if [[ "${1:-}" == "login" ]]; then
  cat >/dev/null
fi
EOF

cat > "${FAKE_BIN}/aws" <<'EOF'
#!/usr/bin/env bash
set -euo pipefail
printf 'aws %s\n' "$*" >> "${CALLS_FILE}"
case "$*" in
  *"ecr describe-repositories"*)
    printf '%s\n' '662119809355.dkr.ecr.ap-northeast-2.amazonaws.com/testcase-ac-stresser'
    ;;
  *"ecr get-login-password"*)
    printf '%s\n' 'fake-password'
    ;;
  *"lambda get-function"*"Configuration.LastUpdateStatus"*)
    printf '%s\n' 'Successful'
    ;;
  *"lambda get-function"*"Code.ImageUri"*)
    printf '%s\n' '662119809355.dkr.ecr.ap-northeast-2.amazonaws.com/testcase-ac-stresser:release-sha'
    ;;
esac
EOF

chmod +x "${FAKE_BIN}/aws" "${FAKE_BIN}/docker"

export CALLS_FILE
export PATH="${FAKE_BIN}:/usr/bin:/bin"
export STRESSER_AWS_REGION="ap-northeast-2"
export STRESSER_ECR_REPOSITORY_NAME="testcase-ac-stresser"
export STRESSER_FUNCTION_NAME="testcase-ac-stresser"
export STRESSER_IMAGE_TAG="release-sha"
export STRESSER_LOCAL_IMAGE="local-stresser:tested"

"${REPO_ROOT}/deploy/stresser-release.sh"

expected_calls="${TMP_DIR}/expected-calls"
cat > "${expected_calls}" <<'EOF'
docker image inspect local-stresser:tested
aws ecr describe-repositories --region ap-northeast-2 --repository-names testcase-ac-stresser --query repositories[0].repositoryUri --output text
aws ecr get-login-password --region ap-northeast-2
docker login --username AWS --password-stdin 662119809355.dkr.ecr.ap-northeast-2.amazonaws.com
docker tag local-stresser:tested 662119809355.dkr.ecr.ap-northeast-2.amazonaws.com/testcase-ac-stresser:release-sha
docker push 662119809355.dkr.ecr.ap-northeast-2.amazonaws.com/testcase-ac-stresser:release-sha
aws lambda update-function-code --region ap-northeast-2 --function-name testcase-ac-stresser --image-uri 662119809355.dkr.ecr.ap-northeast-2.amazonaws.com/testcase-ac-stresser:release-sha --output json
aws lambda get-function --region ap-northeast-2 --function-name testcase-ac-stresser --query Configuration.LastUpdateStatus --output text
aws lambda get-function --region ap-northeast-2 --function-name testcase-ac-stresser --query Code.ImageUri --output text
EOF

diff -u "${expected_calls}" "${CALLS_FILE}"
