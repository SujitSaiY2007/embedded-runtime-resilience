#!/bin/sh
set -eu

HOST_EXPERIMENT="${HOST_EXPERIMENT:-${PWD}/reference/build/host_experiment}"
TMP_BASE="${TMPDIR:-/tmp}/embedded-runtime-replay-$$"
A="$TMP_BASE/a"
B="$TMP_BASE/b"
trap 'rm -rf "$TMP_BASE"' EXIT
mkdir -p "$A" "$B"

"$HOST_EXPERIMENT" "$A"
"$HOST_EXPERIMENT" "$B"

cmp "$A/host_summary.csv" "$B/host_summary.csv"
# Normalize path-independent raw traces: the trace file bytes must replay identically.
find "$A/traces" -type f -printf '%f\n' | sort > "$A/files"
find "$B/traces" -type f -printf '%f\n' | sort > "$B/files"
cmp "$A/files" "$B/files"
while IFS= read -r f; do
    cmp "$A/traces/$f" "$B/traces/$f"
done < "$A/files"

# Matched-input equivalence: every workload/schedule appears exactly once for each P0-P4 variant.
awk -F, 'NR==1{next} {key=$3 FS $4; count[key]++; variants[$3 FS $4 FS $2]=1} END {
    for (k in count) if (count[k] != 5) exit 2;
    if (count == 0) exit 3;
}' "$A/host_summary.csv"

exit 0
