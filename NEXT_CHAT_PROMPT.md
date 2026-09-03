# Next Chat Prompt — Minimal Reference Implementation

Copy/paste the following prompt into the next ChatGPT 5 chat.

---

You are continuing my embedded-systems research project from the canonical GitHub repository:

`SujitSaiY2007/embedded-runtime-resilience`

## 1. IMPORTANT: CONTINUATION, NOT RESTART

This is a continuation of an existing research project. Do not restart topic ideation, prior-art exploration, MCU selection, Phase 1 preparation, Gate A, Gate B, Gate C, Gate D, or Gate E.

GitHub is the durable source of truth. Reconstruct the project from `main` before doing substantive work.

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
11. `research/phase1_gateE_experimental_protocol_final.md`
12. `research/phase1_event_model.md`
13. `research/phase1_mcu_board_selection.md`
14. `research/phase1_peripheral_testbed_fault_model.md`
15. `research/phase1_recovery_policy_design.md`

Then provide a concise continuity check covering:

- frozen research topic;
- frozen research question;
- STM32U575ZI / NUCLEO-U575ZI-Q platform direction;
- Gate A result;
- Gate B result;
- Gate C result;
- Gate D result;
- Gate E result;
- why Gates A–E form one coherent research chain;
- exact implementation task for this chat;
- explicit non-goals.

Do not restart research or redesign completed gates without identifying a concrete contradiction.

## 3. FROZEN PROJECT

### Topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

### Research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

### Platform direction

**STM32U575ZI / NUCLEO-U575ZI-Q**

I2C is primary, SPI secondary, UART/USART diagnostic/control. Hardware availability is not assumed.

## 4. FROZEN GATES A–E

### Gate A — Event Model

Final artifact: `research/phase1_gateA_event_model_final.md`

Frozen semantics:

- `EventRef = {slot_id, generation}`;
- separate bounded transaction identity;
- explicit `INDEPENDENT`, `ORDERED`, `COUPLED/TRANSACTIONAL` dependencies;
- dependencies are not inferred from peripheral equality;
- FIFO is admission order, not universal execution order;
- eligibility controls execution;
- quarantine is retained non-executable state;
- preservation means correct verified execution;
- protocol envelope now frozen by Gate E as `QMAX=16`, `XMAX=4`, `DMAX=4`.

### Gate B — Fault Model

Final artifact: `research/phase1_gateB_fault_model_final.md`

Primary I2C observations:

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

Recurrence/persistence are episode/history attributes. Software injection is deterministic test stimulus, not physical validation.

### Gate C — Recovery Policy

Final artifact: `research/phase1_gateC_recovery_policy_final.md`

Minimum policy context:

- `fault_class`
- `association_level`
- bounded `attempt_count`
- `criticality`
- bounded `recovery_safety` precondition results
- `episode_state`

Logical actions:

- `RETRY`
- `REINIT_OR_RESET`
- `DEGRADE`
- `ESCALATE`

Exact budget:

`T1=RETRY #1 -> T2=RETRY #2 -> T3=REINIT_OR_RESET -> T4=terminal`

`MAX_RECOVERY_ACTIONS=4`.

Association, scheduling, dependency, coupled-transaction, degraded-mode, release, and ablation semantics remain frozen as defined in Gate C.

Ablation:

- P0 fixed retry;
- P1 fixed retry + peripheral recovery;
- P2 context-only;
- P3 context + episode history;
- P4 integrated context/history + dependency-aware event quarantine.

### Gate D — Formal Properties

Final artifact: `research/phase1_gateD_formal_properties_final.md`

Formalized/check-specified properties include quarantine safety, fault-association conservatism, service preservation versus correct blocking, dependency safety, bounded recovery termination, bounded resources, EventRef generation validity/stale-reference rejection, release safety, coupled-transaction containment, and deterministic decision-table totality/consistency.

A host-side abstract audit covered **33,792** encoded policy contexts with exactly one outcome per context. This is model-level evidence only.

### Gate E — Experimental Protocol

Final artifact: `research/phase1_gateE_experimental_protocol_final.md`

Gate E is accepted at the experimental-design/protocol level.

Frozen comparison set:

- P0 fixed retry baseline;
- P1 fixed retry + peripheral recovery baseline;
- P2 context-only ablation;
- P3 context + episode-history ablation;
- P4 integrated proposed mechanism.

P0/P1 are principal baselines; P2/P3 isolate mechanism contributions; P4 is the integrated mechanism.

Frozen canonical workloads:

W01 independent preservation; W02 ordered dependency blocking; W03 coupled transaction containment; W04 shared-peripheral non-causality; W05 retry-success; W06 retry-failure then reinit/reset success; W07 terminal degradation; W08 terminal escalation; W09 queue-capacity boundary; W10 quarantine-capacity boundary; W11 stale EventRef generation; W12 association ambiguity; W13 criticality/degradability; W14 mixed integrated workload.

Frozen protocol envelope:

`QMAX=16`, `XMAX=4`, `DMAX=4`, `EPMAX=1` for the normative reference prototype unless explicitly amended.

Frozen stimulus/evidence rules:

- deterministic software fault injection is the primary repeatable stimulus;
- I2C is primary and SPI secondary;
- physical fault injection is a later validation layer;
- host results are not MCU measurements;
- software injection is not physical validation;
- energy is optional only if valid instrumentation becomes available;
- no unsupported performance, robustness, generalization, novelty, or patentability claims.

Frozen trace/logging requirements include stable `run_id`, `trace_seq`, `event_ref`, `fault_episode_id`, `observation_seq`, action index, and final outcome/correctness fields.

## 5. ONLY MAJOR TASK NOW: MINIMAL REFERENCE IMPLEMENTATION

Build the **smallest testable reference prototype**, not a general resilience framework.

The implementation must begin from the frozen Gates A–E contracts.

### Required first-stage objectives

1. Define the smallest executable host/reference architecture.
2. Concretely specify the fixed storage layout for events, queue, quarantine/recovery retention, dependencies, and the single active recovery episode.
3. Concretely specify the finite `EventRef` generation width and wrap/fail-closed behavior.
4. Define a deterministic scheduler selection rule consistent with Gate A.
5. Implement the Gate C recovery-policy decision interface and bounded state machine.
6. Implement deterministic software fault injection using the Gate B semantic fault classes.
7. Implement the canonical Gate E workload traces, initially prioritizing W01–W08 and then the capacity/identity/ambiguity workloads.
8. Add host-side assertions/property tests corresponding to Gate D.
9. Add structured trace output using the Gate E identifiers/schema.
10. Demonstrate zero runtime heap allocation in the reference implementation and provide static resource accounting.
11. Keep MCU-specific code isolated from the host reference until the reference semantics are stable.
12. Preserve raw/reproducible test inputs and avoid hidden test-only behavior.

### Required implementation decisions to make explicitly

Before coding substantial amounts, document:

- language/toolchain for the host reference;
- source-tree structure;
- fixed event-slot count and relationship to `QMAX`/`XMAX`;
- exact queue/quarantine storage strategy so events are not double-counted;
- generation integer width and wrap policy;
- dependency representation using `DMAX=4`;
- deterministic eligible-event selection rule;
- exact episode record for `EPMAX=1`;
- fixed-size `PolicyDecision` representation;
- verification interface for retry/reinit/degrade/escalate outcomes;
- fault-schedule representation;
- trace serialization format;
- compile/test commands;
- static RAM/Flash estimates for the host/reference representation where meaningful.

Do not invent MCU RAM/Flash results from host measurements.

## 6. TESTING REQUIREMENTS

The first reference test suite must verify at least:

### Event/dependency

- independent event bypass of quarantined unrelated work;
- ordered predecessor blocking;
- coupled transaction containment;
- shared-peripheral non-causality;
- full-queue deterministic behavior.

### Recovery

- retry success on first retry;
- second-retry success;
- reinit/reset success after two failed retries;
- terminal degradation;
- terminal escalation;
- no fifth recovery action;
- terminal state cannot re-enter recovery.

### Identity/quarantine

- quarantined event cannot execute through ordinary dispatch;
- authorized retry is distinguishable from ordinary dispatch;
- stale generation reference cannot target a new event;
- release returns to eligibility evaluation rather than unconditional execution.

### Association

- exact association permits the narrowest safe target;
- service-only/peripheral-only evidence cannot create false event-level attribution;
- ambiguous evidence remains conservative.

### Resource/boundary

- queue occupancy never exceeds `QMAX` without an explicit overflow outcome;
- quarantine occupancy never exceeds `XMAX` without an explicit bounded outcome;
- dependency entries never exceed `DMAX`;
- episode state remains within `EPMAX=1`;
- no dynamic allocation path exists.

### Trace correctness

Every test result must be attributable to the declared workload, fault schedule, variant, event reference, episode, action sequence, and final outcome.

## 7. IMPLEMENTATION DISCIPLINE

Do not silently modify Gate A–E.

If implementation exposes a contradiction:

1. stop at the smallest affected boundary;
2. identify the exact contradiction;
3. do not silently patch the semantic contract;
4. record an explicit decision/amendment before proceeding.

Do not add:

- generic plugin architecture;
- dynamic containers;
- unnecessary RTOS dependencies;
- unrelated peripherals;
- production-grade resilience features;
- optimization before correctness;
- physical fault injection before the reference semantics are stable.

The objective is a research reference implementation that is small enough to inspect and reproduce.

## 8. STOPPING RULE FOR THIS CHAT

Stop at the **smallest testable reference implementation checkpoint** once:

- the core fixed-storage model exists;
- policy and scheduler semantics are executable;
- deterministic fault injection works;
- the initial canonical correctness suite passes;
- Gate D properties are asserted/tested where applicable;
- traces are reproducible;
- zero-heap/static-allocation constraints are demonstrated for the reference;
- implementation decisions are documented;
- `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, `DECISION_LOG.md`, and `NEXT_CHAT_PROMPT.md` are updated as needed.

Do not automatically proceed into full MCU firmware integration or physical testbed bring-up in the same chat merely because the host prototype passes.

## 9. RESEARCH HONESTY

Never fabricate:

- hardware availability;
- MCU timing/RAM/Flash measurements;
- energy measurements;
- physical fault-injection results;
- benchmark results;
- statistical significance;
- novelty;
- patentability.

Host/reference results must remain explicitly labeled as host/reference evidence.

## 10. CONTINUITY REQUIREMENT

At the end of the chat, the repository must be sufficient for another chat to continue without relying on this conversation history.

The next continuation prompt must be generated from the actual repository state, not from assumptions.

---
