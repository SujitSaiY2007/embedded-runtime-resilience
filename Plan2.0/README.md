# Plan 2.0 — Reference Overhaul + Hardware Demonstration

**Status:** Active planning and execution framework  
**Control branch:** `main` only  
**Repository:** [embedded-runtime-resilience](https://github.com/SujitSaiY2007/embedded-runtime-resilience)

## Purpose

Plan 2.0 begins the next phase after the software/reference-model demonstrator: conduct a defensible, source-verified literature and reference overhaul, and build and validate a physical hardware demonstrator without misrepresenting host-model results as MCU evidence.

## Non-negotiable rules

1. **Work only on `main`.** Do not create, switch to, merge from, or write to any other branch for Plan 2.0.
2. **Preserve existing work.** Do not overwrite or delete the protected C reference runtime, tests, frozen experimental results, Gate A–E contracts, prior-art analyses, or dated research records.
3. **Archive, do not discard.** A historical snapshot of pre-Plan-2.0 non-code documentation and preliminary reference material is retained under `archive/legacy_snapshot/`. Original paths remain intact during setup so history and links are not lost.
4. **No unsupported claims.** The current 400-run campaign is deterministic host/reference-model evidence. It is not physical MCU evidence and does not prove universal P4 superiority, legal novelty, non-obviousness, or patentability.
5. **Trace every source.** Do not claim a baseline was copied from a paper unless the specific source and design relationship are verified.
6. **Evidence before closure.** Record actual commands, toolchain/board versions, raw traces, configuration, commit SHA, and test outcomes. Distinguish user-reported checks from independently reproduced checks.

## Start here

1. [Current state and branch rules](CURRENT_STATE.md)
2. [Execution roadmap and chat sequence](EXECUTION_ROADMAP.md)
3. [Reference overhaul protocol](REFERENCE_OVERHAUL.md)
4. [Hardware demonstration plan](HARDWARE_DEMONSTRATION.md)
5. [Multi-chat continuity protocol](CHAT_PROTOCOL.md)
6. [Chat 00 — initialization and next-chat handoff](CHAT_00_INITIALIZATION.md)
7. [Chat 05 hardware compatibility audit](hardware/CHAT_05_HARDWARE_COMPATIBILITY_AUDIT.md)
8. [Chat 05.2 — detailed hardware bring-up prompt](prompts/CHAT_05_2_ZERO_BUDGET_HARDWARE_BRINGUP_PROMPT.md)
9. [Chat 05.2 handoff — paused at ST-LINK initialization](handoffs/CHAT_05_2_HANDOFF.md)
10. [Chat 05.3 — ST-LINK debugger continuation prompt](prompts/CHAT_05_3_STLINK_DEBUGGER_CONTINUATION_PROMPT.md)
11. [Chat 05.3 — bounded diagnosis handoff](handoffs/CHAT_05_3_HANDOFF.md)
12. [Archive index](../archive/README.md)

## Definition of done

- Verified, high-quality bibliography with publication-type and source-quality classifications, DOI/metadata checks, and source-to-design traceability.
- Revised literature review and novelty/gap analysis with claims proportionate to evidence.
- Safe, reproducible physical demonstration using the actual board and documented peripheral setup.
- MCU-specific measurements and raw artifacts, clearly separated from host-model results.
- Updated top-level README, project state, decision log, and next-chat handoff.
- Every chat closes with an evidence-backed handoff so the next chat can continue without rediscovery.
