# PandaKB Corne V3 MX ZMK config

ZMK user-config repository for:

- PandaKB Wireless Corne MX V3 PCB
- SuperMini nRF52840 controllers, built with the `nice_nano_v2` target
- 128x32 Corne OLED modules through the stock Corne shield support
- 54 addressable LEDs total, configured as 27 LEDs per half
- The owner's three-layer traditional Corne keymap
- BLE experimental connection/features settings retained for Windows and Linux compatibility

## Maturity

Slightly embarassingly, it turns out AI can write code better than I can. AI helped significantly with this build; hence the jump from Take 2 to Take 4. Takes after 4 will likely only contain slight changes to keymaps, etc. 

## Original Roadmap

 - Take 1: Initial functional firmware. I'm currently typing this on my Corne with Take 1 firmware.
 - Take 2: RGB LEDs support
 - Take 3: Turning off the Nice!Nano onboard LEDs. Turns out this may not be very possible.
 - Take 4: OLED support. This will likely take a while as OLED support in ZMK is flaky enough that ZMK themselves advise against using it.
