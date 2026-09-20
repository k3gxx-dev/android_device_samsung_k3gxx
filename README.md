# Samsung Galaxy S5 Exynos 3G (SM-G900H) Device Tree

Device tree and product configuration for the **Samsung Galaxy S5 Exynos 3G (SM-G900H, codename `k3gxx`)** targeting **LineageOS 18.1 (Android 11)**.

## Overview

- **SoC**: Samsung Exynos 5422 (Octa-core: 4x Cortex-A15 @ 1.9GHz + 4x Cortex-A7 @ 1.3GHz)
- **Architecture**: ARMv7-A (32-bit)
- **Android Target**: LineageOS 18.1 (Android 11)
- **Common Platform**: Inherits [`universal5420-common`](../universal5420-common) via explicit `TARGET_SOC := exynos5422` conditionals.

## Repository Structure

- `BoardConfig.mk` / `device.mk`: Hardware definitions, partition sizes, vendor interfaces, and product packages.
- `configs/`: Audio policy, media codecs, GPS, Wi-Fi, Bluetooth, and GPS configurations.
- `ramdisk/`: Init rc scripts for Exynos 5422 hardware initialization.
- `sepolicy/`: SELinux security policies and context definitions for vendor components.
- `configs/permissions/`: System feature XML definitions.

## Build Target

Configured for `lineage_k3gxx-userdebug`:

```bash
source build/envsetup.sh
lunch lineage_k3gxx-userdebug
m bacon
```
