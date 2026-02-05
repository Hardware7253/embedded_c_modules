# Software Timer Module
This modules provides a structure and functions for
polling a periodic or oneshot software timer.

## Usage
    // 10 Hz software timer
    software_timer_t stimer_1 = construct_stimer_f(get_tick_frequency(), 10, HAL_GetTick(), PERIODIC_ST);

    // 2 second period oneshot software timer
    software_timer_t stimer_2 = construct_stimer_p(get_tick_frequency(), 2000, HAL_GetTick(), ONESHOT_ST);

    while (true) {
        if (is_stimer_finished(&stimer_1, HAL_GetTick())) {
            // Do something when the software timer is finished
            // Periodic software timers are automatically reset and run again when they are complete
            (void) 0; 
        }

        if (is_stimer_finished(&stimer_2, HAL_GetTick())) {
            // Do something when the software timer is finished
            // After this the oneshot timer won't fire again unless it is reset with reset_stimer()
            (void) 0; 
        }
    }

