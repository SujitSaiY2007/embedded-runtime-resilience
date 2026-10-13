# Live Software Demonstrator

This folder implements the professor-facing UI and the HTTP-to-C execution bridge. For the curated runbook, see [../docs/DEMONSTRATOR_GUIDE.md](../docs/DEMONSTRATOR_GUIDE.md).

## Live architecture

```text
demo/index.html
  → demo/server.py
  → reference/virtual/src/virtual_demo_cli.c
  → reference/virtual/src/virtual_system.c
  → reference/src/ref_runtime.c
  → JSON result (outcome, digest, runtime trace, wrapper trace)
  → browser UI
```

The C reference runtime remains the sole authority for recovery decisions. The UI and Python bridge do not implement a competing recovery policy.

## Run

From the repository root:

```powershell
cmake -S reference -B reference/build
cmake --build reference/build --config Debug
ctest --test-dir reference/build -C Debug --output-on-failure
python demo/test_ui_contracts.py
python demo/server.py 8000
```

Open http://localhost:8000/. Keep the server terminal running.

## Modes and failure behavior

The bridge should report live execution only when it can find and invoke the compiled C CLI. Static scenario/evidence data, where used, is read-only and must never be presented as a fresh runtime execution. A live request error must remain visible rather than silently falling back to a stale success. Virtual connection controls require live mode.

## What the demo proves

It demonstrates the software integration path, registered scenarios, policy-variant requests, bounded virtual resource availability, and display of runtime/wrapper traces returned by the C execution path.

It does not demonstrate physical pins, an MCU running the firmware, electrical fault injection, hardware timing, energy consumption, or measured MCU memory use.

## Validation provenance

On 2026-10-13, the user reported that local CTest/UI contract tests passed and that the browser demo worked. This has not been independently reproduced by a remote CI runner. Keep that distinction in any presentation.
