#!/usr/bin/env python3
"""
Deterministic Contract Verification for K.7 Professor-Facing UI

Verifies:
1. Scenario selection maps to valid scenarios (S01, S02, S05, S06, S08, S14).
2. Execution invokes the authoritative C virtual-system and reference runtime.
3. UI / wrapper does NOT manufacture authoritative EventRefs.
4. Runtime remains sole authority for recovery decisions (policy_decide).
5. Trace correlation between wrapper and runtime records is intact.
6. S08 preserves the no-fabricated-EventRef isolation guarantee.
7. Replay determinism (identical digest over multiple runs).
8. Pre-exported scenarios_data.json is complete and valid.
"""

import json
import subprocess
import sys
from pathlib import Path

DEMO_DIR = Path(__file__).resolve().parent
REPO_ROOT = DEMO_DIR.parent
CLI_BIN = REPO_ROOT / "reference" / "build" / "virtual" / "Debug" / "virtual_demo_cli.exe"

if not CLI_BIN.exists():
    CLI_BIN = REPO_ROOT / "reference" / "build" / "virtual" / "Release" / "virtual_demo_cli.exe"

def run_cli(args):
    cmd = [str(CLI_BIN)] + args
    res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, check=True)
    return json.loads(res.stdout)

def test_scenario_selection():
    print("[TEST 1] Scenario selection maps to valid scenarios...")
    expected = ["S01", "S02", "S05", "S06", "S08", "S14"]
    for sc in expected:
        data = run_cli(["--scenario", sc, "--step", "0"])
        assert data["scenario_id"] == sc, f"Mismatch: {data['scenario_id']} vs {sc}"
        assert data["step_count"] > 0, f"Scenario {sc} has 0 steps"
        assert data["runtime_authoritative"] is True
    print("  PASS: All 6 canonical scenarios mapped successfully.")

def test_authoritative_execution():
    print("[TEST 2] Execution invokes C virtual system and reference runtime...")
    s05 = run_cli(["--scenario", "S05", "--run"])
    assert s05["is_complete"] is True
    assert s05["outcome_str"] == "OUTCOME_SUCCESS"
    assert s05["digest"] == "0xBDC168BD"
    assert len(s05["runtime_trace"]) >= 4
    assert len(s05["wrapper_trace"]) >= 3
    print("  PASS: Authoritative C execution verified.")

def test_policy_authority():
    print("[TEST 3] Runtime remains sole authority for recovery decisions...")
    # S05 step 3 applies fault recovery
    s05_st3 = run_cli(["--scenario", "S05", "--step", "3"])
    ep = s05_st3["episode"]
    assert ep["in_use"] is False  # episode completed and released
    # Check wrapper trace action
    wrap_acts = [w["action"] for w in s05_st3["wrapper_trace"] if w["action"] != "ACT_NONE"]
    assert "ACT_RETRY" in wrap_acts, f"Expected ACT_RETRY in wrapper trace, got {wrap_acts}"

    # S06 progression to restart
    s06 = run_cli(["--scenario", "S06", "--run"])
    wrap_acts_s06 = [w["action"] for w in s06["wrapper_trace"] if w["action"] != "ACT_NONE"]
    assert "ACT_RETRY" in wrap_acts_s06
    assert "ACT_REINIT_OR_RESET" in wrap_acts_s06
    print("  PASS: Policy decisions originate from C runtime.")

def test_s08_no_fabricated_event_ref():
    print("[TEST 4] S08 ambiguous fault preserves no-fabricated-EventRef behavior...")
    s08 = run_cli(["--scenario", "S08", "--run"])
    assert s08["outcome_str"] == "OUTCOME_TERMINAL_ESCALATE"
    assert s08["digest"] == "0x5A52628A"

    # Only 1 runtime trace record (initial admit) should exist
    assert len(s08["runtime_trace"]) == 1, f"Expected 1 runtime record, got {len(s08['runtime_trace'])}"
    rt0 = s08["runtime_trace"][0]
    assert rt0["slot_id"] == 0
    assert rt0["generation"] == 1
    assert rt0["tx_id"] == 801

    # Episode target slot must be INVALID_SLOT (255)
    assert s08["episode"]["target_slot"] == 255, f"Fabricated slot: {s08['episode']['target_slot']}"
    assert s08["episode"]["target_gen"] == 0

    # Admitted slot 0 must not be falsely associated
    slot0 = [s for s in s08["active_slots"] if s["slot_id"] == 0][0]
    assert slot0["fault_associated"] is False, "Slot 0 was incorrectly faulted"
    print("  PASS: Zero fabricated EventRefs in ambiguous fault.")

def test_trace_correlation():
    print("[TEST 5] Wrapper and runtime trace correlation is intact...")
    scenarios = ["S01", "S02", "S05", "S06", "S08", "S14"]
    for sc in scenarios:
        data = run_cli(["--scenario", sc, "--run"])
        rt_seqs = {r["seq"] for r in data["runtime_trace"]}
        for w in data["wrapper_trace"]:
            assert w["runtime_authoritative"] is True
            first, last = w["rt_first"], w["rt_last"]
            if first > 0 and last > 0:
                assert first <= last, f"{sc}: first {first} > last {last}"
                for s in range(first, last + 1):
                    assert s in rt_seqs, f"{sc}: sequence {s} not found in runtime trace"
    print("  PASS: Trace sequence correlation verified across all scenarios.")

def test_replay_determinism():
    print("[TEST 6] Replay determinism (multiple identical runs)...")
    expected_digests = {
        "S01": "0xB72131CB",
        "S02": "0xE8691374",
        "S05": "0xBDC168BD",
        "S06": "0xA123BB47",
        "S08": "0x5A52628A",
        "S14": "0x9185616C"
    }
    for sc, exp_d in expected_digests.items():
        run1 = run_cli(["--scenario", sc, "--run"])
        run2 = run_cli(["--scenario", sc, "--run"])
        assert run1["digest"] == exp_d, f"{sc} run1 digest {run1['digest']} != {exp_d}"
        assert run2["digest"] == exp_d, f"{sc} run2 digest {run2['digest']} != {exp_d}"
        assert run1["digest"] == run2["digest"], f"{sc} non-deterministic digest"
    print("  PASS: All replay digests bit-for-bit identical.")

def test_scenarios_data_json():
    print("[TEST 7] Verifying pre-exported scenarios_data.json...")
    json_path = DEMO_DIR / "scenarios_data.json"
    assert json_path.exists(), "scenarios_data.json missing"
    with open(json_path, "r", encoding="utf-8") as f:
        data = json.load(f)

    assert "scenarios" in data
    expected = ["S01", "S02", "S05", "S06", "S08", "S14"]
    for sc in expected:
        assert sc in data["scenarios"], f"{sc} missing from scenarios_data.json"
        entry = data["scenarios"][sc]
        assert "timeline" in entry
        assert len(entry["timeline"]) == entry["step_count"] + 1
        final_state = entry["timeline"][-1]
        assert final_state["is_complete"] is True
    print("  PASS: Pre-exported offline JSON dataset valid and complete.")

def main():
    print("=" * 65)
    print("K.7 Professor-Facing UI Contract Verification")
    print(f"Testing against C binary: {CLI_BIN}")
    print("=" * 65)
    test_scenario_selection()
    test_authoritative_execution()
    test_policy_authority()
    test_s08_no_fabricated_event_ref()
    test_trace_correlation()
    test_replay_determinism()
    test_scenarios_data_json()
    print("=" * 65)
    print("ALL K.7 UI CONTRACT TESTS PASSED SUCCESSFULLY.")
    print("=" * 65)

if __name__ == "__main__":
    main()
