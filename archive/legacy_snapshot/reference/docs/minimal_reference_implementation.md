# Minimal Reference Implementation

Status: implementation checkpoint after Gates A-E. This document records implementation-level choices without modifying the frozen semantic contracts.

## 1. Host reference toolchain

- Language: ISO C11.
- Build: CMake 3.16+ with a conventional C compiler.
- Compiler flags: `-std=c11 -Wall -Wextra -Werror -pedantic`.
- No RTOS and no MCU SDK dependency.
- Host code is the executable reference; it is not MCU measurement evidence.

## 2. Fixed storage layout

The reference uses one fixed `EventSlot[ACTIVE_MAX]` pool where `ACTIVE_MAX = QMAX + XMAX = 20`.

- Normal queue: `uint8_t queue[QMAX]` contains slot IDs only.
- Quarantine retention: quarantined events remain in the same `EventSlot` pool and are removed from the normal queue. No duplicate event record is created.
- `quarantine_count` tracks retained quarantined slots and is bounded by `XMAX`.
- Dependencies: `DependencyEntry[DMAX]` is embedded in every event slot.
- Transactions: a fixed `TransactionRecord[QMAX]` array is reserved; no heap objects exist.
- Recovery: exactly one `FaultContext` is retained (`EPMAX=1`).
- Trace: fixed `TraceRecord[TRACE_EVENT_CAP]` storage.

This makes storage auditable and avoids double-counting a quarantined event in both queue and quarantine storage.

## 3. Event identity and generation policy

`EventRef = {slot_id, generation}`.

`slot_id` is 8-bit because the active domain is 20 slots. `generation` is 8-bit in the reference prototype.

Generation starts from 1 and increments on reuse of the same slot. Zero is avoided. The implementation refuses to wrap an 8-bit generation: once a slot reaches `UINT8_MAX`, further reuse of that slot fails closed with `OUTCOME_STALE_REF`.

This is intentionally conservative. It does not claim that 8 bits is universally sufficient; it establishes a concrete finite policy for the reference prototype and exposes the wrap boundary rather than silently allowing ABA ambiguity.

## 4. Scheduler rule

The scheduler performs a deterministic scan from queue index 0 through `queue_count-1` and selects the first event that satisfies the Gate A dispatchability predicate.

A queued event is marked `ELIGIBLE` when dependencies are currently satisfied. A quarantined/fault-associated event is never ordinary-dispatchable.

This preserves FIFO admission order while allowing an eligible independent event to bypass an earlier blocked/quarantined event.

## 5. Quarantine model

A fault-associated exact event transitions to `QUARANTINED` and is removed from the normal queue, but its `EventSlot` remains active. Recovery therefore retains the event without a second record.

Only an authorized recovery operation may execute the quarantined event. A successful recovery operation verifies the event/service and then returns the event to the queue as `QUEUED`; ordinary scheduler eligibility is evaluated again before completion.

Association levels below exact event/transaction do not fabricate an event-level quarantine target. In this smallest prototype, unsupported broader-scope recovery fails closed to terminal escalation rather than inventing an event target.

## 6. Dependency model

Each event has at most four explicit incoming dependency entries. `ORDERED` dependencies require the referenced event to reach the declared acceptable state. `COUPLED` dependencies require the referenced event to be verified and its shared state valid.

Peripheral equality is never used to construct a dependency.

## 7. Episode model

`EPMAX=1` is normative for the reference prototype. A second simultaneous recovery episode returns `OUTCOME_EPISODE_FULL` rather than allocating hidden recovery state.

Multiple retained quarantined event slots are representable up to `XMAX`, but only one recovery episode is active. This is deliberate and is exercised by W10 as an explicit capacity boundary rather than treated as a hidden capability.

## 8. Policy interface and bound

`PolicyDecision policy_decide(const Runtime *, const FaultContext *)` is a fixed-size value result containing action, target scope, quarantine/retry/release flags, terminal flag, attempt index, and reason code.

The integrated P4 ladder is:

`RETRY #1 -> RETRY #2 -> REINIT_OR_RESET -> DEGRADE/ESCALATE`.

At most three non-terminal recovery actions are counted; the fourth action is terminal handling. Therefore the Gate C maximum of four recovery-action transitions is preserved.

## 9. Fault injection

`FaultInjection` is a fixed record. Injection is deterministic and keyed by `EventRef` plus action index. The schedule can fail an initial execution or a selected recovery action without changing the workload after observing a result.

The injected classes map to the Gate B semantic taxonomy. Software injection represents repeatable stimulus, not physical fault validation.

## 10. Trace representation

`TraceRecord` contains stable `run_id`, monotonic `trace_seq`, `fault_episode_id`, `event_ref`, transaction ID, `observation_seq`, `action_index`, lifecycle state, action, outcome, and correctness fields. Runtime metadata also carries workload and fault-schedule IDs. `trace_write_csv()` emits a deterministic CSV stream using fixed local formatting buffers and `write()`. No dynamic trace objects are required.

## 11. Zero-heap evidence

The reference implementation contains no allocator calls and all runtime state is embedded in `Runtime` or caller-owned fixed records.

The correctness test executable uses only fixed automatic/static storage. Host-library behavior is not presented as an MCU heap measurement.

Recommended audit commands:

```text
grep -RInE '\\b(malloc|calloc|realloc|free)\\b' include src tests
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
nm -u build/reference_tests | grep -E 'malloc|calloc|realloc|free'
```

## 12. Static resource accounting

The current host build reports `Runtime=8164` bytes, `EventSlot=84` bytes, `TraceRecord=24` bytes, and a fixed trace pool of `6144` bytes. These are host C-layout measurements only.

No MCU RAM/Flash figure is inferred from them. MCU footprint measurement remains a later physical-build task.
