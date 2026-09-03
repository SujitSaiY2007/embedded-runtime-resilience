# Next Chat Prompt — Gate C

Copy/paste the following prompt into the next ChatGPT 5 chat.

---

You are continuing my embedded-systems research project from the canonical GitHub repository:

`SujitSaiY2007/embedded-runtime-resilience`

## IMPORTANT: CONTINUATION, NOT RESTART

Do **not** restart topic ideation, prior-art exploration, MCU selection, Phase 1 preparation, Gate A, or Gate B.

The project has already passed those stages.

Your first responsibility is to reconstruct the current state from GitHub and continue from the exact repository checkpoint.

### Mandatory first step

Read these files from the `main` branch before doing substantive work:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `CHAT_CONTINUITY_PROTOCOL.md`
6. `research/phase1_gateA_event_model_final.md`
7. `research/phase1_gateB_fault_model_final.md`
8. `research/phase1_event_model.md`
9. `research/phase1_mcu_board_selection.md`
10. `research/phase1_peripheral_testbed_fault_model.md`
11. `research/phase1_recovery_policy_design.md`

Treat GitHub as the durable source of truth. Do not rely on missing conversation history when the repository can answer the question.

## CURRENT CHECKPOINT

The frozen topic is:

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short working title:

**Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

Core research question:

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

### Completed gates

- **Gate A — Exact Event Model and Dependency Semantics: COMPLETE**
- **Gate B — Fault Model + Fault Association: COMPLETE**

Gate A final artifact:

`research/phase1_gateA_event_model_final.md`

Gate B final artifact:

`research/phase1_gateB_fault_model_final.md`

The original baseline documents remain retained.

## FROZEN GATE A SEMANTICS

- active event identity: `EventRef = {slot_id, generation}`;
- transaction identity is separate and bounded;
- dependencies are explicitly `INDEPENDENT`, `ORDERED`, or `COUPLED/TRANSACTIONAL`;
- dependencies are not inferred from peripheral equality;
- FIFO is admission order, not universal execution order;
- dispatch uses an explicit eligibility predicate;
- quarantine is retained non-executable state;
- preservation means correct verified execution, not merely queue retention;
- fault-association precision may not exceed evidence precision;
- provisional host-model bounds remain `QMAX=16`, `XMAX=4`, `DMAX=4` pending Gate E validation.

## FROZEN GATE B SEMANTICS

### Primary I2C observed fault classes

- NACK/non-acknowledge;
- transfer timeout/no-progress;
- bus/protocol error;
- arbitration/bus-ownership error;
- persistent no-progress / suspected peripheral-state failure.

### Secondary SPI classes

- transfer timeout/no-progress;
- transaction/protocol verification failure;
- persistent communication failure;
- ambiguous attribution.

### Attribution classes

- `EXACT_EVENT_TRANSACTION`
- `SERVICE_ONLY`
- `PERIPHERAL_ONLY`
- `UNKNOWN_AMBIGUOUS`

### Critical evidence rules

- recurrence and persistence are history/episode attributes, not independent instantaneous fault classes;
- NACK, timeout, BERR, etc. are observations, not automatic physical root-cause proofs;
- same-peripheral membership never justifies event-level causal attribution;
- service/driver failure without sufficient peripheral evidence must remain distinct;
- software fault injection is deterministic test stimulus, not physical hardware validation;
- physical fault-injection candidates remain unvalidated until actual hardware, safety, and repeatability are demonstrated;
- a fault episode continues across qualifying repeated observations until verified success, degraded terminal handling, or escalation; a post-terminal fault begins a new episode;
- fault association scope and dependency-blocking scope are distinct.

## PRIMARY PLATFORM DIRECTION

**STM32U575ZI / NUCLEO-U575ZI-Q**

Initial interfaces:

- I2C — primary experimental interface;
- SPI — secondary interface;
- UART/USART — diagnostic/control path.

Physical acquisition is not assumed. No physical measurement may be claimed without actual hardware execution.

## YOUR TASK NOW: GATE C

### Gate C — Recovery Policy + Bounded State Machine

This is the **only major gate to work on in this chat**.

Do not jump to firmware implementation.

Do not begin large-scale C code.

Do not redesign Gate A or Gate B unless a genuine contradiction is found. If one is found, explicitly identify it, explain why it matters, preserve the original artifact, and document the amendment rather than silently rewriting history.

## GATE C OBJECTIVES

Using the completed Gate A and Gate B contracts, freeze:

1. the minimum fault-context variables that materially change recovery decisions;
2. the minimum useful bounded recovery-history representation;
3. the finite recovery action set and technically distinct action semantics;
4. the deterministic recovery decision table/policy;
5. recovery behavior for each association-confidence level;
6. exact retry/reinitialization/degradation/escalation transitions;
7. the bounded recovery transition budget;
8. interaction between recovery and event scheduling/quarantine/dependency blocking;
9. safe degraded-mode semantics for the reference services;
10. the compact policy output record and its fixed-size storage semantics;
11. policy ablation variants needed to test whether context/history actually contributes value.

## CRITICAL GATE C STANDARD

Treat every policy variable and action as a hypothesis to test.

For every proposed input variable ask:

- Does it change a recovery decision?
- Is it already derivable from another field?
- Can it be observed reliably?
- Does retaining it justify its RAM/Flash cost?
- Would removing it change the experiment's ability to falsify the hypothesis?

For every proposed recovery action ask:

- Is it technically distinct on the selected platform/peripheral?
- What state does it change?
- What events must remain blocked while it executes?
- What evidence is required before release?
- What is its worst-case bounded cost?
- What happens if it fails?

Do not add scoring engines, machine learning, dynamic recovery objects, or general resilience features unless evidence demonstrates that the minimal deterministic policy is inadequate.

## STARTING BASELINE TO CHALLENGE

`research/phase1_recovery_policy_design.md` is an earlier proposed architecture, not a frozen policy.

Its current candidate inputs include:

- `fault_class`
- `fault_recurrence`
- `attempt_count`
- `last_action`
- `last_outcome`
- `service_criticality`
- `event_dependency_status`
- `pending_independent_work`

Its current effective candidate action set is:

- `RETRY`
- `REINIT_OR_RESET`
- `DEGRADE`
- `ESCALATE`

The baseline suggests a small deterministic decision table and a provisional recovery transition bound such as `Rmax=3`, but none of these numerical/policy choices is frozen yet.

Challenge them rather than copying them.

## REQUIRED GATE C ARTIFACT

Create:

`research/phase1_gateC_recovery_policy_final.md`

It must include:

- scope and acceptance criteria;
- policy inputs and evidence basis;
- minimum bounded recovery history;
- exact action semantics;
- action safety/preconditions/postconditions;
- association-confidence-dependent policy behavior;
- deterministic decision table;
- recovery state machine;
- exact bounded transition/attempt semantics;
- degraded-mode semantics;
- interaction with Gate A quarantine/dependency rules;
- policy output record;
- policy ablation plan;
- explicit rejected assumptions;
- unresolved questions transferred to Gate D;
- final Gate C acceptance/rejection decision.

## RESEARCH HONESTY

- no fabricated benchmarks;
- no fabricated physical measurements;
- no fabricated board availability;
- no unsupported novelty claims;
- no claim that host simulation equals hardware validation;
- report negative/inconclusive design conclusions honestly;
- keep the implementation minimal and directly tied to the research question.

## GITHUB CHECKPOINT REQUIREMENT

At the end of this chat:

1. update `research/phase1_gateC_recovery_policy_final.md`;
2. update `PROJECT_STATE.md`;
3. update `CURRENT_HANDOFF.md`;
4. update `DECISION_LOG.md`;
5. update this `NEXT_CHAT_PROMPT.md` for Gate D;
6. preserve all historical documents;
7. avoid unnecessary deletions or cosmetic rewrites;
8. ensure `main` contains the complete checkpoint;
9. synchronize the active design branch with `main` if appropriate;
10. verify actual branch state before declaring completion.

Do not claim the checkpoint is complete until GitHub actually reflects it.

## CHAT C STOPPING RULE

**Stop after Gate C is fully checkpointed.**

Do not continue into Gate D merely because Gate C finishes early.

The next chat after this one must begin:

**Gate D — Formal Properties + Proof/Check Strategy**

The repository must contain enough information for that next chat to reconstruct the project without depending on this conversation's history.

Proceed from the repository checkpoint and begin **Gate C — Recovery Policy + Bounded State Machine**.

---
