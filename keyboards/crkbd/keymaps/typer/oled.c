#include QMK_KEYBOARD_H

#ifdef OLED_TASK_KB_OVERRIDE
bool oled_task_kb(void) {
    return oled_task_user();
}
#endif

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_ln("Master Side", false);
    } else {
        oled_write_ln("Slave Side", false);
    }
    return true;
}
