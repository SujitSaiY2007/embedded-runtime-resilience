# Next Chat Prompt — Chat 07.1: Integrate Verified BME280 Baseline and Prepare Recovery Test

Continue the existing Plan 2.0 hardware work from the user's successful sensor chip-ID read on 25 October 2026. **Do not restart setup or repeat successful checks.** The immediate goal is to preserve the working sensor baseline, inspect source provenance, and make a minimal safe path toward a controlled peripheral recovery demonstration.

## Read first
1. `README.md`
2. `PROJECT_STATE.md`
3. `CURRENT_HANDOFF.md`
4. `Plan2.0/CURRENT_STATE.md`
5. `Plan2.0/CHAT_PROTOCOL.md`
6. `Plan2.0/EXECUTION_ROADMAP.md`
7. `Plan2.0/results/CHAT_05_3_GPIO_RECOVERY_EXPERIMENT_2026-10-24.md`
8. `Plan2.0/firmware/ld2_gpio_recovery/README.md`
9. `Plan2.0/results/CHAT_07_BME280_CHIP_ID_DETECTION_2026-10-25.md`

Fetch live GitHub state and current `main` HEAD before making changes. Work on **main only**.

## Latest user-supplied hardware evidence (2026-10-25)
- Board: ST NUCLEO-L476RG, revision MB1136 C, STM32L476RG, device ID `0x415`.
- ST-LINK firmware V2J48M35; GDB server 7.14.0; STM32CubeProgrammer 2.23.0 bundled with CubeIDE; board voltage in log 3.26 V.
- User-pasted log says firmware download completed and **“Download verified successfully.”**
- Debugger Expressions screenshot:
  - `sensor_found = 1`
  - `sensor_address = 118` decimal = `0x76`
  - `sensor_chip_id = 96` decimal = `0x60`
  - `sensor_type = 1` (test's BME280 classification)
  - `sensor_error = 0`
- This supports a successful I²C register-`0xD0` chip-ID read from a responding device at `0x76`, with ID `0x60` matching BME280. It does **not** establish full temperature/pressure/humidity measurements or recovery after a sensor fault.
- Sensor wiring reported by user: VIN→3V3, GND→GND, SCL→D15/PB8/I2C1_SCL, SDA→D14/PB9/I2C1_SDA. The exact breakout's electrical design/pull-ups have not been independently verified.
- Timing line used in the latest test: `I2C1->TIMINGR = 0x30420F13U`; HSI16 enable/wait code was added before selecting HSI16 for I2C1. The user said the build worked.
- Old `test_*` Expressions entries showed “Error: Multiple errors…” in the sensor-test debug session; likely stale expressions from the earlier LD2 firmware. Do not mistake these for sensor failure; clear/recreate expressions when appropriate.
- Earlier LD2 PA5 GPIO mode-fault/recovery test remains a separate, previously successful milestone. Preserve its source/evidence.

## Chat objective
1. Inspect the actual current sensor-test source in the user's local project or ask for the minimum needed source if not already available. Do not pretend the full source is already in GitHub.
2. Compare it with `Plan2.0/firmware/ld2_gpio_recovery/` and preserve clear separation between sensor baseline test and prior LD2 experiment. Do not overwrite external `main.c` backup or working local project.
3. Store a provenance-labelled sensor-test source record only after reviewing the exact source. Keep generated startup/linker/IDE artifacts out unless a deliberate scaffold design requires them.
4. Design the smallest safe next experiment: a baseline BME280 chip-ID read followed by a controlled/reversible I²C transaction fault and recovery, with a **fresh successful chip-ID read after recovery** as the acceptance criterion. Prefer controlled software fault injection (e.g. temporarily force a software error/skip a transaction) over electrical shorting or unsafe pin manipulation. State exactly what the test proves and does not prove.
5. Use a staged plan: source review → local build → only then user-approved flash/debug → fresh post-recovery transaction → document raw results. Do not flash without explaining the step and waiting for the user's go-ahead.
6. Update the canonical docs/handoff/prompt on `main` after results. Preserve user evidence provenance.

## Hard constraints
- Main branch only; fetch live HEAD and current file blob SHAs before each write; sequential writes; never force-push or create/switch branches.
- Do not change `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, Gate A–E contracts, frozen K.10 evidence, prior-art reviews, manuscript, or historical records.
- Do not rerun the frozen 400-execution matrix.
- Preserve the successful LD2 GPIO recovery source and the user's external backup.
- Do not install software, purchase/borrow hardware, or ask the user to repeat USB detection, ST-LINK firmware update, old port checks, or the already successful chip-ID read.
- Distinguish user-provided logs/screenshots from checks actually performed by GitHub tools.
- No electrical shorting, forced SDA/SCL drive, unsafe voltage changes, or uncontrolled hardware fault. Do not claim physical peripheral-damage recovery from a software-injected fault.
- Keep the project goal in view: complete the smallest credible hardware demonstration, then evidence, documentation, and final audit—not endless setup diagnostics.

## Definition of done for this chat
- Exact source provenance reviewed and preserved.
- One documented baseline BME280 chip-ID result linked to the evidence report.
- A reviewed, safe recovery-test design with a measurable fresh-operation acceptance criterion.
- Local test/build/flash steps recorded with accurate provenance.
- GitHub current state, handoff, roadmap, README navigation, and next prompt consistent.
- End with one exact next action and the new commit SHA.
