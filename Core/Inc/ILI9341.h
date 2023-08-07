/*
 * ILI9341.h
 *
 *  Created on: 6 авг. 2023 г.
 *      Author: AnastasII
 */
#include "stm32f103xb.h"
#include "main.h"

#ifndef ILI9341_H_
#define ILI9341_H_


typedef	union{
	uint8_t	all;
	struct{
		uint8_t	D_0:	1;
		uint8_t	D_1:	1;
		uint8_t	D_2:	1;
		uint8_t	D_3:	1;
		uint8_t	D_4:	1;
		uint8_t	D_5:	1;
		uint8_t	D_6:	1;
		uint8_t	D_7:	1;
	}bit;
}D_ARR;

#define D_DEFAULT  {0x0}

void ILI_Reset(uint32_t cmd);
void ILI_9341_init();
void GPIO_Init();
#endif /* ILI9341_H_ */