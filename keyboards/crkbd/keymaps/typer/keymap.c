#include QMK_KEYBOARD_H
#include "oled.h"

enum custom_keycodes {
    BSPC_ENT = SAFE_RANGE,
    CTRL_X,
    CTRL_C,
    LCTL_LSFT_V,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,   KC_M,   KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,  MO(1),  KC_SPC,    BSPC_ENT, MO(2),  AC_TOGG
                                      //`--------------------------'  `--------------------------'
  ),

    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      CTRL_X,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CTRL_C, RGB_TOG, RGB_HUD, RGB_HUI, RGB_RMOD, RGB_MOD,                     KC_TRNS,  KC_UP,  KC_TRNS, KC_TRNS, KC_DEL,  KC_HOME,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   LCTL_LSFT_V, KC_CAPS, RGB_SAD, RGB_SAI, RGB_SPD, RGB_SPI,                    KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_INS, KC_END,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LALT, KC_TRNS, KC_SPC,      KC_ENT,  MO(3),  EE_CLR
                                      //`--------------------------'  `--------------------------'
  ),

    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB, KC_EXLM,  KC_AT,  KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_TRNS,  KC_SPC,   KC_ENT, KC_RALT, KC_TRNS
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
            return false;

        case CTRL_X:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL)); // Hold CTRL
                tap_code(KC_X);                 // Tap X
                unregister_mods(MOD_BIT(KC_LCTL)); // Release CTRL
            }
            return false;

        case CTRL_C:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL)); // Hold CTRL
                tap_code(KC_C);                 // Tap C
                unregister_mods(MOD_BIT(KC_LCTL)); // Release CTRL
            }
            return false;

        case LCTL_LSFT_V:
            if (record->event.pressed) {
                register_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)); // Hold CTRL+SHIFT
                tap_code(KC_V);                                    // Tap V
                unregister_mods(MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)); // Release CTRL+SHIFT
            }
            return false;

        default:
            return true;
    }
}

void keyboard_post_init_user(void) {
   rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
   rgb_matrix_sethsv(170, 255, 255);

    autocorrect_enable();
}
