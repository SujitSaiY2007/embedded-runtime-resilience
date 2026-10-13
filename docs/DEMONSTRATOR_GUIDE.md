# Software Demonstrator Guide

## Purpose

Run the professor-facing virtual embedded-system demonstrator. It exercises the registered scenario through the C virtual adapter and the same C reference runtime used by the research. It does not execute on a physical MCU.

## Prerequisites

- C11-capable compiler supported by CMake
- CMake 3.16 or newer
- Python 3
- Modern browser
- No API keys, paid APIs, or third-party Python packages required

## Build and test (Windows PowerShell)

Run from the repository root:

```powershell
cmake -S reference -B reference/build
cmake --build reference/build --config Debug
ctest --test-dir reference/build -C Debug --output-on-failure
python demo/test_ui_contracts.py
```

If the project was already configured in `reference/build`, the configure step is usually unnecessary. If the executable path differs by platform/configuration, use the location emitted by the build; the bridge searches common Windows and Unix executable locations.

## Launch

In a separate terminal, from the repository root:

```powershell
python demo/server.py 8000
```

Open [http://localhost:8000/](http://localhost:8000/) and keep the server terminal running.

## Professor-demo sequence

1. Explain the research question and bounded evidence from the project overview.
2. Select a registered scenario and policy variant.
3. Use Reset, Step Next/Back, Play, or Run All to show deterministic execution.
4. Show the runtime outcome and runtime trace alongside the virtual wrapper trace.
5. Disconnect a peripheral used by the selected scenario; run it and show the explicit admission rejection.
6. Reconnect the peripheral, reset, and rerun to demonstrate a valid execution path.
7. Explain that the C runtime supplies the decision/trace and the UI only presents it.
8. Close with the measured scope, counterexamples, resource limits, and future hardware plan.

## Acceptance checklist

- [ ] UI loads and the server remains running.
- [ ] Scenario and policy variant selection works.
- [ ] Reset, step controls, Play, and Run All behave coherently.
- [ ] Live requests return current C output; errors are not silently replaced by stale success.
- [ ] Disconnected peripheral rejects dependent admission visibly.
- [ ] Reconnection followed by reset/rerun restores the valid path.
- [ ] Runtime and wrapper traces are populated and correlated.
- [ ] Frozen research evidence is clearly distinguished from live run output.
- [ ] No UI text implies physical hardware validation.
- [ ] CTest and `python demo/test_ui_contracts.py` pass.

## Troubleshooting

- **CLI not found:** build with CMake and inspect `reference/build/virtual/` for the platform-specific executable.
- **Port in use:** start on another port, e.g. `python demo/server.py 8080`, then open `http://localhost:8080/`.
- **HTTP validation error:** confirm scenario ID, step index, policy variant, and peripheral identifier.
- **Bridge/CLI error:** inspect server terminal JSON error, rebuild, and rerun the test suite.
- **UI appears stale:** stop the server, restart it from the repository root, and hard-refresh the browser (Ctrl+F5).
- **Offline/read-only view:** do not interpret static evidence data as a live execution. Restore the built CLI path and explicitly rerun the scenario.

## Scope note

The local build/tests/browser run was reported successful by the user on 2026-10-13. This repository record does not claim independent CI reproduction. Physical board execution and measurement remain future work.
