/*
 * RCC.c
 *
 *  Created on: Jun 19, 2023
 *      Author: Sokolov EvgenII
 */
#include "stm32f103xb.h"

#define SYSCLOCK	360000000U		//Частота процессора

void RCC_init(){

	/*Задаётся тактирование HCLK = 36MHz*/
    RCC->CR |= ((uint32_t) RCC_CR_HSEON);	//Включение кварца
    while (!(RCC->CR & RCC_CR_HSERDY));		//Жду включение кварца.тактирования

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;		//Задаю тактирование общей шины AHB 48 - 72MHz...
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;		//Тактирование шины APB1..
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;		//Тактирование шины APB2.

    RCC->CFGR &= ~RCC_CFGR_PLLMULL;			//Множители и делители приравниваю к 0
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;			//Делитель для тактирования (после PLL Source mux)
    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;		//Делитель для тактирования HSE (После "HSE") => 1

    RCC->CFGR |= RCC_CFGR_PLLSRC;			//PLL Source MUX
    RCC->CFGR |= RCC_CFGR_PLLXTPRE;			//Делитель для тактирования HSE/2
    RCC->CFGR |= RCC_CFGR_PLLMULL9;			//Множитель PLL = 9

    RCC->CR |= RCC_CR_PLLON;				//Включение Множителя PLL
    while((RCC->CR & RCC_CR_PLLRDY) == 0);

    RCC->CFGR &= ~RCC_CFGR_SW;				//System clock mux
    RCC->CFGR |= RCC_CFGR_SW_1;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1);	//Жду пока включится
}


void MCO(){

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;		//Включение тактирование шины APB2, где есть вывод MCO

    GPIOA->CRH &= ~GPIO_CRH_CNF8_0;

    RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;
}

void Sys_clock(){

    SysTick->LOAD &= ~SysTick_LOAD_RELOAD_Msk;
    SysTick->VAL &= ~SysTick_VAL_CURRENT_Msk;
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;		//Выкл. выключенного счётчика

    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;		//Вкл. отсчёта до нуля
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;	//Источник синхронизации без делителя 24MHz

    SysTick->LOAD = 35999;				//Задаю значение с которого будет отсчёт счётчика

    SysTick->VAL = 35999;				//Задаю текущее значение счётчика

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;		//Вкл. счётчик
}
