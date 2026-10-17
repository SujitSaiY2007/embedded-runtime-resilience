# Prior-Art Recheck — 2026-08-27

## Scope
Current lead candidate: Lightweight Runtime Contract and Recovery Framework for Resource-Constrained Event-Driven Embedded Systems.

## Key findings

1. Contract-based resilience is already established. CLAIR (2020) combines component contracts, contract-violation observers, and a lightweight resilience manager that reacts to faults. This overlaps strongly with the broad runtime-contract/resilience-manager concept.

2. Hierarchical contract research already covers non-functional properties such as power and latency, with automatic decomposition and optimization. Generic timing/resource contracts therefore cannot be the novelty anchor.

3. Runtime verification for embedded real-time systems is established literature. Reinbacher, Függer and Brauer (2014) presented online monitoring of temporal specifications for embedded real-time systems.

4. Runtime enforcement is active recent research. 2025 work addresses CPS enforcement using Signal Temporal Logic; 2026 work addresses hybrid-system enforcement using suppression, delay and insertion of events. Therefore monitor-plus-intervention is not novel by itself.

5. A July 2026 automotive-ECU thesis demonstrates continuing work on runtime verification and timing-dependent faults using hardware traces.

6. QNX PLMS 8.0 already documents recovery actions including stop, restart, fault handling, retries and delays. Generic graded task recovery is therefore not a sufficient novelty claim.

7. ZeroKernel/ZeroBits currently advertises a deterministic MCU runtime with execution contracts, fault-aware supervision, safe mode and watchdog support, including ESP32-oriented use. This is particularly close to the intended implementation class.

8. US20090198389A1 describes runtime monitoring for microcontroller-controlled devices, including communication, sensor and cyclic task monitoring, task execution-time bounds, and error elimination rather than only full-system reset.

9. US20230229538A1 / US11726852 covers runtime/hardware watchdog behavior with safe-mode or reset responses.

10. CN119028042A describes fault-sequence/event-history recording.

11. CN122220037A, published 16 June 2026, describes task-state recovery using snapshots and ordered patches. This is not MCU-specific, but shows that generic task recovery/state restoration is also active patent territory.

## Assessment

Current broad-concept novelty risk: HIGH.

The following are already well established individually: runtime monitoring, execution-time contracts, event-sequence monitoring, contract-based resilience, timing/resource monitoring, fault diagnosis, runtime intervention, task restart, safe-mode escalation, watchdog recovery, and fault/event logging.

Do NOT claim novelty for the broad statement: "a lightweight runtime contract and recovery framework for embedded systems."

## Direction to investigate next

If the research family survives, narrow it toward a demonstrably new MCU-specific mechanism, such as a resource-bounded joint representation of event ordering, timing slack and resource pressure combined with a precisely defined minimal-disruption recovery policy. These are hypotheses only.

Next searches should target: lightweight MCU runtime enforcement; joint event-order/deadline/resource contracts; minimal-disruption recovery; severity-based recovery selection; ESP32/ARM Cortex-M runtime resilience; resource-bounded monitors; task-level recovery without full reset.

## Decision

Do not freeze the current candidate. Treat Runtime Contract & Recovery as a research family, not the final invention.
