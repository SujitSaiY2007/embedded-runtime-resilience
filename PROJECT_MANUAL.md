# Project Manual

## 1. Purpose

This repository is the canonical working record for a solo, software-dominant embedded-systems research project focused on **missed opportunities in simpler areas of embedded systems**.

The frozen development topic is:

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short working title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**.

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

The project therefore requires an actual MPU-capable MCU development board for final physical validation of MPU behavior, interrupt timing, peripheral behavior, resource footprint, and hardware-relevant faults. No physical board is currently assumed to be available; board selection/acquisition is a Phase 1 prerequisite.

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

`topic freeze -> architecture -> MCU/testbed -> fault model -> policy -> invariants -> baselines -> prototype -> experiment -> evaluation`

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

- exact mechanism defined;
- hardware/testbed feasible;
- credible fault model;
- reproducible baseline;
- measurable technical contribution;
- reproducible evaluation;
- no unsupported novelty claims;
- publication-quality evidence;
- patent-sensitive details handled deliberately.

## 10. Patent disclaimer

A project being described as “potentially patentable” is not a legal conclusion. Patentability depends on jurisdiction, claim construction, prior art, disclosure timing, inventorship, and professional legal assessment.
