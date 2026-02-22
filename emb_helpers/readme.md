# Embedded Helpers Module
Provides some useful helper functions that are common in embedded projects.
Currently there is only an Arduino-like map function.

## Typical usage
    int32_t output = map(-50, -100, 100, 0, 100); // Output = 25