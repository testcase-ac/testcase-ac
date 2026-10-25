#!/usr/bin/env bash
set -euo pipefail

dotnet_home="${DOTNET_CLI_HOME:-/tmp/dotnet}"
mkdir -p "${dotnet_home}"
if [[ ! -e "${dotnet_home}/.nuget" ]]; then
  ln -s /var/task/dotnet-cache/.nuget "${dotnet_home}/.nuget"
fi

# Load Node before accepting work so cold image startup is outside contestant timing.
node --stack-size=65536 -e 'require("node:fs"); process.stdout.write("")'

exec /var/task/bootstrap
