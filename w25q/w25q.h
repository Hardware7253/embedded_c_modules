#pragma once

#include <stdint.h>
#include <stdbool.h>

#define W25Q_SECTOR_SIZE 4096
#define W25Q_PAGE_SIZE 256


// SPI TX function pointer - should not control CS
// Parameters should be: tx_buf, tx_buf_size 
typedef void (*flash_tx_fp)(uint8_t*, uint32_t); 

// SPI RX function pointer - should not control CS
// Parameters should be: rx_buf, rx_cnt
typedef void (*flash_rx_fp)(uint8_t*, uint32_t); 

// SPI set CS function_pointer
// Writes the chip select pin for the flash to either the idle state or the CS state
// Parameter: true -> CS, false -> idle
typedef void (*flash_write_cs_fp)(bool);

typedef struct {
    flash_tx_fp tx_fp;
    flash_rx_fp rx_fp;
    flash_write_cs_fp cs_fp;
} w25q_t;

typedef enum {
    SECTOR_ERASE_4KIB = 0x20,
    BLOCK_ERASE_32KIB = 0x52,
    BLOCK_ERASE_64KIB = 0xd8,
    CHIP_ERASE        = 0x60,
} flash_erase_t;

void w25q_init(w25q_t *w25q, flash_tx_fp tx_fp, flash_rx_fp rx_fp, flash_write_cs_fp cs_fp);
bool w25q_is_busy(w25q_t *w25q);
void w25q_erase(w25q_t *w25q, flash_erase_t erase_type, uint32_t address);
void w25q_write(w25q_t *w25q, uint32_t address, uint8_t* data_buf, uint16_t buf_len);
void w25q_read(w25q_t *w25q, uint32_t start_address, uint8_t* rx_buf, uint16_t rx_buf_len);