#!/usr/bin/env bash
set -euo pipefail

# Usage: ./build.sh [Debug|Release]
BUILD_TYPE="${1:-Debug}"
BUILD_DIR="build/${BUILD_TYPE}"
EXE_NAME="paoo_lab"   # change if your target name changes

echo "==> Configuring (${BUILD_TYPE})"
cmake -S . -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"

echo "==> Building"
cmake --build "${BUILD_DIR}" --parallel

echo "==> Running"
"./${BUILD_DIR}/${EXE_NAME}"
