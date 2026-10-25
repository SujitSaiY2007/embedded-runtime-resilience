# Next Work Prompt — Journal Manuscript Drafting and Evidence Audit

**Repository:** https://github.com/SujitSaiY2007/embedded-runtime-resilience  
**Branch policy:** `main` only. Do not create, delete, or switch branches.

The bounded five-policy hardware demonstration has been recorded from user-provided STM32CubeIDE evidence. The next primary work package is a rigorous, journal-quality manuscript draft.

## Read first

1. `README.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `Plan2.0/CURRENT_STATE.md`
5. `Plan2.0/results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md`
6. `docs/PROJECT_OVERVIEW.md`, `docs/ARCHITECTURE_AND_REPOSITORY_MAP.md`, and `docs/DEMONSTRATOR_GUIDE.md`
7. Frozen K.10 results, K.10.4 conclusion, K.11 synthesis, K.12 audit, Gate A–E contracts, prior-art and bibliography audit records
8. `research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md`

## Required work

Give Claude the repository link and the complete prompt in `research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md`. Claude should inspect the complete repository, build a claim-to-evidence ledger, verify the reference list against authoritative sources, select a suitable journal format, and draft a complete manuscript with figures/tables derived only from repository data.

## Evidence boundaries

- Frozen host/reference campaign: 16 case families × 5 policies × 5 repetitions = 400 executions.
- Latest physical run: one controlled wrong-address I²C NACK, followed by I²C1 peripheral recovery/reinitialization; P1 and P4 post-recovery BME280 ID reads returned `0x60` and release result 1.
- P0/P2/P3 ended in `R_TERMINAL`; do not call those sensor recoveries.
- 80 embedded runtime decisions are not 80 physical fault injections and are not proven identical to the frozen host case families.
- Matrix-status discrepancy: a screenshot shows `matrix_status[79]=1`; the user separately said all matrix entries were 1 except the last. Preserve this conflict until a complete readable export resolves it.
- Do not claim physical stuck-bus recovery, repeatability, MCU performance/resource measurements, or universal P4 superiority.
- Never rerun or overwrite the frozen 400-execution corpus or modify the protected reference runtime.

## Deliverables

Create an additive manuscript workspace (draft, evidence ledger, verified reference audit, figure/table plan, open-issues list). Mark missing author metadata as placeholders; do not invent affiliations or emails. Preserve any approved/frozen title and abstract found in the repository. Finish with changed-file list, commit SHA, reference-validation method, checks actually run, unresolved evidence gaps, and next steps.
