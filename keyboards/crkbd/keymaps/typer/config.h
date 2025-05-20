// Custom RGB Matrix configuration
#ifdef RGB_MATRIX_CUSTOM_USER
#   define RGB_MATRIX_CUSTOM_EFFECTS
#   define RGB_MATRIX_ENABLE
#   define ENABLE_RGB_MATRIX_BLUE_HEATMAP
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define RGB_MATRIX_KEYPRESSES
#endif

// OLED configuration
#ifdef OLED_ENABLE
#   define SPLIT_OLED_ENABLE
#   define OLED_TIMEOUT 30000  // 30 Seconds
#   define OLED_TASK_KB_OVERRIDE
#endif
