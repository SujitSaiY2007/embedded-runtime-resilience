from pathlib import Path

ROOT = Path(__file__).resolve().parents[1] / "experiments"


def parse_rows(path):
    rows = []
    for raw in (ROOT / path).read_text().splitlines():
        if not raw or raw.startswith("#"):
            continue
        rows.append(raw.split("|"))
    return rows


def main():
    workloads = parse_rows("workloads.txt")
    schedules = {row[0]: row for row in parse_rows("fault_schedules.txt")}
    assert len(workloads) == 14, len(workloads)
    for row in workloads:
        assert len(row) == 11, row
        workload_id = row[0]
        schedule_id = row[10]
        assert schedule_id in schedules, (workload_id, schedule_id)
        assert row[4] == schedules[schedule_id][1], (workload_id, schedule_id)
    assert [row[0] for row in workloads] == [f"W{i:02d}" for i in range(1, 15)]


if __name__ == "__main__":
    main()
