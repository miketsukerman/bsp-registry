# Yocto Releases

This directory contains the pinned KAS release manifests used by the BSP registry. Each release
has its own directory, with one manifest per supported Yocto Project version or point release.
The upstream release archive is available at
<https://downloads.yoctoproject.org/releases/yocto/>.

## Releases

| Release | Yocto versions | Latest upstream point release | Directory |
|---------|----------------|-------------------------------|-----------|
| Kirkstone | 4.0.x | 4.0.35 (2026-04-29) | [kirkstone](kirkstone/README.md) |
| Mickledore | 4.2.x | 4.2.4 (2023-12-08) | [mickledore](mickledore/README.md) |
| Nanbield | 4.3.x | 4.3.4 (2024-04-09) | [nanbield](nanbield/README.md) |
| Scarthgap | 5.0.x | 5.0.19 (2026-07-21) | [scarthgap](scarthgap/README.md) |
| Styhead | 5.1.x | 5.1.4 (2025-04-01) | [styhead](styhead/README.md) |
| Walnascar | 5.2.x | 5.2.4 (2025-10-14) | [walnascar](walnascar/README.md) |
| Whinlatter | 5.3.x | 5.3.4 (2026-05-12) | [whinlatter](whinlatter/README.md) |
| Wrynose | 6.0.x | 6.0.2 (2026-07-15) | [wrynose](wrynose/README.md) |

The dates in this table are the directory timestamps shown by the upstream Yocto release
archive, consulted on 2026-08-17. They identify the latest point release currently published
upstream; they do not replace the commit pins in the local KAS manifests.

## Using A Release

Use the release-specific entry point in this directory when selecting a Yocto series. The
versioned files below each release directory are useful when a build must be pinned to an exact
point release. KAS combines these release manifests with the shared repository definitions in
[`../yocto.yaml`](../yocto.yaml) and the extension configuration in
[`../yocto-ext.yaml`](../yocto-ext.yaml).

Yocto Project point releases are maintenance updates to a release series. They normally contain
updated fixes and metadata while retaining the series identity, so the exact manifest should be
selected deliberately for reproducibility. Check the upstream archive and release notes before
adding a new point-release manifest.

The versioned manifests pin the upstream repositories and commits needed for reproducible builds.
The top-level `kirkstone.yml`, `mickledore.yml`, and similar files provide release-level entry
points; `master.yml` contains the rolling development configuration.

See the repository [build documentation](../../README.md) for the complete build workflow.
