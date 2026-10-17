# Plan 2.0 — Current State

**Snapshot date:** 2026-10-17  
**Execution branch:** `main` only  
**Phase:** Plan 2.0 initialized; reference overhaul and physical hardware validation not yet completed.

## Completed before Plan 2.0

- C11 reference runtime and tests.
- Virtual embedded system, scenario runner, Python bridge, and browser demonstrator.
- Frozen deterministic host/reference campaign: 16 case families × 5 policy variants × 5 repetitions = 400 executions.
- Evidence-bounded K.10 findings and K.10.1–K.10.4 distinction reviews.
- K.11 software synthesis/hardware handoff and K.12 software demonstrator audit.

## Not yet complete

- Full reference-by-reference metadata, venue quality, and relevance verification.
- Traceability from each relevant publication to design decisions, baselines/ablations, implementation, and the precise contribution claimed.
- Final manuscript literature review and reference cleanup.
- Physical firmware build, safe fault injection, recovery validation, and board-specific measurements.
- Independent hardware evidence; no physical validation may be claimed until performed and recorded.

## Evidence boundaries

The existing 400 executions are host/reference-model evidence. They do not measure MCU timing, memory, peripheral recovery, or hardware reliability. Exact-event quarantine is shared across P0–P4; do not present it as P4-exclusive. Report bounded advantages and trade-offs, not universal superiority.

## Hardware target gate

Earlier design documents proposed STM32U575ZI / NUCLEO-U575ZI-Q. The user has also identified an STM32 NUCLEO-L476RG board. Before implementation, compare the actual board and silicon capabilities with the project's MPU/security/peripheral requirements. Do not silently treat these boards as interchangeable. Record the final board, revision, MCU, debugger/interface, and reason for selection in a hardware decision.

## Next action

Chat 01: inventory and audit the preliminary reference set before changing the manuscript bibliography. In parallel, gather exact board and component information, but do not alter protected runtime code until the hardware adapter design and acceptance tests are reviewed.
