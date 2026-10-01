# K.10 — P4 Advantage & Novelty Investigation Results

**Date:** 2026-10-01  
**Status:** INCOMPLETE / EXECUTION BLOCKED IN THIS CHAT ENVIRONMENT

## 1. Starting-state verification

Live `exp` HEAD was verified as `da2c89e2ea3a78fb61dcb4eb39c1f38cd6a6a0de`.

The earlier K.10 handoff declared `e28af7a539eec790aa7b9fc7a3bdc819f1992403` as the expected continuity HEAD. The live HEAD is five commits ahead of that state, and the compare shows only continuity/control-document changes in those commits; no protected runtime source file changed.

Protected runtime blobs:
- `reference/src/ref_runtime.c`: `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81`
- `reference/include/ref_runtime.h`: `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`

Gates A-E remain frozen. `policy_decide()` remains the policy authority and `runtime_apply_policy()` remains the transition authority.

## 2. Instrumentation changes

None. No protected runtime or policy semantics were changed.

## 3. Experimental protocol

The K.9.2 21-dimension matrix and required case families/controls were audited. The decisive K.10 experiment matrix was **not executed** in this environment because the required Antigravity repository execution agent is unavailable and no local/CI execution path is exposed.

Therefore no new raw or derived performance metrics are claimed.

## 4. Metrics

The locked admissible measurements remain:
- terminal outcomes;
- recovery attempts/actions;
- authoritative trace transitions;
- work disposition;
- fault containment;
- logical transition/stage-distance measures explicitly labelled software-model metrics;
- host/reference static accounting;
- non-invasive policy-decision operation counts if implemented without semantic change.

Physical MCU cycles, wall-clock latency, RTOS context switches, physical RAM/Flash, energy, electrical timing and hardware MPU behavior remain out of scope.

## 5. P4 vs baseline comparisons

No new K.10 performance comparison is claimed.

Existing attribution locks remain in force:
- exact-event quarantine is shared across P0-P4;
- S06 recovery is shared by P1/P2/P3/P4;
- W09/W10 are capacity-confounded;
- determinism is a validation property unless a controlled policy-specific difference is demonstrated.

## 6. Interaction analysis

Not executed. Required interactions include history x persistence, history x queue pressure, ambiguity x workload, fault-during-recovery x dependency, prior recovery failure/escalation x subsequent fault, criticality x persistence, recovery/resource contention x repeated fault, recurrence x prior recovery outcome, and queue position x fault timing.

## 7. Trade-offs

Not measured in K.10 here. The locked protocol requires explicit reporting of P4 costs and conditions in which a simpler baseline may legitimately be cheaper.

## 8. Negative/no-difference findings

No new K.10 negative/no-difference result can be claimed because the decisive matrix was not executed.

## 9. Adversarial prior-art investigation

Fresh searches were performed against the locked decomposition.

Major evidence:
- Phoenix (USENIX ATC 2015) establishes constrained embedded peripheral-failure recovery with lightweight checkpoint/rollback.
- US7386764B2 / US7000154B1 establish event-based fault correlation/history and recovery-action selection/escalation.
- US8510592B1 establishes peripheral error containment/isolation, recovery/reinitialization/reset and escalation.
- US10331522 and US10929373 establish failed-event/resource association, retry and message quarantine.
- US10921871B2 establishes recovery history affecting increasingly aggressive restart/restore actions.
- Ahn et al. establish dependency/severity-based containment with preservation of unaffected applications.
- R2U2-related work establishes resource-bounded runtime monitoring/fault disambiguation and trace/verdict-driven mitigation.
- US12688084 establishes paused event flow, retained failed-event queues, retry using stored identifiers, and resume after recovery.
- Microreboot establishes fine-grained localized recovery intended to avoid disturbing unaffected components and reduce lost work.

Interpretation:
1. Individual elements are broadly established.
2. Several pairwise combinations are directly covered by prior art.
3. Multiple references collectively cover many three-or-more-element subsets.
4. No single searched reference was identified that clearly discloses the complete proposed MCU-specific combination of evidence-bounded fault-to-event association, retained event quarantine, dependency/order-aware preservation, bounded history-conditioned recovery ladder, static/zero-heap bounded implementation, deterministic release/escalation, and peripheral-fault initiation.

This is an unresolved search result, **not a novelty conclusion**. Absence of a single complete reference does not establish novelty, and inventive step/non-obviousness remains separate.

## 10. Falsification assessment

### Performance hypothesis
**UNTESTED.** No evidence supports a P4 advantage, neutral result, trade-off, baseline advantage, equivalence or inconclusive experimental finding yet.

### Integrated novelty hypothesis
**Narrowed / weakened at component and pairwise level; unresolved at whole-combination level.** Broad framings are not defensible. The exact integrated distinction remains a research hypothesis, not an established novelty claim.

## 11. Limitations

1. Antigravity is not available in this ChatGPT environment.
2. No local repository checkout/build execution path is available here.
3. Mandatory K.10 matched scenarios, controls and raw metrics were therefore not executed.
4. Prior-art search is technical research, not an exhaustive legal search or patentability opinion.
5. Software-model results cannot be generalized to STM32U575 hardware.

## 12. Evidence-bounded conclusion

**K.10 is NOT COMPLETE.**

Repository state and protected-runtime integrity were audited successfully. Fresh adversarial prior-art research substantially weakens broad component/pairwise novelty framings, while the whole-combination question remains unresolved. The decisive K.10 experiment matrix was not executed, so no P4 performance/superiority conclusion is made.

K.11 must remain inactive. The next action is actual K.10 execution through the designated Antigravity repository agent (or an explicitly authorized equivalent execution environment), followed by metric-level analysis and continuity updates.
