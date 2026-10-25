# Execution Roadmap — Plan 2.0

Each numbered chat is a bounded work package. Read the current state, previous handoff, relevant original artifacts, and protected-boundary rules before proceeding.

| Chat | Work package | Required output | Exit condition |
|---|---|---|---|
| 00 | Initialize Plan 2.0 | State, protocols, roadmap, archive index, README navigation | Framework committed on `main`; no code/evidence changed |
| 01 | Reference inventory | Complete source inventory and per-entry status for preliminary ~43 references | Every entry has a stable ID and verification status |
| 02 | Metadata and venue verification | DOI/title/authors/year/venue/type checks; journal/conference/source classification | No fabricated or silently guessed metadata |
| 03 | Literature gap and influence mapping | Source-to-design traceability, related-work matrix, research-gap map | Each project claim linked to evidence or flagged unsupported |
| 04 | Bibliography/manuscript revision | IEEE-style reference list and revised related work | Citations resolve and claims are source-supported |
| 05 | Hardware compatibility audit | Board/component inventory, target discrepancy, zero-budget feasibility, risk register | Compatibility blockers documented; no unsafe wiring approved |
| 05.2 | Zero-budget hardware bring-up — paused | Board-only USB detection and ST-LINK firmware update succeeded; generated Empty Project builds cleanly; GDB server/ST-LINK initialization fails. See current state and handoff. | Resume from recorded diagnostics; do not repeat completed checks; no sensor wiring until gates pass |
| 05.3 | ST-LINK debugger continuation — **debugger now working for local test** | Reconcile earlier GDB blocker with the new successful CubeIDE download/debug evidence; document the narrow GPIO experiment | Download verification and debugger execution evidenced; broader recovery claims remain bounded |
| 06 | Minimal firmware scaffold and provenance — **in progress** | Source files and provenance notes are preserved under `Plan2.0/firmware/ld2_gpio_recovery/`; inspect the local CubeIDE project configuration and establish a reproducible procedure without generated startup/linker churn | Source provenance explicit; reproducibility procedure documented and checked without overwriting the working project; build/download evidence kept distinct |
| 07 | Baseline peripheral integration | Sensor/peripheral reads with raw logs | Stable baseline demonstrated and documented |
| 08 | Controlled fault and recovery — **integration candidate prepared; target validation pending** | Connect `policy_decide()` to the real BME280 I2C reinitialization adapter, then require fresh chip-ID verification before runtime release | Clean CubeIDE build, expected P4 decision/action variables, fresh chip ID `0x60`, successful runtime release, and documented evidence; no physical stuck-bus claim |
| 09 | Measurement and repeatability | MCU timing/resource observations, raw traces, repetitions and limitations | Results reproducible and clearly separated from host results |
| 10 | Manuscript and demo integration | Hardware methods/results, figures, demo guide, limitations | All claims trace to artifacts |
| 11 | Final audit and release | Repository audit, clean README/state/handoff, evidence manifest | No unverified claims or unresolved critical gaps hidden |

## Rules for every chat

- Read `Plan2.0/CURRENT_STATE.md`, `Plan2.0/CHAT_PROTOCOL.md`, and the latest handoff first.
- Make the smallest scope-specific changes; use only `main`.
- Do not run or rewrite the frozen 400-execution campaign to repair a documentation inconsistency.
- Do not edit the protected reference runtime or frozen reports merely to make new hardware work.
- Before claiming a source is influential, classify the relationship as direct adoption, adaptation, conceptual context, comparator, or no demonstrated influence.
- Close with a handoff containing completed work, files changed, checks actually run, commit SHA, open questions, and the exact next task.


**Chat 06 progress update (2026-10-24):** source files and provenance are preserved in `Plan2.0/firmware/ld2_gpio_recovery/`. User screenshots confirm the local CubeIDE Debug configuration, GNU Tools for STM32 14.3.rel1, GNU11, `STM32L476RGTX_FLASH.ld`, map-file generation, unused-section removal, and `--specs=nosys.specs`. The generated project tree includes startup/build artifacts, ELF/list/map outputs, debug launch configuration, and Flash/RAM linker scripts. No more configuration screenshots should be requested absent a concrete blocker. Chat 06 must now consolidate a safe reproduction procedure and evidence boundaries; do not copy generated artifacts or disturb the local project/backup.

## Chat 06 milestone update — 2026-10-24

The user confirmed that `Project → Build Project` works in the existing local CubeIDE project after the settings review. Source preservation, configuration recording, and local rebuild continuity are complete for this stage. A clean build from a repository checkout is still **not demonstrated**; do not label the GitHub source folder a standalone CubeIDE project. The user asked to stop further configuration inspection. Chat 07 may begin with sensor identity/electrical-compatibility research only; keep the module unwired until its identity, pinout, supply/logic levels, and pull-ups are verified.

## Chat 07 update — 2026-10-25

The user has demonstrated a successful BME280 chip-ID read on the NUCLEO-L476RG: `sensor_found=1`, address `0x76`, chip ID `0x60`, `sensor_type=1`, `sensor_error=0`; ST-LINK log reported “Download verified successfully.” This is user-provided screenshot/log evidence and a baseline peripheral-read milestone. See `results/CHAT_07_BME280_CHIP_ID_DETECTION_2026-10-25.md`.

**Next:** Chat 07.1 reviews and preserves the exact local sensor-test source, then prepares a controlled software-only I²C fault/recovery test. Recovery acceptance requires a fresh successful chip-ID read after recovery. Do not overwrite the LD2 GPIO experiment, external backup, or protected reference/research assets. No electrical shorts or unsafe pin forcing. Use `prompts/CHAT_07_1_BME280_BASELINE_AND_RECOVERY_PROMPT_2026-10-25.md`.


## Chat 07.1 closeout — 2026-10-25

The user-supplied debugger screenshot confirms the controlled address-NACK/I²C1 reinitialization experiment reached `RECOVERY_PASSED` and a fresh BME280 ID read returned `0x60`. See `results/CHAT_07_1_BME280_CONTROLLED_NACK_RECOVERY_2026-10-25.md`. This closes the Chat 07.1 experimental acceptance gate for that specific test, not the broader runtime integration goal.

**Chat 08 is now the next package:** integrate the actual runtime decision/action path with the physical BME280 operation. Audit interfaces and protected boundaries first; define a safe fault model; require a fresh successful post-recovery transaction; preserve source provenance and distinguish user evidence from tool-run checks. Prompt: `prompts/CHAT_08_RUNTIME_HARDWARE_INTEGRATION_PROMPT_2026-10-25.md`.


## Chat 08 execution update — 2026-10-25

A separate BME280 firmware candidate and README are now committed under `Plan2.0/firmware/bme280_policy_integration/`. It routes the controlled NACK through the P4 runtime decision and executes the selected I2C reinitialization action before a fresh sensor read gates event release. See [Chat 08 candidate report](results/CHAT_08_POLICY_HARDWARE_INTEGRATION_CANDIDATE_2026-10-25.md).

**Current exit status:** source candidate and evidence plan prepared; not yet built or flashed. The next action is a local CubeIDE build using the exact runtime header/source. Only after a clean build and explicit user approval may the candidate be flashed and tested. Keep prior LD2 and Chat 07.1 evidence separate.

## Chat 08–09 execution status

- **Chat 08 — P4 policy-to-BME280 hardware integration:** completed successfully according to user-provided build and debugger evidence. See [Chat 08 result](results/CHAT_08_POLICY_HARDWARE_INTEGRATION_CANDIDATE_2026-10-25.md).
- **Chat 09 — evidence reconciliation and final handoff:** capture/reconcile the policy decision, selected action, hardware-action result, runtime release and trace fields; verify the current candidate and docs agree; document any remaining evidence gap. No redundant baseline/NACK run unless justified by a specific gap. Protected reference runtime and frozen host evidence remain unchanged.


## Chat 09 closeout — 2026-10-25

**Outcome: ACCEPTED for the bounded hardware-demonstration milestone.** The user-provided Chat 08 CubeIDE evidence supports one successful controlled address-NACK → P4-selected I²C1 reinitialization → fresh BME280 chip-ID read (`0x60`) → runtime event release → terminal report code 8. Chat 09 audited the current firmware, current protected reference runtime (read-only), report and handoff.

The source-derived expected auxiliary policy values are documented separately from the observed screenshot fields; event slot/generation, trace count and runtime byte count remain not captured. Report code 8 is assigned only after the fresh sensor read and successful runtime release. The terminal `__BKPT(0)` followed by an infinite loop is intentional debugger-visible behavior.

No further hardware run or flash is recommended solely to close Chat 08. An optional debugger-only inspection of the already-saved terminal session may fill auxiliary evidence fields, but is not an acceptance blocker. Further work should be a separately scoped reproducibility/evidence-packaging and MCU measurement plan; no MCU performance/memory or stuck-bus claims are currently supported.

Full report: `results/CHAT_09_HARDWARE_EVIDENCE_RECONCILIATION_2026-10-25.md`. Firmware notes reconciled: `firmware/bme280_policy_integration/README.md`. Protected source, Gate A–E contracts, frozen 400-execution evidence, prior-art reviews and manuscript were not changed.

## Chat 10 planning update — 2026-10-25

Chat 09's bounded hardware demonstration and evidence reconciliation are accepted. The next package is **Chat 10 — Final Hardware Validation, Evidence Closure & UI Integration Readiness**. The Chat 10 prompt is at `prompts/CHAT_10_FINAL_HARDWARE_VALIDATION_PROMPT_2026-10-25.md`.

Chat 10 begins with an evidence audit and a proposed matrix; no initial reflash. It evaluates justified, safe target validation and resource measurements, but must not represent unperformed tests as completed. Any flashing/hardware-affecting change requires explicit user approval after source review and a clean build. Once hardware findings and limitations are documented, prepare Chat 11 for real-time integration with the existing UI. UI implementation is explicitly out of scope for Chat 10.


## Chat 10 execution update — 2026-10-25

The five-total-trial protocol has been defined in `results/CHAT_10_FINAL_HARDWARE_VALIDATION_2026-10-25.md`. Trial 1 is the existing Chat 08 run (one run, two complementary screenshots); Trials 2–5 remain pending. The firmware is one-shot and halts at its terminal breakpoint, so repeated trials require restarting the unchanged image from reset. No flash/build/hardware operation was performed by the GitHub-side audit, and flashing remains prohibited without explicit user approval after review and a clean build. Do not report the repeatability gate as passed until the four additional trial records are reconciled.

## 2026-10-25 hardware matrix scope update

A separate candidate `Plan2.0/firmware/bme280_policy_integration/embedded_runtime_five_policy_matrix.c` and review plan `Plan2.0/results/FIVE_POLICY_HARDWARE_MATRIX_PLAN_2026-10-25.md` were added on `main`. This candidate targets P0–P4 for one physical controlled NACK scenario and a provisional 5×16 runtime-decision matrix. It is **not yet built or validated**. Before flashing, reconcile the 16 candidate contexts with the frozen host case corpus, inspect resource use and compiler diagnostics, and obtain explicit approval for download. Do not call the in-firmware matrix 80 physical tests or claim equivalence with the frozen 400-execution campaign.



## Chat 11 closeout — diagnostic hardware evidence and manuscript next (2026-10-25)

The user-provided CubeIDE run reached `progress_stage=900`, `finished=1`, `overall_code=1`. Baseline error slots were 0; the controlled wrong-address read returned `E_NACK=-1`; P1 and P4 passed their harness physical checks and returned post-recovery BME280 ID `0x60` with release result 1. P0/P2/P3 ended in `R_TERMINAL`. See [Chat 11 report](results/CHAT_11_FIVE_POLICY_DIAGNOSTIC_HARDWARE_RUN_2026-10-25.md).

This closes the current bounded hardware demonstration only. It does not establish physical stuck-bus recovery, repeatability, MCU resource measurements, 80 physical experiments or universal P4 superiority. The complete 80-element matrix-status array has not been independently captured; a discrepancy exists between the user's statement about the final entry and a screenshot showing `matrix_status[79]=1`.

**Next work package: manuscript drafting.** Audit the full repository and references, create a claim-to-evidence ledger, draft a journal manuscript and verify every citation. Start from [Claude journal manuscript prompt](../research/manuscript/CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md). Do not rerun or modify the frozen 400-execution host campaign or protected reference runtime.
