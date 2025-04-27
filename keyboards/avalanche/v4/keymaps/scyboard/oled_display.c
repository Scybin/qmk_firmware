// oled_display.c
#include "oled_display.h"  // Include header for OLED logic
#include QMK_KEYBOARD_H

// Override the default oled_task_user to customize OLED behavior
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Clear the OLED display
        oled_clear();

        // Display "scyboard" at the top
        oled_write_P(PSTR("scyboard"), false);

        // Move to the second line
        oled_set_cursor(0, 1);

        // Get the current layer
        uint8_t current_layer = biton32(layer_state);

        // Display the layer name
        oled_write_P(PSTR("Layer: "), false);

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
    return false;  // Return false to indicate the OLED update was handled
}
