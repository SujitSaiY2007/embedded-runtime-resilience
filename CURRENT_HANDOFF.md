# Current Handoff

## Session status

Gates A-E remain closed and normative. The Minimal Reference Implementation remains the smallest executable host/reference checkpoint; this session adds the first explicit host experiment harness layer without changing the gates.

## Frozen topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

## Frozen platform direction

**STM32U575ZI / NUCLEO-U575ZI-Q**, I2C primary, SPI secondary, UART/USART diagnostic/control. Hardware acquisition is not assumed.

## Continuity check

- **Gate A:** exact event/dependency semantics remain frozen, including `EventRef={slot_id,generation}`, explicit dependency classes, FIFO admission versus eligibility-driven execution, and retained quarantine.
- **Gate B:** observable fault taxonomy and evidence-bounded association remain frozen; `association precision <= evidence precision`.
- **Gate C:** deterministic bounded recovery policy remains frozen with RETRY, REINIT_OR_RESET, DEGRADE, ESCALATE and four recovery-action transitions.
- **Gate D:** formal safety/termination/boundedness/identity/release/transaction properties remain frozen; the 33,792-context audit remains model-level evidence.
- **Gate E:** P0-P4, W01-W14, deterministic injection, fixed capacities, trace schema, metrics, reset/repetition rules, and evidence boundaries remain frozen.

## Reference implementation audit result

The committed host implementation is consistent with the main Gate A storage/identity/quarantine contracts at its declared prototype boundary:

- one `EventSlot[20]` pool;
- queue stores slot IDs only;
- quarantined events retain the same slot and leave the normal queue;
- explicit four-entry dependencies;
- one active recovery episode (`EPMAX=1`);
- 8-bit generation starting at 1 with fail-closed wrap;
- deterministic first-eligible scheduler scan;
- deterministic software injection keyed by `EventRef` and action index;
- fixed policy result and fixed trace storage.

A concrete implementation qualification was reaffirmed rather than silently changed: the executable recovery path directly supports exact event/transaction targeting. `SERVICE_ONLY`, `PERIPHERAL_ONLY`, and `UNKNOWN_AMBIGUOUS` do not fabricate an event target; unsupported broader-scope recovery fails closed. This is an implementation boundary, not a Gate B/C semantic amendment.

No semantic gate contradiction was used to justify changing the frozen contracts.

## Host experiment harness checkpoint

Added under `reference/experiments/`:

- `workloads.txt` — explicit W01-W14 workload records.
- `fault_schedules.txt` — explicit deterministic fault/recovery schedules.
- `harness.c` — smallest input-driven matched P0-P4 host runner reusing the existing reference runtime.
- `run_host_experiment.sh` — reproducible build/run entry point.
- `RESULTS_SCHEMA.md` — summary-field definitions and evidence boundary.
- replay/input-consistency test material.

The harness writes one matched summary row for each `(workload, schedule, variant)` combination and fixed-buffer runtime traces. It records explicit capacity-confounding and trace-completeness flags rather than treating capacity or trace loss as ordinary policy performance.

The harness intentionally does not implement a second resilience framework, randomized campaign, MCU timing path, or physical fault path.

## Verification status

The pre-existing reference test suite is documented as passing on `main` for W01-W14 plus bounded recovery, policy-property, trace-metadata, and static-accounting checks.

This session added new harness code but **did not obtain a successful local build/CTest execution from the connected GitHub environment**. The repository currently has no discoverable GitHub Actions workflow at the expected `.github/workflows` paths through the available connector. Therefore the new harness is a committed implementation checkpoint, not yet a claimed executed-result corpus.

## Host layout evidence retained

- `sizeof(Runtime) = 8164` bytes
- `sizeof(EventSlot) = 84` bytes
- `sizeof(TraceRecord) = 24` bytes
- fixed trace pool = `6144` bytes

These remain host/reference observations only and must not be presented as STM32U575 RAM/Flash/timing measurements.

## Exact next task

Execute the new harness in a real local checkout/build environment, inspect and correct any compile/runtime issues, then generate and commit the first deterministic P0-P4 host trace corpus and summary from the explicit W01-W14 input records.

After that, add any narrowly justified oracle fixes needed to report the frozen Gate E correctness metrics honestly. Do not redesign Gates A-E.

## Explicit non-goals

Do not yet:

- integrate full STM32U575 firmware;
- claim MCU RAM/Flash/timing;
- perform physical fault injection;
- add RTOS/framework layers;
- add unrelated peripherals;
- add machine learning or weighted recovery scores;
- claim statistical significance, generalization, robustness, novelty, or patentability.
