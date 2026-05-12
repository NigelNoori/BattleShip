#!/usr/bin/env python3
"""
Battleship CORS Proxy + Static File Server
Run: python3 proxy.py
Then open: http://localhost:8080

Routes:
  /api/*  -> forwarded to gameServer at localhost:8800 (strips /api prefix)
  /*      -> serves static files from current directory (index.html etc.)
"""

import http.server
import urllib.request
import urllib.error
import json
import os
import sys

GAME_SERVER   = "http://localhost:8800"
PROXY_PORT    = 8080

CORS_HEADERS = {
    "Access-Control-Allow-Origin":  "*",
    "Access-Control-Allow-Methods": "GET, POST, PUT, DELETE, OPTIONS",
    "Access-Control-Allow-Headers": "Content-Type, Authorization",
}

class ProxyHandler(http.server.SimpleHTTPRequestHandler):

    def end_headers(self):
        for k, v in CORS_HEADERS.items():
            self.send_header(k, v)
        super().end_headers()

    def do_OPTIONS(self):
        self.send_response(200)
        self.end_headers()

    def _proxy(self, method):
        if not self.path.startswith("/api"):
            # Serve static file
            return super().do_GET() if method == "GET" else None

        backend_path = self.path[4:]  # strip /api
        url = GAME_SERVER + backend_path

        content_length = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(content_length) if content_length else None

        req = urllib.request.Request(url, data=body, method=method)
        if body:
            req.add_header("Content-Type", "application/json")

        try:
            with urllib.request.urlopen(req, timeout=5) as resp:
                data = resp.read()
                self.send_response(resp.status)
                self.send_header("Content-Type", "application/json")
                self.end_headers()
                self.wfile.write(data)
        except urllib.error.HTTPError as e:
            data = e.read()
            self.send_response(e.code)
            self.send_header("Content-Type", "application/json")
            self.end_headers()
            self.wfile.write(data)
        except Exception as e:
            self.send_response(502)
            self.send_header("Content-Type", "application/json")
            self.end_headers()
            self.wfile.write(json.dumps({"error": str(e)}).encode())

    def do_GET(self):
        if self.path.startswith("/api"):
            self._proxy("GET")
        else:
            super().do_GET()

    def do_POST(self):
        self._proxy("POST")

    def do_DELETE(self):
        self._proxy("DELETE")

    def log_message(self, fmt, *args):
        # Quieter logging
        if "/api" in (args[0] if args else ""):
            print(f"  → {args[0][:60]}")

if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    port = int(sys.argv[1]) if len(sys.argv) > 1 else PROXY_PORT
    print(f"🚢  Battleship proxy running at http://localhost:{port}")
    print(f"    Forwarding /api/* → {GAME_SERVER}")
    print(f"    Serving static files from: {os.getcwd()}")
    print(f"    Open: http://localhost:{port}/index.html\n")
    server = http.server.HTTPServer(("", port), ProxyHandler)
    server.serve_forever()
