# Professor-Facing Software Demonstrator (K.7)

This directory contains the professor-facing front-end demonstrator for the research project:

> **Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware**

---

## Architectural Authority

The demonstrator follows the locked K.4/K.7 architecture:

```text
Professor-Facing UI (demo/index.html)
       ↓ (HTTP / Live Bridge)
Virtual Embedded System Adapter (reference/virtual/)
       ↓ (C Function Call Boundary)
SAME C Reference Runtime (reference/src/ref_runtime.c)
       ↓ (Authoritative Decision)
policy_decide() & runtime_apply_policy()
       ↓ (Verified Execution)
Correlated Inspectable Trace
```

**Critical Rule:** The UI is purely an inspectable presentation and interactive control layer. It does **NOT** select recovery actions, alter scheduling rules, fabricate EventRefs, or implement an alternative recovery state machine. All state, transitions, decisions, and traces originate strictly from the ISO C11 reference runtime.

---

## Running the Demonstrator

### Mode 1: Live C Backend Mode (Recommended for Live Demonstrations)

Runs a lightweight local server that executes the compiled C binary (`virtual_demo_cli.exe`) on demand for every step and click:

1. Ensure the C reference target is built:
   ```powershell
   cmake --build reference/build --config Debug
   ```
2. Start the local demonstrator server:
   ```powershell
   python demo/server.py
   ```
3. Open `http://localhost:8000/` in any modern web browser.
   The header badge will indicate `LIVE C BINARY` in green.

### Mode 2: Standalone Offline Mode (Zero Setup)

Double-click or open `demo/index.html` directly in any web browser (Chrome, Firefox, Edge, Safari):

* **No server or installation required.**
* Loads the authoritative pre-exported scenario data (`demo/scenarios_data.json`) generated directly from `virtual_demo_cli --export-all`.
* The header badge will indicate `STANDALONE OFFLINE`.

---

## Demonstrated Scenarios

| Scenario | Title | Research Invariant Demonstrated |
| :--- | :--- | :--- |
| **S01** | Independent Preservation Under Fault | Non-faulted independent tasks on I2C0 and UART0 continue to execution while faulted task is quarantined and recovered. |
| **S02** | Ordered Dependency Blocking | Ordered successor (`DEP_ORDERED`) is blocked in `ST_QUEUED` while predecessor recovers; independent task completes. |
| **S05** | Retry Success & Trace Correlation | Single transient I2C NACK resolved by retry; illustrates 1:1 wrapper-to-runtime trace sequence linkage. |
| **S06** | Bounded Progression to Restart | Repeated I2C timeout exhausts retry attempts (1 & 2), escalating deterministically to `ACT_RESTART` (attempt 3). |
| **S08** | Ambiguous Association Isolation | Unmapped environmental fault safely escalates without fabricating a synthetic `EventRef` (target remains `INVALID_SLOT`). |
| **S14** | Mixed Dependencies & Deterministic Replay | Chained dependencies (ordered + coupled) with transient recovery; produces identical 32-bit replay digest (`0x9185616C`). |

---

## Inspectable Evidence Features

1. **Pipeline Stage Indicator:**
   Visual flow from Virtual Environment → Event Admission → Fault Observation → `policy_decide()` → `runtime_apply_policy()` → Verify & Release → Correlated Trace.
2. **Active Event Slots & Gate A Dispatchability:**
   Inspects `EventRef={slot_id, generation}`, state, criticality, quarantine flag, and whether the event is dispatchable under Gate A.
3. **Recovery Policy Context:**
   Live display of the fault episode, attempt index, and the exact `PolicyDecision` action chosen by `policy_decide()`.
4. **Interactive Trace Correlation Dual-View:**
   * **Wrapper Trace:** Records scenario events, timestamps, and the corresponding runtime trace sequence range (`rt_first`..`rt_last`).
   * **Runtime Trace:** Authoritative `TraceRecord` output directly from `ref_runtime.c`.
   * **Correlation Highlighting:** Hovering or selecting any wrapper trace row highlights the exact runtime trace rows executed for that event.

---

## Evidence Boundary

The software demonstrator demonstrates the correctness, determinism, and inspectability of the software policy. It does **not** establish STM32U575 physical RAM/Flash/timing measurements, physical MPU containment, electrical fault tolerance, statistical superiority, or patentability.