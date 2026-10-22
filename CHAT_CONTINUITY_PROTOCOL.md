# Chat Continuity Protocol — Embedded Runtime Resilience

## Current active state (2026-10-22)

The software/research baseline K.10–K.12 remains finalized and protected. Plan 2.0 hardware bring-up is now active. Chat 05.2 is paused at an ST-LINK/GDB initialization failure; the next continuation is Chat 05.3.

Canonical live hardware state: Plan2.0/CURRENT_STATE.md  
Previous chat handoff: Plan2.0/handoffs/CHAT_05_2_HANDOFF.md  
Next execution prompt: Plan2.0/prompts/CHAT_05_3_STLINK_DEBUGGER_CONTINUATION_PROMPT.md

## Canonical startup reading

1. README.md
2. Plan2.0/README.md
3. Plan2.0/CURRENT_STATE.md
4. Plan2.0/CHAT_PROTOCOL.md
5. Plan2.0/EXECUTION_ROADMAP.md
6. Latest Chat 05.2 handoff and Chat 05.3 continuation prompt.
7. Original Chat 05.2 prompt and hardware compatibility audit for inventory/safety gates.
8. Read the protected research/software records only as relevant; do not rerun the frozen 400-run matrix.

## Current hardware truth

User evidence shows the NUCLEO-L476RG board powers on and is detected over USB; ST-LINK firmware update to V2J48M35 succeeded; the generated CubeIDE empty project builds with 0 errors and 0 warnings. The GDB server does not start and reports ST-LINK initialization failure plus port bind errors on 61234/61235. The same two ports returned no matching netstat entries. The user does not have standalone STM32CubeProgrammer. Firmware flashing, MCU execution, sensor reads, fault injection and recovery are not verified.

## Integrity and safety rules

- Work on main only; no new branches, switching branches, merges or force-pushes.
- Before writing, inspect live main HEAD and re-fetch/reconcile files.
- Preserve reference/src/ref_runtime.c, reference/include/ref_runtime.h, Gate A–E contracts, frozen K.10 evidence, experiment sources/configuration, prior-art analysis, manuscript and historical records.
- Never represent host/virtual results as physical MCU evidence.
- Do not claim universal P4 superiority, legal patentability, or unverified hardware results.
- Do not rerun already completed hardware checks without a new evidence-based reason.
- No new purchases, borrowing, installations or dependencies; budget is ₹0.
- Do not wire the BME280-labelled module until exact identity, pinout, supply/logic levels, pull-ups and board routing are verified and an exact wiring table is reviewed.
- Distinguish user-reported observations from independently reproduced checks and CI evidence.

## Required closeout

Record Chat ID/date, exact branch and commit SHA, files changed, commands/checks actually performed and their provenance, evidence status, blocker/risks, and one exact next prompt. Never say a check passed if it was not run. The hardware task may remain BLOCKED if available tools/hardware do not permit safe verification.
