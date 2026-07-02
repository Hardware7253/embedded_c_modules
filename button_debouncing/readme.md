# Button Debouncing Module 
Allows for software debouncing of buttons and detecting long presses.
When polling the functions they will only return true once 
(on the rising edge of the debounced button press).

## Typical usage
```c
// Init
button_debounce_t debounce_1 = {0};

bool pin_state = (bool)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
if (button_pressed(&debounce_1, pin_state, HAL_GetTick())) {
    (void) 0; // Any press detected (with debouncing)
}

if (button_long_pressed(&debounce_1, pin_state, HAL_GetTick())) {
    (void) 0; // Long press detected
}

if (debounce_1.consecutive_presses == 2) {
    (void) 0; // Double click detected
}
```

## Configuration
If the default settings aren't satisfactory a configuration header can be made like so:

```c
#pragma once

#define ENABLE_BUTTON_COUNTING 1 
#define BUTTON_DEBOUNCE_MS 50
#define BUTTON_LONG_PRESS_MS 700
#define BUTTON_CONSECUTIVE_PRESS_MS 250
```

Just remember to include the configuration header before including the button debouncing module