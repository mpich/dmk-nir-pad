# dmk-nir-pad

Custom keyboard hardware and layout configuration for **nir-pad** (20 direct-pin keys, 30 WS2812 RGB LEDs) based on **[DMK Firmware](https://github.com/aroum/dmk)**.

## Hardware Specification

- **MCU:** nRF52840 (e.g. SuperMini nRF52840 / Pro Micro nRF52840)
- **Matrix Type:** `DIRECT` (20 keys, 4 rows x 5 columns)
- **RGB Underglow/Backlight:** 30x WS2812 LEDs on `P0_06` (Pin 1 / D1)
- **Vial Support:** Enabled (`vial.json` and pre-generated `vial_generated.h`)

### Pinout Mapping

| Label | Key Index | Schematic Pin | MCU GPIO Pin |
|---|---|---|---|
| **R0C0** | 0 | Pin 22 (RST) | `P0_18` |
| **R0C1** | 1 | Pin 7 (D4) | `P0_22` |
| **R0C2** | 2 | Pin 6 (D3) | `P0_20` |
| **R0C3** | 3 | Pin 5 (D2) | `P0_17` |
| **R0C4** | 4 | Pin 2 (D0) | `P0_08` |
| **R1C0** | 5 | Pin 27 | `P1_01` |
| **R1C1** | 6 | Pin 12 (D9) | `P1_06` |
| **R1C2** | 7 | Pin 11 (D8) | `P1_04` |
| **R1C3** | 8 | Pin 10 (D7) | `P0_11` |
| **R1C4** | 9 | Pin 9 (D6) | `P1_00` |
| **R2C0** | 10 | Pin 18 (D19) | `P0_02` |
| **R2C1** | 11 | Pin 19 (D20) | `P0_29` |
| **R2C2** | 12 | Pin 20 (D21) | `P0_31` |
| **R2C3** | 13 | Pin 25 | `P1_07` |
| **R2C4** | 14 | Pin 26 | `P1_02` |
| **R3C0** | 15 | Pin 13 (D10) | `P0_09` |
| **R3C1** | 16 | Pin 14 (D16) | `P0_10` |
| **R3C2** | 17 | Pin 15 (D14) | `P1_11` |
| **R3C3** | 18 | Pin 16 (D15) | `P1_13` |
| **R3C4** | 19 | Pin 17 (D18) | `P1_15` |
| **RGB** | - | Pin 1 (D1) | `P0_06` (30 LEDs) |

## Layout: Frogpad (Left & Right Hand)

The default layout implements the **Frogpad** layout with support for one-handed typing on either hand:

- **Layers 0–3 (Left Hand):**
  - **Layer 0 (Base):** Primary 15 keys + thumb row (`Shift`, `Enter`, `Symbol`, `Number`, `Space [Hold: Green]`).
  - **Layer 1 (Green):** Secondary characters and symbols activated by holding `Space`.
  - **Layer 2 (Number):** Numeric keypad (3x3 grid) and navigation keys activated by holding `Number`.
  - **Layer 3 (Symbol):** Punctuation and brackets activated by holding `Symbol`.
- **Layers 4–7 (Right Hand):**
  - Full horizontal mirror of all layers and thumb cluster (`Space [Hold: Green]`, `Number`, `Symbol`, `Enter`, `Shift`).
- **Hand Switching Chord:**
  - Pressing all 4 resting fingers on the home row (`D + T + H + E` or `T + H + E + O` on left hand, and mirrored on right hand) instantly toggles between Left Hand mode (Layer 0) and Right Hand mode (Layer 4).

## How to Build

### 1. GitHub Actions (Automatic)
Push changes to the `main` or `master` branch and download the `.uf2` binary from the **Actions** tab artifacts.

### 2. Local Build
```bash
# Clone DMK firmware core
git clone https://github.com/aroum/dmk.git
mkdir -p dmk/keyboards

# Copy nir-pad config
cp -r keyboards/nir-pad dmk/keyboards/

# Build
cd dmk
./build_all.sh -b nir-pad --mcu nrf52840 -c --uf2
```
