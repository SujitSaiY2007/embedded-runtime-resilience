# Next Chat Prompt — Gate E

Copy/paste the following prompt into the next ChatGPT 5 chat.

---

You are continuing my embedded-systems research project from the canonical GitHub repository:

`SujitSaiY2007/embedded-runtime-resilience`

## 1. IMPORTANT: CONTINUATION, NOT RESTART

This is a continuation of an existing research project. Do not restart topic ideation, prior-art exploration, MCU selection, Phase 1 preparation, Gate A, Gate B, Gate C, or Gate D.

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
10. `research/phase1_gateD_formal_properties_final.md`
11. `research/phase1_event_model.md`
12. `research/phase1_mcu_board_selection.md`
13. `research/phase1_peripheral_testbed_fault_model.md`
14. `research/phase1_recovery_policy_design.md`

Then provide a concise continuity check covering:

- frozen research topic;
- frozen research question;
- platform direction;
- Gate A result;
- Gate B result;
- Gate C result;
- Gate D result;
- why Gates A–D matter together;
- exact Gate E task;
- explicit non-goals.

Do not begin firmware implementation.

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

## 7. COMPLETED GATE D

`research/phase1_gateD_formal_properties_final.md`

Gate D is accepted at the semantic/design-model level.

### Formalized properties

Gate D formalized/check-specified:

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

### Gate D model-level result

A host-side abstract audit enumerated **33,792** encoded policy contexts and found exactly one outcome for every context. The audit covers 11 bounded fault classes, 4 association levels, 3 criticality classes, 4 active attempt-count values, 8 recovery-safety masks, and success/prohibition/containment status bits.

This is model-level evidence about decision totality/determinism. It is not firmware verification, MCU validation, or physical fault validation.

### Gate D qualifications

- `QMAX=16`, `XMAX=4`, `DMAX=4` remain provisional until Gate E workload validation.
- Generation width/wrap behavior must be concretely specified before implementation; stale references must fail closed.
- A single active recovery episode was used as a host-model proof decomposition. If implementation permits multiple simultaneous service/peripheral episodes outside retained event slots, a fixed `EPMAX` must be declared and resource-accounted before implementation.
- Host-state checking is evidence about the modeled semantics, not proof of arbitrary MCU/hardware behavior.

## 8. ONLY MAJOR TASK NOW: GATE E

### Gate E — Baselines + Experimental Protocol

Do not jump to firmware implementation, physical bring-up, or experimental execution before the Gate E protocol is frozen.

Use Gates A–D as normative contracts. Do not silently modify them. If a real contradiction is discovered, identify it precisely, preserve history, and record an explicit amendment decision.

Gate E must:

1. freeze baseline definitions and exact comparability;
2. freeze the workload matrix and event/dependency scenarios;
3. freeze the deterministic software fault schedule and define how later physical-fault scenarios map to the semantic fault classes;
4. validate or revise `QMAX`, `XMAX`, and `DMAX` using the workload rather than convenience;
5. define any required finite recovery-context bound such as `EPMAX` if the implementation supports simultaneous episodes;
6. freeze the final history-window/episode-record capacity used in experiments;
7. freeze correctness metrics and performance/resource metrics;
8. freeze logging schema, event/episode identifiers, and trace correlation;
9. freeze repetitions, deterministic schedules/randomization rules, and reset/warm-up policy;
10. freeze statistical/reproducibility treatment and handling of invalid runs;
11. freeze acceptance criteria and reporting format;
12. separate host-model measurements from MCU measurements and from physical fault-validation claims;
13. define the minimum evidence required before making any performance, robustness, or generalization claim.

### Baselines to reconcile carefully

The project has two related descriptions of the comparison set that must be reconciled without losing history:

- Gate C ablation: P0 fixed retry; P1 fixed retry + peripheral recovery; P2 context-only; P3 context + episode history; P4 integrated policy + dependency-aware event quarantine.
- Earlier experimental direction: fixed retry; fixed retry + peripheral reset/reinitialization; proposed zero-heap context-aware recovery + dependency-aware event quarantine.

Do not silently collapse or delete these definitions. Determine the smallest coherent experimental matrix that preserves the research question and makes comparisons fair. If a variant is redundant, document the rationale and retain the historical terminology.

### Workload requirements

At minimum, Gate E should define scenarios containing:

- independent valid events;
- ordered dependencies;
- coupled/transactional events;
- fault-associated event/transaction;
- multiple queued events sharing a peripheral without implying causal association;
- recovery success after retry;
- retry failure followed by reinitialization/reset;
- terminal degradation;
- terminal escalation;
- queue and quarantine capacity boundaries;
- stale `EventRef` generation cases;
- ambiguity/service-only/peripheral-only association cases where practical in the host model.

### Required correctness outcomes

At minimum define how to measure/count:

- quarantine violations;
- stale-reference mis-targeting;
- incorrect event-level attribution;
- preserved independent events;
- correctly blocked dependent events;
- incorrectly blocked/lost valid independent events;
- lost events;
- duplicated events;
- invalid coupled-transaction execution;
- recovery-action bound violations;
- premature release;
- terminal-state re-entry into recovery.

### Required performance/resource outcomes

Define reproducible measurement methods for:

- fault-detection latency;
- service-restoration latency;
- recovery success/failure;
- whole-system reset/escalation count;
- queue occupancy/high-water mark;
- quarantine occupancy/high-water mark;
- CPU time/overhead;
- RAM footprint;
- Flash footprint;
- energy only if a valid measurement method becomes available.

Do not invent numerical acceptance thresholds before they are justified by the experiment/design objective.

### Fault schedule

Start with deterministic software injection because it is reproducible. The schedule should specify:

- fault class;
- injection point;
- affected event/transaction;
- association level;
- workload position;
- recovery configuration;
- expected verification outcome;
- run identifier/seed if applicable.

Physical fault injection is a later validation layer, not a prerequisite for freezing the host experimental protocol.

## 9. RESEARCH DISCIPLINE

For every Gate E decision ask:

- What exact hypothesis does this choice test?
- Is the baseline genuinely comparable to the proposed mechanism?
- Which variables are fixed and which are independent variables?
- Could the workload accidentally reward aggressive blocking?
- Are queue-capacity effects being mistaken for recovery benefit?
- Are software-injected faults being overinterpreted as physical faults?
- Can another researcher reproduce the schedule and logging?
- Which claims will still require MCU hardware evidence?

Avoid theorem inflation and experimenter degrees of freedom that can be changed after seeing results.

## 10. RESEARCH HONESTY

Never fabricate:

- hardware availability;
- physical measurements;
- benchmark results;
- energy measurements;
- hardware fault-injection results;
- statistical significance before data exist;
- novelty;
- patentability.

Host-side results are not MCU measurements. Software fault injection is not physical fault validation.

## 11. GATE E ARTIFACT AND CHECKPOINT

When Gate E is complete, create:

`research/phase1_gateE_experimental_protocol_final.md`

Then update:

- `PROJECT_STATE.md`
- `CURRENT_HANDOFF.md`
- `DECISION_LOG.md`
- `NEXT_CHAT_PROMPT.md` (replace it with the complete Minimal Reference Implementation startup prompt)

Preserve all historical files. Avoid unnecessary deletions and cosmetic rewrites. Ensure `main` contains the complete Gate E checkpoint and synchronize the active design branch with `main` if appropriate. Verify actual branch state before declaring completion.

## 12. CHAT E STOPPING RULE

Stop after Gate E is fully reasoned, checked at the design/protocol level, documented, accepted/rejected, checkpointed, and synchronized.

Do not continue into firmware implementation or physical testbed bring-up.

The next chat begins:

**Minimal Reference Implementation — smallest testable reference prototype**

---
