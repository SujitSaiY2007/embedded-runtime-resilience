# Chat 03 — Source-to-Design Traceability

**Audit date:** 2026-10-20  
**Repository:** [SujitSaiY2007/embedded-runtime-resilience](https://github.com/SujitSaiY2007/embedded-runtime-resilience)  
**Control branch:** `main` only  
**Starting live `main` SHA:** `e71e8243a66200836d6c9069600d64e1838df7a7`  
**Scope:** Evidence mapping only. No manuscript or bibliography edits; no runtime, tests, gates, prior-art reports, or frozen experiment artifacts changed.

## 1. Executive finding

The repository demonstrates a bounded C11 **host/reference model** for event admission, explicit dependency semantics, fault association, quarantine, recovery decisions, and trace generation. Its design contracts and executable code support an engineering hypothesis about preserving valid unrelated work while containing an affected event. The frozen K.10 report records localized advantages for P4 in CF04 and CF07, but also no measured advantage in six case families and a cost trade-off in CF16.

The inspected sources do **not** establish that any particular source directly caused the design. The clearest evidence-backed source relationships are **comparison/prior-art context** (not direct adoption), particularly Phoenix (P-001), Karma (P-002), driver recovery (P-003), microreboot (P-004), failed-event/patent families (P-009–P-017), and static event-pool documentation (P-008/A-023). The K.10.3 review explicitly treats Phoenix + failed-event queue + QP/C as a credible combination attack. The narrow integrated distinction remains a **research hypothesis**, not a novelty, legal obviousness, or patentability conclusion.

## 2. Method and evidence hierarchy

Evidence was checked in this order:

1. Actual implementation and tests in `reference/`.
2. Normative design contracts: `research/phase1_gateA_event_model_final.md` through Gate E and `research/phase1_reference_implementation_design.md`.
3. Frozen experiment implementation and saved interpretation: `reference/experiments/k10_experiment.c`, `reference/experiments/evaluate_k10_advantage.py`, and `research/phase2_k10_p4_advantage_novelty_results.md`.
4. Existing prior-art analyses: `research/phase2_k10_1_adversarial_distinction_review.md`, `research/phase2_k10_2_single_reference_anticipation_review.md`, `research/phase2_k10_3_multi_reference_combination_review.md`, and `research/phase2_k10_4_final_technical_distinction_and_research_conclusion.md`.
5. Chat 02's metadata register and verification notes. Metadata verification is not treated as full-text inspection.

Relationship classes used here:
- **Direct adoption:** explicit evidence that a source-defined method is implemented.
- **Adaptation:** explicit evidence that a source method was materially modified.
- **Conceptual context:** supports problem framing, not proven implementation influence.
- **Comparison:** prior-art, baseline, or competing approach considered in analysis.
- **No demonstrated influence:** inspected evidence does not connect the source to a design decision.
- **Unresolved:** source identity or source-to-design evidence is insufficient.

A citation, thematic similarity, or shared vocabulary alone is not evidence of direct adoption. The project documentation does not provide dated design notes that establish a direct derivation from the candidate sources. Accordingly, no source is classified as direct adoption on the evidence inspected in this pass.

## 3. Implementation-side anchors

| Project artifact | Observed mechanism or claim | What it establishes | Boundary |
|---|---|---|---|
| `reference/include/ref_runtime.h` | `QMAX=16`, `XMAX=4`, `DMAX=4`, `ACTIVE_MAX=20`; fixed-width event identity; dependency, fault, action, outcome, policy enums | Static bounded reference-model data structures and explicit policy vocabulary | Header contract does not prove MCU RAM/Flash/timing costs |
| `reference/src/ref_runtime.c` | `EventRef={slot_id,generation}`; stale-reference checks; bounded slot allocation; trace records; lifecycle and policy routines | Executable host implementation of the documented model | Must not be represented as MCU firmware validation |
| `reference/tests/test_reference.c` | W01 independent-work preservation; W02 ordered blocking; W03 coupled containment, plus other runtime assertions | Deterministic host tests exercise selected semantic properties | Test presence is not a record of tests run during this audit; not exhaustive proof |
| `research/phase1_gateA_event_model_final.md` | Explicit INDEPENDENT / ORDERED / COUPLED dependency classes; peripheral equality alone is insufficient | Normative event/dependency contract | Design-level contract alone is not implementation evidence |
| `research/phase1_gateB_fault_model_final.md` | Fault taxonomy, association levels and evidence-precision constraint | Normative fault-observation and association model | Does not prove physical cause inference or physical sensor/driver behavior |
| `research/phase1_gateC_recovery_policy_final.md` | Finite policy, action preconditions/effects, history and terminal handling | Normative bounded-policy contract | Design acceptance is not physical validation |
| `research/phase1_gateD_formal_properties_final.md` | Safety, termination, identity, boundedness and proof/check strategy | Explicit verification obligations | Does not claim full formal verification of firmware |
| `research/phase1_gateE_experimental_protocol_final.md` | Matched P0–P4 design, dependent variables and evidence limits | Planned experimental protocol and limitations | It explicitly disclaims MCU results, statistical significance, novelty and patentability |
| `reference/experiments/k10_experiment.c` | 16 families, five variants, five repetitions; run and trace CSV generation | Frozen host experiment harness structure | This audit did not execute it |
| `reference/experiments/evaluate_k10_advantage.py` | Expects 400 runs; derives comparison metrics | Analysis implementation for frozen host corpus | Running it can execute/recompute the campaign; deliberately not run |
| `research/phase2_k10_p4_advantage_novelty_results.md` | Records CF04/CF07 advantages, six no-advantage families and CF16 trade-off | Saved host-model interpretation | Reported result is not independent MCU evidence |
| `research/phase2_k10_3_multi_reference_combination_review.md` | Phoenix + IBM failed-event queue + QP/C is a credible combination attack | Prior-art risk already identified by project | Not a legal opinion; does not establish legal obviousness |
| `Plan2.0/HARDWARE_DEMONSTRATION.md` | Board decision, safe fault injection, fresh post-recovery transaction and raw evidence requirements | Hardware acceptance plan | No physical demonstration is evidenced by this plan alone |

## 4. Source-to-design matrix — all 43 inventory IDs accounted for

**Important:** “Comparison” means a source is relevant to the prior-art/comparator analysis; it does not assert that it was a measured experimental baseline or that code was copied. “Metadata verified” refers to Chat 02's identity status, not full-text verification.

| ID | Chat 02 identity status | Defensible relationship to current project | Evidence / limitation |
|---|---|---|---|
| P-001 — Phoenix, *Surviving Peripheral Failures in Embedded Systems* | Verified metadata | **Comparison** | K.10.1–K.10.3 identify Phoenix as close embedded peripheral-recovery prior art; rollback/checkpointing differs from retained in-pool event quarantine. Project records identify paper inspection in prior work, but exact passage/page mapping was not re-audited here. |
| P-002 — Karma, *Intermittent Asynchronous Peripheral Operations* | Partial | **Comparison** | K.10.3 discusses dependency-aware peripheral replay/rollback as adjacent teaching. Primary ACM DOI/pages remain open; author-hosted PDF/institutional record does not close all metadata questions. |
| P-003 — *Recovering Device Drivers* | Verified metadata | **Comparison** | K.10 prior-art analysis uses driver fault containment as adjacent precedent; OS-level shadow-driver design is not proof of bare-metal implementation influence. |
| P-004 — *Microreboot—A Technique for Cheap Recovery* | Verified metadata | **Comparison** | K.10 prior-art analysis treats fine-grained component recovery as established background; domain differs from the static event-slot model. |
| P-005 — *Runtime verification of embedded real-time systems* | Verified metadata | **Conceptual context** | Monitoring/verification is relevant to the evidence and property framing; no implementation derivation is documented. |
| P-006 — Robonaut2 runtime verification for fault disambiguation | Verified metadata | **Conceptual context / comparison** | Relevant to constrained fault disambiguation; no documented method transfer into the runtime. |
| P-007 — *Preventing Interrupt Overload* | Partial | **Conceptual context** | Interrupt overload is an adjacent fault class, but the current frozen model is not an interrupt-overload experiment; primary publisher metadata gap remains. |
| P-008 — QP/C QMPool class reference | Verified metadata | **Comparison** | K.10.3 compares static supplied pool storage with the project's fixed EventSlot lifecycle; QMPool allocation/recycling is not equivalent to the same-slot quarantine invariant. |
| P-009 — peripheral bus error containment/recovery patent | Partial | **Comparison** | Patent family is retained in K.10 prior-art scope; exact claims and official-source completeness require caution. |
| P-010 — recovery after I/O error-containment events patent | Partial | **Comparison** | Adjacent error containment/recovery; no direct adoption established. |
| P-011 — multimaster serial single-ended system fault recovery patent | Partial | **Comparison** | Bus-level fault recovery comparator; not evidence of the event/dependency mechanism. |
| P-012 — BAS/HVAC control-device recovery patent | Partial | **Comparison** | Domain-specific automatic recovery comparator; transferability and exact claims require further inspection. |
| P-013 — event failure management patent | Partial | **Comparison** | Relevant to failed-event handling; K.10.3 combination analysis identifies enterprise failed-event queue concepts as adjacent teaching. |
| P-014 — application-server failed-event processing patent | Partial | **Comparison** | Failed-event retention/replay comparator; application-server domain differs from zero-heap MCU constraints. |
| P-015 — I²C status monitoring/fault recovery/isolation patent | Partial | **Comparison** | Closest bus-specific comparator; official claims/source verification remains incomplete. |
| P-016 — data-processing-system peripheral management/recovery patent | Partial | **Comparison** | Peripheral management/recovery comparator; exact claim-to-feature map remains open. |
| P-017 — management/recovery of data-processing-system peripherals patent | Partial | **Comparison** | Related patent comparator; do not infer legal family/claim scope beyond audited evidence. |
| A-001 — RTLola monitoring system, exact publication unresolved | Partial / unresolved identity | **Unresolved** | Source identity/version and exact paper are not pinned; no source-to-design mapping justified. |
| A-002 — past-time temporal monitoring/contracts | Unresolved | **Unresolved** | Broad strand, not one identified source; cannot be cited as a specific publication. |
| A-003 — watchdogs/trusted recovery | Unresolved | **Unresolved** | No exact source identified; no defensible mapping. |
| A-004 — micro-recovery/scheduling beyond P-004 | Unresolved | **Unresolved** | Broad research strand; must not be counted as an additional verified paper. |
| A-005 — MSP-FRAM-UTILITIES CTPL | Verified metadata | **Conceptual context / no demonstrated influence** | Official utility documentation is relevant to persistence after power loss, but not the current event-level peripheral quarantine mechanism. No direct use is documented. |
| A-006 — MSP-FRAM-UTILITIES NVS | Verified metadata | **Conceptual context / no demonstrated influence** | Persistent storage context; no direct use in the in-memory recovery policy demonstrated. |
| A-007 — event-driven workload scaling/interrupt overload | Unresolved | **Unresolved** | No exact publication or project artifact linkage. |
| A-008 — FSM-based adaptive sampling | Unresolved | **Unresolved** | No exact source; adaptive sampling is not established as an implemented mechanism here. |
| A-009 — ML-based adaptive sensing/scheduling | Unresolved | **Unresolved** | No exact source; no ML mechanism in the inspected reference runtime. |
| A-010 — automatic CAN bus-off recovery | Unresolved | **Unresolved** | No exact source and CAN is not a demonstrated K.10 hardware interface. |
| A-011 — AUTOSAR fault/event/driver mechanisms | Unresolved | **Unresolved** | No exact AUTOSAR document/release pinned; no implementation mapping established. |
| A-012 — Zephyr driver-model documentation | Partial / release not pinned | **Conceptual context / comparison** | Official documentation family can contextualize driver lifecycle; exact version/section not pinned and no adoption demonstrated. |
| A-013 — FreeRTOS queue documentation | Partial / release not pinned | **Conceptual context / comparison** | Queue concepts are contextual; no claim that P0–P4 reproduce FreeRTOS behavior. |
| A-014 — NuttX driver/event mechanisms | Unresolved | **Unresolved** | Exact source/release not identified. |
| A-015 — *Failure Resilience for Device Drivers* | Partial | **Comparison** | Adjacent driver recovery; source identity is not sufficiently complete for detailed claim mapping. |
| A-016 — *Falkirk Wheel: Rollback Recovery for Dataflow Systems* | Verified identity | **Comparison** | Rollback recovery is an adjacent systems comparator; dataflow system is not the project's MCU runtime. |
| A-017 — “Fault-Tolerant Service Robots” (Ahn et al., 2013) | Unresolved | **Unresolved** | Exact identity not established; do not quote or cite as verified. |
| A-018 — historical “Fault recovery of peripheral I/O lines” patent lead | Unresolved | **Unresolved** | Official patent identity/claims not established; no legal conclusion permitted. |
| A-019 — 2015 interrupt-overload study | Unresolved | **Unresolved** | No exact paper identity. |
| A-020 — 2017 IEEE MECO execution-time-monitoring paper | Unresolved | **Unresolved** | No exact paper identity/pages/DOI confirmed. |
| A-021 — NXP S32 Safety Software Framework | Unresolved exact document/version | **Unresolved** | Official framework source/version not pinned. |
| A-022 — R2U2 runtime-verification project | Partial / exact paper unresolved | **Conceptual context / unresolved** | Project identity is a lead; exact publication/release and relevance to this mechanism remain open. |
| A-023 — QP/C QF framework documentation | Partial / release not pinned | **Comparison / conceptual context** | Event-driven framework context; QF/QMPool are not equivalent to the project's recovery semantics. |
| A-024 — microfsm framework | Unresolved | **Unresolved** | Canonical project identity not established. |
| A-025 — Nooks/MINIX 3/OS driver-recovery literature | Unresolved umbrella lead | **Unresolved** | Multiple systems are grouped under a broad lead; must be separated into exact sources before detailed comparison. |
| A-026 — safety-critical/aerospace/historical embedded recovery | Unresolved umbrella lead | **Unresolved** | Broad direction, not a citable work or comprehensive survey. |

### Matrix counts and definitions

- **Mapped (comparison/context): 25** — 17 P-series entries plus A-005, A-006, A-012, A-013, A-015, A-016, A-022, A-023, with A-001's identity limitation kept visible; these are provisional topical mappings, not 26 demonstrated influence claims.
- **Partially mapped: 0 as a separate exclusive count** — partial metadata is reported in the status column; the evidence is not strong enough to promote a mapping where the table says unresolved.
- **Relationship unresolved: 18** — A-001 plus A-002, A-003, A-004, A-007–A-011, A-014, A-017–A-021, A-024–A-026. A-022 has a provisional topical mapping but its exact paper/release remains unresolved.
- **Direct adoption: 0; adaptation: 0** — no auditable source-to-code derivation was established in this pass.
- **No demonstrated influence: explicitly noted for A-005/A-006; not asserted for every unresolved source.**

The counts above describe the mapping status, not the number of papers read. Because “mapped” can otherwise be mistaken for proven influence, the matrix is the authoritative detail and no mapped row should be described as direct adoption.

## 5. Baselines and ablations — source attribution boundary

The header and frozen K.10 artifacts identify P0–P4 as project policy variants:
- P0 fixed retry
- P1 fixed retry + reset/recovery
- P2 context only
- P3 context + history
- P4 integrated proposal

The inspected evidence does not establish that P0–P4 are faithful reproductions of Phoenix, Karma, a patent, QP/C, FreeRTOS, Zephyr, or another named system. Treat them as **internal matched baselines/ablations**, not published-system replications. Gate E says the controlled comparison is intended to isolate context, history, association, dependency, and integrated policy effects.

## 6. Unresolved source-to-design mappings

1. For every candidate source, locate the exact full-text passage, section, page, algorithm, or patent claim before using it to support a precise mechanism claim.
2. Complete official ACM metadata checks for P-002 and P-007 and official patent-record/claim checks for the relevant P-series patent records.
3. Pin exact versions and sections for Zephyr, FreeRTOS, QP/C, RTLola, R2U2, and NXP documentation.
4. Split broad A-series strands into exact publications or mark them excluded from manuscript citation.
5. Record provenance for any source that actually influenced a design choice. If no dated record or explicit correspondence exists, retain “no demonstrated influence.”
6. Reconcile any new full-text findings with K.10.1–K.10.4 without rewriting those historical records in this chat.

## 7. Evidence boundary

This report distinguishes (a) code present in the repository, (b) tests present in the repository, (c) saved host experiment outputs and interpretations, and (d) physical hardware evidence. Only the first three categories are represented in the inspected artifacts. No hardware behavior, MCU timing, MCU memory footprint, energy result, or physical fault-recovery success is established here.

**Bottom line:** The repository's mechanism is traceable to explicit project contracts and executable host code. Its relation to prior art is currently best described as comparative and conceptual, not proven direct adoption. The evidence supports a narrow engineering question and a credible multi-reference challenge; it does not establish comprehensive novelty or legal conclusions.
