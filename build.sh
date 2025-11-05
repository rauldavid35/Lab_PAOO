#!/usr/bin/env bash
set -euo pipefail
BUILD_TYPE="${1:-Debug}"
BUILD_DIR="build/${BUILD_TYPE}"

echo "==> Configuring (${BUILD_TYPE})"
cmake -S . -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"

echo "==> Building"
cmake --build "${BUILD_DIR}" --parallel

echo "==> Running"
"./${BUILD_DIR}/wallet" || "./${BUILD_DIR}/wallet.exe" || true
