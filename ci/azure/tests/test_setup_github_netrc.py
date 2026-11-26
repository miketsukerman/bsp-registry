"""Unit tests for ci/azure/setup_github_netrc.py."""

import io
import os
import stat
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from unittest import mock

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

import setup_github_netrc as sgn  # noqa: E402


class GithubTokenTest(unittest.TestCase):
    def test_token_stripped(self):
        self.assertEqual(sgn.github_token({"GITHUB_FETCH_TOKEN": " ghp_abc\n"}), "ghp_abc")

    def test_unset_blank_or_unresolved_macro(self):
        for env in ({}, {"GITHUB_FETCH_TOKEN": " "}, {"GITHUB_FETCH_TOKEN": "$(GITHUB_FETCH_TOKEN)"}):
            self.assertEqual(sgn.github_token(env), "")


class NetrcTextTest(unittest.TestCase):
    def test_entry_for_github(self):
        self.assertEqual(sgn.netrc_text("tok"),
                         "machine github.com\nlogin x-access-token\npassword tok\n")

    def test_whitespace_rejected(self):
        with self.assertRaises(ValueError):
            sgn.netrc_text("a b")


class MainTest(unittest.TestCase):
    def run_main(self, env, path):
        buf = io.StringIO()
        with mock.patch.dict(os.environ, env, clear=True), redirect_stdout(buf):
            rc = sgn.main(["x", path])
        return rc, buf.getvalue()

    def test_writes_private_file_and_exports_variable(self):
        with tempfile.TemporaryDirectory() as d:
            path = os.path.join(d, "sub", "netrc")
            rc, out = self.run_main({"GITHUB_FETCH_TOKEN": "tok"}, path)
            self.assertEqual(rc, 0)
            with open(path) as f:
                self.assertIn("password tok\n", f.read())
            self.assertEqual(stat.S_IMODE(os.stat(path).st_mode), 0o600)
            self.assertIn(f"##vso[task.setvariable variable=NETRC_FILE]{path}", out)
            self.assertNotIn("tok", out.replace(path, ""))

    def test_existing_file_made_private(self):
        with tempfile.TemporaryDirectory() as d:
            path = os.path.join(d, "netrc")
            with open(path, "w") as f:
                f.write("old")
            os.chmod(path, 0o644)
            self.assertEqual(self.run_main({"GITHUB_FETCH_TOKEN": "tok"}, path)[0], 0)
            self.assertEqual(stat.S_IMODE(os.stat(path).st_mode), 0o600)

    def test_no_token_writes_nothing(self):
        with tempfile.TemporaryDirectory() as d:
            path = os.path.join(d, "netrc")
            rc, out = self.run_main({"GITHUB_FETCH_TOKEN": "$(GITHUB_FETCH_TOKEN)"}, path)
            self.assertEqual(rc, 0)
            self.assertFalse(os.path.exists(path))
            self.assertNotIn("NETRC_FILE", out)

    def test_invalid_token_fails(self):
        with tempfile.TemporaryDirectory() as d:
            path = os.path.join(d, "netrc")
            rc, out = self.run_main({"GITHUB_FETCH_TOKEN": "a b"}, path)
            self.assertEqual(rc, 1)
            self.assertIn("task.logissue type=error", out)
            self.assertFalse(os.path.exists(path))

    def test_usage(self):
        with redirect_stdout(io.StringIO()), mock.patch("sys.stderr", io.StringIO()):
            self.assertEqual(sgn.main(["x"]), 2)


if __name__ == "__main__":
    unittest.main()
