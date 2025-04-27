#include QMK_KEYBOARD_H

bool oled_task_kb(void) {
    // Use your custom OLED logic
    if (is_keyboard_master()) {
        oled_clear();
        oled_write_P(PSTR("sycboard\n"), false);
        oled_set_cursor(0, 1);

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
    } else {
        // Slave OLED display
        oled_clear();
        oled_write_P(PSTR("Slave OLED\n"), false);
    }

    return false; // Return false to prevent fallback to default logic
}
