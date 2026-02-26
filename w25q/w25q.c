#include "w25q.h"

#define CS_IDLE_STATE 0
#define CS_ACTIVE_STATE 1

#define GET_BE_ADDR_24(address) (uint8_t)(address >> 16), (uint8_t)(address >> 8), (uint8_t)(address)

// Status register bits
#define SR_BUSY 0x01

// Writes a basic command
// A basic command only contains the command byte 
static void write_basic_command(w25q_t *w25q, uint8_t command) {
    w25q->cs_fp(CS_ACTIVE_STATE);
    w25q->tx_fp(&command, 1);
    w25q->cs_fp(CS_IDLE_STATE);
}

// Initialises an empty w25q struct with function pointers
void w25q_init(w25q_t *w25q, flash_tx_fp tx_fp, flash_rx_fp rx_fp, flash_write_cs_fp cs_fp) {
    w25q->tx_fp = tx_fp;
    w25q->rx_fp = rx_fp;
    w25q->cs_fp = cs_fp;

    // Release power down
    write_basic_command(w25q, 0xAB);
}

// Send the write enable instruction
static void send_write_enable(w25q_t *w25q) {
    write_basic_command(w25q, 0x06);
}

// Returns the contents of the status register
static uint8_t read_sr(w25q_t *w25q) {
    uint8_t rx = 0;
    w25q->cs_fp(CS_ACTIVE_STATE);
    w25q->tx_fp((uint8_t[]){0x05}, 1);
    w25q->rx_fp(&rx, 1);
    w25q->cs_fp(CS_IDLE_STATE);
    return rx;
}


// Return true if the flash is busy
inline bool w25q_is_busy(w25q_t *w25q) {
    return (read_sr(w25q) & SR_BUSY) != 0;
}

static inline void wait_for_busy(w25q_t *w25q) {
    while (w25q_is_busy(w25q)) {
        for (uint32_t i = 0; i < 0x00FFFFFF; i++) {
            (void) 0;
        }
    }
}

// Erase flash at address
// Can erase a specific sector, block, or the whole chip 
// This starts the erase but doesn't wait until it is finished
void w25q_erase(w25q_t *w25q, flash_erase_t erase_type, uint32_t address) {
    wait_for_busy(w25q);
    send_write_enable(w25q);

    w25q->cs_fp(CS_ACTIVE_STATE);
    if (erase_type == CHIP_ERASE) {
        w25q->tx_fp((uint8_t[]){erase_type}, 1);
    } else {
        uint8_t command_buf[] = {erase_type, GET_BE_ADDR_24(address)};
        w25q->tx_fp(command_buf, 4);
    }

    w25q->cs_fp(CS_IDLE_STATE);
}

// Writes a buf to a page within the flash memory
// The address is a byte address
// If a whole page is being written to the bottom 8 address bits should be 0
// The buf len cannot exceed the boundary of the page or the start of the page will be overwritten with the remainder of the buffer
// A page is 256 bytes long
// The flash being written to needs to be erased first
void w25q_write(w25q_t *w25q, uint32_t address, uint8_t* data_buf, uint16_t buf_len) {
    wait_for_busy(w25q);
    send_write_enable(w25q);

    // Send page program instruction and the data to write
    w25q->cs_fp(CS_ACTIVE_STATE);
    uint8_t command_buf[] = {0x02, GET_BE_ADDR_24(address)};
    w25q->tx_fp(command_buf, 4);
    w25q->tx_fp(data_buf, buf_len);
    w25q->cs_fp(CS_IDLE_STATE);
}

// Read to a buffer from the flash start address
// The recieve buffer size is limited by HAL function not SPI flash chip capabilities
void w25q_read(w25q_t *w25q, uint32_t start_address, uint8_t* rx_buf, uint16_t rx_buf_len) {
    wait_for_busy(w25q);

    // Use fast read instruction to support high peripheral clock speeds
    w25q->cs_fp(CS_ACTIVE_STATE);
    uint8_t command_buf[] = {0x0b, GET_BE_ADDR_24(start_address), 0};
    w25q->tx_fp(command_buf, 5);
    w25q->rx_fp(rx_buf, rx_buf_len);
    w25q->cs_fp(CS_IDLE_STATE);
}