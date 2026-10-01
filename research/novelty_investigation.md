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

---
# K.4 Deep Prior-Art Re-Research — 2026-10-01

## Search standard

The search was adversarial: actively seek evidence that would disprove or substantially weaken the novelty hypothesis. Absence of an identical result is not treated as proof of novelty.

## Key references

| ID | Reference | Main overlap | Status |
|---|---|---|---|
| PA-01 | Smith & Rixner, Phoenix, USENIX ATC 2015 | Resource-constrained peripheral recovery, checkpoint/rollback, dependency-aware redo | Established / partial overlap |
| PA-02 | US8510592B1, PCI Error Resilience | Peripheral error detection, containment/isolation, recovery, reinit, reset policy, escalation, continued service | Strong partial overlap |
| PA-03 | US10921871B2 | Recovery history used to choose subsequent recovery action | Established |
| PA-04 | US10331522 / US10929373 | Failed-event/resource association, retry, relationship analysis, message quarantine | Strong partial overlap |
| PA-05 | US20180365126A1 | Failed-event queue, failure reason, corrective action, replay | Strong partial overlap |
| PA-06 | US12688084 | Paused event retention, failed-event queue, retry, recovery verification, release of retained events | Recent adjacent contradicting evidence |
| PA-07 | Ahn et al., Fault-Tolerant Service Robots | Severity/dependency containment, preserving unaffected applications | Established partial overlap |
| PA-08 | Falkirk Wheel | Selective rollback/preservation based on event/logical-time domains | Established adjacent prior art |
| PA-09 | Reinbacher et al.; Kempa et al.; R2U2 | Resource-constrained runtime observation, fault disambiguation, trace/verdict monitoring | Established |
| PA-10 | microfsm and similar embedded frameworks | Static/caller-owned state, zero dynamic allocation | Established engineering practice |

## Source record

PA-01: https://www.usenix.org/conference/atc15/technical-session/presentation/smith  
PA-02: https://patents.google.com/patent/US8510592B1/en  
PA-03: https://patents.google.com/patent/US10921871B2/en  
PA-04: https://patents.justia.com/patent/10331522 and https://patents.justia.com/patent/10929373  
PA-05: https://patents.justia.com/patent/20180365126  
PA-06: https://patents.justia.com/patent/12688084  
PA-07: https://journals.sagepub.com/doi/full/10.5772/54023  
PA-08: https://arxiv.org/abs/1503.08877  
PA-09: https://link.springer.com/article/10.1007/s10703-013-0199-z ; https://rcl.ece.iastate.edu/publications/KemZha20A ; https://r2u2.github.io/r2u2/  
PA-10: https://github.com/Vanderhell/microfsm

## Element-by-element matrix

| Proposed element | Current evidence status | Interpretation |
|---|---|---|
| Peripheral fault detection | Established | Not a novelty center |
| Peripheral recovery/reinit/reset | Established | Not a novelty center |
| Recovery escalation | Established | Not a novelty center |
| Recovery history affects later action | Established | Broad history-based framing is weak |
| Failed-event identity + retry | Established | Not a novelty center |
| Event/message quarantine | Established | Not a novelty center |
| Retention of queued work during recovery | Established adjacent | Weakens broad preservation framing |
| Dependency-aware containment | Established | Not a novelty center |
| Selective rollback/preservation | Established adjacent | Not a novelty center |
| Runtime fault disambiguation | Established | Not a novelty center |
| Deterministic trace/verdict | Established | Not a novelty center |
| Zero-heap/static bounded state | Established practice | Constraint, not standalone novelty |
| Fault-to-specific-event association with evidence limits | No exact match in searched set | Potential differentiator, unresolved |
| Event-level quarantine specifically tied to peripheral-fault evidence | Partial overlaps only | Unresolved |
| Dependency/order-aware preservation of unrelated queued MCU events | Adjacent matches outside MCU | Potential differentiator, unresolved |
| Short bounded history + fixed recovery ladder + event quarantine | Components appear separately | Potential differentiator, unresolved |
| Complete combination in one constrained event-driven MCU runtime | No identical reference found in this search | Unresolved, not novel |

## Direct overlap conclusions

### Peripheral recovery + containment + continued service
Already strongly disclosed by PA-01 and PA-02. Not a defensible novelty center.

### Recovery history + bounded retry/escalation
Disclosed by PA-03 and broadly in recovery systems. Not a defensible novelty center.

### Failed event + resource association + quarantine + retry
Disclosed by PA-04 and PA-05. Not a defensible novelty center.

### Dependency-aware containment/preservation
Disclosed by PA-01, PA-07 and PA-08. Not a defensible novelty center.

### Constrained fault disambiguation + trace/verification
Disclosed by PA-09. Not a defensible novelty center.

### Complete proposed MCU integration
The current search did not identify one reference clearly disclosing all of:
1. evidence-bounded fault-to-event association;
2. event-level quarantine/retention;
3. dependency/order-aware preservation of unrelated queued events;
4. short bounded recovery history controlling a fixed recovery ladder;
5. static/zero-heap bounded implementation;
6. deterministic verification/release/escalation;
7. peripheral-fault context as the initiating fault domain.

Status: UNRESOLVED, NOT NOVEL.

An obvious-combination/recombination challenge remains plausible even without a single anticipatory reference.

## Falsification criteria

The hypothesis must be narrowed or rejected if:
- a constrained MCU/RTOS/bare-metal reference substantially discloses the combined mechanism; or
- closely related references show that these elements were routinely combined in the same technical field for the same technical purpose.

## Narrowed hypothesis

> There may be a technically meaningful distinction in implementing evidence-limited fault-to-event association together with retained event quarantine, dependency/order-aware preservation, and bounded history-conditioned recovery as one statically bounded mechanism for constrained event-driven MCU firmware.

Status: UNRESOLVED.

## Follow-on search targets

Prioritize:
- event quarantine + MCU/RTOS/bare metal;
- poison-event isolation in embedded queues;
- peripheral fault + transaction/event identity;
- I2C/SPI fault + queued transaction recovery;
- dependency-aware event release after peripheral recovery;
- driver recovery with request/transaction quarantine;
- safety-critical event queue containment;
- embedded fault managers using recovery history;
- AUTOSAR fault/event management;
- avionics/spacecraft task recovery;
- patent families on embedded transaction quarantine.

Legal boundary: this is technical prior-art research, not a legal patentability opinion.
