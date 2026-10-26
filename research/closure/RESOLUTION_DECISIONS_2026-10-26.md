# Issue-Resolution Decisions and User-Handoff — 26 October 2026

**Repository:** SujitSaiY2007/embedded-runtime-resilience  
**Execution branch:** main (per current repository policy)  
**Protected baseline:** exp and all canonical reference/, Gates A–E, frozen K.10 records remain untouched.

## Executive decision

Proceed with an additive candidate under reference_v2/. This is the technical work area for addressing defects and testing new baselines without rewriting the protected reference runtime. These are the technical lead's working decisions, not claims that an external professor or journal has approved anything.

## Findings and decisions

| Item | Current finding | Decision / action |
|---|---|---|
| Original K.10 CSVs | reference/experiments/out/k10_runs.csv and k10_traces.csv are absent at those repository paths. The manuscript audit reports them absent from all remote branches. | Search the author's PC for original outputs. Never overwrite/regenerate in the original out/. A new corrected 560-run P0–P6 campaign has a separate runner and fresh output path. |
| Hardware screenshots, Chats 05–11 | Evidence reports exist, but original PNG screenshots are not committed. | User must provide original PNGs or commit them from the local evidence folder. These cannot be reconstructed from written summaries. |
| 80-element matrix export | A status discrepancy remains in the hardware report. | Request a full debugger export only if the original terminal session is still available; otherwise preserve the discrepancy and make no full-array claim. |
| Exact flashed firmware | Three firmware candidates exist; the precise flashed file is not hash-linked to the saved run. | User should identify the actual file and provide its SHA-256 or exact local source file. |
| Tool versions | Some versions are recorded; complete build environment/MSVC metadata is not. | Capture only missing version fields locally; do not repeat completed CubeIDE configuration checks. |
| O-01 full-queue release | Canonical source appends without checking queue capacity in runtime_verify_and_release(); existing repository probe describes assertion/out-of-bounds failure. | Candidate adds a capacity check and leaves the event quarantined if release cannot fit. |
| O-02 8-bit generation exhaustion | Canonical runtime uses an 8-bit generation field with zero reserved; reuse eventually fails at the 255 boundary. | Candidate widens generation token and counter to 16 bits. It still has a finite lifetime bound at 16-bit exhaustion; state this limit. |
| O-03 invalid-target episode leak | Canonical policy path can return OUTCOME_STALE_REF without closing the active episode. | Candidate closes the episode as terminal escalation before returning stale-reference status. This may reduce the original P4 advantage and requires a corrected campaign. |
| O-04 trace cap | Canonical trace buffer silently stops at 256 records. | Keep the fixed-size buffer for bounded memory; candidate adds a saturating dropped-record counter. It exposes loss but does not recover omitted records. |
| O-05 unreachable reason/scope code | Existing manuscript probe reports reason code 18 unreachable and the scope clamp ineffective. | Treat as a code-quality finding, not a performance claim. Clean up only in v2 after tests show no intended semantic dependency. |
| 255 admission / 256 trace limits | Design boundaries, not journal decisions. | Widen generation token in v2; retain 256-record bounded buffer but report dropped records. Re-evaluate memory cost in the resource table. |
| P5/P6 baselines | Not in protected P0–P4 runtime. | Define P5 as immediate reset/reinitialization-only (no retry) and P6 as retry-only, up to three retries with exponential logical backoff units (1, 2, 4, then escalation). These are in-house comparators, not published baselines. No elapsed-time claim is made. |
| Corrected host campaign | Must be run after v2 compiles. | New runner expects 16 families × 7 policies × 5 repetitions = 560 runs, checks matrix/repetition stability, and compares replay SHA-256. Original 400-run evidence remains frozen. |
| Control/repeated hardware runs | Existing hardware evidence is one controlled wrong-address NACK; no no-reinit control or independent repeatability evidence is recorded. | Plan a 30-trial control and 30 trials per policy only after local candidate tests and source review. Keep no-reinitialization control separate. |
| MCU resource measurements | No verified flash/RAM/stack/decision-latency measurements are in the evidence report. | Measure on STM32L476RG with build-identical firmware and report core clock/optimization. Do not estimate MCU numbers from host sizeof. |
| Physical stuck-SDA | Not demonstrated; optional. | Do only after wiring and open-drain safety review. Never drive the bus high push-pull against a pin holding it low. |
| Journal/reference ratio | Draft cites 6/10 journal articles, below the recorded 75% target. | Treat 75% as a working requirement; verify relevant primary journal papers rather than padding. Recheck publisher venue guidelines before final formatting. |
| Professor involvement | User requests no professor involvement until the end. | Do technical triage and research-method decisions as project lead. Do not invent author affiliations, consent, institutional declarations, or final author approvals. Present those for author confirmation at the final submission gate. |

## Candidate files added

- reference_v2/src/ref_runtime.c
- reference_v2/include/ref_runtime.h
- reference_v2/tests/test_runtime_edge_cases.c
- reference_v2/CMakeLists.txt
- reference_v2/experiments/k10_v2_experiment.c
- reference_v2/experiments/run_k10_v2.py
- reference_v2/README.md
- reference_v2/CHANGELOG.md

The candidate has **not yet been compiled or executed in this chat**. A local git clone was unavailable in the current environment, so these source changes must not be described as passing. Build/test output is the next required gate.

## User help needed now — only these items

1. **Local compile/test:** pull latest main, then run:
   ```powershell
   cmake -S reference_v2 -B reference_v2/build
   cmake --build reference_v2/build
   ctest --test-dir reference_v2/build --output-on-failure
   ```
   Send complete terminal output, including any compiler/test failure. Do not flash this candidate to the board.
2. **Original evidence search:** search the local PC for k10_runs.csv and k10_traces.csv. If found, send them unchanged. If not found, say “not found”; use separate v2 outputs only after the candidate passes tests.
3. **Hardware originals:** when convenient, provide original PNGs from the existing evidence folder (not messaging-app copies) and the exact firmware file flashed, if available. No new hardware run is needed just to supply files.
4. **Professor decisions are deferred:** no need to contact the professor now. The eventual human-confirmation items are factual authorship/affiliation/declaration details and final manuscript approval.

## Next sequence

1. Build and test v2.
2. Fix candidate build/test failures; do not proceed on a failing build.
3. Run the new 560-execution P0–P6 campaign in a new dated folder; inspect matrix/manifest checks and compare outcomes against the frozen report without replacing it.
4. Finish reference verification and the claim-to-evidence ledger.
5. Collect control/repeated hardware logs and MCU resource measurements with the user at the board.
6. Update manuscript results and references from validated artifacts.
7. Perform final author metadata and submission-format confirmation at the end.

**No universal P4 superiority claim is accepted in advance.** O-03's correction is expected to alter the previously reported P4 advantage; new evidence must determine the conclusion.
