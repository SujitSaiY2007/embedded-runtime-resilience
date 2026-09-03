# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Status:** Development topic frozen; Phase 1E.1 active; Gate A complete; Gate B is next.  
**Project mode:** Solo software-dominant embedded-systems project  
**Primary ambition:** Research-grade implementation with publication potential and possible patent pathway if supported by evidence and professional assessment.

## Frozen development topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

### Short working title

**Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

This is the frozen development topic. The wording is intentionally specific: zero-heap is an architectural constraint, MPU support is a target platform capability rather than a universal MCU requirement, and event quarantine is the mechanism for preventing a fault-triggering event from poisoning otherwise valid queued work.

## Core research question

Can a compact, deterministic, software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Frozen architecture constraints

1. **Zero-heap:** recovery-manager/reference-firmware state uses statically allocated, bounded memory.
2. **Context/history:** policy uses only bounded, experimentally justified fault/event context and short recovery history.
3. **Bounded actions:** finite recovery-action set with explicit terminal escalation.
4. **Event quarantine:** isolate the smallest defensible fault-associated event/transaction scope rather than flushing unrelated valid work.
5. **MPU:** target an MPU-capable MCU where practical; MPU is a containment mechanism, not the invention itself.
6. **Event-driven firmware:** keep the reference architecture lightweight and avoid unnecessary heavyweight RTOS dependence.
7. **Formal reasoning:** establish selected queue/recovery invariants; do not claim full formal verification of the firmware.

## Six core invariants established at the start of Phase 1E.1

1. **Quarantine safety:** a quarantined event must not execute until an explicitly permitted transition releases/reclassifies it.
2. **Fault association:** recovery acts on the smallest defensible event/transaction scope supported by available context; ambiguity is not silently treated as precision.
3. **Service preservation:** a fault-associated event may be isolated without removing unrelated valid work when dependency, ordering, shared-state, and recovery-safety conditions permit it.
4. **Dependency safety:** an event that depends on an invalid or quarantined predecessor/shared state must not bypass that dependency merely because it is not itself fault-associated.
5. **Recovery termination:** every fault episode reaches success, degraded, or escalated terminal handling within a declared bounded transition budget.
6. **Bounded resource usage:** queue, quarantine storage, recovery state, and history remain within fixed statically allocated limits; no runtime heap growth is permitted.

These invariants form the current formal correctness boundary. They are properties to be specified, reasoned about, and later experimentally tested—not claims that the complete firmware is formally verified.

## Current phase

### Phase 1E.1 — Experimental Design / Formalization Foundation

**Status: active. Gate A is complete at the semantic-design level. Gate B is the next gate.**

## Completed Gate A — Exact Event Model and Dependency Semantics

Final artifact:

`research/phase1_gateA_event_model_final.md`

Important accepted semantics:

- `EventRef = {slot_id, generation}`;
- finite event types;
- explicit producer/service/consumer semantics;
- separate peripheral association and dependency semantics;
- finite criticality classes;
- `INDEPENDENT`, `ORDERED`, and `COUPLED/TRANSACTIONAL` dependencies;
- bounded explicit dependency representation;
- FIFO admission order separated from execution eligibility;
- explicit event lifecycle;
- evidence-bounded fault association;
- retained non-executable quarantine;
- bounded queue/quarantine assumptions;
- explicit full-queue behavior;
- preservation defined as correct verified execution.

Provisional host-model capacity parameters are `QMAX=16`, `XMAX=4`, and `DMAX=4`; Gate E must validate or revise them against the workload and report the chosen values explicitly.

The original `research/phase1_event_model.md` remains retained as historical design-baseline material. It is not deleted.

## Existing design baselines retained

The repository retains the Phase 1 design references for:

- MCU/board selection;
- event model;
- peripheral testbed/fault model;
- recovery-policy design.

The primary platform direction is **STM32U575ZI / NUCLEO-U575ZI-Q**, with I2C as the primary interface, SPI as a secondary interface, and UART/USART as the initial diagnostic/control path. Physical acquisition/validation remains a factual checkpoint rather than an assumption.

## Next gate — Gate B

### Fault Model + Fault Association

Gate B must freeze:

- exact fault taxonomy for the selected experimental peripheral(s);
- deterministic software fault-injection semantics;
- safely reproducible hardware/protocol fault classes;
- bounded fault-record representation;
- fault-to-event/transaction association rules;
- association-confidence handling;
- fault-episode boundaries and recurrence semantics;
- evidence needed to distinguish event fault, service fault, peripheral fault, and ambiguous fault;
- quarantine-scope implications of each association level.

No large-scale firmware implementation begins during Gate B.

A complete ready-to-paste next-chat prompt is stored in:

`NEXT_CHAT_PROMPT.md`

## Experimental direction

Compare, using the same workload and fault schedule:

1. fixed retry;
2. fixed retry + peripheral reset/reinitialization;
3. proposed zero-heap context-aware recovery + dependency-aware event quarantine.

Primary metrics include detection latency, service-restoration latency, recovery success, whole-system resets, unrelated-event preservation, quarantine violations, lost/duplicated events, queue occupancy, CPU overhead, RAM/Flash footprint, and energy where practical.

## What remains explicitly NOT claimed

- Zero-heap embedded firmware is not novel by itself.
- MPU isolation is not novel by itself.
- Peripheral recovery is not novel by itself.
- Event queues are not novel.
- Event quarantine is not automatically novel.
- Context-aware recovery is not automatically novel.
- Formal invariants are not automatically novel.
- Patentability is not established.
- No physical measurement is claimed until actual MCU execution provides the evidence.

The novelty hypothesis remains the **specific combined mechanism and measured technical trade-off**, not any individual ingredient.

## Implementation gate

No large-scale firmware implementation begins until Gates A–E are sufficiently specified:

- **Gate A:** Event model + dependency semantics — COMPLETE
- **Gate B:** Fault model + fault association — NEXT
- **Gate C:** Recovery policy + bounded state machine
- **Gate D:** Formal properties + proof/check strategy
- **Gate E:** Baselines + experimental protocol

After Gate E, implement the **smallest testable reference prototype**, not a general resilience framework.
