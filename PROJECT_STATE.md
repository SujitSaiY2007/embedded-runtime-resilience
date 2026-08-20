# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`
**Status:** Development topic frozen; implementation/design phase may proceed, while exact novelty remains evidence-dependent.
**Project mode:** Solo software-dominant embedded-systems project
**Primary ambition:** Research-grade implementation with publication potential and a possible patent pathway if supported by prior art and professional assessment.

## Frozen development topic

**Design and Implementation of a Lightweight Context-Aware Peripheral Recovery Policy for Resource-Constrained Event-Driven MCU Firmware**

This topic was selected after the Phase 0 research-space map and a focused deep prior-art attack. The freeze means this is the topic to develop; it does **not** mean novelty or patentability has been legally or academically proven.

## Research question

Can a compact software-only recovery policy, using observed peripheral fault context and recovery history, select bounded recovery actions and contain the affected service while preserving unrelated event-driven work, with lower service interruption and acceptable MCU overhead than fixed retry/reset strategies?

## Working contribution hypothesis

A deliberately small, deterministic recovery policy for cooperative/event-driven MCU firmware can use local fault context and short recovery history to choose among bounded recovery actions while explicitly preserving unrelated event-driven service. The mechanism should be evaluated against fixed retry/reset baselines.

Candidate recovery actions:

1. retry;
2. reinitialize;
3. peripheral reset;
4. controlled degradation/isolation;
5. escalation to system-level recovery.

Candidate context signals:

- fault type;
- timeout/error pattern;
- recurrence/history;
- peripheral/service criticality;
- pending event workload;
- previous recovery outcome.

The exact policy formulation remains a design variable.

## Deep prior-art attack conclusion

The attack established that the following are **not** valid novelty claims by themselves:

- peripheral fault recovery;
- selective peripheral restart;
- context-aware recovery;
- recovery state machines;
- retry/reinitialize/reset/degrade actions;
- event-driven resilience;
- graceful degradation.

Particularly important prior art includes Phoenix (peripheral rollback/recovery on resource-constrained embedded systems), Karma (asynchronous peripheral operation recovery/state handling), OS/device-driver recovery research, context-aware embedded health management, extensive graceful-degradation work, and recent patent activity around selective peripheral recovery and isolation.

The surviving research hypothesis is narrower: a software-only, deterministic, MCU-scale policy that combines local fault context/history with bounded recovery selection and explicit preservation of unrelated event-driven service.

This exact combination was not identified as an obvious one-to-one match during the focused search, but absence of an obvious match is **not proof of novelty**.

## Course-guideline fit

The supplied course guideline requires a real-world problem, literature and existing-solution review, a technical gap, embedded implementation, algorithm/software contribution, quantitative experimental validation, comparison with a reference method, and research/patent preparation. The selected topic supports all of these elements. The guideline also explicitly rejects projects that merely demonstrate functionality without measurable evaluation.

## Planned baseline and evaluation

Baseline A: fixed retry.

Baseline B: fixed retry + peripheral reset/reinitialize.

Where relevant, baseline C: vendor/protocol-standard recovery.

Primary metrics:

- fault detection latency;
- recovery latency;
- recovery success rate;
- unnecessary whole-system resets;
- unrelated-service interruption time;
- lost transactions/events;
- duplicate transactions/events;
- event-queue disruption;
- CPU overhead;
- RAM/Flash overhead;
- energy impact where practical.

Fault injection must be reproducible and cover selected timeout, stuck/bus-error, and peripheral-state fault scenarios appropriate to the selected MCU/peripheral set.

## Scope boundary

Initial implementation: one MCU family, limited peripheral interfaces, bounded fault classes, deterministic cooperative/event-driven firmware. No requirement for cross-platform generality in the first prototype.

The exact MCU board, peripherals, fault-injection apparatus, recovery-state machine, and benchmark suite are the next design decisions.

## Phase status

**Phase 0 — Topic Validation / Development Topic Selection: COMPLETE**

- [x] Repository continuity infrastructure established
- [x] Project requirements and constraints documented
- [x] Research-space decomposed
- [x] Candidate shortlist created
- [x] Deep academic prior-art attack performed
- [x] Patent prior-art attack performed
- [x] Commercial/vendor evidence considered
- [x] Broad runtime-contract framing rejected as too broad
- [x] Development topic frozen

**Next phase — Design and Experimental Planning:**

- [ ] Formal contribution definition
- [ ] Exact architecture
- [ ] MCU/peripheral testbed selection
- [ ] Fault model and injection apparatus
- [ ] Baseline implementation design
- [ ] Recovery-policy design
- [ ] Experimental protocol
- [ ] Reproducibility plan
- [ ] Final patent-sensitive disclosure boundary

## Falsification rule

If a later exact-mechanism search finds close prior art that materially discloses the same software-only architecture and policy, or if experiments show no meaningful advantage after accounting for overhead, the mechanism must be narrowed, redesigned, merged with another opportunity, or rejected.

## Canonical research record

See `research/deep_prior_art_attack_topic_freeze.md` for the detailed prior-art attack and reasoning.
