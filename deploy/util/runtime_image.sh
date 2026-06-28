#!/usr/bin/env bash

# Shared helpers for local Docker images that package the testcase runtime.

RUNTIME_IMAGE_LABEL="testcase-ac.runtime-source-hash"
RUNTIME_PLATFORM_LABEL="testcase-ac.runtime-platform"

# shellcheck source=runtime_image_hash.sh
source "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/runtime_image_hash.sh"

native_runtime_platform() {
  case "$(uname -m)" in
    x86_64|amd64)
      printf '%s' "linux/amd64"
      ;;
    arm64|aarch64)
      printf '%s' "linux/arm64"
      ;;
    *)
      echo "Unsupported native machine architecture: $(uname -m)" >&2
      echo "Set RUNTIME_PLATFORM to one of: linux/amd64, linux/arm64" >&2
      return 1
      ;;
  esac
}

runtime_platform() {
  if [ -n "${RUNTIME_PLATFORM:-}" ]; then
    printf '%s' "${RUNTIME_PLATFORM}"
    return
  fi
  native_runtime_platform
}

runtime_target_arch() {
  case "$(runtime_platform)" in
    linux/amd64)
      printf '%s' "amd64"
      ;;
    linux/arm64)
      printf '%s' "arm64"
      ;;
    *)
      echo "Unsupported RUNTIME_PLATFORM: $(runtime_platform)" >&2
      echo "Expected one of: linux/amd64, linux/arm64" >&2
      return 1
      ;;
  esac
}

ensure_runtime_image() {
  local repo_root="$1"
  local image_name="$2"
  local dockerfile_path="$3"
  local force_build="${4:-0}"
  local source_hash
  local image_hash
  local platform
  local image_platform
  local target_arch

  source_hash="$(stresser_runtime_source_hash "$repo_root")"
  platform="$(runtime_platform)"
  target_arch="$(runtime_target_arch)"
  image_hash="$(docker image inspect -f "{{ index .Config.Labels \"${RUNTIME_IMAGE_LABEL}\" }}" "$image_name" 2>/dev/null || true)"
  image_platform="$(docker image inspect -f "{{ index .Config.Labels \"${RUNTIME_PLATFORM_LABEL}\" }}" "$image_name" 2>/dev/null || true)"

  if [ "$force_build" = "1" ] || [ "$source_hash" != "$image_hash" ] || [ "$platform" != "$image_platform" ]; then
    echo "Building Linux runtime image (${image_name}, ${platform})..."
    docker build \
      --platform "$platform" \
      --build-arg "TARGETARCH=${target_arch}" \
      -f "$dockerfile_path" \
      --label "${RUNTIME_IMAGE_LABEL}=${source_hash}" \
      --label "${RUNTIME_PLATFORM_LABEL}=${platform}" \
      -t "$image_name" "$repo_root"
  else
    echo "Using existing Linux runtime image (${image_name}, ${platform})..."
  fi
}
