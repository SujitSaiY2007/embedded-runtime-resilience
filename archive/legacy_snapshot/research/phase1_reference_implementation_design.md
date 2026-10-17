# Phase 1 — Minimal Reference Implementation Decisions

**Status:** Accepted implementation checkpoint  
**Date:** 2026-09-05

This document records implementation-level decisions derived from the frozen Gates A-E contracts. It does not amend those gates.

## Decisions

### I-001 — ISO C11 host reference with CMake
The reference implementation uses ISO C11 and a small CMake build with strict warnings. No RTOS or MCU SDK is included. The host model is the executable semantic reference, not MCU evidence.

### I-002 — Single event-slot pool
Use `ACTIVE_MAX = QMAX + XMAX = 20` fixed `EventSlot` records. This provides a bounded active domain while preserving separate normal-queue and quarantine counts.

### I-003 — Queue stores slot IDs only
The normal queue is `uint8_t queue[QMAX]`. Quarantine removes the event's slot ID from the normal queue but retains the same `EventSlot`. No second event record is created, preventing double-counting.

### I-004 — Fixed dependency storage
Each event embeds exactly `DMAX=4` dependency entries. Dependencies are explicit references with `ORDERED` or `COUPLED` semantics; peripheral equality never creates a dependency.

### I-005 — EPMAX=1
The normative reference prototype stores exactly one active `FaultContext`. A second simultaneous episode returns `OUTCOME_EPISODE_FULL` rather than allocating hidden state. Multiple quarantined slots can exist up to `XMAX`, but only one episode is actively controlled.

### I-006 — 8-bit generation, fail-closed wrap
`EventRef` uses an 8-bit `slot_id` and 8-bit `generation`. Generation starts at 1 and increments on reuse of the same slot. The implementation refuses generation wrap after `UINT8_MAX` and reports a bounded failure instead. This is a conservative prototype policy, not a claim that 8 bits is universally optimal.

### I-007 — Deterministic first-eligible scheduler
The scheduler scans the queue in admission order and selects the first event satisfying the Gate A dispatchability predicate. Thus FIFO remains an admission property while independent eligible work can bypass blocked/quarantined work.

### I-008 — Exact-target recovery only in the minimal prototype
The executable recovery path supports exact event/transaction targeting. For broader association levels, it never invents an event target; if a safe broader recovery operation is not implemented, the prototype fails closed to terminal escalation. This is an implementation boundary, not a change to Gate B/C semantics.

### I-009 — Fixed policy result
`PolicyDecision` is returned by value and contains action, target scope, quarantine/retry/release flags, terminal flag, attempt index, and reason code. No dynamic policy objects are used.

### I-010 — Deterministic fault injection
`FaultInjection` is fixed-size and targets a specific `EventRef` plus action index. The schedule can deterministically force initial or recovery failure. It does not change after observing results.

### I-011 — Structured fixed-buffer trace
Trace records contain `run_id`, monotonic `trace_seq`, `fault_episode_id`, `event_ref`, transaction ID, `observation_seq`, `action_index`, lifecycle state, action, outcome, and correctness. Runtime metadata also records workload and fault-schedule IDs. CSV serialization uses fixed local buffers and `write()`.

### I-012 — Host-only resource accounting
The current host build reports `Runtime=8164` bytes, `EventSlot=84` bytes, `TraceRecord=24` bytes, and a 6144-byte trace pool. These are host C-layout measurements only and must not be presented as STM32U575 RAM/Flash measurements.

### I-013 — Zero-heap implementation audit
The reference source contains no allocator calls. A symbol audit of the test executable found no unresolved `malloc`, `calloc`, `realloc`, or `free` symbols. This demonstrates the reference's own allocation discipline; it is not a claim about the host C library generally.

### I-014 — W01-W14 executable checkpoint
The first correctness suite directly exercises the frozen Gate E W01-W14 workload IDs, plus recovery-bound, policy-property, trace-metadata, and static-accounting checks.

## Verification result

CMake build and CTest pass in the development environment. The result is host/reference evidence only.

## Deferred

MCU integration, physical fault injection, MCU timing/resource measurements, energy measurement, large-scale performance campaigns, and final physical testbed work remain deferred to later checkpoints.
