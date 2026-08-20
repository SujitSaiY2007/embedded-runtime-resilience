# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`
**Status:** Topic not yet finalized; research-space map completed; shortlisted candidates entering systematic prior-art investigation
**Project mode:** Solo software-based embedded-systems project
**Primary ambition:** Novel research-grade implementation with potential patent/publication value

## Current objective

Identify and validate a genuinely underexplored software-only embedded-systems problem arising from a missed opportunity in a comparatively simple area of embedded-system design.

## Current lead candidate

**Lightweight Runtime Contract and Recovery Framework for Resource-Constrained Event-Driven Embedded Systems**

Status: **lead hypothesis only**. It is not a confirmed gap, final topic, novelty claim, or patentability conclusion. Phase 0 mapping found substantial existing work in runtime verification, watchdogs, runtime resource assurance, and fine-grained recovery; the lead therefore requires narrowing and falsification.

## Non-negotiable principles

1. Do not claim novelty before systematic prior-art research.
2. Distinguish clearly between established facts, inference, hypotheses, and speculation.
3. Prefer a small, technically defensible core invention over feature-heavy complexity.
4. The final implementation must be reproducible and experimentally evaluable.
5. Maintain an auditable record of literature, patents, competing approaches, rejected ideas, design decisions, experiments, and evidence.
6. Protect potentially patent-relevant details from unnecessary public disclosure until an appropriate IP strategy is decided.
7. Every major project decision must be recoverable from this repository.

## Current phase

**Phase 0 — Topic Validation and Research-Space Decomposition**

### Phase gates

- [x] Repository continuity infrastructure established
- [x] Project requirements and constraints documented
- [x] Candidate problem space mapped
- [ ] Academic prior art systematically searched
- [ ] Patent prior art systematically searched
- [ ] Existing commercial/open-source solutions systematically assessed
- [ ] Explicit gap statement established
- [ ] Candidate architecture selected
- [ ] Novelty risk assessed
- [ ] Implementation feasibility assessed
- [ ] Experimental methodology defined
- [ ] Topic formally frozen

## Phase 0 research-space result

Twelve opportunity classes were mapped in `research/phase0_research_space_map.md`.

### Shortlist for next-stage investigation

1. **OC-02 — Lightweight peripheral-failure recovery without full subsystem restart**
2. **OC-01 — Context-aware runtime contracts with bounded local recovery**
3. **OC-10 — Lightweight execution-time anomaly detection for MCU software**
4. **OC-11 — Self-verifying event pipelines**
5. **OC-06 — Localized software recovery / micro-restart for cooperative event-driven firmware**
6. **OC-03 — Event-burst containment for event-driven MCU software**

The ordering is preliminary and reflects problem relevance, MCU implementability, baseline measurability, and apparent research depth—not proven novelty.

## Important Phase 0 finding

The broad phrase “missed opportunities in simpler areas” is a useful research direction but is not itself a research gap. Likewise, “runtime contracts + recovery” is not automatically novel. Runtime verification, watchdog/recovery, resource contracts, micro-recovery, power-loss recovery, overload management, and adaptive scheduling all have substantial prior work.

The emerging hypothesis is narrower: **small, explicit, event-driven resilience policies that connect fault detection to bounded local recovery or degradation under MCU resource constraints may contain useful underexplored intersections.** This remains a hypothesis requiring candidate-specific prior-art testing.

## Next exact task

Build an evidence matrix for the six shortlisted opportunity classes covering:

1. academic papers/proceedings;
2. patents/patent families;
3. standards/specifications;
4. commercial/vendor implementations;
5. open-source implementations;
6. closest competing mechanisms;
7. candidate differentiating mechanism;
8. experimental baseline;
9. fault model;
10. novelty-risk assessment.

Start with **OC-02, OC-01, and OC-10**, but reject or reorder them if stronger evidence emerges.

## Continuity rule

This file is the first recovery point for future chats. At the beginning of a continuation session, inspect this file together with `CURRENT_HANDOFF.md`, `DECISION_LOG.md`, and the latest research records before making substantive decisions.
