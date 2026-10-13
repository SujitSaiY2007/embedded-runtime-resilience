# Embedded Runtime Resilience — Complete Project Understanding & Repository Guide

**Document status:** Integrated project guide / handoff baseline  
**Prepared:** 2026-10-13  
**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Current working branch:** `feature/k10-4-final-technical-conclusion-2026-10-13`  
**Canonical research branch:** `exp`  
**Integration target:** `main` (readiness preparation only; not synchronized by this document)  
**Research topic:** *Design and Implementation of a Lightweight Zero-Heap Context-Aware Peripheral Recovery Policy with Event Quarantine for Resource-Constrained MPU-Enabled Event-Driven MCU Firmware*

---

## 1. Why this document exists

This is the orientation document for understanding the project as a complete research artifact, not just as a demo that runs. It connects the motivation, hypothesis, reference runtime, policy variants, experimental evidence, virtual demonstrator, repository governance, limits, and the next review sequence.

Use it alongside, not instead of, the detailed authoritative artifacts:
- `PROJECT_MANUAL.md` — scope and research rules.
- `PROJECT_STATE.md` — current checkpoint state and history.
- `CURRENT_HANDOFF.md` — current operating constraints.
- `DECISION_LOG.md` — recorded decisions.
- `NEXT_CHAT_PROMPT.md` — checkpoint execution instructions.
- `research/PART_II_CHAT_PLAN.md` — authoritative Part-II sequence.
- `research/phase2_k10_p4_advantage_novelty_results.md` — frozen K.10 results.
- `research/phase2_k10_4_final_technical_distinction_and_research_conclusion.md` — technical distinction and bounded conclusion.
- `research/phase2_k11_final_software_synthesis_and_hardware_handoff.md` — software synthesis and proposed hardware validation.
- `research/phase2_k12_professor_facing_software_demo_and_final_audit.md` — K.12 implementation/audit record.
- `research/chat_records/` — checkpoint-level provenance.

If a short summary conflicts with a frozen result report or a protected decision, stop and reconcile against the authoritative source. Do not silently harmonize contradictions.

## 2. Project in one minute

The project studies a small, deterministic, zero-heap recovery policy for event-driven embedded firmware. When a peripheral fault occurs, the runtime observes the fault in the context of the affected event and limited recovery history, quarantines the event associated with the fault, and selects a bounded recovery action. The intended safety property is that a problematic event does not indefinitely block unrelated valid queued work, while recovery progresses through a finite action ladder.

The research compares five policy variants (P0–P4) in a frozen deterministic host/reference model. The evidence supports **specific, bounded advantages** for the integrated P4 policy in selected case families. It does **not** support universal superiority, a claim that every mechanism is individually novel, patentability, or physical MCU performance. The interactive K.12 UI exposes the existing C execution path; it is not a second implementation of the recovery algorithm.

## 3. Research question and falsifiable hypothesis

### Research question

Can a compact deterministic software-only recovery policy for event-driven MCU firmware use peripheral-fault context and short recovery history to choose a bounded recovery action while quarantining the fault-associated event, preserving unrelated valid queued events, and maintaining fixed memory/resource bounds?

### Working hypothesis

The integrated policy P4 can improve handling in some combined fault/context/history situations compared with simpler policies, while retaining bounded operation and safe event isolation.

### What would weaken or falsify the hypothesis

- P4 does not outperform simpler variants in the case families that motivate integration.
- Any claimed benefit disappears when compared using matched cases and equal constraints.
- The result depends on a capacity limit or other confound that prevents attributing the effect to policy design.
- Event association, quarantine, boundedness, or recovery outcomes are not supported by the runtime trace.
- A matched comparison or original evidence record contradicts the reported result.

## 4. Core concepts

- **Zero-heap:** the protected recovery/reference path is designed around bounded static/fixed-capacity structures rather than dynamic heap allocation.
- **Context-aware:** recovery decisions consider the fault/event/peripheral context rather than applying only a fixed retry count.
- **Short recovery history:** prior recovery observations can influence the selected action.
- **Event quarantine:** the fault-associated event is isolated so it does not continue to execute as if valid; quarantine itself is shared behaviour across P0–P4 and must not be represented as a P4-exclusive invention.
- **Bounded recovery ladder:** recovery actions progress within explicit limits; an unrecoverable condition can terminate/escalate rather than loop indefinitely.
- **Authoritative C runtime:** `reference/src/ref_runtime.c` and its public contract determine actual policy transitions and trace records. UI labels or Python wrappers are not the recovery oracle.
- **Virtual peripheral:** an executable model of a supported resource (I2C0, SPI0, UART0), not a physical pin map or board driver.
- **Replay digest:** a deterministic fingerprint used to detect output changes in a fixed scenario/variant configuration. A digest validates reproducibility for that configuration; it does not by itself prove correctness or scientific novelty.

## 5. Architecture and execution flow

The intended live path is:

```text
Browser UI (HTML/CSS/JavaScript)
    ↓ HTTP request
Python bridge (demo/server.py; standard library)
    ↓ validated CLI arguments
C virtual-system adapter / virtual_demo_cli
    ↓ bounded virtual environment + scenario registry
Same protected C reference runtime
    ↓ policy decision + policy application
Authoritative runtime trace + outcome + digest
    ↓ JSON response
UI state, peripheral view, correlated traces, evidence panel
```

### Component responsibilities

| Component | Responsibility | Must not do |
|---|---|---|
| `demo/index.html` | Scenario/variant selection, deterministic stepping, virtual link controls, status cards, traces, evidence and limitations | Invent runtime decisions or silently substitute static data for failed live requests |
| `demo/server.py` | Validate requests, locate the C CLI, invoke it with bounded timeout, validate/return JSON | Reimplement policy logic or manufacture trace records |
| `reference/virtual/` | Bounded virtual-system state, supported resource availability, scenario/CLI adaptation and tests | Change the protected policy/runtime contract |
| `reference/src/ref_runtime.c` | Authoritative runtime state transitions, decisions/actions, trace/outcome | Be edited as part of K.12 UI work |
| `reference/include/ref_runtime.h` | Public reference-runtime interface and contract | Be edited as part of K.12 UI work |
| `demo/test_ui_contracts.py` | Contract checks for the bridge/UI-facing C CLI, scenarios, traces, digests, disconnection rejection | Assume obsolete digest values after the executable/model contract changes |
| Research reports | Record frozen experiments, analysis, limits and hardware plan | Recalculate or rewrite frozen K.10 results from an interactive demo run |

## 6. K.10 experimental design and results

The frozen K.10 campaign evaluated 16 case families (CF01–CF16), five policy variants (P0–P4), and five deterministic repetitions: **400 matched executions**. The recorded variance in the deterministic host/reference model was zero.

### Policy variants

The shorthand used in the results is:
- **P0:** Fixed Retry
- **P1:** Retry + Reset
- **P2:** Context Only
- **P3:** Context + History
- **P4:** Integrated (Context + History + Quarantine)

Use the frozen result report for exact per-case outputs and the definition of each experimental gate.

### Bounded findings supported by the report

- **CF04 + CF07:** P4 showed bounded benefit from fail-closed ambiguous-association handling and clean episode closure, preserving capacity for a later episode.
- **CF05:** P4 reached terminal recovery handling under cascading recovery faults; P2/P3 did not terminate within the tested bound.
- **Shared behaviour:** exact-event quarantine exists across P0–P4 and is not P4-exclusive.
- **No measured P4 advantage:** CF02, CF09, CF11, CF12, CF13 and CF15.
- **CF16 trade-off:** P2 succeeds in one attempt while P4 requires three attempts in the frozen report.
- **Capacity confounds:** QMAX=16 and EPMAX=1 affect interpretation of some outcomes. These limits must accompany any discussion of results.

### CF01 evidence discrepancy — do not conceal

The K.10 results table and narrative disagree about the P2 attempt count for CF01; K.10.4 records a different count again. The original raw `k10_runs.csv` and `k10_traces.csv` were absent from the inspected remote branch, so the discrepancy could not be reconciled from primary records in that inspection.

**Rule:** Do not use CF01 P2's attempt count as a comparative finding until the original run and trace records are available and reconciled. Do not rerun the frozen 400-execution matrix as a substitute for the missing historical records. Preserve the inconsistency in the audit trail.

### Claim boundary

The evidence supports a bounded, deterministic host/reference-model conclusion for the tested cases. It is not proof of universal superiority, formal safety, real-time performance on a physical MCU, legal novelty, non-obviousness, or patentability. Any publication/patent assessment requires further prior-art scrutiny and appropriate expert review.

## 7. K.12 virtual software demonstrator

The professor-facing UI lets a reviewer select a registered scenario and policy variant, step/replay the scenario, inspect runtime state and traces, and change modeled peripheral availability.

### What a live run demonstrates

- The UI request is passed through the Python bridge to the C CLI.
- The C CLI runs the registered scenario against the reference runtime.
- The resulting state, actions, outcome, trace and digest are returned for display.
- Virtual link availability is represented in the C adapter; a scenario that depends on a disconnected fixed virtual peripheral is rejected before event admission mutates runtime state.
- The UI should report that rejection clearly rather than make a disconnected run look like a successful recovery.
- The frozen research evidence panel is transcribed from frozen reports; it is not recalculated by the interactive run.

### Verified in the user's local environment

As reported by the user on 2026-10-13:
- The CMake build/test workflow was run locally.
- The digest assertions in `demo/test_ui_contracts.py` were updated to values observed from the current C executable.
- The user reported that all tests passed.
- The user reported that the UI is working locally.

This is user-confirmed local evidence, not an independent execution performed by the author of this document. Preserve the test output and the final commit SHA in the closure record.

### UI/product limitations to retain

- The virtual system is an executable software model, not physical wiring.
- The fixed scenario registry is not an arbitrary pin-level wiring editor.
- The browser view must not imply physical MCU execution.
- The C runtime alone is authoritative for recovery actions.
- Frozen evidence is not recalculated by the UI.
- Hardware target/pin/clock/timeout information is a proposal pending board-revision verification, not a validated board configuration.

## 8. Local build, test and run procedure (Windows PowerShell)

Run from the repository root. Use the build directory and configuration that exist in the local checkout.

```powershell
# Inspect repository state first
git status --short
git branch --show-current
git log -1 --oneline

# Build the virtual C executable
cmake --build reference/build --config Debug

# Run all registered CTest tests
ctest --test-dir reference/build -C Debug --output-on-failure

# Run the K.12 CLI contract test directly
python demo/test_ui_contracts.py

# Start the UI server in its own terminal
python demo/server.py
```

Open the local URL printed by the server. If the server's configured port is 8000, use `http://127.0.0.1:8000`. Do not assume a port if the server prints a different one. Keep the server terminal open.

### Minimum manual browser acceptance checklist

1. Page loads without console/server errors.
2. Each registered scenario can be selected and run.
3. Step Back/Step Next, Reset, Play and Run All update the current step and output coherently.
4. Changing policy variant changes the C-run output where the C runtime says it should.
5. Disconnecting a peripheral used by a selected scenario produces a visible fail-closed rejection; reconnecting permits a valid retry.
6. Runtime trace and wrapper/environment trace are populated from the response and remain correlated.
7. Live run failures are visible; no stale successful result is silently presented as the new result.
8. The UI distinguishes live runtime evidence from frozen K.10 research findings.
9. Responsive layout is usable at the target presentation size.
10. Stop the server with Ctrl+C after the demo.

## 9. Future hardware validation — planned, not performed

The proposed target is NUCLEO-U575ZI-Q / STM32U575ZI. Current planning notes include:
- I2C1 on PB8/PB9, planned 100 kHz baseline.
- SPI1 on PA5/PA6/PA7, planned 1 MHz, mode 0, 8-bit MSB-first; PD14 planned as chip-select.
- MSI 16 MHz SYSCLK without PLL.
- 1 MHz timer tick where feasible.
- Initial transfer timeout of 10 ms.
- UART/USART pins and alternate functions must be verified against the exact board revision and schematic.

These are planning parameters only. No MCU flashing, physical fault injection, oscilloscope/logic-analyzer measurement, MPU containment measurement, or physical board validation is established by K.12. Any hardware work needs a separately authorized, safety-reviewed checkpoint.

## 10. Protected boundaries and non-negotiable rules

Do not modify the following during UI/productization or project-orientation work unless a new, explicit research checkpoint authorizes it:
- `reference/src/ref_runtime.c`
- `reference/include/ref_runtime.h`
- `policy_decide()` and `runtime_apply_policy()`
- Gate-defining artifacts A–E
- Frozen K.10 raw/results evidence and the matched 400-execution matrix

Other rules:
- Do not rerun the frozen K.10 matrix to repair missing historical raw records.
- Do not infer that a local-only commit is present on GitHub unless its object/ref is verified.
- Keep the original local-only history preserved in the original local checkout.
- Keep `exp` unchanged during K.12 closure unless a later authorized integration plan explicitly says otherwise.
- Do not synchronize `main` until the final audit has been reviewed and explicitly approved.
- Never represent a software-model result as physical MCU validation.
- Never claim universal superiority, legal novelty, non-obviousness or patentability from the current data.

## 11. Branch and integration status

Verified remote refs at the time this guide was prepared:
- `main`: `0bff0b32e24dccb1b94c20b6e305cb918a49ec6f`
- `exp`: `ab766b47ce7bae2791028cea22b7915f8debc41c`
- `feature/k10-4-final-technical-conclusion-2026-10-13`: `a45057b65a5cc81df7120fc8df062e76c4fc75d1`

The feature branch contains K.12 remote source changes through the virtual-link rejection UI fix. Local digest-test/report edits were visible in the user's checkout but were not part of that remote HEAD when the refs were inspected.

### What “make main ready” means here

Main-readiness preparation includes:
1. Freeze the feature-branch worktree and capture test outputs.
2. Review the full feature diff against `exp`, classifying each file as required, historical/provenance, or unintended.
3. Verify protected-file blob SHAs and confirm no protected runtime/Gate/K.10 artifacts changed.
4. Reconcile or explicitly retain the CF01 discrepancy; do not silently rewrite evidence.
5. Ensure K.12 reports accurately distinguish user-run tests from independently verified CI.
6. Remove temporary backup files only after confirming they contain no unique edits.
7. Update the handoff/state/decision log and record the final feature SHA.
8. Compare `exp...feature` and `main...exp`; check for unexpected commits and file-level overwrite risk.
9. Prepare an explicit merge plan with expected base SHA and expected head SHA.
10. Only after ChatGPT's final audit approval, perform the separately authorized main synchronization and verify the resulting refs.

**This guide does not merge, push, or update `main` or `exp`.** Main remains intentionally unsynchronized until that audit/approval gate is passed.

## 12. Final closure gates

K.12 may be called closed only when all of the following are recorded:

- [ ] C build completes in the target local environment.
- [ ] Full CTest suite passes; test output/log is preserved.
- [ ] Direct `python demo/test_ui_contracts.py` passes.
- [ ] Manual browser acceptance checklist is completed.
- [ ] `git diff --check` is clean and line endings are intentional.
- [ ] All final changes are reviewed; no temporary backup is committed.
- [ ] Protected runtime and gate-defining files remain byte-identical to the frozen baseline.
- [ ] CF01 discrepancy is documented and not used as unsupported comparative evidence.
- [ ] K.12 report, project state, current handoff, decision log and Part-II plan agree on checkpoint status.
- [ ] Final commit is pushed to the authorized feature branch and remote HEAD is verified.
- [ ] `exp` and `main` refs are checked and their change status is recorded.
- [ ] ChatGPT explicitly approves closure before `main` is synchronized.

## 13. The next phase: complete project/repository understanding

After K.12 closure, do not jump straight to hardware or add new features. Conduct a structured orientation phase:

1. **Repository map:** classify each directory and important file as runtime, virtual system, UI, tests, experiments, frozen evidence, governance, or historical record.
2. **Call/data flow:** trace one scenario from browser input through Python and CLI into the C runtime and back to the UI, identifying exact structs/contracts at each boundary.
3. **Runtime walkthrough:** explain event admission, EventRef association, fault observation, episode tracking, policy decision/application, quarantine, bounded recovery, terminal outcomes and digest calculation from the source.
4. **Experiment walkthrough:** reconstruct the 16 case families, P0–P4 variants, gates, metrics, matched comparisons, confounds and each supported/unsupported conclusion from the frozen reports.
5. **Test map:** map each unit, integration, baseline and UI contract test to the invariant it protects and the failure it would catch.
6. **Evidence/provenance audit:** identify authoritative source files, derived summaries, historical records, missing raw evidence and unresolved discrepancies.
7. **Architecture and novelty critique:** separate known mechanisms, their integration, the bounded technical distinction, alternative explanations and the remaining falsification work.
8. **Professor narrative:** prepare a concise demonstration script that connects problem → hypothesis → implementation → live trace → evidence → limitations → hardware validation plan.
9. **Final blueprint:** document what exists, what is demonstrated, what is unproven, what remains, and what decision gates must be passed before further work.

The objective is complete understanding and defensible explanation—not merely repository familiarity.

---

## 14. Current conclusion

The user reports that the local build/test flow passed and the K.12 UI works. This marks a major software-demonstration milestone. It does not by itself complete repository closure: the final local diff, report edits, temporary backup, final feature-branch commit/push, and explicit audit decision still need to be reconciled. Once those are closed, the project can move to the planned repository-wide understanding and structuring phase, while physical validation remains a future separately authorized task.
