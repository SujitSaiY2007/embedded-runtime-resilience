# Phase 0 — Research-Space Decomposition

**Status:** Preliminary map; not a topic-selection document.
**Date:** 2026-08-20
**Scope:** Software-dominant, resource-constrained embedded systems suitable for a solo undergraduate implementation on an existing MCU development board.

## Evidence discipline

This document distinguishes four levels:

- **Established evidence:** directly supported by cited literature, patents, vendor documentation, or implementations.
- **Inference:** reasoned interpretation of the evidence.
- **Hypothesis:** a candidate research proposition that requires systematic prior-art and experimental validation.
- **Speculation:** a possible direction without enough evidence yet.

The existence of prior work in a class is not itself a reason to reject it; the question is whether a narrower, simpler mechanism remains technically differentiated and experimentally defensible.

## Preliminary landscape observations

1. Runtime verification/monitoring on constrained embedded systems is established research, including R2U2, RTLola, past-time temporal monitoring, and contract/runtime-checker work. Therefore, a generic "lightweight runtime contract framework" is not by itself a demonstrated gap. citeturn702651search4turn702651search7turn702651search88
2. Watchdog-based liveness detection and recovery are mature, including windowed watchdogs, hierarchical watchdogs, trusted recovery, and patent activity. A simple watchdog wrapper is therefore a weak novelty candidate. citeturn307031search2turn738776search7turn738776search10
3. Fine-grained/local recovery is also established. Phoenix demonstrated peripheral-failure rollback with lightweight checkpointing; other work studied micro-recovery and recovery-conscious scheduling. citeturn104721search8turn901582search3turn901582search5
4. Power-loss state restoration and crash consistency are established, including TI's CTPL/NVS utilities and recent NVM recovery work. A generic checkpoint/restore mechanism is therefore unlikely to be differentiated. citeturn854213search4turn854213search6turn426253search7
5. Overload management is a mature real-time topic, including event-driven workload scaling and interrupt-overload prevention. A generic overload controller is unlikely to be a strong gap. citeturn874782search1turn699679search1
6. Adaptive sensing/scheduling is active research, including lightweight FSM-based adaptive sampling and newer ML-based methods. A generic adaptive sampler is not enough. citeturn708012academia74turn708012search7

These observations push the project toward **narrow intersections** where a small software mechanism can connect established primitives in a way that addresses an under-served MCU-specific failure mode, with a clear baseline and measurable trade-off.

## Opportunity classes

### OC-01 — Context-aware runtime contracts with bounded local recovery

**Underlying problem:** Embedded applications often have liveness, timing, sequencing, range, and resource expectations, but runtime mechanisms frequently separate detection from recovery or are implemented as coarse watchdog/reset logic.

**Why it may be a missed opportunity:** There is strong evidence for runtime monitoring and for recovery, but the space between a detected local contract violation and the *least-disruptive bounded recovery action* may admit simpler MCU-specific mechanisms. This is a hypothesis, not an established gap. Runtime contract checking itself is well established. citeturn702651search4turn702651search88turn307031search4

**Existing solution families:** Runtime verification, design-by-contract/assertions, task/watchdog monitoring, hierarchical watchdogs, local restart/micro-recovery, graceful degradation. citeturn702651search2turn475644search0turn901582search6

**Do NOT pursue:** "watchdog + heartbeat + reset"; generic temporal-logic monitor; generic assertions; generic hierarchical watchdog; generic micro-reboot.

**Potential research question:** Can a compact event-driven MCU runtime map a small set of contracts to bounded, dependency-aware local recovery actions while reducing unnecessary whole-system resets compared with conventional watchdog-only recovery?

**Constraints:** RAM/Flash budget, deterministic execution, ISR safety, no dynamic allocation, dependency management, bounded recovery time.

**Metrics:** detection latency; false-positive rate; recovery success rate; recovery latency; system availability; whole-system reset count; CPU time; Flash/RAM overhead; deadline impact.

**Solo feasibility:** High for a small prototype if limited to cooperative/event-driven applications and 3–5 contract types.

**Research potential:** Medium–High, contingent on finding a specific unserved combination of contract semantics + recovery policy.

**Patent/novelty potential:** Medium initially; prior-art density is high. Potential depends on a specific recovery-selection mechanism rather than the broad framework.

**Search terms:** `embedded runtime contract local recovery`; `microcontroller contract violation recovery`; `event-driven runtime assurance recovery`; `bounded local recovery embedded`; `runtime monitor recovery action MCU`; `watchdog contract selective restart`; `resource-constrained runtime assurance recovery`.

### OC-02 — Lightweight peripheral-failure recovery without full subsystem restart

**Underlying problem:** I2C/SPI/UART/CAN and sensor/actuator peripherals can enter stuck or error states; common recovery often involves peripheral reinitialization, bus recovery, retries, or larger subsystem restart.

**Why it may be a missed opportunity:** Peripheral failure is real and directly observable, and vendors already provide protocol-specific recovery. A research opportunity may exist in a **generic but very small software recovery state machine** that classifies failures, preserves queued work safely, and chooses among reset/retry/reinitialize/degrade actions while bounding disruption.

**Existing solution families:** Protocol-specific bus recovery, automatic CAN bus-off recovery, peripheral reset/reinit, application callbacks, Phoenix-style peripheral rollback/checkpointing. citeturn104721search3turn104721search4turn104721search8

**Do NOT pursue:** I2C 9-clock recovery alone; CAN bus-off recovery alone; generic retry loops; driver reset wrapper.

**Potential research question:** Can a platform-agnostic, event-driven recovery policy reduce service interruption and inconsistent peripheral state across heterogeneous MCU peripherals compared with vendor-recommended reset/retry sequences?

**Constraints:** protocol semantics, device-specific state, ISR/concurrency interaction, bounded recovery, no assumptions of peripheral idempotence.

**Metrics:** recovery success rate; time-to-service-restoration; lost/duplicated transactions; stale-state incidents; code size; RAM; CPU overhead.

**Solo feasibility:** High if constrained to 2–3 peripheral classes and one MCU family, with fault injection performed by software/hardware test hooks.

**Research potential:** High if the contribution is genuinely cross-peripheral and experimentally validated rather than another single-bus recipe.

**Patent/novelty potential:** Medium–High; protocol-specific prior art is dense, so novelty must be architectural/policy-level and carefully searched.

**Search terms:** `generic peripheral recovery embedded microcontroller`; `cross-peripheral fault recovery MCU`; `I2C SPI CAN unified recovery`; `embedded peripheral state recovery`; `peripheral reset transaction preservation`; `device driver recovery resource constrained MCU`.

### OC-03 — Event-burst containment for event-driven MCU software

**Underlying problem:** Event-driven firmware can become unstable or starve critical work when interrupts/events arrive in bursts. Interrupt overload is a known failure mode. citeturn699679search1

**Why it may be a missed opportunity:** Classic solutions focus on interrupt scheduling, admission, dropping, and queue management. A narrower opportunity may exist in an application-level **event-health mechanism** that detects pathological burst behavior and applies bounded selective suppression/coalescing while preserving critical event semantics.

**Existing solution families:** Interrupt schedulers, selective interrupt dropping/delay, event-driven workload scaling, priority queues, interrupt coalescing. citeturn699679search1turn426253search2turn874782search4

**Do NOT pursue:** basic debouncing; fixed queue limits; priority queue implementation; generic ISR-to-task deferral.

**Potential research question:** Can a tiny event-health policy distinguish benign burst load from pathological producer behavior and preserve critical-event latency with lower overhead than static admission limits?

**Constraints:** event criticality, bounded buffers, ISR execution time, deterministic policy, loss semantics.

**Metrics:** queue occupancy; overflow/drop rate; critical-event latency; noncritical event loss; CPU utilization; worst-case ISR time; recovery-to-normal time.

**Solo feasibility:** High.

**Research potential:** Medium–High; strongest if tied to a principled contract or adaptive policy rather than a heuristic alone.

**Patent/novelty potential:** Medium; prior art on overload prevention is substantial.

**Search terms:** `event burst containment embedded systems`; `microcontroller event overload control`; `event health monitoring embedded`; `adaptive event admission MCU`; `critical event preservation overload embedded`; `event queue resilience microcontroller`.

### OC-04 — Data-freshness-aware execution for small event-driven embedded pipelines

**Underlying problem:** Periodic execution and rigid scheduling can process stale sensor data or oversample inputs. Data freshness is an active research problem, including recent 2026 work on multi-rate task-chain scheduling. citeturn458745academia141turn708012search5

**Why it may be a missed opportunity:** Small MCU systems often use simple periodic timers despite event-driven sensing. A lightweight runtime policy could suppress work whose inputs have become stale and prioritize computation that can still produce useful outputs.

**Existing solution families:** LET, freshness-aware scheduling, age-of-information scheduling, value-aware scheduling, adaptive sampling. citeturn458745academia141turn708012search5turn708012search8

**Do NOT pursue:** generic EDF; generic adaptive sampling; generic AoI optimization.

**Potential research question:** Can a low-cost freshness gate in an MCU event pipeline improve useful-output rate and reduce wasted computation under bursty sensing workloads compared with fixed-period execution?

**Constraints:** sensor timestamping, bounded queueing, application-specific freshness function, deterministic scheduling.

**Metrics:** useful-output fraction; stale-output rate; end-to-end latency; CPU energy; missed deadlines; queue depth.

**Solo feasibility:** High.

**Research potential:** Medium; active literature means narrowing is essential.

**Patent/novelty potential:** Medium–Low at the broad level; stronger only with a specific embedded mechanism.

**Search terms:** `microcontroller data freshness runtime gate`; `embedded stale data suppression`; `freshness-aware event-driven MCU`; `sensor data age execution embedded`; `stale computation suppression embedded systems`.

### OC-05 — Resource-budget contracts for small embedded applications

**Underlying problem:** MCU software must operate under finite CPU, RAM, queue, stack, and energy budgets. Runtime resource assurance and contracts already have a substantial literature. citeturn935099search1turn935099search2

**Why it may be a missed opportunity:** Existing approaches often target component-based frameworks, adaptive systems, or richer execution environments. A deliberately tiny static-capacity runtime could make resource budgets first-class *runtime safety constraints* for small bare-metal/event-driven applications.

**Existing solution families:** Qinna/resource contracts, resource-aware orchestration, adaptive scheduling, RTOS resource monitors. citeturn935099search0turn935099search1

**Do NOT pursue:** generic memory monitor; CPU utilization gauge; generic quota counters.

**Potential research question:** Can a compile-time declared set of resource budgets be enforced at runtime with bounded overhead and deterministic degradation on a small MCU?

**Constraints:** precise accounting, measurement perturbation, fragmentation, interrupt attribution.

**Metrics:** accounting error; overhead; budget violation detection latency; service preservation; memory/flash overhead.

**Solo feasibility:** High.

**Research potential:** Medium unless a novel enforcement/degradation mechanism emerges.

**Patent/novelty potential:** Medium–Low broad, potentially Medium for a specific enforcement/recovery technique.

**Search terms:** `resource budget runtime enforcement MCU`; `embedded resource contract bare metal`; `bounded resource contract microcontroller`; `runtime memory budget enforcement embedded`; `deterministic resource degradation MCU`.

### OC-06 — Localized software recovery / micro-restart for cooperative event-driven firmware

**Underlying problem:** Whole-device resets are blunt recovery actions; fine-grained recovery has been studied in larger embedded and OS/storage systems. citeturn901582search3turn901582search5turn901582search6

**Why it may be a missed opportunity:** There may be a useful undergraduate-scale contribution in a *discipline for restartable event-driven components* with explicit state boundaries and dependency-safe restart ordering.

**Existing solution families:** micro-reboot, partial restart, recovery-conscious scheduling, component restart, compartment restart. citeturn901582search6turn901582search5turn901582search72

**Do NOT pursue:** simply restarting a task after timeout; generic state reset; process restart on an RTOS.

**Potential research question:** Can explicit restart contracts for event-driven components reduce collateral interruption and recovery time without requiring an RTOS process model?

**Constraints:** state ownership, queued messages, shared peripherals, dependency ordering, restart safety.

**Metrics:** fault containment radius; recovery time; preserved service fraction; queue/message loss; code/RAM overhead.

**Solo feasibility:** High for cooperative firmware.

**Research potential:** Medium–High if the restart contract/dependency mechanism is specific and simple.

**Patent/novelty potential:** Medium; crowded conceptual territory.

**Search terms:** `event-driven microcontroller local restart`; `micro-reboot cooperative embedded firmware`; `restartable component contract MCU`; `dependency-aware restart embedded`; `partial restart event-driven firmware`.

### OC-07 — Lightweight software aging detection and targeted rejuvenation on MCU firmware

**Underlying problem:** Long-running software can degrade through leaks, fragmentation, corruption, or accumulated state. Software aging and rejuvenation are established topics and include embedded-specific work. citeturn351638search1turn351638search6turn351638search7

**Why it may be a missed opportunity:** MCU systems often avoid dynamic allocation precisely because the problem is difficult, but long-lived event-driven firmware can still accumulate queue, buffer, protocol, or state-machine degradation. A tiny, measurable aging indicator tied to selective cleanup may be practical.

**Existing solution families:** periodic rejuvenation, partial rejuvenation, memory/resource monitoring, micro-rejuvenation. citeturn351638search2turn351638search3

**Do NOT pursue:** scheduled reboot; simple periodic memory cleanup; generic leak detection.

**Potential research question:** Can application-state telemetry predict or detect degradation early enough to trigger targeted rejuvenation with less downtime than periodic reboot?

**Constraints:** long-duration experiments, representative aging faults, reliable health metrics.

**Metrics:** time-to-failure extension; false alarms; downtime; recovery cost; memory/CPU overhead.

**Solo feasibility:** Medium because experiments need long runs and realistic aging models.

**Research potential:** Medium–High.

**Patent/novelty potential:** Medium; broad rejuvenation is highly established.

**Search terms:** `microcontroller software aging detection`; `embedded software rejuvenation MCU`; `event-driven firmware aging`; `targeted rejuvenation embedded systems`; `queue state aging microcontroller`.

### OC-08 — Power-loss/crash-consistent state transitions for intermittent MCU tasks

**Underlying problem:** Unexpected power loss can leave persistent application state inconsistent or force full restart from an initial state.

**Why it may be a missed opportunity:** Checkpointing, FRAM utilities, journaling, and crash consistency are mature, but low-cost MCUs with ordinary flash/EEPROM often need simpler application-level transaction semantics. citeturn854213search4turn854213search12

**Existing solution families:** checkpoint/restart, NVM journals, shadow stacks, CTPL, atomic/copy-on-write updates.

**Do NOT pursue:** generic EEPROM wear leveling; simple double-buffer storage; generic journaling filesystem.

**Potential research question:** Can a tiny event-level commit protocol provide sufficient crash consistency for selected application state with less write amplification than generic logging?

**Constraints:** flash erase granularity, endurance, interrupt/power timing, recovery boot time.

**Metrics:** recovery correctness; writes/event; endurance projection; recovery time; RAM/flash overhead.

**Solo feasibility:** High with a controlled power-interruption jig or software fault model.

**Research potential:** Medium; highly established field, so the exact protocol must be differentiated.

**Patent/novelty potential:** Medium–Low broad.

**Search terms:** `microcontroller event atomic commit flash`; `embedded crash consistency application state`; `low write amplification MCU persistence`; `power-loss safe event log microcontroller`; `transactional state update embedded flash`.

### OC-09 — Fault-aware degradation based on dependency and service criticality

**Underlying problem:** Embedded systems can fail hard when a noncritical function blocks or faults, even though a reduced service mode would remain safe/useful.

**Why it may be a missed opportunity:** Graceful degradation is a mature research field, but much of the work addresses distributed, automotive, or component-rich systems. A compact MCU policy for dependency-aware degradation could be experimentally approachable. citeturn979833search2turn979833search3

**Existing solution families:** graceful degradation, fail-operational scheduling, product-family architecture, component prioritization.

**Do NOT pursue:** generic "safe mode"; simple feature disable switches; static fallback state machine without dynamic fault evidence.

**Potential research question:** Can a compact dependency graph plus runtime health score preserve the highest-value service subset under MCU faults with bounded decision cost?

**Constraints:** defining service value; dependency cycles; deterministic transitions; safety assumptions.

**Metrics:** preserved service value; recovery decision latency; energy/CPU overhead; number of unnecessary feature removals; failure containment.

**Solo feasibility:** High.

**Research potential:** Medium–High if narrowly targeted to small event-driven systems.

**Patent/novelty potential:** Medium; broad graceful-degradation concepts are crowded.

**Search terms:** `embedded graceful degradation microcontroller software`; `dependency-aware degradation MCU`; `runtime service degradation embedded`; `event-driven graceful degradation`; `fault-aware feature shedding embedded`.

### OC-10 — Lightweight execution-time anomaly detection for MCU software

**Underlying problem:** Software faults can manifest as abnormal execution time even when conventional checks do not catch them.

**Why it may be a missed opportunity:** Execution-time monitoring is known to detect faults; the specific opportunity is to create a tiny online detector with bounded windows and recovery actions suited to low-end MCUs. citeturn500731search6

**Existing solution families:** WCET/deadline monitoring, runtime verification, hardware execution monitors, fault injection campaigns.

**Do NOT pursue:** generic timer-based deadline checker; static WCET analysis alone; generic profiler.

**Potential research question:** Can low-memory streaming execution-time signatures detect selected control-flow/runtime faults earlier or more cheaply than conventional watchdogs?

**Constraints:** timer resolution, variability in execution time, context dependence, false positives.

**Metrics:** detection coverage under fault injection; detection latency; false positives; CPU/RAM/Flash overhead; recovery outcome.

**Solo feasibility:** High.

**Research potential:** High if a carefully chosen anomaly signature demonstrates meaningful detection beyond watchdogs.

**Patent/novelty potential:** Medium; execution-time monitoring itself is known.

**Search terms:** `execution time anomaly detection microcontroller`; `embedded runtime timing anomaly`; `software fault detection execution time MCU`; `timing signature fault detection embedded`; `lightweight execution monitor microcontroller`.

### OC-11 — Self-verifying event pipelines: detect semantic faults before state corruption propagates

**Underlying problem:** Event-driven firmware can receive semantically invalid sequences even when individual events are syntactically valid; existing queue/driver logic may not enforce cross-event sequencing.

**Why it may be a missed opportunity:** Runtime verification already checks temporal properties, but there may be a smaller application-focused design that compiles a restricted event grammar into a constant-memory checker tightly coupled to recovery/degradation.

**Existing solution families:** temporal logic monitors, state machines, runtime contract checkers, event queue architectures. citeturn702651search7turn702651search88turn557905search5

**Do NOT pursue:** generic FSM implementation; generic temporal-logic runtime monitor.

**Potential research question:** Can a restricted event-grammar monitor detect semantically dangerous event sequences with lower memory and latency than general-purpose runtime verification, while triggering local containment?

**Constraints:** expressiveness vs. compactness; compile-time tooling; event timestamping; recovery semantics.

**Metrics:** detection coverage; memory; CPU overhead; detection latency; number of prevented unsafe transitions.

**Solo feasibility:** High.

**Research potential:** Medium–High.

**Patent/novelty potential:** Medium; exact compilation and containment mechanism would matter.

**Search terms:** `event sequence anomaly embedded firmware`; `finite event grammar runtime monitor MCU`; `semantic event validation microcontroller`; `constant memory event monitor embedded`; `event sequence fault containment embedded`.

### OC-12 — Unified resilience instrumentation for small MCU firmware

**Underlying problem:** Fault-injection and runtime observability frameworks can be too heavyweight for small boards, while ad hoc logging makes resilience experiments difficult to reproduce.

**Why it may be a missed opportunity:** A tiny, deterministic instrumentation layer that records contract violations, timing anomalies, event bursts, recovery actions, and reset causes could make low-end MCU resilience experiments reproducible.

**Existing solution families:** runtime monitors, fault-injection frameworks, vendor debug/monitoring tools, FreeMASTER-like runtime tools. citeturn500731search1turn426253search9

**Do NOT pursue:** generic serial logger; generic profiler; general debugger replacement.

**Potential research question:** Can a bounded telemetry schema capture enough causal context to classify and reproduce resilience failures on low-end MCUs with less overhead than conventional tracing?

**Constraints:** storage limits; instrumentation perturbation; timestamping; host integration.

**Metrics:** trace fidelity; overhead; storage compression; fault classification accuracy; reproducibility rate.

**Solo feasibility:** High.

**Research potential:** Medium; stronger as an enabling research artifact than as the main invention unless a new compression/causal encoding is demonstrated.

**Patent/novelty potential:** Low–Medium.

**Search terms:** `lightweight resilience instrumentation microcontroller`; `embedded fault telemetry low overhead`; `causal tracing MCU firmware`; `fault injection telemetry microcontroller`; `bounded trace embedded resilience`.

## Preliminary ranking

### Strongest candidates for the next prior-art stage

1. **OC-02 — Lightweight peripheral-failure recovery without full subsystem restart**
2. **OC-01 — Context-aware runtime contracts with bounded local recovery**
3. **OC-10 — Lightweight execution-time anomaly detection for MCU software**
4. **OC-11 — Self-verifying event pipelines**
5. **OC-06 — Localized software recovery / micro-restart for cooperative event-driven firmware**
6. **OC-03 — Event-burst containment for event-driven MCU software**

### Candidates currently lower priority

- **OC-04:** scientifically strong but crowded by active freshness/scheduling literature.
- **OC-05:** useful engineering problem but runtime resource contracts have significant prior work.
- **OC-07:** researchable but slow to validate experimentally and crowded by software-aging literature.
- **OC-08:** technically important but prior art in crash consistency/NVM is extensive.
- **OC-09:** broad graceful degradation is mature; requires a sharper MCU-specific mechanism.
- **OC-12:** valuable as infrastructure, but weaker as a standalone invention candidate.

## Cross-cutting hypothesis emerging from the map

The strongest region may be **small, explicit, event-driven resilience policies that connect detection to a bounded, local recovery or degradation action**. The likely differentiator is not any single primitive (watchdog, contract, queue, state machine, retry, restart), but a narrowly specified policy that combines them under MCU constraints and demonstrates a measurable reduction in collateral disruption.

This is still a hypothesis. It must be attacked by candidate-specific prior-art and patent searches before it can be elevated.

## Lead-candidate assessment

The current lead — **Lightweight Runtime Contract and Recovery Framework for Resource-Constrained Event-Driven Embedded Systems** — remains viable as a *research direction*, but its current wording is too broad and overlaps established runtime verification, runtime resource assurance, contract checking, watchdog, and local recovery literature. citeturn702651search4turn935099search1turn702651search88turn901582search6

Therefore:

- **Status:** retain as a lead hypothesis, not preferred-final candidate.
- **Required narrowing:** identify a specific contract class, recovery decision mechanism, or fault domain.
- **Falsification criterion:** if the exact combination can be mapped cleanly to a known framework/patent/product with no meaningful technical delta, reject or redesign it.

## Phase 0 decision

**Decision:** Do not freeze a topic. Advance the six strongest classes into systematic prior-art investigation, beginning with OC-02, OC-01, and OC-10 because they have strong real-world problems, implementable MCU testbeds, measurable baselines, and identifiable technical mechanisms.

## Next-stage investigation protocol

For each shortlisted class, construct an evidence matrix covering:

1. Academic papers/proceedings.
2. Patents/patent families.
3. Standards/specifications.
4. Commercial/vendor implementations.
5. Open-source implementations.
6. Closest competing mechanisms.
7. Explicit differentiating feature(s).
8. Candidate baseline.
9. Experimental fault model.
10. Novelty-risk assessment.

Only after this matrix should a narrowed problem statement be selected.
