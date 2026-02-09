# Rotary Encoder Module
Simple module for reading left / right inputs from a rotary encoder.
This code is not sensitive to bouncing.

## Typical Usage
    // Init
    renc_t renc = {0};
    int32_t counter = 0;

    while (true) {
        bool p1_state = (bool)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
        bool p2_state = (bool)HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
        update_renc(&renc, p1_state, p2_state);

        if (is_renc_left(&renc)) {
            counter++;
        }

        if (is_renc_right(&renc)) {
            counter--;
        }
    }

