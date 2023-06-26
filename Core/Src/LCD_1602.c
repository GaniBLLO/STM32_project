/*
 * LCD_1602.c
 *
 *  Created on: 23 июн. 2023 г.
 *      Author: Sokolov EvgenII
 */

#include "stdint.h"

void LCD_Scan(uint16_t address){

    for(uint16_t addr = 0; addr < 127; addr++){

//	return 1;
    }
//    return 0;
}

void LCD_init(){
    uint16_t addr = 0x0;
    LCD_Scan(addr);
}


