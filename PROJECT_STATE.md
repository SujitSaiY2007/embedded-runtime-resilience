# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`
**Status:** Development topic frozen; design now proceeds under explicit zero-heap and event-quarantine constraints.
**Project mode:** Solo software-dominant embedded-systems project
**Primary ambition:** Research-grade implementation with publication potential and possible patent pathway if supported by evidence and professional assessment.

## Frozen development topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

### Short working title

**Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

This is the frozen development topic. The wording is intentionally specific: zero-heap is an architectural constraint, MPU support is a target platform capability rather than a universal MCU requirement, and event quarantine is the mechanism for preventing a fault-triggering event from poisoning otherwise valid queued work.

## Core research question

Can a compact, deterministic, software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Integration decision on proposed additions

### 1. Zero-heap recovery manager — ACCEPTED, but narrowed

The project will be **strictly zero-heap**: the recovery manager itself and the reference firmware must not rely on runtime dynamic allocation. State, recovery records, queues, and policy tables will use statically allocated memory.

The motivation is technically sound: deterministic memory use and avoidance of fragmentation are established embedded concerns. Zero-heap is therefore **not claimed as novel by itself**. The contribution lies in the recovery-policy architecture operating under this constraint.

### 2. MPU integration — ACCEPTED as a platform constraint/containment mechanism, NOT as the invention by itself

The prototype will target an MCU architecture with a usable MPU where practical. MPU regions may be used to isolate protected firmware state/recovery-manager memory and/or distinguish protected service components.

However, the MPU itself is not novel and is not required to detect a peripheral communication fault. The topic must not claim that "using an MPU for recovery" is novel. The research question is how MPU-supported containment can be combined with a small zero-heap recovery policy.

If an available development environment makes MPU experimentation impractical, the core policy remains valid; MPU-specific containment becomes a secondary experimental configuration rather than a reason to abandon the project.

### 3. Asynchronous queue poisoning prevention — ACCEPTED after terminology refinement

The project will use the term **event quarantine** or **fault-associated event quarantine**, not "queue poisoning prevention" as the formal contribution name.

When a peripheral fault is associated with a particular event/transaction, the recovery mechanism should quarantine or invalidate only the implicated event/transaction context while preserving independent valid events already present in the queue, subject to dependency constraints.

This directly strengthens the core research objective because it gives us a measurable service-preservation mechanism rather than merely another recovery action.

The queue policy must define:

- event identity;
- dependency/ordering relation;
- fault association;
- quarantine state;
- preservation rule for unaffected events;
- reinsertion/retry rule;
- bounded memory behavior.

### 4. Formal mathematical proofs — DEFERRED/REFINED

A full formal proof of the entire firmware is out of scope. Instead, the project will aim to provide **formal properties and proofs for the queue/recovery policy**, where tractable.

Candidate properties include:

- unaffected valid events are not removed by a single-event fault;
- a quarantined event cannot be executed again until explicitly released/reclassified;
- queue capacity remains bounded;
- recovery transitions terminate within a bounded number of policy steps;
- event ordering is preserved for independent events where required.

These can be expressed using invariants and transition-system reasoning and then experimentally tested. A formal proof is a research-strengthening component, not a prerequisite for claiming that the overall system is mathematically proven correct.

## What remains explicitly NOT claimed

- Zero-heap embedded firmware is not novel by itself.
- MPU isolation is not novel by itself.
- Peripheral recovery is not novel by itself.
- Event queues are not novel.
- Event quarantine is not automatically novel.
- Context-aware recovery is not automatically novel.
- Formal invariants are not automatically novel.
- Patentability is not established.
- The exact combined mechanism has not been professionally cleared for patentability.

The novelty hypothesis is the **specific combination and implementation discipline**: a compact deterministic zero-heap recovery policy for MCU event-driven firmware that uses local fault context/history and explicit event quarantine to minimize collateral service disruption, optionally strengthened by MPU-supported isolation.

## Hardware reality and scope

The current project is **not a laptop/PC-only implementation if it is to remain a genuine MCU firmware project**. A laptop/PC is sufficient for development, simulation, automated fault-model testing, analysis, and some emulation, but real MCU MPU behavior, peripheral-driver behavior, interrupt timing, and hardware fault modes require an actual development board/MCU for the strongest experimental claims.

No physical MCU board is currently assumed to be available. Therefore hardware acquisition/selection is now a development prerequisite, not an already-completed resource.

If hardware is temporarily unavailable, software architecture and host-side simulation can proceed, but those results must be labeled simulation results rather than physical embedded measurements.

## Experimental direction

Compare:

1. fixed retry;
2. fixed retry + peripheral reset/reinitialization;
3. proposed zero-heap context-aware recovery + event quarantine.

Primary metrics:

- detection latency;
- service-restoration latency;
- recovery success rate;
- whole-system reset count;
- unrelated-event preservation rate;
- fault-associated event quarantine correctness;
- lost/duplicated events;
- queue occupancy;
- CPU overhead;
- RAM/Flash footprint;
- recovery-state count;
- energy impact where practical.

## Current phase

**Phase 1 — Preparation / System Design**

Completed:

- [x] Research-space decomposition
- [x] Candidate shortlist
- [x] Deep prior-art attack
- [x] Development topic selection
- [x] Integration decision on zero-heap constraint
- [x] Integration decision on event quarantine
- [x] Scope decision on MPU usage

Next:

- [ ] Select MCU/development board with MPU support
- [ ] Define exact peripheral testbed
- [ ] Define fault model and injection method
- [ ] Define event model and dependency semantics
- [ ] Define recovery-policy state machine
- [ ] Define queue invariants
- [ ] Define formal properties/proof strategy
- [ ] Define baseline implementations
- [ ] Build minimal architecture before feature expansion
