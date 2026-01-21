#include "button.h"

// Detects if button has been pressed with debouncing
// Will only return true on the button press rising edge
bool button_pressed(button_debounce_t* button_debounce, bool button_state, uint32_t millis) {
    if (button_debounce->last_state != button_state) { 

        // Only register edge if the debounce time has passed since the last edge
        if ((millis - button_debounce->last_edge_ms) > BUTTON_DEBOUNCE_MS) {
            button_debounce->last_edge_ms = millis;    
            button_debounce->last_state = button_state;
            button_debounce->long_press_registered = false;
            return button_state;
        }
    }

    return false;
}

// Return true if a button long press has been triggered
// button_pressed is expected to be polled before this function is called
bool button_long_pressed(button_debounce_t* button_debounce, bool button_state, uint32_t millis) {
    if (button_state && !button_debounce->long_press_registered) {
        if ((millis - button_debounce->last_edge_ms) > BUTTON_LONG_PRESS_MS) {
            button_debounce->long_press_registered = true;
            return true;
        }
    }

    return false;
}