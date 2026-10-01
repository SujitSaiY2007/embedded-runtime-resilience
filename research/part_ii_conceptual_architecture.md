# Part II Conceptual Architecture — K.4 Lock

Checkpoint: K.4 — Novelty Re-Research + Conceptual Architecture Lock
Date: 2026-10-01
Status: Conceptual architecture locked; implementation deferred to K.5+

## 1. Locked chain

**UI -> Virtual Embedded System -> SAME C Reference Runtime -> Recovery Decision -> Trace/Evidence -> UI**

The C reference runtime is the sole authority for recovery semantics.

## 2. Component responsibilities

### UI
Owns scenario selection, deterministic stimulus selection, start/reset controls, visualization of virtual state, queue/quarantine/dependency state, recovery action display, verification display, and trace presentation.

Does not own fault association, recovery policy, retry counters, quarantine eligibility, dependency semantics, verification rules, release/degrade/escalation decisions, or an alternative recovery algorithm.

### Virtual Embedded System
Owns deterministic workload/event environment, virtual event queue/scheduler environment, virtual I2C/SPI/UART state, deterministic fault injection, virtual peripheral responses, sequence progression, and exposure of dependency/order context.

Does not own recovery-policy decisions, evidence-bounded association, recovery ladder semantics, quarantine decisions, or final verification/release/escalation.

### C Reference Runtime
Owns Gate A EventRef/dependency semantics, Gate B evidence-bounded fault association, event quarantine/retention, bounded context/history, Gate C recovery ladder, recovery action selection, episode bounds, verification, release/degrade/escalation, and authoritative state transitions.

### Recovery Decision
This is a conceptual presentation stage, not a second software component. It is the observable result of the existing C runtime policy path.

### Trace/Evidence
Owns run/scenario identity, EventRef, fault observation identity, association result, precision/ambiguity, recovery episode/action index, action/outcome, quarantine/preservation/blocking effects, verification result, terminal state, correctness/evidence flags, and ordering information sufficient to reconstruct the decision path.

The trace layer records runtime outputs; it does not infer a policy decision.

## 3. Authority rule

Exactly one recovery-policy authority exists:

> The existing ISO C11 reference runtime.

If another layer needs behavior not exposed by the runtime, K.5 must define an interface around the existing semantics rather than recreating them.

## 4. Conceptual boundaries

### B1 — UI -> Virtual System
Input: scenario identifier, workload selection, deterministic fault-stimulus request, reset/start command.
Output: acknowledgement and run identifier.

The UI cannot pass a desired recovery action.

### B2 — Virtual System -> C Runtime
Input: event admission/dispatch context, EventRef/dependency information, peripheral observation, fault evidence, bounded history/state required by the frozen runtime interface, deterministic sequence information.
Output: runtime transition, association result, quarantine/retention decision, recovery action, verification/result, terminal outcome, trace records.

Exact signatures and serialization formats are K.5 work.

### B3 — C Runtime -> Trace/Evidence
The runtime produces authoritative lifecycle and decision events. Trace preserves identity and ordering so the sequence fault observation -> association -> quarantine -> action -> verification -> release/escalation can be reconstructed without inference.

### B4 — Trace/Evidence -> UI
Read-only evidence: run metadata, current state, event/queue/quarantine snapshot, recovery decision, trace timeline, verification outcome, final disposition.

The UI renders this information and does not modify policy state.

## 5. Conceptual scenario flow

1. UI requests a predefined scenario.
2. Virtual system initializes deterministic workload/peripheral state.
3. Virtual system emits the specified event/fault stimulus.
4. C runtime observes fault evidence.
5. C runtime determines evidence-bounded association.
6. C runtime applies frozen quarantine/dependency semantics.
7. C runtime selects the bounded recovery action using existing context/history.
8. Virtual system models execution of that action.
9. C runtime verifies the result.
10. C runtime releases retained work, degrades, or escalates according to frozen policy.
11. Trace records authoritative transitions.
12. UI renders state and trace.

Step 8 is environmental execution, not a second recovery policy.

## 6. Scenario authority

Scenarios are declarative demonstrations of already-defined Gate A-E semantics. They may specify workload, dependencies, peripheral, fault stimulus, expected observation and expected trace class. They may not contain hidden alternative recovery logic.

## 7. Evidence boundary

The demonstrator may establish end-to-end software execution of the existing reference mechanism, trace coherence, deterministic replay if implemented, visible quarantine/preservation semantics, and bounded recovery decision flow.

It cannot establish STM32U575 timing, physical peripheral behavior, electrical fault response, target MPU behavior, target RAM/Flash usage, or hardware performance.

## 8. K.5 architecture invariants

1. Single policy authority: C runtime only.
2. No UI policy.
3. No simulator policy.
4. Deterministic stimulus.
5. Stable run/EventRef/episode identity.
6. Trace causality: displayed decisions map to runtime-produced trace events.
7. No hidden state affecting runtime policy context.
8. Bounded capacities remain explicit.
9. Displayed causal precision cannot exceed runtime evidence precision.
10. Gates A-E remain unchanged.

## 9. K.5 handoff

K.5 must turn these conceptual boundaries into implementable contracts for the virtual scheduler/environment, I2C/SPI/UART models, deterministic fault injection, C-runtime adapter, UI-facing state/trace schema, and baseline interface boundary.

K.5 must not implement the simulator or UI and must not redesign the recovery policy.
