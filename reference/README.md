# Minimal Reference Implementation

This directory contains the smallest executable host/reference prototype for the frozen Gates A-E contracts.

## Current status

**Host/reference foundation complete.** Gates A-E, K.1, K.2, and K.3 are complete; the active software phase adds a professor-facing demonstrator without changing this reference.

## Build and test

```text
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The test suite covers W01-W14 plus bounded-recovery and static-accounting checks.

## K.3 final status

**K.3 COMPLETE — host/reference final-synthesis checkpoint.** Gates A-E remain frozen. K.1/K.2 host verification and corpus validation are complete.

### Mandatory qualifications

- **P0-P3 are not clean quarantine ablations.** The current runtime applies exact-event quarantine across all variants; therefore `ablation_contract_valid=0` for P0-P3 and `=1` for P4 under the current implementation boundary.
- **W09/W10 are capacity-confounded.** Their results are explicit capacity-boundary observations, not unconstrained policy comparisons.
- **MCU/physical evidence is absent.** Software fault injection is deterministic host stimulus, not physical fault validation.



Passing host tests establish reference-model/software-injection behavior only. They do not establish STM32U575 timing, RAM/Flash, physical fault behavior, energy, statistical significance, generalization, novelty, or patentability.

## Trace output

The runtime keeps a fixed trace pool and provides `trace_write_csv()` for deterministic structured output. The schema includes run/trace/episode identity, EventRef generation, action index, outcome, and correctness.

## Zero-heap audit

There are no allocator calls in `include/`, `src/`, or `tests/`. The reference runtime uses fixed arrays and bounded records. Host-library behavior is not presented as MCU heap evidence.


## Software demonstrator relationship

`demo/index.html` is the presentation layer for the software proof of concept. This C reference remains the authoritative executable software model; the UI must not be treated as a replacement specification.

The current software-phase methodology lock is recorded in `research/phase1_software_demonstrator_methodology_lock.md`.