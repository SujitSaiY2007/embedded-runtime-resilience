# Plan 2.0 — Current State

**Snapshot date:** 2026-10-22  
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

## Current hardware bring-up status (Chat 05 / 05.2)

- STM32CubeIDE is installed and open. The user created a generated STM32L476RG-family Empty Project; its empty-project build screenshot reported 0 errors and 1 warning. This is not evidence of custom firmware, flashing, sensor operation, or recovery.
- The user reported that the physical board was not connected during IDE setup.
- The zero-budget component inventory and unknowns are recorded in [Chat 05.2 prompt](prompts/CHAT_05_2_ZERO_BUDGET_HARDWARE_BRINGUP_PROMPT.md) and [Chat 05.2 handoff](handoffs/CHAT_05_2_HANDOFF.md).
- Physical sensor wiring remains **BLOCKED** until the exact board/module/cable, pinout, supply and logic levels, pull-ups, and board routing are verified. Candidate PB9/D14 SDA and PB8/D15 SCL mappings are not wiring approval.
- The earlier NUCLEO-U575ZI-Q target versus the user-selected STM32L476RG family remains a research requirements discrepancy to resolve explicitly.
- No additional hardware or purchases are permitted; budget remains ₹0.

## Next action

Execute [Chat 05.2 — Zero-Budget Hardware Bring-Up](prompts/CHAT_05_2_ZERO_BUDGET_HARDWARE_BRINGUP_PROMPT.md) using the detailed gates and inventory. Work only on `main`, inspect the live head first, and stop at any unresolved safety/compatibility gate. Do not claim physical validation until supported by raw hardware evidence.
