# Current Handoff

## Session status

Phase 0 topic validation and Phase 1 system-design preparation are complete. The development topic is frozen. The project is in **Phase 1E.1 — Experimental Design / Formalization Foundation**.

**Gate A — Exact Event Model and Dependency Semantics is COMPLETE and checkpointed.**  
**Gate B — Fault Model + Fault Association is COMPLETE and checkpointed.**  
**Gate C — Recovery Policy + Bounded State Machine is COMPLETE and checkpointed.**  
**Gate D — Formal Properties + Proof/Check Strategy is COMPLETE and checkpointed at the semantic/design-model level.**

The next chat must begin **Gate E — Baselines + Experimental Protocol**.

## Frozen development topic

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

**Short working title:** Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine

## Core research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Core invariants

1. **Quarantine safety** — a quarantined event cannot execute until an explicitly permitted transition.
2. **Fault association** — recovery uses the smallest defensible event/transaction scope; ambiguity is not silently converted into precision.
3. **Service preservation** — unrelated valid work remains eligible only when dependency, ordering, shared-state, and recovery-safety conditions permit it.
4. **Dependency safety** — dependent events cannot bypass an invalid/quarantined predecessor or shared state merely because they are not themselves fault-associated.
5. **Recovery termination** — each fault episode reaches success, degraded, or escalated terminal handling within a declared bounded transition budget.
6. **Bounded resource usage** — queue, quarantine storage, history, and recovery state remain within fixed limits with no runtime heap growth.

## Gate A checkpoint

Final artifact: `research/phase1_gateA_event_model_final.md`

Frozen semantics include `EventRef = {slot_id, generation}`, separate transaction identity, explicit `INDEPENDENT`/`ORDERED`/`COUPLED/TRANSACTIONAL` dependencies, FIFO admission versus eligibility-driven execution, retained non-executable quarantine, preservation as verified execution, and provisional `QMAX=16`, `XMAX=4`, `DMAX=4` pending Gate E validation.

The original `research/phase1_event_model.md` remains retained as historical baseline material.

## Gate B checkpoint

Final artifact: `research/phase1_gateB_fault_model_final.md`  
Educational companion: `research/phase1_gateB_learning_summary.md`

Gate B froze the evidence-aware primary I2C taxonomy, reduced secondary SPI taxonomy, four association levels, episode-based recurrence/persistence, fixed-size fault context, and deterministic software injection as the primary repeatable stimulus.

Critical rule:

`association precision <= evidence precision`

Software fault injection is not physical hardware validation. No physical measurements are claimed.

## Gate C checkpoint

Final artifact: `research/phase1_gateC_recovery_policy_final.md`

Gate C is accepted at the semantic/design level.

### Minimum policy context

- `fault_class`
- `association_level`
- bounded `attempt_count`
- `criticality`
- bounded `recovery_safety` preconditions
- `episode_state`

`fault_recurrence` is derived from episode progression rather than retained as a separate policy variable. `last_action` and `last_outcome` are represented by the explicit state machine rather than duplicated fields. `pending_independent_work` remains scheduler state. Dependency status is evaluated through Gate A predicates/preconditions rather than duplicated as policy state.

### Action set

- `RETRY`
- `REINIT_OR_RESET`
- `DEGRADE`
- `ESCALATE`

Reinitialization and peripheral reset are one logical policy action but may be distinct implementation methods on U575; do not assume identical or different experimental outcomes without evidence.

### Exact recovery budget

At most two retry actions, then one `REINIT_OR_RESET`, then one terminal `DEGRADE` or `ESCALATE` if recovery has not succeeded:

`T1=RETRY #1 -> T2=RETRY #2 -> T3=REINIT_OR_RESET -> T4=terminal`

`MAX_RECOVERY_ACTIONS=4`.

An attempt is one recovery-action invocation plus its verification; scheduler work and repeated fault observations alone are not recovery attempts.

### Association behavior

- `EXACT_EVENT_TRANSACTION`: specific event/transaction can be quarantined when safe.
- `SERVICE_ONLY`: service-level containment only; do not invent event attribution.
- `PERIPHERAL_ONLY`: peripheral recovery/blocking of dependent work; no invented event attribution.
- `UNKNOWN_AMBIGUOUS`: conservative containment only; if safe local containment cannot be established, escalate.

### Scheduling and dependency

Independent events may execute while another event is quarantined if Gate A eligibility permits. Ordered and coupled work remains blocked where required. During peripheral recovery, events depending on invalid peripheral/shared state remain blocked until verification. Release returns the event to Gate A eligibility evaluation; it is not unconditional execution.

Coupled transactions cannot be retried member-by-member unless their contract explicitly makes that safe.

### Release criteria

Release requires successful action completion, relevant peripheral/service verification, event/transaction verification where applicable, satisfied Gate A dependencies/order, valid shared state, no active recovery prohibition, and a still-valid `EventRef`.

### Degraded mode

Common bounded abstraction: `ACTIVE -> DEGRADED -> TERMINAL`, with service-specific safe degraded behavior. A critical service without a safe degraded contract escalates.

### Policy output

Conceptual fixed-size record:

`PolicyDecision { action, target_scope, quarantine_required, retry_permitted, attempt_index, terminal, release_permitted, reason_code }`

### Ablation

P0 fixed retry; P1 fixed retry + peripheral recovery; P2 context-only; P3 context + episode history; P4 integrated policy + dependency-aware quarantine.

The mechanism remains falsifiable.

## Gate D checkpoint

Final artifact: `research/phase1_gateD_formal_properties_final.md`

Gate D is **ACCEPTED at the semantic/design-model level**.

### Formalized properties

Gate D defines predicates/check obligations for:

1. quarantine safety;
2. fault-association conservatism;
3. service preservation versus correct blocking;
4. dependency safety;
5. recovery termination under the four-action bound;
6. bounded resource usage;
7. `EventRef` generation validity and stale-reference rejection;
8. release safety and Gate A eligibility re-entry;
9. coupled-transaction containment;
10. deterministic decision-table totality and consistency.

### Gate D model-level check

A host-side abstract audit enumerated **33,792** policy contexts formed from 11 bounded fault classes, 4 association levels, 3 criticality classes, 4 active attempt-count values, 8 recovery-safety masks, and success/prohibition/containment status bits. Every encoded context produced exactly one deterministic outcome. This establishes totality/determinism for the modeled policy abstraction only; it is not firmware or hardware validation.

### Gate D qualifications

- `QMAX=16`, `XMAX=4`, `DMAX=4` remain provisional until Gate E workload validation.
- Generation width/wrap behavior must be concretely specified before implementation; stale references must fail closed.
- A single active recovery episode is used as a host-model proof decomposition. If implementation permits multiple simultaneous service/peripheral episodes outside retained event slots, a fixed `EPMAX` must be declared and resource-accounted before implementation.
- Host-state checking is evidence about the modeled semantics, not proof of arbitrary MCU/hardware behavior.

## Primary platform direction

**STM32U575ZI / NUCLEO-U575ZI-Q**

I2C is primary, SPI secondary, UART/USART diagnostic/control. Hardware acquisition is not assumed and no physical validation has been claimed.

## Next exact task — Gate E

### Baselines + Experimental Protocol

Use Gates A–D as normative contracts. Do not redesign them without identifying a genuine contradiction.

Gate E must freeze:

1. baseline definitions and exact comparability;
2. workload matrix and event/dependency scenarios;
3. deterministic software fault schedule and any later physical-fault mapping;
4. final queue/quarantine/dependency/recovery capacities where required;
5. metrics and correctness outcomes;
6. logging schema and trace/event identifiers;
7. repetitions, randomization, or deterministic schedule policy;
8. statistical and reproducibility treatment;
9. acceptance criteria and reporting format;
10. what is measured on host versus what must wait for MCU hardware.

Do not begin large-scale firmware implementation during Gate E.

## Subsequent gates

- **Implementation:** smallest reference prototype only after A–E are sufficiently specified.
- **Physical validation:** after board/testbed acquisition and safe fault-injection setup.
- **Baseline experiments:** matched baseline measurements with raw artifacts preserved.
- **Proposed-policy experiments:** proposed mechanism measurements and correctness observations.
- **Analysis:** statistical/technical analysis, limitations, and interpretation.
- **Final synthesis:** report/paper/patent assessment and final repository organization.

## Research honesty

Do not fabricate hardware availability, physical measurements, benchmarks, energy measurements, fault-injection success, novelty, or patentability.

Host simulation is not physical MCU validation. Software fault injection is not proof of a physical fault mechanism.

## Chat boundary

**Stop after Gate E is fully reasoned, documented, accepted/rejected, checkpointed, and synchronized. Do not continue into implementation.**

The next chat begins:

**Gate E — Baselines + Experimental Protocol**

The repository must be sufficient for the next chat to continue without relying on this conversation.
