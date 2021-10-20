/*
 * File:   main.c
 * Author: |H_e_c_t_o_r|
 * 
 * V2.0
 *    Planned new features
 *      1. Simple windowing system
 *      2. Change underlying mode to regular dump of an in-memory buffer
 *         rather than writing directly to screen pixels.
 */
#include "mbed.h"
#include "OLED_128X64.h"
#include "font.h"
#include "bitmap.h"

DigitalOut myled(LED1);

OLED_128X64 oled(p8 /* cs */, p9 /* reset */, p11 /* dc */, p7 /* clock */, p5 /* data */); // LPC1768

int main(void)
{
unsigned char i, j; 
unsigned int k;
char buffer2[20];

    oled.Oled_Init();

    oled.Oled_SetFont(Terminal12x16, 12, 16, 32,127);
    oled.Oled_ConstText("library for", 0, 0);
    oled.Oled_ConstText("Graphic", 0, 2);
    oled.Oled_ConstText("OLED 128x64", 0, 4);
    oled.Oled_ConstText("SSD1306", 0, 6);
    wait_ms(3000);

    oled.Oled_FillScreen(0x00);
    oled.Oled_ConstText("lines", 30, 0);
    for(i=16; i<64; i=i+4) {
        oled.Oled_Line(0, 16, 127, i, BLACK);
        wait_ms(500);
    }
    wait_ms(3000);

    oled.Oled_FillScreen(0x00);
    oled.Oled_ConstText("Circles", 10, 0);
    for(i=1; i<16; i=i+3) {
        oled.Oled_Circle(63, 31, i, BLACK);
        wait_ms(500);
    }
    wait_ms(3000);

    oled.Oled_FillScreen(0x00);
    oled.Oled_ConstText("Rectangles", 0, 0);
    for(i = 0; i < 15; i = i + 4) {
        oled.Oled_Rectangle(16+i, 16+i, 112-i, 46-i, BLACK);
        wait_ms(500);
    }
    wait_ms(3000);

    oled.Oled_FillScreen(0x00);
    oled.Oled_ConstText("  Inverts  ", 0, 0);
    for(i=0; i<8; i++) {
        oled.Oled_InvertRam(0, 0, 127, 7);
        wait_ms(1500);
    } 

    wait_ms(1000);
    oled.Oled_FillScreen(0x00);
    oled.Oled_ConstText("Main Menu", 8, 0);
    oled.Oled_Icon(icon1,20,3,32,32); 
    oled.Oled_Icon(icon2,72,3,32,32); wait_ms(3000);
    oled.Oled_Icon(icon3,20,3,32,32); 
    oled.Oled_Icon(icon4,72,3,32,32); wait_ms(3000);

    wait_ms(1000);
    oled.Oled_FillScreen(0x00);
    oled.Oled_ConstText("Fonts", 35, 0);
    for(i=0; i<113; i++) {
        sprintf(buffer2,"%03d",i);
        oled.Oled_SetFont(Segment_25x40, 25, 40, 46, 58);
        oled.Oled_Text(buffer2, 0, 3);
        oled.Oled_SetFont(Terminal12x16, 12, 16, 32 ,127);
        oled.Oled_Text(buffer2, 90, 3);
        oled.Oled_SetFont(Font_6x8, 6, 8, 32, 127);
        oled.Oled_Text(buffer2, 99, 6);
        wait_ms(200);
    }

    wait_ms(3000);
    oled.Oled_Image(truck_bmp);

    wait_ms(5000);
    oled.Oled_FillScreen(0x00);
    oled.Oled_SetFont(Terminal12x16, 12, 16, 32 ,127);
    oled.Oled_ResetScroll();
    for(k=0; k<500; k++) {
        oled.Oled_ConstTextScroll("This is a new scroll function  ");
        wait_ms(50);
    }

    oled.Oled_FillScreen(0x00);
    i=10; j=0;
    oled.Oled_ResetScroll();
    while(1) {
        oled.Oled_SetFont(Terminal12x16, 12, 16, 32,127); 
        oled.Oled_ConstTextScroll("The Serial Peripheral Interface (SPI) bus is a synchronous serial data communication bus that operates in Full-Duplex mode.   ");
        if(i==10) { 
            sprintf(buffer2,"%03d",j);
            oled.Oled_SetFont(Segment_25x40, 25, 40, 46, 58);
            oled.Oled_Text(buffer2, 26, 3); 
            if(j==120) {
                j = 0;
            } else {
                j++;
            }
            i=0;
        }
        wait_ms(50);
        i++;
    }
    
    while(1){}
}
