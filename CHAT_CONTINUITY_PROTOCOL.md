# Chat Continuity Protocol — Embedded Runtime Resilience

## Current active state — 2026-10-25

The frozen software/reference scope remains finalized and protected. The bounded five-policy diagnostic hardware run is complete at the level supported by user-provided CubeIDE evidence. **The next active work package is journal-manuscript drafting and evidence/reference audit.**

Canonical current state: [PROJECT_STATE.md](PROJECT_STATE.md)  
Current hardware state and evidence boundary: [Plan2.0/CURRENT_STATE.md](Plan2.0/CURRENT_STATE.md)  
Latest handoff: [CURRENT_HANDOFF.md](CURRENT_HANDOFF.md)  
Latest hardware report: [Chat 11 five-policy diagnostic run](Plan2.0/results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md)  
Claude drafting prompt: [research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md](research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md)

## Canonical startup reading

1. `README.md`
2. `PROJECT_STATE.md` and `CURRENT_HANDOFF.md`
3. `Plan2.0/CURRENT_STATE.md` and `Plan2.0/EXECUTION_ROADMAP.md`
4. `docs/PROJECT_OVERVIEW.md` and `docs/ARCHITECTURE_AND_REPOSITORY_MAP.md`
5. Frozen K.10 result report, K.10.4 conclusion, K.11 synthesis, K.12 demonstrator audit and Gate A–E contracts.
6. Prior-art/reference-overhaul artifacts and relevant Plan 2.0 hardware reports.
7. `research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md`.

## Current hardware truth

The user-provided CubeIDE screenshots for the diagnostic five-policy run show `progress_stage=900`, `finished=1`, `overall_code=1`; baseline error slots 0; `nack_result[0..4]=-1` matching source-defined `E_NACK`; physical status values P0–P4 = 7,1,7,7,1; and successful post-recovery chip ID `0x60` plus release result for P1 and P4. This is one controlled address-NACK → I²C1 peripheral recovery/reinitialization → fresh BME280 ID read → runtime release run. It does not establish physical stuck-bus recovery, repeated-run reliability, MCU performance/resource metrics, or universal P4 superiority.

Matrix note: one screenshot showed `matrix_status[79]=1`, while the user stated that all matrix entries were 1 except the last. The complete 80-element array was not captured in a readable export, so preserve this as unresolved rather than making an all-80 claim. The firmware's 16 contexts are provisional and not proven equivalent to frozen CF01–CF16.

## Research evidence integrity rules

- Frozen host campaign: 16 case families × 5 policies × 5 repetitions = 400 deterministic host/reference executions. Do not rerun, overwrite or silently alter it.
- Keep host/reference evidence, source-derived properties, user-observed hardware values, and unmeasured expectations distinct.
- Never present the 80 embedded decisions as 80 physical experiments.
- Do not claim physical stuck SDA/SCL recovery, MCU timing/stack/Flash/RAM/energy measurements, statistical generalization, or universal P4 superiority without additional evidence.
- Preserve `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, Gate A–E contracts, frozen results, prior-art analyses and historical records.
- Work on `main` only. Do not create, delete, or switch branches.
- Verify citations through authoritative sources; never invent metadata, DOI, affiliations or experimental values.

## Required closeout

Record Chat ID/date, exact branch/commit SHA, changed files, checks actually performed and provenance, evidence limits, unresolved issues, and one exact next prompt. A GitHub documentation audit is not a hardware build or run. Never claim a test passed if it was not performed.
