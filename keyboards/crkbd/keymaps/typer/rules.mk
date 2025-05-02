# Feature Configuration
RGB_MATRIX_ENABLE = yes
AUTOCORRECT_ENABLE = yes
WPM_ENABLE = yes
OLED_ENABLE = yes
RGBLIGHT_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no
NKRO_ENABLE = no
BOOTMAGIC_ENABLE = no
TAP_DANCE_ENABLE = no
ONESHOT_ENABLE = no
UNICODE_ENABLE = no
DYNAMIC_MACRO_ENABLE = no

# Custom Source Files
SRC += oled.c
SRC_FILTER = -<keyboards/crkbd/crkbd.c>
SRC += custom/custom_rgb_matrix.c
SRC += custom/typing_heatmap_anim.c
SRC_FILTER += -<quantum/rgb_matrix/rgb_matrix.c>
SRC_FILTER += -<quantum/rgb_matrix/rgb_matrix.h>
SRC_FILTER += -<quantum/rgb_matrix/animations/typing_heatmap_anim.h>

# Optimization Settings
LINK_TIME_OPTIMIZATION_ENABLE = yes
EXTRAFLAGS += -flto

# Disable Unused Features
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

NO_DEBUG = yes
NO_PRINT = yes
