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
#define DIRECT_PINS {     P0_18, P0_22, P0_20, P0_17, P0_08,     P1_01, P1_06, P1_04, P0_11, P1_00,     P0_02, P0_29, P0_31, P1_07, P1_02,     P0_09, P0_10, P1_11, P1_13, P1_15  }
#define RGB_PIN P0_06
#endif

#ifndef VIAL
#define VIAL
#endif
#define VIAL_KEYBOARD_NAME "nir-pad"
#define VIAL_VENDOR_ID 0xCafe
#define VIAL_PRODUCT_ID 0x4015

/* --- RGB Settings --- */
#define RGB_NUM 30
// clang-format off
#define RGB_MAP {     0,  1,  2,  3,  4,  5,  6,  7,  8,  9,      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,     20, 21, 22, 23, 24, 25, 26, 27, 28, 29  }
#define RGB_THEME_DEFAULT {     0xFF0000, 0xFF7F00, 0xFFFF00, 0x00FF00, 0x00FFFF, 0x0000FF, 0x8B00FF, 0xFF00FF, 0xFFFFFF, 0x888888,     0xFF0000, 0xFF7F00, 0xFFFF00, 0x00FF00, 0x00FFFF, 0x0000FF, 0x8B00FF, 0xFF00FF, 0xFFFFFF, 0x888888,     0xFF0000, 0xFF7F00, 0xFFFF00, 0x00FF00, 0x00FFFF, 0x0000FF, 0x8B00FF, 0xFF00FF, 0xFFFFFF, 0x888888  }
#define RGB_THEME_GAMING {     0xFF4500, 0xFF8C00, 0xFFD700, 0xADFF2F, 0x00FF7F, 0x00CED1, 0x1E90FF, 0x9370DB, 0xFF1493, 0xFF0000,     0xFF4500, 0xFF8C00, 0xFFD700, 0xADFF2F, 0x00FF7F, 0x00CED1, 0x1E90FF, 0x9370DB, 0xFF1493, 0xFF0000,     0xFF4500, 0xFF8C00, 0xFFD700, 0xADFF2F, 0x00FF7F, 0x00CED1, 0x1E90FF, 0x9370DB, 0xFF1493, 0xFF0000  }
#define RGB_THEMES { RGB_THEME_DEFAULT, RGB_THEME_GAMING }
// clang-format on

#define NUM_ROWS 1
#define NUM_COLS 20
#define NUM_KEYS 20

// {ROW, COL}
// clang-format off
#define LAYOUT {     {0, 0},  {0, 1},  {0, 2},  {0, 3},  {0, 4},      {0, 5},  {0, 6},  {0, 7},  {0, 8},  {0, 9},      {0, 10}, {0, 11}, {0, 12}, {0, 13}, {0, 14},     {0, 15}, {0, 16}, {0, 17}, {0, 18}, {0, 19}  }
#define LAYOUT_DEFAULT LAYOUT

#define LAYOUT_EDITOR {     {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4},     {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4},     {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4},     {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}  }
// clang-format on

/* --- Chords Configuration --- */
#define CHORD_TIMEOUT_MS 100
#define CHORDS_COUNT 4

#ifdef DEFINE_KEYMAP

// Frogpad Layer Enumeration (8 layers total: 4 Left Hand + 4 Right Hand)
enum frogpad_layers {
    L_BASE = 0,   // Left hand: Base layer
    L_GREEN = 1,  // Left hand: Green layer (hold Space)
    L_NUM = 2,    // Left hand: Number/Nav layer (hold Number)
    L_SYM = 3,    // Left hand: Symbol layer (hold Symbol)
    R_BASE = 4,   // Right hand: Base layer (mirrored)
    R_GREEN = 5,  // Right hand: Green layer (mirrored)
    R_NUM = 6,    // Right hand: Number/Nav layer (mirrored)
    R_SYM = 7     // Right hand: Symbol layer (mirrored)
};

// Toggle Hand Layout action (switches between Left Hand base layer 0 and Right Hand base layer 4)
extern void layers_set_state(uint16_t state);

static bool s_is_right_hand = false;

static void toggle_hand_layout(void) {
    s_is_right_hand = !s_is_right_hand;
    if (s_is_right_hand) {
        layers_set_state(1U << R_BASE);
    } else {
        layers_set_state(1U << L_BASE);
    }
}

// 4-key chords for switching between Left and Right hand:
// 4 fingers on home row (D, T, H, E or T, H, E, O)
const Chord my_chords[CHORDS_COUNT] = {
    // Left hand (layer 0) -> Right hand (layer 4)
    {
        .keys = { K(0, 5, L_BASE), K(0, 6, L_BASE), K(0, 7, L_BASE), K(0, 8, L_BASE) },
        .key_count = 4,
        .action = toggle_hand_layout
    },
    {
        .keys = { K(0, 6, L_BASE), K(0, 7, L_BASE), K(0, 8, L_BASE), K(0, 9, L_BASE) },
        .key_count = 4,
        .action = toggle_hand_layout
    },
    // Right hand (layer 4) -> Left hand (layer 0)
    {
        .keys = { K(0, 5, R_BASE), K(0, 6, R_BASE), K(0, 7, R_BASE), K(0, 8, R_BASE) },
        .key_count = 4,
        .action = toggle_hand_layout
    },
    {
        .keys = { K(0, 6, R_BASE), K(0, 7, R_BASE), K(0, 8, R_BASE), K(0, 9, R_BASE) },
        .key_count = 4,
        .action = toggle_hand_layout
    }
};

#if __has_include("keymap_external.h")
#include "keymap_external.h"
#else
// clang-format off
const uint32_t keymap[][NUM_KEYS] = {
    /* -------------------------------------------------------------
     * LEFT HAND - LAYER 0: BASE
     * ------------------------------------------------------------- */
    [L_BASE] = {
        // Row 0: P, W, R, A, F
        K_P,               K_W,               K_R,               K_A,               K_F,
        // Row 1: D, T, H, E, O
        K_D,               K_T,               K_H,               K_E,               K_O,
        // Row 2: Y, S, N, I, U
        K_Y,               K_S,               K_N,               K_I,               K_U,
        // Row 3: Shift, Enter, Symbol, Number, Space (Hold: Green)
        K_LSFT,          K_ENT,           MO(L_SYM),         MO(L_NUM),         HT(L_GREEN, K_SPC)
    },

    /* -------------------------------------------------------------
     * LEFT HAND - LAYER 1: GREEN (Space held)
     * ------------------------------------------------------------- */
    [L_GREEN] = {
        // Row 0: J, M, B, ', Tab
        K_J,               K_M,               K_B,               K_QUOT,            K_TAB,
        // Row 1: V, C, L, Z, Q
        K_V,               K_C,               K_L,               K_Z,               K_Q,
        // Row 2: X, G, K, Backspace, Delete
        K_X,               K_G,               K_K,               K_BSPC,            K_DEL,
        // Row 3: Trans, Period, Comma, Trans, Trans
        K_TRNS,            K_DOT,             K_COMM,            K_TRNS,            K_TRNS
    },

    /* -------------------------------------------------------------
     * LEFT HAND - LAYER 2: NUMBER / NAV (Number held)
     * ------------------------------------------------------------- */
    [L_NUM] = {
        // Row 0: -, 7, 8, 9, *
        K_MINS,            K_7,               K_8,               K_9,               MK(MOD_LSHIFT, K_8),
        // Row 1: +, 4, 5, 6, /
        MK(MOD_LSHIFT, K_EQL), K_4,         K_5,               K_6,               K_SLSH,
        // Row 2: 0, 1, 2, 3, .
        K_0,               K_1,               K_2,               K_3,               K_DOT,
        // Row 3: Trans
        K_TRNS,            K_TRNS,            K_TRNS,            K_TRNS,            K_TRNS
    },

    /* -------------------------------------------------------------
     * LEFT HAND - LAYER 3: SYMBOL (Symbol held)
     * ------------------------------------------------------------- */
    [L_SYM] = {
        // Row 0: ;, :, *, &, ?
        K_SCLN,            MK(MOD_LSHIFT, K_SCLN), MK(MOD_LSHIFT, K_8), MK(MOD_LSHIFT, K_7), MK(MOD_LSHIFT, K_SLSH),
        // Row 1: _, @, -, !, /
        MK(MOD_LSHIFT, K_MINS), MK(MOD_LSHIFT, K_2), K_MINS,     MK(MOD_LSHIFT, K_1), K_SLSH,
        // Row 2: {, [, (, <, "
        MK(MOD_LSHIFT, K_LBRC), K_LBRC,       MK(MOD_LSHIFT, K_9), MK(MOD_LSHIFT, K_COMM), MK(MOD_LSHIFT, K_QUOT),
        // Row 3: Trans
        K_TRNS,            K_TRNS,            K_TRNS,            K_TRNS,            K_TRNS
    },

    /* -------------------------------------------------------------
     * RIGHT HAND - LAYER 4: BASE (Horizontal Mirror)
     * ------------------------------------------------------------- */
    [R_BASE] = {
        // Row 0: F, A, R, W, P
        K_F,               K_A,               K_R,               K_W,               K_P,
        // Row 1: O, E, H, T, D
        K_O,               K_E,               K_H,               K_T,               K_D,
        // Row 2: U, I, N, S, Y
        K_U,               K_I,               K_N,               K_S,               K_Y,
        // Row 3: Space (Hold: Green), Number, Symbol, Enter, Shift
        HT(R_GREEN, K_SPC), MO(R_NUM),      MO(R_SYM),         K_ENT,           K_RSFT
    },

    /* -------------------------------------------------------------
     * RIGHT HAND - LAYER 5: GREEN (Space held)
     * ------------------------------------------------------------- */
    [R_GREEN] = {
        // Row 0: Tab, ', B, M, J
        K_TAB,             K_QUOT,            K_B,               K_M,               K_J,
        // Row 1: Q, Z, L, C, V
        K_Q,               K_Z,               K_L,               K_C,               K_V,
        // Row 2: Delete, Backspace, K, G, X
        K_DEL,             K_BSPC,            K_K,               K_G,               K_X,
        // Row 3: Trans, Trans, Comma, Period, Trans
        K_TRNS,            K_TRNS,            K_COMM,            K_DOT,             K_TRNS
    },

    /* -------------------------------------------------------------
     * RIGHT HAND - LAYER 6: NUMBER / NAV (Number held)
     * ------------------------------------------------------------- */
    [R_NUM] = {
        // Row 0: *, 9, 8, 7, -
        MK(MOD_LSHIFT, K_8), K_9,             K_8,               K_7,               K_MINS,
        // Row 1: /, 6, 5, 4, +
        K_SLSH,            K_6,               K_5,               K_4,               MK(MOD_LSHIFT, K_EQL),
        // Row 2: ., 3, 2, 1, 0
        K_DOT,             K_3,               K_2,               K_1,               K_0,
        // Row 3: Trans
        K_TRNS,            K_TRNS,            K_TRNS,            K_TRNS,            K_TRNS
    },

    /* -------------------------------------------------------------
     * RIGHT HAND - LAYER 7: SYMBOL (Symbol held)
     * ------------------------------------------------------------- */
    [R_SYM] = {
        // Row 0: ?, &, *, :, ;
        MK(MOD_LSHIFT, K_SLSH), MK(MOD_LSHIFT, K_7), MK(MOD_LSHIFT, K_8), MK(MOD_LSHIFT, K_SCLN), K_SCLN,
        // Row 1: /, !, -, @, _
        K_SLSH,            MK(MOD_LSHIFT, K_1), K_MINS,          MK(MOD_LSHIFT, K_2), MK(MOD_LSHIFT, K_MINS),
        // Row 2: ", <, (, [, {
        MK(MOD_LSHIFT, K_QUOT), MK(MOD_LSHIFT, K_COMM), MK(MOD_LSHIFT, K_9), K_LBRC, MK(MOD_LSHIFT, K_LBRC),
        // Row 3: Trans
        K_TRNS,            K_TRNS,            K_TRNS,            K_TRNS,            K_TRNS
    }
};
// clang-format on

const size_t keymap_layers = sizeof(keymap) / sizeof(keymap[0]);

const Macro keyboard_macros[] = {};
const uint8_t keyboard_macros_count = sizeof(keyboard_macros) / sizeof(keyboard_macros[0]);
#endif
#endif

#endif // CONFIG_H
