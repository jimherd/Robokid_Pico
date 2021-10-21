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
#define PWM_DIRECT       ( 0x00, 0x00000001,  0 ) 
#define EXTCAP           ( 0x00, 0x00000002,  1 ) 
#define PAR_MODE         ( 0x00, 0x00000004,  2 ) 
#define TEST_MODE        ( 0x00, 0x00000080,  7 ) 

// Register  GSTAT
#define RESET            ( 0x01, 0x00000001,  0 ) 
#define DRV_ERR          ( 0x01, 0x00000002,  1 ) 
#define U3V5             ( 0x01, 0x00000004,  2 ) 

// Register  IFCNT
#define IFCNT            ( 0x02, 0x000000FF,  0 ) 

// Register  SLAVECONF
#define SLAVECONF        ( 0x03, 0x00000F00,  8 ) 

// Register  IOIN
#define EN               ( 0x06, 0x00000001,  0 ) 
#define NSTDBY           ( 0x06, 0x00000002,  1 ) 
#define AD0              ( 0x06, 0x00000004,  2 ) 
#define AD1              ( 0x06, 0x00000008,  3 ) 
#define DIAG             ( 0x06, 0x00000010,  4 ) 
#define UART_ENABLED     ( 0x06, 0x00000020,  5 ) 
#define UART_INPUT       ( 0x06, 0x00000040,  6 ) 
#define MODE_INPUT       ( 0x06, 0x00000080,  7 ) 
#define A2               ( 0x06, 0x00000100,  8 ) 
#define A1               ( 0x06, 0x00000200,  9 ) 
#define COMP_A1A2        ( 0x06, 0x00000400, 10 ) 
#define COMP_B1B2        ( 0x06, 0x00000800, 11 ) 

// Register  CURRENT_LIMIT
#define MOTORRUN         ( 0x10, 0x00000001,  0 ) 
#define IRUN             ( 0x10, 0x00001F00,  8 ) 

// Register  PWM_AB
#define PWM_A            ( 0x22, 0x000001FF,  0 ) 
#define PWM_B            ( 0x22, 0x01FF0000, 16 ) 
#define PWM_AB           ( 0x22, 0x000001FF,  0 ) 

// Register  CHOPCONF
#define ENABLEDRV        ( 0x6C, 0x00000001,  0 ) 
#define TBL              ( 0x6C, 0x00018000, 15 ) 
#define DISS2G           ( 0x6C, 0x40000000, 30 ) 
#define DISS2VS          ( 0x6C, 0x80000000, 31 ) 

// Register  DRV_STATUS
#define OTPW             ( 0x6F, 0x00000001,  0 )  
#define OT               ( 0x6F, 0x00000002,  1 )  
#define S2GA             ( 0x6F, 0x00000004,  2 )  
#define S2GB             ( 0x6F, 0x00000008,  3 )  
#define S2VSA            ( 0x6F, 0x00000010,  4 )  
#define S2VSB            ( 0x6F, 0x00000020,  5 )  
#define OLA              ( 0x6F, 0x00000040,  6 )  
#define OLB              ( 0x6F, 0x00000080,  7 )  
#define T120             ( 0x6F, 0x00000100,  8 )  
#define T150             ( 0x6F, 0x00000200,  9 )  

// Register  PWMCONF
#define PWM_FREQ         ( 0x70, 0x00030000, 16 ) 
#define FREEWHEEL        ( 0x70, 0x00300000, 20 ) 

#endif