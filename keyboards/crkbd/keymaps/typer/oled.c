#include QMK_KEYBOARD_H

bool oled_task_kb(void) {
    if (is_keyboard_master()) {
        oled_write_ln("TEST MASTER", false); // Display "TEST MASTER" on the master side
    } else {
        oled_write_ln("TEST SLAVE", false);  // Display "TEST SLAVE" on the slave side
    }
    return false; // Indicate no further processing is needed
}
