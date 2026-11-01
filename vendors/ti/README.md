# Texas Instruments BSP (Arago Project `meta-ti` / `meta-arago`)

This directory contains the **Texas Instruments vendor BSP integration** for the BSP
Registry. It is based on the TI **[Arago Project](https://www.arago-project.org/)** layers
(`meta-ti`, `meta-arago`) and the `arago` reference distribution. Builds are driven through
the registry manager (`bsp`), which selects the container, cache variables and build
directory layout.

## What's included

### Vendor common (`ti-common.yml`)

- Sets the distro to `arago` (the Arago Project reference distribution provided by
  `meta-arago-distro`).
- Default image targets: `tisdk-base-image` and `tisdk-default-image`.
- Accepts the TI EULA (`LICENSE_FLAGS_ACCEPTED += "ti-eula-unrestricted-binaries"`) required
  by the TI-licensed firmware and multimedia binaries.

### Layer-pin fragments

Each fragment pins `meta-ti` (`meta-ti-bsp`, `meta-ti-extras`) and `meta-arago`
(`meta-arago-distro`, `meta-arago-extras`) to a specific commit on the matching Arago branch.
The `meta-arm` / `meta-arm-toolchain` layers required for TF-A and OP-TEE are already provided
by the generic Yocto release fragments (`yocto/releases/<release>.yml`).

| Fragment | Arago branch | Yocto release |
|----------|--------------|---------------|
| `ti-scarthgap.yml` | `scarthgap` | Yocto 5.0 LTS (Scarthgap) |
| `ti-kirkstone.yml` | `kirkstone` | Yocto 4.0 LTS (Kirkstone) |
| `ti-wrynose.yml`   | `wrynose`   | Yocto 6.0 (Wrynose) |

### Reference machine configs (`machine/`)

- Sitara: `am62xx-evm`, `am64xx-evm`
- Jacinto: `j721e-evm` (TDA4VM), `j722s-evm` (AM67x / J722S, AM6734)

## BSPs in the registry

The top-level `bsp-registry.yml` exposes these TI presets:

| Preset | Releases | SoC |
|--------|----------|-----|
| `am62xx-evm` | kirkstone, scarthgap, wrynose | Sitara AM62x |
| `am64xx-evm` | kirkstone, scarthgap, wrynose | Sitara AM64x |
| `j721e-evm`  | kirkstone, scarthgap, wrynose | Jacinto J721e (TDA4VM) |
| `j722s-evm`  | kirkstone, scarthgap, wrynose | AM67x / J722S (AM6734) |

## Build instructions

From the repository root:

```bash
# List available TI BSPs
bsp list | grep -Ei 'am62|am64|j721e'

# Fast config checkout/validation (no build)
bsp build am62xx-evm-scarthgap --checkout

# Full build
bsp build am62xx-evm-scarthgap

# Interactive build shell
bsp shell am62xx-evm-scarthgap
```

Build artifacts follow the standard Yocto layout, e.g.:

`build/<bsp-name>/build/tmp/deploy/images/<machine>/`

## Notes and limitations

- **TI K3 dual-boot firmware:** the AM6x / J7 (K3) SoCs boot a Cortex-R5 first-stage loader
  before the Cortex-A cores. `meta-ti` builds the R5 (`*-k3r5`) artifacts automatically as part
  of the main machine build; no separate preset is required.
- **Proprietary components / licensing:** the TI BSP downloads TI-licensed firmware and
  multimedia binaries that require accepting the TI EULA (handled in `ti-common.yml`).
- **Flashing:** TI EVMs use SD-card / `wic` images compatible with the registry's generic
  `bmaptool` / `wic` flow; eMMC and UART/USB-DFU boot flows may require follow-up configuration.

## References

- Arago Project: https://www.arago-project.org/
- meta-ti: https://git.ti.com/cgit/arago-project/meta-ti/ (GitHub mirror:
  https://github.com/TexasInstruments/meta-ti)
- meta-arago: https://git.ti.com/cgit/arago-project/meta-arago/ (GitHub mirror:
  https://github.com/TexasInstruments/meta-arago)
- TI Processor SDK Linux: https://www.ti.com/tool/PROCESSOR-SDK-LINUX
