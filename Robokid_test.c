/**
 * @file Robokid_test.c
 * @author Jim Herd
 * @brief Development program for Robokid based on Pico/Trinamic devices
 * @version 0.1
 * @date 2021-11-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
 
#include "OLED_128X64.h"
#include "system.h"

#include "TMC7300.h"
#include "TMC7300_Registers.h"
#include "TMC7300_Fields.h"

int main() {

    stdio_init_all();

    Oled_Init();
    TMC7300_Init();
//
// print hello message 

    Oled_SetFont(Terminal12x16, 12, 16, 32,127);
    Oled_ConstText("Test code",   0, 0);
    Oled_ConstText("Robikid 3",   0, 2);
    Oled_ConstText("Oled 128x64", 0, 4);
    Oled_ConstText("SSD1306  ",   0, 6);

    sleep_ms(3000);
    printf("Loaded\r\n");

    Oled_Demo();
    
    while(1){}
}
