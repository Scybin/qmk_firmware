# Feature configuration
MOUSEKEY_ENABLE = no                  # Mouse key support
TAP_DANCE_ENABLE = yes                # Tap dance functionality
RGBLIGHT_ENABLE = yes                 # RGB lighting
OLED_ENABLE = yes                     # OLED support

# Disable unused RGBLight modes
RGBLIGHT_EFFECT_BREATHING = no
RGBLIGHT_EFFECT_RAINBOW_MOOD = no
RGBLIGHT_EFFECT_RAINBOW_SWIRL = no
RGBLIGHT_EFFECT_SNAKE = no
RGBLIGHT_EFFECT_STATIC_GRADIENT = no
RGBLIGHT_EFFECT_RGB_TEST = no
RGBLIGHT_EFFECT_ALTERNATING = no

# Include custom source files
SRC += oled.c                         # Include the custom OLED logic

# Optimization settings
LINK_TIME_OPTIMIZATION_ENABLE = yes   # Link-time optimization
EXTRAFLAGS += -flto                   # Additional flags
									  
# Disable unused features			  
#define NO_ACTION_MACRO               # Macro actions
#define NO_ACTION_FUNCTION            # Function actions
