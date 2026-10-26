# Reference Runtime v2 — Isolated Defect-Fix Candidate

This directory is an additive candidate. The protected canonical runtime under `reference/` remains unchanged.

## Fixes in this candidate

1. **Full-queue release:** `runtime_verify_and_release()` checks `queue_count >= QMAX` before changing the quarantined event or appending to the queue. It returns `OUTCOME_QUEUE_FULL` and leaves the episode/quarantine intact, allowing the caller to retry release after queue capacity becomes available.
2. **Invalid-target episode leak:** when retry/reinitialization or release encounters an invalid target reference, the candidate closes the episode as terminal escalation before returning `OUTCOME_STALE_REF`. This avoids leaving `episode_in_use` set indefinitely.

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
- Existing canonical tests and all frozen evidence remain unchanged.
