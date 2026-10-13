# K.11 — Final Software Synthesis and Hardware-Validation Handoff

**Status:** APPROVED AND CLOSED BY CHATGPT (2026-10-13)  
**Date:** 2026-10-13  
**Working branch:** `feature/k10-4-final-technical-conclusion-2026-10-13`  
**Canonical reference branch:** `exp` at `ab766b47ce7bae2791028cea22b7915f8debc41c`  
**K.10.4 closure ancestor:** `09c17a413c7fb0b48c3c5da4642e24a402edd970`  
**Scope:** Software research synthesis, publication-oriented results structure, professor-facing closure, and a future physical-validation specification.  
**Explicit exclusion:** No physical MCU flashing, physical fault injection, physical measurement, runtime redesign, K.10 experiment reruns, legal opinion, branch merge to `exp`, or synchronization of `main`.

---

## 1. Executive conclusion

The completed K.10 campaign provides deterministic host/reference-model evidence for a **bounded integrated recovery-policy hypothesis**, not universal superiority and not physical-MCU validation. The matched campaign comprised 16 case families (CF01–CF16), five policy variants (P0–P4), and five repetitions: 400 executions. The recorded variance was zero in that deterministic model.

The strongest supported positive results are the bounded P4 advantages in CF04 and CF07 (fail-closed handling of ambiguous association and avoidance of an unclosed episode that blocks subsequent recovery) and CF05 (finite termination of the recovery ladder under cascading recovery faults). These results must always be reported alongside counterevidence: shared exact-event quarantine across P0–P4; six case families with no measured P4 advantage; and the CF16 baseline win in which P2 succeeds in one attempt while P4 requires three.

The prior-art review does not support a broad claim that individual mechanisms are new. K.10.2 recorded no single-reference anticipation across PA-01–PA-10 for the complete integration under review. K.10.3's C1 combination challenge remains substantial and unresolved. The defensible research framing is therefore: **an evidence-bounded integration hypothesis with identified behavioral trade-offs, tested in a deterministic host/reference environment and awaiting independent reproduction and target-MCU validation.** This is not a legal conclusion about novelty, inventive step, non-obviousness, or patentability.

## 2. Scope, authority, and frozen invariants

K.11 consumes the approved K.10.x evidence as-is. It does not rerun or alter the 400-execution matrix. It does not redesign Gates A–E or modify:

- `reference/src/ref_runtime.c`
- `reference/include/ref_runtime.h`
- `policy_decide()`
- `runtime_apply_policy()`
- K.10 experimental source data, run records, or trace records

The five protected Git blob SHAs were verified against the working branch at K.11 startup:

| Protected artifact | Expected and observed Git blob SHA | Result |
|---|---|---|
| `reference/src/ref_runtime.c` | `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81` | Match |
| `reference/include/ref_runtime.h` | `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198` | Match |
| `research/phase1_reference_implementation_design.md` | `b7fb120692756740bc969aa3412acaa89320c188` | Match |
| `research/phase2_k9_methodology_lock.md` | `bd75f2c2c21c3964ec15b338eea99b386eff7aec` | Match |
| `research/phase2_k9_2_p4_advantage_novelty_design.md` | `98d88ea2a0fc3a88d9d38f5b48aa274498d5e00d` | Match |

Startup refs observed: `exp = ab766b47ce7bae2791028cea22b7915f8debc41c`; `main = 0bff0b32e24dccb1b94c20b6e305cb918a49ec6f`; working branch HEAD at verification was `26b037584bb0a0acce3a293bed3f5a516ffab6c2`, which is descended from the K.10.4 closure commit. No K.11 merge to `exp` or sync to `main` is authorized. The local-only commit `9c6596b2c32bf79bb652f3881e6d41695d43bb38` cannot be verified by the remote view and must be preserved in the original local checkout.

## 3. Architecture and contribution statement

The research concerns a constrained integration contract for recovery in an event-driven embedded runtime. The intended integration combines:

1. Evidence-bounded association precision: an action must not claim more target precision than the available evidence supports.
2. Generation-qualified event references and stale-reference containment.
3. Same-slot, in-pool event quarantine without dynamic allocation or dynamic recycling.
4. Dependency-aware dispatchability so dependent work remains queued while a predecessor is quarantined.
5. A bounded four-rung recovery ladder with terminal handling under repeated recovery faults.
6. Unified deterministic recovery-episode transition/closure authority.
7. Bounded traceable outcomes suitable for post-run auditing.

The contribution must be described as the **integration and interaction of constraints**, not as invention of retry, reset, quarantine, fixed-size storage, event tracing, or fail-safe handling individually. This document does not establish that the combination is legally novel or non-obvious.

## 4. Publication-oriented research questions

- **RQ1 — Association safety:** Does evidence-bounded association handling prevent unsafe retry attempts against an ambiguous or invalid target and close the recovery episode deterministically?
- **RQ2 — Episode liveness:** Does terminal handling of an ambiguous episode preserve capacity for a later valid fault episode?
- **RQ3 — Bounded recovery:** Does a finite recovery ladder terminate when recovery operations themselves repeatedly fail?
- **RQ4 — Cost and trade-offs:** In which fault families do simpler policies outperform the integrated policy, and what are the attempt-count costs?
- **RQ5 — Resource constraints:** Which results depend on bounded capacities such as `QMAX=16` and `EPMAX=1`, and how might these limits confound observed behavior?
- **RQ6 — Transfer to hardware:** Which host-model invariants survive under MCU timing, peripheral, interrupt, bus, and MPU conditions?

## 5. Methods and evidence boundary

### 5.1 Host/reference campaign

The canonical evaluation is a deterministic matched matrix:

```text
16 case families × 5 policy variants × 5 repetitions = 400 executions
```

The five policy variants are P0–P4. The 16 case families are CF01–CF16. The source of truth is the existing K.10 report and its recorded run/trace artifacts. K.11 performs no rerun and does not alter those artifacts.

Zero observed variance is evidence of repeatability for the deterministic host model and fixed input corpus. It is not evidence of robustness to real electrical noise, MCU timing jitter, clock-domain behavior, interrupt races, or environmental variability.

### 5.2 Result interpretation

| Finding | Supported interpretation | Not supported |
|---|---|---|
| CF04 | P4 fails closed under ambiguous fault association and closes the episode where P0–P3 leave a stale-reference outcome and active episode | All ambiguity handling is novel or all real bus faults will be classified correctly |
| CF07 | The CF04 closure difference preserves capacity for a subsequent valid fault episode in the tested model | Universal availability improvement under all queue/episode capacities |
| CF05 | P4's bounded progression terminates in the tested cascading-recovery-fault case where P2/P3 do not terminate within the modeled bound | A proven hard real-time bound on a physical MCU |
| Shared quarantine | Exact-event quarantine behavior is shared across P0–P4 in the reference runtime | Quarantine itself is P4-exclusive |
| CF16 | P2 succeeds in one attempt; P4 takes three attempts in the modeled persistent-bus case | P4 dominates simpler policies on recovery cost |
| CF02, CF09, CF11, CF12, CF13, CF15 | No measured P4 advantage in these six case families | Broad superiority over baselines |

### 5.3 Capacity confounds

The fixed capacity values `QMAX=16` and `EPMAX=1` are important interpretation constraints. A single episode slot can make an unclosed episode block a later episode; that is meaningful under the chosen resource model, but the magnitude and frequency of the effect may change with different capacities. The queue limit can similarly shape backpressure and preservation observations. The publication must report these capacities as part of the method and avoid extrapolating beyond them without a separately authorized study.

### 5.4 Threats to validity

- **Construct validity:** The fault-case labels are operational model scenarios, not a complete taxonomy of peripheral faults.
- **Internal validity:** Matched deterministic execution improves policy comparison, but conclusions remain dependent on the encoded fault model and reference implementation.
- **External validity:** No physical STM32U575ZI measurements have been taken under K.11.
- **Capacity validity:** `QMAX=16` and `EPMAX=1` may influence queue pressure, episode exhaustion, and apparent liveness.
- **Baseline fairness:** CF16 shows a meaningful cost trade-off; the integrated policy should not be presented as universally more efficient.
- **Prior-art validity:** A bounded literature/reference set cannot establish the absence of all relevant prior art.
- **Reproducibility:** A future external reproduction should verify repository revision, compiler, build flags, input corpus, and trace interpretation without modifying the frozen baseline.

## 6. Prior-art and novelty boundaries

### 6.1 Single-reference review

K.10.2 recorded the single-reference anticipation hypothesis as refuted across the inspected candidates PA-01–PA-10 for the full integrated contract. This is a bounded finding about the references and limitation mapping actually examined, not proof that no single reference anywhere discloses overlapping subject matter.

### 6.2 Multi-reference combination risk

K.10.3 left C1 (Phoenix + IBM PA-08 + Quantum Leaps QP/C) as a substantial, unresolved combination challenge. An adversarial reader may argue that known ingredients can be combined through routine engineering. The integrated contract—association precision, generation-qualified references, in-pool quarantine, dependency-aware dispatchability, bounded recovery, and unified episode closure—should be presented as a research hypothesis to evaluate, not a proven legal distinction.

### 6.3 Permitted claim language

Use: “In the tested deterministic host/reference model, P4 demonstrated bounded advantages in CF04, CF07, and CF05, alongside identified counterexamples and resource-capacity limitations.”

Do not use: “P4 is universally superior,” “the invention is novel/non-obvious,” “patentable,” or “hardware validated.”

## 7. Target platform and hardware-validation specification

**Target:** STMicroelectronics STM32U575ZI MCU on the NUCLEO-U575ZI-Q development board. This section is a future validation specification only. It does not authorize connecting, powering, flashing, or testing hardware.

### 7.1 Platform and tooling requirements

- Use the exact board/MCU ordering code and board revision recorded in the eventual lab record. Verify package, memory map, clock limits, pin mapping, and errata against the current ST datasheet, reference manual, board user manual, and errata sheet before implementation.
- Use a pinned Arm GNU Toolchain (GCC, binutils, newlib/newlib-nano as selected) or a pinned Arm-compatible Clang/LLVM toolchain. Record complete version output, target triple, linker version, and build flags.
- Use CMSIS device headers and the vendor-supported startup/system source matching STM32U5. Pin CMSIS Core and STM32U5 device package versions. Do not silently mix startup files, CMSIS versions, HAL versions, or linker scripts.
- Build bare-metal firmware without an RTOS for the initial transfer test unless a later protocol explicitly authorizes a different execution model. No heap allocation may be introduced into the protected recovery path.
- Use a linker script explicitly defining Flash, SRAM, vector table, stack, heap policy (prefer no heap for this test), and section placement. Produce ELF, map file, disassembly, symbol report, build manifest, and reproducible build command.
- Peripheral access must use either a pinned STM32CubeU5 HAL/LL release or a documented CMSIS/register-level driver layer. Select one approach per experiment and do not mix abstraction layers without recording the boundary.
- The first validation firmware should run the unchanged reference runtime through a thin hardware adapter. Hardware-specific code must be outside the frozen reference runtime and must not alter Gates A–E or the policy/transition functions.

### 7.2 Clock and peripheral integration

- Define and document the clock tree from reset to the selected system clock, including oscillator source, PLL settings if used, bus prescalers, flash latency, peripheral clock sources, and any clock-security behavior. Derive values from the exact device revision and verify them at runtime; do not copy generic STM32 settings blindly.
- Begin with a conservative, documented clock configuration. The initial reference test should avoid dynamic clock switching. Clock-change fault scenarios, if later authorized, must be a separately labeled experiment.
- Use one physical I2C peripheral and one SPI peripheral with documented pins, alternate functions, pull-ups, voltage levels, bus speed, mode, and attached test fixture. The board's onboard circuitry and pin conflicts must be checked before wiring.
- Include explicit driver boundaries for peripheral init, transfer start/completion, timeout, error/NACK reporting, bus recovery, peripheral reinitialization, and final status. Each hardware status must map to a defined software evidence/association class; unknown association must never be upgraded to exact.
- Use a monotonic timer source for deadlines and trace timestamps. Record its clock source, tick frequency, wrap behavior, and conversion to time units.
- Interrupt and DMA use must be documented. The initial implementation should choose a single transfer-completion model and keep ISR work bounded; callbacks must not mutate episode/queue state outside the runtime's defined transition authority.

### 7.3 MPU and execution isolation

The STM32U575ZI uses a Cortex-M33-class execution environment with an MPU; exact MPU capability and region constraints must be checked against the selected device documentation and CMSIS definitions before configuring it.

Specify and record a memory map with separate regions for:
1. immutable executable code and vector table (read/execute, not writable);
2. runtime state, queues, episodes, and trace buffers (read/write, execute-never);
3. peripheral MMIO (only the privileged/authorized access domain permitted by the chosen protection design);
4. stack(s) with guard strategy where supported by the MPU's region/alignment constraints;
5. optional DMA buffers with the required access policy and explicit ownership protocol.

The MPU setup must be established before entering the test loop. Region size, alignment, access permissions, execute-never settings, privileged defaults, subregion behavior if available, and overlap priority must be documented. Do not assume arbitrary byte-sized regions are representable. Test intended access permissions using safe, isolated positive and negative probes only after a separate hardware-execution authorization. A protection fault must be captured by a bounded fault handler; the handler must not attempt unsafe recovery using corrupted state. Define which faults are terminal and how a reset/restart is recorded. MPU isolation is not proof of complete system security.

### 7.4 Physical fault-injection fixture and protocols

All protocols below are **planned procedures**, not executed tests. Use a current-limited, voltage-compatible fixture and avoid driving a line against the MCU or another device. Prefer a dedicated peripheral test fixture or secondary controller. Never short supply rails or apply out-of-range voltages.

**Baseline control:** Capture healthy I2C and SPI transfers, successful completion, normal timing, idle bus state, and expected application-level event sequence. Record the same workload without injection before testing each fault class.

**I2C NACK stimulus:** Use a controllable target/fixture that deliberately NACKs a selected address or data phase. Record which phase was NACKed, peripheral status flags, driver result, recovery decision, trace outcome, and whether subsequent healthy transfers complete.

**I2C clock-stretch/timeout stimulus:** Use a target fixture capable of stretching SCL within the device and bus limits. Test a compliant stretch that completes before the configured deadline and a separately controlled over-deadline condition. If the fixture cannot reliably produce controlled clock stretching, mark the scenario unsupported rather than simulating it in software and calling it physical evidence.

**I2C bus disturbance:** Use a controlled fixture to delay release or perturb SDA/SCL within electrically safe bounds, with repeatable timing and a hardware interlock. Record line state and edge timing. Any deliberate out-of-spec disturbance must be clearly separated from normal protocol-compliance tests.

**SPI fault stimulus:** Use a fixture to control a selected peripheral response, suppress or delay readiness where the protocol allows, or inject a bounded transfer timeout. SPI has no universal NACK signal; do not describe an application-level missing response as an SPI NACK. Record chip-select, SCK, MOSI, MISO, transaction length, timeout, and driver status.

**Recovery-operation fault:** Where safely feasible, make a recovery attempt fail in a controlled and repeatable way (for example, maintain the test fixture's fault state through a documented recovery rung). Do not damage or electrically overstress the device. If physical control cannot reproduce the intended condition, report the case as not tested.

**Association ambiguity:** Create overlapping or incomplete transaction evidence only through a deterministic fixture procedure, then verify that the adapter reports ambiguity rather than inventing an exact event target.

For every trial, capture: trial ID, firmware hash, board/MCU revision, toolchain, clock setup, peripheral configuration, injection method and timing, logic-analyzer/oscilloscope setup, raw trace filename, runtime trace, outcome, and deviations. Repeat counts and acceptance thresholds must be fixed before data collection in the separately authorized hardware phase.

### 7.5 Physical instrumentation

- A logic analyzer with adequate sample rate and digital thresholds for the selected bus speed; record sample rate, threshold, probe location, and decoder settings. Save raw captures, not only screenshots.
- An oscilloscope with appropriate bandwidth and probes for validating voltage levels, edge rise/fall behavior, ringing, clock stretching, and disturbance timing. Use high-impedance probes and avoid excessive loading.
- Common timebase or a documented alignment event between instrument traces and firmware trace timestamps. A GPIO marker may be used if its instrumentation overhead is measured and reported.
- A stable power source and current-limited setup; record supply voltage and relevant environmental conditions.
- Version-controlled test scripts/configuration and checksums for all raw data. Screenshots may illustrate results but cannot replace raw evidence.

## 8. Hardware validation success criteria and falsification

Hardware testing must be separately authorized and preregistered. The following criteria define a future acceptance protocol; they are not claims of achieved results.

### 8.1 Acceptance criteria

1. **Build integrity:** Clean, reproducible bare-metal build with archived toolchain versions, flags, linker map, ELF, and firmware hash.
2. **Baseline correctness:** Healthy I2C/SPI controls complete as expected without spurious recovery.
3. **Evidence discipline:** Ambiguous or unknown association never triggers a target-specific retry as if exact; the trace records the conservative outcome.
4. **Quarantine invariant:** Quarantined target work is not dispatched while quarantined; unrelated eligible work and dependent work follow the declared dependency rules.
5. **Bounded termination:** Injected recovery-operation faults terminate within the implementation's declared finite rung/attempt bound, with an explicit terminal outcome and closed episode where the contract requires it.
6. **Recovery liveness:** After a terminally handled fault, a subsequent valid independent fault can be processed when the declared capacity model permits it.
7. **Containment:** Invalid/stale references are rejected without memory corruption; intended MPU violations trap in the defined handler.
8. **Resource bounds:** Stack, static RAM, trace buffer, queue, and episode usage remain within predeclared limits; no heap allocation occurs in the recovery path.
9. **Timing evidence:** Deadline behavior is measured from physical signals and a documented timer; worst observed values and trial count are reported without claiming a WCET proof unless a separate analysis establishes it.
10. **Reproducibility:** A second clean build and repeated preregistered trials produce interpretable traces with no unexplained mismatches between instrument evidence and runtime outcomes.

### 8.2 Falsification conditions

The integrated hardware hypothesis is weakened or falsified for the tested configuration if any of the following occurs:

- ambiguous evidence is promoted to exact association or causes a target-specific retry;
- the same fault sequence causes an unbounded recovery loop or episode that remains active contrary to the contract;
- quarantined work executes early or a required dependency ordering is violated;
- a stale/invalid reference causes unsafe access or memory corruption;
- a subsequent eligible fault cannot be handled under the declared available capacity after the prior episode should have closed;
- the runtime trace contradicts the captured bus signals or driver status without a diagnosed instrumentation issue;
- protection configuration permits an explicitly forbidden access or fails to contain the selected test violation;
- resource bounds are exceeded, or heap use enters the protected recovery path;
- behavior depends on undocumented timing, clock, driver, or fixture assumptions that cannot be reproduced.

A failed criterion must be reported, not silently tuned away. Any change to the frozen reference runtime would require a separate, explicitly authorized future checkpoint and a new evidence lineage.

## 9. Professor-facing software closure narrative

The software phase developed and evaluated a constrained peripheral-recovery policy through a deterministic host/reference runtime. Its purpose was to investigate whether a specific integration of evidence-bounded fault association, generation-qualified references, bounded recovery progression, in-pool quarantine, dependency-aware dispatch, and deterministic episode closure can improve behavior in selected failure scenarios under resource constraints.

The evaluation used 400 matched executions across 16 case families and five policy variants. P4 showed bounded advantages in CF04, CF07, and CF05, while CF16 demonstrated a baseline advantage for P2 and six other case families showed no measured P4 advantage. Quarantine behavior was shared across all variants, and the results are sensitive to the bounded queue and episode capacities. Prior-art review did not identify a single inspected reference anticipating the entire integration, but a multi-reference combination challenge remains unresolved.

Accordingly, the software-level research phase is ready for academic review as an evidence-bounded result. It does not claim universal superiority, legal novelty, or physical validation. The next authorized productization stage is K.12; physical MCU validation remains a separately gated activity and must not be conflated with the software demonstration.

## 10. Publication results structure

A paper or report should be organized as follows:

1. **Problem and motivation:** Peripheral faults, ambiguous attribution, constrained memory, and recovery-liveness trade-offs.
2. **System model:** Event queue, peripheral classes, episode state, association precision, fixed capacities, policy variants.
3. **Integrated contract:** Gates A–E and recovery/dispatch invariants, with reference-runtime revision pinned.
4. **Experimental design:** CF01–CF16, P0–P4, five repetitions, 400 executions, deterministic injection and trace collection.
5. **Primary results:** CF04, CF07, CF05 with outcome tables and trace-backed explanations.
6. **Counterevidence and controls:** CF16 P2 baseline win; six no-advantage cases; shared quarantine; negative controls.
7. **Capacity and validity limits:** QMAX=16, EPMAX=1, deterministic host model, threats to validity.
8. **Prior-art discussion:** PA-01–PA-10 single-reference result and unresolved C1 combination risk, avoiding legal conclusions.
9. **Limitations and next steps:** Independent reproduction, hardware adapter, MCU validation, timing and resource measurements.
10. **Conclusion:** Narrow evidence-bounded integrated-policy hypothesis.

Recommended tables/figures: system-state/transition diagram; experimental matrix; all-16-case result table; three primary-case trace timelines; attempt-count trade-off table; capacity/validity table; and a hardware validation protocol matrix. Every figure must identify host-model evidence versus future hardware measurements.

## 11. Deliverable status and next gate

- [x] Startup branch/HEAD checks performed against GitHub.
- [x] `exp` and `main` HEADs verified at the expected SHAs.
- [x] Five protected blob SHAs verified.
- [x] Required continuity documents and K.10.4 records inspected for presence and state.
- [ ] Professor-facing software demonstration productization — K.12.
- [ ] Physical MCU flashing, measurement, and fault injection — not authorized by K.11.
- [ ] Merge to `exp` and sync to `main` — not authorized by K.11.

**Checkpoint conclusion:** K.11 defines the evidence-bounded software synthesis and a concrete future hardware-validation protocol. Formal K.11 closure remains subject to ChatGPT review of the committed deliverables.

---

## 12. Substantive review addendum and locked implementation baseline

**Review disposition:** K.11 is approved and closed by ChatGPT on 2026-10-13, subject to the explicit non-blocking evidence-reconciliation item below being carried into K.12. This approval validates the K.11 synthesis and specification as a handoff; it does not assert hardware execution, legal novelty, or universal superiority.

### 12.1 Concrete target-board baseline for the future authorized hardware phase

The selected board is **NUCLEO-U575ZI-Q**, whose on-board MCU is **STM32U575ZIT6Q**. At the start of the hardware phase, record the board revision and MCU silicon revision printed/identified on the actual unit and consult the matching STM32U575 device errata and NUCLEO-U575ZI-Q board manual. ST's board manual is UM2861; ST's product page identifies the MCU fitted to this board. Sources:
- ST NUCLEO-U575ZI-Q product page: https://www.st.com/en/evaluation-tools/nucleo-u575zi-q.html
- ST STM32U5 Nucleo-144 board user manual UM2861: https://www.st.com/resource/en/user_manual/um2861-stm32u5-nucleo144-board-mb1549-stmicroelectronics.pdf
- ST STM32U575 device page: https://www.st.com/en/microcontrollers-microprocessors/stm32u575zi.html

Use this documented **initial baseline** unless a separately recorded pin-conflict or board-revision check requires an approved alternative:

| Function | MCU pin | Board header / signal | Baseline setting |
|---|---|---|---|
| I2C1 SCL | PB8 | Arduino Zio CN7, D15 / I2C_A_SCL | 100 kHz standard mode |
| I2C1 SDA | PB9 | Arduino Zio CN7, D14 / I2C_A_SDA | 3.3 V bus; external pull-ups only after checking existing board/fixture pull-ups |
| SPI1 SCK | PA5 | Arduino Zio CN7, D13 / SPI_A_SCK | SPI mode 0, 1 MHz initial clock |
| SPI1 MISO | PA6 | Arduino Zio CN7, D12 / SPI_A_MISO | 8-bit frames, MSB first |
| SPI1 MOSI | PA7 | Arduino Zio CN7, D11 / SPI_A_MOSI | 8-bit frames, MSB first |
| SPI1 software chip select | PD14 | Arduino Zio CN7, D10 / SPI_A_CS | GPIO-controlled, inactive high for the test fixture unless the fixture protocol requires otherwise |
| Ground reference | Board GND | Corresponding header GND | Common ground between board and compatible fixture |

These mappings are based on UM2861's connector pinout and must still be checked against the physical board revision and any connected shields. Do not connect an unknown peripheral or assume that a connector pin is electrically free merely because the MCU alternate function exists. SPI mode 0 and 1 MHz are the initial fixture protocol choices, not claims that all SPI peripherals require those settings. The fixture protocol must explicitly define the test target and response semantics.

**Clock baseline:** use the internal MSI oscillator selected at **16 MHz as SYSCLK**, with no PLL, and AHB/APB prescalers at 1 for the initial baseline. Select peripheral clock sources explicitly in RCC; use the documented bus clock for I2C1/SPI1 unless the selected reference manual or driver configuration requires another supported source. Set Flash latency and voltage-scaling configuration according to the exact STM32U575 datasheet/reference manual before switching clocks. Record the measured/verified clock configuration in firmware output. This is a proposed conservative starting configuration, not a verified physical configuration.

**Timer and deadlines:** use one documented hardware timer as a monotonic timestamp source, configured for a 1 MHz counter tick if the selected timer clock and prescaler permit it. Define the initial software timeout for controlled transfer tests as **10 ms**, then preregister any additional timeout values before data collection. Record wraparound handling and prove timeout conversion against the actual timer clock configuration.

**Build and memory:** the hardware phase must pin one exact Arm GNU Toolchain release (or one exact Arm-compatible Clang/LLVM release), CMSIS Core version, STM32U5 CMSIS device package, STM32CubeU5 HAL/LL release if used, linker script revision, startup/system source, optimization/debug flags, and board/MCU revision in a checked-in manifest. Do not claim reproducibility from compiler family names alone. Use the official STM32U5 CMSIS startup/system files matched to the chosen package; no hand-copied startup file with an unrecorded provenance. The reference runtime remains an unchanged source unit behind the adapter.

**Instrumentation baseline:** capture I2C at 100 kHz and SPI at 1 MHz with a logic analyzer configured for at least 10 MS/s (20 MS/s preferred for timing margin) and thresholds compatible with the 3.3 V logic domain. Use an oscilloscope for voltage/edge integrity and controlled disturbance timing. Probe loading, sample rates, thresholds, and channel-to-firmware trace alignment must be recorded. These are minimum planning values; instrument adequacy must be reassessed for faster edges or any higher bus rate.

### 12.2 CF01 source-table inconsistency — preserved, not silently repaired

A review cross-check found a pre-existing discrepancy in the frozen K.10 records:
- In `research/phase2_k10_p4_advantage_novelty_results.md`, the CF01 row's P2 result field states `SUCCESS, att=3`, while the row's explanatory text says P2 succeeds in one attempt.
- The CF01 row in `research/phase2_k10_4_final_technical_distinction_and_research_conclusion.md` records P2 as `SUCCESS (att=1)`.

The existing raw CSV paths are cited by the reports but were not retrievable through the inspected branch contents during this review. No experiment was rerun and no frozen K.10 result was edited. Therefore, the **CF01 P2 attempt count remains unresolved** and must not be used as a comparative claim until K.12's final audit reconciles it against the original raw records if those records are available. This discrepancy does not alter the K.11 CF16 comparison, whose one-attempt P2 versus three-attempt P4 finding is retained from the K.10 report.

### 12.3 Formal closure and handoff

K.11 is **APPROVED AND CLOSED**. K.12 is authorized to begin software-only professor-facing demonstration productization and final software audit. K.12 does not inherit permission for MCU flashing, physical fault injection, or physical measurement. The `exp` branch remains canonical and unchanged; `main` remains unsynchronized. The original local-only commit `9c6596b2c32bf79bb652f3881e6d41695d43bb38` remains a preservation obligation for the original local checkout.
