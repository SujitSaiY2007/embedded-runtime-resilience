# Next Chat Prompt — Chat 09: Evidence Reconciliation and Hardware Integration Audit

Continue the existing project: https://github.com/SujitSaiY2007/embedded-runtime-resilience

**Repository branch policy: `main` only.** Do not create or switch branches.

## Starting status

Chat 08 is complete at the main milestone level. The user-provided CubeIDE screenshots show a successful build (0 errors, 0 warnings), successful flash/download verification, and terminal test result:

- `baseline_ok=1`
- `fault_attempted=1`
- `fault_nack_observed=1`
- `recovery_attempted=1`
- `post_recovery_read_ok=1`
- `post_recovery_chip_id=96 (0x60)`
- `sensor_error=0`
- `test_state=3`
- `test_finished=1`
- `test_report_code=8`

The debugger halted at the terminal report breakpoint. The user saved the screenshots. This is evidence of one successful controlled transaction-level NACK → recovery attempt → fresh sensor read on the physical NUCLEO-L476RG with BME280. It is **not** proof of physical stuck-bus recovery, repeated-run reliability, MCU performance, or universal P4 superiority.

## Read first

1. `README.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `Plan2.0/CURRENT_STATE.md`
5. `Plan2.0/README.md`
6. `Plan2.0/EXECUTION_ROADMAP.md`
7. `Plan2.0/results/CHAT_08_POLICY_HARDWARE_INTEGRATION_CANDIDATE_2026-10-25.md`
8. `Plan2.0/firmware/bme280_policy_integration/README.md`
9. `Plan2.0/firmware/bme280_policy_integration/main.c`
10. `reference/include/ref_runtime.h` and `reference/src/ref_runtime.c` for reading only.

Fetch current `main` HEAD and live contents before any repository edits. Do not assume previous descriptions match current files.

## Goals

1. Audit the firmware source and current report for consistency with the user-observed result.
2. Reconcile available runtime fields: policy variant, event admission result, fault-start result, decision action/reason, hardware action result, release result, event slot/generation and runtime trace count.
3. Use the actual screenshots/current code as evidence. If a field was not captured, mark it **not captured**; do not fabricate or infer its exact value.
4. Check that terminal report code 8 is assigned only after the full success path and that the terminal breakpoint behavior is intentional.
5. Update only relevant Chat 09 evidence/handoff documentation on `main`, with precise claims and clear limitations.
6. Determine whether the project can close the hardware demonstration phase or whether one specific, minimal validation gap remains. Avoid redundant baseline/NACK runs.
7. Prepare a concise next-step decision at the end.

## Non-negotiable constraints

- Do not modify `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, Gate A–E contracts, frozen 400-execution evidence, prior-art reviews, manuscript, or historic evidence.
- Preserve existing firmware backups and the user's saved screenshots.
- Do not change hardware wiring or request new components unless evidence requires it.
- Do not flash the board again unless a code change is necessary, builds cleanly, and the user explicitly approves.
- Do not claim physical stuck-bus recovery, statistical superiority, or MCU performance/memory results from the current run.
- No branch creation, deletion, switching, or changes outside `main`.

## Required deliverables

- An audit/result note for Chat 09.
- Updated `Plan2.0/CURRENT_STATE.md`, `Plan2.0/EXECUTION_ROADMAP.md`, and `CURRENT_HANDOFF.md` if the audit changes the state.
- A clear recommendation for whether a further hardware run is necessary.
- A Chat 10 prompt only if another bounded work package is justified; otherwise state that the current hardware milestone is complete and specify remaining project-level work.

Begin with repository/source audit and evidence reconciliation. Do not ask the user to repeat completed setup or upload source again.
