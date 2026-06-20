#pragma once

// This module allows for basic AD9833 DDS chip usage
// Right now one pair of frequency and phase registers are always used
// This does not allow for quick swapping of the registers

// Be careful using square output because the output swings between 0 and supply voltage

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    SINE_OUT,
    SQUARE_OUT,
    TRIANGLE_OUT,
} ad9833_mode_t;

typedef struct {
    void (*spi_write)(uint16_t);
    float mclk_speed; // Speed in Hz of external clock for the AD9833 (typ 25 MHz)
} ad9833_t;

typedef struct {
	ad9833_mode_t mode;
    float frequency; // Hz
    float phase; // Radians
} ad9833_cfg_t;


ad9833_cfg_t start_ad9833(const ad9833_t *ad9833, const ad9833_cfg_t *cfg);
void init_ad9833(const ad9833_t *ad9833);
void stop_ad9833(const ad9833_t *ad9833);
