#ifndef CONFIG_H
#define CONFIG_H

#include "pin_defs.h"

/* --- Matrix Settings --- */
#define MATRIX_TYPE DIRECT

#if defined(MCU_nrf52840)
// Direct pins for 20 keys (4 rows x 5 columns)
// Row 0: R0C0 (RST/P0_18), R0C1 (D10/P0_09), R0C2 (D20/P0_29), R0C3 (D8/P1_04), R0C4 (D2/P0_17)
// Row 1: R1C0 (P1.07),     R1C1 (D4/P0_22),  R1C2 (D16/P0_10), R1C3 (D21/P0_31), R1C4 (D7/P0_11)
// Row 2: R2C0 (D19/P0_02), R2C1 (D9/P1_06),  R2C2 (D3/P0_20),  R2C3 (D14/P1_11), R2C4 (P1.01)
// Row 3: R3C0 (D15/P1_13), R3C1 (D0/P0_08),  R3C2 (D6/P1_00),  R3C3 (P1.02),     R3C4 (D18/P1_15)
#define DIRECT_PINS { \
    P0_18, P0_09, P0_29, P1_04, P0_17, \
    P1_07, P0_22, P0_10, P0_31, P0_11, \
    P0_02, P1_06, P0_20, P1_11, P1_01, \
    P1_13, P0_08, P1_00, P1_02, P1_15  \
}
#define RGB_PIN P0_06
#endif

#define VIAL
#define VIAL_KEYBOARD_NAME "nir-pad"
#define VIAL_VENDOR_ID 0xCafe
#define VIAL_PRODUCT_ID 0x4015

/* --- RGB Settings --- */
#define RGB_NUM 30
// clang-format off
#define RGB_MAP { \
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  \
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29  \
}
#define RGB_THEME_DEFAULT { \
    0xFF0000, 0xFF7F00, 0xFFFF00, 0x00FF00, 0x00FFFF, 0x0000FF, 0x8B00FF, 0xFF00FF, 0xFFFFFF, 0x888888, \
    0xFF0000, 0xFF7F00, 0xFFFF00, 0x00FF00, 0x00FFFF, 0x0000FF, 0x8B00FF, 0xFF00FF, 0xFFFFFF, 0x888888, \
    0xFF0000, 0xFF7F00, 0xFFFF00, 0x00FF00, 0x00FFFF, 0x0000FF, 0x8B00FF, 0xFF00FF, 0xFFFFFF, 0x888888  \
}
#define RGB_THEME_GAMING { \
    0xFF4500, 0xFF8C00, 0xFFD700, 0xADFF2F, 0x00FF7F, 0x00CED1, 0x1E90FF, 0x9370DB, 0xFF1493, 0xFF0000, \
    0xFF4500, 0xFF8C00, 0xFFD700, 0xADFF2F, 0x00FF7F, 0x00CED1, 0x1E90FF, 0x9370DB, 0xFF1493, 0xFF0000, \
    0xFF4500, 0xFF8C00, 0xFFD700, 0xADFF2F, 0x00FF7F, 0x00CED1, 0x1E90FF, 0x9370DB, 0xFF1493, 0xFF0000  \
}
#define RGB_THEMES { RGB_THEME_DEFAULT, RGB_THEME_GAMING }
// clang-format on

#define NUM_ROWS 1
#define NUM_COLS 20
#define NUM_KEYS 20

// {ROW, COL}
// clang-format off
#define LAYOUT { \
    {0, 0},  {0, 1},  {0, 2},  {0, 3},  {0, 4},  \
    {0, 5},  {0, 6},  {0, 7},  {0, 8},  {0, 9},  \
    {0, 10}, {0, 11}, {0, 12}, {0, 13}, {0, 14}, \
    {0, 15}, {0, 16}, {0, 17}, {0, 18}, {0, 19}  \
}
#define LAYOUT_DEFAULT LAYOUT

#define LAYOUT_EDITOR { \
    {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, \
    {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, \
    {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, \
    {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}  \
}
// clang-format on

#ifdef DEFINE_KEYMAP
#define DEF 0
#define FN1 1

#if __has_include("keymap_external.h")
#include "keymap_external.h"
#else
// clang-format off
const uint32_t keymap[][NUM_KEYS] = {
    [DEF] = {
        K_ESC,  K_TAB,  K_BSPC, K_DEL,         RGB_TOGG,
        K_KP7,  K_KP8,  K_KP9,  K_KP_SLASH,    RGB_NEXT,
        K_KP4,  K_KP5,  K_KP6,  K_KP_ASTERISK, K_KP_MINUS,
        K_KP1,  K_KP2,  K_KP3,  K_KP_PLUS,     K_KP_ENTER
    },
    [FN1] = {
        K_TRNS, K_TRNS, K_TRNS, K_TRNS,        RGB_TOGG,
        K_HOME, K_UP,   K_PGUP, RGB_HUI,       RGB_HUD,
        K_LEFT, K_KP0,  K_RIGHT, RGB_SAI,      RGB_SAD,
        K_END,  K_DOWN, K_PGDN, RGB_VAI,       RGB_VAD
    }
};
// clang-format on

const size_t keymap_layers = sizeof(keymap) / sizeof(keymap[0]);

const Macro keyboard_macros[] = {};
const uint8_t keyboard_macros_count = sizeof(keyboard_macros) / sizeof(keyboard_macros[0]);
#endif
#endif

#endif // CONFIG_H
