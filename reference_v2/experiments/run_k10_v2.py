#!/usr/bin/env python3
"""Run the additive P0-P6 campaign twice and validate deterministic outputs.

Requires a fresh output path. Never deletes or overwrites existing evidence.
"""
from __future__ import annotations
import argparse, csv, hashlib, subprocess
from pathlib import Path
ROOT = Path(__file__).resolve().parents[1]
def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(65536), b""): h.update(chunk)
    return h.hexdigest()
def read_rows(path: Path):
    with path.open(newline="", encoding="utf-8") as f: return list(csv.DictReader(f))
def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--exe", type=Path, default=ROOT / "build" / "k10_v2_experiment")
    ap.add_argument("--out", type=Path, required=True, help="New, non-existing output directory")
    args = ap.parse_args()
    exe = args.exe if args.exe.is_absolute() else (Path.cwd() / args.exe).resolve()
    if not exe.exists() and exe.with_suffix(".exe").exists(): exe = exe.with_suffix(".exe")
    if not exe.exists(): raise FileNotFoundError(f"Experiment binary not found: {exe}")
    out = args.out.resolve()
    replay = out.with_name(out.name + ".replay")
    if out.exists() or replay.exists(): raise FileExistsError(f"Refusing to overwrite evidence: {out} or {replay}")
    out.mkdir(parents=True); replay.mkdir(parents=True)
    def run(dest: Path):
        subprocess.run([str(exe), str(dest / "k10_v2_runs.csv"), str(dest / "k10_v2_traces.csv")], check=True)
    run(out); run(replay)
    runs, traces = out / "k10_v2_runs.csv", out / "k10_v2_traces.csv"
    deterministic = sha256(runs) == sha256(replay / runs.name) and sha256(traces) == sha256(replay / traces.name)
    rows = read_rows(runs)
    keys = {(int(r["family_id"]), int(r["variant_id"]), int(r["repetition"])) for r in rows}
    complete = len(rows) == 560 and len(keys) == 560 and {int(r["family_id"]) for r in rows} == set(range(1,17)) and {int(r["variant_id"]) for r in rows} == set(range(7)) and {int(r["repetition"]) for r in rows} == set(range(1,6))
    summaries = {}
    stable = True
    fields = ["family_name","terminal_outcome","episode_active","recovery_attempts","preserved_work","blocked_work","trace_records","reason_code","final_action","harness_ok"]
    for row in rows:
        key=(row["family_id"],row["variant_id"]); summary=tuple(row[k] for k in fields)
        if key in summaries and summaries[key] != summary: stable=False
        summaries[key]=summary
    manifest = out / "campaign_manifest.txt"
    manifest.write_text(
        f"run_count={len(rows)}\nexpected_run_count=560\n"
        f"matrix_complete={'PASS' if complete else 'FAIL'}\n"
        f"repetition_stability={'PASS' if stable else 'FAIL'}\n"
        f"deterministic_replay={'PASS' if deterministic else 'FAIL'}\n"
        f"runs_sha256={sha256(runs)}\ntraces_sha256={sha256(traces)}\n"
        "evidence_class=host_reference_model_only\nphysical_hardware_evidence=0\n"
        "backoff_units=scheduled logical units, not measured elapsed time\n", encoding="utf-8")
    print(f"runs={len(rows)}")
    print(f"matrix_complete={'PASS' if complete else 'FAIL'}")
    print(f"repetition_stability={'PASS' if stable else 'FAIL'}")
    print(f"deterministic_replay={'PASS' if deterministic else 'FAIL'}")
    return 0 if complete and stable and deterministic else 1
if __name__ == "__main__": raise SystemExit(main())
