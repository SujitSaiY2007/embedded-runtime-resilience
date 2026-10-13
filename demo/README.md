# Integrated Professor-Facing Virtual Embedded-System Demonstrator (K.12)

This directory contains the live software twin for the Embedded Runtime Resilience research project. It reuses the repository's HTML/CSS/vanilla-JavaScript UI, standard-library Python HTTP bridge, bounded C virtual-system adapter, and unchanged C reference runtime.

## Execution authority and modes

```text
Browser UI (demo/index.html)
        -> Python bridge (demo/server.py)
        -> virtual_demo_cli (reference/virtual/src/virtual_demo_cli.c)
        -> bounded VirtualSystem (reference/virtual/src/virtual_system.c)
        -> frozen C reference runtime (reference/src/ref_runtime.c)
        -> JSON outcome + runtime trace + wrapper trace
        -> UI tables and evidence interpretation
```

The bridge marks live mode only when it finds the compiled C executable. The browser must not silently substitute an offline timeline after a live request fails. When no executable is present, `demo/scenarios_data.json` is a **read-only evidence view**, not an interactive execution or a substitute for current runtime output. Virtual connection controls are disabled in read-only mode.

## Prerequisites and build

Required tools: a C11 compiler, CMake 3.16+, Python 3, and a modern browser. No Python package installation is required.

From the repository root:

```sh
cmake -S reference -B reference/build
cmake --build reference/build --config Debug
ctest --test-dir reference/build --output-on-failure
```

The CMake Debug configuration can place the executable in a platform-dependent location. The Python bridge searches Windows `.exe` names and Unix executable names in `reference/build/virtual/`.

## Launch

From the repository root:

```sh
python demo/server.py 8000
```

Open http://localhost:8000/ and confirm the header displays **LIVE C REFERENCE PATH**. The diagnostic box should confirm that the C executable was found. If the UI reports **OFFLINE EVIDENCE VIEW**, build the executable before presenting interactive run claims.

## Walkthrough for a professor

1. **Independent work preservation — S01.** Select S01 and P4. Step through event admission, fault observation and recovery. Observe authoritative slot status and both traces.
2. **Dependency gating — S02.** Observe that the ordered successor remains queued until its required predecessor completes. An unrelated event can progress.
3. **Recovery progression — S06.** Run all. Observe retry followed by reinitialization and clean terminal state under the modeled deterministic schedule.
4. **Ambiguous association — S08.** Run all. Inspect the invalid target slot (`INVALID_SLOT`) and terminal escalation. The UI must not invent an event reference.
5. **Runtime correlation — S14.** Inspect wrapper spans and associated runtime trace sequence IDs. Repeat the same scenario to see a stable digest for the same run ID and configuration.
6. **Virtual hardware link failure.** With live mode active and S01 selected, disconnect I2C0, then step once. The C adapter should report `adapter_error=true` / `OUTCOME_INVALID_DEPENDENCY` before event admission mutates runtime state. Reconnect I2C0 and reset/step again. This is modeled resource availability, not arbitrary pin-level wiring.
7. **Research interpretation.** Review the separate evidence panel. It reports frozen K.10 findings rather than recalculating them from the interactive run. CF01 P2 attempt count is unresolved; CF16 P2 one attempt versus P4 three attempts remains a separate reported trade-off.

## Available CLI commands

```sh
reference/build/virtual/virtual_demo_cli --list
reference/build/virtual/virtual_demo_cli --scenario S01 --step 0 --variant 4
reference/build/virtual/virtual_demo_cli --scenario S01 --run --variant 4
reference/build/virtual/virtual_demo_cli --scenario S01 --step 1 --disconnect I2C0 --variant 4
reference/build/virtual/virtual_demo_cli --verify
```

On Windows, use the actual built `.exe` path. The `--disconnect` option accepts only `I2C0`, `SPI0`, and `UART0`; unsupported names fail closed. Each HTTP step request starts a fresh virtual scenario state through the CLI, so Reset constructs a clean execution at step zero rather than retaining mutable runtime state in Python.

## What the demo establishes

The demonstrator makes deterministic host/reference behaviour inspectable and reproducible. The frozen K.10 reports describe bounded P4 advantages in CF04/CF07 and CF05; exact-event quarantine is shared across P0–P4; six case families have no measured P4 advantage; CF16 shows a P2 attempt-count advantage over P4. `QMAX=16` and `EPMAX=1` are relevant capacity confounds.

## Limitations

- **CF01 P2 attempt count remains unresolved.** The K.10 results row says `att=3` while its explanation says one attempt; K.10.4 reports `att=1`. The cited raw K.10 CSV files are absent from the remote feature branch. Do not rerun the frozen 400-execution matrix or edit frozen results to guess the answer.
- The interactive connection control disconnects modeled virtual resources only. It does not dynamically remap scenario event definitions or physical pins.
- Host runtime sizes, digest values and host execution time are not target-MCU measurements.
- STM32U575ZI / NUCLEO-U575ZI-Q mapping is a future validation specification. Physical firmware flashing, fault injection, instrument measurements and board validation are **PENDING / NOT PERFORMED**.
- No claim of universal P4 superiority, legal novelty, non-obviousness, inventive step or patentability is made.

## Troubleshooting

| Symptom | Action |
|---|---|
| UI shows Offline Evidence View | Run `cmake -S reference -B reference/build` and `cmake --build reference/build --config Debug`, then reload. |
| C CLI test script cannot find executable | Confirm the path under `reference/build/virtual/`; run the script from the repository root or use its repo-relative path detection. |
| A disconnected resource is not referenced by the chosen scenario | The scenario can continue if its event list does not use that resource; choose a scenario that uses the resource to observe admission rejection. |
| Request returns HTTP 400 | Check scenario ID, step integer, variant 0–4, and fixed virtual peripheral ID. |
| Request returns HTTP 500/502/503/504 | Read the JSON error; check the build, executable permissions, JSON output, and 10-second bridge timeout. |
| UI becomes offline during a demo | Do not interpret a static timeline as a live run. Restore the backend and explicitly rerun the scenario. |

The UI is a display/control surface and does not implement policy logic. The repository's frozen C runtime remains the authority for recovery decisions.
