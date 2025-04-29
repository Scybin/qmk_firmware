#include QMK_KEYBOARD_H
#include "oled_state.h"

// Bitmap for "scyboard" (128x64 OLED screen)
static const unsigned char PROGMEM scyboard_logo[] = {
    // (Bitmap data remains unchanged)
};

// Layer names for display
static const char *layer_names[] = {
    "BASE", "LIGHT", "DEV", "OSRS", "LOWER", "UPPER"
};

static void oled_write_line(uint8_t row, const char *text) {
    oled_set_cursor(0, row);
    oled_write(text, false);
}

static void oled_write_formatted(uint8_t row, const char *format, ...) {
    char buffer[32];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    oled_write_line(row, buffer);
}

// Timer for OLED sleep
static uint32_t oled_timer = 0;

// Helper function to reset OLED timer on keypress
void oled_reset_timer_on_keypress(void) {
    oled_timer = timer_read32(); // Reset the timer
}

bool oled_task_user(void) {
    // Check if the OLED should be turned off due to inactivity
    if (timer_elapsed32(oled_timer) > 5000) { // 5 seconds timeout
        oled_off();
        return false;
    }

    if (is_keyboard_master()) {
        oled_on(); // Ensure OLED is on when active
        oled_clear();

        uint8_t current_layer = biton32(layer_state);
        oled_set_cursor(0, 0);
        oled_write_P(PSTR("Layer: "), false);
        oled_write(layer_names[current_layer], false);

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            matrix_row_t current_row = matrix_get_row(row);
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                bool was_pressed = get_previous_matrix_row(row) & (1 << col);
                bool is_pressed = current_row & (1 << col);

                if (is_pressed && !was_pressed) {
                    process_keypress(row, col, current_layer);
                    break;
                }
            }
            set_previous_matrix_row(row, current_row);
        }

        if (get_last_keycode() != 0) {
            oled_write_formatted(2, "Row: %d Col: %d", get_last_row(), get_last_col());
            oled_write_formatted(4, "KC: 0x%04X - %05d", get_last_keycode(), get_last_keycode());
        } else {
            oled_write_line(2, "Row: None Col: None");
            oled_write_line(4, "KC: None");
        }

        oled_write_formatted(6, "Chars: %lu", get_total_characters());
    } else {
        oled_on(); // Ensure OLED is on when active
        oled_clear();
        oled_write_raw_P((const char *)scyboard_logo, sizeof(scyboard_logo));
    }

    return false;
}
