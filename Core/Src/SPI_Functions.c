/*
 * SPI_Functions.c
 *
 *  Created on: Aug 2, 2023
 *      Author: AnastasII
 */

#include "SPI_Functions.h"
#include <IRQ.h>

extern GLOBAL_TIME TIME;
#define CS_ON	GPIOA->BSRR |= GPIO_BSRR_BR4;
#define CS_OFF	GPIOA->BSRR |= GPIO_BSRR_BS4;

void SPI_init(){

	SPI1->CR1 &= ~SPI_CR1_SPE;				//Выкл. SPI

	//RCC
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;		//Альтернативный вывод пина
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;		//Вкл. тактирование SPI
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;		//Вкл. тактирование порта A

	/*GPIO
	 * NSS(CS) 	-> 	PA4	General push-pull
	 * SCK 		-> 	PA5 Alternative func. push-pull
	 * MISO		->	PA6 Input floating/input pull-up
	 * MOSI		->	PA7 Alternative func. push-pull
	 * */

	//SCK
	GPIOA->CRL |= GPIO_CRL_MODE5;			//MAX 50MHz			|1|1|
	GPIOA->CRL &= ~GPIO_CRL_CNF5;			//Empty reg.	 	|0|0|
	GPIOA->CRL |= GPIO_CRL_CNF5_1;			//Al.func push-pull |1|0|
	//MISO
	GPIOA->CRL &= ~GPIO_CRL_MODE6;			//mode 				|0|0|
	GPIOA->CRL &= ~GPIO_CRL_CNF6;			//Empty reg.	 	|0|0|
	GPIOA->CRL |= GPIO_CRL_CNF6_1;			//Input pull-up 	|1|0|
	GPIOA->CRL |= GPIO_ODR_ODR6;			//??				|1|
	//MOSI
	GPIOA->CRL |= GPIO_CRL_MODE7;			//MAX 50MHz			|1|1|
	GPIOA->CRL &= ~GPIO_CRL_CNF7;			//Empty reg.	 	|0|0|
	GPIOA->CRL |= GPIO_CRL_CNF7_1;			//Al.func push-pull |1|0|
	//NSS(CS)
	GPIOA->CRL |= GPIO_CRL_MODE4;			//MAX 50MHz			|1|1|
	GPIOA->CRL &= ~GPIO_CRL_CNF4;			//General push-pull	|0|0|
	CS_OFF;

	//SPI_CR1
	SPI1->CR1 &= ~SPI_CR1_BR;				//Делитель(f/2) скорости шины  => 000 => 18MBits/s
	SPI1->CR1 |= SPI_CR1_CPHA;				//С первого тика -> начало передачи данных  =>  с положения 1
	SPI1->CR1 &= ~SPI_CR1_CPOL;				//С какого положения будет начинаться такт передачи данных  => 0

	SPI1->CR1 &= ~SPI_CR1_DFF;				//Размер посылки 8бит => 0
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;			//Сначала передаются первые 4 бита => 0
	SPI1->CR1 |= SPI_CR1_SSM;				//Вкл. программный Chip_select => 1
	SPI1->CR1 |= SPI_CR1_SSI;				//Вкл. программный Chip_select => 1
	SPI1->CR1 |= SPI_CR1_MSTR;				//Мастер => 1

	//SPI_CR2
	SPI1->I2SCFGR &= ~SPI_I2SCFGR_I2SMOD;	//Режим SPI !I2S

	SPI1->CR1 |= SPI_CR1_SPE;				//Вкл. SPI
}

SPI_STATUS SPI_Transmit(SPI_TypeDef* SPI, uint8_t* data, uint16_t size, uint32_t time){

	static uint32_t	timeout = 0;
	CS_ON;
	//SysTick_Config(TimerTick);
	if(!(SPI->SR & SPI_SR_BSY)){				//Проверка занятости интерфейса

		SPI->DR = *data;						//Добавление данных в регстр
		for(uint16_t i = 0; i < size; ++i){
			timeout = TIME.ms;
			while(!(SPI->SR & SPI_SR_TXE)){
				timeout = TIME.ms - timeout;
				if(timeout > time)
					return TIMEOUT;
			}
			SPI->DR = *(data+i);
		}

		timeout = TIME.ms;
		while(!(SPI->SR & SPI_SR_TXE)){
			timeout = TIME.ms - timeout;
			if(timeout > time)
				return TIMEOUT;
		}

		timeout = TIME.ms;
		while(SPI->SR & SPI_SR_BSY){
			timeout = TIME.ms - timeout;
			if(timeout > time)
				return TIMEOUT;
		}

		CS_OFF;
		return OK;
	}
	else
		return BUSY;
}
