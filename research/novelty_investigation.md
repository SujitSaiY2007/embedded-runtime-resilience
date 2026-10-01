# Novelty Investigation — Part II Opening Record

Date: 2026-10-01
Status: Active investigation — not a novelty conclusion

## 1. Purpose
The project is pursuing a defensible novelty hypothesis, not assuming novelty. The investigation must test the complete proposed mechanism against prior art rather than relying on individual ingredients.

## 2. Working combination under investigation
1. Resource-constrained event-driven MCU firmware.
2. Zero-heap/static bounded recovery state.
3. Evidence-bounded fault association.
4. Short recovery history used in bounded action selection.
5. Finite recovery ladder with terminal escalation/degradation.
6. Event-level quarantine/retention rather than indiscriminate queue flushing.
7. Dependency/order-aware preservation and release.
8. Deterministic traceability from fault to association to action to verification to release/escalation.
9. Optional MPU-enabled containment at the target architecture level.
None of these is treated as individually novel.

## 3. Initial prior-art position
Peripheral recovery is established. Phoenix (USENIX ATC 2015) presents automated recovery from peripheral failures in resource-constrained embedded systems using checkpointing/rollback and covers timeouts, protocol violations and interrupt-related faults.
Policy-driven peripheral recovery is established. US8510592B1 describes peripheral error containment, recovery routines, reinitialization, reset policy and escalation.
Selective recovery is established in adjacent storage and hardware-recovery systems.
Context/state-aware recovery is established broadly, including recovery controllers maintaining dependency topology and context/state.
Zero-heap deterministic event-driven execution is established in embedded state-machine frameworks.

## 4. Narrow novelty question
Is there prior art that already discloses, in a resource-constrained event-driven MCU runtime, the specific integrated sequence of evidence-bounded event/fault association, bounded context/history-driven recovery selection, event-level quarantine/retention, dependency/order-aware preservation of unrelated queued work, and deterministic verification/release or terminal escalation under a zero-heap bounded-state model?

## 5. Element matrix
| Element | Current status |
|---|---|
| Peripheral fault recovery | Established |
| Retry/reinit/reset/escalation | Established |
| Checkpoint/rollback | Established |
| Context/state-aware recovery | Established broadly |
| Zero-heap/static bounded state | Established |
| Event-driven queue | Established |
| Fault-to-event association | Requires deeper search |
| Dependency-aware event quarantine | Requires deeper search |
| Retention of quarantined work | Requires deeper search |
| Preservation of unrelated queued work during recovery | Requires deeper search |
| Association precision bounded by evidence precision | Requires deeper search |
| Short history plus bounded action selection | Requires deeper search |
| Deterministic fault-to-release trace | Requires deeper search |
| Integrated zero-heap combination | Requires combination search |
| MPU-enabled containment | Established technology |

## 6. Preliminary hypothesis
A deliberately small, deterministic, zero-heap recovery runtime may combine evidence-bounded fault association with bounded context/history-aware recovery and event-level quarantine/dependency preservation in a way that limits collateral disruption in event-driven MCU workloads.
This is a research hypothesis, not an established novelty or patentability conclusion.

## 7. K.4 search requirements
Search specifically for event quarantine + embedded/MCU/peripheral; fault-associated event recovery; dependency-aware event recovery; selective event recovery in embedded systems; event retention and queue preservation after peripheral faults; event-level fault containment; transaction quarantine in firmware; context-history recovery policy; zero-heap fault recovery; and patents combining peripheral recovery with queue/event isolation.
Record both supporting and contradicting prior art.

## 8. What would strengthen the hypothesis
Evidence that prior art usually resets/reinitializes a peripheral or task without retaining/quarantining the specific fault-associated event; that event quarantine elsewhere is not tied to peripheral-fault association plus bounded recovery history in constrained MCU firmware; that dependency-aware preservation is a correctness condition; and that the complete combination produces a measurable reduction in collateral event loss/delay.

## 9. What would weaken or falsify it
A single reference or tightly linked prior-art family substantially disclosing the combined fault-to-event association, selective event quarantine/retention, dependency-aware release, bounded history-based recovery, constrained implementation and peripheral recovery would require the hypothesis to be narrowed or rejected.

## 10. Legal boundary
This repository can document technical prior art and a research novelty hypothesis. It does not provide a legal patentability opinion.

## 11. Opening conclusion
The initial search does not justify a novelty claim yet. It does justify a narrower combination-level investigation before implementation.