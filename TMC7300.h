//
// TMC7300
//
// Author   : Jim Herd
// Date     : Oct 2021

#ifndef __TMC7300_H__
#define __TMC3700_H__

//                                                                              
// 
//                                                                              

void  TMC7300_Init(void);

 #define  register_GCONF             0x00
 #define  register_GSTAT             0x01
 #define  register_IFCNT             0x02
 #define  register_SLAVECONF         0x03
 #define  register_IOIN              0x06
 #define  register_CURRENT_LIMIT     0x10
 #define  register_PWM_AB            0x22
 #define  register_CHOPCONF          0x6C
 #define  register_DRV_STATUS        0x6F
 #define  register_PWMCONF           0x70

// Register GCONF
#define PWM_DIRECT        0x00000001
#define EXTCAP            0x00000002
#define PAR_MODE          0x00000004
#define TEST_MODE         0x00000080

// Register  GSTAT
#define RESET            0x00000001
#define DRV_ERR          0x00000002
#define U3V5             0x00000004

// Register  IFCNT
#define IFCNT            0x000000FF

// Register  SLAVECONF
#define SLAVECONF        0x00000F00

// Register  IOIN
#define EN                0x00000001
#define NSTDBY            0x00000002
#define AD0               0x00000004
#define AD1               0x00000008
#define DIAG              0x00000010
#define UART_ENABLED      0x00000020
#define UART_INPUT        0x00000040
#define MODE_INPUT        0x00000080
#define A2                0x00000100
#define A1                0x00000200
#define COMP_A1A2         0x00000400 
#define COMP_B1B2         0x00000800

// Register  CURRENT_LIMIT
#define MOTORRUN         0x00000001
#define IRUN             0x00001F00

// Register  PWM_AB
#define PWM_A            0x000001FF
#define PWM_B            0x01FF0000
#define PWM_AB           0x000001FF

// Register  CHOPCONF
#define ENABLEDRV        0x00000001
#define TBL              0x00018000
#define DISS2G           0x40000000
#define DISS2VS          0x80000000

// Register  DRV_STATUS
#define OTPW             0x00000001 
#define OT               0x00000002 
#define S2GA             0x00000004 
#define S2GB             0x00000008 
#define S2VSA            0x00000010
#define S2VSB            0x00000020
#define OLA              0x00000040
#define OLB              0x00000080 
#define T120             0x00000100
#define T150             0x00000200

// Register  PWMCONF
#define PWM_FREQ         0x00030000
#define FREEWHEEL        0x00300000

#endif