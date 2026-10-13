# ACTIVE NEXT-CHAT PROMPT — K.12

## Professor-Facing Software Demonstration Productization & Final Software Audit

**Repository:** `SujitSaiY2007/embedded-runtime-resilience`  
**Canonical reference branch:** `exp`  
**K.10.4 closure commit:** `09c17a413c7fb0b48c3c5da4642e24a402edd970`  
**K.11 deliverables:** `research/phase2_k11_final_software_synthesis_and_hardware_handoff.md`, `research/chat_records/chat_k11_record.md`  
**Checkpoint authority:** ChatGPT  
**Repository execution agent:** Antigravity only when explicitly invoked by ChatGPT

> **Gate:** This prompt is a prepared continuation brief, not permission to begin K.12 before ChatGPT explicitly approves and closes K.11. Do not sync `main`. No physical hardware execution or MCU flashing is authorized by this prompt.

## 1. Startup verification

1. Verify the current working branch and that it contains the approved K.10.4 closure and K.11 deliverables.
2. Verify `exp` remains at `ab766b47ce7bae2791028cea22b7915f8debc41c` unless ChatGPT explicitly authorizes a different baseline.
3. Verify `main` remains at `0bff0b32e24dccb1b94c20b6e305cb918a49ec6f`.
4. Preserve the original local-only commit `9c6596b2c32bf79bb652f3881e6d41695d43bb38`; do not reset, overwrite, merge away, or force-push it.
5. Verify the five protected Git blob SHAs remain:
   - `reference/src/ref_runtime.c`: `bd865e6c75fdb60e592a2fb3050ef1e066ef9a81`
   - `reference/include/ref_runtime.h`: `fbb7bb07bdb712fbadcde3d83bca19f82b5c8198`
   - `research/phase1_reference_implementation_design.md`: `b7fb120692756740bc969aa3412acaa89320c188`
   - `research/phase2_k9_methodology_lock.md`: `bd75f2c2c21c3964ec15b338eea99b386eff7aec`
   - `research/phase2_k9_2_p4_advantage_novelty_design.md`: `98d88ea2a0fc3a88d9d38f5b48aa274498d5e00d`
6. Read `PROJECT_MANUAL.md`, `PROJECT_STATE.md`, `CURRENT_HANDOFF.md`, `DECISION_LOG.md`, `research/PART_II_CHAT_PLAN.md`, the K.10.4 report/record, and both K.11 deliverables.

## 2. K.12 objective

Create a minimal, reliable, professor-facing software demonstration of the completed reference/virtual system. K.12 is productization and final software audit, not a new research campaign.

### Required work

1. Define the smallest clear demonstration flow from UI through virtual embedded system into the same existing C reference runtime, recovery decision, trace, and UI presentation.
2. Make the demo reproducible from a clean clone with explicit dependencies, commands, expected outputs, and troubleshooting.
3. Ensure displayed claims distinguish deterministic host/reference results from any physical hardware evidence (none is authorized here).
4. Provide a concise professor-facing walkthrough and explain CF04, CF05, CF07, shared quarantine, CF16 trade-off, and capacity caveats accurately.
5. Audit source, tests, build/run instructions, evidence, and documentation consistency.
6. Update the K.12 report, chat record, and continuity artifacts with exact commits and outcomes.

## 3. Frozen boundaries

- Do not modify Gates A–E, `reference/src/ref_runtime.c`, `reference/include/ref_runtime.h`, `policy_decide()`, or `runtime_apply_policy()`.
- Do not rerun the 400-execution K.10 matrix.
- Do not claim universal P4 superiority, legal novelty, non-obviousness, inventive step, or patentability.
- Do not perform physical MCU flashing, fault injection, or measurement.
- Do not merge the feature branch into `exp` or synchronize `main` without explicit ChatGPT authorization after final audit.
- Preserve all historical branches and the local-only commit.

## 4. Required deliverables

1. `research/phase2_k12_professor_facing_software_demo_and_final_audit.md`
2. `research/chat_records/chat_k12_record.md`
3. Updated `CURRENT_HANDOFF.md`, `PROJECT_STATE.md`, `DECISION_LOG.md`, `research/PART_II_CHAT_PLAN.md`, and next-step guidance only if ChatGPT authorizes a further checkpoint.

## 5. Completion criteria

K.12 may be recommended for closure only when:
- a clean-clone demonstration path is documented and actually verified within authorized software-only scope;
- the UI-to-runtime-to-trace flow is traceable to the existing C reference runtime;
- tests and outputs are reproducible and no protected runtime file changed;
- all limitations and counterexamples are visible in the professor narrative;
- the final audit reports exact branch/commit SHAs and verifies `exp`, `main`, and protected blob integrity;
- no unsupported hardware or legal claims remain.

**Start condition:** ChatGPT has explicitly approved and closed K.11. If that approval is absent, stop after startup verification and report the gate as closed.
