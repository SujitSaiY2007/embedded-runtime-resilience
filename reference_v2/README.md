# Reference Runtime v2 — Isolated Defect-Fix Candidate

This directory is an additive candidate. The protected canonical runtime under `reference/` remains unchanged.

## Fixes in this candidate

1. **Full-queue release:** `runtime_verify_and_release()` checks `queue_count >= QMAX` before changing the quarantined event or appending to the queue. It returns `OUTCOME_QUEUE_FULL` and leaves the episode/quarantine intact, allowing the caller to retry release after queue capacity becomes available.
2. **Generation exhaustion at 255 reuses:** `EventRef.generation` and the per-slot generation counter are widened to 16 bits in this isolated candidate. A regression test reuses a slot 300 times. This moves the stale-reference exhaustion point; it does not make wraparound mathematically impossible, so lifetime bounds still need documenting.
3. **Trace-cap observability:** the 256-record cap remains fixed to preserve bounded storage, but `trace_dropped_count` now increments (saturating at `UINT32_MAX`) whenever a record is omitted. This does not recover omitted records; it makes truncation observable.
4. **Invalid-target episode leak:** when retry/reinitialization or release encounters an invalid target reference, the candidate closes the episode as terminal escalation before returning `OUTCOME_STALE_REF`. This avoids leaving `episode_in_use` set indefinitely.

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
