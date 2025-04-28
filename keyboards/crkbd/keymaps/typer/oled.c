#include QMK_KEYBOARD_H

// Override the parent implementation of oled_task_kb
bool oled_task_kb(void) {
    return oled_task_user(); // Use your custom user-defined OLED task
}

// Custom user-defined OLED task
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_ln("Master Side", false);
    } else {
        oled_write_ln("Slave Side", false);
    }
    return true;
}

// Optional: Override other parent functions if needed
void oled_render_layer_state(void) {
    oled_write_ln("Custom Layer State", false);
}

void oled_render_logo(void) {
    oled_write_ln("Custom Logo", false);
}
