#include "oled_state.h"

// State variables
static uint32_t total_characters = 0;
static matrix_row_t previous_matrix[MATRIX_ROWS] = {0};
static uint8_t last_row = 0, last_col = 0;
static uint16_t last_keycode = 0;

// Timeout variables
static uint32_t oled_last_activity = 0;

void oled_state_init(void) {
    total_characters = 0;
    memset(previous_matrix, 0, sizeof(previous_matrix));
    last_row = last_col = 0;
    last_keycode = 0;
    oled_last_activity = timer_read32();
}

void update_key_state(uint8_t row, uint8_t col, uint8_t layer, bool is_pressed) {
    if (is_pressed) {
        last_row = row;
        last_col = col;
        last_keycode = keymap_key_to_keycode(layer, (keypos_t){.row = row, .col = col});
        total_characters++;
        reset_oled_timer();
    }
}

uint32_t get_total_characters(void) {
    return total_characters;
}

uint8_t get_last_row(void) {
    return last_row;
}

uint8_t get_last_col(void) {
    return last_col;
}

uint16_t get_last_keycode(void) {
    return last_keycode;
}

matrix_row_t get_previous_matrix_row(uint8_t row) {
    return previous_matrix[row];
}

void set_previous_matrix_row(uint8_t row, matrix_row_t value) {
    previous_matrix[row] = value;
}

void reset_oled_timer(void) {
    oled_last_activity = timer_read32();
}

bool is_oled_timed_out(void) {
    return (timer_elapsed32(oled_last_activity) > OLED_TIMEOUT);
}
