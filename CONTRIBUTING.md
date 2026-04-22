# Contributing to the BSP Registry

Thank you for contributing! This guide explains how to keep the documentation accurate and consistent.

## Documentation Guidelines

### Source of Truth

`bsp-registry.yml` is the canonical source for:

- BSP names (the `name:` field under the `bsp:` list)
- Device slugs and vendor assignments
- Supported releases per board
- Container definitions

All documentation must be consistent with `bsp-registry.yml`.

### Documentation QA Checklist

Before opening a pull request with documentation changes, verify the following:

**BSP command examples**

- [ ] Every `bsp build <name>` example uses a BSP `name` that exists in `bsp-registry.yml`
- [ ] Every `bsp shell <name>` example uses an existing BSP name
- [ ] No BSP name contains a release suffix (`-scarthgap`, `-walnascar`, etc.) unless the actual BSP name in the registry includes it
- [ ] No trailing characters (e.g., stray `:`) after BSP names in shell commands

**CLI usage**

- [ ] All CLI examples use `bsp` (not the legacy `python bsp.py`)
- [ ] Installation instructions reference `pip3 install bsp-registry-tools`

**Internal links**

- [ ] All relative Markdown links (`[text](path)`) resolve to files that exist in the repository
- [ ] Vendor overlay paths use `vendors/advantech-europe/` (not `vendors/advantech/`) for the Europe overlay READMEs and machine configs

**Version references**

- [ ] Qualcomm QLI version strings match the config filename (`qcom-6.6.97-qli.1.6-ver.1.2-scarthgap.yml` → QLI v1.6 Ver.1.2)
- [ ] Yocto release names are lowercase (`scarthgap`, `walnascar`, etc.) in compatibility matrices

### Verifying BSP Names

Use `grep` to confirm a BSP name exists before documenting it:

```bash
grep "name: <bsp-name>" bsp-registry.yml
```

Or list all BSP names at once:

```bash
grep '^\s*- name:' bsp-registry.yml | awk '{print $3}'
```

### Verifying Internal Links

A quick way to check relative Markdown links from the repository root:

```bash
grep -rh '\](vendors/[^)]*\|patches/[^)]*\|isar/[^)]*\|BUILDING[^)]*)' --include='*.md' \
  | grep -oP '\]\(\K[^)]+' \
  | sort -u \
  | while read f; do [ -e "$f" ] || echo "MISSING: $f"; done
```

## Commit Messages

Use `docs:` as the commit prefix for documentation-only changes, e.g.:

```
docs: fix BSP names in Qualcomm vendor README
docs: update MediaTek build commands to use bsp CLI
```

## Pull Request Process

1. Run the checklist above before opening the PR.
2. If adding a new BSP, also update the relevant compatibility matrix in `README.md` and any vendor README under `vendors/`.
3. If removing or renaming a BSP in `bsp-registry.yml`, search for and update all documentation references to the old name.
