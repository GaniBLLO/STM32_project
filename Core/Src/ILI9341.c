/*
 * ILI9341.c
 *
 *  Created on: 6 авг. 2023 г.
 *      Author: AnastasII
 */
#include "ILI9341.h"
#include <IRQ.h>
#define RST_ON	GPIOB->BSRR = GPIO_BSRR_BR0;
#define RST_OFF	GPIOB->BSRR = GPIO_BSRR_BS0;

#define CS_ON	GPIOB->BSRR = GPIO_BSRR_BR1;
#define CS_OFF	GPIOB->BSRR = GPIO_BSRR_BS1;

#define RSx_ON	GPIOB->BSRR = GPIO_BSRR_BR10;
#define RSx_OFF	GPIOB->BSRR = GPIO_BSRR_BS10;

#define WR_ON	GPIOB->BSRR = GPIO_BSRR_BR11;
#define WR_OFF	GPIOB->BSRR = GPIO_BSRR_BS11;

#define RD_ON	GPIOB->BSRR = GPIO_BSRR_BR12;
#define RD_OFF	GPIOB->BSRR = GPIO_BSRR_BS12;



D_ARR	D	=	D_DEFAULT;

void GPIO_Init(){
	//RCC
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	GPIOA->ODR = 0x0;
	GPIOB->ODR = 0x0;
	//GPIO
	/* D[0:7] => 0
	 * D0	->	PA5
	 * D1	->	PA6
	 * D2	->	PA7
	 * D3	->	PA8
	 * D4	->	PA9
	 * D5	->	PA10
	 * D6	->	PA11
	 * D7	->	PA12	*/
	//D0
	GPIOA->CRL |= GPIO_CRL_MODE5;
	GPIOA->CRL &= ~GPIO_CRL_CNF5;
	GPIOA->BSRR |= GPIO_BSRR_BR5;
	//D1
	GPIOA->CRL |= GPIO_CRL_MODE6;
	GPIOA->CRL &= ~GPIO_CRL_CNF6;
	GPIOA->BSRR |= GPIO_BSRR_BR6;
	//D2
	GPIOA->CRL |= GPIO_CRL_MODE7;
	GPIOA->CRL &= ~GPIO_CRL_CNF7;
	GPIOA->BSRR |= GPIO_BSRR_BR7;
	//D3
	GPIOA->CRH |= GPIO_CRH_MODE8;
	GPIOA->CRH &= ~GPIO_CRH_CNF8;
	GPIOA->BSRR |= GPIO_BSRR_BR8;
	//D4
	GPIOA->CRH |= GPIO_CRH_MODE9;
	GPIOA->CRH &= ~GPIO_CRH_CNF9;
	GPIOA->BSRR |= GPIO_BSRR_BR9;
	//D5
	GPIOA->CRH |= GPIO_CRH_MODE10;
	GPIOA->CRH &= ~GPIO_CRH_CNF10;
	GPIOA->BSRR |= GPIO_BSRR_BR10;
	//D6
	GPIOA->CRH |= GPIO_CRH_MODE11;
	GPIOA->CRH &= ~GPIO_CRH_CNF11;
	GPIOA->BSRR |= GPIO_BSRR_BR11;
	//D7
	GPIOA->CRH |= GPIO_CRH_MODE12;
	GPIOA->CRH &= ~GPIO_CRH_CNF12;
	GPIOA->BSRR |= GPIO_BSRR_BR12;

	/* Control PINS
	 * RST	->	PB0
	 * CS	->	PB1
	 * RSx	->	PB10
	 * WRx	->	PB11
	 * RDx	->	PB12*/
	//RST
	GPIOB->CRL |= GPIO_CRL_MODE0;
	GPIOB->CRL &= ~GPIO_CRL_CNF0;
	GPIOB->BSRR |= GPIO_BSRR_BS0;
	//CS
	GPIOB->CRL |= GPIO_CRL_MODE1;
	GPIOB->CRL &= ~GPIO_CRL_CNF1;
	GPIOB->BSRR |= GPIO_BSRR_BS1;
	//RSx
	GPIOB->CRH |= GPIO_CRH_MODE10;
	GPIOB->CRH &= ~GPIO_CRH_CNF10;
	GPIOB->BSRR |= GPIO_BSRR_BS10;
	//WRx
	GPIOB->CRH |= GPIO_CRH_MODE11;
	GPIOB->CRH &= ~GPIO_CRH_CNF11;
	GPIOB->BSRR |= GPIO_BSRR_BS11;
	//RDx
	GPIOB->CRH |= GPIO_CRH_MODE12;
	GPIOB->CRH &= ~GPIO_CRH_CNF12;
	GPIOB->BSRR |= GPIO_BSRR_BS12;
}

void Send_Command(uint8_t command){
	D.all = command;

	CS_ON;
	delay_time(5);
	RSx_ON;
	WR_ON;

	GPIOA->ODR = (command << 5);
	delay_time(5);
//	if(D.bit.D_0)
//		GPIOA->BSRR = GPIO_BSRR_BS5;
//	else
//		GPIOA->BSRR = GPIO_BSRR_BR5;
//
//	if(D.bit.D_1)
//		GPIOA->BSRR = GPIO_BSRR_BS6;
//	else
//		GPIOA->BSRR = GPIO_BSRR_BR6;
//
//	if(D.bit.D_2)
//		GPIOA->BSRR = GPIO_BSRR_BS7;
//	else
//		GPIOA->BSRR = GPIO_BSRR_BR7;
//
//	if(D.bit.D_3)
//		GPIOA->BSRR = GPIO_BSRR_BS8;
//	else
//		GPIOA->BSRR = GPIO_BSRR_BR8;
//
//	if(D.bit.D_4)
//		GPIOA->BSRR = GPIO_BSRR_BS9;
//	else
//		GPIOA->BSRR = GPIO_BSRR_BR9;
//
//	if(D.bit.D_5)
//		GPIOA->BSRR = GPIO_BSRR_BS10;
//	else
//		GPIOA->BSRR = GPIO_BSRR_BR10;
//
//	if(D.bit.D_6)
//		GPIOA->BSRR = GPIO_BSRR_BS11;
//	else
//		GPIOA->BSRR = GPIO_BSRR_BR11;
//
//	if(D.bit.D_7)
//		GPIOA->BSRR = GPIO_BSRR_BS12;
//	else
//		GPIOA->BSRR = GPIO_BSRR_BR12;

	WR_OFF;
	RSx_OFF;
	CS_OFF;
	delay_time(220);
}


void ILI_Reset(){

	RST_ON;
	delay_time(1000);
	RST_OFF;
	delay_time(1000);
}

void ILI_9341_init(){
	GPIO_Init();

	RST_OFF;
	CS_OFF;
	RSx_OFF;
	WR_OFF;
	RD_OFF;

	ILI_Reset();

	Send_Command(0x1);		//Software reset
	delay_time(1000);

	Send_Command(0x10);		//Sleep mode
	Send_Command(0x28);		//Display off

}




