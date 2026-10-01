# Host Experiment Harness

This directory is the smallest host-only reproducibility layer over the committed reference runtime.

## Inputs

- `workloads.csv` is the declarative workload operation stream.
- `fault_schedules.csv` is the deterministic fault/action schedule.
- Neither file is generated from test assertions at runtime.

## Build

From `reference/`:

```text
cmake -S . -B build
cmake --build build
```

## Run

```text
python3 experiments/run_host_experiment.py
```

The script:

1. copies the raw input schedules into a timestamp-independent corpus directory;
2. runs the C harness for P0-P4 over the same workload/fault inputs;
3. writes machine-readable run summaries and traces;
4. reruns the harness and compares SHA-256 hashes for deterministic replay;
5. writes `corpus_manifest.csv`.

## Outputs

`out/` contains:

- `raw/workloads.csv`
- `raw/fault_schedules.csv`
- `runs.csv`
- `trace.csv`
- `corpus_manifest.csv`

The harness records `capacity_confounded` for W09/W10 and `ablation_contract_valid` as 0 for P0-P3 because the current reference implementation applies exact-event quarantine to every variant. This is an implementation qualification, not an amendment to Gates A-E.

## Evidence boundary

All outputs are host/reference/software-injection evidence. They do not measure STM32U575 timing, RAM, Flash, energy, electrical fault behavior, or physical recovery.
