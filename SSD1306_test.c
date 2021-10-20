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

int main() {

    Oled_Init();

    Oled_SetFont(Terminal12x16, 12, 16, 32,127);
    Oled_ConstText("library for", 0, 0);
    Oled_ConstText("Graphic", 0, 2);
    Oled_ConstText("Oled 128x64", 0, 4);
    Oled_ConstText("SSD1306  ", 0, 6);

    
}
