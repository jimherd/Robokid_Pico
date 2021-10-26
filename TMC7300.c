//
// TMC7300

#include "TMC7300.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"


//==============================================================================
// TMC7300_Init
//==============================================================================
/**
 * @brief Configure TMC7300 H-bridge chip
 * 
 * @return      void
 * 
 */
void  TMC7300_Init(void) {

    uart_init(UART_PORT, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

}

//==============================================================================
// TMC7300_CRC8 
//==============================================================================
/**
 * @brief  calculate 8-bit CRC on array of bytes
 * 
 * @param[in] data      array of 8-bit values
 * @param[in] length    number of array
 * @return              8-bit CRC value
 * 
 * @note    Fast CRC generation using table lookup
 * @author  Trinamic
 * @date    Oct 2021
 */
uint8_t TMC7300_CRC8(uint8_t *data, uint32_t length) {

uint8_t crc = 0;

    while(--length) {
        crc = TMC7300_crc_table[crc ^ *data++];
    }
    return crc;
}

//==============================================================================
// TMC7300_write_reg
//==============================================================================
/**
 * @brief Write 8 byte datagram to TMC7300 h-bridge chip
 * 
 * @param datagram pointer to 8-byte array 
 */
void    TMC7300_write_reg(TMC7300_write_datagram_t *datagram) {

    uart_write_blocking(UART_PORT, (uint8_t *)datagram, sizeof(TMC7300_write_datagram_t));
}