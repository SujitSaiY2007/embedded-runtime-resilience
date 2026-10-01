# K.9.2 — P4 Advantage & Novelty Investigation Design Lock

Date: 2026-10-01
Status: ACTIVE — design/decision checkpoint; no decisive advantage experiment or new prior-art conclusion is executed by this document.
Canonical base: `exp @ 72edc4f86986c868b2e7102c192441d069c6dba7`

## 1. Purpose

K.9.2 exists between K.9 methodology lock and K.10. Its purpose is to prevent the project from moving directly to a final conclusion before systematically testing where, if anywhere, P4 has a meaningful measurable advantage and before completing the planned combination-level novelty investigation.

K.9.2 is a **research-design lock**, not a predetermined claim that P4 is superior or novel.

The next chat executes K.9.2 only. The following chat executes K.10 using this locked design.

## 2. Research question

Do not ask only:

> Does P4 have the highest success rate?

Ask instead:

> Under which defined fault, workload, history, dependency, resource-pressure, and compound-condition combinations does P4 differ meaningfully from P0-P3, and are those differences beneficial, neutral, or costly across defensible software-level metrics?

A P4 advantage may be absent. A trade-off may be the correct result. Success-rate superiority is neither required nor assumed.

## 3. P4 Advantage Matrix

The K.10 experiment/analysis must consider, where the current software model can measure them without fabrication:

| Dimension | Candidate measures | Existing evidence | New work |
|---|---|---|---|
| Outcome resilience | success, terminal escalation, stale-ref, safe degradation, unrecovered state | Yes | Re-analyze/extend only if needed |
| Recovery efficiency | attempts to recovery, retries, unnecessary retries, recovery actions | Partial/yes | Controlled cases |
| Recovery latency | fault-to-decision, decision-to-recovery, fault-to-recovery, fault-to-escalation | Limited | Likely new instrumentation/model |
| State-transition cost | total transitions, retry/quarantine/recovery/release/escalation transitions | Yes/partial | Controlled comparison |
| Scheduler/context cost | scheduler transitions, context switches, interrupted/restarted work | Uncertain | Only if model supports valid measurement |
| Work preservation | useful work preserved, re-executed work, lost/delayed work, unaffected work completed | Partial | Controlled cases |
| Fault containment | correct target isolation, unrelated-event contamination, release correctness | Partial | Controlled cases |
| Retry efficiency | redundant retries avoided, retries before escalation/recovery | Yes | Stress combinations |
| Escalation quality | premature, delayed, or appropriate escalation; time before escalation | Partial | Controlled cases |
| Resource cost | CPU/step count, fixed-state use, trace/storage overhead, communication actions where modeled | Partial | New measurements where valid |
| Memory overhead | static state/trace/resource footprint attributable to policy | Partial | Comparative accounting |
| Policy decision cost | bounded decision steps/operations if validly measurable | Limited | Instrument only if non-invasive |
| Resilience overhead | cost per successful recovery / cost per contained fault | Partial | New derived metrics |
| Decision accuracy | correct vs unnecessary retry/reinit/degrade/escalate decisions | Partial | Scenario expansion |
| Fault-class adaptability | transient, persistent, intermittent, recurring, task/queue/peripheral/event/resource faults | Limited | Matrix expansion |
| Compound-fault behavior | fault + load + history + contention + dependency combinations | Limited | High-priority new cases |
| Graceful degradation | controlled degradation vs unsafe failure/terminal loss | Partial | Targeted cases |
| Worst-case behavior | worst latency, attempts, transitions, resource cost, propagation | Partial | New analysis |
| Predictability | deterministic replay and boundedness | Strong existing evidence | Validation criterion, not assumed P4 advantage |
| Complexity-vs-benefit | additional mechanism cost vs measurable resilience benefit | Partial | Trade-off analysis |

### Measurement rule

A metric may be used only if its semantics are explicitly defined and the existing host/virtual model can measure it faithfully. Never invent MCU cycle counts, scheduler context switches, cache effects, energy, electrical timing, RAM/Flash figures, or other physical quantities from a software-only trace.

## 4. Scenario-combination search space

K.10 must not cherry-pick only cases expected to favor P4. Include both differentiating and no-difference cases.

### Fault dimension
- transient
- persistent
- intermittent
- recurring/repeated
- consecutive faults
- alternating fault classes
- fault during recovery
- fault after previous recovery

### Context/history dimension
- first fault
- repeated fault on same event/resource
- prior successful recovery
- prior failed recovery
- prior escalation
- history available vs history-insufficient
- critical vs deferable work

### Workload/scheduling dimension
- low load
- high load
- queue pressure
- dependency chain
- independent concurrent work
- mixed criticality
- fault at early/middle/late queue position

### Resource/environment dimension
- peripheral fault
- event fault
- resource/queue pressure
- recovery-resource contention
- multiple affected resources where the model supports it

### Association dimension
- exact association
- ambiguous association
- invalid/stale identity
- association evidence insufficient for a safe target

### Compound combinations
Prioritize combinations such as:
1. persistent peripheral fault + repeated history + dependent queued work;
2. persistent fault + high queue load;
3. intermittent fault + repeated same-resource failure;
4. prior recovery failure + new fault;
5. ambiguous association + high workload;
6. fault during recovery + dependency chain;
7. mixed critical/deferable work + persistent fault;
8. repeated fault + resource contention;
9. fault after a previous successful reinit;
10. compound combinations that expose differences between context-aware/history-aware and history-blind baselines.

The purpose is to expose **interaction effects** of P4's integrated mechanism, not to manufacture favorable outcomes.

## 5. Required baseline attribution

Every observed P4 difference must be attributed to the actual differing mechanism.

Existing locks remain mandatory:
- P0-P3 are not clean quarantine ablations because exact-event quarantine is shared.
- S06 success is shared by P1/P2/P3/P4; P4 is not uniquely superior there.
- W09/W10 are capacity-confounded.
- Exact-event quarantine cannot be claimed as a unique P4 benefit in the current implementation.
- P2 must remain distinct from P1/P3/P4 on S06: P2 succeeds through its history-blind third retry path, with authoritative digest `0xCDAB2617`.

If a new experiment changes any mechanism shared by baselines, it must be explicitly classified as a new experimental mechanism rather than silently folded into P4.

## 6. Advantage interpretation hierarchy

For each candidate metric, classify results as:
1. **P4 advantage** — a pre-defined beneficial metric difference attributable to P4's integrated mechanism.
2. **P4 neutral** — no meaningful difference.
3. **P4 trade-off/cost** — P4 improves one property while imposing measurable cost elsewhere.
4. **Baseline advantage** — a baseline is better on that metric.
5. **Inconclusive** — measurement/model does not support a defensible comparison.

Do not use an overall score, ranking, tier, or single composite winner. Preserve metric-level evidence and trade-offs.

## 7. Novelty investigation scope

Novelty is a separate question from performance.

Decompose the proposed mechanism into:
- context-aware recovery decision;
- bounded recovery history;
- fixed recovery ladder;
- peripheral recovery/reinit/reset;
- evidence-bounded fault-to-event association;
- event-level quarantine/retention;
- dependency/order-aware preservation of unrelated work;
- deterministic verification/release/escalation;
- zero-heap/static bounded implementation;
- the specific interaction/integration of these elements.

K.10 should search:
- academic papers;
- patents and patent families;
- technical systems and standards;
- embedded/RTOS/bare-metal implementations;
- peripheral/driver recovery systems;
- transaction/message/event quarantine systems;
- safety-critical fault-management systems.

Search individual elements, pairwise combinations, higher-order combinations, and whole-combination disclosures.

The current prior-art record already establishes that peripheral recovery, recovery history, failed-event quarantine, dependency-aware containment, selective preservation, constrained fault disambiguation, deterministic tracing, and zero-dynamic-allocation execution are individually established or have strong adjacent prior art. The unresolved question is the specific integrated combination under the constrained event-driven MCU setting.

Do not claim novelty merely because no identical reference is found. Also distinguish technical novelty from inventive step/non-obviousness; this repository is not a legal patentability opinion.

## 8. Falsification conditions

The research must be willing to conclude:
- P4 has no meaningful advantage under the modeled conditions;
- P4 has only conditional advantages;
- P4 has benefits with measurable overhead/trade-offs;
- a baseline is better for some conditions;
- the integrated novelty hypothesis is weakened or contradicted by prior art.

A negative or mixed result is valid research evidence.

## 9. K.9.2 boundaries

K.9.2 must:
- lock the metric definitions;
- lock scenario/combinatorial dimensions;
- define admissible and inadmissible measurements;
- define attribution rules;
- define the novelty search decomposition;
- define falsification criteria;
- update continuity and the next-chat prompt.

K.9.2 must not:
- modify Gates A-E;
- modify `reference/src/ref_runtime.c` or `reference/include/ref_runtime.h`;
- redesign P4;
- add a new policy variant;
- create a second recovery engine;
- run the decisive K.10 experiment matrix;
- issue a final superiority conclusion;
- issue a final novelty/patentability conclusion;
- perform hardware experiments.

## 10. Antigravity role

Antigravity is the execution agent for the repository. The K.9.2 ChatGPT chat is the research-control/audit layer.

K.9.2 ChatGPT must give Antigravity a bounded execution brief that:
1. starts from the latest `exp` commit;
2. reads the continuity and K.9.2 design files first;
3. audits the current instrumentation and existing evidence for the locked metrics;
4. identifies exactly which metrics are already measurable and which require new, non-invasive instrumentation;
5. maps the scenario-combination space to current W01-W14/S01-S14 coverage;
6. proposes/records any missing K.10 experiment cases without executing the decisive matrix;
7. performs repository/document consistency checks;
8. preserves all historical K.1-K.9 records;
9. commits only K.9.2 design/continuity artifacts to the K.9.2 branch and returns exact commit/branch/test/status information.

Antigravity must not implement new P4 behavior merely because a metric is difficult to measure. If a required metric cannot be measured faithfully in the current software model, mark it unavailable and design an appropriate bounded alternative.

## 11. Required K.9.2 exit artifacts

- this design lock;
- `research/chat_records/chat_k9_2_record.md`;
- updated `research/PART_II_CHAT_PLAN.md`;
- updated `CURRENT_HANDOFF.md`;
- updated `PROJECT_STATE.md`;
- updated `DECISION_LOG.md` if a new decision is recorded;
- updated `NEXT_CHAT_PROMPT.md` pointing to K.10;
- no modification to historical K.9 record.

## 12. K.10 handoff

K.10 is no longer “final conclusion” at entry.

K.10 must execute the locked **P4 Advantage & Novelty Investigation**:
- implement only the measurement/instrumentation changes approved by K.9.2;
- run the defined matched advantage/interaction experiments;
- analyze metric-level P4 vs P0-P3 differences and trade-offs;
- perform the deeper prior-art search;
- produce an evidence-bounded result for both performance advantage and technical differentiation.

A later checkpoint must perform final synthesis/hardware handoff only after K.10 evidence is complete. No K.10 result may be predetermined.
