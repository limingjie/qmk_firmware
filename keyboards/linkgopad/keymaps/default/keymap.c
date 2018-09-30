#include QMK_KEYBOARD_H

#define PAD      0
#define FUNCTION 1

// Readability keycodes
#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [PAD] = pad_5x5(
        KC_HOME, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS,
        KC_PGUP, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS,
        KC_PGDN, KC_KP_1, KC_KP_2, KC_KP_3, KC_PSLS,
        KC_END,  KC_KP_0, KC_UP,   KC_PDOT, KC_PAST,
        MO(1),   KC_LEFT, KC_DOWN, KC_RGHT, KC_PENT),
    [FUNCTION] = pad_5x5(
        KC_ESC,   _______, _______, _______, KC_BSPC,
        RGB_MOD,  _______, _______, _______, _______,
        RGB_RMOD, _______, _______, _______, _______,
        RGB_TOG,  _______, _______, KC_COMM, _______,
        _______,  _______, KC_SPC,  _______, RESET)
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch (id)
    {
    case 0:
        if (record->event.pressed)
        {
            register_code(KC_RSFT);
        }
        else
        {
            unregister_code(KC_RSFT);
        }
        break;
    }
    return MACRO_NONE;
};

void matrix_init_user(void)
{
}

void matrix_scan_user(void)
{
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    return true;
}

void led_set_user(uint8_t usb_led)
{
}
