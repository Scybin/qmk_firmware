#include "oled.h"
#include QMK_KEYBOARD_H
#include <stdio.h>

// OLED setup for a 128x64 display
void oled_init(void) {
    // Initialize the OLED screen here
    oled_init_ports();
    oled_on();
    oled_clear();
}

void oled_task_user(void) {
    // Only run this function if the keyboard is the master
    if (is_keyboard_master()) {
        // Clear the display before rendering
        oled_clear();

        // Display the text "scyboard"
        oled_write_P(PSTR("scyboard"), false);

        // Optionally, you can add more information here (like layer or keypress data)
    }
}
