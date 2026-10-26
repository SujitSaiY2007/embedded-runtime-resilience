#!/usr/bin/env bash
# Rebuilds and runs the host probes used in Section 4.4 of the draft. Needs gcc. Run from anywhere.
set -u
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../.." && pwd)"
TMP="$(mktemp -d)"; trap 'rm -rf "$TMP"' EXIT
INC="-I$ROOT/reference/include"; SRC="$ROOT/reference/src/ref_runtime.c"; S="$ROOT/research/manuscript/scripts"
echo "== exhaustive policy_decide enumeration"
gcc -std=c11 -w $INC "$S/probe_policy_inputs.c" "$SRC" -o "$TMP/enum" && "$TMP/enum"
echo "== runtime limits, assertions enabled (expect abort in probe 2)"
gcc -std=c11 -w -O0 -fsanitize=address,undefined $INC "$S/probe_runtime_limits.c" "$SRC" -o "$TMP/p1" && "$TMP/p1" 2>&1 | head -8
echo "== runtime limits, NDEBUG (expect UBSan out-of-bounds report)"
gcc -std=c11 -w -O2 -DNDEBUG -fsanitize=address,undefined $INC "$S/probe_runtime_limits.c" "$SRC" -o "$TMP/p2" && "$TMP/p2" 2>&1 | head -8
