# Project State — Canonical Current Snapshot

**Last reconciled:** 2026-10-22  
**Project:** Embedded Runtime Resilience  
**Repository:** SujitSaiY2007/embedded-runtime-resilience  
**Current state:** **Software/research scope finalized; Plan 2.0 hardware bring-up active, paused at ST-LINK/GDB initialization.**

> Current hardware status is maintained in [Plan2.0/CURRENT_STATE.md](Plan2.0/CURRENT_STATE.md). The historical software/research findings below remain valid; the old “hardware is future work” wording is superseded by active Plan 2.0 bring-up. As of 2026-10-22, board-only USB detection, ST-LINK firmware upgrade, and a generated empty-project build are user-verified. Debugger initialization fails; firmware flash/execution and sensor operation are not verified.

## 1. Finalized deliverable

The repository contains:
- frozen Gates A–E and protected C reference runtime;
- deterministic host experiment sources and frozen K.10 result report;
- adversarial technical-distinction review K.10.1–K.10.4;
- evidence-bounded final research conclusion;
- K.11 software synthesis and future hardware handoff;
- K.12 virtual embedded-system demo, Python bridge, browser UI and tests;
- curated project documentation under `docs/`;
- historical checkpoint records and decision logs.

## 2. Branch status

- `main`: finalized reader-facing documentation and approved software/research implementation.
- `exp`: retained unchanged at `ab766b47ce7bae2791028cea22b7915f8debc41c` as frozen research baseline.
- `feature/k10-4-final-technical-conclusion-2026-10-13`: preserved historical integration branch; not the current presentation entry point.

Always query GitHub for live branch heads before a new write. This snapshot is a dated record, not a substitute for fetching current refs.

## 3. Verification provenance

The user reported successful local CMake/CTest and UI-contract test runs and a working browser demo on 2026-10-13. These are user-run observations. The remote GitHub review did not independently run the Windows toolchain or browser; do not call these CI-verified.

## 4. Research conclusion

The frozen K.10 campaign contains 16 case families × 5 variants × 5 repetitions = 400 deterministic host/reference executions. The reports support bounded advantages for P4 in selected cases, not universal superiority. Exact-event quarantine is shared across P0–P4. The CF16 trade-off records P2 success in one attempt versus P4 in three. QMAX=16 and EPMAX=1 are important constraints.

CF01 has a table/narrative conflict on P2 attempt count. For final presentation, use only the uncontested qualitative outcomes (P0 terminal escalation, P2 success, P4 success) and omit the disputed count from numerical comparisons. Frozen records remain unchanged.

## 5. Protected boundaries

Do not alter without a separately approved research change:
- `reference/src/ref_runtime.c`
- `reference/include/ref_runtime.h`
- `research/phase1_reference_implementation_design.md`
- `research/phase2_k9_methodology_lock.md`
- `research/phase2_k9_2_p4_advantage_novelty_design.md`
- frozen K.10 results and Gate A–E contracts.

Do not rerun the K.10 matrix to resolve editorial inconsistencies. Do not imply hardware validation was performed.

## 6. Plan 2.0 hardware continuation (current as of 2026-10-22)

The historical software/research closure remains valid, but the separate Plan 2.0 physical-demonstration work package is now active. Chat 05.2 is paused at ST-LINK/GDB initialization on the user-reported NUCLEO-L476RG (revision MB1136 C). Board-only USB detection, ST-LINK firmware upgrade, and a generated CubeIDE empty-project build are user-verified. SWD connection, flash, MCU execution, sensor wiring, sensor reads, fault injection, recovery and MCU-specific measurements remain unverified. The earlier NUCLEO-U575ZI-Q proposal remains a target-requirements discrepancy to assess, not a resolved equivalence. Continue from Plan2.0/CURRENT_STATE.md and Plan2.0/prompts/CHAT_05_3_STLINK_DEBUGGER_CONTINUATION_PROMPT.md. Do not claim hardware validation or imply no hardware task is active.

## 7. Reader navigation

Start with `README.md`, then `docs/PROJECT_OVERVIEW.md`, `docs/ARCHITECTURE_AND_REPOSITORY_MAP.md`, `docs/DEMONSTRATOR_GUIDE.md`, and the final K.10.4/K.11/K.12 reports. The root continuity files and `research/chat_records/` preserve detailed history.
