# Minimal Reference Implementation

This directory contains the smallest executable host/reference prototype for the frozen Gates A-E contracts.

## Build and test

```text
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The test suite covers W01-W14 plus bounded-recovery and static-accounting checks.

## Evidence boundary

Passing host tests establish reference-model/software-injection behavior only. They do not establish STM32U575 timing, RAM/Flash, physical fault behavior, energy, statistical significance, generalization, novelty, or patentability.

## Trace output

The runtime keeps a fixed trace pool and provides `trace_write_csv()` for deterministic structured output. The schema includes run/trace/episode identity, EventRef generation, action index, outcome, and correctness.

## Zero-heap audit

There are no allocator calls in `include/`, `src/`, or `tests/`. The reference runtime uses fixed arrays and bounded records. Host-library behavior is not presented as MCU heap evidence.
