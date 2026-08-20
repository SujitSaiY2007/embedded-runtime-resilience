# Current Handoff

## Session status

Phase 0 topic validation is complete. The research-space was decomposed, six candidates were shortlisted, the leading candidates were attacked with academic/patent/vendor evidence, and the development topic was frozen. The zero-heap and event-quarantine additions were evaluated and integrated without changing the project's core problem.

Phase 1 architecture is now substantially defined. Sub-phases 1A–1D are complete. The project is currently in **Phase 1E — Formal Specification & Experimental Design**.

## Frozen development topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

**Short working title:** Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine

This topic is frozen for development. Do not restart topic ideation unless new evidence makes the mechanism technically invalid or infeasible.

## Core research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Core architecture constraints

1. **Zero-heap:** no runtime dynamic allocation in the recovery manager/reference firmware; use static bounded memory.
2. **Context/history:** policy uses a compact set of fault/event context and bounded recent recovery history.
3. **Bounded actions:** effective minimum action set is RETRY, REINIT_OR_RESET, DEGRADE, ESCALATE; reset and reinitialization remain distinct only if experimentally distinct on the selected peripheral.
4. **Event quarantine:** isolate the fault-associated event/transaction rather than indiscriminately flushing unrelated valid queued events, subject to dependency/order semantics.
5. **MPU:** target an MCU with usable MPU support where practical; use it for containment/isolation, not as a claimed invention.
6. **Event-driven firmware:** cooperative/resource-constrained reference architecture; heavyweight OS dependency is not required.
7. **Formal reasoning:** use tractable queue/recovery properties; do not claim full formal verification of the firmware.

## Important prior-art lessons

The project must not claim novelty for any individual ingredient. Generic peripheral recovery, selective restart, context-aware health management, graceful degradation, watchdog/recovery, event queues, zero-heap allocation discipline, MPU isolation, and formal invariants are established concepts.

The surviving contribution hypothesis is the **specific integrated mechanism and measured trade-off**: a compact deterministic zero-heap MCU policy using local fault context/history and dependency-aware event quarantine to reduce collateral interruption of unrelated event-driven service.

See `research/deep_prior_art_attack_topic_freeze.md` for the detailed prior-art attack.

## Phase 1 structure

### 1A — MCU / Development Board Selection — COMPLETE

Primary recommendation: **STM32U575ZI on NUCLEO-U575ZI-Q**.

Fallback: **Renesas EK-RA6M5**.

The board is not yet considered physically acquired. Acquisition verification remains open.

### 1B — Peripheral Testbed & Fault Model — COMPLETE

- I2C: primary experimental interface.
- SPI: secondary cross-protocol validation.
- UART/USART: diagnostic/control path initially.
- Prefer one low-cost I2C/SPI-capable external device for the minimum testbed.
- CAN deferred.
- Primary faults: deterministic software-injected timeout, non-response/error, repeated failure, invalid peripheral state, and event-triggered service failure.
- Hardware-relevant faults are a later validation layer.

See `research/phase1_peripheral_testbed_fault_model.md`.

### 1C — Formal Event Model — COMPLETE

The bounded event semantics cover identity, type, producer, consumer/service, peripheral/transaction association, criticality, dependency, ordering, state, fault association, and retry information.

Dependency cases are independent, ordered, or coupled/transactional.

The project uses **dependency-aware event quarantine**, not unconditional queue filtering or peripheral-wide queue flushing.

Quarantine means retained but non-executable until an explicit permitted transition.

Core queue invariant:

`0 <= |Q| <= Qmax`

See `research/phase1_event_model.md`.

### 1D — Recovery Policy Design — COMPLETE

Policy abstraction:

`Action = Policy(FaultContext, RecoveryHistory, EventContext, ServiceCriticality)`

Initial context variables:

1. fault class;
2. fault recurrence;
3. attempt count;
4. previous action;
5. previous outcome;
6. service criticality;
7. event dependency status;
8. pending independent workload.

Effective action set:

`RETRY`, `REINIT_OR_RESET`, `DEGRADE`, `ESCALATE`.

Initial state machine:

`NORMAL -> FAULT_DETECTED -> CLASSIFIED -> QUARANTINED -> RECOVERING -> VERIFY -> SUCCESS/REASSESS -> RELEASED/DEGRADED/ESCALATED`

Every fault episode must terminate in SUCCESS, DEGRADED, or ESCALATED within a finite transition bound.

Initial policy ablations:

- P0 fixed retry;
- P1 context without history;
- P2 context + short history;
- P3 context + history + dependency-aware event quarantine.

See `research/phase1_recovery_policy_design.md`.

## Current Phase 1E — Formal Specification & Experimental Design

**Do not implement firmware yet.**

### 1E.1 Formal properties / invariants — NEXT

Define the minimal tractable formal specification covering:

- quarantine safety;
- unrelated-event preservation;
- queue boundedness;
- recovery termination;
- ordering preservation;
- fault-association correctness;
- bounded quarantine/recovery storage.

Select the lightest defensible validation method: state-transition reasoning, assertions, bounded model checking/model checking, or another practical method.

### 1E.2 Baseline definitions

Precisely specify fixed retry, fixed retry + peripheral reset/reinitialization, and the proposed mechanism. Define policy-ablation variants where useful. Use identical workloads and fault schedules across comparisons.

### 1E.3 Experimental protocol

Define workloads, event mixes, fault injection schedules, repetitions, configuration parameters, warm-up/reset rules, measurement points, logging, randomization/deterministic seeds where relevant, and reproducibility procedure.

### 1E.4 Measurement/data schema

Define exact metrics and a machine-readable experiment record covering detection/recovery/restoration latency, success, reset count, preservation, quarantine violations, lost/duplicated events, queue occupancy, CPU/RAM/Flash cost, recovery-state count, and energy where practical.

### 1E.5 Phase-1 design review / closure

Verify feasibility, safety, boundedness, reproducibility, falsifiability, measurement completeness, prior-art consistency, and implementation readiness.

**Phase 1 must NOT be marked complete until 1E.1–1E.5 pass.**

## Hardware reality and budget

No physical MCU board is currently assumed acquired. No physical measurements may be claimed before actual hardware execution.

Initial target hardware budget is approximately **₹3,100–₹3,500**, subject to current price/availability:

- NUCLEO-U575ZI-Q;
- breadboard;
- jumper wires;
- one low-cost I2C/SPI-capable peripheral.

Logic analyzer, external fault-injection hardware, second board, and oscilloscope are deferred unless experiments justify them.

## Research discipline

Do not:

- restart topic selection;
- add unrelated resilience features;
- equate complexity with novelty;
- claim patentability;
- claim novelty for individual established ingredients;
- invent physical measurements;
- treat host simulation as equivalent to MCU validation;
- expose patent-sensitive implementation details unnecessarily.

## Exact next task

**Begin Phase 1E.1 — Formal Properties / Invariants.**

Derive the formal specification directly from `research/phase1_event_model.md` and `research/phase1_recovery_policy_design.md`. Challenge each proposed property for correctness and usefulness. Then continue through 1E.2–1E.5 in order, updating continuity files after each consequential milestone.
