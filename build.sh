#!/usr/bin/env bash
set -euo pipefail
BUILD_DIR="build"

echo "==> Configuring..."
cmake -S . -B "${BUILD_DIR}"

echo "==> Building..."
cmake --build "${BUILD_DIR}" --parallel

echo "==> Running"
"./wallet" || "./wallet.exe" || true
