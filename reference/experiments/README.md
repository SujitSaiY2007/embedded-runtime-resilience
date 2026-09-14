# Host Experiment Harness

This directory contains the smallest reproducible host experiment layer for the frozen Gate E protocol.

## Evidence boundary

All outputs are **host/reference evidence** from the committed ISO C11 model and deterministic software fault injection. They are not STM32U575 timing, RAM, Flash, energy, or physical-fault evidence.

## Inputs

- `workloads.txt` — explicit canonical workload records.
- `fault_schedules.txt` — explicit deterministic fault/recovery schedules.

The harness must consume these records as data; workload behavior is not hidden inside the harness test logic.

## Intended output layout

```text
reference/experiments/results/
  raw_inputs/
  traces/
  summaries/
```

Each variant/run receives a stable `run_id` and `trace_id` derived from the explicit workload, schedule, and variant identifiers. Matched P0-P4 runs reuse the same workload/schedule records.

Capacity-related outcomes are reported separately and flagged as `CAPACITY_CONFOUNDED` when the scenario's result cannot be interpreted as a mechanism comparison without queue/quarantine/episode capacity effects.

No statistical estimation is performed by this harness.
