#include QMK_KEYBOARD_H

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Master OLED display
        oled_clear();

        oled_write_P(PSTR("scyboard"), false);

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
        }
    } else {
        // Slave OLED display
        oled_clear();

        oled_set_cursor(0, 0);
        oled_write_P(PSTR("test"), false);
    }

    return false;
}
