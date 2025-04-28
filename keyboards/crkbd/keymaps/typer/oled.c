#include QMK_KEYBOARD_H

// Function prototypes
void oled_render_layer_state(void);
void oled_render_keylog(void);
void oled_render_logo(void);

bool oled_task_kb(void) {
    // Call the user-defined OLED task
    if (!oled_task_user()) {
        return false;
    }

    // Master-side rendering
    if (is_keyboard_master()) {
        oled_render_layer_state(); // Custom layer state rendering
        oled_render_keylog();      // Custom keylog rendering
    } else {
        oled_render_logo();        // Custom logo rendering
    }

    return false; // Return false to indicate no further processing is needed
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

// Custom rendering for layer state
void oled_render_layer_state(void) {
    oled_write_ln("Custom Layer State", false);
}

// Custom rendering for logo
void oled_render_logo(void) {
    oled_write_ln("Custom Logo", false);
}

// Optional: Custom rendering for keylog
void oled_render_keylog(void) {
    oled_write_ln("Custom Keylog", false);
}
