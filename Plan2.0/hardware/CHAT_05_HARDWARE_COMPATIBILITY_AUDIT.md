# Chat 05 — Hardware Compatibility Audit

**Date:** 2026-10-22  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Branch:** `main` only  
**Audit baseline commit:** `52bf814862fec94d991f190b28a01698996d4223`  
**Outcome:** `PARTIALLY VERIFIED`; BME280 wiring is `BLOCKED` pending physical module identification.

## 1. Scope and evidence rules

This is a repository/documentation and official-documentation audit. The physical board, sensor, cable, resistor packs, buttons, breadboard, and jumper wires were not available for direct inspection in this audit. Their actual markings therefore remain unverified. No circuit has been wired or powered, and no physical test has been performed.

The only approved additional-hardware budget is **₹0**. Do not buy or borrow anything to resolve blockers.

## 2. Live repository baseline

- Live default branch: `main`.
- Initial commit SHA: `52bf814862fec94d991f190b28a01698996d4223`.
- Working-tree status: **not available through the GitHub API audit**; this is not a local clone and no local `git status` was run.
- Existing Plan2.0 root contains Chat 01–04 handoffs. No `Plan2.0/hardware/` directory existed at audit start.
- Existing hardware planning document: [HARDWARE_DEMONSTRATION.md](../HARDWARE_DEMONSTRATION.md).
- Protected runtime files were inspected by repository metadata: `reference/src/ref_runtime.c` blob `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81`; `reference/include/ref_runtime.h` blob `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`.
- The CMake project is a C11 host/reference runtime with tests, host experiment executables and a virtual-system subproject. No hardware-specific BME280, STM32 HAL, GPIO, I²C driver or board-adaptation file was found in the inspected repository paths/search results. A full local filesystem search was not possible.
- Repository documentation explicitly says the 400-run campaign is host/reference-model evidence and that firmware integration and physical recovery verification remain pending.

## 3. Fixed board: identity and capabilities

**User-specified starting point:** STMicroelectronics NUCLEO-L476RG, product identifier NUCLEO-L476RGSKU1, MB1136 revision C.

**Status:** `PARTIALLY VERIFIED`. ST’s official product page identifies NUCLEO-L476RG as a Nucleo-64 board using STM32L476RG, with Arduino Uno V3 and ST Morpho connectors and an onboard ST-LINK debugger/programmer. The official UM1724 board manual identifies the MB1136 family and includes NUCLEO-L476RG pin tables. The actual board’s silk-screen, product code and MB1136 revision still require the user to check the physical board.

### Official references

1. STMicroelectronics, [NUCLEO-L476RG product page](https://www.st.com/en/evaluation-tools/nucleo-l476rg.html). Establishes the board family, MCU, connectors and integrated ST-LINK.
2. STMicroelectronics, [UM1724 — STM32 Nucleo-64 boards (MB1136) user manual, PDF](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf), especially the NUCLEO-L476RG layout and Table 23 (Arduino connector mapping).
3. STMicroelectronics, [STM32L476RG product page](https://www.st.com/en/microcontrollers-microprocessors/stm32l476rg.html). MCU overview including the Cortex-M4, memory and MPU.
4. Bosch Sensortec, [BME280 datasheet, PDF](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf), and [official BME280 product page](https://www.bosch-sensortec.com/en/products/environmental-sensors/humidity-sensors-bme280).

## 4. Board-side interface findings

UM1724 Table 23 maps the NUCLEO-L476RG Arduino connectors as follows:

- Arduino D14: PB9, I2C1_SDA.
- Arduino D15: PB8, I2C1_SCL.
- Arduino A4: PC1 or PB9 (PB9 provides I2C1_SDA depending on the board configuration/solder-bridge routing).
- Arduino A5: PC0 or PB8 (PB8 provides I2C1_SCL depending on the board configuration/solder-bridge routing).
- CN6 provides board 3.3 V, 5 V, GND and VIN pins, but this does **not** establish which voltage is safe for an unidentified sensor breakout.

This establishes candidate MCU/board I²C routing, **not an approved wiring instruction**. Before use, verify the actual board revision and solder-bridge configuration from UM1724 and the matching schematic. Firmware pin configuration and bus timing must also be checked. No wiring is approved at this stage.

## 5. Purchased inventory — receipt information preserved

| Item as described | Receipt quantity | Receipt total | Audit status |
|---|---:|---:|---|
| 4-pin, 5 mm push-button packs, three buttons per pack | 2 packs | ₹20 | Exact switch pin geometry not physically checked |
| MB-102 solderless breadboard, 830 tie points | 1 | ₹69 | Model recorded; actual condition/layout not inspected |
| Programming cable described as for Arduino Uno/Mega | 1 | ₹40 | Connector ends and data capability unknown |
| Resistor packs | 4 | ₹20 | Resistance values/tolerance unknown |
| Jumper-wire items/packs | 6 | ₹60 | Actual wire types and item counts unknown |
| BME280 sensor/module | 1 | ₹530 | Exact breakout/model and pinout unknown |
| **Total already spent** | | **₹739** | Receipt total only; no further spending approved |

The receipt does not establish that the programming cable has the connector needed by the Nucleo board. Nor does the product label “BME280” identify the breakout’s regulator, level shifting, pull-ups, supply pin, or connector layout.

## 6. BME280 chip versus breakout board

Bosch’s bare BME280 device supports I²C and SPI. Bosch specifies bare-chip supply ranges of VDD 1.71–3.6 V and VDDIO 1.2–3.6 V. Those chip specifications **cannot be applied automatically to the purchased module’s supply pin**: a breakout may add a regulator, level shifting, pull-up resistors, or a different pin arrangement.

| Compatibility requirement | Evidence currently available | Status |
|---|---|---|
| Exact module manufacturer/model | Receipt says only “BME280 sensor/module” | `UNVERIFIED` |
| Bare sensor vs breakout | No physical image/markings inspected | `UNVERIFIED` |
| Module supply-pin voltage range | Unknown breakout circuitry | `UNVERIFIED` |
| I/O logic voltage | Unknown breakout circuitry | `UNVERIFIED` |
| GND/VCC/SDA/SCL pin labels/order | No module pinout | `UNVERIFIED` |
| Onboard regulator/level shifting | Unknown | `UNVERIFIED` |
| I²C pull-ups and their rail | Unknown | `UNVERIFIED` |
| I²C address selection | Unknown SDO/CS wiring and board design | `UNVERIFIED` |
| Board-side candidate I²C pins | UM1724 Table 23 maps PB9/PB8 to I2C1 SDA/SCL | `PARTIALLY VERIFIED` |
| Firmware/driver compatibility | No sensor driver or STM32 hardware adapter found in inspected repository paths | `UNVERIFIED` |

**Verdict: `BLOCKED` for physical sensor wiring.** The BME280 silicon’s I²C capability alone is insufficient to approve this unknown module. Do not connect its power, SDA or SCL pins until the module’s exact identity, pinout, supply and logic levels, and pull-up arrangement have been established.

Minimum evidence needed to reopen this gate: one clear photo showing the whole module and every pin label, plus any legible board/PCB marking or packaging model number. This is a request for evidence only; no purchase is needed. If a clear identification still cannot establish electrical specifications, leave it blocked.

## 7. Programming cable

ST states that the NUCLEO-L476RG has an onboard ST-LINK debugger/programmer; a separate debugger is not normally required. The board’s ST-LINK USB connector is the intended host connection for programming/debugging and the virtual COM port.

The purchased cable description “for Arduino Uno/Mega” is not enough to determine compatibility. Inspect both ends and compare the board-side connector with the actual ST-LINK connector on the board. Confirm the cable carries USB data, not merely power. Do not connect it by force or use an incompatible connector.

- Integrated ST-LINK on board family: `VERIFIED` from ST product documentation.
- Actual connector on user’s board and matching cable end: `UNVERIFIED`.
- Whether the cable supports data: `UNVERIFIED`.
- Programming connection with the exact cable: `BLOCKED` pending physical connector check.

No replacement cable is recommended.

## 8. Buttons, resistors, breadboard and wires

- **Buttons:** the Nucleo board includes a user push-button. This may be sufficient for an initial button event after board identity and firmware configuration are checked. The purchased buttons’ pin geometry is unknown; do not infer which pins are internally connected.
- **Resistors:** values are unknown. Any design depending on an external resistance is blocked until the value is read/measured. Do not use an unknown resistor to set sensor pull-ups or supply current.
- **Breadboard:** MB-102 is the recorded model. Its actual rail continuity, split points and condition were not checked. Do not assume power rails are continuous without verifying the exact board.
- **Jumper wires:** receipt quantity does not mean six individual wires. Wire type, male/female ends and quantity remain unverified.
- **Reuse decision:** the existing board, onboard button/LED, and integrated ST-LINK are potential zero-cost resources. The breadboard, purchased switches, resistors, jumper wires and BME280 are not approved for circuit use until the relevant details above are checked.

## 9. Hardware target discrepancy

Plan2.0/CURRENT_STATE.md and the existing hardware plan record an earlier NUCLEO-U575ZI-Q / STM32U575ZI target, while the fixed board for this phase is NUCLEO-L476RG. These targets are not interchangeable by assumption. STM32L476RG has an MPU, but equivalence to any intended U575-specific features, security configuration, memory, peripheral availability, or planned measurements has not been established.

Do not silently change the scientific claim or port the runtime. A separate documented capability/requirements comparison is needed before committing to the L476 as the final research target.

## 10. Compatibility decision

- Board family documentation: `PARTIALLY VERIFIED` (actual physical marking/revision still to be checked).
- Candidate I²C mapping PB9/SDA and PB8/SCL: `PARTIALLY VERIFIED` (board manual mapping found; solder bridges/configuration and firmware not checked).
- BME280 breakout electrical compatibility: `UNVERIFIED`.
- Cable programming suitability: `UNVERIFIED`.
- Physical wiring: `BLOCKED`.
- Ready for safe wiring: **No**.
- Additional purchase: **None permitted or recommended**.
