# Project Manual

## 1. Purpose

This repository is the canonical working record for a solo, software-dominant embedded-systems research project focused on **missed opportunities in simpler areas of embedded systems**.

The frozen development topic is:

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short working title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**.

**Current status:** Phase 1E.1 — Experimental Design / Formalization Foundation. Gates A, B, C, and D are accepted at the semantic/design-model level. Gate E — Baselines + Experimental Protocol — is next. Large-scale firmware implementation and physical validation remain deferred.

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
- **Gate E:** Baselines + experimental protocol — NEXT

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
- reproducible baseline — Gate E pending;
- measurable technical contribution — experimental evidence pending;
- reproducible evaluation — Gate E and later experiments pending;
- no unsupported novelty claims — required throughout;
- publication-quality evidence — later-stage objective;
- patent-sensitive details handled deliberately — required throughout.

## 10. Patent disclaimer

A project being described as “potentially patentable” is not a legal conclusion. Patentability depends on jurisdiction, claim construction, prior art, disclosure timing, inventorship, and professional legal assessment.
