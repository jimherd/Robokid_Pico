//
// TMC7300

#include "TMC7300.h"



void  TMC7300_Init(void) {
}

uint8_t TMC7300_CRC8(uint8_t *data, uint32_t bytes) {

uint8_t crc = 0;
    while(--bytes) {
        crc = crc_table[crc ^ *data++];
    }
    return crc;

}