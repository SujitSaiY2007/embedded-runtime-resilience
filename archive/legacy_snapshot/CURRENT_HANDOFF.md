# Current Handoff — Finalized Software Project

**Last reconciled:** 2026-10-13  
**Status:** K.10–K.12 software/research scope closed. Physical hardware validation is future work.

## Current truth

The repository now presents the project as a research case study with a live software demonstrator. The C reference runtime is the recovery-policy authority. The Python bridge invokes the C CLI, and the browser displays outcomes and traces.

The user reported local CTest/UI-contract success and a working browser demo. This is user-run verification, not independently reproduced CI.

## Research findings to present

- K.10: 16 case families × 5 variants × 5 repetitions = 400 deterministic host/reference executions.
- P4 advantages are bounded to selected cases; no universal-superiority claim.
- Exact-event quarantine is shared across P0–P4.
- CF16 records P2 success in one attempt and P4 in three attempts.
- QMAX=16 and EPMAX=1 constrain interpretation.
- CF01's P2 attempt count is inconsistent across frozen table/narrative sources. Present the uncontested outcomes and omit the disputed count from comparisons.

## Do not do

- Do not edit protected runtime/Gate files or frozen K.10 results as part of documentation work.
- Do not rerun the K.10 matrix to force agreement.
- Do not claim hardware implementation, flashing, fault injection or measurements.
- Do not change `exp` as part of public-facing documentation overhaul.

## Next use of this repository

Generate a standalone professional report/presentation from the curated docs and primary research sources. Hardware validation may be proposed as future work. Start with `README.md`, then `docs/PROJECT_OVERVIEW.md`, `docs/ARCHITECTURE_AND_REPOSITORY_MAP.md`, `docs/DEMONSTRATOR_GUIDE.md`, and the K.10.4/K.11/K.12 reports.
