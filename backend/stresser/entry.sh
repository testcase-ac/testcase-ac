#!/usr/bin/env bash
set -euo pipefail

dotnet_home="${DOTNET_CLI_HOME:-/tmp/dotnet}"
mkdir -p "${dotnet_home}"
if [[ ! -e "${dotnet_home}/.nuget" ]]; then
  ln -s /var/task/dotnet-cache/.nuget "${dotnet_home}/.nuget"
fi

if [[ -z "${AWS_LAMBDA_RUNTIME_API:-}" ]]; then
  exec /usr/local/bin/aws-lambda-rie /var/task/bootstrap
fi

exec /var/task/bootstrap
