#!/usr/bin/env python3
"""
Professor-Facing UI Server for Embedded Runtime Resilience (K.7)

Serves the front-end UI and proxies live execution requests directly to the
compiled C virtual-system CLI binary, preserving complete runtime authority.
Zero external dependencies (uses standard library http.server and subprocess).
"""

import http.server
import json
import os
import subprocess
import sys
import urllib.parse
from pathlib import Path

DEMO_DIR = Path(__file__).resolve().parent
REPO_ROOT = DEMO_DIR.parent

# Locate the compiled C virtual demo executable
BIN_CANDIDATES = [
    REPO_ROOT / "reference" / "build" / "virtual" / "Debug" / "virtual_demo_cli.exe",
    REPO_ROOT / "reference" / "build" / "virtual" / "Release" / "virtual_demo_cli.exe",
    REPO_ROOT / "reference" / "build" / "virtual" / "virtual_demo_cli.exe",
    REPO_ROOT / "reference" / "build" / "virtual" / "virtual_demo_cli",
]

def find_cli_binary():
    for candidate in BIN_CANDIDATES:
        if candidate.exists() and os.access(candidate, os.X_OK):
            return candidate
    return None

class DemoRequestHandler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(DEMO_DIR), **kwargs)

    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path
        query = urllib.parse.parse_qs(parsed.query)

        if path == "/api/status":
            self.handle_api_status()
        elif path == "/api/scenarios":
            self.handle_api_scenarios()
        elif path == "/api/step":
            self.handle_api_step(query)
        elif path == "/api/run":
            self.handle_api_run(query)
        else:
            # Fall back to serving static files from demo/
            super().do_GET()

    def send_json(self, data, status=200):
        body = json.dumps(data, indent=2).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(body)

    def send_json_raw(self, raw_bytes, status=200):
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(raw_bytes)))
        self.send_header("Access-Control-Allow-Origin", "*")
        self.end_headers()
        self.wfile.write(raw_bytes)

    def handle_api_status(self):
        cli = find_cli_binary()
        self.send_json({
            "status": "ok",
            "c_binary_found": cli is not None,
            "c_binary_path": str(cli) if cli else None,
            "architecture": "UI -> Python Bridge -> C Virtual System -> C Reference Runtime"
        })

    def handle_api_scenarios(self):
        cli = find_cli_binary()
        if not cli:
            self.send_json({"error": "C virtual system binary not found. Build reference/ first."}, 500)
            return
        # If pre-exported scenarios_data.json exists, return scenario metadata from it
        data_file = DEMO_DIR / "scenarios_data.json"
        if data_file.exists():
            with open(data_file, "r", encoding="utf-8") as f:
                data = json.load(f)
                summaries = []
                for k, v in data.get("scenarios", {}).items():
                    summaries.append({
                        "id": v["id"],
                        "name": v["name"],
                        "description": v["description"],
                        "step_count": v["step_count"]
                    })
                self.send_json({"scenarios": summaries})
                return

        self.send_json({"scenarios": [
            {"id": "S01", "name": "Independent Preservation Under Transient Fault", "step_count": 7},
            {"id": "S02", "name": "Ordered Dependency Blocking", "step_count": 8},
            {"id": "S05", "name": "Retry Success and Trace Correlation", "step_count": 3},
            {"id": "S06", "name": "Bounded Progression to Subsystem Restart", "step_count": 5},
            {"id": "S08", "name": "Ambiguous Association Isolation", "step_count": 3},
            {"id": "S14", "name": "Mixed Dependencies and Deterministic Replay", "step_count": 9}
        ]})

    def handle_api_step(self, query):
        cli = find_cli_binary()
        if not cli:
            self.send_json({"error": "C virtual system binary not found. Build reference/ first."}, 500)
            return

        scenario = query.get("scenario", ["S01"])[0]
        step = query.get("step", ["0"])[0]
        variant = query.get("variant", ["4"])[0]

        cmd = [str(cli), "--scenario", scenario, "--step", step, "--variant", variant]
        try:
            res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
            self.send_json_raw(res.stdout)
        except subprocess.CalledProcessError as e:
            self.send_json({
                "error": "C binary execution error",
                "stderr": e.stderr.decode("utf-8", errors="replace"),
                "cmd": cmd
            }, 500)

    def handle_api_run(self, query):
        cli = find_cli_binary()
        if not cli:
            self.send_json({"error": "C virtual system binary not found. Build reference/ first."}, 500)
            return

        scenario = query.get("scenario", ["S01"])[0]
        variant = query.get("variant", ["4"])[0]

        cmd = [str(cli), "--scenario", scenario, "--run", "--variant", variant]
        try:
            res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
            self.send_json_raw(res.stdout)
        except subprocess.CalledProcessError as e:
            self.send_json({
                "error": "C binary execution error",
                "stderr": e.stderr.decode("utf-8", errors="replace"),
                "cmd": cmd
            }, 500)

def main():
    port = 8000
    if len(sys.argv) > 1:
        try:
            port = int(sys.argv[1])
        except ValueError:
            pass

    cli = find_cli_binary()
    print("=" * 65)
    print("Embedded Runtime Resilience — Professor-Facing Demonstrator (K.7)")
    print("=" * 65)
    if cli:
        print(f"Authoritative C binary: {cli} (FOUND)")
    else:
        print("WARNING: C binary not found! Please run 'cmake --build reference/build' first.")
    print(f"Serving UI at: http://localhost:{port}/")
    print("Press Ctrl+C to stop.")
    print("=" * 65)

    server = http.server.HTTPServer(("", port), DemoRequestHandler)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nStopping server.")
        server.server_close()

if __name__ == "__main__":
    main()
