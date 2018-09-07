#include QMK_KEYBOARD_H

#include "time.h"

// Helpful defines
#define _______ KC_TRNS

#define FN_CAPS LT(1, KC_CAPS)
#define FN      MO(1)
#define RSFT_UP RSFT_T(KC_UP)

// Layers
#define L_QWERTY   0
#define L_FUNCTION 1
#define L_NUMBER   2

enum custom_keycodes
{
    KC_P00 = SAFE_RANGE,
    BLK_INC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi_split_rshift(
         KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0, KC_MINS,  KC_EQL, KC_BSPC,
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        FN_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,   KC_DOT, KC_SLSH,          RSFT_UP,      FN,
        KC_LCTL, KC_LALT, KC_LGUI,                             KC_SPC,                             KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT),
    [1] = LAYOUT_60_ansi_split_rshift(
         KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_HOME, KC_PGUP, KC_PGDN,  KC_END,  KC_PSCR, KC_SLCK, KC_PAUS,   RESET,
        _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_INS,   KC_NO,          _______,
        _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  BLK_INC,          _______, _______,
        _______, _______, _______,                            _______,                             _______, _______, _______,  _______),
    [2] = LAYOUT_60_ansi_split_rshift(
         KC_ESC,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_P7,   KC_P8,   KC_P9,  KC_PSLS,   KC_NO,   KC_NO, KC_BSPC,
        _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_P4,   KC_P5,   KC_P6,  KC_PAST,   KC_NO,   KC_NO,   KC_NO,
        _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,  KC_PMNS,   KC_NO,          KC_PENT,
        _______,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_P0,  KC_P00, KC_PDOT,  KC_PPLS,          _______, _______,
        _______, _______, _______,                            _______,                             _______, _______, _______, _______)};

// Backlight blinking
static uint32_t timer;
static bool blinking = false;
static int blink_seq = 0;
static int blink_effects[][100] = {
    [0] = {
        9,   // number of steps
        0,   // current step
        200, // interval
        1, 2, 3, 3, 3, 2, 2, 1, 1 // levels
    },
    [1] = {
        2,   // number of steps
        0,   // current step
        100, // interval
        0, 3 // levels
    },
    [2] = {
        9,   // number of steps
        0,   // current step
        200, // interval
        0, 3, 0, 0, 3, 0, 0, 0, 3 // levels
    },
    [3] = {
        6,   // number of steps
        0,   // current step
        100, // interval
        3, 2, 3, 1, 3, 0 // levels
    }
};

void enable_blinking(void)
{
    blinking = true;
    timer = timer_read32();
}

void disable_blinking(void)
{
    blinking = false;
    backlight_level(BACKLIGHT_LEVELS);
}

void blink_backlight(void)
{
    uint32_t now = timer_read32();
    if (now - timer > blink_effects[blink_seq][2])
    {
        timer = now;
        backlight_level(blink_effects[blink_seq][blink_effects[blink_seq][1]++ + 3]);
        blink_effects[blink_seq][1] %= blink_effects[blink_seq][0];
    }
}

void matrix_scan_user(void)
{
    if (blinking) blink_backlight();
}

// Update layer and set underglow
uint32_t layer_state_set_user(uint32_t state)
{
    switch (biton32(state))
    {
    case L_QWERTY:
        disable_blinking();
        backlight_level(BACKLIGHT_LEVELS);
        break;
    case L_FUNCTION:
        enable_blinking();
        break;
    case L_NUMBER:
        disable_blinking();
        backlight_level(0);
        break;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed)
    {
        switch (keycode)
        {
        case KC_P00:
            SEND_STRING("00");
            return false;
        case BLK_INC:
            blink_seq++;
            blink_seq %= sizeof (blink_effects) / sizeof(blink_effects[0]);
            return false;
        }
    }
    return true;
};
