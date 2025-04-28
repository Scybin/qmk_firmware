#include QMK_KEYBOARD_H

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_ln("Custom Master", false); // Custom message for the master side
    } else {
        oled_write_ln("Custom Slave", false);  // Custom message for the slave side
    }
    return false; // Indicate no further processing is needed
}
