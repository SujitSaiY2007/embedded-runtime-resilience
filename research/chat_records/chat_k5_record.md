# Chat K.5 Record — Virtual Embedded System Technical Design + Interface Contracts

Date: 2026-10-01  
Checkpoint: K.5  
Base exp commit: 5b7e1c3565a20462629c20c97b13545a1be8f878  
Focused branch: design/k5-virtual-system-contracts-2026-10-01

## Objective

Turn the K.4 conceptual architecture into implementation-ready virtual-system and interface contracts without implementing the simulator/UI or changing the recovery policy.

## Continuity findings

- Part I K.1-K.3 is complete.
- Part II is active.
- K.4 prior-art investigation and conceptual architecture lock are complete.
- The novelty hypothesis remains unresolved.
- Gates A-E remain frozen.
- Existing C runtime is the sole recovery-policy authority.

## Work performed

1. Inspected the current C runtime header/source and reference tests.
2. Confirmed fixed bounds and actual runtime API.
3. Designed deterministic workload/event and virtual scheduler contracts around those APIs.
4. Defined I2C/SPI/UART environmental contracts.
5. Defined deterministic fault-injection mapping to existing FaultInjection.
6. Defined runtime input/output and ownership/lifetime boundaries.
7. Defined UI-facing evidence as a read-only projection.
8. Defined fourteen deterministic scenario contracts for K.6.
9. Identified the adapter limitation: runtime has no peripheral-action callback; K.6 must not silently introduce one.

## Decisions

### K5-D01 — Runtime remains sole policy authority
No simulator/UI recovery logic is introduced.

### K5-D02 — Runtime-generated identity is authoritative
Scenario keys may map to returned EventRefs; environment never assigns EventRef values.

### K5-D03 — Peripheral models are environmental
I2C/SPI/UART state and operation results are environmental inputs/observations.

### K5-D04 — Fault schedules are immutable
Fault timing/outcomes are fixed before execution and cannot adapt to runtime results.

### K5-D05 — Existing C API is the K.6 integration boundary
K.6 uses the current ref_runtime.h API. No recovery API change is authorized by K.5.

### K5-D06 — Environmental recovery-action mirroring is non-authoritative
Because the current runtime lacks an action-execution callback, K.6 may mirror deterministic action success/failure for visualization, but runtime remains authoritative for transition and verification. A future callback redesign requires a separate decision.

## Rejected alternatives

- UI-selected recovery actions.
- Simulator-owned retry counters/action ladder.
- Dependency inference from shared peripheral.
- Synthetic exact EventRef for ambiguous faults.
- Dynamic event/peripheral/history allocation.
- Silent modification of runtime_apply_policy() to call a virtual peripheral.
- Separate baseline recovery engine.

## Assumptions

- Canonical K.6 demonstrator uses current ISO C11 runtime.
- QMAX=16, XMAX=4, DMAX=4, EPMAX=1, MAX_RECOVERY_ACTIONS=4, TRACE_EVENT_CAP=256 remain unchanged.
- K.6 can represent environment state with bounded storage.
- Runtime trace remains authoritative recovery evidence.

## Unresolved questions

1. Whether K.6 needs wrapper trace fields not emitted by TraceRecord.
2. Whether the peripheral mirror can remain one-to-one with runtime deterministic schedules without misleading visual semantics.
3. Whether later hardware validation requires a different physical adapter boundary.
4. Whether P0-P3 ablation limitation can be resolved later; K.5 does not change it.

## Exact K.5 exit state

K.5 is complete at design level when the virtual scheduler/environment, I2C/SPI/UART, deterministic fault injection, C-runtime adapter, runtime schemas, UI authority boundary, EventRef/dependency/order/ownership semantics and S01-S14 scenarios are explicit; no second recovery policy is introduced; Gates A-E remain unchanged; and K.6 has a concrete implementation sequence.

No simulator, UI, hardware, experiment, or recovery-policy code was implemented in K.5.
