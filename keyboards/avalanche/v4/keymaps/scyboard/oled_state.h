#ifndef OLED_STATE_H
#define OLED_STATE_H

#include QMK_KEYBOARD_H

void oled_state_init(void);
void update_key_state(uint8_t row, uint8_t col, uint8_t layer, bool is_pressed);
uint32_t get_total_characters(void);
uint8_t get_last_row(void);
uint8_t get_last_col(void);
uint16_t get_last_keycode(void);

#endif
