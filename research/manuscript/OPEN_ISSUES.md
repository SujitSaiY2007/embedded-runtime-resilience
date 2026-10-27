# Open Issues

Date: 2026-10-26. Classification follows the project convention: **Defect** (to fix in code), **Design limitation** (supervisor decision), **Missing requirement**, **Evidence gap**, **Unverified assumption**, **Metadata**. Nothing here has been changed in the protected runtime or frozen records.

## A. Findings about the reference runtime (protected; no edits made)

| ID | Type | Issue | Reproduction |
|---|---|---|---|
| O-01 | Defect | `queue_append` has no capacity check in a release build. Releasing a quarantined event into a full 16-entry queue aborts (assertions on) or writes `queue[16]` (NDEBUG). Reachable: 16 admitted events, one exact fault, one more admission, then release. | `bash research/manuscript/scripts/run_probes.sh` |
| O-02 | Design limitation | 8-bit generation counter with 0 reserved: `runtime_admit` returns `OUTCOME_STALE_REF` at admission 256 when the same slot is reused, with the queue empty. Intended lifetime of a runtime instance is not documented. | same script, probe 1 |
| O-03 | Defect candidate | `runtime_apply_policy` returns `OUTCOME_STALE_REF` for a retry or reinit on an invalid target without closing the episode, so EPMAX = 1 blocks all later faults (`OUTCOME_EPISODE_FULL`). This is the mechanism behind the CF04/CF07 "P4 advantage". A runtime fix may shrink that advantage. | Source reading; raw traces unavailable |
| O-04 | Design limitation | Trace buffer silently stops at 256 records. | Source reading (`trace_event`) |
| O-05 | Defect candidate (dead code) | P4 reason 18 is unreachable; the clamp using `precision_leq` never changes the target scope. | Enumeration, same script |
| O-24 | Unverified assumption | Association level and safety flags are supplied by the caller (assumption A1). The runtime does not infer them, so "evidence-bounded association" depends on caller correctness. | Source reading |

Decision needed: whether to open a separately approved research change for O-01 to O-03. Until then the manuscript reports them as limits.

## B. Evidence gaps

| ID | Type | Issue | Action |
|---|---|---|---|
| O-06 | Evidence gap | Raw K.10 outputs (`k10_runs.csv`, `k10_traces.csv`) are in none of the 15 remote branches; user searched locally and cannot find them. All original host numbers therefore come from the frozen report table. | Treat original CSVs as unavailable unless recovered later. If new data are required, run the corrected campaign into a fresh v2 output directory after source/test review; never recreate files under the original names. |
| O-07 | Documentation conflict | CF01 P2 attempts: table 3, narrative 1. | Frozen rule applied: count omitted |
| O-08 | Documentation conflict | CF08 P0: table shows success (1 attempt); narrative says P0 escalates both. Which outcome is correct for P0, and is "success" meaningful there? | Authors to check generator output |
| O-09 | Documentation conflict | Report §6 lists six identical families; the table shows seven (CF14 omitted). | Draft uses seven |
| O-10 | Evidence gap | `matrix_status`: user statement ("all 1 except the last") conflicts with a screenshot showing index 79 = 1. By source, `overall_code = 1` requires all 80 recorded. | Export the 80-element array from the debugger if the board session is still available; otherwise keep the statement as is |
| O-11 | Evidence gap | Screenshots have been supplied in this conversation, but original image files are not yet committed to the repository. | Preserve the screenshots as user-observed supporting evidence; commit original PNGs to a dedicated evidence folder if available. Do not repeat the completed run just to recreate screenshots. |
| O-12 | Resolved for scoped experiment | Five control trials recorded NACK at 0x77 and then successfully read BME280 ID 0x60 without calling full `iinit()` between probe and read. | Documented in `research/closure/PHASE2_HARDWARE_CLOSURE_2026-10-26.md`; interpretation is limited to this address-NACK scenario and does not isolate all transaction cleanup |
| O-21 | Unverified assumption | User supplied `hardware_exp.c` as the source used for the hardware results; SHA-256 `8d65294a7dbf8aca22cab9f2c56732bdb015bf7c3fab87cee6b555f7ae6a1ee8`. Three firmware variants are also committed. The exact flashed binary is not hash-linked to this source. | Cite the supplied source as identified by the user, retain its source hash, and state that binary identity is unverified. If the original `.elf`/`.bin` is available, hash it; no rebuild/reflash is needed solely for provenance. |
| O-22 | Metadata | Not captured: STM32CubeIDE, ARM GCC, HAL/CMSIS, ST-LINK firmware versions; MSVC version. | Record from the authors' machine |
| O-13 | Documentation conflict | Frozen K.10 text names STM32U575 as target; hardware is STM32L476RG. | State the change of target in the paper (done in 7.1 by naming the board only) |
| O-23 | Design limitation | Baselines P0–P3 are in-house ablations. | Add independently designed baselines (future work) |

## C. Literature

| ID | Type | Issue | Action |
|---|---|---|---|
| O-14 | Evidence gap | No systematic search was done. A thesis found while checking references (Kleeberger, TU München 2019, robust embedded software against peripheral failures, fault injection and HAL-level protection) is directly relevant and unreviewed. | Review it and its journal and conference papers before any gap statement |
| O-15 | Evidence gap | Patent records P-009 to P-017 are "partially verified" aggregator data. They are not cited. | Legal and technical review if the gap section discusses patents |
| O-16 | Metadata | References [4], [6]–[10] rely on repository audit metadata; [3] has no DOI; [4] authors/pages unchecked this session. | Re-check against publisher pages |
| O-17 | Requirement conflict | Supervisor target is at least 75% journal articles; draft has 6 of 10 (60%). Arithmetic: with 4 non-journal items fixed, 75% needs j/(j+4) ≥ 0.75, so j ≥ 12 journal articles, i.e. 6 more. Fixing the non-journal items is justified (they are the primary comparators), so the gap must be closed with relevant, verified journal papers, not filler. | See REFERENCE_AUDIT.md candidates |

## D. Candidate v2 and manuscript gate

| ID | Type | Issue | Action |
|---|---|---|---|
| O-25 | Candidate v2 validation | User-run CTest passed 1/1; two fresh 560-run campaigns passed completeness, repetition stability, deterministic replay, and zero harness failures, with matching run and trace SHA-256 hashes. | User-observed Windows/MSVC campaign evidence; record hashes in the phase-1 closure record when available. Keep candidate v2 separate from protected `reference/`; do not treat it as physical-hardware evidence. |

## D. Venue and metadata

| ID | Type | Issue | Action |
|---|---|---|---|
| O-18 | Metadata | Affiliations, emails, CRediT roles, funding, conflicts, ethics, AI-use disclosure, data DOI: placeholders. Author order and spelling could not be checked (no author record in the repository). | Authors |
| O-19 | Decision | No frozen title or abstract found. Proposed title and 180-word abstract need approval. | Authors |
| O-20 | Metadata | Venue formatting rests on a 2018 author-pack copy of *Journal of Systems Architecture* and third-party mirrors. Check abstract limit, keyword limit, highlights, reference style, template, and scope fit on elsevier.com. | Before submission |


## E. Phase 2 hardware closure (2026-10-26)

Hardware phase is closed for the planned scope; no further runs are planned. See [`research/closure/PHASE2_HARDWARE_CLOSURE_2026-10-26.md`](../closure/PHASE2_HARDWARE_CLOSURE_2026-10-26.md). The controlled NACK control succeeded 5/5; P1 and P4 passed the single policy comparison run; P0, P2 and P3 produced terminal/non-pass outcomes. Exact flashed binary identity, complete matrix export, exact enum-name mapping for runtime result 4, repeated independent policy runs, stuck-bus behavior, and target runtime resource measurements remain limitations/future work. These limitations do not block closing this phase, but must remain explicit in the manuscript.


## E. 27 October runtime correction and fresh K.10 audit

| ID | Type | Status | Evidence / action |
|---|---|---|---|
| O-01 | Runtime defect: full-queue release | Corrected on `audit/runtime-correction-2026-10-27`; user-run CTest 8/8 passed | `reference/src/ref_runtime.c`; regression test verifies queue-full release returns without destructive mutation. Retest in the repository's normal build before any future runtime edits. |
| O-02 | Generation exhaustion outcome | Corrected on `audit/runtime-correction-2026-10-27`; user-run CTest 8/8 passed | Exhausted slots are skipped; no reusable slots return `OUTCOME_SLOT_FULL` rather than `OUTCOME_STALE_REF`. |
| O-03 | Stale-target episode leak | Corrected on `audit/runtime-correction-2026-10-27`; user-run CTest 8/8 passed | Invalid recovery targets close the episode and clear associated quarantine accounting. The K.10 scenario results remain a separate policy-matrix evaluation and should not be conflated with the C regression tests. |
| O-26 | Fresh K.10 raw outputs not in repository | Evidence gap remains | User-run fresh campaign generated 400 rows, 80 family/variant groups with five matching repetitions, and `harness_ok=1` for all rows. Local hashes and CF04–CF07 results are recorded in `research/closure/FINAL_RUNTIME_AND_K10_AUDIT_2026-10-27.md`; upload raw CSV/trace/report artifacts to enable independent replay. |
| O-27 | Manuscript binary not regenerated | Evidence/artifact gap remains | Text release index and audit updated. Regenerate and review the DOCX/PDF before describing the binary manuscript as revised. |
