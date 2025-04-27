#include QMK_KEYBOARD_H

// Custom macros
enum custom_macros {
    M_0,
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
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_P,    KC_O,    KC_I,    KC_U,    KC_Y,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, FN_MO13,  KC_SPC,     KC_ENT, FN_MO23, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      MACRO(M_5),    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                   KC_0,    KC_9,    KC_8,    KC_7,    KC_6,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, RGB_TOG, RGB_HUD, RGB_HUI, RGB_RMOD, RGB_MOD,                      KC_HOME,  KC_DEL, KC_TRNS, KC_TRNS,   KC_UP, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_CAPS, RGB_SAD, RGB_SAI, RGB_SPD, RGB_SPI,                      KC_END,   KC_INS, KC_TRNS, KC_RGHT, KC_DOWN, KC_LEFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_TRNS,  KC_SPC,     KC_ENT,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                      S(KC_0), S(KC_9), S(KC_8), S(KC_7), S(KC_6),  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_TRNS, MACRO(M_10), KC_TRNS, MACRO(M_1), MACRO(M_7), KC_GRV,  KC_BSLS, KC_RBRC, KC_LBRC,  KC_EQL, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_TRNS, MACRO(M_9), MACRO(M_8), MACRO(M_6), MACRO(M_0), S(KC_GRV), S(KC_BSLS), S(KC_RBRC), S(KC_LBRC), S(KC_EQL), S(KC_MINS),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_TRNS,  KC_SPC,     KC_ENT, KC_RALT, KC_TRNS
                                      //`--------------------------'  `--------------------------'
  ),

    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F10,   KC_F9,   KC_F8,   KC_F7,   KC_F6,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LSFT,   KC_NO,    KC_W,   KC_NO,   KC_NO,                      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LCTL,    KC_A,    KC_S,    KC_D,   KC_NO,                      KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_TRNS,  KC_SPC,     KC_ENT, DF(0),   KC_NO
                                      //`--------------------------'  `--------------------------'
  )
};

// Macro handling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_0:
            if (record->event.pressed) {
                SEND_STRING("SandyCory" SS_TAP(X_P5) SS_TAP(X_P7) SS_TAP(X_P9));
            }
            break;
        case M_1:
            if (record->event.pressed) {
                SEND_STRING("4319");
            }
            break;
        case M_2:
            if (record->event.pressed) {
                SEND_STRING("1628");
            }
            break;
        case M_3:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("c"));
            }
            break;
        case M_4:
            if (record->event.pressed) {
                SEND_STRING(SS_LSFT(SS_LCTL("v")));
            }
            break;
        case M_5:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL("x"));
            }
            break;
        case M_6:
            if (record->event.pressed) {
                SEND_STRING("ahoughton");
            }
            break;
        case M_7:
            if (record->event.pressed) {
                SEND_STRING("CorySandy866");
            }
            break;
        case M_8:
            if (record->event.pressed) {
                SEND_STRING("Synapse" SS_TAP(X_P4) "$");
            }
            break;
        case M_9:
            if (record->event.pressed) {
                SEND_STRING("texas\ahoughton");
            }
            break;
        case M_10:
            if (record->event.pressed) {
                SEND_STRING("ahoughton@envisionradiology.com");
            }
            break;
    }
    return true;
}
