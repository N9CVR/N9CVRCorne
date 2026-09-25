# PandaKB Corne V3 MX ZMK config

Starter ZMK user-config repository for:

- PandaKB Wireless Corne MX V3 PCB
- SuperMini nRF52840 controllers, built with the `nice_nano//zmk` target
- 128x32 Corne OLED modules through the stock Corne shield support
- 54 addressable LEDs total, configured as 27 LEDs per half
- The owner's three-layer traditional Corne keymap
- BLE experimental connection/features settings retained for Windows and Linux compatibility

## Build

1. Create an empty GitHub repository.
2. Unzip this package and push its contents to the repository root.
3. Open the repository's **Actions** tab and select the latest **Build ZMK firmware** run.
4. Download the firmware artifact produced by the workflow.
5. Flash the left and right UF2 files to their matching halves.

A `settings_reset` image is also built. Use it on both halves before the normal left/right images if old split or Bluetooth settings interfere with pairing.

## Hardware assumptions

- The SuperMini is treated as pin-compatible with the ZMK `nice_nano//zmk` board target.
- The stock ZMK Corne shield is expected to provide the matrix, OLED, and LED-strip hardware definitions.
- PandaKB's QMK definition reports 54 LEDs split 27/27. ZMK requires `chain-length` per half, so this keymap uses 27 rather than 54.
- ZMK RGB underglow treats the full addressable LED string as one strip. This should permit static color/effect control over both the per-key and underglow LEDs, but it is not QMK RGB Matrix with individual key coordinates.

## First test

Test keys, USB, BLE, OLED, and RGB at low brightness. Addressable RGB can consume substantial battery current.
