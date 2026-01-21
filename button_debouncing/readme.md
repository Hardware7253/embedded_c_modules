# Button Debouncing Module 
Allows for software debouncing of buttons and detecting long presses.
When polling the functions they will only return true once 
(on the rising edge of the debounced button press).

## Typical usage
    // Init
    button_debounce_t debounce_1 = {0};

    bool pin_state = (bool)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
    if (button_pressed(&debounce_1, pin_state, HAL_GetTick())) {
        (void) 0; // Any press detected (with debouncing)
    }

    if (button_long_pressed(&debounce_1, pin_state, HAL_GetTick())) {
        (void) 0; // Long press detected
    }

