#include <math.h>
#include "ad9833.h"

#define BIT(x) (1UL << (x))
#define PI 3.14159265358979323846F

// Control register bit defines
#define CR_D28      BIT(13)
#define CR_HLB      BIT(12)
#define CR_FSELECT  BIT(11)
#define CR_PSELECT  BIT(10)
#define CR_RESET    BIT(8)
#define CR_SLEEP1   BIT(7)
#define CR_SLEEP12  BIT(6)
#define CR_OPBITEN  BIT(5)
#define CR_DIV2     BIT(3)
#define CR_MODE     BIT(1)

// Register select defines
#define CR_SEL      0
#define FREQ0_SEL   BIT(14)
#define FREQ1_SEL   BIT(15)
#define PHASE0_SEL  (BIT(14) | BIT(15))
#define PHASE1_SEL  (BIT(13) | BIT(14) | BIT(15))

#define FREQ_REGISTER 0
#define PHASE_REGISTER 0

// Reset chip 
void stop_ad9833(const ad9833_t *ad9833) {
    ad9833->spi_write(CR_SEL | CR_RESET | CR_SLEEP1 | CR_SLEEP12);
}

// Reset chip
inline void init_ad9833(const ad9833_t *ad9833) {
    stop_ad9833(ad9833);
}

// Starts outputting a wave with frequency, phase, and mode defined within the configuration parameter 
// Also returns a new configuration struct, with the true output frequency and phase after quantisation
ad9833_cfg_t start_ad9833(const ad9833_t *ad9833, const ad9833_cfg_t *cfg) {

    uint16_t control_reg = CR_SEL | CR_D28 |
        (FREQ_REGISTER ? CR_FSELECT : 0) |
        (PHASE_REGISTER ? CR_PSELECT : 0);

    uint8_t frequency_multiplier = 1;

    switch (cfg->mode) {
        case (SINE_OUT):
            break;
        case (TRIANGLE_OUT):
            control_reg |= CR_MODE;
            break;
        case (SQUARE_OUT):
            // For the AD9833, the fequency register sets the time between sqaure wave edges (half period)
            // So we multiply the frequency by 2 to account for this
            frequency_multiplier = 2; 
            control_reg |= CR_OPBITEN;
            break;
    }
    ad9833->spi_write(control_reg);

    // Calculate and write phase register
    uint16_t phase_reg = (cfg->phase / (2 * PI)) * BIT(12);
    ad9833->spi_write(phase_reg + (PHASE_REGISTER ? PHASE1_SEL : PHASE0_SEL));

    // Calculate and write frequency register
    uint16_t register_sel = (FREQ_REGISTER ? FREQ1_SEL : FREQ0_SEL);
    uint32_t freq_reg = (uint32_t)round((BIT(28) * cfg->frequency * frequency_multiplier) / ad9833->mclk_speed);
    uint16_t lower_bits = (uint16_t)(freq_reg & 0x3FFF); // Get 14 LSB
    uint16_t upper_bits = (uint16_t)(freq_reg >> 14); // Get 14 MSB
    ad9833->spi_write(lower_bits | register_sel); 
    ad9833->spi_write(upper_bits | register_sel); 

    // Calculate quantised frequency and phase
    ad9833_cfg_t out_values = {
        .frequency = (freq_reg * (ad9833->mclk_speed / BIT(28))) / frequency_multiplier,
        .phase = phase_reg * ((2 * PI) / BIT(12)),
        .mode = cfg->mode,
    };
    return out_values; 
}