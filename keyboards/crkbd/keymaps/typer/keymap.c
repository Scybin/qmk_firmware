#include QMK_KEYBOARD_H

enum custom_keycodes {
    BSPC_ENT = SAFE_RANGE,
};

enum custom_macros {
    M_0 = SAFE_RANGE + 1,
    M_1,
    M_2,
    M_3,
    M_4,
    M_5,
    M_6,
    M_7,
    M_8,
    M_9,
    M_10
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,  KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,  MO(1),  KC_SPC,    BSPC_ENT, MO(2),   DF(3)
                                      //`--------------------------'  `--------------------------'
  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       M_5,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      M_3,    RGB_TOG, RGB_HUD, RGB_HUI, RGB_RMOD, RGB_MOD,                     KC_TRNS,  KC_UP,  KC_TRNS, KC_TRNS, KC_DEL,  KC_HOME,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      M_4,     KC_CAPS, RGB_SAD, RGB_SAI, RGB_SPD, RGB_SPI,                     KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_INS, KC_END,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LALT, KC_TRNS,  KC_SPC,    BSPC_ENT, MO(3),  KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB, KC_EXLM,  KC_AT,  KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_TRNS,  M_10,   KC_TRNS,  M_1,     M_7,                        KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_TRNS,  M_9,     M_8,     M_6,     M_0,                        KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_TRNS,  KC_SPC,   BSPC_ENT, KC_RALT, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LSFT,  KC_NO,    KC_W,   KC_NO,   KC_NO,                       KC_NO,    KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LCTL,  KC_A,    KC_S,    KC_D,   KC_NO,                        KC_NO,    KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_NO,   KC_SPC,    BSPC_ENT, KC_NO,   DF(0)
                                      //`--------------------------'  `--------------------------'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BSPC_ENT:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code(KC_ENT);
                } else {
                    tap_code(KC_BSPC);
                }
            }
            return false; // Skip further processing for this key

        case M_0:
            if (record->event.pressed) {
                SEND_STRING("SandyCory" SS_TAP(X_P5) SS_TAP(X_P7) SS_TAP(X_P9));
            }
            return false;

        case M_1:
            if (record->event.pressed) {
                SEND_STRING("4319");
            }
            return false;

        case M_2:
            if (record->event.pressed) {
                SEND_STRING("1628");
            }
            return false;

        case M_3:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c"));
            }
            return false;

        case M_4:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_LCTL("v")));
            }
            return false;

        case M_5:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x"));
            }
            return false;

        case M_6:
            if (record->event.pressed) {
                SEND_STRING("ahoughton");
            }
            return false;

        case M_7:
            if (record->event.pressed) {
                SEND_STRING("CorySandy866");
            }
            return false;

        case M_8:
            if (record->event.pressed) {
                SEND_STRING("Synapse" SS_TAP(X_P4) "$");
            }
            return false;

        case M_9:
            if (record->event.pressed) {
                SEND_STRING("texas\ahoughton");
            }
            return false;

        case M_10:
            if (record->event.pressed) {
                SEND_STRING("ahoughton@envisionradiology.com");
            }
            return false;

        default:
            return true; // Allow further processing for all other keycodes
    }
}
