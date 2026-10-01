# Software Demonstrator

This is the professor-facing software-only proof-of-concept UI for the project.

## Use

Open `demo/index.html` in a browser. No external package or service is required.

The UI demonstrates the frozen end-to-end mechanism: fault observation -> context/history -> event quarantine -> bounded recovery -> verification/release or terminal outcome -> traceable explanation.

## Authority and evidence boundary

The ISO C11 implementation under `reference/` remains the authoritative software implementation and the host experiment corpus remains the executable evidence layer. The UI is a presentation/demonstration layer and must not be treated as a second implementation of the research specification.

The demonstration is host/software-only. It does not establish STM32U575 RAM/Flash/timing, MPU behavior, electrical fault behavior, physical recovery, statistical significance, or novelty/patentability.