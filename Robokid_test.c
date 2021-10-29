/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
 
#include "OLED_128X64.h"
#include "font.h"
#include "bitmap.h"

#include "TMC7300.h"
#include "TMC7300_Registers.h"
#include "TMC7300_Fields.h"

int main() {

char buffer2[20];
uint32_t  i, j, k;

    Oled_Init();

    Oled_SetFont(Terminal12x16, 12, 16, 32,127);
    Oled_ConstText("Test code", 0, 0);
    Oled_ConstText("Robikid", 0, 2);
    Oled_ConstText("Oled 128x64", 0, 4);
    Oled_ConstText("SSD1306  ", 0, 6);

    sleep_ms(3000);

    TMC7300_Init();

    Oled_FillScreen(0x00);
    Oled_ConstText("lines", 30, 0);
    for(i=16; i<64; i=i+4) {
        Oled_Line(0, 16, 127, i, BLACK);
        sleep_ms(500);
    }
    sleep_ms(3000);

    Oled_FillScreen(0x00);
    Oled_ConstText("Circles", 10, 0);
    for(i=1; i<16; i=i+3) {
        Oled_Circle(63, 31, i, BLACK);
        sleep_ms(500);
    }
    sleep_ms(3000);

    Oled_FillScreen(0x00);
    Oled_ConstText("Rectangles", 0, 0);
    for(i = 0; i < 15; i = i + 4) {
        Oled_Rectangle(16+i, 16+i, 112-i, 46-i, BLACK);
        sleep_ms(500);
    }
    sleep_ms(3000);

    Oled_FillScreen(0x00);
    Oled_ConstText("  Inverts  ", 0, 0);
    for(i=0; i<8; i++) {
        Oled_InvertRam(0, 0, 127, 7);
        sleep_ms(1500);
    } 

    sleep_ms(1000);
    Oled_FillScreen(0x00);
    Oled_ConstText("Main Menu", 8, 0);
    Oled_Icon(icon1,20,3,32,32); 
    Oled_Icon(icon2,72,3,32,32); sleep_ms(3000);
    Oled_Icon(icon3,20,3,32,32); 
    Oled_Icon(icon4,72,3,32,32); sleep_ms(3000);

    sleep_ms(1000);
    Oled_FillScreen(0x00);
    Oled_ConstText("Fonts", 35, 0);
    for(i=0; i<113; i++) {
        sprintf(buffer2,"%03d",i);
        Oled_SetFont(Segment_25x40, 25, 40, 46, 58);
        Oled_Text(buffer2, 0, 3);
        Oled_SetFont(Terminal12x16, 12, 16, 32 ,127);
        Oled_Text(buffer2, 90, 3);
        Oled_SetFont(Font_6x8, 6, 8, 32, 127);
        Oled_Text(buffer2, 99, 6);
        sleep_ms(200);
    }

    sleep_ms(3500);
    Oled_Image(truck_bmp);

    sleep_ms(5000);
    Oled_FillScreen(0x00);
    Oled_SetFont(Terminal12x16, 12, 16, 32 ,127);
    Oled_ResetScroll();
    for(k=0; k<500; k++) {
        Oled_ConstTextScroll("This is a new scroll function  ");
        sleep_ms(50);
    }

    Oled_FillScreen(0x00);
    i=10; j=0;
    Oled_ResetScroll();
    while(1) {
        Oled_SetFont(Terminal12x16, 12, 16, 32,127); 
        Oled_ConstTextScroll("The Serial Peripheral Interface (SPI) bus is a synchronous serial data communication bus that operates in Full-Duplex mode.   ");
        if(i==10) { 
            sprintf(buffer2,"%03d",j);
            Oled_SetFont(Segment_25x40, 25, 40, 46, 58);
            Oled_Text(buffer2, 26, 3); 
            if(j==120) {
                j = 0;
            } else {
                j++;
            }
            i=0;
        }
        sleep_ms(50);
        i++;
    }
    
    while(1){}
    
}
