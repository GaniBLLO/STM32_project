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

 /* Настройка пина
  * SCL -> I2C clock 	=> PB6	Alternative func.open drain
  * SDA -> I2C Data I/O => PB7	Alternative func.open drain*/
    GPIOB->CRL &= ~GPIO_CRL_CNF6;	//Обнулил регистр
    GPIOB->CRL |= GPIO_CRL_CNF6;	//Open-drain
    GPIOB->CRL |= GPIO_CRL_MODE6;	//Alternative func Макс 50МГц т.к частота шины

    GPIOB->CRL &= ~GPIO_CRL_CNF7;
    GPIOB->CRL |= GPIO_CRL_CNF7;
    GPIOB->CRL |= GPIO_CRL_MODE7;

    /*Настройка I2C по умолчанию все регистры равны нулю ToDo проверить так ли это? на примере OAR1/2?*/
    /*Формулы
     * Tclk = 1ns/24MHz = 24ns
     * SM = 1000ns | FM = 300ns
     * Выбран StandartMode
     * TRISE = (SM/Tclk) +1 => 0x25
     * CCR = Tsm(36MHz - частота шины APB)/2*10kHz - стандратная скорость = 180 => 0xB4*/

    I2C1->CR1 &= ~I2C_CR1_PE;		//Отключаю интерфейс для его настройки
    I2C1->CR1 |= I2C_CR1_SWRST;		//Перезагружаю для обнуления регистров
    delay_time(5);
    I2C1->CR1 &= ~I2C_CR1_SWRST;	//Действия аналогично HAL
    delay_time(5);
    I2C1->CR1 &= ~I2C_CR1_SMBUS;	//Режим I2C

    I2C1->CR2 = 0x24; 				//HEX(24) = 36MHz (MAX для шины APB1)

    I2C1->CCR &= ~I2C_CCR_FS;		//Включил стандартный режи работы интерфейса
    I2C1->CCR = 0xB4;				//Задаю тактирование для SCL
    I2C1->TRISE = 0x25;				//Время нарастания фронта сигнала

    I2C1->CR1 |= I2C_CR1_PE;		//Включение интерфейса
}

uint8_t I2C_send(uint8_t address, uint8_t command){

    uint8_t f_ready = 0;
    I2C1->CR1 &= ~I2C_CR1_POS;		/*Этот бит ставится что бы показать,
					 	 	 	 	 *что след.бит будет принят в регистр -> DR
					 	 	 	 	 *для его дальнейшего смещения*/
    I2C1->CR1 |= I2C_CR1_START;		//Генерируем стартовый бит
    while(!(I2C1->SR1 & I2C_SR1_SB));	//Ждём пока регситр не сгенерирует бит старта. 0 => ждём... 1 = > готово!

    I2C1->DR = address & (uint8_t)(~I2C_OAR1_ADD0);	//В сдвиговый регистр добавляю адрес устройства


    return f_ready;
}
