#include QMK_KEYBOARD_H

#define PAD 0

// Readability keycodes
#define _______ KC_TRNS

enum custom_keycodes
{
    KC_RED = SAFE_RANGE,
    KC_GREEN,
    KC_YELLOW
};

// Used to check underglow status
extern rgblight_config_t rgblight_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [PAD] = pad_5x5(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        KC_RED,  RESET,   KC_GREEN, _______, KC_YELLOW,
        RGB_M_B, RGB_M_R, RGB_M_SN, RGB_M_X, RGB_M_T)
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
    if (!rgblight_config.enable)
    {
        rgblight_enable_noeeprom();
    }

    if (record->event.pressed)
    {
        switch (keycode)
        {
        case KC_RED:
            rgblight_sethsv_noeeprom_red();
            rgblight_mode_noeeprom(1);
            return false;
        case KC_GREEN:
            rgblight_sethsv_noeeprom_green();
            rgblight_mode_noeeprom(1);
            return false;
        case KC_YELLOW:
            rgblight_sethsv_noeeprom_yellow();
            rgblight_mode_noeeprom(1);
            return false;
        }
    }
    return true;
}

void led_set_user(uint8_t usb_led)
{
}
