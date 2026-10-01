#!/usr/bin/env python3
"""Run the smallest reproducible matched P0-P4 host corpus."""

from __future__ import annotations
import argparse, csv, hashlib, shutil, subprocess
from pathlib import Path

VARIANTS = 5

def sha256(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(65536), b""):
            h.update(chunk)
    return h.hexdigest()

def run_once(exe: Path, workloads: Path, schedules: Path, out: Path) -> None:
    out.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        [str(exe), str(workloads), str(schedules),
         str(out / "runs.csv"), str(out / "trace.csv")],
        check=True,
    )

def read_runs(path: Path):
    with path.open(newline="") as f:
        return list(csv.DictReader(f))

def main() -> int:
    ap = argparse.ArgumentParser()
    ap.add_argument("--exe", type=Path, default=Path("build/host_experiment"))
    ap.add_argument("--out", type=Path, default=Path("experiments/out"))
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()

    root = Path(__file__).resolve().parent
    workloads = root / "workloads.csv"
    schedules = root / "fault_schedules.csv"
    exe = args.exe if args.exe.is_absolute() else (root.parent / args.exe)
    if not exe.exists():
        for candidate in (
            exe.with_suffix(".exe"),
            exe.parent / "Debug" / f"{exe.name}.exe",
            exe.parent / "Release" / f"{exe.name}.exe",
            exe.parent / "Debug" / exe.name,
            exe.parent / "Release" / exe.name,
        ):
            if candidate.exists():
                exe = candidate
                break

    out = args.out if args.out.is_absolute() else (root.parent / args.out)
    replay = out.with_name(out.name + ".replay")
    for p in (out, replay):
        if p.exists():
            shutil.rmtree(p, ignore_errors=True)
        p.mkdir(parents=True, exist_ok=True)

    for dest in (out / "raw", replay / "raw"):
        dest.mkdir(parents=True, exist_ok=True)
        shutil.copy2(workloads, dest / "workloads.csv")
        shutil.copy2(schedules, dest / "fault_schedules.csv")

    run_once(exe, workloads, schedules, out)
    run_once(exe, workloads, schedules, replay)

    deterministic = all(
        sha256(out / name) == sha256(replay / name)
        for name in ("runs.csv", "trace.csv")
    )
    input_same = (
        sha256(workloads) == sha256(out / "raw" / "workloads.csv")
        and sha256(schedules) == sha256(out / "raw" / "fault_schedules.csv")
    )

    rows = read_runs(out / "runs.csv")
    by_workload = {}
    for row in rows:
        by_workload.setdefault(int(row["workload_id"]), []).append(row)
    matched = all(len(v) == VARIANTS and
                  {int(x["variant_id"]) for x in v} == set(range(VARIANTS))
                  for v in by_workload.values())
    capacity_flagged = all(
        (row["workload_id"] in ("9", "10")) ==
        (row["capacity_confounded"] == "1")
        for row in rows
    )
    ablation_flagged = all(
        (row["variant_id"] == "4") == (row["ablation_contract_valid"] == "1")
        for row in rows
    )

    manifest = out / "corpus_manifest.csv"
    with manifest.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["field", "value"])
        w.writerow(["workload_sha256", sha256(workloads)])
        w.writerow(["fault_schedule_sha256", sha256(schedules)])
        w.writerow(["raw_input_preserved", "PASS" if input_same else "FAIL"])
        w.writerow(["matched_input_equivalence", "PASS" if matched else "FAIL"])
        w.writerow(["capacity_confounds_explicit", "PASS" if capacity_flagged else "FAIL"])
        w.writerow(["ablation_contract_flagging", "PASS" if ablation_flagged else "FAIL"])
        w.writerow(["deterministic_replay", "PASS" if deterministic else "FAIL"])
        w.writerow(["run_count", len(rows)])
        w.writerow(["host_evidence_only", "1"])
        w.writerow(["mcu_evidence", "0"])
        w.writerow(["physical_fault_evidence", "0"])

    if args.check or True:
        ok = deterministic and input_same and matched and capacity_flagged and ablation_flagged
        print(f"deterministic_replay={'PASS' if deterministic else 'FAIL'}")
        print(f"matched_input_equivalence={'PASS' if matched else 'FAIL'}")
        print(f"raw_input_preserved={'PASS' if input_same else 'FAIL'}")
        print(f"capacity_confounds_explicit={'PASS' if capacity_flagged else 'FAIL'}")
        print(f"ablation_contract_flagging={'PASS' if ablation_flagged else 'FAIL'}")
        print(f"runs={len(rows)}")
        return 0 if ok else 1
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
