# K.9.2 — P4 Advantage & Novelty Investigation Design Lock
Date: 2026-10-01
Repository: `SujitSaiY2007/embedded-runtime-resilience`
Branch: `exp`
Starting HEAD: `50951ed32fd7ba7ee27ffdb4d9cb9658e4322062`
Status: **COMPLETE — design/audit checkpoint**

## 1. Continuity Check

- Part II remains active.
- K.1-K.8 are historical completed checkpoints.
- K.9 is historically CLOSED and remains unchanged.
- K.9.2 is inserted between K.9 and K.10 by Decision D-112.
- Gates A-E remain frozen and normative.
- The C reference runtime remains authoritative.
- K.10 is not executed by this record.

## 2. Starting-state audit

The latest `exp` head was verified before K.9.2 changes: `50951ed32fd7ba7ee27ffdb4d9cb9658e4322062`.

The K.9 closure remains `d1e0dcba836320526686806980572ef3a5a6a5cb`. The current branch is ahead through continuity/design commits; this does not reopen K.9.

Runtime integrity was checked by comparing Git blob SHAs against the K.9 closure:

| File | K.9 SHA | Current SHA | Result |
|---|---|---|---|
| `reference/src/ref_runtime.c` | `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81` | `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81` | UNCHANGED |
| `reference/include/ref_runtime.h` | `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198` | `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198` | UNCHANGED |

No Gate A-E modification was made.

## 3. Existing measurement audit

### Measurable now
- terminal outcomes and outcome classes;
- recovery attempt/action sequences;
- authoritative trace records and logical transition counts;
- stale-reference and association outcomes;
- deterministic replay/digest equality;
- existing static host/reference accounting;
- virtual scenario step counts.

### Partially measurable
- work preservation/disposition;
- fault containment;
- escalation quality;
- resource/trace cost;
- worst-case software-model behavior;
- resilience overhead;
- fault-class adaptability.

These require carefully defined scenario labels or derived metrics before interpretation.

### Not faithfully represented as physical quantities
- MCU cycle latency;
- real fault-to-detection wall-clock time;
- RTOS scheduler context switches;
- interrupt/context-switch overhead;
- energy;
- physical RAM/Flash occupancy;
- electrical/peripheral timing.

Logical trace/step distance may be measured if explicitly named as a software-model metric, but it must never be presented as hardware timing.

## 4. Scenario-space audit

Existing host workloads W01-W14 cover the main Gate-E semantic classes, including dependency, preservation, retry/recovery, degradation, ambiguity, capacity, stale identity, criticality and mixed workloads.

Virtual scenarios S01/S02/S05/S06/S08/S14 provide interactive coverage of independent preservation, ordered blocking, retry success, bounded persistent recovery, ambiguous association and mixed deterministic replay.

The missing differentiating space is not another copy of the basic cases. K.10 must cross:
- fault recurrence/intermittency/alternation;
- prior recovery success/failure/escalation;
- load and queue pressure;
- queue position;
- dependency chains and mixed criticality;
- recovery-resource contention;
- fault during recovery;
- compound history + workload + dependency combinations.

## 5. Required controls

K.10 must contain:
- positive differentiating cases;
- negative controls;
- no-difference controls;
- cases where a baseline can have lower cost;
- cases where P4 incurs additional trace/decision overhead.

No cherry-picking is permitted.

## 6. Attribution locks

1. Exact-event quarantine is shared across P0-P4 and is not a unique P4 benefit.
2. S06 recovery is shared by P1/P2/P3/P4. P2 remains distinct through its history-blind path with digest `0xCDAB2617`.
3. W09/W10 remain `capacity_confounded=1`.
4. Determinism is a validation property unless a controlled policy difference is demonstrated.
5. Host/reference measurements remain software-model evidence only.

## 7. K.10 compound-case priority

Priority cases include persistent fault + repeated history + dependency, persistent fault + high load, intermittent same-resource fault + prior recovery, prior recovery failure + new fault, prior escalation + new fault, ambiguous association + high workload, fault during recovery + dependency, mixed critical/deferable work + persistent fault, repeated fault + contention, and fault after successful reinitialization.

## 8. Novelty search lock

K.10 must search individual elements, pairwise combinations, higher-order combinations and whole-combination disclosures across:
- academic literature;
- patents/patent families;
- standards/technical systems;
- embedded/RTOS/bare-metal implementations;
- peripheral-driver recovery;
- event/message/transaction quarantine;
- safety-critical fault management.

A materially equivalent combination or routine combination of closely linked references is sufficient to weaken the integrated hypothesis. Absence of an identical reference is not proof of novelty.

## 9. Falsification

Valid outcomes include:
- no meaningful P4 advantage;
- conditional advantage;
- advantage with measurable overhead;
- baseline advantage on particular metrics/conditions;
- equivalent behavior;
- inconclusive measurement;
- prior art that weakens or materially discloses the integrated novelty hypothesis.

## 10. Boundary

K.9.2 did not:
- run decisive K.10 experiments;
- perform the final prior-art investigation;
- alter Gates A-E;
- alter `ref_runtime.c/.h`;
- redesign P4;
- add policies/schedulers/recovery engines;
- perform hardware experiments;
- claim superiority, novelty or patentability.

## 11. Antigravity handoff

Antigravity remains the repository execution agent. For K.10 it must start from the exact post-K.9.2 commit, inspect the repository/working tree and continuity files, implement only approved instrumentation, preserve the runtime authority boundary, execute the locked cases and return exact validation/status information.

## 12. Exit

K.9.2 is complete. The next checkpoint is **K.10 — P4 Advantage & Novelty Investigation**. STOP here; do not execute K.10 from this record.
