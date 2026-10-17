# Phase 1E.1 — Gate B Final Fault Model and Fault Association Contract

**Gate:** B — Fault Model + Fault Association  
**Phase:** 1E.1 — Experimental Design / Formalization Foundation  
**Status:** **ACCEPTED** at the semantic/design level; implementation and physical fault-injection validation remain deferred.  
**Date:** 2026-09-03

## 1. Purpose and acceptance boundary

Gate B freezes the smallest defensible fault model needed to test the frozen research question:

> Can a compact deterministic zero-heap recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead?

Gate B defines:

- the observable fault taxonomy for the primary I2C experiment and the secondary SPI path;
- deterministic software fault-injection semantics;
- candidate physical/protocol fault classes subject to later hardware feasibility verification;
- a bounded semantic fault record;
- evidence-bounded fault association;
- ambiguity handling;
- fault-episode and recurrence semantics;
- quarantine-scope implications;
- the evidence boundary between observation and causal inference.

Gate B does **not** freeze:

- exact C struct packing;
- final queue/history capacities;
- exact retry/transition budgets;
- final recovery action policy;
- final physical fault-injection apparatus;
- MPU configuration;
- experimental workload/repetition counts.

Those decisions belong to Gates C–E or physical testbed bring-up.

## 2. Relationship to Gate A and retained baseline

Gate A remains the authoritative semantic contract for event identity, dependency, lifecycle, queue admission/execution semantics, and quarantine. In particular:

- active event identity is `EventRef = {slot_id, generation}`;
- transaction identity is separate and bounded;
- dependencies are explicit `INDEPENDENT`, `ORDERED`, or `COUPLED/TRANSACTIONAL` relations;
- FIFO describes admission order, not universal execution order;
- quarantine is retained non-executable state;
- association precision must not exceed evidence precision.

The original `research/phase1_peripheral_testbed_fault_model.md` is retained as historical/baseline material. It remains useful for the initial testbed intent, but several statements are refined here rather than silently treated as final.

### Baseline disposition

| Baseline item | Gate B disposition | Reason |
|---|---|---|
| I2C as primary experimental interface | **Retained** | Provides protocol-level error/status evidence and a direct event/transaction context. |
| SPI as secondary interface | **Retained with reduced scope** | Useful for demonstrating that the policy is not purely an I2C recipe, but exact fault evidence is more implementation/device dependent. |
| Timeout/no-progress | **Refined** | A timeout is an observed failure condition, not proof of a specific physical cause. |
| NACK/error response | **Retained** | Directly observable at the controller/driver boundary for I2C. |
| Bus/protocol fault | **Retained and split by evidence** | Controller flags can establish some protocol/bus conditions; they do not identify the physical cause. |
| Peripheral state-machine lockup | **Renamed to persistent no-progress / suspected peripheral-state failure** | Internal lockup is normally an inference unless additional instrumentation proves it. |
| Repeated transient failure | **Moved to history/episode semantics** | Recurrence is a property over observations, not a distinct instantaneous fault class. |
| Persistent failure | **Moved to history/episode semantics** | Persistence requires repeated observations/recovery outcomes. |
| Ambiguous fault | **Retained** | Required when available evidence cannot defensibly narrow scope. |
| Service/software failure | **Retained as a distinct attribution class** | Needed to avoid incorrectly blaming the peripheral for driver/service failures. |
| Natural faults as primary experiment | **Rejected as primary mechanism** | Not reproducible enough for matched experiments. |

## 3. Evidence vocabulary

Every fault observation is interpreted at three levels:

### 3.1 Direct observation

A value or event actually available to the firmware/test harness, for example:

- I2C status/error flag;
- driver return code;
- transaction deadline expiry;
- transfer-progress counter not advancing within a declared interval;
- transaction verification failure;
- event/service/transaction identity recorded at the time of failure.

### 3.2 Software inference

A conclusion derived from multiple observations, for example:

- repeated failures of the same transaction under otherwise identical conditions;
- persistence after a defined reinitialization attempt;
- likely peripheral unavailability because the address repeatedly receives NACK;
- likely service-level failure when the controller reports no peripheral error but the service verification fails.

### 3.3 Unresolved physical cause

A physical explanation that cannot be established by the available instrumentation, such as:

- a particular electrical noise source causing a bus error;
- an internal peripheral state-machine defect;
- a specific sensor internal failure;
- an external power/interconnect cause when it was not measured.

Such explanations must not be encoded as if they were observed facts.

The governing rule is:

`association precision <= evidence precision`

## 4. Primary I2C fault taxonomy

The taxonomy is intentionally small. Fault class describes the **observed failure mode**; recurrence/persistence are separate history attributes.

### F-I2C-01 — NACK / non-acknowledge response

**Definition:** the I2C controller/driver observes a non-acknowledge condition during an address or data phase.

**Direct evidence:** controller/driver reports NACK (`NACKF` at the peripheral boundary where applicable) or an equivalent driver error.

**What can be inferred:** the addressed transfer did not receive the expected acknowledge. Depending on phase, this is compatible with an unavailable device, wrong address, device-side refusal/busy behavior, or another protocol condition.

**What cannot be inferred from NACK alone:** the physical root cause, or that the entire peripheral is permanently failed.

**Injection suitability:** highly suitable for deterministic software injection by forcing the driver/test harness to return a NACK-class error. Physical reproduction may be possible by a safe testbed configuration that causes non-response, but it must be validated on the actual device before being claimed.

**Research usefulness:** high; it provides a clean, repeatable failure signal for comparing recovery policies.

### F-I2C-02 — Transfer timeout / no-progress deadline expiry

**Definition:** a declared transfer fails to reach its required progress/completion condition before the experiment's timeout boundary.

**Direct evidence:** software deadline expiry and/or supported controller timeout indication.

The STM32U5 I2C implementation exposes timeout-related status in the I2C peripheral model, including a `TIMEOUT` flag for the supported SMBus timeout feature. The experiment may also use a software transaction deadline for ordinary I2C operation. These are not semantically identical and must be recorded distinctly if both are used. citeturn3search23turn3search2

**What can be inferred:** the expected transfer progress did not occur within the declared bound.

**What cannot be inferred:** a timeout does not by itself prove that the peripheral internally locked up, that SDA/SCL is physically stuck, or that the peripheral is defective.

**Injection suitability:** excellent for deterministic software testing through a bounded simulated stall or forced timeout; physical fault reproduction requires later hardware validation.

**Research usefulness:** high because it tests bounded recovery and latency.

### F-I2C-03 — Bus/protocol error

**Definition:** the controller reports a protocol/bus-level error such as `BERR` or another explicitly supported protocol error condition.

**Direct evidence:** controller status/driver error corresponding to the observed protocol condition. STM32U5 exposes `BERR`, `ARLO`, `NACKF`, `OVR`, and related I2C status indications through the I2C status interface. citeturn3search1turn3search3

**What can be inferred:** the controller detected a defined bus/protocol condition.

**What cannot be inferred:** the precise physical cause. For example, ST's STM32U575/U585 errata documents a case of spurious bus-error detection in master mode, demonstrating why a `BERR` observation must not automatically be translated into a physical-fault claim. citeturn3search21

**Injection suitability:** software injection is safe and deterministic. Physical protocol disruption is a candidate only after a safe fixture is established.

**Research usefulness:** high as a distinct observed class, but not as proof of a particular physical mechanism.

### F-I2C-04 — Arbitration / bus-ownership error

**Definition:** the controller reports arbitration loss (`ARLO`) or equivalent bus-ownership failure.

**Direct evidence:** `ARLO` status/driver error.

**What can be inferred:** the controller detected loss of arbitration under the bus protocol.

**Scope qualification:** the primary testbed is intended to be simple and single-master. Therefore `ARLO` should not be made a central workload fault class unless the physical/test configuration actually permits another master. If the experiment is single-master and `ARLO` is nevertheless observed, it should be retained as an observed controller condition and treated conservatively rather than fabricated into a normal injected scenario.

**Injection suitability:** deterministic software injection is safe; physical multi-master injection is out of scope for the minimal testbed unless later justified.

**Research usefulness:** secondary/low for the core hypothesis.

### F-I2C-05 — Persistent no-progress / suspected peripheral-state failure

**Definition:** a transaction repeatedly exhibits no-progress/failure across a defined recovery sequence, while available evidence does not prove an internal peripheral state-machine lockup.

**Direct evidence:** repeated no-progress/timeout/error observations plus unsuccessful defined recovery attempts.

**Inference:** persistence increases the plausibility that the peripheral or communication path is in a non-recovering state, but does not prove the internal failure location.

**Important distinction:** the baseline phrase "peripheral state-machine lockup" is therefore not retained as a directly observable fault class. The observable class is **persistent no-progress**; "peripheral lockup" is an optional hypothesis recorded only when supporting evidence exists.

**Injection suitability:** strong in software as a bounded persistent-stall scenario. Physical reproduction is conditional on safe hardware feasibility.

**Research usefulness:** high because it distinguishes repeated retry from escalation/degradation behavior.

## 5. Secondary SPI fault taxonomy

SPI has no universal acknowledgement semantics equivalent to I2C NACK. Therefore the same labels must not be mechanically reused.

The secondary SPI path uses only these minimum observed classes:

1. **F-SPI-01 — transfer timeout/no-progress:** transaction fails to reach its completion/progress condition within the declared deadline.
2. **F-SPI-02 — transaction/protocol verification failure:** transfer completes at the controller boundary but the expected device response/verification condition fails.
3. **F-SPI-03 — persistent communication failure:** repeated timeout or verification failures across a defined recovery sequence.
4. **F-SPI-04 — ambiguous attribution:** available evidence cannot distinguish device-side behavior, controller/configuration error, wiring/interconnect issue, or service-level error.

SPI-specific controller error flags, if available on the selected STM32U575 peripheral instance and driver configuration, may be recorded as evidence flags rather than automatically becoming new top-level fault classes.

The secondary SPI experiment is therefore deliberately smaller than the I2C experiment. Its purpose is contrast, not exhaustive SPI fault characterization.

The BMP280 is a suitable *candidate* because Bosch documents both I2C and SPI interfaces, but its use remains subject to later electrical compatibility, acquisition, and test-fixture verification. citeturn0search29turn0search1

## 6. Software/service-level fault class

### F-SW-01 — Service/driver-level failure without sufficient peripheral evidence

This class is necessary to prevent attribution bias.

Examples:

- the service rejects a transaction because its own precondition fails;
- a driver/API returns a logical error before a peripheral transaction is actually initiated;
- transaction verification fails while no controller-level peripheral error is observed;
- an internal service state inconsistency prevents valid submission.

The exact software causes are not assumed in advance. The key semantic criterion is:

> The failure is observed at the service/driver layer, but available evidence is insufficient to attribute it to a peripheral fault.

Such a failure must not automatically trigger peripheral-wide quarantine.

## 7. Ambiguous fault class

### F-AMB-01 — Insufficiently attributable failure

Use this class when multiple explanations remain consistent with the evidence and the instrumentation cannot defensibly select one.

Examples:

- transaction timeout with multiple possible blocked components;
- service verification failure with no controller error and no independent peripheral-health evidence;
- a shared bus condition affecting multiple transactions when the failing transaction cannot be uniquely identified;
- stale/reused identifiers where the active `EventRef` cannot be matched safely.

`UNKNOWN_AMBIGUOUS` is an association-confidence outcome as well as a fault-attribution result. It is not a license to guess.

## 8. Recurrence and persistence are history attributes, not new fault classes

The baseline listed "repeated transient failure" and "persistent failure" alongside instantaneous fault types. Gate B deliberately separates these concepts.

### 8.1 Observation

One concrete fault observation belongs to one event/transaction context and has one observed fault class.

### 8.2 Recurrence

`recurrence_count` is the number of qualifying observations of the same episode/fault signature within the bounded history window.

A recurrence increment does **not** create a new fault episode.

### 8.3 Persistence

A failure is considered persistent only after the episode has accumulated the defined evidence threshold, such as repeated failure after one or more permitted recovery transitions. The exact numerical threshold is Gate C policy work.

### 8.4 Transient

A fault is treated as transient-looking when the episode ends with verified recovery before persistence criteria are met. "Transient" is therefore a post-observation/history classification, not proof of the physical root cause.

This separation prevents the taxonomy from multiplying every fault class by every possible recurrence state.

## 9. Fault-to-event/transaction association model

The association hierarchy frozen by Gate A is made operational as follows.

### A0 — Exact event/transaction association

Use `EXACT_EVENT_TRANSACTION` only when the failure is captured while a uniquely identified event/transaction is active and the evidence ties the observed failure to that operation.

Minimum evidence:

- valid current `EventRef`;
- transaction identity when the service uses one;
- active execution/in-flight context;
- observed fault returned by or synchronously attributable to that transaction;
- no evidence that the identity was recycled or invalidated before recording.

Examples:

- an I2C transaction for `EventRef E7` receives `NACKF` and the driver returns the failure before the transaction context ends;
- a bounded software injection targets transaction T9 and the harness records T9's active `EventRef`.

Permitted scope: the specific event/transaction may be quarantined.

### A1 — Service-only association

Use `SERVICE_ONLY` when event/transaction identity is not defensibly available but one service owns the failing operation and the evidence localizes the failure to that service.

Minimum evidence:

- service identity is valid;
- the service has an active operation or uniquely attributable failure context;
- event identity is absent/invalid/ambiguous;
- evidence does not justify narrowing to one event.

Permitted scope: service-level containment/recovery may be considered by Gate C. Specific event-level quarantine is not justified solely by this evidence.

### A2 — Peripheral-only association

Use `PERIPHERAL_ONLY` when the evidence establishes that a peripheral/bus resource is in an observed fault condition but multiple queued operations or services could be responsible.

Minimum evidence:

- valid peripheral/resource identity;
- controller/bus evidence or other direct resource evidence;
- no defensible unique event/service causal link.

Permitted scope: peripheral-level recovery may be considered. Event-level attribution is forbidden.

### A3 — Unknown/ambiguous association

Use `UNKNOWN_AMBIGUOUS` when even service/peripheral localization is not sufficiently defensible.

Permitted scope: only the conservative containment/recovery action justified by Gate C's safety rules. No invented event association.

## 10. Association evidence matrix

| Evidence available | Highest defensible association | Why |
|---|---|---|
| Active `EventRef` + matching transaction + direct transaction error | `EXACT_EVENT_TRANSACTION` | Causal operation context is explicit. |
| Active service + failure, but event/transaction identity unavailable | `SERVICE_ONLY` | Service ownership is known; event causality is not. |
| Peripheral/controller error + multiple candidate events | `PERIPHERAL_ONLY` | Resource is implicated; one event is not identifiable. |
| Timeout with several possible causes and no unique owner | `UNKNOWN_AMBIGUOUS` | Evidence does not support narrowing. |
| Peripheral equality only | **No event-level association** | Sharing a peripheral is not evidence of causality. |
| Event was already terminal/recycled before fault record capture | **Do not use stale event identity** | `EventRef` generation semantics prevent false attribution. |
| Software injection explicitly targeted one active transaction | `EXACT_EVENT_TRANSACTION` | The injection harness itself provides the missing causal link, provided the active identity is valid. |
| Driver logical error before peripheral transaction begins | `SERVICE_ONLY` or `UNKNOWN_AMBIGUOUS` | No peripheral transaction evidence exists. |

## 11. Multiple queued events on one peripheral

The following rule is mandatory:

> **Same peripheral does not imply same fault scope.**

Suppose events `E1`, `E2`, and `E3` all use I2C0.

- If `E2` is executing and receives a directly attributable NACK, `E2` may be quarantined if the transaction context is valid.
- `E1` and `E3` are not automatically quarantined.
- If a bus-level condition is observed while several events are pending and the failing transaction cannot be uniquely identified, association may be only `PERIPHERAL_ONLY`.
- If `E3` is `ORDERED` after `E2`, `E3` remains blocked by the Gate A dependency semantics even though it is not fault-associated.
- If `E1` is independent and its shared-state assumptions remain valid, it may remain eligible.

This distinction is central to the proposed mechanism: quarantine scope is derived from evidence plus dependency semantics, not from peripheral equality.

## 12. Fault record semantic model

The record is fixed-size and statically allocated in the eventual implementation. Gate B defines semantics before byte packing.

Conceptually:

```text
FaultRecord {
    episode_id
    observation_seq
    time_or_tick
    peripheral_id
    fault_class
    association_confidence
    event_ref              // valid only when association justifies it
    transaction_id         // valid only when applicable/justified
    service_id
    evidence_flags
    recurrence_count
    recovery_attempt_count
    last_recovery_outcome
    episode_status
}
```

### Field necessity

| Field | Required? | Later decision/metric supported |
|---|---|---|
| `episode_id` | Yes | Groups repeated observations into one bounded fault episode and supports history. |
| `observation_seq` | Yes | Distinguishes observations within an episode without treating them as new episodes. |
| `time_or_tick` | Yes, bounded | Detection/service-restoration latency and temporal ordering. Exact width is implementation/Gate E work. |
| `peripheral_id` | Yes | Selects resource context and supports peripheral-level association. |
| `fault_class` | Yes | Selects recovery-policy input and enables matched fault-class comparison. |
| `association_confidence` | Yes | Prevents policy from treating ambiguous evidence as precise. |
| `event_ref` | Conditional value | Identifies the quarantined event only when evidence supports event-level association. |
| `transaction_id` | Conditional value | Distinguishes multiple operations within one service/peripheral. |
| `service_id` | Yes | Supports service-level recovery and service preservation analysis. |
| `evidence_flags` | Yes, bounded bitset | Records which observations justify the classification/association. |
| `recurrence_count` | Yes | Supplies bounded recovery-history context. |
| `recovery_attempt_count` | Yes | Enforces/analyses bounded recovery progression. |
| `last_recovery_outcome` | Yes | Provides immediate history for deterministic policy selection. |
| `episode_status` | Yes | Supports terminal detection and recovery-termination measurement. |

The final implementation may combine or encode some fields more compactly, but it may not silently remove semantics required by the policy or experiment.

## 13. Evidence flags

The exact bit assignments are implementation work, but the semantic set should remain small. Candidate flags are:

- `EVIDENCE_ACTIVE_EVENT`
- `EVIDENCE_ACTIVE_TRANSACTION`
- `EVIDENCE_DRIVER_ERROR`
- `EVIDENCE_I2C_NACK`
- `EVIDENCE_I2C_BERR`
- `EVIDENCE_I2C_ARLO`
- `EVIDENCE_TIMEOUT`
- `EVIDENCE_PROGRESS_STALL`
- `EVIDENCE_VERIFICATION_FAILURE`
- `EVIDENCE_RECOVERY_RETRY_FAILED`
- `EVIDENCE_REINIT_FAILED`
- `EVIDENCE_MULTIPLE_CANDIDATE_EVENTS`
- `EVIDENCE_SHARED_STATE_RISK`

Only flags actually observed may be set. A flag representing an inferred root cause must not be added merely because it is plausible.

## 14. Fault episode semantics

### 14.1 Episode start

A new episode begins when a qualifying fault observation occurs and there is no currently open episode for the relevant fault context.

The default matching context is bounded and conservative:

- same service/peripheral context;
- same active transaction/event when still valid, or the same resource context when association is only peripheral-level;
- no intervening verified terminal recovery boundary.

The exact matching function is intentionally left compact and deterministic for Gate C.

### 14.2 Episode continuation

An observation continues the existing episode when it matches the current episode's bounded context and occurs before the episode reaches a terminal outcome.

Examples:

- three consecutive injected NACKs for the same active transaction during one recovery attempt;
- timeout followed by a retry failure for the same retained event;
- repeated no-progress observations while the recovery manager is still handling the same incident.

These increase `observation_seq` and/or `recurrence_count`; they do not create independent episodes.

### 14.3 Episode termination

An episode ends when one of these terminal conditions is reached:

1. **SUCCESS:** the relevant event/service transaction is verified successful after recovery;
2. **DEGRADED:** the service enters its declared safe degraded terminal behavior;
3. **ESCALATED:** local recovery gives control to the declared escalation path;
4. **ABORTED/INVALIDATED:** only if a later implementation defines an explicit safe terminal condition for an invalid test scenario; this must not be used to hide a failed recovery result.

For the core research metrics, SUCCESS/DEGRADED/ESCALATED are the primary terminal outcomes.

### 14.4 New episode after recovery

A later failure after a verified terminal success is a new episode, even if the fault class is identical.

This prevents an old episode from absorbing unrelated future faults indefinitely.

### 14.5 Repeated fault after terminal handling

If a new fault occurs after terminal handling, it receives a new `episode_id`. Historical recurrence information may still be available through the bounded history window, but the new episode is not merged with the old one.

## 15. Quarantine-scope implications

| Association | Default quarantine scope | What is prohibited |
|---|---|---|
| `EXACT_EVENT_TRANSACTION` | Specific event/transaction | Execution of that retained event until permitted transition. |
| `SERVICE_ONLY` | No automatic event-level quarantine; service-level containment may be used | Guessing one event as causal. |
| `PERIPHERAL_ONLY` | Peripheral/resource-level containment may be considered | Treating all events as independent or selecting one event without evidence. |
| `UNKNOWN_AMBIGUOUS` | Conservative scope determined by later safety policy | False precision; unsafe execution under unresolved uncertainty. |

Quarantine scope may be **broader** than the fault label only when broader containment is explicitly justified by dependency/shared-state safety. It may never be narrower than the evidence requires in a way that allows unsafe bypass.

This yields an important distinction:

`fault association scope != dependency blocking scope`

An event can be non-fault-associated but correctly blocked because it depends on quarantined or invalid state.

## 16. Software fault-injection semantics

Software injection is the primary mechanism for deterministic host/firmware experiments.

Each injection command/configuration must specify at least:

```text
InjectionSpec {
    target_event_or_transaction
    fault_class
    trigger_point
    occurrence_index_or_count
    duration_or_timeout_bound
}
```

### Required properties

1. **Deterministic:** the same workload + injection specification produces the same intended fault observation sequence, subject to explicitly measured nondeterminism in the host/firmware environment.
2. **Bounded:** injection cannot allocate unbounded state or run indefinitely.
3. **Isolated:** injection does not silently modify unrelated event metadata.
4. **Observable:** the resulting fault record identifies that the fault was software-injected.
5. **Non-equivalence:** software injection is never reported as proof of an equivalent physical hardware fault.

### Recommended software injection cases

- force NACK-class driver result;
- force a bounded timeout/no-progress result;
- force a BERR/ARLO-class controller error result where the driver abstraction can represent it;
- force repeated failure for a chosen episode;
- force transaction verification failure;
- simulate persistent no-progress across recovery attempts.

The injector should operate at the lowest layer necessary to test the policy while preserving the same event/transaction context used by the real path.

## 17. Physical/protocol fault-injection candidates

These are **candidates, not yet validated methods**.

### Candidate P1 — Controlled peripheral non-response

A safe test fixture may be used to make the selected I2C peripheral unavailable/non-responsive. This could produce an observable NACK or timeout, depending on the exact setup.

**Status:** candidate only. Electrical implementation and reproducibility must be verified after hardware acquisition.

### Candidate P2 — Controlled communication disruption

A safe, current-limited and electrically compliant fixture may be used to disrupt communication in a controlled way sufficient to trigger an observable protocol/no-progress condition.

**Status:** candidate only. No shorting, overvoltage, rail abuse, or uncontrolled contention is permitted.

### Candidate P3 — Controlled device reset/power-state transition

Where the chosen peripheral module exposes a safe reset/power-control mechanism, a controlled state transition may be used to test device unavailability and recovery.

**Status:** candidate only; depends on actual module and fixture.

### Candidate P4 — Multi-master/arbitration scenario

A second master could create arbitration loss, but this adds unnecessary testbed complexity and is not part of the primary experiment unless later justified.

**Status:** deferred.

### Explicit non-candidates

- deliberate supply-rail shorting;
- deliberate overvoltage/overcurrent;
- uncontrolled GPIO contention;
- physical abuse intended to damage a device;
- fault injection whose electrical limits cannot be bounded.

## 18. Hardware evidence limitations

The STM32U575 documentation establishes that the platform exposes relevant I2C status/error facilities and that the device has documented errata. The errata itself is a reason to distinguish controller observations from physical root-cause claims. citeturn3search21turn3search23

The selected BMP280 candidate supports both I2C and SPI, but that establishes interface capability, not the feasibility of every proposed fault injection. citeturn0search29turn0search1

No physical fault class is considered experimentally validated until the actual acquired hardware, wiring, fixture, and observed logs establish repeatability.

## 19. Interaction with the six core invariants

### I1 — Quarantine safety

A fault record can cause an event to become quarantined only through an explicit transition. A quarantined event remains non-executable until release/reclassification is permitted.

### I2 — Fault association

The association-confidence field and evidence matrix directly enforce:

`association precision <= evidence precision`.

Ambiguous evidence cannot be converted into event-level causality merely because a peripheral matches.

### I3 — Service preservation

Exact event association permits selective quarantine while unrelated independent events may remain eligible. Broader association may reduce preservation, but this must be recorded as a consequence of evidence limitations rather than misreported as successful preservation.

### I4 — Dependency safety

Fault association does not override Gate A dependency semantics. An event can be non-fault-associated yet correctly blocked because its predecessor/shared state is quarantined or invalid.

### I5 — Recovery termination

Episode identity, recovery-attempt count, and terminal episode status provide the state needed by Gate C to impose a bounded transition budget.

### I6 — Bounded resource usage

The fault record, evidence flags, episode identity, and recurrence state are fixed-size semantic objects. The implementation must use static storage and fixed maxima; no runtime heap growth is introduced by Gate B.

## 20. Explicit rejected assumptions

1. **"NACK means the peripheral is broken."** Rejected. NACK establishes non-acknowledgement, not root cause.
2. **"Timeout means the peripheral state machine is locked."** Rejected. Timeout establishes missed progress/deadline, not internal cause.
3. **"BERR means electrical noise."** Rejected. A controller bus-error flag does not identify the physical cause; STM32U575 errata even documents a spurious master-mode bus-error condition. citeturn3search21
4. **"All events using the same peripheral are fault-associated."** Rejected. Peripheral equality is not a dependency or causal relation.
5. **"Repeated observations are separate fault episodes."** Rejected. Repetition belongs to episode/history semantics until a terminal boundary occurs.
6. **"Persistent failure proves an internal peripheral lockup."** Rejected. Persistence supports a stronger recovery decision but does not prove internal failure location.
7. **"Software-injected faults are hardware faults."** Rejected. They are deterministic test stimuli.
8. **"A retained queued event is preserved."** Rejected by Gate A's preservation definition; preservation requires correct verified execution.
9. **"ARLO should be a normal primary fault injection."** Rejected for the minimal single-master testbed unless later evidence justifies a multi-master setup.
10. **"A service verification failure automatically implicates the peripheral."** Rejected. The failure may be service/driver-level or ambiguous.

## 21. Acceptance criteria

Gate B is accepted only if all of the following are true:

- [x] Fault taxonomy is finite and small enough for matched experiments.
- [x] Fault classes are separated from recurrence/persistence history.
- [x] Direct observations are distinguished from inference and unknown physical cause.
- [x] Deterministic software-injection semantics are defined.
- [x] Physical/protocol injection candidates are explicitly marked unvalidated until hardware feasibility is demonstrated.
- [x] Unsafe electrical fault injection is excluded.
- [x] Fault-record semantics are fixed-size and every field has a later purpose.
- [x] Event/service/peripheral/ambiguous association levels are operationally defined.
- [x] Multiple queued events sharing one peripheral are handled without false event-level attribution.
- [x] Episode boundaries and recurrence semantics are defined.
- [x] Quarantine implications are mapped to association confidence.
- [x] All six core invariants are addressed.
- [x] Historical baseline material is preserved and its refinements/rejections are documented.
- [x] No physical measurements or hardware validation are claimed.

## 22. Unresolved questions transferred to Gate C

Gate B intentionally transfers these policy questions rather than answering them prematurely:

1. What minimum subset of fault context actually changes the recovery action?
2. What exact retry budget should each observed fault class receive?
3. When should repeated failure trigger `REINIT_OR_RESET`, `DEGRADE`, or `ESCALATE`?
4. What exact recovery-history window is sufficient without unnecessary RAM cost?
5. What precise action is safe for each association-confidence level?
6. When is peripheral-level containment required by shared-state/dependency safety?
7. What degraded-mode semantics are valid for each reference service?
8. What is the exact bounded recovery transition budget?
9. How should the scheduler interleave independent eligible work during recovery?
10. Which STM32U575 I2C error indications are available in the exact chosen driver configuration, and which should be normalized into the semantic fault classes above?
11. Are driver reinitialization and peripheral reset experimentally distinct on the final U575 implementation?
12. Which physical fault-injection candidate is safest and most reproducible after hardware acquisition?

## 23. Gate B decision

### **ACCEPTED — Gate B complete at the semantic/design level.**

The project may now proceed to **Gate C — Recovery Policy + Bounded State Machine** in a new chat.

This acceptance does **not** mean:

- physical fault injection has been validated;
- the STM32U575 board has been acquired;
- the fault taxonomy is a complete taxonomy of all possible embedded failures;
- causal physical fault identification is solved;
- the recovery policy is already proven effective.

It means the project now has a bounded, evidence-aware fault model sufficient to derive the next recovery-policy gate without silently manufacturing causal precision.

## 24. Sources consulted for Gate B

Primary/official sources used for platform/protocol semantics:

- STMicroelectronics, **RM0456 STM32U5 series Arm-based 32-bit MCUs reference manual**, I2C chapter and status/timeout definitions. citeturn3search23turn3search2
- STMicroelectronics, **ES0499 STM32U575xx/STM32U585xx device errata**, including the documented master-mode spurious bus-error condition. citeturn3search21
- Bosch Sensortec, **BMP280 datasheet/product documentation**, confirming I2C and SPI interfaces. citeturn0search29turn0search1

These sources establish device/protocol capabilities and documented observations. They do not establish novelty or patentability of the proposed recovery mechanism.
