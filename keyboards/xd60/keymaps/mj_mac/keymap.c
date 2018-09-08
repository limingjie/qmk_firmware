 #include QMK_KEYBOARD_H

// Helpful Defines
#define _______    KC_TRNS
#define XXXXXXX    KC_NO
#define FN_CAPS    LT(1, KC_CAPS)

// Mac Keyboard Shorts
#define SCR2DSK    LSFT(LGUI(KC_3))        // Take screenshot and save to desktop
#define SCR2CLP    LCTL(LSFT(LGUI(KC_4)))  // Take screenshot of selected area to clipboard
#define FINDER     LALT(LGUI(KC_SPACE))    // Open finder (Fn + E simulates Win + E)
#define FULLSCR    LCTL(LGUI(KC_F))        // Toggle full screen
#define LOCKSCR    LCTL(LGUI(KC_Q))        // Lock screen (Fn + L simulates Win + L)

// Layers
#define L_QWERTY   0
#define L_FUNCTION 1

// Status Variables
static uint8_t layer = L_QWERTY;
static uint8_t caps  = 0;

// Used to check underglow status
extern rgblight_config_t rgblight_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // QWERTY Layer
    [0] = LAYOUT_all(
          KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,  KC_EQL,  KC_GRV, KC_BSPC,
          KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC,          KC_BSLS,
         FN_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, XXXXXXX,           KC_ENT,
         KC_LSPO, XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX, KC_RSPC,   MO(1),
         KC_LCTL, KC_LALT, KC_LGUI,                             KC_SPC,                            KC_RGUI, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT),
    // Function Lay
    [1] = LAYOUT_all(
        KC_POWER,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______,  KC_DEL,
         _______, _______, SCR2DSK, _______, _______, _______, KC_PGUP, KC_HOME,   KC_UP,  KC_END, KC_MPLY, KC_MRWD, KC_MFFD,            RESET,
         _______,   KC_F4, SCR2CLP,  KC_F11, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_F14,  KC_F15, XXXXXXX,          _______,
         _______, XXXXXXX, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_BTN1, XXXXXXX, KC_BTN2, _______,
         _______, _______, _______,                            _______,                            _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R)
};

// Set underglow color base on caps lock state and layer
// Use _noeeprom methods to prevent underglow from enabling on restart.
// Color predefinitions in /quantum/rgblight_list.h
void set_underglow(void)
{
    if (layer == L_QWERTY && caps == 0)
    {
        rgblight_disable_noeeprom();
        return;
    }

    if (!rgblight_config.enable)
        rgblight_enable_noeeprom();
    if (rgblight_config.mode != 1)
        rgblight_mode_noeeprom(1);

    switch (layer)
    {
    case L_QWERTY:
        if (caps == 0)
        {
            // rgblight_disable_noeeprom();
        }
        else
        {
            rgblight_sethsv_noeeprom_coral();
        }
        break;
    case L_FUNCTION:
        if (caps == 0)
        {
            rgblight_sethsv_noeeprom_turquoise();
        }
        else
        {
            rgblight_sethsv_noeeprom_magenta();
        }
        break;
    default:
        rgblight_disable_noeeprom();
        break;
    }
}

void matrix_init_user(void)
{
    // cannot close rgb here...
    rgblight_enable_noeeprom();
    rgblight_setrgb(0x00, 0x00, 0x00);
    rgblight_disable_noeeprom();
}

// Update layer and set underglow
uint32_t layer_state_set_user(uint32_t state)
{
    int new_layer = biton32(state);
    if (layer != new_layer)
    {
        layer = new_layer;
        set_underglow();
    }
    return state;
}

// Update caps lock status and set underglow
void led_set_user(uint8_t usb_led)
{
    int new_caps = usb_led & (1 << USB_LED_CAPS_LOCK);
    if (caps != new_caps)
    {
        caps = new_caps;
        set_underglow();
    }
}
