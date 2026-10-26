# Figure and Table Plan

Rules: every plot comes from committed data through a script; grayscale for print; each item is explained in the body text. Regenerate with `python3 research/manuscript/scripts/derive_source_decisions.py` then `python3 research/manuscript/scripts/make_figures.py` (needs gcc, matplotlib).

| Item | Content | Source data | Status |
|---|---|---|---|
| Fig. 1 | Runtime flow: queue, scheduler, episode, quarantine, policy, release | `reference/src/ref_runtime.c` (drawn from code) | Mermaid draft in manuscript; redraw as vector (TikZ, draw.io or Inkscape export to PDF) |
| Fig. 2 | Host outcome and attempt matrix, 16 families × 5 policies, hatch = episode left active, CF01/P2 count masked | `research/phase2_k10_p4_advantage_novelty_results.md` table, via `derived/k10_outcomes_from_report.csv` | Done: `figures/fig_host_outcomes.pdf/.png` |
| Fig. 3 | Hardware transaction sequence per policy | `physical()` in the diagnostic firmware | Mermaid draft; redraw as vector |
| Fig. 4 | Host-computed first decision per policy over 16 firmware contexts | `derived/source_derived_decisions.csv` | Done: `figures/fig_source_decisions.pdf/.png` |
| Table 1 | Policy decision rules | `policy_decide()` | In manuscript |
| Table 2 | Outcome counts per policy | `derived/k10_policy_summary.csv` | In manuscript; checked against the CSV |
| Table 3 | Observed hardware values | `CHAT_11_...md` | In manuscript; "not captured" cells kept |
| Table 4 | Source-derived decision versus observed status (hardware context) | `derived/source_derived_decisions.csv`, `CHAT_11_...md` | In manuscript |
| Evidence table (candidate) | Claim classes supported and not supported | `EVIDENCE_LEDGER.md` | Optional; move last section of the ledger into a journal table |

**Not planned until data exist:** timing, memory or energy charts; repeatability plots; any chart of the 80-element matrix beyond the three captured entries.

**Venue figure rules (to confirm):** vector PDF or high-resolution TIFF/EPS, readable at column width, captions that say measured versus modeled. Verify against the current guide.
