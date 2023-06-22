/*
 * I2C.c
 *
 *  Created on: 20 июн. 2023 г.
 *      Author: Sokolov EvgenII
 */

#include "stm32f103xb.h"

void I2C_init(){
/*включение тактирования портов для интерфейса*/
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;		//Включил тактирование на шине с интрейсом
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;		//Включил тактирование пинов GPIOB

 /* Настройка пина Alternative func.open drain
  * SCL -> I2C clock => PB6
  * SDA -> I2C Data I/O => PB7*/
    GPIOB->CRL |= GPIO_CRL_CNF6;	//Open-drain
    GPIOB->CRL |= GPIO_CRL_MODE6;	//Alternative func Макс 10МГц т.к частота шины 24MHz
    GPIOB->CRL |= GPIO_CRL_CNF7;
    GPIOB->CRL |= GPIO_CRL_MODE7;

    /*Настройка I2C*/

    I2C1->CR1 &= ~I2C_CR1_PE;		//Отключаю интерфейс для его настройки
    I2C1->CR1 |= I2C_CR1_SWRST;		//Перезагружаю
    I2C1->CR1 &= ~I2C_CR1_SWRST;	//Действия аналогично HAL
    I2C1->CR2 |= 0x18; 			//HEX(18) = 24MHz шины APB1
    //I2C1->TRISE =
}
