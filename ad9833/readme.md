# AD9833 Module
A c module for the Analog Devices AD9833 DDS chip

## Typical usage
```c
// Spi write function for ad9833
void spi_write_u16(uint16_t val) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi, (uint8_t*)(&val), 1, 100);
    wait_us(2);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    wait_us(2);
}

const ad9833_t AD9833 = {
    .spi_write = spi_write_u16,
    .mclk_speed = 25000000,
};

int main(void) {
    init_ad9833(&AD9833);

    // 100Hz triangle wave with no phase shift
    ad9833_cfg_t dds_cfg = {
        .mode = TRIANGLE_OUT,
        .frequency = 100.0,
        .phase = 0.0,
    };

    start_ad9833(&AD9833, &dds_cfg);
    wait_ms(3000);
    stop_ad9833(&AD9833);
}
```
