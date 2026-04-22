# MediaTek BSP (Rity)

This directory contains the **MediaTek vendor BSP integration** for the Advantech BSP Registry.
The current integration is based on **MediaTek AIoT Rity** for **Yocto Scarthgap** and is intended
to be built through the registry manager (`bsp` CLI from `bsp-registry-tools`) which takes care of container selection,
cache variables, and the build directory layout.

## What’s included

### KAS fragments (layers + pins)

- `mtk-rity-v25.0-scarthgap.yml`
  - Pulls MediaTek Rity layers from GitLab and pins them to `refs/tags/rity-scarthgap-v25.0`.
  - Enables extra build features used by this registry:
    - `yocto/scarthgap.yml` (base Yocto Scarthgap repos)
    - `compilers/clang/clang.yml`
    - `features/deep-learning/tensorflow.yml`
  - Applies local patches from this repository:
    - `patches/mediatek/scarthgap/0001-Fix-recipe-dtbo-name.patch`
    - `patches/mediatek/scarthgap/0002-Fix-git-checkout-for-arm-compute-library.patch`

### Reference machine configs

- `evk/genio-1200-evk.yml`
  - Machine: `genio-1200-evk`
  - Target image: `rity-demo-image`
  - Adds distro features required by the Rity demo distro:
    - `DISTRO_FEATURES += "wayland opengl vulkan"`
    - `LICENSE_FLAGS_ACCEPTED += "commercial"`

## BSPs in the registry

The top-level registry file `bsp-registry.yml` currently exposes the following MediaTek BSP build targets:

- `mediatek-genio-1200-evk`
  - Device: `genio-1200-evk`
  - Build dir: `build/mediatek-genio-1200-evk`

## Build instructions (recommended)

From the repository root:

```bash
# List available BSPs
bsp list | grep -i mediatek

# Fast config checkout/validation (no build)
bsp build mediatek-genio-1200-evk --checkout

# Full build
bsp build mediatek-genio-1200-evk

# Enter an interactive build shell
bsp shell mediatek-genio-1200-evk
```

Build artifacts follow the standard Yocto layout under the registry build directory, e.g.:

`build/<bsp-name>/build/tmp/deploy/images/<machine>/`

## References

- MediaTek Genio 1200 EVK documentation:
  https://mediatek.gitlab.io/aiot/doc/aiot-dev-guide/master/hw/g1200-evk.html
- Upstream Rity layers (referenced by `mtk-rity-v25.0-scarthgap.yml`):
  - https://gitlab.com/mediatek/aiot/rity/
