# LD2 GPIO Recovery Experiment — Preserved Source

**Purpose:** Preserve the three source files supplied by the user after the successful Chat 05.3 local STM32CubeIDE experiment and make their provenance explicit.

## Contents

- `main.c`: PA5/LD2 setup, software-injected mode fault, runtime calls, and debugger-visible results.
- `err_runtime.c`: small experiment-specific runtime and bounded GPIO recovery loop.
- `err_runtime.h`: types, state enumeration, and function declarations.

## Source provenance and preservation

These files were transcribed from the user-supplied source in Chat 06 on 24 October 2026. Whitespace and Markdown paste artifacts were normalized into plain C source; the implementation logic was not intentionally redesigned. The user's external backup of the earlier `main.c` remains separate and must not be overwritten or deleted.

This directory is a **source-preservation record**, not a complete standalone STM32CubeIDE project. It intentionally does not include generated startup code, system initialization files, linker scripts, IDE metadata, binaries, or workspace files. The local generated CubeIDE project remains the environment in which the user reported the successful build, download, and debugger run.

## Experiment scope

The code targets the STM32L476RG on the NUCLEO-L476RG board and the onboard LD2 green LED on PA5. It changes PA5 from output mode to input mode as a software-controlled configuration fault, reports peripheral ID `1U`, attempts recovery, restores output mode, writes PA5 high, and checks the GPIO mode and output data latch.

The code is a narrow hardware-specific experiment. It is not the protected C reference runtime and does not implement or validate the full P0–P4 research policies.

## User-reported evidence from 24 October 2026

The user-provided STM32CubeIDE screenshots showed:
- Build completed with 0 errors and 0 warnings.
- Download console displayed “Download verified successfully.”
- Debugger reached the final loop.
- Expected values: event count 1, fault count 1, recovery count 1, state 4 (`ERR_STATE_RECOVERED`), recovered 1, fault injected 1, GPIO mode 1 (output), and GPIO output latch 1 (high).

These are user-supplied screenshot observations, not checks performed by GitHub or CI. The successful run does not prove physical peripheral-damage recovery, measured pin voltage, sensor operation, repeatability, worst-case timing, stack/energy usage, or target equivalence between STM32L476RG and the earlier proposed STM32U575ZI.

## Reproducibility status

Source is preserved here, but a clean, independently repeated build from a repository checkout has **not** been performed. To reproduce the reported result, use the existing local STM32CubeIDE 2.2.0 project that was used for the successful run; do not import this folder over the working project or copy generated project files blindly. Before a future rebuild or download, verify the selected project, target, and build configuration. Inspect the eight debugger variables listed above after execution.

The source record alone does not establish a reproducible, clean-room build. That requires a later reviewed project/scaffold decision and an actual build test.


## Local CubeIDE configuration review — 2026-10-24

The user supplied screenshots from the existing local STM32CubeIDE 2.2.0 project properties. Confirmed from those screenshots:
- Active configuration: `Debug`.
- Workspace toolchain: GNU Tools for STM32 `14.3.rel1`.
- Compiler language standard: GNU11 (`-std=gnu11`).
- Linker script field: `${workspace_loc:/${ProjName}/STM32L476RGTX_FLASH.ld}`, resolving to the project-root Flash linker script.
- Linker options visible: map-file generation enabled; unused-section removal enabled; system calls set to Minimal implementation (`--specs=nosys.specs`).
- Project tree shows source/startup folders, generated Debug build artifacts, an ELF/list/map, a debug launch configuration, and both `STM32L476RGTX_FLASH.ld` and `STM32L476RGTX_RAM.ld` files.

The screenshots do not establish the full compiler CPU/FPU flags, whether the RAM linker script is ever selected, or a clean rebuild from a repository checkout. The user explicitly requested that configuration inspection stop here and that work proceed; do not request further settings screenshots unless a concrete reproducibility blocker later requires one. No settings were intentionally changed during inspection. These are user-provided screenshot observations, not repository-side verification.