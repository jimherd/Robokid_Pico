/**
 * @file robokid_2.h
 * @author Jim Herd 
 * @brief  Constants relating to Robokid robot
 * @version 0.1
 * @date 2021-11-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

//==============================================================================
// Constants
//==============================================================================

#define     TMC7300_UART_PORT   uart1  
#define     BAUD_RATE           115200    
                                                                             
#define     UART_TX_PIN         GP8          // Pin 11
#define     UART_RX_PIN         GP9          // Pin 12
#define     TMC7300_EN_PIN      GP10         // Pin 14

#define     NOS_ROBOKID_MOTORS  2

//==============================================================================
// enum definitions
//==============================================================================

typedef enum  { GCONF_IDX,
                GSTAT_IDX,
                IFCNT_IDX,
                SLAVECONF_IDX,
                IOIN_IDX,
                CURRENT_LIMIT_IDX,
                PWM_AB_IDX,
                CHOPCONF_IDX,
                DRV_STATUS_IDX,
                PWMCONF_IDX
} reg_index_t;

//==============================================================================
// Macros
//==============================================================================

#define     DISABLE_POWER_STAGE          gpio_put(TMC7300_EN_PIN, 0)
#define     ENABLE_POWER_STAGE           gpio_put(TMC7300_EN_PIN, 1)

