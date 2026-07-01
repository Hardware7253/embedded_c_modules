// Button module for software debouncing, detecting long presses, and counting consecutive presses
// button_state variable is expected to be true when the button is pressed
#pragma once

#include <stdint.h>
#include <stdbool.h>

// Button needs to be pressed for this long to register a long press
#ifndef BUTTON_LONG_PRESS_MS
#define BUTTON_LONG_PRESS_MS 700
#endif

// A press won't be registered until this time has passed since the falling edge
#ifndef BUTTON_DEBOUNCE_MS 
#define BUTTON_DEBOUNCE_MS 50
#endif

// Minimum time between button presses to register a consecutive press
#ifndef BUTTON_CONSECUTIVE_PRESS_MS 
#define BUTTON_CONSECUTIVE_PRESS_MS 250
#endif

#ifndef ENABLE_CONSECUTIVE_COUNTING 
#define ENABLE_CONSECUTIVE_COUNTING false 
#endif


// Can be safely initialised with 0's
typedef struct {
   uint32_t last_edge_ms;
   bool last_state;
   bool long_press_registered;

   #if ENABLE_CONSECUTIVE_COUNTING
      uint8_t consecutive_presses;
      uint32_t last_press_ms;
   #endif
} button_debounce_t;

bool button_pressed(button_debounce_t* button_debounce, bool button_state, uint32_t millis);
bool button_long_pressed(button_debounce_t* button_debounce, bool button_state, uint32_t millis);

