# Current Handoff

## Session status

Gates A-E remain closed and normative. The **Minimal Reference Implementation — smallest testable host/reference checkpoint** is now complete and tested.

## Frozen topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

## Frozen platform direction

**STM32U575ZI / NUCLEO-U575ZI-Q**, I2C primary, SPI secondary, UART/USART diagnostic/control. Hardware acquisition is not assumed.

## Continuity check

- **Gate A:** exact event/dependency semantics are frozen, including `EventRef={slot_id,generation}`, explicit dependency classes, FIFO admission versus eligibility-driven execution, and retained quarantine.
- **Gate B:** observable fault taxonomy and evidence-bounded association are frozen; `association precision <= evidence precision`.
- **Gate C:** deterministic bounded recovery policy is frozen with RETRY, REINIT_OR_RESET, DEGRADE, ESCALATE and four recovery-action transitions.
- **Gate D:** formal safety/termination/boundedness/identity/release/transaction properties are specified; the 33,792-context audit remains model-level evidence.
- **Gate E:** P0-P4, W01-W14, deterministic injection, fixed capacities, trace schema, metrics, and evidence boundaries are frozen.

These gates are one chain: event semantics constrain fault association; fault context constrains policy; policy/recovery interacts with scheduler/quarantine semantics; formal properties define correctness; the experimental protocol makes those properties comparable and reproducible.

## What was implemented

Directory: `reference/`

- ISO C11 host reference.
- CMake build.
- Fixed `EventSlot[20]` storage (`QMAX=16`, `XMAX=4`).
- Queue stores slot IDs; quarantine retains the same event slot and does not duplicate records.
- Four fixed dependency entries per event (`DMAX=4`).
- One fixed recovery episode (`EPMAX=1`).
- 8-bit EventRef generation; generation wrap fails closed instead of recycling.
- Deterministic first-eligible scheduler scan.
- Fixed-size `PolicyDecision` and P0-P4 policy variants.
- Deterministic software fault injection keyed by EventRef/action index.
- W01-W14 executable correctness scenarios.
- Gate-D-oriented policy/property assertions.
- Stable trace identifiers and deterministic CSV trace serialization.
- Static resource accounting and allocator audit.

## Verification result

Host C11/CMake build passed. `ctest` passed the W01-W14 suite plus recovery-bound, policy-property, trace-metadata, and static-accounting checks.

Host layout observed in this build:

- Runtime: 8164 bytes
- EventSlot: 84 bytes
- TraceRecord: 24 bytes
- fixed trace pool: 6144 bytes

Allocator source/symbol audit found no runtime allocator path in the reference implementation/test executable.

## Important implementation qualification

The minimal prototype intentionally implements exact event/transaction recovery as the executable recovery target. For `SERVICE_ONLY`, `PERIPHERAL_ONLY`, and `UNKNOWN_AMBIGUOUS`, it does not invent an event target; where broader recovery is not implemented safely, it fails closed to terminal escalation. This is an implementation boundary, not a change to Gate B/C semantics.

`EPMAX=1` is explicit. W10 tests the bounded second-episode outcome rather than hiding additional recovery storage.

## Exact next task

The next chat should **not** redesign Gates A-E. It should review the committed host reference implementation against the frozen contracts, close any concrete semantic/test contradictions, then prepare the next smallest checkpoint for reproducible host experiment execution if the reference remains consistent.

The next likely boundary is: **host reference experiment harness + frozen trace corpus + matched P0-P4 execution**, still without claiming MCU or physical evidence.

## Non-goals

Do not yet:

- integrate full STM32U575 firmware;
- claim MCU RAM/Flash/timing;
- perform physical fault injection;
- add RTOS/framework layers;
- add unrelated peripherals;
- optimize before correctness;
- claim novelty, patentability, robustness, generalization, or statistical significance.
