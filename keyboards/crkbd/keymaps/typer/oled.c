#include QMK_KEYBOARD_H

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_ln("Master Side", false);
    } else {
        oled_write_ln("Slave Side", false);
    }
    return true; // Indicate the task was handled
}
