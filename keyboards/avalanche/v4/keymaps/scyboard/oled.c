#include "oled.h"
#include QMK_KEYBOARD_H
#include <stdio.h>
#include <drivers/oled/oled_driver.h>

// Initialize the OLED screen
bool oled_init(oled_rotation_t rotation) {
    oled_init_ports();
    oled_on();
    oled_clear();
    return true;  // Return true to indicate successful initialization
}

// OLED task to display "scyboard"
bool oled_task_user(void) {
    // Only run this function if the keyboard is the master
    if (is_keyboard_master()) {
        // Clear the display before rendering
        oled_clear();

        // Display the text "scyboard"
        oled_write_P(PSTR("scyboard"), false);

        // Optionally, you can add more information here (like layer or keypress data)
    }

    return true;  // Return true to indicate successful execution
}
