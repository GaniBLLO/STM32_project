/*
 * LCD_1602.c
 *
 *  Created on: 23 июн. 2023 г.
 *      Author: Sokolov EvgenII
 */

#include "stdint.h"
#include "LCD_1602.h"
#define LCD_ADDRESS	0x37

ErrorStatus LCD_Scan(uint8_t address){

    for(uint8_t addr = 0; addr < 255; ++addr){

    }
    return SUCCESS;
}

ErrorStatus LCD_1602_init(void){

    LCD_Scan(LCD_ADDRESS);

    return SUCCESS;
}


