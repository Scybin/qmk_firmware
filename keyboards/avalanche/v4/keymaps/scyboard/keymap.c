// Copyright 2025 Andrew Houghton (@Scybin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "oled.h"

// OLED logic
#ifndef OLED_TASK_KB_OVERRIDE
bool oled_task_kb(void) {
    return oled_task_user();
}
#endif

// Sleep/Wakeup logic
void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        suspend_wakeup_init();
    }
    return true;
}

// Name layers
enum layer {
    BASE,
    LIGHT,
    DEV,
    OSRS,
    LOWER,
    UPPER,
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
                   KC_ESC,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                             KC_6,      KC_7,    KC_8,     KC_9,    KC_0,    KC_MINS,
                   KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                             KC_Y,      KC_U,    KC_I,     KC_O,    KC_P,    KC_LBRC,
        TD(LOSRS), KC_LCTL,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                             KC_H,      KC_J,    KC_K,     KC_L,    KC_SCLN, KC_QUOT, KC_RBRC,
                   TD(SHIFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,      TD(LLIGHT), XXXXXXX, XXXXXXX, KC_RALT, KC_N,      KC_M,    KC_COMM,  KC_DOT,  KC_SLSH, KC_BSLS,
                                                     EE_CLR,  XXXXXXX, MO(LOWER), KC_SPC,     KC_LWIN, KC_ENT,  KC_BSPC, MO(UPPER), XXXXXXX, DF(OSRS)
    ),                                                                                                                                             
    [LIGHT] = LAYOUT(                                                                                                                              
                   XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, UG_VALD, UG_VALU,                                          XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
                   XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, UG_SATD, UG_SATU,                                          XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,   XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, UG_HUED, UG_HUEU,                                          XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                   XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, UG_PREV, UG_NEXT,   TD(LBASE),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
                                                     XXXXXXX, UG_SPDD, UG_SPDU,   RGB_TOG,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX   
    ),                                                                                                                                                 
    [DEV] = LAYOUT(                                                                                                                                    
                   _______,        _______, _______, _______, _______, _______,                                          _______,   _______, _______,  _______, _______, _______,
                   _______,        _______, _______, _______, _______, _______,                                          _______,   _______, _______,  _______, _______, _______,
        _______,   _______,        _______, _______, _______, _______, _______,                                          _______,   _______, _______,  _______, _______, _______, _______,
                   _______,        _______, _______, _______, _______, _______,   _______,    _______, _______, _______, _______,   _______, _______,  _______, _______, _______,
                                                     _______, _______, _______,   _______,    _______, _______, _______, _______,   _______, _______   
    ),                                                                                                                                                 
    [OSRS] = LAYOUT(                                                                                                                                   
                   _______,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                          XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
                   XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                          XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
        TD(LBASE), KC_ESC,         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                            KC_F6,     KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,  XXXXXXX,
                   KC_LCTL,        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   RGB_TOG,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
                                                     XXXXXXX, XXXXXXX, XXXXXXX,   _______,    XXXXXXX, _______, _______, KC_BSPC,   XXXXXXX, DF(BASE) 
    ),                                                                                                                                                 
    [LOWER] = LAYOUT(                                                                                                                                  
                   KC_F12,         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                            KC_F6,     KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,
                   _______,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                             KC_6,      KC_7,    KC_8,     KC_9,    KC_0,    KC_BSPC,
        _______,   _______,        _______, _______, _______, _______, _______,                                          _______,   KC_UP,   _______,  _______, KC_DEL,  KC_HOME, KC_ESC,
                   _______,        _______, _______, _______, _______, _______,   _______,    _______, _______, _______, KC_LEFT,   KC_DOWN, KC_RIGHT, _______, KC_INS,  KC_END,
                                                     _______, _______, _______,   _______,    _______, _______, _______, _______,   _______, _______   
    ),                                                                                                                                                 
    [UPPER] = LAYOUT(                                                                                                                                  
                   KC_F12,         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                            KC_F6,     KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,
                   KC_TILD,        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                          KC_CIRC,   KC_AMPR, KC_ASTR,  KC_LPRN, KC_RPRN, KC_BSPC,
        _______,   _______,        _______, _______, _______, _______, _______,                                          KC_MINS,   KC_EQL,  KC_LBRC,  KC_RBRC, KC_BSLS, KC_GRV,  _______,
                   _______,        _______, _______, _______, _______, _______,   _______,    _______, _______, _______, KC_UNDS,   KC_PLUS, KC_LCBR,  KC_RCBR, KC_PIPE, _______,
                                                     _______, _______, _______,   _______,    _______, _______, _______, _______,   _______, _______
    ),                                                                            
};
