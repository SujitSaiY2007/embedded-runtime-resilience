# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Status:** Development topic frozen; Phase 1E.1 active; Gates A and B complete; Gate C is next.  
**Project mode:** Solo software-dominant embedded-systems project  
**Primary ambition:** Research-grade implementation with publication potential and possible patent pathway if supported by evidence and professional assessment.

## Frozen development topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

### Short working title

**Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

## Core research question

Can a compact, deterministic, software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Six core invariants

1. **Quarantine safety:** a quarantined event must not execute until an explicitly permitted transition releases/reclassifies it.
2. **Fault association:** recovery acts on the smallest defensible event/transaction scope supported by available context; ambiguity is not silently treated as precision.
3. **Service preservation:** a fault-associated event may be isolated without removing unrelated valid work when dependency, ordering, shared-state, and recovery-safety conditions permit it.
4. **Dependency safety:** an event that depends on an invalid or quarantined predecessor/shared state must not bypass that dependency merely because it is not itself fault-associated.
5. **Recovery termination:** every fault episode reaches success, degraded, or escalated terminal handling within a declared bounded transition budget.
6. **Bounded resource usage:** queue, quarantine storage, recovery state, and history remain within fixed statically allocated limits; no runtime heap growth is permitted.

## Current phase

### Phase 1E.1 — Experimental Design / Formalization Foundation

**Status: active. Gates A and B are complete at the semantic/design level. Gate C is next.**

## Completed Gate A — Exact Event Model and Dependency Semantics

Final artifact: `research/phase1_gateA_event_model_final.md`

The original `research/phase1_event_model.md` remains retained as historical design-baseline material and is not deleted.

Gate A established the final semantic contract for event identity, event types, service ownership, peripheral association, criticality, explicit dependency classes, bounded dependency representation, admission/execution ordering, lifecycle, evidence-bounded fault association, quarantine, capacity, full-queue behavior, and preservation correctness.

Provisional host-model capacity parameters are `QMAX=16`, `XMAX=4`, and `DMAX=4`; Gate E must validate or revise them against the workload and report the chosen values explicitly.

## Completed Gate B — Fault Model + Fault Association

Final artifact: `research/phase1_gateB_fault_model_final.md`

Educational companion: `research/phase1_gateB_learning_summary.md`

Gate B freezes a small evidence-aware taxonomy centered on the primary I2C path, with a deliberately reduced secondary SPI taxonomy. It separates observed controller/service evidence from inference and unknown physical cause.

### Gate B in simple terms

Gate A defines how work and dependencies behave. Gate B defines how the system describes a failure before recovery decisions are made.

`EVENT MODEL -> FAULT UNDERSTANDING -> RECOVERY POLICY`

Gate B turns “something went wrong” into a bounded fault context describing what was observed, where it can defensibly be associated, how certain that association is, whether the observation belongs to an ongoing episode, and what scope may need to be isolated or blocked.

The governing evidence rule is:

`association precision <= evidence precision`

An observed NACK, timeout, or bus/protocol error is not automatically treated as proof of a particular physical root cause. Same-peripheral membership does not by itself establish event-level causality. Fault association scope and dependency-blocking scope remain separate.

### Key Gate B decisions

- I2C NACK/non-acknowledge, transfer timeout/no-progress, bus/protocol error, and arbitration loss are observable fault classes where the relevant controller/driver evidence exists.
- Persistent no-progress is a history-derived condition, not proof of an internal peripheral state-machine lockup.
- Recurrence and persistence are history/episode attributes, not independent instantaneous fault classes.
- Service/driver-level failures without sufficient peripheral evidence are kept distinct from peripheral faults.
- `EXACT_EVENT_TRANSACTION`, `SERVICE_ONLY`, `PERIPHERAL_ONLY`, and `UNKNOWN_AMBIGUOUS` are operational association levels.
- Peripheral equality alone never justifies event-level fault attribution.
- Quarantine scope may be selective or broader only when dependency/shared-state safety justifies it; association scope and dependency-blocking scope are distinct.
- Software injection is the primary deterministic testing mechanism; software faults are not represented as equivalent to physical hardware faults.
- Physical/protocol injection methods remain candidates until actual hardware, fixture safety, and repeatability testing are demonstrated.
- The semantic fault record is fixed-size/static and retains only information needed for later policy decisions and metrics.
- A fault episode continues across qualifying repeated observations until verified success, degraded terminal handling, or escalation; a post-terminal fault starts a new episode.

Gate B is accepted at the semantic/design level. No physical measurement or hardware validation is claimed.

## Existing design baselines retained

The repository retains the Phase 1 design references for MCU/board selection, event model, peripheral testbed/fault model, and recovery-policy design.

The primary platform direction is **STM32U575ZI / NUCLEO-U575ZI-Q**, with I2C as the primary interface, SPI as a secondary interface, and UART/USART as the initial diagnostic/control path. Physical acquisition/validation remains a factual checkpoint rather than an assumption.

## Next gate — Gate C

### Recovery Policy + Bounded State Machine

Gate C must derive and freeze:

- minimum fault-context variables that materially change recovery decisions;
- minimum useful bounded recovery history;
- finite recovery action set and technically distinct action semantics;
- deterministic decision table/policy;
- association-confidence-dependent recovery behavior;
- exact retry/reinitialization/degradation/escalation rules;
- bounded recovery transition budget;
- interaction between recovery and event scheduling/quarantine;
- degraded-mode semantics for the reference services.

No large-scale firmware implementation begins during Gate C.

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
- Gate B's candidate physical fault mechanisms are not yet hardware-validated.

The novelty hypothesis remains the **specific combined mechanism and measured technical trade-off**, not any individual ingredient.

## Implementation gate

No large-scale firmware implementation begins until Gates A–E are sufficiently specified:

- **Gate A:** Event model + dependency semantics — COMPLETE
- **Gate B:** Fault model + fault association — COMPLETE
- **Gate C:** Recovery policy + bounded state machine — NEXT
- **Gate D:** Formal properties + proof/check strategy
- **Gate E:** Baselines + experimental protocol

After Gate E, implement the **smallest testable reference prototype**, not a general resilience framework.

## Continuity

`CURRENT_HANDOFF.md` contains the current handoff and stopping boundary. `NEXT_CHAT_PROMPT.md` contains the Gate C startup prompt and remains the durable startup instruction. The Gate B educational companion is retained separately so future chats can understand the concepts without replacing the normative Gate B artifact. `CHAT_CONTINUITY_PROTOCOL.md` records the educational companion as optional conceptual continuity material. At each gate boundary, update the relevant final artifact plus `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, and `DECISION_LOG.md`, preserve historical material, and synchronize the active branch with `main` before starting a new chat.
