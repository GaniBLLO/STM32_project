/*
 * I2C.c
 *
 *  Created on: 20 июн. 2023 г.
 *      Author: Sokolov EvgenII
 */

#include "stm32f103xb.h"
#include <IRQ.h>

void I2C_init(){
/*включение тактирования портов для интерфейса*/
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;		//Включил тактирование на шине с интрейсом
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;		//Вкл. тактирование алтернативной функции
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;		//Включил тактирование пинов GPIOB

 /* Настройка пина Alternative func.open drain
  * SCL -> I2C clock => PB6
  * SDA -> I2C Data I/O => PB7*/
    GPIOB->CRL |= GPIO_CRL_CNF6;	//Open-drain
    GPIOB->CRL &= ~GPIO_CRL_CNF6;	//Обнулил регистр
    GPIOB->CRL |= GPIO_CRL_MODE6;	//Alternative func Макс 50МГц т.к частота шины 24MHz

    GPIOB->CRL |= GPIO_CRL_CNF7;
    GPIOB->CRL &= ~GPIO_CRL_CNF7;
    GPIOB->CRL |= GPIO_CRL_MODE7;

    /*Настройка I2C по умолчанию все регистры равны нулю ToDo проверить так ли это? на примере OAR1/2?*/
    /*Формула Tclk = 1ns/24MHz = 24ns
     * SM = 1000ns | FM = 300ns
     * Выбран StandartMode
     * TRISE = (SM/Tclk) +1 => 25 = 0x19
     * CCR = Tsm(sm mode freq = 100kHz)/2*Tclk(1/24MHz) = 120 => 0x7A*/

    I2C1->CR1 &= ~I2C_CR1_PE;		//Отключаю интерфейс для его настройки
    I2C1->CR1 |= I2C_CR1_SWRST;		//Перезагружаю
    delay_time(10);
    //тут должна быть пауза
    I2C1->CR1 &= ~I2C_CR1_SWRST;	//Действия аналогично HAL
    delay_time(10);
    // и тут пауза

    I2C1->CR2 = 0x24; 			//HEX(24) = 36MHz шины APB1
    I2C1->TRISE = 0x25;			//Время нарастания фронта сигнала

    I2C1->CCR &= ~I2C_CCR_FS;		//Настройка режима мастер SM = 0
    I2C1->CCR = 0x7A;			//Задаю тактирование для SCL

    I2C1->CR1 |= I2C_CR1_PE;		//Включение интерфейса
}
