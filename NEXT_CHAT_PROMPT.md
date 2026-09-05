# Next Chat Prompt — Host Reference Experiment Harness

Copy/paste the following prompt into the next ChatGPT chat.

---

You are continuing my embedded-systems research project from the canonical GitHub repository:

`SujitSaiY2007/embedded-runtime-resilience`

This is a continuation, not a restart. GitHub `main` is the durable source of truth.

## Mandatory startup reading

Read, in order:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `CHAT_CONTINUITY_PROTOCOL.md`
6. `research/phase1_gateA_event_model_final.md`
7. `research/phase1_gateB_fault_model_final.md`
8. `research/phase1_gateB_learning_summary.md`
9. `research/phase1_gateC_recovery_policy_final.md`
10. `research/phase1_gateD_formal_properties_final.md`
11. `research/phase1_gateE_experimental_protocol_final.md`
12. `research/phase1_reference_implementation_design.md`
13. `reference/README.md`
14. `reference/docs/minimal_reference_implementation.md`
15. `reference/tests/canonical_workloads.md`
16. relevant files under `reference/include`, `reference/src`, and `reference/tests`

Then provide a concise continuity check: frozen topic/question/platform; Gate A-E results; host reference implementation status; test result; exact next task; explicit non-goals.

## Frozen research

Topic:

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Research question:

Can a compact deterministic software-only recovery policy use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

Platform direction: **STM32U575ZI / NUCLEO-U575ZI-Q**; I2C primary, SPI secondary, UART/USART diagnostic/control. Hardware availability is not assumed.

## Frozen Gates A-E

Do not redesign them without identifying a concrete contradiction.

- Gate A: `EventRef={slot_id,generation}`; explicit INDEPENDENT/ORDERED/COUPLED dependencies; FIFO admission versus eligibility; retained quarantine.
- Gate B: observable I2C fault taxonomy and four evidence-bounded association levels under `association precision <= evidence precision`.
- Gate C: RETRY, REINIT_OR_RESET, DEGRADE, ESCALATE with `T1 RETRY #1 -> T2 RETRY #2 -> T3 REINIT_OR_RESET -> T4 terminal`, maximum four recovery-action transitions.
- Gate D: quarantine, association, preservation/blocking, dependency, termination, resource, identity, release, coupled-transaction, and decision-table properties.
- Gate E: P0-P4, W01-W14, deterministic fault schedules, `QMAX=16`, `XMAX=4`, `DMAX=4`, `EPMAX=1`, trace schema, metrics, and evidence boundaries.

## Current implementation checkpoint

`reference/` contains the smallest host/reference prototype.

Implementation decisions are already fixed:

- ISO C11 + CMake.
- 20 fixed event slots (`QMAX+XMAX`).
- queue stores slot IDs; quarantined events remain in the same slot pool and are removed from the normal queue, avoiding duplicate storage.
- four dependency entries per event.
- one active recovery episode.
- 8-bit per-slot generation starting at 1; generation wrap fails closed.
- deterministic first-eligible queue scan.
- fixed-size policy decision and P0-P4 variant selector.
- deterministic software fault injection keyed by EventRef and action index.
- stable trace IDs and fixed-buffer CSV serialization.
- no runtime allocator calls in the reference implementation.

Host verification already passed: W01-W14, recovery-bound, policy-property, trace-metadata, and static-accounting tests.

Current host layout evidence: Runtime 8164 bytes; EventSlot 84 bytes; TraceRecord 24 bytes; fixed trace pool 6144 bytes. These are host C-layout measurements only.

## ONLY TASK NOW

Review the actual committed reference implementation against Gates A-E, then build the **smallest reproducible host experiment harness and trace corpus** for matched P0-P4 execution.

The harness should:

1. consume explicit workload/fault-schedule records rather than hidden test behavior;
2. run matched variants P0-P4 on identical workload/fault inputs where applicable;
3. emit the frozen Gate E trace identifiers and outcome/correctness fields;
4. preserve raw input schedules and generated traces;
5. calculate only the frozen host/reference correctness and host-performance metrics that can be measured honestly;
6. flag capacity-confounded runs explicitly;
7. keep host evidence separate from future MCU/physical evidence;
8. add tests for deterministic replay and matched-input equivalence;
9. avoid adding framework abstractions or premature MCU integration.

Before changing semantics, stop and document any genuine contradiction with Gates A-E. Do not silently patch the contracts.

## Explicit non-goals

Do not yet:

- perform STM32U575 firmware integration;
- claim MCU timing/RAM/Flash;
- perform physical fault injection;
- add an RTOS;
- add unrelated peripherals;
- add machine learning or a weighted recovery score;
- claim statistical significance, generalization, novelty, or patentability.

Stop at the smallest reproducible host-experiment checkpoint and update `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, and implementation decision records from the actual repository state.

---
