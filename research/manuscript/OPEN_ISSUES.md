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
| O-06 | Evidence gap | Raw K.10 outputs (`k10_runs.csv`, `k10_traces.csv`) are in none of the 15 remote branches. All host numbers come from the report table. | Locate the author's copy and commit it, or approve a regeneration into a new directory (not an overwrite). Not rerun here |
| O-07 | Documentation conflict | CF01 P2 attempts: table 3, narrative 1. | Frozen rule applied: count omitted |
| O-08 | Documentation conflict | CF08 P0: table shows success (1 attempt); narrative says P0 escalates both. Which outcome is correct for P0, and is "success" meaningful there? | Authors to check generator output |
| O-09 | Documentation conflict | Report §6 lists six identical families; the table shows seven (CF14 omitted). | Draft uses seven |
| O-10 | Evidence gap | `matrix_status`: user statement ("all 1 except the last") conflicts with a screenshot showing index 79 = 1. By source, `overall_code = 1` requires all 80 recorded. | Export the 80-element array from the debugger if the board session is still available; otherwise keep the statement as is |
| O-11 | Evidence gap | Hardware screenshots are not in the repository. | Commit the originals to a new evidence folder |
| O-12 | Evidence gap | No control read (no reinit after NACK). Without it, the P1/P4 pass does not show that reinit was needed. | Add control to next hardware run |
| O-21 | Unverified assumption | Three firmware variants are committed (`...matrix.c`, `...matrix_diagnostic.c`, `...matrix_formatted.c`). The flashed one is not recorded. The draft cites the diagnostic file because `CHAT_11` names it as the preserved candidate. | Authors to confirm; add a hash or commit id |
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

## D. Venue and metadata

| ID | Type | Issue | Action |
|---|---|---|---|
| O-18 | Metadata | Affiliations, emails, CRediT roles, funding, conflicts, ethics, AI-use disclosure, data DOI: placeholders. Author order and spelling could not be checked (no author record in the repository). | Authors |
| O-19 | Decision | No frozen title or abstract found. Proposed title and 180-word abstract need approval. | Authors |
| O-20 | Metadata | Venue formatting rests on a 2018 author-pack copy of *Journal of Systems Architecture* and third-party mirrors. Check abstract limit, keyword limit, highlights, reference style, template, and scope fit on elsevier.com. | Before submission |
