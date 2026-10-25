# Chat 10 — Final Hardware Validation and UI Integration Readiness

**Date:** 2026-10-25  
**Branch:** `main` only  
**Status:** Source audit and protocol design completed; repeated-trial execution is pending. No new firmware build, flash, reset, or physical trial was performed by this audit.

## Objective and scope

Close the evidence gap around repeatability of the existing P4-integrated BME280 recovery demonstration and prepare an implementation-ready Chat 11 handoff. The user selected a target of five total trials. No firmware flashing is authorized unless the user explicitly approves it after reviewing the proposed source/build implications and a clean build.

## Verified starting evidence

The two CubeIDE screenshots from Chat 08 document the same successful run, not two trials. User-provided evidence records:

- build reported as 0 errors / 0 warnings and download verification successful;
- `baseline_ok=1`;
- `fault_attempted=1`, `fault_nack_observed=1`;
- `recovery_attempted=1`;
- `post_recovery_read_ok=1`, `post_recovery_chip_id=0x60`;
- `sensor_error=0`;
- `test_state=3`, `test_finished=1`, `test_report_code=8`;
- debugger stopped at the terminal reporting breakpoint.

This run is designated **Trial 1 (historical evidence)** for the requested five-trial target. It is a partial trial record: its exact build artifact hash, trial timestamp, and all auxiliary policy/runtime variables are not captured in the current evidence summary. It must not be treated as independently reproduced by this audit.

## Source audit

Read-only inspection of `Plan2.0/firmware/bme280_policy_integration/main.c` (blob SHA `8928bb9f0e5991461783e01afdfc31a44379c430`) confirms the existing test performs the following sequence:

1. Initialize I2C1 and read BME280 ID register `0xD0` at 7-bit address `0x76`; expected ID is `0x60`.
2. Initialize the runtime with `VAR_P4_INTEGRATED` and admit a peripheral-read event.
3. Attempt a read at address `0x77` as a controlled NACK stimulus. Continue only if the driver observes `ERR_NACK`.
4. Start an exact-associated `FAULT_I2C_NACK` episode and call `policy_decide()`.
5. If the decision is `ACT_REINIT_OR_RESET`, reset/reinitialize the MCU I2C1 peripheral via `i2c_recover()`.
6. Perform a fresh BME280 chip-ID read at `0x76`.
7. Mark verification fields and call `runtime_verify_and_release()` only if the fresh read succeeds with ID `0x60`.
8. Record terminal variables and stop at `__BKPT(0)`, then an infinite loop.

The controlled fault is a transaction-level address NACK, not an electrically stuck SDA/SCL bus. The existing program is one-shot and halts at its terminal breakpoint; repeated trials require restarting execution from reset with the same already-programmed image. A new flash is not inherently required if that exact image is already present and unchanged, but image identity has not been independently verified here.

## Five-trial protocol and predeclared criteria

**Target:** five total trials. Trial 1 is the existing Chat 08 run. Trials 2–5 are pending a user-operated reset/re-run procedure and evidence capture. If the firmware image or source changes, do not combine results across image versions without explicitly identifying the change.

For each new trial:

1. Record trial number, local date/time, board identity, firmware/source revision, and whether a flash occurred. Do not flash unless separately approved.
2. Start the same unchanged firmware from reset in the existing CubeIDE debug setup. Do not change wiring or force electrical faults.
3. Capture the build/download state only if a build or download is actually performed; do not claim a new build or flash otherwise.
4. Capture the debugger-visible terminal values: `baseline_ok`, `fault_attempted`, `fault_nack_observed`, `recovery_attempted`, `post_recovery_read_ok`, `post_recovery_chip_id`, `sensor_error`, `test_state`, `test_finished`, `test_report_code`.
5. Where visible, also capture `policy_variant`, `policy_event_admit_result`, `policy_fault_start_result`, `policy_decision_action`, `policy_decision_reason`, `policy_action_attempted`, `hardware_action_result`, `policy_release_result`, `policy_event_slot`, `policy_event_generation`, `policy_runtime_bytes`, and `policy_runtime_trace_count`. Label any unavailable value “not captured”; never infer it from source.
6. Preserve a screenshot or raw export for each trial before restarting for the next one.

### Trial acceptance

A trial is a **pass** only when all required terminal evidence is captured and consistent with the intended path:

- initial baseline read succeeded;
- controlled NACK was attempted and observed;
- P4 decision selected the supported I2C1 reinitialization action;
- recovery action was attempted and returned success;
- a fresh post-recovery read succeeded and returned ID `0x60`;
- runtime event release succeeded;
- terminal state is `test_state=3`, `test_finished=1`, `test_report_code=8`.

A failure or timeout is recorded as **fail**, not silently retried. A trial with missing or contradictory evidence is **inconclusive**. Preserve the first outcome; any diagnostic rerun must be a separately numbered trial. Report the actual pass/fail/inconclusive count over the five trials and do not extrapolate to all I2C faults or long-term reliability.

**Current tally:** Trial 1: user-evidence pass for the bounded primary path, with incomplete auxiliary metadata. Trials 2–5: not yet run. Therefore the five-trial repeatability objective is **not complete**.

## Proposed validation matrix

| Candidate | Current disposition | Reason / acceptance boundary |
|---|---|---|
| Existing baseline + controlled NACK + P4 reinitialization + fresh ID read | Trial 1 evidenced; reuse | No need to repeat it as a separate new baseline task |
| Trials 2–5 using same image, reset/re-run only | Pending user execution | Collect per-trial terminal evidence; no new flash required if image unchanged |
| Existing debugger-session auxiliary-field inspection | Optional, non-invasive | Record only fields actually visible |
| Flash/text and static RAM accounting from existing map/build outputs | Not yet measured in this audit | Requires available artifact inspection and explicit units/scope |
| Policy-decision and end-to-end recovery timing | Not measured | Requires a defensible instrumentation method and overhead accounting |
| P0–P4 hardware comparison | Deferred | Current physical run exercises P4 only |
| Physically stuck SDA/SCL recovery | Deferred | Requires separately reviewed safe fault injection; no shorts or unsafe line forcing |
| Stack/energy measurements | Not established | Do not claim without a defensible target-specific method |

## UI integration readiness

The firmware currently exposes debugger-visible variables, not a verified host telemetry protocol. The inspected source does not establish that it emits a machine-readable serial message. Although board documentation and ST-LINK setup previously indicated a Virtual COM Port capability, that alone does not prove the current firmware sends telemetry over it.

Chat 11 should first inspect the actual board USB/VCP path and the existing UI/Python bridge, then design the smallest truthful telemetry contract. Prefer newline-delimited, versioned messages over the existing supported host interface if verified feasible. Do not implement or claim live telemetry until the firmware actually transmits it and the host demonstrably receives it.

Candidate fields already present in firmware include:
- sensor address and chip ID, baseline and post-recovery read results;
- controlled-fault attempted/observed flags;
- recovery attempted/result;
- P4 policy variant, decision action/reason and action-attempt flag;
- runtime release result, terminal state and report code.

The source declares these variables, but their declaration alone is not a serial protocol. Timestamps, monotonic sequence numbers, build identifiers and message framing are not currently established as transmitted fields.

## Preservation and provenance

- Work branch remains `main` only.
- Protected files `reference/include/ref_runtime.h` and `reference/src/ref_runtime.c` were read-only and are not changed by this plan.
- Frozen 400-execution evidence, Gates A–E, prior-art analysis, manuscript, historical reports, user screenshots, and firmware backups must remain untouched.
- No compiler, unit test, CubeIDE, local screenshot, MCU, reset, or flash operation was run by this GitHub-side audit.
- Do not represent the four future trials, resource measurements, timing measurements, or physical stuck-bus test as completed.

## Remaining work and exit status

1. User performs Trials 2–5 by resetting/re-running the unchanged programmed image and supplies the four terminal evidence captures. No flash is authorized by this report.
2. Reconcile each trial against the acceptance criteria and publish the actual tally.
3. Inspect existing map/build outputs if available; otherwise document the resource measurement blocker.
4. Update the current state and handoff with actual outcomes.
5. Start Chat 11 only after the trial record is complete or the user explicitly chooses to proceed with the repeatability gap documented.

**Chat 10 status: IN PROGRESS — procedure defined; repeated-trial execution and final UI-readiness closure remain pending.**
