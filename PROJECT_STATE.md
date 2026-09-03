# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Status:** Development topic frozen; Phase 1E.1 complete through Gate E at the experimental-design/protocol level; Minimal Reference Implementation is next.  
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

**Status: Gate A, B, C, D, and E complete at their respective semantic/design/protocol levels.** Large-scale firmware implementation and physical validation remain deferred until the next implementation gate.

## Completed Gate A — Exact Event Model and Dependency Semantics

Final artifact: `research/phase1_gateA_event_model_final.md`

Gate A established the final semantic contract for event identity, event types, service ownership, peripheral association, criticality, explicit dependency classes, bounded dependency representation, admission/execution ordering, lifecycle, evidence-bounded fault association, quarantine, capacity, full-queue behavior, and preservation correctness.

Provisional host-model capacity parameters were `QMAX=16`, `XMAX=4`, and `DMAX=4`; Gate E has now frozen these as the reproducible protocol envelope, subject to empirical adequacy reporting and explicit amendment if capacity confounding is discovered.

## Completed Gate B — Fault Model + Fault Association

Final artifact: `research/phase1_gateB_fault_model_final.md`

Educational companion: `research/phase1_gateB_learning_summary.md`

Gate B freezes a small evidence-aware taxonomy centered on the primary I2C path, with a deliberately reduced secondary SPI taxonomy. It separates observed controller/service evidence from inference and unknown physical cause.

The governing evidence rule is:

`association precision <= evidence precision`

Key decisions include the five-class primary I2C taxonomy, four association levels (`EXACT_EVENT_TRANSACTION`, `SERVICE_ONLY`, `PERIPHERAL_ONLY`, `UNKNOWN_AMBIGUOUS`), episode-based recurrence/persistence, fixed-size fault context, and deterministic software injection as the primary repeatable stimulus. No physical measurement or hardware validation is claimed.

## Completed Gate C — Recovery Policy + Bounded State Machine

Final artifact: `research/phase1_gateC_recovery_policy_final.md`

Gate C is **ACCEPTED at the semantic/design level**. The frozen policy uses the minimum context of `fault_class`, `association_level`, bounded `attempt_count`, `criticality`, bounded `recovery_safety` preconditions, and `episode_state`. The logical actions are `RETRY`, `REINIT_OR_RESET`, `DEGRADE`, and `ESCALATE`, with at most two retries followed by one peripheral recovery action and one terminal action (`MAX_RECOVERY_ACTIONS=4`). Dependency-aware quarantine and conservative association are mandatory policy behavior.

## Completed Gate D — Formal Properties + Proof/Check Strategy

Final artifact: `research/phase1_gateD_formal_properties_final.md`

Gate D is **ACCEPTED at the semantic/design-model level**. It formalizes the six core invariants and supporting identity, release, dependency, transaction, termination, resource, and decision-table properties without claiming full formal verification of future firmware.

A host-side abstract audit enumerated **33,792** bounded policy contexts and found exactly one outcome for every encoded context. This is evidence about the modeled decision function, not proof of firmware or hardware behavior.

The finite-model qualifications, generation-wrap requirements, and possible multiple-episode bound were carried into Gate E.

## Completed Gate E — Baselines + Experimental Protocol

Final artifact: `research/phase1_gateE_experimental_protocol_final.md`

Gate E is **ACCEPTED at the experimental-design/protocol level**.

Frozen decisions include:

- five variants P0–P4;
- P0/P1 as principal baselines, P2/P3 as mechanism ablations, P4 as the integrated proposal;
- fourteen canonical workloads W01–W14 covering independent preservation, ordered/coupled dependencies, shared-peripheral non-causality, recovery paths, capacity boundaries, stale references, ambiguity, criticality, and mixed workloads;
- deterministic software fault injection as the primary repeatable stimulus;
- I2C as primary fault domain and SPI as secondary;
- `QMAX=16`, `XMAX=4`, `DMAX=4` as the reproducible protocol envelope;
- `EPMAX=1` for the normative reference prototype unless explicitly amended;
- bounded episode-state history rather than unbounded history;
- fixed run/event/episode/trace identifiers and structured logging;
- deterministic canonical schedules, with predeclared repetitions/seeds for later performance campaigns;
- fresh model state per host run and fixed reset/warm-up rules;
- predeclared invalid-run handling;
- correctness targets and latency/resource metrics;
- explicit separation of host, MCU, and physical evidence.

Gate E explicitly does **not** claim benchmark results, MCU measurements, energy measurements, physical fault validation, statistical significance, generalization, novelty, or patentability.

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
- Gate E freezes a protocol; it does not constitute experimental evidence.

The novelty hypothesis remains the **specific combined mechanism and measured technical trade-off**, not any individual ingredient.

## Implementation gate

The design/protocol foundation is now sufficiently specified to begin the **Minimal Reference Implementation — smallest testable reference prototype**. Implementation must remain deliberately small and must preserve Gates A–E as normative contracts.

The next implementation phase must first make the host/reference semantics executable and testable before attempting a full MCU application. It must concretely specify generation width/wrap behavior, fixed storage layout, scheduler rule, and any implementation-level details left intentionally open by the semantic gates, with explicit resource accounting.

## Continuity

`CURRENT_HANDOFF.md` contains the exact post-Gate-E continuation point. `NEXT_CHAT_PROMPT.md` contains the Minimal Reference Implementation startup prompt. `DECISION_LOG.md` records Gate E decisions and rejected alternatives. Historical documents remain preserved.
