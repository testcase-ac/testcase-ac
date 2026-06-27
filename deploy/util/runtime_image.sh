#!/usr/bin/env bash

# Shared helpers for local Docker images that package the testcase runtime.

RUNTIME_IMAGE_LABEL="testcase-ac.runtime-source-hash"

# shellcheck source=runtime_image_hash.sh
source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/runtime_image_hash.sh"

ensure_runtime_image() {
  local repo_root="$1"
  local image_name="$2"
  local dockerfile_path="$3"
  local force_build="${4:-0}"
  local source_hash
  local image_hash

  source_hash="$(stresser_runtime_source_hash "$repo_root")"
  image_hash="$(docker image inspect -f "{{ index .Config.Labels \"${RUNTIME_IMAGE_LABEL}\" }}" "$image_name" 2>/dev/null || true)"

  if [ "$force_build" = "1" ] || [ "$source_hash" != "$image_hash" ]; then
    echo "Building Linux runtime image (${image_name})..."
    docker build \
      -f "$dockerfile_path" \
      --label "${RUNTIME_IMAGE_LABEL}=${source_hash}" \
      -t "$image_name" "$repo_root"
  else
    echo "Using existing Linux runtime image (${image_name})..."
  fi
}
