# Host Experiment Harness Decisions

## H-001 — Explicit input records
Workload and fault schedules are stored as repository files under `reference/experiments/`. The harness reads them at runtime rather than encoding canonical scenarios solely in control flow.

## H-002 — Matched P0-P4 execution
Each workload/schedule pair is executed once for each P0-P4 variant using the same parsed input records. No variant-specific workload mutation is permitted in the harness.

## H-003 — Reuse the reference runtime
The harness calls the existing `ref_runtime` API and does not introduce a second scheduler, recovery framework, heap-backed data model, or policy implementation.

## H-004 — Host evidence boundary
Harness outputs are host/reference software-injection evidence only. They are not MCU timing/RAM/Flash, energy, physical-fault, statistical-significance, generalization, novelty, or patentability evidence.

## H-005 — Raw trace preservation
The committed `TraceRecord` CSV is preserved as the raw low-level runtime trace. Experiment-level run/workload/schedule/variant metadata remains in the summary/input layer until the runtime trace schema is deliberately expanded.

## H-006 — Capacity-confounding rule
Runs affected by QMAX/XMAX/EPMAX or fixed trace-pool limits are explicitly marked rather than interpreted as evidence of recovery superiority/inferiority.

## H-007 — Verification honesty
No new harness pass/corpus result is claimed until an actual local build, execution, and replay check has been observed. The connected GitHub environment did not expose a runnable CI workflow for this repository.
