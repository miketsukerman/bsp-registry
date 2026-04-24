# Release Notes — v1.0

**Release date:** April 2026  
**Repository:** [miketsukerman/bsp-registry](https://github.com/miketsukerman/bsp-registry)

---

## Overview

Version 1.0 marks the first stable release of the **Advantech BSP Configurations Registry** — a structured, reproducible build configuration registry for Advantech embedded hardware platforms. This release establishes the registry schema, tooling, multi-platform hardware support, and an extensible feature system for embedded Linux BSPs.

---

## What's New

### Build System Support

- **Yocto Project** build system support with KAS integration, covering Yocto releases:
  - Whinlatter (5.3)
  - Walnascar (5.2)
  - Styhead (5.1)
  - Scarthgap (5.0 LTS)
  - Mickledore (4.2)
  - Kirkstone (4.0 LTS)

- **Isar** (Integration System for Automated Root filesystem generation) build system support for Debian-based embedded systems:
  - Supports Debian Bookworm, Bullseye, Trixie, Sid
  - Supports Ubuntu Focal, Jammy, Noble
  - QEMU targets available for ARM and ARM64 (ready for testing)
  - RSB-3720 Isar target (in development)

### Hardware Platform Support

#### NXP Boards (Stable)

| Board          | Supported Yocto Releases                               | Status     |
|----------------|--------------------------------------------------------|------------|
| RSB-3720       | whinlatter, walnascar, styhead, scarthgap              | 🟢 Stable  |
| RSB-3720 4G    | whinlatter, walnascar                                  | 🟢 Stable  |
| RSB-3720 6G    | whinlatter, walnascar                                  | 🟢 Stable  |
| RSB-3730       | mickledore                                             | 🟡 Development |
| ROM-2620       | whinlatter, walnascar, styhead, scarthgap              | 🟢 Stable  |
| ROM-5720       | whinlatter, walnascar, styhead, scarthgap              | 🟢 Stable  |
| ROM-5721       | whinlatter, walnascar, styhead, scarthgap, mickledore  | 🟢 Stable  |
| ROM-5721 1G    | whinlatter, walnascar, scarthgap, mickledore           | 🟢 Stable  |
| ROM-5721 2G    | whinlatter, walnascar, scarthgap, mickledore           | 🟢 Stable  |
| ROM-5722       | whinlatter, walnascar, styhead, scarthgap              | 🟢 Stable  |
| ROM-2820       | whinlatter, walnascar, styhead, scarthgap              | 🟢 Stable  |
| AOM-5521 A1    | scarthgap (stable), walnascar (development)            | 🟢 Stable  |
| AOM-5521 A2    | walnascar                                              | 🟢 Stable  |

#### MediaTek Boards (Development)

| Board              | Supported Yocto Releases | Status          |
|--------------------|--------------------------|-----------------|
| Genio 1200 EVK     | scarthgap                | 🟡 Development  |
| RSB-3810           | scarthgap                | 🟡 Development  |

MediaTek support is built on the **MediaTek AIoT Rity** BSP stack (Rity v25.0).

#### Qualcomm Boards (Development)

| Board              | Supported Yocto Releases | Status          |
|--------------------|--------------------------|-----------------|
| QCS6490 RB3gen2    | scarthgap                | 🟡 Development  |
| AOM-2721           | scarthgap                | 🟡 Development  |

Qualcomm support is built on the **Qualcomm Linux (QLI)** BSP stack (QLI v1.5 Ver.1.1).

### Optional Feature Layers

The registry introduces an extensible feature system. Features are opt-in KAS configuration overlays that add capabilities to any compatible BSP:

| Feature          | Description                                                                 |
|------------------|-----------------------------------------------------------------------------|
| **Qt**           | Qt6 framework support (versions 6.3, 6.5, 6.7, 6.8.x, 6.9.x)             |
| **ROS 2**        | Robot Operating System 2 support (Humble, Jazzy, Kilted, Rolling)          |
| **OTA — RAUC**   | Robust Auto-Update Controller with atomic updates and rollback support      |
| **OTA — SWUpdate** | SWUpdate-based software update framework for embedded systems             |
| **OTA — OSTree** | Atomic filesystem-tree upgrades (whinlatter, walnascar, styhead, scarthgap) |
| **Browser**      | Browser integration support                                                  |
| **Cameras**      | Camera subsystem support (including Intel RealSense)                         |
| **Deep Learning** | AI accelerator support including Hailo and TensorFlow                       |
| **Python AI**    | Python-based AI/ML framework integration                                     |
| **Protocols**    | Additional protocol stack support (Zenoh, etc.)                              |
| **SBOM**         | Software Bill of Materials generation support (Timesys)                     |

#### OTA Support Matrix

| Board             | RAUC | SWUpdate | OSTree | Supported Releases                            |
|-------------------|:----:|:--------:|:------:|-----------------------------------------------|
| RSB-3720          | ✅   | ✅       | ✅     | whinlatter, walnascar, styhead, scarthgap      |
| RSB-3720 4G       | ✅   | ✅       | ❌     | whinlatter, walnascar                          |
| RSB-3720 6G       | ✅   | ✅       | ❌     | whinlatter, walnascar                          |
| ROM-2620          | ✅   | ✅       | ✅     | whinlatter, walnascar, styhead, scarthgap      |
| ROM-2820          | ✅   | ✅       | ✅     | whinlatter, walnascar, styhead, scarthgap      |
| ROM-5720          | ✅   | ✅       | ✅     | whinlatter, walnascar, styhead, scarthgap      |
| ROM-5721 1G       | ✅   | ✅       | ✅     | whinlatter, walnascar                          |
| ROM-5721 2G       | ✅   | ✅       | ✅     | whinlatter, walnascar                          |
| ROM-5722          | ✅   | ✅       | ✅     | whinlatter, walnascar, styhead, scarthgap      |

### BSP Registry Manager (`bsp` CLI)

The registry is managed via the [`bsp-registry-tools`](https://pypi.org/project/bsp-registry-tools/) Python package (Python 3.7+), which provides:

- `bsp list` — list all available BSPs in the registry
- `bsp build <bsp>` — build a BSP using KAS in an isolated Docker container
- `bsp build <bsp> --checkout` — fast checkout and validation without a full build (useful for CI)
- `bsp shell <bsp>` — enter an interactive build shell
- `bsp export <bsp>` — export a flattened KAS configuration
- `bsp containers` — list all available container definitions

### Docker Container Environments

Pre-defined, reproducible build containers are included for all supported build environments:

| Container         | Base OS            | KAS Version |
|-------------------|--------------------|-------------|
| `ubuntu-20.04`    | Ubuntu 20.04       | 4.7         |
| `ubuntu-22.04`    | Ubuntu 22.04       | 5.2         |
| `ubuntu-24.04`    | Ubuntu 24.04       | 5.2         |
| `debian-12`       | Debian Bookworm    | 5.2         |
| `debian-13`       | Debian Trixie      | 5.2         |
| `isar-debian-13`  | Debian Trixie (Isar) | 5.2       |

### CI / Validation

- GitHub Actions workflows for automated KAS configuration validation
- GitHub Actions workflows for Docker container image validation
- Azure Pipelines integration with BSP build matrix generation

### Registry Schema

- Registry schema version `2.0` with structured support for:
  - Global and per-BSP environment variable management (with `$ENV{}` expansion)
  - Artifact deployment configuration (Azure Storage)
  - LAVA test framework integration
  - Named build environments referencing shared container definitions

---

## Known Limitations

- **MediaTek** and **Qualcomm** board support is in active development and may have build or runtime limitations
- **RSB-3730** (NXP) is in development; production use is not recommended
- **RSB-3720 Isar** support is under development; QEMU Isar targets are functional
- **Isar QEMU networking** requires `--device=/dev/net/tun --cap-add=NET_ADMIN` (handled automatically by the registry)

---

## Getting Started

```bash
# Install the BSP Registry Manager
pip3 install bsp-registry-tools

# List all available BSPs
bsp list

# Build an NXP board BSP (example)
bsp build modular-bsp-rsb3720-walnascar

# Build an Isar QEMU target
bsp build isar-qemuarm64-debian-trixie

# Validate a configuration without building
bsp build modular-bsp-rsb3720-walnascar --checkout
```

For full documentation, see the [README](README.md) and the [Isar README](isar/README.md).

---

## Links

- [Advantech EECC GitHub](https://github.com/Advantech-EECC)
- [bsp-registry-tools on PyPI](https://pypi.org/project/bsp-registry-tools/)
- [Yocto Project Releases](https://www.yoctoproject.org/development/releases/)
- [Isar Build System](https://github.com/ilbers/isar)
- [KAS Build Tool](https://kas.readthedocs.io/)
