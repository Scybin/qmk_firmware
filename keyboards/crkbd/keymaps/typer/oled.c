#include QMK_KEYBOARD_H

static uint32_t autocorrect_count = 0;

bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    autocorrect_count++;
    return true;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        if (autocorrect_is_enabled()) {
            oled_write_ln("Autocorrect: ON", false);
        } else {
            oled_write_ln("Autocorrect: OFF", false);
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), "Count: %lu", autocorrect_count);
        oled_write_ln(buffer, false);
    } else {
        oled_write_ln("Slave Side", false);
    }
    return false;
}
