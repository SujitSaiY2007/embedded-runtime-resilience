# Reference Runtime v2 — Isolated Defect-Fix Candidate

This directory is an additive candidate. The protected canonical runtime under `reference/` remains unchanged.

## Fixes in this candidate

1. **Full-queue release:** `runtime_verify_and_release()` checks `queue_count >= QMAX` before changing the quarantined event or appending to the queue. It returns `OUTCOME_QUEUE_FULL` and leaves the episode/quarantine intact, allowing the caller to retry release after queue capacity becomes available.
2. **Generation exhaustion at 255 reuses:** `EventRef.generation` and the per-slot generation counter are widened to 16 bits in this isolated candidate. A regression test reuses a slot 300 times. This moves the stale-reference exhaustion point; it does not make wraparound mathematically impossible, so lifetime bounds still need documenting.
3. **Trace-cap observability:** the 256-record cap remains fixed to preserve bounded storage, but `trace_dropped_count` now increments (saturating at `UINT32_MAX`) whenever a record is omitted. This does not recover omitted records; it makes truncation observable.
4. **Invalid-target episode leak:** when retry/reinitialization or release encounters an invalid target reference, the candidate closes the episode as terminal escalation before returning `OUTCOME_STALE_REF`. This avoids leaving `episode_in_use` set indefinitely.

## P5/P6 comparator rules (candidate design)

- **P5 — reset-only:** if `reinit_safe`, immediately choose `ACT_REINIT_OR_RESET` with broad (`ASSOC_UNKNOWN`) target scope; otherwise terminal escalation. No retry action is permitted.
- **P6 — bounded exponential-backoff retry:** authorize retry while `retry_safe` and `attempt_count < 3`; otherwise terminal escalation. `policy_backoff_delay(index)` returns abstract delay units 1, 2, 4, 8, ... capped at 256 units. The C runtime does not sleep or measure elapsed time; a host harness must record/simulate the delay explicitly. Do not describe this as a physical timing measurement.

These are newly authored in-house comparators, not implementations copied from a published system. Their fairness must be checked against the same fault inputs and resource constraints before comparing results.

## Seven-policy host campaign

The additive `experiments/k10_v2_experiment.c` extends the 16-family scenario definitions to P0–P6. The runner refuses to overwrite existing evidence, runs twice, checks 16 × 7 × 5 = 560 rows, validates repetition stability, and compares SHA-256 hashes. P5/P6 are in-house comparators. P6 logs scheduled exponential-backoff delay in logical units; no wall-clock delay or MCU timing is measured. Results are host/reference-model evidence only.

Build and run from repository root:

```text
cmake -S reference_v2 -B reference_v2/build
cmake --build reference_v2/build
ctest --test-dir reference_v2/build --output-on-failure
python3 reference_v2/experiments/run_k10_v2.py --out research/evidence/host/v2_rerun_YYYY-MM-DD
```

Use a fresh date-stamped path. Keep both the output directory and its `.replay` sibling. Never point this runner at `reference/experiments/out`.

## Verification status

- Candidate source copied from canonical `reference/src/ref_runtime.c` at blob SHA `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81`.
- Header copied from canonical `reference/include/ref_runtime.h` at blob SHA `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`.
- Regression test source: `tests/test_runtime_edge_cases.c`.
- **Not yet compiled or executed in this change.** Do not treat the test source as a passing test until built and run in a compatible C environment.
- The original runtime, frozen K.10 campaign, and prior reports are not changed by these files.

## Intended local test

Compile `src/ref_runtime.c` and `tests/test_runtime_edge_cases.c` with the project's existing C standard and include path, plus any required platform flags. The runtime uses `write()` for CSV export; on Windows it maps to `_write()`. Integrate this test with the existing test harness after confirming the repository's actual build/test conventions.

## Acceptance conditions

- Full queue: first release attempt returns `OUTCOME_QUEUE_FULL` without assertion or state corruption; after one queue item is consumed, release succeeds.
- Invalid target: policy application returns `OUTCOME_STALE_REF` and clears `episode_in_use`, `episode.active`, and `active_fault_episode_id`.
- Generation: 300 reuse cycles of one slot succeed with monotonically changing 16-bit generations.
- Trace cap: the buffer remains at 256 records and counts every dropped record.
- Existing canonical tests and all frozen evidence remain unchanged.
