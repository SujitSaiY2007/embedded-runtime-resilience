# Next Chat Prompt — Gate D

Copy/paste the following prompt into the next ChatGPT 5 chat.

---

You are continuing my embedded-systems research project from the canonical GitHub repository:

`SujitSaiY2007/embedded-runtime-resilience`

## 1. IMPORTANT: CONTINUATION, NOT RESTART

This is a continuation of an existing research project. Do not restart topic ideation, prior-art exploration, MCU selection, Phase 1 preparation, Gate A, Gate B, or Gate C.

GitHub is the durable source of truth. Reconstruct the project from the repository before doing substantive work.

## 2. MANDATORY STARTUP READING

Read these files from `main` in this order:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `CHAT_CONTINUITY_PROTOCOL.md`
6. `research/phase1_gateA_event_model_final.md`
7. `research/phase1_gateB_fault_model_final.md`
8. `research/phase1_gateB_learning_summary.md`
9. `research/phase1_gateC_recovery_policy_final.md`
10. `research/phase1_event_model.md`
11. `research/phase1_mcu_board_selection.md`
12. `research/phase1_peripheral_testbed_fault_model.md`
13. `research/phase1_recovery_policy_design.md`

Then provide a concise continuity check covering:

- frozen research topic;
- frozen research question;
- Gate A result;
- Gate B result;
- Gate C result;
- why Gate C matters;
- exact Gate D task;
- explicit non-goals.

Do not begin implementation.

## 3. FROZEN PROJECT

### Topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

### Research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

### Platform direction

**STM32U575ZI / NUCLEO-U575ZI-Q**

I2C is primary, SPI secondary, UART/USART diagnostic/control. Hardware acquisition is not assumed.

## 4. COMPLETED GATE A

`research/phase1_gateA_event_model_final.md`

Frozen semantics:

- `EventRef = {slot_id, generation}`;
- separate bounded transaction identity;
- explicit `INDEPENDENT`, `ORDERED`, `COUPLED/TRANSACTIONAL` dependencies;
- dependencies are not inferred from peripheral equality;
- FIFO is admission order, not universal execution order;
- eligibility controls execution;
- quarantine is retained non-executable state;
- preservation means correct verified execution;
- provisional `QMAX=16`, `XMAX=4`, `DMAX=4` pending Gate E validation.

## 5. COMPLETED GATE B

`research/phase1_gateB_fault_model_final.md`

Frozen primary I2C observations:

- NACK/non-acknowledge;
- transfer timeout/no-progress;
- bus/protocol error;
- arbitration/bus-ownership error;
- persistent no-progress/suspected peripheral-state failure.

Association levels:

- `EXACT_EVENT_TRANSACTION`
- `SERVICE_ONLY`
- `PERIPHERAL_ONLY`
- `UNKNOWN_AMBIGUOUS`

Core rule:

`association precision <= evidence precision`

Recurrence/persistence are episode/history attributes. Software injection is deterministic test stimulus, not physical validation. No physical measurements are claimed.

## 6. COMPLETED GATE C

`research/phase1_gateC_recovery_policy_final.md`

Gate C is accepted at the semantic/design level.

### Minimum policy context

- `fault_class`
- `association_level`
- bounded `attempt_count`
- `criticality`
- bounded `recovery_safety` precondition results
- `episode_state`

Not independent policy inputs:

- recurrence is represented by episode progression;
- `last_action` and `last_outcome` are represented by the explicit state machine;
- `pending_independent_work` is scheduler state;
- dependency status is evaluated through Gate A predicates/preconditions.

### Logical action set

- `RETRY`
- `REINIT_OR_RESET`
- `DEGRADE`
- `ESCALATE`

Reinitialization and peripheral reset are one logical policy action but may be distinct implementation methods; do not assume identical or different experimental outcomes without evidence.

### Exact recovery budget

`T1=RETRY #1`  
`T2=RETRY #2`  
`T3=REINIT_OR_RESET`  
`T4=terminal DEGRADE or ESCALATE`

`MAX_RECOVERY_ACTIONS=4`.

An attempt is one recovery-action invocation plus its verification. Scheduler work and repeated fault observations alone are not recovery attempts.

### Association behavior

- exact association: specific event/transaction may be quarantined when safe;
- service-only: service-level containment, no invented event attribution;
- peripheral-only: peripheral recovery/blocking of dependent work, no invented event attribution;
- ambiguous: conservative containment only; escalate if safe local containment cannot be established.

### Scheduling

Independent work may execute if Gate A eligibility permits. Ordered/coupled work remains blocked when required. Recovery cannot bypass shared-state validity. Release requires successful verification and re-entry through Gate A eligibility.

### Coupled transactions

No member-by-member retry unless the transaction contract explicitly establishes retry safety.

### Degraded mode

Common bounded abstraction: `ACTIVE -> DEGRADED -> TERMINAL`, with service-specific safety semantics.

### Output

Conceptual fixed-size record:

`PolicyDecision { action, target_scope, quarantine_required, retry_permitted, attempt_index, terminal, release_permitted, reason_code }`

### Ablation

P0 fixed retry; P1 fixed retry + peripheral recovery; P2 context-only; P3 context + episode history; P4 integrated policy + dependency-aware event quarantine.

## 7. ONLY MAJOR TASK NOW: GATE D

### Gate D — Formal Properties + Proof/Check Strategy

Do not jump to firmware implementation or Gate E.

Use Gates A–C as normative contracts. Do not silently modify them. If a real contradiction is discovered, identify it precisely, preserve history, and record an explicit amendment decision.

Gate D must:

1. formalize the six core invariants;
2. define precise predicates for quarantine safety, association conservatism, preservation/correct blocking, dependency safety, recovery termination, and bounded resource use;
3. formalize `EventRef` generation validity;
4. formalize release safety;
5. formalize coupled-transaction containment;
6. prove/check the four-action recovery bound;
7. check completeness and consistency of the deterministic decision table across Gate B fault/association combinations;
8. identify finite-state assumptions and state-space bounds suitable for host-side exhaustive checking;
9. design assertions/property checks that can later be embedded in the reference prototype;
10. distinguish properties that can be proven from those requiring experimental validation;
11. define a practical proof/check strategy without claiming full formal verification of the firmware.

## 8. RESEARCH DISCIPLINE

For every property ask:

- What is the exact state space?
- What is assumed?
- Is the property safety, liveness/termination, boundedness, or observational correctness?
- Can it be exhaustively checked on a finite host model?
- Can it be represented as a runtime assertion later?
- What counterexample would falsify it?
- Does it depend on hardware behavior not yet validated?

Avoid theorem inflation. A finite host model is evidence about the modeled semantics, not proof that arbitrary firmware/hardware behavior satisfies them.

## 9. RESEARCH HONESTY

Never fabricate:

- hardware availability;
- physical measurements;
- benchmark results;
- energy measurements;
- hardware fault-injection results;
- novelty;
- patentability.

Host-side exhaustive checking is not physical MCU validation. Software fault injection is not physical fault validation.

## 10. GATE D ARTIFACT AND CHECKPOINT

When Gate D is complete, create:

`research/phase1_gateD_formal_properties_final.md`

Then update:

- `PROJECT_STATE.md`
- `CURRENT_HANDOFF.md`
- `DECISION_LOG.md`
- `NEXT_CHAT_PROMPT.md` (replace it with the complete Gate E startup prompt)

Preserve all historical files. Avoid unnecessary deletions and cosmetic rewrites. Ensure `main` contains the complete Gate D checkpoint and synchronize the active design branch with `main` if appropriate. Verify actual branch state before declaring completion.

## 11. CHAT D STOPPING RULE

Stop after Gate D is fully reasoned, checked at the design/model level, documented, accepted/rejected, checkpointed, and synchronized.

Do not continue into Gate E.

The next chat begins:

**Gate E — Baselines + Experimental Protocol**

Proceed now with Gate D — Formal Properties + Proof/Check Strategy.

---
