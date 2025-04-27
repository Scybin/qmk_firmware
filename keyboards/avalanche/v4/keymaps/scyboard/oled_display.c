#include "oled_display.h"  // Include header for OLED logic
#include QMK_KEYBOARD_H

// Define the oled_task_user function to show custom content on the OLED display
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Clear the OLED display to refresh it
        oled_clear();

        // Display "scyboard" at the top (in the first row)
        oled_write_P(PSTR("scyboard"), false);

        // Move to the second line of the OLED
        oled_set_cursor(0, 1); 

        // Get the current active layer using biton32
        uint8_t current_layer = biton32(layer_state);

        // Display the layer name based on the current layer
        oled_write_P(PSTR("Layer: "), false);  // Display the text "Layer: "

        // Custom mapping of layers to their names
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
