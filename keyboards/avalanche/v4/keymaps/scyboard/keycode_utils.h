#ifndef KEYCODE_UTILS_H
#define KEYCODE_UTILS_H

#include QMK_KEYBOARD_H

// Declare enums as extern to reference them from keymap.c
extern enum layer {
    BASE,
    LIGHT,
    DEV,
    OSRS,
    LOWER,
    UPPER,
};

extern enum tap_dance {
    SHIFT_CAPS = 1,
    LOSRS,
    LBASE,
    LLIGHT,
};

const char* get_keycode_name(uint16_t keycode);

#endif
