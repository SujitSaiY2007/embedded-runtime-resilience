# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Status:** Development topic frozen; Phase 1E.1 active; Gates A, B, and C complete at the semantic/design level; Gate D is next.  
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

**Status: active. Gates A, B, and C are complete at the semantic/design level. Gate D is next.**

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

## Existing design baselines retained

The repository retains the Phase 1 design references for MCU/board selection, event model, peripheral testbed/fault model, and the earlier recovery-policy proposal. The earlier recovery proposal remains historical and is not silently rewritten.

The primary platform direction is **STM32U575ZI / NUCLEO-U575ZI-Q**, with I2C as the primary interface, SPI as a secondary interface, and UART/USART as the initial diagnostic/control path. Physical acquisition/validation remains a factual checkpoint rather than an assumption.

## Next gate — Gate D

### Formal Properties + Proof/Check Strategy

Gate D must formalize and practically check the properties implied by Gates A–C, especially:

- quarantine safety;
- fault-association conservatism;
- service preservation/correct blocking;
- dependency safety;
- recovery termination under the four-action bound;
- bounded resource usage;
- valid `EventRef` generation handling;
- safe release criteria;
- coupled-transaction containment;
- completeness of the deterministic decision table.

Gate D should identify which properties can be checked by exhaustive host-state exploration, assertions, model checking, invariant reasoning, or deterministic trace tests. It must not claim full formal verification of the firmware.

## Experimental direction

Compare, using matched workload and fault schedules:

1. fixed retry;
2. fixed retry + peripheral reset/reinitialization;
3. proposed zero-heap context-aware recovery + dependency-aware event quarantine.

Primary metrics include detection latency, service-restoration latency, recovery success, whole-system resets, unrelated-event preservation, quarantine violations, lost/duplicated events, queue occupancy, CPU overhead, RAM/Flash footprint, and energy where practical.

Gate E will freeze the workload matrix, capacities, repetitions, logging, and statistical/reproducibility protocol.

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

The novelty hypothesis remains the **specific combined mechanism and measured technical trade-off**, not any individual ingredient.

## Implementation gate

No large-scale firmware implementation begins until Gates A–E are sufficiently specified:

- **Gate A:** Event model + dependency semantics — COMPLETE
- **Gate B:** Fault model + fault association — COMPLETE
- **Gate C:** Recovery policy + bounded state machine — COMPLETE
- **Gate D:** Formal properties + proof/check strategy — NEXT
- **Gate E:** Baselines + experimental protocol

After Gate E, implement the **smallest testable reference prototype**, not a general resilience framework.

## Continuity

`CURRENT_HANDOFF.md` contains the exact Gate D continuation point. `NEXT_CHAT_PROMPT.md` contains the Gate D startup prompt. `DECISION_LOG.md` records Gate C decisions and rejected alternatives. Historical documents remain preserved.
