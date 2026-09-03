# Next Chat Prompt — Gate C

Copy/paste the following prompt into the next ChatGPT 5 chat.

---

You are continuing my embedded-systems research project from the canonical GitHub repository:

`SujitSaiY2007/embedded-runtime-resilience`

## 1. IMPORTANT: CONTINUATION, NOT RESTART

Do **not** restart topic ideation, prior-art exploration, MCU selection, Phase 1 preparation, Gate A, or Gate B.

The project has already passed those stages.

Your first responsibility is to reconstruct the current state from GitHub and continue from the exact repository checkpoint.

GitHub is the durable source of truth. Do not rely on missing conversation history when the repository can answer the question.

## 2. MANDATORY FIRST STEP

Before doing substantive design work, read these files from `main` in this order:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. `CHAT_CONTINUITY_PROTOCOL.md`
6. `research/phase1_gateA_event_model_final.md`
7. `research/phase1_gateB_fault_model_final.md`
8. `research/phase1_gateB_learning_summary.md`
9. `research/phase1_event_model.md`
10. `research/phase1_mcu_board_selection.md`
11. `research/phase1_peripheral_testbed_fault_model.md`
12. `research/phase1_recovery_policy_design.md`

After reading them, briefly state:

- what the project is;
- what Gate A froze;
- what Gate B froze;
- why Gate B matters to the research question;
- exactly what Gate C is now expected to freeze.

Do not begin implementation at this point.

## 3. CURRENT PROJECT CHECKPOINT

Frozen topic:

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short working title:

**Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

Core research question:

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## 4. COMPLETED GATES

### Gate A — Exact Event Model and Dependency Semantics: COMPLETE

Final artifact:

`research/phase1_gateA_event_model_final.md`

Important frozen semantics:

- active event identity is `EventRef = {slot_id, generation}`;
- transaction identity is separate and bounded;
- dependencies are explicitly `INDEPENDENT`, `ORDERED`, or `COUPLED/TRANSACTIONAL`;
- dependencies are not inferred from peripheral equality;
- FIFO is admission order, not universal execution order;
- dispatch uses an explicit eligibility predicate;
- quarantine is retained non-executable state, not deletion or global queue flushing;
- preservation means correct verified execution, not merely queue retention;
- fault-association precision may not exceed evidence precision;
- provisional host-model bounds are `QMAX=16`, `XMAX=4`, `DMAX=4` pending Gate E validation.

### Gate B — Fault Model + Fault Association: COMPLETE

Final artifact:

`research/phase1_gateB_fault_model_final.md`

Educational companion:

`research/phase1_gateB_learning_summary.md`

Gate B is accepted at the semantic/design level. No physical measurements or hardware validation are claimed.

Primary I2C observed fault classes:

- NACK/non-acknowledge;
- transfer timeout/no-progress;
- bus/protocol error;
- arbitration/bus-ownership error;
- persistent no-progress / suspected peripheral-state failure.

Secondary SPI classes are deliberately reduced because SPI fault evidence is more implementation/device dependent and SPI has no universal NACK equivalent.

Association levels:

- `EXACT_EVENT_TRANSACTION`
- `SERVICE_ONLY`
- `PERIPHERAL_ONLY`
- `UNKNOWN_AMBIGUOUS`

Critical Gate B rules:

- recurrence and persistence are history/episode attributes, not independent instantaneous fault classes;
- observed NACK/timeout/BERR/etc. are evidence about an observed condition, not automatic proof of a physical root cause;
- same-peripheral membership never justifies event-level causal attribution;
- service/driver failure without sufficient peripheral evidence remains distinct from peripheral failure;
- fault association scope and dependency-blocking scope are distinct;
- software fault injection is deterministic test stimulus, not physical hardware validation;
- physical/protocol fault-injection candidates remain unvalidated until actual hardware, safety review, and repeatability testing;
- a fault episode continues across qualifying repeated observations until verified success, degraded terminal handling, or escalation; a post-terminal failure starts a new episode;
- the semantic fault record is fixed-size/static and bounded.

The most important mental model is:

`Gate A: What work exists and what depends on what?`

`Gate B: What failed, what can we prove, and what work is defensibly associated with it?`

`Gate C: Given that context and recovery history, what bounded action should be taken?`

## 5. PRIMARY PLATFORM DIRECTION

**STM32U575ZI / NUCLEO-U575ZI-Q**

Initial interfaces:

- I2C — primary experimental interface;
- SPI — secondary interface;
- UART/USART — diagnostic/control path.

Physical acquisition is not assumed. No physical measurement may be claimed without actual hardware execution.

## 6. YOUR ONLY MAJOR TASK NOW: GATE C

### Gate C — Recovery Policy + Bounded State Machine

Use the completed Gate A and Gate B contracts to derive and freeze the smallest defensible deterministic recovery policy.

Do **not** jump to firmware implementation.

Do **not** start large-scale C code.

Do **not** redesign Gate A or Gate B unless you find a genuine semantic contradiction. If a contradiction is found:

1. identify the exact contradiction;
2. explain why it matters;
3. preserve the original artifact/history;
4. propose an explicit amendment;
5. record the decision rather than silently rewriting history.

## 7. GATE C OBJECTIVES

Freeze all of the following:

1. **Minimum fault context** — identify only variables that materially change recovery decisions.
2. **Minimum bounded recovery history** — determine the smallest useful fixed-size representation of recent recovery outcomes.
3. **Finite recovery action set** — define technically distinct actions, especially whether peripheral reinitialization and peripheral reset are genuinely distinct on the selected U575 path.
4. **Deterministic policy** — produce an exact decision table or equivalent deterministic rule set with no hidden scoring/heuristics.
5. **Association-aware behavior** — define what happens for `EXACT_EVENT_TRANSACTION`, `SERVICE_ONLY`, `PERIPHERAL_ONLY`, and `UNKNOWN_AMBIGUOUS`.
6. **Exact transitions** — define retry, reinitialization/reset, degradation, escalation, success, failure, and release/requeue behavior.
7. **Bounded transition budget** — define exactly what counts as an attempt/transition and prove that every episode has a finite maximum policy progression.
8. **Scheduling interaction** — define how recovery interacts with event eligibility, quarantine, FIFO admission, ordering, coupled transactions, and dependency blocking from Gate A.
9. **Degraded mode** — define safe, bounded degraded behavior for reference services without inventing a general resilience framework.
10. **Policy output record** — define a fixed-size output/action record that later implementation and experiments can consume.
11. **Ablation variants** — define experiments that can distinguish the value of context and history from a simpler fixed policy.

## 8. CRITICAL DESIGN DISCIPLINE

Treat every policy variable and action as a hypothesis, not as a default feature.

For every proposed input variable ask:

- Does it actually change a recovery decision?
- Is it already derivable from another field?
- Can it be observed reliably on the reference architecture?
- What is its static RAM/Flash cost?
- Does keeping it improve falsifiability or measurement?
- What happens if the value is ambiguous or unavailable?

For every proposed recovery action ask:

- Is it technically distinct on the selected platform/peripheral?
- What state does it change?
- What events must remain blocked while it runs?
- What evidence is required before affected work can be released?
- What is the worst-case bounded cost?
- What happens if the action itself fails?
- Can the action terminate the episode within the declared bound?

Challenge complexity aggressively. Do not add machine learning, dynamic recovery objects, large scoring engines, adaptive frameworks, or unrelated resilience features unless a concrete contradiction shows the minimal deterministic design cannot answer the research question.

## 9. STARTING BASELINE TO CHALLENGE

The file:

`research/phase1_recovery_policy_design.md`

is an earlier proposed design baseline. It is **not** frozen.

Its candidate inputs include:

- `fault_class`
- `fault_recurrence`
- `attempt_count`
- `last_action`
- `last_outcome`
- `service_criticality`
- `event_dependency_status`
- `pending_independent_work`

Its candidate action set is:

- `RETRY`
- `REINIT_OR_RESET`
- `DEGRADE`
- `ESCALATE`

It suggests a provisional bound such as `Rmax=3`.

Do not copy these choices blindly. Determine whether each is necessary, redundant, ambiguous, experimentally useful, and technically implementable. Numerical values must be justified rather than inherited merely because they appear in the baseline.

## 10. REQUIRED GATE C ARTIFACT

Create:

`research/phase1_gateC_recovery_policy_final.md`

It must contain, at minimum:

- scope and acceptance criteria;
- relationship to Gate A and Gate B;
- policy inputs and evidence basis;
- minimum bounded recovery history;
- exact action set and semantics;
- action preconditions, effects, postconditions, and failure handling;
- association-confidence-dependent policy behavior;
- deterministic decision table;
- complete recovery state machine;
- exact attempt/transition-budget semantics;
- event quarantine/scheduling/dependency interaction;
- degraded-mode semantics;
- fixed-size policy output record;
- policy ablation plan;
- resource-boundedness implications;
- explicit rejected assumptions and rejected alternatives;
- unresolved questions transferred to Gate D;
- final Gate C acceptance/rejection decision.

## 11. REQUIRED RESEARCH REASONING

Before freezing the policy, explicitly test at least these potential weaknesses:

- whether `service_criticality` belongs in the policy or only in scheduling/dependency semantics;
- whether `pending_independent_work` is truly a policy input or merely a consequence of the scheduler state;
- whether `last_action` and `last_outcome` provide independent information beyond an episode/retry counter;
- whether `fault_recurrence` can be represented more compactly as bounded episode history;
- whether `REINIT` and `RESET` are truly distinct experimentally on U575;
- whether ambiguous association should cause broader containment or a conservative no-release state;
- whether retrying a coupled transaction can violate Gate A transaction semantics;
- whether degraded mode needs a service-specific state or can use a bounded common abstraction;
- whether the policy can remain deterministic without a numeric score;
- whether the proposed transition bound is sufficient for all defined action paths while remaining experimentally meaningful.

## 12. RESEARCH HONESTY

Do not fabricate:

- hardware availability;
- physical measurements;
- benchmark results;
- energy measurements;
- fault-injection success on hardware;
- novelty;
- patentability.

Host simulation is not physical MCU validation.

Software fault injection is not proof of a physical fault mechanism.

The project contribution must remain the specific integrated mechanism and its measured trade-off, not any individual established ingredient.

## 13. GITHUB CHECKPOINT REQUIREMENT

At the end of Gate C:

1. create/update `research/phase1_gateC_recovery_policy_final.md`;
2. update `PROJECT_STATE.md`;
3. update `CURRENT_HANDOFF.md`;
4. update `DECISION_LOG.md`;
5. replace/update `NEXT_CHAT_PROMPT.md` so it becomes the complete Gate D startup prompt;
6. preserve all historical documents;
7. avoid unnecessary deletions and cosmetic rewrites;
8. ensure `main` contains the complete Gate C checkpoint;
9. synchronize the active design branch with `main` if appropriate;
10. verify the actual branch state before declaring completion.

Do not claim completion until the repository actually reflects the checkpoint.

## 14. CHAT C STOPPING RULE

**Stop after Gate C is fully designed, accepted/rejected, documented, checkpointed, and synchronized.**

Do not continue into Gate D merely because Gate C finishes early.

The next chat must begin:

**Gate D — Formal Properties + Proof/Check Strategy**

The repository must contain enough information for that next chat to reconstruct the project without depending on this conversation's history.

Proceed from the repository checkpoint and begin **Gate C — Recovery Policy + Bounded State Machine**.

---
