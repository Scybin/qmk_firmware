#include QMK_KEYBOARD_H

const char* get_keycode_name(uint16_t keycode) {
    switch (keycode) {
        case KC_SPC: return "KC_SPC";
        case KC_TAB: return "KC_TAB";
        case KC_ESC: return "KC_ESC";
        case KC_BSPC: return "KC_BSPC";
        case KC_ENT: return "KC_ENT";
        case KC_LCTL: return "KC_LCTL";
        case KC_LSFT: return "KC_LSFT";
        case KC_LALT: return "KC_LALT";
        case KC_LGUI: return "KC_LGUI";
        case KC_RALT: return "KC_RALT";
        case KC_UP: return "KC_UP";
        case KC_DOWN: return "KC_DOWN";
        case KC_LEFT: return "KC_LEFT";
        case KC_RIGHT: return "KC_RIGHT";
        // Add more keycodes as needed
        default: return "UNKNOWN";
    }
}
