#!/usr/bin/env bash
set -euo pipefail

dotnet_home="${DOTNET_CLI_HOME:-/tmp/dotnet}"
mkdir -p "${dotnet_home}"
if [[ ! -e "${dotnet_home}/.nuget" ]]; then
  ln -s /var/task/dotnet-cache/.nuget "${dotnet_home}/.nuget"
fi

exec /var/task/bootstrap
