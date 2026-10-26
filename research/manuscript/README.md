# Manuscript Workspace

**Status (2026-10-26):** first full draft (v0.1) with evidence ledger, reference audit, figure plan and open issues. Not yet reviewed by the authors. Not submission-ready: see "Before submission".
**Repository:** [embedded-runtime-resilience](https://github.com/SujitSaiY2007/embedded-runtime-resilience)
**Task specification:** [CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md](CLAUDE_JOURNAL_MANUSCRIPT_PROMPT.md)

## Files

| File | Purpose |
|---|---|
| `DRAFT_MANUSCRIPT.md` | Full draft. Title and abstract are proposals (none was frozen). `<!--Lnn-->` tags link paragraphs to the ledger |
| `EVIDENCE_LEDGER.md` | Claim-to-evidence map with evidence classes and the list of claims deliberately not made |
| `REFERENCE_AUDIT.md` | Verification tier for each citation, links, journal-share arithmetic, candidates and leads |
| `FIGURE_TABLE_PLAN.md` | Figures and tables with exact source data and status |
| `OPEN_ISSUES.md` | Defects, design limitations, evidence gaps and metadata gaps, each with an action |
| `scripts/` | `derive_source_decisions.py`, `make_figures.py`, `run_probes.sh` and the two C probes |
| `derived/` | CSV files produced by the scripts from committed artifacts |
| `figures/` | Grayscale figures (PDF and PNG) produced by `make_figures.py` |

## Regenerate derived data and figures

```bash
python3 research/manuscript/scripts/derive_source_decisions.py   # needs gcc
python3 research/manuscript/scripts/make_figures.py              # needs matplotlib
bash research/manuscript/scripts/run_probes.sh                   # runtime-limit probes, needs gcc
```

All scripts read protected files and never write to them.

## Evidence streams kept separate in the draft

1. Frozen host/reference campaign: 16 families × 5 policies × 5 repetitions = 400 executions (Section 6). Only the report's data columns are used.
2. Source-level properties and host computations made for this draft (Sections 4.1, 4.4, 7.3).
3. One user-observed STM32L476RG/BME280 run with a controlled wrong-address NACK (Section 7).
4. Software demonstrator, described from repository documentation (Section 8).

## Venue recommendation (provisional)

**First choice to evaluate: *Journal of Systems Architecture* (Elsevier).** Its published scope covers embedded software design, real-time systems and operating systems, and it says case studies must contribute more than a design for one piece of software. That scope text was read from a third-party mirror, not from elsevier.com.
**Candor on readiness:** the evidence is a host campaign with in-house baselines and one hardware run. A reviewer at this venue is likely to ask for MCU measurements, repeated runs with a control, a stuck-bus test and independent baselines. Adding these first would raise the chance of acceptance; no outcome can be guaranteed.
**Alternatives, scope not checked:** *Microprocessors and Microsystems*, *Journal of Systems and Software*, *ACM Transactions on Embedded Computing Systems* (higher bar), *IEEE Embedded Systems Letters* (short format, needs a reduced paper).
**Format applied provisionally:** abstract ≤ 200 words (draft: 180), ≤ 5 keywords, numbered sections, highlights, declarations block with CRediT placeholders, numeric references. These come from a 2018 author-pack copy and must be re-checked (O-20).

## Validation actually performed (2026-10-26)

Environment: Ubuntu 24.04.4 LTS x86-64, gcc 13.3.0, Python 3.12.3, matplotlib 3.10.8.
- Cloned `main`, then fetched all 15 remote branches. Compared the protected runtime with the K.10 start commit `79f394a`: identical (`git diff` empty).
- Compiled the protected runtime in a temporary directory and ran the scripts and probes. Results are in the ledger (L05, L07, L10, L21, L22).
- Parsed the K.10 report table (80 cells) and checked Table 2 of the draft against `derived/k10_policy_summary.csv`.
- Searched publisher or institutional pages for [1], [2], [3], [5] (tier A) and for venue instructions (third-party mirrors only).
- **Not done:** repository CTest and UI tests, any hardware or CubeIDE operation, full-text claim checks, a systematic literature search, a rerun of the frozen campaign.

## Before submission (human checklist)

1. Approve or replace the title and abstract (O-19).
2. Supply affiliations, emails, CRediT roles, funding, conflicts, ethics, AI-use statement; confirm author names and order (O-18).
3. Commit the hardware screenshots and, if still possible, a full 80-element matrix export (O-10, O-11).
4. Locate or regenerate (in a new directory, with approval) the raw K.10 outputs (O-06).
5. Decide on the runtime findings O-01 to O-03: fix under a separate research change, or keep as stated limits.
6. Resolve CF01 and CF08 report conflicts (O-07, O-08) and confirm which firmware file was flashed (O-21).
7. Review the Kleeberger line of work and complete a systematic prior-art search before keeping the gap statement (O-14).
8. Re-check references [4], [6]–[10], add the DOI for [3], and add verified journal papers to approach the 75% target without padding (O-16, O-17).
9. Check the current guide for authors and template of the chosen venue, redraw Figures 1 and 3 as vectors, and remove all HTML comments (O-20).
