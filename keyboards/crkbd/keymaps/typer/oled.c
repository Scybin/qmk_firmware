#include QMK_KEYBOARD_H

static uint32_t autocorrect_count = 0; // Counter for autocorrect events

bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    autocorrect_count++; // Increment the counter on each autocorrect event
    return true; // Allow the default autocorrect behavior to proceed
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "Autocorrect: %lu", autocorrect_count);
        oled_write_ln(buffer, false); // Display the autocorrect counter
    } else {
        oled_write_ln("Slave Side", false); // Display a message for the slave side
    }
    return false; // Indicate no further processing is needed
}
