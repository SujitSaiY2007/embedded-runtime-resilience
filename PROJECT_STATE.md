# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Status:** Development topic frozen; Phase 1E.1 active; Gates A, B, C, and D complete at the semantic/design-model level; Gate E is next.  
**Project mode:** Solo software-dominant embedded-systems project  
**Primary ambition:** Research-grade implementation with publication potential and possible patent pathway if supported by evidence and professional assessment.

The project has two broad phases: Phase 0 — research and topic selection; Phase 1 — the main engineering/research work covering system design, formalization, experimental protocol, implementation, physical validation, experiments, analysis, and final synthesis.

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
4. **Dependency safety:** an event that depends on an invalid or quarantined predecessor/shared state must not bypass that dependency merely because it is not fault-associated.
5. **Recovery termination:** every fault episode reaches success, degraded, or escalated terminal handling within a declared bounded transition budget.
6. **Bounded resource usage:** queue, quarantine storage, recovery state, and history remain within fixed statically allocated limits; no runtime heap growth is permitted.

## Current phase

### Phase 1E.1 — Experimental Design / Formalization Foundation

**Status: active. Gates A, B, C, and D are complete at the semantic/design-model level. Gate E is next.**

## Completed Gate A — Exact Event Model and Dependency Semantics

Final artifact: `research/phase1_gateA_event_model_final.md`

Gate A established the final semantic contract for event identity, event types, service ownership, peripheral association, criticality, explicit dependency classes, bounded dependency representation, admission/execution ordering, lifecycle, evidence-bounded fault association, quarantine, capacity, full-queue behavior, and preservation correctness.

Provisional host-model capacity parameters are `QMAX=16`, `XMAX=4`, and `DMAX=4`; Gate E must validate or revise them against the workload and report the chosen values explicitly.

## Completed Gate B — Fault Model + Fault Association

Final artifact: `research/phase1_gateB_fault_model_final.md`

Educational companion: `research/phase1_gateB_learning_summary.md`

Gate B freezes a small evidence-aware taxonomy centered on the primary I2C path, with a deliberately reduced secondary SPI taxonomy. It separates observed controller/service evidence from inference and unknown physical cause.

The governing evidence rule is:

`association precision <= evidence precision`

Key decisions include the five-class primary I2C taxonomy, four association levels (`EXACT_EVENT_TRANSACTION`, `SERVICE_ONLY`, `PERIPHERAL_ONLY`, `UNKNOWN_AMBIGUOUS`), episode-based recurrence/persistence, fixed-size fault context, and deterministic software injection as the primary repeatable stimulus. No physical measurement or hardware validation is claimed.

## Completed Gate C — Recovery Policy + Bounded State Machine

Final artifact: `research/phase1_gateC_recovery_policy_final.md`

Gate C is **ACCEPTED at the semantic/design level**. Large-scale implementation remains deferred.

The frozen policy uses the minimum context of `fault_class`, `association_level`, bounded `attempt_count`, `criticality`, bounded `recovery_safety` preconditions, and `episode_state`. The logical actions are `RETRY`, `REINIT_OR_RESET`, `DEGRADE`, and `ESCALATE`, with at most two retries followed by one peripheral recovery action and one terminal action (`MAX_RECOVERY_ACTIONS=4`). Dependency-aware quarantine and conservative association are mandatory policy behavior.

## Completed Gate D — Formal Properties + Proof/Check Strategy

Final artifact: `research/phase1_gateD_formal_properties_final.md`

Gate D is **ACCEPTED at the semantic/design-model level**. It formalizes the six core invariants and supporting identity, release, dependency, transaction, termination, resource, and decision-table properties without claiming full formal verification of future firmware.

A host-side abstract decision-table audit enumerated **33,792** bounded contexts and found exactly one outcome for every encoded context. This is evidence about the modeled decision function, not proof of firmware or hardware behavior.

The finite-model qualification, generation-wrap requirements, and possible explicit `EPMAX` bound for multiple simultaneous recovery episodes remain implementation concerns to resolve before implementation.

## Next gate — Gate E

### Baselines + Experimental Protocol

Gate E must freeze:

- baseline definitions and exact comparability;
- workload matrix and event/dependency scenarios;
- software fault schedule;
- final experimental capacities where required;
- metrics and correctness outcomes;
- logging schema and trace identifiers;
- repetitions/randomization or deterministic schedule policy;
- statistical/reproducibility treatment;
- acceptance criteria and reporting format.

Gate E must use Gates A–D as normative inputs and must not silently modify them. If a contradiction is discovered, it must be documented and explicitly amended.

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
- Gate B physical fault mechanisms remain unvalidated until hardware testing.
- Gate C does not establish performance or recovery-success results.
- Gate D does not establish firmware correctness beyond the defined model or prove arbitrary hardware behavior.

The novelty hypothesis remains the **specific combined mechanism and measured technical trade-off**, not any individual ingredient.

## Implementation gate

No large-scale firmware implementation begins until Gates A–E are sufficiently specified:

- **Gate A:** Event model + dependency semantics — COMPLETE
- **Gate B:** Fault model + fault association — COMPLETE
- **Gate C:** Recovery policy + bounded state machine — COMPLETE
- **Gate D:** Formal properties + proof/check strategy — COMPLETE
- **Gate E:** Baselines + experimental protocol — NEXT

After Gate E, implement the **smallest testable reference prototype**, not a general resilience framework.

## Continuity

`CURRENT_HANDOFF.md` contains the exact Gate E continuation point. `NEXT_CHAT_PROMPT.md` contains the Gate E startup prompt. `DECISION_LOG.md` records Gate D decisions and rejected alternatives. Historical documents remain preserved.
