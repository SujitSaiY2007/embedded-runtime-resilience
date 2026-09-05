# Project State

**Project:** Embedded Systems — Missed Opportunities in Simpler Areas  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Status:** Gates A-E complete at their respective semantic/design/protocol levels; Minimal Reference Implementation checkpoint complete at host level.  
**Project mode:** Solo software-dominant embedded-systems research project.

## Frozen development topic

**Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

Short title: **Zero-Heap Context-Aware Peripheral Recovery with Event Quarantine**

## Research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral fault context and short recovery history to select a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining acceptable CPU/RAM/Flash overhead on an MPU-enabled resource-constrained MCU?

## Platform direction

**STM32U575ZI / NUCLEO-U575ZI-Q**, with I2C primary, SPI secondary, and UART/USART diagnostic/control. Hardware acquisition/physical validation is not assumed or claimed.

## Gates A-E

- **Gate A — COMPLETE:** `EventRef={slot_id,generation}`; explicit INDEPENDENT/ORDERED/COUPLED dependencies; FIFO admission versus eligibility-driven execution; retained non-executable quarantine; preservation as verified execution.
- **Gate B — COMPLETE:** evidence-bounded I2C fault taxonomy; four association levels; `association precision <= evidence precision`; recurrence/persistence as episode/history attributes; deterministic software injection as primary stimulus.
- **Gate C — COMPLETE:** minimum policy context; actions RETRY/REINIT_OR_RESET/DEGRADE/ESCALATE; exact ladder `T1 RETRY #1 -> T2 RETRY #2 -> T3 REINIT_OR_RESET -> T4 terminal`; `MAX_RECOVERY_ACTIONS=4`; P0-P4 ablations.
- **Gate D — COMPLETE:** quarantine, association, preservation/blocking, dependency, termination, resource, EventRef, release, transaction, and decision-table properties specified. The prior host abstract audit covered 33,792 bounded policy contexts; this remains model-level evidence.
- **Gate E — COMPLETE:** P0-P4 comparison set, W01-W14 workloads, deterministic fault schedules, `QMAX=16`, `XMAX=4`, `DMAX=4`, `EPMAX=1`, trace identifiers, metrics, reset/repetition rules, and evidence boundaries frozen.

Gates A-E form one chain: Gate A defines what work exists and what may execute; Gate B defines what failed and how precisely it can be associated; Gate C maps bounded context/history to recovery; Gate D states the correctness obligations; Gate E turns those obligations into reproducible comparisons and measurements.

## Minimal Reference Implementation checkpoint

Implemented under `reference/` as a deliberately small ISO C11 host reference with CMake.

### Fixed implementation decisions

- `ACTIVE_MAX = QMAX + XMAX = 20` fixed event slots.
- Normal queue stores slot IDs only; quarantined events remain in the same event-slot pool and leave the normal queue, so no event is double-counted.
- `DMAX=4` fixed dependency entries per event.
- `EPMAX=1` fixed active recovery episode; a second simultaneous episode returns an explicit bounded outcome.
- `EventRef` generation is 8-bit; it starts at 1 and fails closed rather than wrapping after `UINT8_MAX`.
- Scheduler scans queue admission order and selects the first event satisfying the Gate A dispatchability predicate.
- Exact event/transaction recovery is implemented. Broader association scopes never fabricate an event target; unsupported broader-scope recovery fails closed to terminal escalation in this minimal prototype.
- `PolicyDecision` is a fixed-size value result.
- Fault injection is deterministic and keyed by `EventRef` plus recovery action index.
- Trace records contain run/trace/episode identity, EventRef, transaction ID, observation sequence, action index, lifecycle state, action, outcome, and correctness; CSV serialization uses fixed local buffers and `write()`.

### Host verification performed

Local C11/CMake build completed successfully. `ctest` passed the W01-W14 correctness suite, bounded recovery test, policy-property checks, trace-metadata checks, and static-accounting checks.

Current host C-layout accounting:

- `sizeof(Runtime) = 8164` bytes
- `sizeof(EventSlot) = 84` bytes
- `sizeof(TraceRecord) = 24` bytes
- fixed trace pool = `6144` bytes

A source/symbol allocator audit found no `malloc/calloc/realloc/free` references in the reference implementation and no unresolved allocator symbols in the test executable.

These are host/reference observations only. They are **not** STM32U575 RAM/Flash/timing measurements.

## Current boundary

The smallest testable host/reference checkpoint is complete. Do not automatically proceed to full MCU integration or physical fault injection in the same phase merely because host tests pass.

## Explicit non-claims

No MCU performance/resource measurement, physical fault validation, energy measurement, statistical significance, generalization, novelty, or patentability claim is established by the host prototype.

## Continuation

`CURRENT_HANDOFF.md` contains the exact next continuation point. `research/phase1_reference_implementation_design.md` records implementation decisions. `reference/tests/canonical_workloads.md` maps W01-W14 to executable tests. Historical Gate A-E artifacts remain normative and preserved.
