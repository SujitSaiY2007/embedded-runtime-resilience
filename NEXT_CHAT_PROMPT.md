# ACTIVE NEXT-CHAT PROMPT — K.12

## Integrated Virtual Embedded-System Demonstration, Research Results & Final Software Audit

**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Canonical reference branch:** `exp`  
**K.10.4 closure commit:** `09c17a413c7fb0b48c3c5da4642e24a402edd970`  
**K.11 deliverables:** `research/phase2_k11_final_software_synthesis_and_hardware_handoff.md`, `research/chat_records/chat_k11_record.md`  
**Checkpoint authority:** ChatGPT  
**Repository execution agent:** Antigravity only when explicitly invoked and authorized by ChatGPT

> **Gate status (2026-10-13): K.11 has been substantively reviewed and formally APPROVED AND CLOSED BY CHATGPT. K.12 is AUTHORIZED within the software-only scope below. Do not sync `main`. No physical hardware execution or MCU flashing is authorized.**

## 1. Mission

K.12 must deliver an integrated, interactive, professor-facing **software twin / virtual embedded-system demonstrator** that makes the research understandable and allows a professor to configure a supported virtual setup, execute a scenario, observe the actual recovery behaviour, and inspect evidence-based research conclusions.

This is not merely a visual redesign. The required execution path is:

**Professor-facing UI → virtual hardware/system configuration → bounded C virtual system → the same existing C reference runtime → recovery decision → trace/outcome → UI → research evidence and conclusions.**

The interface should make it clear what the research achieved, where P4 shows bounded advantages, where it does not, which limitations remain, and what still requires physical hardware validation.

## 2. Mandatory startup and continuity verification

Before changing files:

1. Verify the current working branch, working-tree state, HEAD, relevant remote references, and the actual K.11 closure artifacts.
2. Verify the K.10.4 closure ancestor `09c17a413c7fb0b48c3c5da4642e24a402edd970` and K.11 deliverables.
3. Verify `exp` remains at `ab766b47ce7bae2791028cea22b7915f8debc41c` unless ChatGPT explicitly authorizes a different baseline.
4. Verify `main` remains at `0bff0b32e24dccb1b94c20b6e305cb918a49ec6f`.
5. Preserve the original local-only commit `9c6596b2c32bf79bb652f3881e6d41695d43bb38` in its original local checkout. Do not reset, overwrite, clean, merge away, or force-push it.
6. Read `PROJECT_MANUAL.md`, `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, `DECISION_LOG.md`, `research/PART_II_CHAT_PLAN.md`, the K.10.4 report/record, both K.11 deliverables, and relevant K.6/K.7 virtual-system/UI code and tests.
7. Inspect and understand `demo/index.html`, `demo/server.py`, the `virtual_demo_cli` build/entry point, scenario definitions, JSON response schemas, and how the CLI invokes the existing C runtime. Do not assume documentation accurately describes current behaviour; verify it.
8. Capture the pre-change status and protected-file hashes before implementation.

If the repository contradicts the handoff, stop before destructive or irreversible operations, preserve evidence, and report the discrepancy.

## 3. UI technology decision

**Preferred stack: reuse the existing implementation.**

- Frontend: existing HTML, CSS, and vanilla JavaScript in `demo/index.html`.
- Backend/bridge: existing Python standard-library HTTP server in `demo/server.py`, unless audit identifies a concrete defect requiring a narrowly justified change.
- Execution: existing `virtual_demo_cli` and bounded C virtual-system implementation, connected to the existing C reference runtime.
- Data: actual runtime responses and trace fields. Do not fabricate runtime results in JavaScript or duplicate the recovery algorithm in Python.

Do not migrate to React, Streamlit, or another framework by default. Avoid new external dependencies unless a verified need justifies them. Prefer minimal, maintainable, reproducible changes to the current stack.

## 4. Required professor-facing experience

Inspect the current UI first, then implement the minimum complete and robust version of the following capabilities.

### A. Virtual hardware workbench

Present a clear visual model of the intended embedded setup, including the MCU/system, supported peripherals, interface ports, connection state, event flow, and relevant resource/boundedness indicators.

- Make supported virtual connections discoverable and interactive. For example, users should be able to select a peripheral and connect its modeled interface to a compatible virtual MCU port using a clear connect/disconnect interaction.
- A connection must update the actual virtual configuration and influence execution wherever the underlying model supports that connection. Do not draw decorative wires that have no effect.
- Validate incompatible or duplicate connections and explain invalid states.
- Display the I2C-primary, SPI-secondary and UART/USART diagnostic/control mapping as a proposed hardware architecture where applicable.
- Distinguish the **virtual software model** from physical pins, wiring, and real electrical behaviour.
- Do not claim arbitrary dynamic wiring is supported if the current C model only exposes fixed scenarios. Audit first; extend only the virtual/demo layer and tests as needed, preserving the established runtime contracts.

### B. Scenario and fault controls

Allow the professor to choose a supported scenario, policy variant where supported, and fault/stimulus options that are genuinely implemented. Provide a clear Run/Step/Reset flow where the CLI supports it. Clearly indicate unavailable options rather than presenting fake controls.

### C. Execution and recovery view

Show results returned by the actual C execution path, including applicable:

- current scenario and step;
- event/peripheral/fault context;
- recovery decision and action progression;
- quarantine, eligibility, preservation, release, degradation, or escalation states when present in the actual trace;
- bounded termination and error outcomes;
- event/episode identifiers and relevant trace fields;
- execution errors and reproducibility information.

Do not label host execution time or host structure sizes as MCU measurements. Do not claim live physical telemetry.

### D. Evidence and research-conclusion dashboard

Present the frozen K.10 evidence accurately and separately from the current interactive demo run. Make the source and scope of each displayed result clear.

Required narrative:

- bounded P4 advantages in CF04 and CF07 (ambiguous association/episode closure preserving later episode capacity) and CF05 (bounded termination under cascading recovery faults);
- exact-event quarantine is shared across P0–P4 and is not a P4-exclusive contribution;
- CF16 trade-off: P2 succeeds in one attempt while P4 requires three attempts;
- no measured P4 advantage in CF02, CF09, CF11, CF12, CF13, or CF15;
- capacity confounds `QMAX=16` and `EPMAX=1`;
- conclusions are bounded to the tested host/reference conditions and examined case set;
- no claim of universal superiority, legal novelty, non-obviousness, inventive step, or patentability.

Do not silently recompute or edit frozen K.10 findings to populate the dashboard. Any comparative values shown must be traceable to authoritative frozen evidence.

### E. Hardware-mapping and future-validation view

Show how the virtual model maps to the proposed STM32U575ZI / NUCLEO-U575ZI-Q setup and the K.11 future-validation specification. Mark all hardware checks, physical measurements, and board validation as **pending/not performed**. The diagram is a software representation, not proof of hardware operation.

## 5. Frozen boundaries

- Do not modify Gates A–E or the protected runtime:
  - `reference/src/ref_runtime.c`
  - `reference/include/ref_runtime.h`
  - `policy_decide()`
  - `runtime_apply_policy()`
- Preserve these known protected Git blob SHAs; verify before and after:
  - `reference/src/ref_runtime.c`: `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81`
  - `reference/include/ref_runtime.h`: `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`
  - `research/phase1_reference_implementation_design.md`: `b7fb120692756740bc969aa3412acaa89320c188`
  - `research/phase2_k9_methodology_lock.md`: `bd75f2c2c21c3964ec15b338eea99b386eff7aec`
  - `research/phase2_k9_2_p4_advantage_novelty_design.md`: `98d88ea2a0fc3a88d9d38f5b48aa274498d5e00d`
- Do not rerun the frozen 400-execution K.10 matrix.
- Do not silently modify frozen K.10 results.
- Do not fabricate tests, traces, metrics, hardware results, or commit SHAs.
- Do not claim universal P4 superiority, legal novelty, non-obviousness, inventive step, or patentability.
- Do not flash firmware, inject physical faults, measure hardware, or claim physical MCU validation.
- Do not merge the feature branch into `exp` or synchronize `main` without explicit ChatGPT authorization after the final audit.
- Preserve all historical branches and the local-only commit.
- Commit/push K.12 work only to the verified authorized working branch and only after reviewing the exact diff.

## 6. CF01 discrepancy — mandatory evidence audit

K.11 identified an unresolved conflict:

- `research/phase2_k10_p4_advantage_novelty_results.md` has a CF01 P2 table entry `SUCCESS, att=3`, while its explanatory text says P2 succeeds in one attempt.
- `research/phase2_k10_4_final_technical_distinction_and_research_conclusion.md` records CF01 P2 as `SUCCESS (att=1)`.

Search for original raw records and establish whether authoritative evidence resolves this. Do not rerun the K.10 matrix or guess. Do not silently edit frozen results. If raw evidence is unavailable, preserve the discrepancy as unresolved and exclude the disputed CF01 attempt count from comparative claims. Keep the distinct CF16 P2-one-attempt versus P4-three-attempt result separate.

## 7. Verification requirements

Create a verification matrix with exact commands/procedures, expected and observed outcomes, PASS/FAIL/BLOCKED/NOT RUN, and evidence paths.

At minimum, verify:

1. Build and launch from documented clean-clone instructions.
2. Existing CTest/unit test suite.
3. CLI scenario and JSON/trace response behaviour.
4. UI-to-Python-bridge-to-CLI-to-C-runtime integration.
5. Run, step, reset, and error handling where supported.
6. Virtual connection/configuration validation and its effect on execution, if implemented.
7. Representative successful and failing scenarios.
8. Trace/result consistency and research-dashboard provenance.
9. Responsive and accessible-enough presentation for a professor demo.
10. Documentation reproducibility and troubleshooting.
11. Protected-file integrity and Git branch/commit integrity.

Distinguish tests that existed before K.12 from checks executed during K.12. Do not claim a test passed unless its output was observed. If the environment prevents a check, record BLOCKED and provide the exact reproducible command for the user's environment.

## 8. Required deliverables

Create or verify:

1. `research/phase2_k12_professor_facing_software_demo_and_final_audit.md`
2. `research/chat_records/chat_k12_record.md`
3. A concise professor demonstration guide with prerequisites, build/setup, launch, scenario walkthrough, expected observable outputs, and troubleshooting.
4. A documented architecture/data-flow and virtual-to-hardware mapping.
5. A verification matrix with evidence paths and explicit limitations.
6. Updated `CURRENT_HANDOFF.md`, `PROJECT_STATE.md`, `DECISION_LOG.md`, and `research/PART_II_CHAT_PLAN.md`.
7. Update `NEXT_CHAT_PROMPT.md` only if a justified follow-up checkpoint is required; K.12 is intended to be the final software checkpoint.

Use the established project conventions and avoid creating conflicting sources of truth.

## 9. Final audit and closure gate

Before recommending closure:

- Review the complete diff for unrelated changes.
- Verify protected files and Gate-defining artifacts remain unchanged.
- Confirm the 400-execution K.10 matrix was not rerun or silently altered.
- Run the applicable final test suite and report exact outcomes.
- Verify that UI outputs are produced by the actual C execution path and that the demo can be reproduced.
- Verify the research dashboard reports bounded advantages, counterexamples, shared mechanisms, capacity confounds, and limitations.
- Verify CF01 is either evidence-resolved with an audit trail or explicitly unresolved.
- Ensure all updated documents agree on project status.
- Record exact working branch HEAD and commit SHAs.
- Verify `exp` and `main` remain unchanged.
- Do not claim preservation of a local-only commit based solely on remote inspection.

If a required check is blocked or fails, report K.12 as INCOMPLETE/BLOCKED rather than declaring success.

## 10. Required final report

Return:

1. K.12 verdict: APPROVED AND CLOSED or explicitly INCOMPLETE/BLOCKED.
2. What the professor can actually configure, execute, observe, and conclude through the UI.
3. Exact verified end-to-end path and commands.
4. Verification matrix and evidence paths.
5. CF01 discrepancy disposition.
6. Deliverable paths and purposes.
7. Branch/commit/push status and confirmation that `exp` and `main` were preserved.
8. Protected-file before/after integrity.
9. Research conclusions and explicit limitations.
10. Hardware-validation handoff and remaining work.

**Start condition:** K.11 was approved and closed by ChatGPT on 2026-10-13. K.12 is authorized. Begin with repository verification, then implement and test the smallest complete integrated demonstration. The outcome must let a professor see what the research achieved through a real software execution path—not merely a static UI—and must never misrepresent software simulation as physical hardware validation.
