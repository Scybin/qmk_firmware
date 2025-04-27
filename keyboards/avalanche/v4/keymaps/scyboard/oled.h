#ifndef OLED_H
#define OLED_H

#include QMK_KEYBOARD_H
#include "config.h"

// Declare OLED functions with corrected signatures
#include <drivers/oled/oled_driver.h>

bool scyboard_oled_task_user(void);  // Renamed to avoid conflict
bool oled_init(oled_rotation_t rotation);  // No change here

#endif
