#!/usr/bin/env bash

# Shared source hash for Docker images that package the testcase runtime.

stresser_runtime_source_hash() {
  local repo_root="${1:-.}"

  (
    cd "$repo_root" || return
    {
      git ls-files \
        backend/contracts \
        backend/go.mod \
        backend/go.sum \
        backend/internal \
        backend/stresser \
        deploy/stresser.Dockerfile \
        third_party/testlib/testlib.h
      git ls-files --others --exclude-standard \
        backend/contracts \
        backend/go.mod \
        backend/go.sum \
        backend/internal \
        backend/stresser \
        deploy/stresser.Dockerfile \
        third_party/testlib/testlib.h
    } | LC_ALL=C sort -u | xargs shasum | shasum | awk '{print $1}'
  )
}
