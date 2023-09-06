/*
 * LCD_1602.h
 *
 *  Created on: 23 июн. 2023 г.
 *      Author: Sokolov EvgenII
 */

#ifndef INC_LCD_1602_H_
#define INC_LCD_1602_H_

#include "stm32f1xx.h"

ErrorStatus LCD_init(void);
ErrorStatus LCD_Scan(uint8_t address);

#endif /* INC_LCD_1602_H_ */
