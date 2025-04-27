// Copyright 2025 Andrew Houghton (@Scybin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Name layers
enum layer {
    BASE,
    LIGHT,
    DEV,
    OSRS,
};

// Tap Dance function declarations and definitions
enum {
    SHIFT_CAPS = 1,
    LOSRS,
    LBASE,
    LLIGHT,
};

void dance_layer1_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_LALT);
    } else if (state->count == 2) {
        layer_clear();
        layer_on(3);         // Turn on Layer OSRS
    }
}

void dance_layer1_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
 
    }
}

void dance_layer2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_LALT);
    } else if (state->count == 2) {
        layer_clear();
        layer_on(0);         // Turn on Layer BASE
    }
}

void dance_layer2_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
     
    }
}

void dance_layer3_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        rgblight_toggle();
    } else if (state->count == 2) {
        layer_clear();
        layer_on(1);         // Turn on Layer LIGHT
    }
}

void dance_layer3_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
     
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [LOSRS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layer1_finished, dance_layer1_reset),
    [LBASE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layer2_finished, dance_layer2_reset),
    [LLIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layer3_finished, dance_layer3_reset),
};

// Layer keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
                   KC_ESC,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
                   KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        TD(LOSRS), KC_LCTL,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_RBRC,
                   TD(SHIFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    TD(LLIGHT), KC_UP,   KC_DEL,  KC_RALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                                              KC_LEFT, KC_RGHT, KC_LWIN,    KC_SPC,  KC_DOWN, KC_INS,  KC_ENT,  KC_BSPC, KC_HOME, KC_END
    ),                                                                                          
    [LIGHT] = LAYOUT(                                                                             
                   XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, UG_VALD, UG_VALU,                                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                   XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, UG_SATD, UG_SATU,                                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,   XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, UG_HUED, UG_HUEU,                                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                   XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, UG_PREV, UG_NEXT, TD(LBASE),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                     XXXXXXX, UG_SPDD, UG_SPDU, RGB_TOG,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),                                                                                        
    [DEV] = LAYOUT(                                                                           
                   _______,        _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
                   _______,        _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
        _______,   _______,        _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______, _______,
                   _______,        _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                     _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______
    ),                                                                                        
    [OSRS] = LAYOUT(                                                                          
                   KC_ESC,         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                   KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        TD(LBASE), KC_LCTL,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSPC,
                   TD(SHIFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    RGB_TOG,    KC_UP,   KC_DEL,  KC_RALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                                              KC_BTN1, KC_LCTL, KC_LSFT,    KC_SPC,  XXXXXXX, XXXXXXX, KC_ENT,  KC_BSPC, XXXXXXX, XXXXXXX
    ),
};

// RGB Settings
void matrix_init_user(void) {
    rgblight_init();
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv(170, 255, 255);              // Set color to blue (hue, sat, val)
}

// Custom OLED task
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_clear();

        oled_write_P(PSTR("scyboard"), false);

        oled_set_cursor(0, 1);

        uint8_t current_layer = biton32(layer_state);

        oled_write_P(PSTR("Layer: "), false);

        // Map the current layer to its name
        switch (current_layer) {
            case 0:
                oled_write_P(PSTR("BASE"), false);
                break;
            case 1:
                oled_write_P(PSTR("LIGHT"), false);
                break;
            case 2:
                oled_write_P(PSTR("DEV"), false);
                break;
            case 3:
                oled_write_P(PSTR("OSRS"), false);
                break;
        }
    }

    return false;
}
