# Next Chat Prompt — Chat 07.1: BME280 Baseline and Recovery

The prior Chat 06 prompt below is retained in Git history but superseded for current work. Continue from the latest sensor result and use the dedicated prompt as the source of truth:

**[Open the full Chat 07.1 prompt](Plan2.0/prompts/CHAT_07_1_BME280_BASELINE_AND_RECOVERY_PROMPT_2026-10-25.md)**

## Latest state (2026-10-25)

User-provided CubeIDE screenshot showed:
- `sensor_found=1`
- `sensor_address=118` decimal = `0x76`
- `sensor_chip_id=96` decimal = `0x60`
- `sensor_type=1`
- `sensor_error=0`

The user-pasted ST-LINK log showed “Download verified successfully,” device ID `0x415`, target voltage 3.26 V. The successful register-`0xD0` read at address `0x76` returned `0x60`, matching BME280. This is a user-evidence-backed physical chip-ID read, not full environmental sensing or sensor fault-recovery proof.

## Immediate next task

Review the exact current local sensor source and preserve its provenance separately from `Plan2.0/firmware/ld2_gpio_recovery/`. Design a safe, controlled software-only I²C fault/recovery test with the acceptance criterion of a fresh successful chip-ID read after recovery. Preserve the external `main.c` backup and protected reference/research evidence. Work on `main` only; do not repeat the successful chip-ID test without a specific reason, do not use electrical shorts or unsafe pin forcing, and do not flash without explaining the step and getting user approval.

Read `Plan2.0/CURRENT_STATE.md`, `CURRENT_HANDOFF.md`, `Plan2.0/CHAT_PROTOCOL.md`, `Plan2.0/EXECUTION_ROADMAP.md`, and the evidence report `Plan2.0/results/CHAT_07_BME280_CHIP_ID_DETECTION_2026-10-25.md` before continuing.
