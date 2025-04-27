#include QMK_KEYBOARD_H

// Bitmap for "scyboard" (example for a 128x32 OLED screen)
static const char PROGMEM scyboard_logo[] = {
    0xFF, 0x81, 0xBD, 0xA5, 0xA5, 0xBD, 0x81, 0xFF,
    0xFF, 0x81, 0xBD, 0xA5, 0xA5, 0xBD, 0x81, 0xFF,
    0xFF, 0x81, 0xBD, 0xA5, 0xA5, 0xBD, 0x81, 0xFF,
    0xFF, 0x81, 0xBD, 0xA5, 0xA5, 0xBD, 0x81, 0xFF
};

bool oled_task_user(void) {
    // Static variables to store the last pressed key's information
    static uint8_t last_row = 0;
    static uint8_t last_col = 0;
    static uint16_t last_keycode = 0;
    static bool key_pressed = false;

    // Custom OLED logic
    if (is_keyboard_master()) {
        oled_clear();

        uint8_t current_layer = biton32(layer_state);

        // Display the current layer at the top row
        oled_set_cursor(0, 0);
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

        // Move cursor one row below the "Layer" text
        oled_set_cursor(0, 2);

        // Iterate through the matrix to find a pressed key
        bool current_key_found = false;
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                if (matrix_is_on(row, col)) {
                    current_key_found = true;

                    // Update the last pressed key's information
                    last_row = row;
                    last_col = col;
                    last_keycode = keymap_key_to_keycode(current_layer, (keypos_t){.row = row, .col = col});
                    key_pressed = true;

                    break; // Exit inner loop
                }
            }
            if (current_key_found) {
                break; // Exit outer loop
            }
        }

        // Display row and column
        if (key_pressed) {
            char row_col_str[16];
            snprintf(row_col_str, sizeof(row_col_str), "Row: %d Col: %d", last_row, last_col);
            oled_write(row_col_str, false);
        } else {
            oled_write_P(PSTR("Row: None Col: None"), false);
        }

        // Move cursor one row below the row and column display
        oled_set_cursor(0, 4);

        // Display the keycode
        if (key_pressed) {
            char keycode_str[16];
            snprintf(keycode_str, sizeof(keycode_str), "KC: 0x%X", last_keycode);
            oled_write(keycode_str, false);
        } else {
            oled_write_P(PSTR("KC: None"), false);
        }
    } else {
        // Slave OLED display
        oled_clear();
        oled_write_raw_P(scyboard_logo, sizeof(scyboard_logo));
    }

    return false; // Return false to prevent fallback to default logic
}
