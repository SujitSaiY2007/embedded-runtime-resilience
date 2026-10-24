# Current Handoff — Plan 2.0 Hardware Bring-Up

**Last reconciled:** 2026-10-24  
**Repository:** SujitSaiY2007/embedded-runtime-resilience  
**Branch:** main only  
**Status:** Chat 05.3 has achieved a successful local firmware download/debug run and narrow GPIO recovery check; next work is Chat 06 reproducible minimal-firmware scaffold.

## Research/software baseline retained

The C reference runtime remains the recovery-policy authority for the software demonstrator. The frozen campaign contains 16 case families × 5 variants × 5 repetitions = 400 host/reference executions. Evidence supports bounded P4 advantages in selected cases, not universal superiority. Exact-event quarantine is shared across P0–P4. CF01's disputed P2 attempt count must remain omitted from comparisons. Preserve protected runtime/Gate contracts, frozen evidence, prior-art reviews, manuscript and historical records.

## Hardware progress verified by user-provided evidence

- Board reported/shown: ST NUCLEO-L476RG, revision MB1136 C, target STM32L476RG.
- Board-only USB power/LEDs and laptop USB-device detection: user-confirmed.
- STLinkUpgrade 3.17.11 firmware update to V2J48M35: successful screenshot.
- Generated STM32CubeIDE Empty Project: build reports 0 errors, 0 warnings. It is not yet custom project firmware.
- Debugger configuration: ST-LINK GDB server / SWD / Cortex-M4.
- Debug launch failure: GDB/SWV port bind errors for 61234/61235 plus expanded ST-LINK initialization error.
- Both prior netstat queries returned no output.
- User does not have standalone STM32CubeProgrammer.

## Not yet verified

No successful SWD connection, MCU identity read through debugger, firmware download, MCU execution, sensor wiring/read, fault injection, recovery, or MCU measurement has been demonstrated. Do not describe any of these as passed.

## Exact continuation

Read Plan2.0/CURRENT_STATE.md, Plan2.0/handoffs/CHAT_05_2_HANDOFF.md, and continue from [Plan2.0/prompts/CHAT_05_3_STLINK_DEBUGGER_CONTINUATION_PROMPT.md](Plan2.0/prompts/CHAT_05_3_STLINK_DEBUGGER_CONTINUATION_PROMPT.md). Do not repeat completed USB detection, firmware upgrade, clean build, or identical empty netstat checks without new justification. Do not ask for standalone CubeProgrammer installation, buy hardware, or wire the sensor.

## Source of truth

The detailed inventory and safety gates remain in the Chat 05.2 original prompt. The latest state/next action is Plan2.0/CURRENT_STATE.md and the Chat 05.3 prompt. All future Plan 2.0 work stays on main; inspect live HEAD before writing.
\n\n## New evidence — 2026-10-24: GPIO experiment\n\nUser-provided CubeIDE screenshots show: build completed with 0 errors/0 warnings; firmware download console said “Download verified successfully”; debugger execution reached the final infinite loop; Expressions view showed event=1, fault=1, recovery=1, state=4 (RECOVERED), recovered=1, fault_injected=1, gpio_mode=1 (output), gpio_output=1 (output latch high). The experiment deliberately changed PA5 from output mode to input mode, then restored output mode and set PA5 high. Full method/limits: [GPIO experiment report](Plan2.0/results/CHAT_05_3_GPIO_RECOVERY_EXPERIMENT_2026-10-24.md).\n\n**Evidence limits:** This verifies one software-injected GPIO configuration case in the local generated CubeIDE project. It does not prove physical peripheral damage recovery, measured pin voltage/LED optics, sensor reads, repeated-run reliability, MCU timing/stack/energy, or integration of this local code into the canonical repository. The sensor remains unwired. The STM32L476RG target is not assumed equivalent to the earlier STM32U575ZI proposal.\n\n## Exact next action\n\nChat 06: preserve the local working source and backup, reconcile source provenance with the canonical repository, and make the minimal firmware test reproducible without copying generated startup/linker files or changing the protected reference runtime. After the baseline is stable, Chat 07 covers sensor/peripheral compatibility and baseline reads; Chat 08 covers broader controlled fault/recovery, with fresh-operation verification.\n

## Chat 06 update — 2026-10-24: source preservation

The user supplied the current experiment source for `main.c`, `err_runtime.c`, and `err_runtime.h`, and confirmed the external backup of the earlier `main.c` exists separately. These three files were transcribed with formatting normalized and preserved under [Plan2.0/firmware/ld2_gpio_recovery/](Plan2.0/firmware/ld2_gpio_recovery/). The accompanying README states provenance and limits. This is not yet a complete, independently buildable CubeIDE project: generated startup/linker files and workspace metadata were intentionally not copied, and no fresh build or download was run by the repository connector.

### Next action

Continue Chat 06 by reviewing the user's local CubeIDE project configuration and identifying the minimum information needed to reproduce the reported build without importing or overwriting the working project. Keep the external backup and working firmware untouched. Do not flash or wire the sensor during this source/configuration review.


## Chat 06 configuration review — 2026-10-24

User-provided screenshots confirm the local project uses Debug, GNU Tools for STM32 14.3.rel1, GNU11, and `STM32L476RGTX_FLASH.ld` through `${workspace_loc:/${ProjName}/STM32L476RGTX_FLASH.ld}`. Map-file generation and unused-section removal are enabled; system calls use Minimal implementation (`--specs=nosys.specs`). The project tree contains startup and Debug build folders, ELF/list/map outputs, a debug launch configuration, and both Flash/RAM linker scripts. Full CPU/FPU flags and clean checkout reproducibility remain unverified.

The user has explicitly requested that further settings inspection stop and work proceed. Do not ask for more configuration screenshots unless a specific blocker arises. No local build, download, debugger action, or hardware interaction was performed during this repository documentation update.