# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Status:** Development topic frozen; Phase 1E.1 active; Gates A, B, C, and D complete at the semantic/design-model level; Gate E is next.  
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
4. **Dependency safety:** an event that depends on an invalid or quarantined predecessor/shared state must not bypass that dependency merely because it is not fault-associated.
5. **Recovery termination:** every fault episode reaches success, degraded, or escalated terminal handling within a declared bounded transition budget.
6. **Bounded resource usage:** queue, quarantine storage, recovery state, and history remain within fixed statically allocated limits; no runtime heap growth is permitted.

## Current phase

### Phase 1E.1 — Experimental Design / Formalization Foundation

**Status: active. Gates A, B, C, and D are complete at the semantic/design-model level. Gate E is next.**

## Completed Gate A — Exact Event Model and Dependency Semantics

Final artifact: `research/phase1_gateA_event_model_final.md`

The original `research/phase1_event_model.md` remains retained as historical design-baseline material and is not deleted.

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

### Gate C result in simple terms

Gate A defined **what work exists and what depends on what**.  
Gate B defined **what failed, what can be proved, and what work can be defensibly associated with it**.  
Gate C now defines **what the recovery mechanism is allowed to do, in what order, for how long, and when it must stop**.

### Frozen Gate C policy

The minimum normative policy context is:

- `fault_class`;
- `association_level`;
- bounded `attempt_count`;
- `criticality`;
- bounded `recovery_safety` precondition results;
- `episode_state`.

`fault_recurrence` is not stored as an independent policy variable; it is represented through bounded episode progression. `last_action` and `last_outcome` are not independent policy inputs because the explicit state machine already represents them. `pending_independent_work` is scheduler state, not policy state. Dependency status is evaluated through Gate A predicates and action preconditions rather than duplicated as a policy graph.

The logical action set is:

1. `RETRY`
2. `REINIT_OR_RESET`
3. `DEGRADE`
4. `ESCALATE`

The U575 policy treats reinitialization and peripheral reset as one logical recovery action because their policy role is the same, while retaining the implementation-level distinction for later controlled experiments. They must not be assumed to have identical effects.

### Frozen recovery ladder

At most two retry actions are permitted per episode, followed by one `REINIT_OR_RESET` opportunity and then one terminal `DEGRADE` or `ESCALATE` action when recovery has not succeeded.

`T1 = RETRY #1`  
`T2 = RETRY #2`  
`T3 = REINIT_OR_RESET`  
`T4 = terminal DEGRADE or ESCALATE`

Thus:

`MAX_RECOVERY_ACTIONS = 4`

The bound counts recovery-action invocations, not internal lifecycle transitions such as `RETRY_PENDING -> VERIFYING`. Verification is part of the action attempt. Unrelated scheduler dispatches are not recovery attempts.

### Association-aware behavior

- `EXACT_EVENT_TRANSACTION`: quarantine the specific event/transaction when safe.
- `SERVICE_ONLY`: do not invent an event target; contain/recover at service scope when justified.
- `PERIPHERAL_ONLY`: do not invent an event target; recover the peripheral and block dependent work until verified.
- `UNKNOWN_AMBIGUOUS`: use only conservative containment justified by evidence/safety; if safe local containment cannot be established, escalate.

Fault-association scope remains distinct from dependency-blocking scope.

### Scheduling/quarantine result

Independent work is not blocked merely because another event is quarantined. Ordered/coupled work remains blocked whenever Gate A semantics require it. During peripheral recovery, events depending on invalid peripheral/shared state remain blocked until verification. Release of a quarantined event is only a return to Gate A eligibility evaluation after successful verification; it is not unconditional execution.

### Coupled transactions

A coupled transaction is never retried member-by-member unless its transaction contract explicitly establishes retry safety. Otherwise the policy skips retry and selects peripheral recovery, degradation, or escalation as permitted.

### Degraded mode

The policy uses a common bounded `ACTIVE -> DEGRADED -> TERMINAL` abstraction with service-specific safe behavior. A noncritical sensor may stop new transactions and expose last-known-valid data as stale/degraded; a critical service without a safe degraded contract must escalate. These are design semantics, not measured outcomes.

### Policy output

The fixed-size conceptual output is:

`PolicyDecision { action, target_scope, quarantine_required, retry_permitted, attempt_index, terminal, release_permitted, reason_code }`

Exact byte packing remains an implementation/Gate E concern.

### Ablation

Gate C freezes four conceptual comparisons:

- P0 fixed retry baseline;
- P1 fixed retry + peripheral recovery;
- P2 context-only policy;
- P3 context + episode-history policy;
- P4 integrated policy with dependency-aware event quarantine.

The design is explicitly falsifiable: additional context/history is not assumed to be beneficial merely because it is more sophisticated.

## Completed Gate D — Formal Properties + Proof/Check Strategy

Final artifact: `research/phase1_gateD_formal_properties_final.md`

Gate D is **ACCEPTED at the semantic/design-model level**. It formalizes the six core invariants and the supporting identity, release, dependency, transaction, termination, resource, and decision-table properties without claiming full formal verification of future firmware.

### Gate D result

Gate D establishes explicit predicates and checking obligations for:

- quarantine safety;
- fault-association conservatism;
- service preservation versus correct blocking;
- dependency safety;
- recovery termination;
- bounded resource use;
- `EventRef = {slot_id, generation}` validity and stale-reference rejection;
- release safety and Gate A eligibility re-entry;
- coupled-transaction containment;
- deterministic decision-table totality and consistency.

The four-action ladder has a direct finite-rank termination argument. A host-side abstract decision-table audit enumerated **33,792** bounded contexts and found exactly one outcome for every encoded context. This is evidence about the modeled decision function, not proof of firmware or hardware behavior.

### Gate D finite-model qualification

The initial bounded envelope remains `QMAX=16`, `XMAX=4`, `DMAX=4`. Gate D uses a layered host-model strategy rather than attempting to enumerate the entire concrete MCU state at once.

For `EventRef`, the checker must model generation changes and stale references explicitly; generation wrap is safe only when no outstanding reference can still identify the older generation. The concrete generation width and wrap policy remain implementation concerns.

A single active recovery episode is used as a proof decomposition for the policy-state model. If implementation permits multiple simultaneous service/peripheral recovery episodes not represented by retained event slots, an explicit finite `EPMAX` must be declared and resource-accounted before implementation.

### Properties that are model-level vs experimental

Model-level properties include quarantine safety, association conservatism, dependency safety, coupled containment, decision determinism/totality, and the four-action termination bound, subject to implementation conformance.

Experimental properties include CPU/RAM/Flash overhead, recovery latency, recovery success rate, physical fault validity, MPU behavior, and energy impact. No physical result is claimed at Gate D.

## Existing design baselines retained

The repository retains the Phase 1 design references for MCU/board selection, event model, peripheral testbed/fault model, and the earlier recovery-policy proposal. The earlier recovery proposal remains historical and is not silently rewritten.

The primary platform direction is **STM32U575ZI / NUCLEO-U575ZI-Q**, with I2C as the primary interface, SPI as a secondary interface, and UART/USART as the initial diagnostic/control path. Physical acquisition/validation remains a factual checkpoint rather than an assumption.

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
