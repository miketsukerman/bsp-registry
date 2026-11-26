#!/usr/bin/env python3
"""Give the build access to private GitHub repositories.

usage: setup_github_netrc.py <netrc-file>

Some presets use layers from private GitHub repositories (e.g. the OTA
features use Advantech-EECC/meta-modular-bsp-ota). When the secret pipeline
variable GITHUB_FETCH_TOKEN is set (mapped into this step's environment), a
netrc file with that token for github.com is written to <netrc-file> (mode
0600) and NETRC_FILE is exported to the following steps.

kas-container mounts NETRC_FILE into the build container and kas installs it
as ~/.netrc of the build, so both the kas layer checkout and BitBake's git
fetcher authenticate with it. The token never appears in a repository URL,
so it does not end up in logs, git mirrors in DL_DIR or build artifacts.

Use a read-only token: a fine-grained personal access token (or GitHub App
installation token) with "Contents: read" on the private repositories only.

Without the variable nothing is written: public presets build as before,
presets with private repositories fail to fetch them.
"""

import os
import sys

TOKEN_VAR = "GITHUB_FETCH_TOKEN"
HOST = "github.com"
# Any user name works with a PAT; GitHub App tokens require this one.
LOGIN = "x-access-token"


def github_token(env):
    """The token from *env*, or "" when unset, blank or an unresolved $(...) macro.

    Azure Pipelines passes the macro text literally when the variable is not
    defined, e.g. "$(GITHUB_FETCH_TOKEN)".
    """
    token = (env.get(TOKEN_VAR) or "").strip()
    if token.startswith("$("):
        return ""
    return token


def netrc_text(token):
    """netrc entry authenticating *token* for github.com."""
    if any(c.isspace() for c in token):
        raise ValueError(f"{TOKEN_VAR} must not contain whitespace")
    return f"machine {HOST}\nlogin {LOGIN}\npassword {token}\n"


def main(argv):
    if len(argv) != 2:
        print(__doc__.strip().splitlines()[2], file=sys.stderr)
        return 2
    netrc_file = os.path.abspath(argv[1])
    token = github_token(os.environ)
    if not token:
        print(f"{TOKEN_VAR} is not set: private GitHub repositories cannot be fetched "
              "(public presets are not affected).")
        return 0
    try:
        text = netrc_text(token)
    except ValueError as e:
        print(f"##vso[task.logissue type=error]{e}")
        return 1

    os.makedirs(os.path.dirname(netrc_file), exist_ok=True)
    fd = os.open(netrc_file, os.O_WRONLY | os.O_CREAT | os.O_TRUNC, 0o600)
    with os.fdopen(fd, "w", encoding="utf-8") as f:
        f.write(text)
    os.chmod(netrc_file, 0o600)  # also when the file already existed

    print(f"GitHub credentials for {HOST} written to {netrc_file}")
    print(f"##vso[task.setvariable variable=NETRC_FILE]{netrc_file}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
