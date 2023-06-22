/*
 * RCC.c
 *
 *  Created on: Jun 19, 2023
 *      Author: Sokolov EvgenII
 */
#include "stm32f103xb.h"

void RCC_init(){
    RCC->CR |= ((uint32_t) RCC_CR_HSEON);	//Включение кварца
    while (!(RCC->CR & RCC_CR_HSERDY));		//Жду включение кварца.тактирования

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;		//Задаю тактирование общей шины AHB 48 - 72MHz...
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;		//Тактирование шины APB1..
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;		//Тактирование шины APB2.

    RCC->CFGR &= ~RCC_CFGR_PLLMULL;		///Множители и делители приравниваю к 0
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;		//Делитель для тактирования (после PLL Source mux)
    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;		//Делитель для тактирования HSE (После "HSE") => 1

    RCC->CFGR |= RCC_CFGR_PLLSRC;		//PLL Source MUX
    RCC->CFGR |= RCC_CFGR_PLLXTPRE;		//Делитель для тактирования HSE/2
    RCC->CFGR |= RCC_CFGR_PLLMULL6;		//Множитель PLL = 6

    RCC->CR |= RCC_CR_PLLON;			//Включение Множителя PLL
    while((RCC->CR & RCC_CR_PLLRDY) == 0);

    RCC->CFGR &= ~RCC_CFGR_SW;			//System clock mux
    RCC->CFGR |= RCC_CFGR_SW_1;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1);	//Жду пока включится
}
