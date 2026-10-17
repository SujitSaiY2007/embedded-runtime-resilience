# C Reference Runtime and Virtual Embedded System

This directory contains the authoritative software runtime, its tests and experiment harnesses, and the bounded virtual-system adapter used by the professor-facing demo.

## Components

- `src/ref_runtime.c`, `include/ref_runtime.h`: protected C11 reference runtime and public contract.
- `tests/`: reference-runtime tests and canonical workload notes.
- `experiments/`: deterministic host/K.10 experiment sources and input definitions.
- `virtual/`: modeled peripheral state, registered scenarios, CLI/JSON adapter, and virtual-system tests.
- `docs/minimal_reference_implementation.md`: compact implementation reference.

## Build and test

From repository root:

```powershell
cmake -S reference -B reference/build
cmake --build reference/build --config Debug
ctest --test-dir reference/build -C Debug --output-on-failure
```

Use the platform-appropriate CMake configuration/executable path. For the complete browser demo, see [the demonstrator guide](../docs/DEMONSTRATOR_GUIDE.md).

## Authority and integrity

The C reference runtime is authoritative for policy state transitions, action selection/application, outcomes and runtime trace records. The virtual system models environment/peripheral availability and scenario steps. The Python bridge validates inputs and launches the C CLI. The browser displays the returned records.

The following files are protected from presentation-layer edits:
- `src/ref_runtime.c`
- `include/ref_runtime.h`

Gates A–E and frozen K.10 empirical outputs are normative. Do not modify the runtime or regenerate the K.10 matrix as a way to resolve a documentation discrepancy.

## Evidence boundary

Host tests and deterministic virtual faults establish behavior only within the software/reference model. They do not establish STM32U575 timing, RAM/Flash use on target, power/energy, physical fault response, or MCU-level containment. The proposed NUCLEO-U575ZI-Q target is future work.

## Related documentation

- [Project overview](../docs/PROJECT_OVERVIEW.md)
- [Architecture map](../docs/ARCHITECTURE_AND_REPOSITORY_MAP.md)
- [Demo guide](../docs/DEMONSTRATOR_GUIDE.md)
- [Frozen K.10 results](../research/phase2_k10_p4_advantage_novelty_results.md)
