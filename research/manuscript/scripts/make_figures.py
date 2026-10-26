#!/usr/bin/env python3
"""Derive tables and grayscale figures from committed artifacts only.

Inputs : research/phase2_k10_p4_advantage_novelty_results.md  (frozen K.10 report, data columns only)
         research/manuscript/derived/source_derived_decisions.csv (from derive_source_decisions.py)
Outputs: research/manuscript/derived/k10_outcomes_from_report.csv
         research/manuscript/derived/k10_policy_summary.csv
         research/manuscript/figures/fig_host_outcomes.png / .pdf
         research/manuscript/figures/fig_source_decisions.png / .pdf
Run    : python3 research/manuscript/scripts/make_figures.py   (needs matplotlib)
The report's free-text 'Differentiation & Finding' column is NOT used (hard-coded text in the
generator script; it conflicts with the data columns for CF01 and CF08).
"""
import csv, re
from collections import Counter, OrderedDict
from pathlib import Path
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

ROOT = Path(__file__).resolve().parents[3]
REPORT = ROOT / "research/phase2_k10_p4_advantage_novelty_results.md"
D = ROOT / "research/manuscript/derived"; F = ROOT / "research/manuscript/figures"
POL = ["P0", "P1", "P2", "P3", "P4"]

def parse_report():
    rows = []
    for line in REPORT.read_text(encoding="utf-8").splitlines():
        if not line.startswith("| **CF"):
            continue
        cells = [c.strip() for c in line.strip().strip("|").split("|")]
        fam = cells[0].strip("*")
        for p, cell in zip(POL, cells[2:7]):
            m = re.match(r"([A-Z_]+)<br>att=(\d+), (CLS|ACT)", cell)
            if not m:
                raise SystemExit(f"cannot parse {fam} {p}: {cell}")
            rows.append(OrderedDict(family=fam, policy=p, outcome=m.group(1),
                                    attempts=int(m.group(2)), episode="closed" if m.group(3) == "CLS" else "active",
                                    attempts_disputed=int(fam.startswith("CF01") and p == "P2")))
    return rows

def main():
    rows = parse_report()
    fams = list(OrderedDict.fromkeys(r["family"] for r in rows))
    assert len(fams) == 16 and len(rows) == 80, (len(fams), len(rows))
    with open(D / "k10_outcomes_from_report.csv", "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0].keys())); w.writeheader(); w.writerows(rows)
    grid = {(r["family"], r["policy"]): r for r in rows}
    # per-policy summary
    with open(D / "k10_policy_summary.csv", "w", newline="") as f:
        w = csv.writer(f); w.writerow(["policy", "success", "terminal_escalate", "terminal_degrade", "stale_ref", "no_terminal", "episode_full", "episode_left_active"])
        for p in POL:
            c = Counter(grid[(fm, p)]["outcome"] for fm in fams)
            act = sum(grid[(fm, p)]["episode"] == "active" for fm in fams)
            w.writerow([p, c["SUCCESS"], c["TERMINAL_ESCALATE"], c["TERMINAL_DEGRADE"], c["STALE_REF"], c["NO_TERMINAL"], c["EPISODE_FULL"], act])
    ident = [fm for fm in fams if len({(grid[(fm, p)]["outcome"], grid[(fm, p)]["attempts"], grid[(fm, p)]["episode"]) for p in POL}) == 1]
    print("families identical across P0-P4 (outcome, attempts, episode):", len(ident), ident)
    # figure 1: outcome matrix (grayscale + labels)
    shade = {"SUCCESS": .95, "TERMINAL_DEGRADE": .78, "TERMINAL_ESCALATE": .6, "NO_TERMINAL": .38, "STALE_REF": .22, "EPISODE_FULL": .08}
    short = {"SUCCESS": "OK", "TERMINAL_DEGRADE": "DEG", "TERMINAL_ESCALATE": "ESC", "NO_TERMINAL": "NOT", "STALE_REF": "STL", "EPISODE_FULL": "EPF"}
    fig, ax = plt.subplots(figsize=(6.8, 6.6))
    for i, fm in enumerate(fams):
        for j, p in enumerate(POL):
            r = grid[(fm, p)]; s = shade[r["outcome"]]
            ax.add_patch(plt.Rectangle((j, 15 - i), 1, 1, facecolor=str(s), edgecolor="black", lw=.6,
                                       hatch="//" if r["episode"] == "active" else None))
            att = "n/d" if r["attempts_disputed"] else r["attempts"]
            ax.text(j + .5, 15 - i + .5, f"{short[r['outcome']]} {att}", ha="center", va="center",
                    fontsize=7.5, color="white" if s < .3 else "black")
    ax.set_xlim(0, 5); ax.set_ylim(0, 16)
    ax.set_xticks([x + .5 for x in range(5)]); ax.set_xticklabels(POL)
    ax.set_yticks([15 - i + .5 for i in range(16)]); ax.set_yticklabels([f.replace("_", " ", 1).split(" ")[0] + " " + f.split("_", 1)[1].replace("_", " ").title() for f in fams], fontsize=7)
    ax.xaxis.tick_top(); ax.tick_params(length=0)
    ax.set_title("Frozen host/reference campaign: outcome and attempt count\n(OK success, DEG terminal degrade, ESC terminal escalate, NOT no terminal,\nSTL stale ref, EPF episode full; hatch = episode left active;\nn/d = CF01/P2 attempt count disputed in frozen record, omitted)", fontsize=7.5, pad=32)
    fig.tight_layout(); fig.savefig(F / "fig_host_outcomes.png", dpi=300); fig.savefig(F / "fig_host_outcomes.pdf"); plt.close(fig)
    # figure 2: source-derived decision actions across the 80 firmware contexts
    names = {0: "none", 1: "retry", 2: "reinit/reset", 3: "degrade", 4: "escalate"}
    dec = list(csv.DictReader(open(D / "source_derived_decisions.csv")))
    assert len(dec) == 80 and all(x["start_outcome"] == "1" for x in dec)
    fig, ax = plt.subplots(figsize=(5.6, 3.2)); bottoms = [0] * 5
    hatches = {1: "", 2: "..", 3: "xx", 4: "//"}; greys = {1: "0.95", 2: "0.7", 3: "0.45", 4: "0.15"}
    for a in (1, 2, 3, 4):
        vals = [sum(1 for x in dec if int(x["policy"]) == p and int(x["action"]) == a) for p in range(5)]
        ax.bar(POL, vals, bottom=bottoms, color=greys[a], edgecolor="black", hatch=hatches[a], label=names[a], lw=.6)
        bottoms = [b + v for b, v in zip(bottoms, vals)]
    ax.set_ylabel("contexts (of 16)"); ax.set_ylim(0, 17); ax.legend(fontsize=7, ncol=4, loc="upper center", bbox_to_anchor=(.5, 1.18), frameon=False)
    ax.set_title("Source-derived first decision per policy over the 16 provisional firmware contexts (host computation)", fontsize=7, pad=24)
    fig.tight_layout(); fig.savefig(F / "fig_source_decisions.png", dpi=300); fig.savefig(F / "fig_source_decisions.pdf"); plt.close(fig)
    print("per-policy summary:"); print(open(D / "k10_policy_summary.csv").read())

if __name__ == "__main__":
    main()
