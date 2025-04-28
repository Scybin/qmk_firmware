#include QMK_KEYBOARD_H

// Override the keyboard-level OLED task
bool oled_task_kb(void) {
    return oled_task_user(); // Delegate to the user-defined OLED task
}

// Custom user-defined OLED task
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_ln("Master Side", false); // Display "Master Side" on the master half
    } else {
        oled_write_ln("Slave Side", false);  // Display "Slave Side" on the slave half
    }
    return true; // Indicate the task was handled
}
