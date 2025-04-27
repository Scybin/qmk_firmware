#include QMK_KEYBOARD_H

bool oled_task_user(void) {
    // Custom OLED logic
    if (is_keyboard_master()) {
        oled_clear();
        oled_write_P(PSTR("sycboard\n"), false);
        oled_set_cursor(0, 2);

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
            case 4:
                oled_write_P(PSTR("LOWER"), false);
                break;
            case 5:
                oled_write_P(PSTR("UPPER"), false);
                break;
        }

        // Move cursor two rows below the "Layer" text
        oled_set_cursor(0, 4);

        // Iterate through the matrix to find a pressed key
        bool key_found = false;
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                if (matrix_is_on(row, col)) {
                    key_found = true;

                    // Display the row and column of the pressed key
                    char keycode_str[16];
                    snprintf(keycode_str, sizeof(keycode_str), "Row: %d Col: %d", row, col);
                    oled_write(keycode_str, false);

                    break; // Exit inner loop
                }
            }
            if (key_found) {
                break; // Exit outer loop
            }
        }

        // If no key is pressed, display "KC: None"
        if (!key_found) {
            oled_write_P(PSTR("KC: None"), false);
        }
    } else {
        // Slave OLED display
        oled_clear();
        oled_write_P(PSTR("Slave OLED\n"), false);
    }

    return false; // Return false to prevent fallback to default logic
}
