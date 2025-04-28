#include QMK_KEYBOARD_H

static uint32_t autocorrect_count = 0; // Counter for autocorrect events
static char last_corrected_word[32] = ""; // Stores the most recent autocorrected word
static bool white_out_flag = false; // Flag to trigger OLED white-out on the slave side

bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct) {
    autocorrect_count++; // Increment the counter
    strncpy(last_corrected_word, correct, sizeof(last_corrected_word) - 1); // Store the corrected word
    last_corrected_word[sizeof(last_corrected_word) - 1] = '\0'; // Ensure null termination
    white_out_flag = true; // Set the white-out flag for the slave side
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

        // Display the most recent autocorrected word
        oled_write_ln("Last Word:", false);
        oled_write_ln(last_corrected_word, false);
    } else {
        // Perform the white-out effect on the slave OLED
        if (white_out_flag) {
            uint8_t white_screen[512]; // Buffer for a 128x32 OLED (128 * 32 / 8 = 512 bytes)
            memset(white_screen, 0xFF, sizeof(white_screen)); // Fill the buffer with white pixels
            oled_write_raw((const char *)white_screen, sizeof(white_screen)); // Write the buffer to the OLED
            wait_ms(200); // Wait for 200 milliseconds
            oled_clear(); // Clear the OLED to blank
            oled_render(); // Render the cleared display
            white_out_flag = false; // Reset the white-out flag
        }
    }
    return false; // Indicate no further processing is needed
}
