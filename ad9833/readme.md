# AD9833 Module
A c module for the Analog Devices AD9833 DDS chip

## Typical usage
    // Spi write function for ad9833
    void spi_write_u16(uint16_t val) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_SPI_Transmit(&hspi, (uint8_t*)(&val), 1, 100);
        wait_us(2);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
        wait_us(2);
    }

    int main(void) {
        ad9833_t ad9833 = {
            .spi_write = spi_write_u16,
            .mclk_speed = 25000000,
        };
        init_ad9833(&ad9833);

        // Start a 100Hz triangle wave with no phase shift
        start_ad9833(&ad9833, TRIANGLE_OUT, 100, 0);  
        wait_ms(3000);
        stop_ad9833(&ad9833);
    }
