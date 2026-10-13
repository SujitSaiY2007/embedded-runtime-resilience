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
ALLOWED_SCENARIOS = {"S01", "S02", "S05", "S06", "S08", "S14"}
ALLOWED_PERIPHERALS = {"I2C0", "SPI0", "UART0"}

# CMake binary candidates across Windows and Unix builds.
BIN_CANDIDATES = [
    REPO_ROOT / "reference" / "build" / "virtual" / "Debug" / "virtual_demo_cli.exe",
    REPO_ROOT / "reference" / "build" / "virtual" / "Release" / "virtual_demo_cli.exe",
    REPO_ROOT / "reference" / "build" / "virtual" / "virtual_demo_cli.exe",
    REPO_ROOT / "reference" / "build" / "virtual" / "Debug" / "virtual_demo_cli",
    REPO_ROOT / "reference" / "build" / "virtual" / "Release" / "virtual_demo_cli",
    REPO_ROOT / "reference" / "build" / "virtual" / "virtual_demo_cli",
]


def find_cli_binary():
    for candidate in BIN_CANDIDATES:
        if candidate.is_file() and (os.name == "nt" or os.access(candidate, os.X_OK)):
            return candidate
    return None


def parse_run_options(query):
    scenario = query.get("scenario", ["S01"])[0]
    variant_text = query.get("variant", ["4"])[0]
    if scenario not in ALLOWED_SCENARIOS:
        raise ValueError(f"Unsupported scenario: {scenario}")
    try:
        variant = int(variant_text)
    except (TypeError, ValueError) as exc:
        raise ValueError("variant must be an integer from 0 to 4") from exc
    if variant not in range(5):
        raise ValueError("variant must be an integer from 0 to 4")
    disconnected = []
    for name in query.get("disconnect", []):
        normalized = name.upper()
        if normalized not in ALLOWED_PERIPHERALS:
            raise ValueError(f"Unsupported virtual peripheral: {name}")
        if normalized not in disconnected:
            disconnected.append(normalized)
    return scenario, variant, disconnected


class DemoRequestHandler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(DEMO_DIR), **kwargs)

    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path
        query = urllib.parse.parse_qs(parsed.query, keep_blank_values=True)

        if path == "/api/status":
            self.handle_api_status()
        elif path == "/api/scenarios":
            self.handle_api_scenarios()
        elif path in {"/api/step", "/api/run"}:
            self.handle_api_execution(path, query)
        else:
            # Serve static demo assets only; API calls never fall back to static results.
            super().do_GET()

    def send_json(self, data, status=200):
        body = json.dumps(data, indent=2).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(body)

    def handle_api_status(self):
        cli = find_cli_binary()
        self.send_json({
            "status": "ok" if cli else "degraded",
            "c_binary_found": cli is not None,
            "c_binary_path": str(cli) if cli else None,
            "architecture": "UI -> Python Bridge -> C Virtual System -> C Reference Runtime",
            "connection_configuration_supported": cli is not None,
            "research_evidence_source": "frozen K.10 reports; not recomputed by UI"
        })

    def handle_api_scenarios(self):
        # Registry is intentionally limited to scenarios compiled into the C CLI.
        self.send_json({"scenarios": [
            {"id": "S01", "name": "Independent Preservation Under Transient Fault", "step_count": 7},
            {"id": "S02", "name": "Ordered Dependency Blocking", "step_count": 8},
            {"id": "S05", "name": "Retry Success and Trace Correlation", "step_count": 3},
            {"id": "S06", "name": "Bounded Progression to Subsystem Restart", "step_count": 5},
            {"id": "S08", "name": "Ambiguous Association Isolation", "step_count": 3},
            {"id": "S14", "name": "Mixed Dependencies and Deterministic Replay", "step_count": 9}
        ]})

    def handle_api_execution(self, path, query):
        cli = find_cli_binary()
        if not cli:
            self.send_json({
                "error": "C virtual-system executable not found. Build reference/ first.",
                "c_binary_found": False,
                "hint": "Run: cmake -S reference -B reference/build && cmake --build reference/build"
            }, 503)
            return
        try:
            scenario, variant, disconnected = parse_run_options(query)
            if path == "/api/step":
                step_text = query.get("step", ["0"])[0]
                try:
                    step = int(step_text)
                except (TypeError, ValueError) as exc:
                    raise ValueError("step must be an integer") from exc
                if step < 0:
                    raise ValueError("step must be zero or greater")
                cmd = [str(cli), "--scenario", scenario, "--step", str(step), "--variant", str(variant)]
            else:
                cmd = [str(cli), "--scenario", scenario, "--run", "--variant", str(variant)]
            for name in disconnected:
                cmd.extend(["--disconnect", name])
            res = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                 check=False, timeout=10)
            if res.returncode != 0:
                self.send_json({
                    "error": "C virtual-system execution failed",
                    "stderr": res.stderr.decode("utf-8", errors="replace"),
                    "return_code": res.returncode
                }, 500)
                return
            try:
                payload = json.loads(res.stdout.decode("utf-8"))
            except (UnicodeDecodeError, json.JSONDecodeError):
                self.send_json({"error": "C executable returned malformed JSON"}, 502)
                return
            # UI callers can reliably distinguish authoritative output from offline export.
            if payload.get("runtime_authoritative") is not True:
                self.send_json({"error": "C output did not declare runtime authority"}, 502)
                return
            self.send_json(payload)
        except ValueError as exc:
            self.send_json({"error": str(exc)}, 400)
        except subprocess.TimeoutExpired:
            self.send_json({"error": "C execution timed out after 10 seconds"}, 504)
        except OSError as exc:
            self.send_json({"error": f"Could not launch C executable: {exc}"}, 500)


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
