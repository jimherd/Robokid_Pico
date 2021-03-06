//
// TMC7300
//
// Author   : Jim Herd
// Date     : Oct 2021

#ifndef __TMC7300_H__
#define __TMC3700_H__


#include    "Pico_IO.h"
#include    "pico/binary_info.h"

#include    "TMC7300_FIELDS.h"

#define     TMC7300_SYNC_BYTE       0x50
#define     TMC7300_WRITE_BIT       0x80
#define     TMC7300_READ_BIT        0x00

#define     LENGTH_WRITE_DATAGRAM       sizeof(TMC7300_write_datagram_t)
#define     LENGTH_READ_DATAGRAM        sizeof(TMC7300_read_datagram_t)
#define     LENGTH_READ_REPLY_DATAGRAM  sizeof(TMC7300_read_reply_datagram_t)

#define     TMC7300_CHIP_0          0
#define     TMC7300_CHIP_1          1
#define     TMC7300_CHIP_2          2
#define     TMC7300_CHIP_3          3

#define     DEFAULT_DELAY_TO_SEND_US        8
#define     BIT_TIMES_MAX                 120

//==============================================================================
// Error codes
//==============================================================================

typedef enum { NO_ERROR         =  0, 
               BAD_MOTOR_NUMBER = -1, 
               BAD_PWM_PERCENT  = -2,
               CRC_ERROR        = -3,
} TMC7300_errors_t;

//==============================================================================
// Macros
//==============================================================================

#define MERGE_REG_VALUE(REGISTER, VALUE, MASK, SHIFT)  VALUE = ((REGISTER && (~MASK)) || (VALUE << SHIFT))
#define EXTRACT_REG_VALUE(VALUE, MASK, SHIFT)          ((VALUE && MASK) >> SHIFT)

//==============================================================================
// Look-up table for CRC8 calculation.
//==============================================================================
/**uint32_t TMC7300(command_t command, RW_mode_t RW_mode, uint32_t value)
 * @brief Look-up table for CRC8 calculation.
 * 
 * @note    Tables of 8-bit vales for polynomial (8,4,2,1).
 *          Polynomial used by Trinamic TMC7300 H-bridge chip.
 * 
 *          Values generated by on-line tool :
 *          https://www.sunshine2k.de/coding/javascript/crc/crc_js.html
 */
static const uint8_t TMC7300_crc_table[] = {
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31,
    0x24, 0x23, 0x2a, 0x2d, 0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65,
    0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d, 0xe0, 0xe7, 0xee, 0xe9,
    0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1,
    0xb4, 0xb3, 0xba, 0xbd, 0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2,
    0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea, 0xb7, 0xb0, 0xb9, 0xbe,
    0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16,
    0x03, 0x04, 0x0d, 0x0a, 0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42,
    0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a, 0x89, 0x8e, 0x87, 0x80,
    0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8,
    0xdd, 0xda, 0xd3, 0xd4, 0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c,
    0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44, 0x19, 0x1e, 0x17, 0x10,
    0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f,
    0x6a, 0x6d, 0x64, 0x63, 0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b,
    0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13, 0xae, 0xa9, 0xa0, 0xa7,
    0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef,
    0xfa, 0xfd, 0xf4, 0xf3
};

//
// initial values of TMC7300 registers

static const uint32_t TMC7300_init_data[] = {
    0x00000000,     // GCONF
    0x00000000,     // GSTAT
    0x00000000,     // IFCNT
    0x00000000,     // SLAVECONF
    0x00000000,     // IOIN
    ((TMC7300_IRUN_MAX << TMC7300_IRUN_SHIFT) | TMC7300_FREEWHEEL_MODE_OP),  // CURRENT_LIMIT
    0x00000000,     // PWM_AB
    0x13008001,     // CHOPCONF
    0x00000000,     // DRV_STATUS
    0xC40D1024      // PWMCONF
};

//==============================================================================
// enum typedef definitions
//==============================================================================

typedef enum { READ_CMD, WRITE_CMD } RW_mode_t;
typedef enum { READ_ONLY, READ_WRITE, WRITE_ONLY } reg_access_t;
typedef enum { SET_PWM_A, SET_PWM_B, SET_SEND_DELAY } command_t;

//==============================================================================
// datagram typedef definitions
//==============================================================================

typedef struct TMC7300_write_datagram {
    uint8_t     sync_byte;
    uint8_t     slave_address;
    uint8_t     register_address;
    uint32_t    data;
    uint8_t     crc;
} TMC7300_write_datagram_t;

typedef struct TMC7300_read_datagram {
    uint8_t     sync_byte;
    uint8_t     slave_address;
    uint8_t     register_address;
    uint8_t     crc;
} TMC7300_read_datagram_t;

typedef struct TMC7300_read_reply_datagram {
    uint8_t     sync_byte;
    uint8_t     master_address;
    uint8_t     register_address;
    uint32_t    data;
    uint8_t     crc;
} TMC7300_read_reply_datagram_t;

typedef struct register_data {
    uint8_t       register_address;
    reg_access_t  RW_mode;
    uint32_t      init_value;
    uint32_t      shadow_value;
} register_data_t;


//==============================================================================
// Function prototypes.
//==============================================================================

void              TMC7300_Init(void);
void              reset_TMC7300(void);
void              TMC7300_write_reg(TMC7300_write_datagram_t *datagram);
TMC7300_errors_t  TMC7300_read_reg(TMC7300_read_datagram_t *datagram, TMC7300_read_reply_datagram_t *reply_datagram);
uint8_t           TMC7300_CRC8(uint8_t *data, uint32_t bytes);
void              create_write_datagram(TMC7300_write_datagram_t *datagram, uint8_t register_address, uint32_t register_value);
void              create_read_datagram(TMC7300_read_datagram_t *datagram, uint8_t register_address);
void              set_master_slave_delay(uint32_t bit_times);
TMC7300_errors_t  execute_cmd(command_t command, RW_mode_t RW_mode, uint32_t value);
//int32_t           abs_int32(int32_t value);

#endif
