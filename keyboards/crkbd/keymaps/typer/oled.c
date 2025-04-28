#include QMK_KEYBOARD_H

static uint32_t autocorrect_count = 0; // Counter for autocorrect events
static char last_corrected_word[32] = ""; // Stores the most recent autocorrected word

bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    autocorrect_count++; // Increment the counter
    strncpy(last_corrected_word, correct, sizeof(last_corrected_word) - 1); // Store the corrected word
    last_corrected_word[sizeof(last_corrected_word) - 1] = '\0'; // Ensure null termination
    return true; // Allow the default autocorrect behavior to proceed
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Display autocorrect status
        if (autocorrect_is_enabled()) {
            oled_write_ln("Autocorrect: ON", false);
        } else {
            oled_write_ln("Autocorrect: OFF", false);
        }

        // Display autocorrect counter
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "Count: %lu", autocorrect_count);
        oled_write_ln(buffer, false);

        // Display the most recent autocorrected word next to "Last Word:"
        char last_word_line[64];
        snprintf(last_word_line, sizeof(last_word_line), "Last Word: %s", last_corrected_word);
        oled_write_ln(last_word_line, false);
    } else {
        // Display "Slave Test" on the slave OLED
        oled_write_ln("Slave Test", false);
    }
    return false; // Indicate no further processing is needed
}
