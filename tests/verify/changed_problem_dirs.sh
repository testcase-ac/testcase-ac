#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -lt 1 ] || [ "$#" -gt 2 ]; then
    echo "usage: $0 <base-ref> [head-ref]" >&2
    exit 2
fi

BASE_REF="$1"
HEAD_REF="${2:-HEAD}"

git diff --name-status "${BASE_REF}" "${HEAD_REF}" |
    awk '{
        path = $NF
        if (path ~ /^testcase\/[^\/]+\/[^\/]+\//) {
            split(path, parts, "/")
            print parts[1] "/" parts[2] "/" parts[3]
        }
    }' |
    sort -u
