# Novelty Investigation — K.4 Re-Research Record

Date: 2026-10-01
Checkpoint: K.4 — Novelty Re-Research + Conceptual Architecture Lock
Status: Active technical prior-art investigation; no novelty or patentability conclusion.

## 1. Falsification rule

This record deliberately attacks the project's novelty hypothesis rather than confirming it.

Working hypothesis:

> A deliberately small, deterministic, zero-heap recovery runtime may combine evidence-bounded fault association with bounded context/history-aware recovery and event-level quarantine/dependency preservation in a way that limits collateral disruption in event-driven MCU workloads.

This is a hypothesis only.

The investigation distinguishes:
- Established prior art
- Partial overlap
- Potential differentiator
- Unresolved
- Contradicting evidence

Search date: 2026-10-01. Sources include academic papers, patents/patent applications, runtime-verification work, and open-source embedded implementations.

## 2. References examined

### PA-01 — Phoenix: peripheral recovery in resource-constrained embedded systems

Rebecca Smith and Scott Rixner, “Surviving Peripheral Failures in Embedded Systems,” USENIX ATC 2015.

Phoenix provides checkpoint-based recovery from peripheral failures in resource-constrained embedded systems. It tracks internal and external peripheral state, identifies the failed peripheral, rolls back to the relevant checkpoint, and reconstructs which peripherals must be redone using programmer-specified dependencies. The paper reports recovery with as little as 6 KB of memory.

Source: https://www.usenix.org/conference/atc15/technical-session/presentation/smith

Assessment: ESTABLISHED PRIOR ART / PARTIAL OVERLAP.

Phoenix materially overlaps peripheral-fault recovery, fault identification, checkpoint/rollback, and dependency-aware redo. Its implementation uses a separate recovery heap and checkpoint/rematerialization structures, so it is not evidence for the project's zero-heap event-quarantine implementation. It also does not establish the proposed retained event quarantine semantics.

### PA-02 — PCI Error Resilience, US8510592B1

US8510592B1 describes peripheral error detection, containment/isolation, recovery, reinitialization, reset-policy selection, verification, continued service and escalation to system panic.

Source: https://patents.google.com/patent/US8510592B1/en

Assessment: STRONG PARTIAL OVERLAP / CONTRADICTING EVIDENCE.

It materially covers peripheral fault observation, isolation, continued operation of unaffected service, recovery/reinitialization, bounded reset choices and escalation. The searched disclosure does not establish the proposed MCU event-level quarantine/retention or evidence-bounded causal association between a peripheral fault and a particular queued event.

### PA-03 — Recovery history, US10921871B2

US10921871B2 explicitly retains recovery history and uses prior recovery outcomes to choose a different recovery solution when a fault persists; exhaustion can lead to escalation.

Source: https://patents.google.com/patent/US10921871B2/en

Assessment: ESTABLISHED PRIOR ART.

This strongly weakens any novelty framing based merely on “short recovery history changes the next action.”

### PA-04 — Event failure management, US10331522 / US10929373

This patent family maintains failed-event information with associated components/resources, retries after resource changes, analyzes relationships between failures, and can prevent processing or store messages in quarantine.

Sources:
https://patents.justia.com/patent/10331522
https://patents.justia.com/patent/10929373

Assessment: STRONG PARTIAL OVERLAP / CONTRADICTING EVIDENCE.

It covers failed-event identity, resource association, failure history, retry, relationship analysis, message quarantine and prevention of processing. Its domain is distributed/application processing rather than constrained MCU firmware.

### PA-05 — Processing Failed Events on an Application Server, US20180365126

The application describes removing a failed event from an event queue, storing it in a failed-event queue with its flow and failure reason, analyzing it, applying corrective action, and repeating replay/corrective-action cycles.

Source: https://patents.justia.com/patent/20180365126

Assessment: STRONG PARTIAL OVERLAP.

This weakens any claim that event-level failure retention plus corrective retry is itself distinctive. It does not target a resource-constrained event-driven MCU runtime.

### PA-06 — Intelligent data flow control valve, US12688084 (2026)

A 2026 patent describes pausing upstream event transmission during recoverable downstream errors, retaining paused events, maintaining a failed-events queue, retrying failed events, verifying recovery, and releasing retained events after recovery.

Source: https://patents.justia.com/patent/12688084

Assessment: RECENT CONTRADICTING ADJACENT EVIDENCE.

This is particularly relevant to the broad preservation framing. It is an integration/data-flow system rather than an MCU runtime, but retaining queued work while recovery occurs and releasing it after verification is clearly established outside the MCU domain.

### PA-07 — Fault-tolerant service robots / dependency-aware containment

Ahn, Loh and Yeo, “A Framework-Based Approach for Fault-Tolerant Service Robots,” International Journal of Advanced Robotic Systems.

Source: https://journals.sagepub.com/doi/full/10.5772/54023

The framework uses severity and dependency rules for fault isolation/containment and allows unaffected applications to continue while dependent applications stop.

Assessment: ESTABLISHED PARTIAL OVERLAP.

Dependency-aware containment and preservation of unaffected service are therefore not new general principles.

### PA-08 — Selective rollback and dependency preservation

Distributed/dataflow recovery literature establishes selective rollback/preservation based on dependencies. Falkirk Wheel models rollback by logical event times and supports selective preservation of event effects.

Source: https://arxiv.org/abs/1503.08877

Assessment: ESTABLISHED ADJACENT PRIOR ART.

“Dependency-aware preservation instead of global rollback” cannot be treated as a new general principle.

### PA-09 — Runtime verification and constrained fault disambiguation

Reinbacher, Függer and Brauer describe runtime verification for embedded real-time systems using execution events as observations and bounded/non-intrusive monitoring.

Source: https://link.springer.com/article/10.1007/s10703-013-0199-z

Kempa et al. describe online runtime verification for fault disambiguation on Robonaut2 under severe resource constraints, including real-time fault disambiguation and mitigation triggering.

Source: https://rcl.ece.iastate.edu/publications/KemZha20A

R2U2 is an established resource-constrained runtime-verification framework.

Source: https://r2u2.github.io/r2u2/

Assessment: ESTABLISHED PRIOR ART for event observation, fault disambiguation, bounded monitoring and trace/verdict reasoning.

### PA-10 — Zero-dynamic-allocation embedded execution

microfsm is an open-source deterministic table-driven C99 state-machine implementation using caller-owned memory and no dynamic allocation.

Source: https://github.com/Vanderhell/microfsm

Assessment: ESTABLISHED ENGINEERING PRACTICE.

Zero-heap/static allocation is an implementation constraint, not standalone novelty.

## 3. Element-by-element matrix

| Proposed element | Relevant evidence | Status |
|---|---|---|
| Peripheral fault detection | PA-01, PA-02 | Established prior art |
| Peripheral recovery/reinit/reset | PA-01, PA-02 | Established prior art |
| Recovery escalation | PA-02, PA-03 | Established prior art |
| Recovery history affects next action | PA-03 | Established prior art |
| Failed-event identity + retry | PA-04, PA-05 | Established prior art |
| Event/message quarantine | PA-04, PA-05 | Established prior art |
| Retention of queued work during recovery | PA-06 | Established adjacent prior art |
| Dependency-aware containment | PA-07 | Established prior art |
| Dependency-aware selective rollback/preservation | PA-01, PA-08 | Established adjacent prior art |
| Runtime fault disambiguation | PA-09 | Established prior art |
| Deterministic trace/verdict layer | PA-09 | Established prior art |
| Zero-heap/static bounded state | PA-10 | Established engineering practice |
| Event-level quarantine tied specifically to a peripheral fault | PA-01/02/04/05 show partial pieces | Unresolved |
| Association precision bounded by available evidence | No exact match identified in searched set | Potential differentiator, unresolved |
| Short bounded history + fixed recovery ladder + event quarantine | Elements appear separately | Potential differentiator, unresolved |
| Dependency/order-aware preservation of unrelated queued MCU events during peripheral recovery | Adjacent matches exist outside MCU | Potential differentiator, unresolved |
| Complete combination in one constrained MCU runtime | No identical reference found in this search | Unresolved, not novel |

## 4. Direct combination assessment

### Peripheral recovery + containment + continued service
Strongly disclosed by PA-01 and PA-02.

Conclusion: not a defensible novelty center.

### Recovery history + bounded retry/escalation
Disclosed by PA-03 and broadly by recovery systems.

Conclusion: not a defensible novelty center.

### Failed event + resource association + quarantine + retry
Disclosed by PA-04 and PA-05.

Conclusion: not a defensible novelty center.

### Dependency-aware containment/preservation
Disclosed by PA-01, PA-07 and PA-08.

Conclusion: not a defensible novelty center.

### Constrained runtime fault disambiguation + trace/verification
Disclosed by PA-09.

Conclusion: not a defensible novelty center.

### Proposed constrained MCU integration
The current search did not identify a single reference clearly disclosing all of:
1. evidence-bounded fault-to-event association;
2. event-level quarantine/retention;
3. dependency/order-aware preservation of unrelated queued events;
4. short bounded recovery history controlling a fixed recovery ladder;
5. static/zero-heap bounded implementation;
6. deterministic verification/release/escalation;
7. peripheral-fault context as the initiating fault domain.

Status: UNRESOLVED, NOT NOVEL.

The absence of one identical hit is not evidence of novelty. An obvious-combination/recombination challenge remains plausible.

## 5. Falsification criteria

Narrow or reject the hypothesis if a reference/family is found that substantially discloses the combined mechanism in constrained MCU/RTOS/bare-metal firmware, or if closely related references show that the combination was routine in the same field and for the same technical purpose.

## 6. Narrowed K.4 hypothesis

> There may be a technically meaningful distinction in implementing evidence-limited fault-to-event association together with retained event quarantine, dependency/order-aware preservation, and bounded history-conditioned recovery as one statically bounded mechanism for constrained event-driven MCU firmware.

Status: UNRESOLVED.

## 7. Required follow-on search

Continue, where practical, with:
- event quarantine + MCU/RTOS/bare metal;
- poison-event isolation in embedded event queues;
- peripheral fault + transaction/event identity;
- I2C/SPI fault + queued transaction recovery;
- dependency-aware event release after peripheral recovery;
- driver recovery with request/transaction quarantine;
- safety-critical event queue containment;
- embedded fault managers using recovery history;
- AUTOSAR/Adaptive or Classic fault/event management;
- avionics/spacecraft event/task recovery with dependency-aware preservation;
- patent families around embedded transaction quarantine.

Prioritize primary patent databases, IEEE/ACM/USENIX/Springer/SAE/AIAA sources and vendor specifications.

## 8. Legal boundary

This is technical prior-art research, not a legal patentability opinion. No novelty, non-obviousness, freedom-to-operate, or patentability conclusion is established.
