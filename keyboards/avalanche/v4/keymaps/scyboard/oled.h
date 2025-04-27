#ifndef OLED_H
#define OLED_H

#include QMK_KEYBOARD_H
#include "config.h"

// Declare OLED functions with corrected signatures
#include <drivers/oled/oled_driver.h>

bool oled_task_user(void);  // Correct return type (_Bool)
bool oled_init(oled_rotation_t rotation);  // Correct parameter

#endif
