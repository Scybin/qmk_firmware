// Copyright 2025 Andrew Houghton (@Scybin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Layers
enum layer {
    BASE,
    LIGHT,
    DEV,
    OSRS,
};

// Tap Dance function declarations and definitions
enum {
    TD_SHIFT_CAPS = 1,
    TD_LOSRS,
    TD_LBASE,
};

void dance_layer1_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_LALT);  // Sends Left Alt on single tap
    } else if (state->count == 2) {
        layer_clear();       // Clear all layers
        layer_on(3);         // Turn on Layer OSRS
    }
}

void dance_layer1_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        // Reset when the key is released
    }
}

void dance_layer2_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_LALT);  // Sends Left Alt on single tap
    } else if (state->count == 2) {
        layer_clear();       // Clear all layers
        layer_on(0);         // Turn on Layer BASE
    }
}

void dance_layer2_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 2) {
        // Reset when the key is released
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_LOSRS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layer1_finished, dance_layer1_reset),
    [TD_LBASE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_layer2_finished, dance_layer2_reset),
};

// Layer keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
                         KC_ESC,            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
                         KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        TD(TD_LOSRS),    KC_LCTL,           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_RBRC,
                         TD(TD_SHIFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    DF(LIGHT), KC_UP,   KC_DEL,  KC_RALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                                              KC_LEFT, KC_RGHT, KC_LWIN, KC_SPC,    KC_DOWN, KC_INS,  KC_ENT,  KC_BSPC, KC_HOME, KC_END
    ),                                                                                          
    [LIGHT] = LAYOUT(                                                                             
                         XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, UG_VALD, UG_VALU,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                         XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, UG_SATD, UG_SATU,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,         XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, UG_HUED, UG_HUEU,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                         XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, UG_PREV, UG_NEXT, DF(BASE),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                              XXXXXXX, UG_SPDD, UG_SPDU, RGB_TOG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),                                                                                          
    [DEV] = LAYOUT(                                                                             
                         _______,           _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
                         _______,           _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______,
        _______,         _______,           _______, _______, _______, _______, _______,                                       _______, _______, _______, _______, _______, _______, _______,
                         _______,           _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                                              _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______
    ),                                                                                          
    [OSRS] = LAYOUT(                                                                            
                         KC_ESC,            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                         KC_TAB,            KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        TD(TD_LBASE),    KC_LCTL,           KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSPC,
                         TD(TD_SHIFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    RGB_TOG,   KC_UP,   KC_DEL,  KC_RALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                                                              KC_BTN1, KC_LCTL, KC_LSFT, KC_SPC,    XXXXXXX, XXXXXXX, KC_ENT,  KC_BSPC, XXXXXXX, XXXXXXX
    ),
};

// RGB Settings
void matrix_init_user(void) {
    rgblight_init();                             // Initialize RGB lighting
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);   // Set to static light mode
    rgblight_sethsv(170, 255, 255);              // Set color to blue (hue=170, max saturation, max value)
}

// Modify the existing `oled_task_user` function
bool oled_task_user(void) {
    // Only display something on the OLED if it's available and the keyboard is the master
    if (is_keyboard_master()) {
        // Clear the OLED display
        oled_clear();

        // Display the word "scyboard" at the top
        oled_write_P(PSTR("scyboard"), false);

        // Add a small delay to make sure the text is visible before updating the next line
        oled_set_cursor(0, 1);  // Move cursor to the next line

        // Get the current layer and display it
        uint8_t current_layer = biton32(layer_state);  // Get the active layer

        // Display "Layer: " text
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

        }
    }

    return false;  // Return false to indicate that the OLED update was handled successfully
}
