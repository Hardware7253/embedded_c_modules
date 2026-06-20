# Windbond W25Qxx Flash Module
A basic module that allows for reading, erasing, and writing of the winbond W25Qxx series flash chips.

## Typical usage
```c
void set_cs(bool is_not_idle) {
    HAL_GPIO_WritePin(CS_PIN_BUS, CS_PIN, is_not_idle ? !CS_IDLE_STATE : CS_IDLE_STATE);
}

void flash_tx(uint8_t *tx_buf, uint32_t tx_buf_len) {
    delay_us(1);
    HAL_SPI_Transmit(&hspi, tx_buf, (uint16_t)tx_buf_len, TX_RX_TIMEOUT);
    delay_us(1);
}

void flash_rx(uint8_t *rx_buf, uint32_t rx_buf_len) {
    delay_us(1);
    HAL_SPI_Receive(&hspi, rx_buf, (uint16_t)rx_buf_len, TX_RX_TIMEOUT);
    delay_us(1);
}

void main(void) {
    w25q_t w25q = {0};
    w25q_init(&w25q, flash_tx, flash_rx, set_cs);

    // Erase 4KiB starting at address 0
    w25q_erase(&w25q, SECTOR_ERASE_4KIB, 0);

    // Write a test buffer to the first page
    uint8_t test_buf[256] = {0};
    w25q_write(&w25q, 0, test_buf, 256);
}
```