# Software Reproducibility Procedure

**Purpose:** Reproduce the repository's live host/reference software tests and browser demonstrator. This procedure does **not** reproduce the physical STM32/BME280 run and does not rerun or overwrite the frozen 400-execution research corpus.

## 1. Environment

Required:
- Git
- C11-capable compiler supported by CMake
- CMake 3.16 or newer
- Python 3
- Modern browser

The software demonstrator requires no API keys, paid services, or third-party Python packages for its documented path.

Record OS/version, compiler/version, CMake version, Python version, repository commit SHA, and date in the manuscript or supplementary material.

## 2. Obtain a clean checkout

From PowerShell:

```powershell
git clone https://github.com/SujitSaiY2007/embedded-runtime-resilience.git
cd embedded-runtime-resilience
git switch main
git status --short
git rev-parse HEAD
```

If already cloned, use `git pull --ff-only origin main` and record the resulting commit SHA. Do not reset, force-push, change branches, or modify protected evidence files.

## 3. Configure and build the C reference/virtual system

Run from the repository root:

```powershell
cmake -S reference -B reference/build
cmake --build reference/build --config Debug
```

Save the full terminal output. If configuration or compilation fails, record the exact command, tool versions, and error rather than silently changing the source.

## 4. Run the available C tests

```powershell
ctest --test-dir reference/build -C Debug --output-on-failure
```

Record the number of tests discovered, passed, failed, and the process exit code. A successful result means the current test suite passed on this host; it is not a physical MCU result.

## 5. Run UI contract tests

```powershell
python demo/test_ui_contracts.py
```

Record the exact output and exit code. Do not report this as an independent CI run unless a separate CI system actually ran it.

## 6. Launch the browser demonstrator

In a terminal at the repository root:

```powershell
python demo/server.py 8000
```

Keep this terminal open. In a browser, visit:

```text
http://localhost:8000/
```

If port 8000 is occupied, use another port, such as `python demo/server.py 8080`, and open `http://localhost:8080/`.

## 7. Perform a controlled software demonstration

1. Confirm the page loads and the server terminal remains active.
2. Select one registered scenario and a policy variant.
3. Reset the run.
4. Use Step Next/Back to inspect deterministic progression.
5. Use Play and Run All to check the remaining controls.
6. Capture the final outcome and runtime trace together with the selected scenario and policy.
7. If testing peripheral admission, disconnect only the virtual peripheral identified by the scenario, observe the explicit rejection, reconnect it, reset, and rerun.
8. Capture the server output for any error; do not interpret a stale UI result as a successful live run.

Do not describe the browser's virtual-system run as executing on the STM32. The C reference runtime supplies the software decision/trace; the UI presents it.

## 8. Preserve the frozen 400-execution evidence

The existing campaign is documented as 16 case families × 5 policies × 5 repetitions = 400 executions. Treat it as frozen research evidence.

- Do not rerun the campaign as part of this basic reproducibility check.
- Do not overwrite or regenerate frozen raw results.
- If a separate future rerun is formally approved, write it to a new output location, record the exact source commit and commands, and compare it against—not replace—the frozen results.
- Keep software campaign results separate from the live demonstrator's current run.

## 9. Evidence to save for the paper

Create a reproduction record containing:
- Repository URL and exact commit SHA
- OS, compiler, CMake, and Python versions
- Commands executed
- Build and test outputs, including exit codes
- Scenario ID, policy, and run result
- Runtime trace and any errors
- Date and whether the run was performed by the authors or independently by another researcher

Screenshots can supplement logs but should not replace command output or machine-readable result files.

## 10. What this procedure does not prove

Passing these steps supports host-level software reproducibility only. It does not establish:
- execution on a physical microcontroller;
- physical fault injection or recovery;
- MCU timing, stack/RAM usage, flash usage, power, or energy overhead;
- repeated physical-trial reliability;
- universal superiority of P4; or
- independent reproduction by another lab.

The separate hardware evidence report should be cited for the bounded STM32L476RG/BME280 experiment. Do not combine the software and physical results into one undifferentiated sample count.
