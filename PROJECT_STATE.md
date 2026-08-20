# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`
**Status:** Development topic frozen; Phase 1 design is in progress. Sub-phases 1A–1D are complete; sub-phase 1E — Formal Specification & Experimental Design — is now active.
**Project mode:** Solo software-dominant embedded-systems project
**Primary ambition:** Research-grade implementation with publication potential and possible patent pathway if supported by evidence and professional assessment.

## Frozen development topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

### Short working title

**Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

## Core research question

Can a compact, deterministic, software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Phase 1 structure

Phase 1 — Preparation / System Design and Experimental Planning

- **1A — MCU / Development Board Selection — COMPLETE**
- **1B — Peripheral Testbed & Fault Model — COMPLETE**
- **1C — Formal Event Model — COMPLETE**
- **1D — Recovery Policy Design — COMPLETE**
- **1E — Formal Specification & Experimental Design — ACTIVE**
  - 1E.1 Formal properties / invariants
  - 1E.2 Baseline definitions
  - 1E.3 Experimental protocol
  - 1E.4 Measurement and data schema
  - 1E.5 Phase-1 design review / closure

Phase 1 is NOT complete until 1E.1–1E.5 are closed.

## Phase 1A — MCU / board decision

**Primary recommendation:** STM32U575ZI on NUCLEO-U575ZI-Q.

**Fallback/alternative:** Renesas EK-RA6M5.

The primary recommendation is based on native Cortex-M33 MPU support, single-core execution, adequate but bounded memory, broad I2C/SPI/UART peripheral access, interrupt/timer resources, mature tooling, and low-power capability without introducing unnecessary multicore experimental variables.

The board is **not yet considered physically acquired**. Current price, Indian availability, genuine sourcing, and accessory availability remain acquisition-gate checks.

## Phase 1B — Peripheral testbed and fault model

Primary interface: I2C.

Secondary interface: SPI.

UART/USART: diagnostic/control path initially, not a separately purchased peripheral requirement.

Prefer one low-cost external device supporting both I2C and SPI where practical. CAN is deferred.

Primary faults: deterministic software-injected timeout, non-response/error, repeated communication failure, invalid peripheral state, and event-triggered service failure.

Hardware-relevant faults are a later validation layer. Naturally occurring faults are optional and not the primary experimental source.

See `research/phase1_peripheral_testbed_fault_model.md`.

## Phase 1C — Formal event model

Events have bounded semantic fields for identity, type, producer, consumer/service, peripheral/transaction association, criticality, dependency, ordering, state, fault association, and retry information.

Dependency semantics distinguish independent, ordered, and coupled/transactional events.

The architecture uses **dependency-aware event quarantine**, not unconditional queue filtering and not peripheral-wide queue flushing.

Quarantine means retained but non-executable until an explicit permitted transition.

Core queue invariant:

`0 <= |Q| <= Qmax`

Core preservation metric and quarantine-violation definition are recorded in `research/phase1_event_model.md`.

## Phase 1D — Recovery policy design

The policy is deterministic and bounded:

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

Effective minimum action set:

- `RETRY`
- `REINIT_OR_RESET`
- `DEGRADE`
- `ESCALATE`

Reinitialize and peripheral reset remain separate only if the selected peripheral implementation provides experimentally distinct semantics.

Initial state machine:

`NORMAL -> FAULT_DETECTED -> CLASSIFIED -> QUARANTINED -> RECOVERING -> VERIFY -> SUCCESS/REASSESS -> RELEASED/DEGRADED/ESCALATED`

Every fault episode must terminate in `SUCCESS`, `DEGRADED`, or `ESCALATED` within a declared finite transition bound.

Policy variants for later ablation:

- P0 fixed retry;
- P1 context without history;
- P2 context + short history;
- P3 context + history + dependency-aware event quarantine.

See `research/phase1_recovery_policy_design.md`.

## Current Phase 1E objective

**Formal Specification & Experimental Design**

The objective is to turn the architecture into a reproducible experimental specification before implementation.

### 1E.1 Formal properties / invariants

Define the smallest tractable set of properties covering:

- quarantine safety;
- unrelated-event preservation;
- queue boundedness;
- recovery termination;
- ordering preservation;
- fault-association correctness;
- bounded quarantine/recovery storage.

Select an appropriate lightweight validation method: state-transition reasoning, assertions, bounded model checking/model checking, or another practical method. Do not introduce heavyweight formalism merely for appearance.

### 1E.2 Baseline definitions

Precisely define and reproduce:

1. fixed retry;
2. fixed retry + peripheral reset/reinitialization;
3. proposed mechanism;
4. policy-ablation variants where useful.

Use identical workload and fault schedules across comparisons. Do not misrepresent sophisticated prior systems as simplistic baselines.

### 1E.3 Experimental protocol

Define workloads, event mixes, fault injection schedule, repetitions, configuration parameters, warm-up rules, reset rules, measurement points, logging, randomization/deterministic seeds where relevant, and reproducibility procedure.

### 1E.4 Measurement and data schema

Define exact measurements for:

- fault detection latency;
- recovery latency;
- service-restoration latency;
- recovery success;
- whole-system reset count;
- unrelated-event preservation;
- quarantine violations;
- lost/duplicated events;
- queue occupancy;
- CPU overhead;
- RAM footprint;
- Flash footprint;
- recovery-state count;
- energy where practical.

Define a machine-readable experiment record before collecting results.

### 1E.5 Phase-1 design review / closure

Verify that the final specification is:

- technically feasible on the selected platform;
- bounded and zero-heap;
- safe to test;
- reproducible;
- falsifiable;
- measurable;
- sufficiently small;
- consistent with prior-art positioning;
- ready for implementation.

Only after 1E.5 passes should Phase 1 be marked COMPLETE and implementation begin.

## Hardware budget constraint

Initial strategy is intentionally minimal. Target approximately ₹3,100–₹3,500 for the starting physical platform where current pricing permits:

- NUCLEO-U575ZI-Q;
- breadboard;
- jumper wires;
- one low-cost I2C/SPI-capable peripheral.

Logic analyzer and additional fault-injection hardware are optional later purchases, justified only if experiments demonstrate the need. Do not purchase RA6M5 as a second platform unless evidence requires it.

## Hardware qualification

No physical measurements are valid until the actual board is acquired and firmware is executed on it. Host simulation results must be explicitly labelled as simulation/host results.

## Research contribution discipline

Do not claim novelty for zero-heap allocation, MPU isolation, peripheral recovery, event queues/quarantine, context-aware recovery, recovery state machines, or formal invariants individually. The research contribution remains the specific integrated mechanism and measured technical trade-off.
