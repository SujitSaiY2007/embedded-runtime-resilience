# Current Handoff

## Last completed step

Phase 0 research-space decomposition has been completed and recorded in `research/phase0_research_space_map.md`.

Twelve opportunity classes were mapped and six were shortlisted for systematic prior-art investigation.

## Current project status

We have **not finalized the invention/topic**.

Research direction:

> Missed Opportunities In Simpler Areas Of Embedded Systems

Current lead hypothesis:

> Lightweight Runtime Contract and Recovery Framework for Resource-Constrained Event-Driven Embedded Systems

The lead remains provisional. Phase 0 found substantial prior work around runtime verification, watchdogs, resource contracts, and local recovery, so the lead must be narrowed or rejected if evidence shows insufficient differentiation.

## Shortlist

1. OC-02 — Lightweight peripheral-failure recovery without full subsystem restart
2. OC-01 — Context-aware runtime contracts with bounded local recovery
3. OC-10 — Lightweight execution-time anomaly detection for MCU software
4. OC-11 — Self-verifying event pipelines
5. OC-06 — Localized software recovery / micro-restart for cooperative event-driven firmware
6. OC-03 — Event-burst containment for event-driven MCU software

## Next action

Build systematic evidence matrices for the six shortlisted classes, beginning with OC-02, OC-01, and OC-10.

For each candidate investigate:

- academic papers/proceedings;
- patents/patent families;
- standards/specifications;
- commercial/vendor solutions;
- open-source implementations;
- closest mechanisms;
- differentiating mechanism hypothesis;
- experimental baseline and fault model;
- novelty risk.

## Do not do yet

- Do not declare the topic novel.
- Do not write a patent claim.
- Do not publicly disclose detailed invention mechanics prematurely.
- Do not begin a large implementation before the research gap is established.
- Do not assume the current lead survives the prior-art stage.

## Important continuity note

The previous handoff described structured prior-art research as the next action. The present Phase 0 work inserted the necessary research-space decomposition step before candidate-specific prior-art analysis. The next chat should therefore continue with the evidence matrices rather than restart the mapping.

## Continuation instruction

When a new chat resumes this project, first read:

1. `PROJECT_MANUAL.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `DECISION_LOG.md`
5. latest research records

Then continue from the first unchecked phase gate without restarting the project.
