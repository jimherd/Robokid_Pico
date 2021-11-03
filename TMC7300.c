/**
 * @file    TMC7300.c
 * @author  Jim Herd 
 * @brief   Routines to control Trinamic TMC7300 H-bridge device
 * @version 0.1
 * @date    2021-10-31
 */
#include "TMC7300.h"
#include "TMC7300_Registers.h"
#include "TMC7300_Fields.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"

//==============================================================================
// Global variables and structures
//==============================================================================

TMC7300_write_datagram_t write_datagram;

struct shadow_registers {
    uint32_t GCONF;
    uint32_t GSTAT;
    uint32_t IFCNT;
    uint32_t SLAVECONF;
    uint32_t IOIN;
    uint32_t CURRENT_LIMIT;
    uint32_t PWM_AB;
    uint32_t CHOPCONF;
    uint32_t DRVSTATUS;
    uint32_t PWMCONF;
} TMC7300_shadow_registers;

//==============================================================================
// Functions
//==============================================================================
// TMC7300_Init
//==============================================================================
/**
 * @brief Configure TMC7300 H-bridge chip
 * 
 * @param       none
 * @return      void
 * 
 */
void  TMC7300_Init(void) {
    

    uart_init(UART_PORT, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    gpio_init(TMC7300_EN_PIN);
    gpio_set_dir(TMC7300_EN_PIN, GPIO_OUT);
    gpio_pull_down(TMC7300_EN_PIN);         // should default but just make sure
    DISABLE_POWER_STAGE;                    // essential before chip configuration

    init_TMC7300_shadow_registers();

    set_master_slave_delay(DEFAULT_DELAY_TO_SEND_US);
}

//==============================================================================
// create_write_datagram
//==============================================================================
/**
 * @brief Create an 8-byte write datagram for TMC7300
 * 
 * @param[out]  datagram            pointer to an 8-byte TMC7300 write command struct
 * @param[in]   register_address    target TMC7300 register for command
 * @param[in]   register_value      value to be written to register
 * 
 * @return      void
 */
void create_write_datagram(TMC7300_write_datagram_t *datagram, uint8_t register_address, uint8_t register_value) {

    datagram->sync_byte =  TMC7300_SYNC_BYTE;
    datagram->slave_address = 0;
    datagram->register_address = register_address | TMC7300_WRITE_BIT;
    datagram->data = register_value;
    datagram->crc = TMC7300_CRC8((uint8_t *)datagram, LENGTH_WRITE_DATAGRAM);

}

//==============================================================================
// create_read_datagram
//==============================================================================
/**
 * @brief Create an 8-byte write datagram for TMC7300
 * 
 * @param[out]  datagram            pointer to 4-byte TMC7300 read command struct
 * @param[in]   register_address    target TMC7300 register for command 
 * 
 * @return      void
 */
void create_read_datagram(TMC7300_read_datagram_t *datagram, uint8_t register_address){

    datagram->sync_byte =  TMC7300_SYNC_BYTE;
    datagram->slave_address = 0;
    datagram->register_address = register_address | TMC7300_READ_BIT;
    datagram->crc = TMC7300_CRC8((uint8_t *)datagram, LENGTH_WRITE_DATAGRAM);
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
 * @param   datagram    pointer to 8-byte array 
 * @return              no value returned
 */
void TMC7300_write_reg(TMC7300_write_datagram_t *datagram) {

    uart_write_blocking(UART_PORT, (uint8_t *)datagram, sizeof(TMC7300_write_datagram_t));
}

//==============================================================================
// set_master_slave_delay
//==============================================================================
/**
 * @brief set delay between recieving a read datagram and sending a reply
 * 
 * @param[in]   delay in units of UART bit times 
 * @return      no value returned
 * 
 */
void set_master_slave_delay(uint32_t bit_times) {

uint32_t  tmp_bit_times, master_slave_delay;

    tmp_bit_times = bit_times;
    if (bit_times > BIT_TIMES_MAX) {
        tmp_bit_times = BIT_TIMES_MAX;
    }
    tmp_bit_times = tmp_bit_times & 0xFFFFFFF8;

    master_slave_delay = (((1000000 * tmp_bit_times) / BAUD_RATE) << 3);

    create_write_datagram(&write_datagram, TMC7300_CHIP_0, TMC7300_SLAVECONF);
    TMC7300_write_reg(&write_datagram);
}

//==============================================================================
// init_TMC7300_shadow_registers
//==============================================================================
/**
 * @brief Set TMC7300 shadow registers to datasheet/reset defaults
 * 
 */
void init_TMC7300_shadow_registers(void) {

    TMC7300_shadow_registers.GCONF         = 0x03;
    TMC7300_shadow_registers.GSTAT         = 0x00;
    TMC7300_shadow_registers.IFCNT         = 0x00;
    TMC7300_shadow_registers.SLAVECONF     = 0x00;
    TMC7300_shadow_registers.IOIN          = 0x00;
    TMC7300_shadow_registers.CURRENT_LIMIT = 0x00001F01;
    TMC7300_shadow_registers.PWM_AB        = 0x00;
    TMC7300_shadow_registers.CHOPCONF      = 0x13008001;
    TMC7300_shadow_registers.DRVSTATUS     = 0x00;
    TMC7300_shadow_registers.PWMCONF       = 0xC40D1024;
}

//==============================================================================
// TMC7300_command
//==============================================================================
/**
 * @brief execute the set of TMC7300 commands
 * 
 */
uint32_t TMC7300(command_t command, RW_mode_t RW_mode, uint32_t value) {

    switch(command) {
        case SET_PWM_A : {
            switch (RW_mode) {
                case READ_CMD : {
                    
                }
                case WRITE_CMD : {

                }
                default : {

                }
            }
            break;
        }
        case SET_PWM_B : {
            break;
        }
        default : {
            break;
        }
    }

}
