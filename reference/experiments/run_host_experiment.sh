#!/bin/sh
set -eu

BUILD_DIR=${1:-reference/build}
OUT_DIR=${2:-reference/experiments/results}

cmake -S reference -B "$BUILD_DIR"
cmake --build "$BUILD_DIR"
"$BUILD_DIR/host_experiment" "$OUT_DIR"
