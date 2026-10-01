# Project State

Project: Embedded Systems — Missed Opportunities in Simpler Areas
Repository: SujitSaiY2007/embedded-runtime-resilience
Status: Part I complete; Part II K.4 active.
Active reference branch: exp
Stable integrated mirror: main

## Partition

### Part I — K.1-K.3 — COMPLETE
- K.1 — Host experiment verification
- K.2 — Corpus validation
- K.3 — Final host/reference synthesis

K.3 is the formal end of Part I.

### Part II — K.4 onward — ACTIVE

Current checkpoint:
K.4 — Novelty Re-Research + Conceptual Architecture Lock

Authoritative plan:
research/PART_II_CHAT_PLAN.md

## Branch state at K.4 entry

- exp: 1f3a471d2987b066ee995f4bf563fcdcbcd74d97
- main: e413a5986df9a486622bb4b34ef13ebc1e63ae80
- main is one merge commit ahead of exp.

The main-only merge contains the older integrated-software-phase interpretation of K.4. It is preserved for history but is not treated as a newer active research state. K.4 work is based strictly on exp.

## Frozen Gates A-E

Gates A-E remain closed and normative. K.4 does not modify event semantics, fault taxonomy/association semantics, the recovery ladder, formal properties, or the experimental protocol.

## K.4 novelty result

The broad novelty framing is not defensible after adversarial re-research.

Established or strongly overlapping prior art covers:
- peripheral recovery and isolation;
- recovery history;
- failed-event retention/quarantine;
- dependency-aware containment;
- selective rollback/preservation;
- runtime fault disambiguation and trace monitoring;
- static/zero-dynamic-allocation embedded execution.

The remaining research hypothesis is:

> There may be a technically meaningful distinction in implementing evidence-limited fault-to-event association together with retained event quarantine, dependency/order-aware preservation, and bounded history-conditioned recovery as one statically bounded mechanism for constrained event-driven MCU firmware.

Status: UNRESOLVED.

This is not a novelty or patentability conclusion.

Detailed evidence:
research/novelty_investigation.md

## K.4 conceptual architecture lock

Locked chain:

UI -> Virtual Embedded System -> SAME C Reference Runtime -> Recovery Decision -> Trace/Evidence -> UI

Authority:
- UI: presentation/scenario control only.
- Virtual system: deterministic environment/workload/peripheral/fault model only.
- C runtime: sole recovery-policy authority.
- Recovery Decision: observable C-runtime result, not a second component.
- Trace/Evidence: authoritative runtime-produced evidence consumed by UI.

Detailed boundary document:
research/part_ii_conceptual_architecture.md

## Documentation inconsistency identified

Historical material from the earlier integrated-software interpretation of K.4 remains in:
- research/chat_records/chat_k4_record.md
- research/phase1_software_demonstrator_methodology_lock.md
- older K.4 continuation sections in continuity documents.

These are preserved for provenance. The active scope is governed by research/PART_II_CHAT_PLAN.md and the Part-II scope override.

## Exact next checkpoint

K.5 — Virtual Embedded System Technical Design + Interface Contracts.

K.5 will define:
- virtual scheduler/environment contracts;
- I2C/SPI/UART model contracts;
- deterministic fault injection API;
- C-runtime adapter contract;
- UI-facing state/trace schema;
- baseline interface boundary.

K.5 must not implement these components and must not redesign the recovery policy.

## Persistent limitations

- P0-P3 are not clean quarantine ablations.
- W09/W10 are capacity-confounded.
- Host/reference evidence is not MCU/physical evidence.
- Host C-layout values are not STM32U575 measurements.
- Novelty/patentability are not established.
