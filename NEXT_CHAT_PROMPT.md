# Next Chat Prompt — Gate B

Copy/paste the following prompt into the next ChatGPT 5 chat.

---

You are continuing my embedded-systems research project from the canonical GitHub repository:

`SujitSaiY2007/embedded-runtime-resilience`

## IMPORTANT: CONTINUATION, NOT RESTART

Do **not** restart topic ideation, prior-art exploration, MCU selection, Phase 1 preparation, or Gate A.

The project has already passed those stages.

Your first responsibility is to reconstruct the current state from GitHub and continue from the exact repository checkpoint.

### Mandatory first step

Read these files from the `main` branch before doing substantive work:

1. `PROJECT_STATE.md`
2. `CURRENT_HANDOFF.md`
3. `DECISION_LOG.md`
4. `CHAT_CONTINUITY_PROTOCOL.md`
5. `research/phase1_gateA_event_model_final.md`
6. `research/phase1_event_model.md`
7. `research/phase1_mcu_board_selection.md`
8. `research/phase1_peripheral_testbed_fault_model.md`
9. `research/phase1_recovery_policy_design.md`

Treat GitHub as the durable source of truth. Do not rely on missing conversation history when the repository can answer the question.

## CURRENT PROJECT STATE

### Frozen development topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short working title:

**Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

### Core research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

### Frozen architecture constraints

- zero runtime heap allocation in the recovery manager/reference firmware;
- bounded local fault context and short recovery history;
- finite deterministic recovery actions with explicit terminal escalation;
- dependency-aware event quarantine instead of global queue flushing;
- MPU as a platform containment mechanism, not the invention itself;
- lightweight event-driven reference architecture;
- selected formal invariants/properties rather than a claim of full formal verification;
- no unnecessary framework/generalization before the research mechanism is validated.

## SIX CORE INVARIANTS

1. **Quarantine safety** — a quarantined event cannot execute until an explicitly permitted transition.
2. **Fault association** — recovery uses the smallest defensible event/transaction scope; ambiguity is not silently converted into precision.
3. **Service preservation** — unrelated valid work remains eligible only when dependency, ordering, shared-state, and recovery-safety conditions permit it.
4. **Dependency safety** — dependent events cannot bypass an invalid/quarantined predecessor or shared state merely because they are not themselves fault-associated.
5. **Recovery termination** — every fault episode reaches success, degraded, or escalated terminal handling within a declared bounded transition budget.
6. **Bounded resource usage** — queue, quarantine storage, history, and recovery state remain within fixed limits with no runtime heap growth.

These are the current formal correctness boundary. They are not a claim that the firmware is already formally verified.

# GATE A STATUS: COMPLETE

Gate A — Exact Event Model and Dependency Semantics — has already been critically reviewed and accepted.

The final semantic contract is:

`research/phase1_gateA_event_model_final.md`

Important frozen Gate A semantics:

- active event identity is `EventRef = {slot_id, generation}`;
- event types are finite and bounded;
- producer/service/consumer roles are explicitly distinguished;
- peripheral association is separate from dependency;
- criticality is finite and does not override safety/dependency constraints;
- dependencies are explicitly classified as `INDEPENDENT`, `ORDERED`, or `COUPLED/TRANSACTIONAL`;
- dependencies are represented explicitly and bounded, never inferred from peripheral equality;
- FIFO is admission order, not universal execution order;
- dispatch uses an explicit eligibility predicate;
- quarantine is retained non-executable state, not deletion or global queue flushing;
- preservation means correct verified execution, not merely retaining an event in storage;
- full-queue behavior is explicit and bounded;
- `RELEASED` is a transition outcome rather than a persistent lifecycle state;
- fault-association precision may not exceed the evidence available.

Provisional host-model bounds:

- `QMAX = 16`
- `XMAX = 4`
- `DMAX = 4`

These values are provisional and must be validated/revised at Gate E. Do not present them as experimentally optimal.

The original `research/phase1_event_model.md` is historical baseline material and must remain retained.

# PRIMARY PLATFORM DIRECTION

Current platform recommendation:

**STM32U575ZI / NUCLEO-U575ZI-Q**

Initial interface direction:

- I2C — primary experimental peripheral;
- SPI — secondary interface;
- UART/USART — diagnostic/control path.

Physical acquisition is not to be assumed. No physical measurement may be claimed before actual hardware execution.

# YOUR TASK NOW: GATE B

## Gate B — Fault Model + Fault Association

This is the **only major gate to work on in this chat**.

Do not jump to firmware implementation.

Do not begin large-scale C code.

Do not redesign Gate A unless you find a genuine contradiction or missing semantic dependency. If you do find one, explicitly identify it, explain why it matters, and update the repository without deleting the historical Gate A artifact.

## Gate B objectives

Freeze a rigorous, experimentally usable fault model covering:

1. exact fault taxonomy for the selected experimental peripheral(s);
2. deterministic software fault-injection semantics;
3. safely reproducible hardware/protocol fault classes where appropriate;
4. bounded fault-record representation;
5. fault-to-event association rules;
6. association-confidence levels and ambiguity handling;
7. fault-episode boundaries;
8. recurrence/repeated-fault semantics;
9. distinction between event fault, service fault, peripheral fault, and ambiguous fault;
10. evidence required before narrowing fault scope;
11. relationship between fault evidence and quarantine scope;
12. interaction with all six core invariants.

## CRITICAL RESEARCH STANDARD

Treat every assumption as a hypothesis to test.

Do not accept a fault model merely because it sounds plausible.

For each proposed fault class, distinguish:

- what is physically observable;
- what the MCU/software can reliably infer;
- what is only an inference;
- what cannot be distinguished from another fault class;
- what evidence is required to justify event-level association.

Do not manufacture precision that the instrumentation cannot support.

The rule from Gate A remains:

`association precision <= evidence precision`

## Fault taxonomy requirement

Build the smallest defensible taxonomy needed for the research question.

Prefer a taxonomy that supports reproducible comparison between:

1. fixed retry;
2. fixed retry + peripheral reset/reinitialization;
3. proposed context-aware recovery + dependency-aware event quarantine.

Do not add exotic fault classes merely to make the system appear sophisticated.

The taxonomy should consider, as applicable to the chosen I2C/SPI testbed:

- timeout/no-response;
- NACK/error response;
- bus/protocol fault;
- peripheral state-machine lockup/stall;
- repeated transient failure;
- persistent failure;
- ambiguous/insufficiently attributable failure;
- software/service-level failure if it is required to distinguish it from a peripheral fault.

Validate which of these are actually reproducible and observable before freezing them.

## Fault injection

Define two separate categories where useful:

### A. Software-injected deterministic faults

Examples may include controlled timeout, synthetic NACK/error result, forced driver error, bounded simulated peripheral stall, or injected status condition.

These are valuable for deterministic host/firmware testing but must not be represented as equivalent to physical hardware faults.

### B. Physical/protocol fault injection

Only include fault mechanisms that can be safely and repeatably created with the selected hardware/testbed.

Do not propose unsafe electrical abuse.

Do not claim a physical fault mechanism until its hardware feasibility and safety are established.

## Fault record

Design a fixed-size, zero-heap fault record sufficient to support later recovery policy decisions.

Do not prematurely optimize the exact C packing.

Define semantics first, including likely fields such as:

- fault sequence/episode identity;
- timestamp or bounded timing representation;
- peripheral/resource identity;
- observed fault class;
- associated `EventRef` when justified;
- transaction ID when justified;
- service ID;
- association confidence;
- retry/history context;
- recurrence count;
- evidence flags;
- terminal/episode status.

Every field must justify why it is needed by a later decision or metric.

## Fault association

Explicitly define when association may be:

- exact event/transaction;
- service-level;
- peripheral-level;
- ambiguous/unknown.

For each level, define what evidence is required.

Do not infer event-level causality from peripheral equality alone.

If a peripheral has multiple queued events, determine when the evidence is strong enough to associate the failure with one event and when the policy must conservatively quarantine a broader scope.

## Fault episode

Define when a fault episode begins and ends.

Handle repeated observations of the same underlying fault without accidentally treating every status observation as a new independent episode.

The episode definition must later support bounded recovery-history reasoning.

## Required Gate B deliverable

Create a final repository artifact, preferably:

`research/phase1_gateB_fault_model_final.md`

It must include:

- scope and acceptance criteria;
- exact fault taxonomy;
- observable evidence for each fault class;
- software injection semantics;
- physical/protocol injection candidates and safety limits;
- fixed-size fault-record semantic model;
- association-confidence model;
- fault episode/repetition semantics;
- quarantine-scope implications;
- explicit rejected assumptions;
- unresolved questions transferred to Gate C;
- Gate B acceptance/rejection decision.

Do not delete the earlier `research/phase1_peripheral_testbed_fault_model.md`; preserve it as baseline/history and explicitly identify what was retained, refined, or rejected.

## GitHub checkpoint requirement

At the end of this chat:

1. update `research/phase1_gateB_fault_model_final.md`;
2. update `PROJECT_STATE.md`;
3. update `CURRENT_HANDOFF.md`;
4. update `DECISION_LOG.md`;
5. preserve all useful historical documents;
6. avoid unnecessary deletions or rewrites;
7. ensure `main` contains the complete checkpoint;
8. synchronize the active design branch with `main` if appropriate;
9. verify branch state before declaring the checkpoint complete.

Do not claim the checkpoint is complete until GitHub actually reflects it.

## CHAT B STOPPING RULE

**Stop after Gate B is fully checkpointed.**

Do not continue into Gate C in this chat merely because Gate B finished early.

The next chat should begin with:

**Gate C — Recovery Policy + Bounded State Machine**

The repository must contain the complete Gate B handoff so the next chat can reconstruct the project without depending on this conversation's history.

## Research honesty requirements

Throughout the project:

- no fabricated benchmarks;
- no fabricated physical measurements;
- no fabricated board availability;
- no unsupported novelty claims;
- no claim that a host simulation equals hardware validation;
- no claim that an established component is novel merely because it is combined with another component;
- report negative or inconclusive results honestly;
- keep the implementation minimal and directly tied to the research question.

Proceed from the repository checkpoint and begin **Gate B — Fault Model + Fault Association**.

---
