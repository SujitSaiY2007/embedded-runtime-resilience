# Project Manual

## 1. Purpose

This repository is the canonical working record for a solo, software-dominant embedded-systems research project focused on **missed opportunities in simpler areas of embedded systems**.

The frozen development topic is:

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short working title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**.

**Current status:** **K.10 COMPLETE; post-K.10 adversarial technical-distinction review ACTIVE.** Part I and K.4-K.10 are complete. The active sequence is K.10.1 -> K.10.2 -> K.10.3 -> K.10.4 -> K.11 -> K.12. Gates A-E remain frozen and normative. The current research objective is to attack the remaining technical distinction against prior art before final synthesis.

The intended outcome is not merely a functioning application. The target is a technically defensible research contribution that may support an academic publication and, if the evidence warrants it, a patent filing.

## 2. Research philosophy

The project begins with evidence and falsifiable hypotheses, not unsupported invention claims.

Even after topic freeze, the exact mechanism must be challenged by:

- peer-reviewed papers;
- conference proceedings;
- theses and technical reports;
- patents and patent applications;
- standards and specifications;
- commercial products;
- open-source implementations;
- archived documentation and historical solutions where relevant.

A feature being uncommon is not sufficient evidence of novelty.

## 3. Frozen scope

The project is software-dominant but targets real MCU firmware validation.

Core constraints/mechanisms:

1. **Zero-heap:** recovery manager and reference firmware use statically allocated state/queues/policy tables; no runtime dynamic allocation.
2. **Context-aware recovery:** recovery action selection can use local fault context and short recovery history.
3. **Bounded recovery:** candidate actions are finite and recovery transitions are bounded.
4. **Event quarantine:** a fault-associated event/transaction can be isolated without indiscriminately flushing unrelated valid queued work, subject to dependency/ordering rules.
5. **MPU-enabled target:** MPU support is used for containment/isolation where practical; MPU technology itself is not claimed as novel.
6. **Event-driven firmware:** the reference architecture is cooperative/event-driven and resource constrained rather than dependent on a heavyweight general-purpose OS.

Formal reasoning will focus on tractable queue/recovery invariants rather than claiming full formal verification of the firmware.

## 4. Hardware boundary

A laptop/PC is sufficient for development, simulation, host-side fault modelling, formal reasoning, and analysis. It is **not sufficient for the strongest final embedded validation claims**.

The current platform direction is **STM32U575ZI / NUCLEO-U575ZI-Q**, with I2C as the primary interface, SPI as a secondary interface, and UART/USART as the initial diagnostic/control path. Physical acquisition remains a factual checkpoint; no physical measurements are claimed until actual hardware is acquired and executed.

The project therefore requires an actual MPU-capable MCU development board for final physical validation of MPU behavior, interrupt timing, peripheral behavior, resource footprint, and hardware-relevant faults.

## 5. Research contribution discipline

Do not claim that any individual ingredient is novel:

- zero-heap/static allocation;
- MPU isolation;
- peripheral recovery;
- event queues;
- event quarantine;
- context-aware recovery;
- retry/reset/reinitialization/degradation;
- formal invariants.

The research hypothesis concerns the **specific integrated mechanism and measurable trade-off**: whether a compact deterministic zero-heap recovery policy using local fault context/history and event quarantine can reduce collateral service disruption on a constrained event-driven MCU.

## 6. Development model

Use controlled, traceable increments:

`research -> hypothesis -> falsification -> design -> prototype -> experiment -> evaluation -> revision`

For the current frozen topic:

`topic freeze -> architecture -> MCU/testbed -> fault model -> policy -> invariants -> experimental protocol -> prototype -> experiment -> evaluation`

Current design-gate progression:

- **Gate A:** Event model + dependency semantics — COMPLETE
- **Gate B:** Fault model + fault association — COMPLETE
- **Gate C:** Recovery policy + bounded state machine — COMPLETE
- **Gate D:** Formal properties + proof/check strategy — COMPLETE
- **Gate E:** Baselines + experimental protocol — COMPLETE

Avoid premature implementation. Code should follow a defined architecture and evaluation protocol.

## 7. Git workflow

Recommended branch classes:

- `research/<topic>` — research exploration
- `design/<component>` — architecture/design work
- `feature/<component>` — implementation
- `experiment/<name>` — reproducible experiments
- `docs/<area>` — documentation

The `main` branch should represent the most defensible integrated state.

Use focused commits with messages that describe the actual change.

## 8. Continuity protocol

Every major session should update:

- `PROJECT_STATE.md` — current state and gates;
- `CURRENT_HANDOFF.md` — exact continuation point;
- `DECISION_LOG.md` — consequential decisions and rejected alternatives;
- research records — new evidence and source assessments.

A future chat must be able to reconstruct the project from these files without relying on old conversation history.

Before substantive work, a future chat must read, in order:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. relevant files under `research/`

## 9. Quality gates

The topic is frozen, but development must still pass these gates:

- exact mechanism defined — Gates A–D complete;
- hardware/testbed feasible — platform direction selected; acquisition/physical validation pending;
- credible fault model — Gate B complete at the semantic/design level;
- reproducible baseline — Gate E frozen; host verification complete;
- measurable technical contribution — hardware/empirical evidence still pending;
- reproducible evaluation — host layer complete; target-MCU evaluation pending;
- no unsupported novelty claims — required throughout;
- publication-quality evidence — later-stage objective;
- patent-sensitive details handled deliberately — required throughout.

## 10. Patent disclaimer

A project being described as “potentially patentable” is not a legal conclusion. Patentability depends on jurisdiction, claim construction, prior art, disclosure timing, inventorship, and professional legal assessment.

## 2026-10-01 Operational Continuity Checkpoint — Chat K.1/K.2

The host/reference experiment checkpoint has now been executed and verified.

**Chat K.1 result:** the matched P0-P4 host harness builds under Windows/MSVC; CTest passes 2/2; the host experiment check passes all deterministic-replay, matched-input, raw-input, capacity-confound, and ablation-contract checks; 14 workloads × 5 variants produce 70 matched runs during verification.

**Current limitations:** W09/W10 are capacity-confounded; P0-P3 are not clean quarantine ablations because exact-event quarantine is currently shared across all variants. Neither limitation is hidden or silently redefined.

**Chat K.2 boundary:** regenerate and inspect the actual host corpus and validate trace/outcome semantics against Gate E. Do not infer policy-level evidence from harness-level PASS alone. Do not start MCU integration or physical validation during this checkpoint.


## 11. Software Proof-of-Concept and Methodology Lock

The professor-facing verification activity is part of the integrated software phase, not a separate gate. The objective is to demonstrate the complete mechanism in software, re-verify the methodology, lock the evidence boundaries, and present a defensible conclusion for proceeding to target-MCU validation.

Authoritative checkpoint: `research/phase1_software_demonstrator_methodology_lock.md`.

The demonstrator must make visible: fault observation, evidence-bounded association, event quarantine, bounded context/history-aware recovery, verification/release or terminal handling, and traceable explanation. It must not introduce a second competing research specification.

## 12. Novelty discipline at the software checkpoint

The project may showcase its **integrated novelty hypothesis** and explain why the combination is worth hardware testing. It must not state that novelty or patentability has already been proven. Individual ingredients remain established concepts. Final novelty assessment depends on the complete prior-art record and the eventual demonstrated implementation/claims.

The software-phase conclusion is that the mechanism is sufficiently specified, implemented, reproducible, and evidence-bounded to justify target-MCU validation. It is not a claim of hardware performance or final patentability.

## 13. Two-Part Project Structure

### Part I — K-Series Host/Reference Foundation — COMPLETE
Part I consists of K.1, K.2 and K.3. K.3 closes Part I as the final host/reference evidence-bounded synthesis checkpoint.

### Part II — Software Demonstrator + Novelty Investigation + Methodology Lock — ACTIVE
Part II begins at K.4. It combines novelty re-investigation, virtual embedded-system construction, UI demonstrator, matched software comparison, complete software re-verification, methodology lock and professor-facing proof of concept.

Professor review is the intended use of this integrated Part-II work, not a separate gate.

The authoritative architecture is:
UI -> Virtual Embedded System -> C Reference Runtime -> Recovery Decision -> Trace -> UI

## 14. Strict Multi-Chat Scope
The active checkpoint plan is maintained in research/PART_II_CHAT_PLAN.md. Every chat has a fixed objective, allowed work, explicit out-of-scope work, required outputs and an exact next-chat handoff. A chat may not execute a later checkpoint simply because it becomes convenient.

## 15. Branch Governance — exp Reference, main Integrated Mirror
exp is the canonical active research/reference branch for Part II. All experimental and implementation progress must be based on the latest exp state.

main is the canonical integrated/stable branch. It must track completed exp checkpoints through explicit pull requests/merges. No direct Part-II development is performed on main.

Every PR from exp to main must identify the source exp commit, checkpoint/chat identifier, files changed, validation, known limitations and whether the merge closes a Part-II checkpoint.

## 16. Continuity Requirement Per Chat
At the beginning of every chat read PROJECT_MANUAL.md, PROJECT_STATE.md, CURRENT_HANDOFF.md, DECISION_LOG.md, research/PART_II_CHAT_PLAN.md and the latest relevant Part-II chat record. Then state a Continuity Check containing current Part, checkpoint, exp reference, completed prior checkpoints, exact scope and explicit out-of-scope work.

At the end of every chat update PROJECT_STATE.md, CURRENT_HANDOFF.md, DECISION_LOG.md when needed, the chat record and next-chat prompt. Verify branch relationship and whether main has been synchronized.

## 17. Novelty Investigation Protocol
The project may pursue a novelty hypothesis, but novelty is not assumed. Prior art must be checked across papers, patents, standards, commercial implementations and open-source implementations.

Current search evidence already shows established prior art for peripheral recovery, checkpoint-based recovery, selective recovery, fault containment and policy-driven recovery. Therefore the novelty question is the narrower integrated mechanism: evidence-bounded fault association plus bounded context/history recovery plus event-level quarantine/dependency preservation under a deterministic zero-heap event-driven MCU model.

No chat may convert this hypothesis into established novelty or patentability without documented technical prior-art analysis and, for patentability, professional legal assessment.


## 2026-10-01 Operational Checkpoint — K.5

Part I K.1-K.3 is COMPLETE. Part II K.4 is COMPLETE and K.5 is COMPLETE at technical-design/contract level.

K.5 defined the virtual embedded-system boundary around the actual existing ISO C11 reference runtime, including deterministic scheduler/environment semantics, I2C/SPI/UART contracts, deterministic fault injection, runtime adapter inputs/outputs, ownership/lifetime, trace/evidence correlation and deterministic scenarios.

The current C runtime remains the sole recovery-policy authority. K.5 identified but did not modify the runtime limitation that there is no peripheral-action callback. Future implementation must not silently add one or otherwise redesign recovery semantics.

Current active checkpoint: K.6 — Virtual Embedded System Implementation around the existing C runtime.


## 13. Canonical post-K.10 execution governance — 2026-10-02

The active checkpoint sequence is maintained exclusively in `research/PART_II_CHAT_PLAN.md`. Conflicting earlier roadmap wording is historical/superseded and must not be used as an active instruction.

### Chat ownership
ChatGPT owns the sequence and checkpoint boundaries. Antigravity is a repository execution agent only within the currently authorized ChatGPT checkpoint. Antigravity must not create, renumber, or advance the chat sequence.

### Post-K.10 sequence
1. K.10.1 — adversarial prior-art + feature/limitation distinction review.
2. K.10.2 — deep single-reference anticipation review.
3. K.10.3 — multi-reference combination / technical obviousness analysis.
4. K.10.4 — final technical distinction + evidence-bounded research conclusion.
5. K.11 — final software synthesis + target-MCU validation handoff.
6. K.12 — final software productization + clean professor-facing UI demonstration.
7. Final `exp` audit followed by synchronization to `main`.

### Branch governance
`exp` is the active research/integration branch. `main` is the integrated mirror and is synchronized only after validated checkpoint closure through the normal PR/merge path. Historical child branches remain provenance records and are not active roadmap authorities.

### Continuity rule
Every checkpoint must close with exact branch/SHA state, changed files, validation, unresolved items, explicit scope boundary, and a complete next-ChatGPT continuation prompt in `NEXT_CHAT_PROMPT.md`.

### Research boundary
K.10 established bounded experimental evidence, not universal superiority. The post-K.10 review may strengthen or weaken the technical-distinction assessment but must not rewrite evidence to obtain a preferred result. Legal patentability remains outside the project's authority and requires professional review.
