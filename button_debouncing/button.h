#include <stdint.h>
#include <stdbool.h>

// Button module for software debouncing and detecting long presses
// button_state variable is expected to be true when the button is pressed

#ifndef BUTTON_LONG_PRESS_MS
#define BUTTON_LONG_PRESS_MS 700
#endif

#ifndef BUTTON_DEBOUNCE_MS 
#define BUTTON_DEBOUNCE_MS 50
#endif

// Can be safely initialised with 0's
typedef struct {
   uint32_t last_edge_ms;
   bool last_state;
   bool long_press_registered;
} button_debounce_t;

bool button_pressed(button_debounce_t* button_debounce, bool button_state, uint32_t millis);
bool button_long_pressed(button_debounce_t* button_debounce, bool button_state, uint32_t millis);