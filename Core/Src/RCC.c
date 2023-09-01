/*
 * RCC.c
 *
 *  Created on: Jun 19, 2023
 *      Author: Sokolov EvgenII
 */
#include "stm32f103xb.h"
#include "stm32f1xx.h"

#define F_CPU 		72000000UL	// Тактовая у нас 72МГЦ
#define TimerTick  	F_CPU/1000-1	// Нам нужен килогерц

void RCC_init(){

    /*Задаётся тактирование HCLK = 72MHz*/

    RCC->CR |= RCC_CR_HSEON;			//Включение кварца HSE 8MHz
    while (!(RCC->CR & RCC_CR_HSERDY));		//Жду включение кварца.тактирования

//    RCC->CR |= RCC_CR_HSION;			//Включение кварца HSI 8MHz
//    while (!(RCC->CR & RCC_CR_HSIRDY));		//Жду включение кварца.тактирования

//    RCC->CR |= RCC_CR_CSSON;

    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 2 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;		//Задал делитель для шины AHB ->/1 => 72/1 = 72MHZ MAX!!
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;		//Задал делитель для шины APB1 ->/2 => 72/2 = 36MHZ MAX!!
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;		//Задал делитель для шины APB2 ->/1 => 72/1 = 72MHZ MAX!!

    RCC->CFGR &= ~RCC_CFGR_PLLSRC;			//Делитель для тактирования (после PLL Source mux)
    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;		//Делитель для тактирования HSE (После "HSE") => 1
    RCC->CFGR &= ~RCC_CFGR_PLLMULL;			//Множители и делители приравниваю к 0

    RCC->CFGR |= RCC_CFGR_PLLSRC;			//делитель перед PLL Source MUX HSE генератора
    RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE;		//Делитель для тактирования HSE/2 перед PLL S_MUX ToDO Проверить т.к он уже отключён
    RCC->CFGR |= RCC_CFGR_PLLMULL9;		//Множитель PLL = 9

    //ADC
    RCC->CFGR &= ~RCC_CFGR_ADCPRE;		//Обнулить значение делителя для АЦП /2
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;		//Задаю делитель для ацп = |1|0| = /6 => 72/6MHz = 12MHz < 18MHz(MAX)

    RCC->CR |= RCC_CR_PLLON;			//Включение Множителя PLL
    while((RCC->CR & RCC_CR_PLLRDY) == 0);

    RCC->CFGR &= ~RCC_CFGR_SW;					//System clock mux
    RCC->CFGR |= RCC_CFGR_SW_PLL;				//RCC_CFGR_SW_1;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);	//Жду пока включится
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

    SysTick->LOAD = TimerTick;				//Задаю значение с которого будет отсчёт счётчика

    SysTick->VAL = TimerTick;				//Задаю текущее значение счётчика

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;		//Вкл. счётчик
}

void TIMx_init(void){

    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;	//Вкл. тактирования таймера
    /*TIM2 APB1 (MAX 36MHz)
     *GPIO
     *PB1 -> TIM3_CH4 Output compare channel <-> Alternative function push pull*/
    //PB1
    GPIOB->CRL &= ~GPIO_CRL_CNF1;	//Обязательная очистка регистра
    GPIOB->CRL |= GPIO_CRL_CNF1_1;	//|1|0| - Alternative function push pull
    GPIOB->CRL |= GPIO_CRL_MODE1;	//|1|1| - Mode MAX 10MHz toDo поменять на 50 МГц

    //TIM3
    TIM3->CR1 &= ~TIM_CR1_OPM;		//Счётчик NE остановится когда произойдёт событие
    TIM3->CR1 &= ~TIM_CR1_DIR;		//Счётчик считает вверх
    TIM3->CR1 &= ~TIM_CR1_CMS;		//Выравнивание работает как задан DIR.
    TIM3->CR1 |= TIM_CR1_ARPE;		//Автоперегрузка таймера
    TIM3->CR1 &= ~TIM_CR1_CKD;		//Множитель для счётчика х1

    TIM3->DIER |= TIM_DIER_UIE;		//Вкл. IRQ

    TIM3->PSC = 2;//1;//719-1;
    TIM3->ARR = 999;//35999;//999;//50000-1;//;

    NVIC_EnableIRQ(TIM3_IRQn);
    TIM3->CR1 |= TIM_CR1_CEN;		//Включения счётчика

    //PWM Output for PB1 - > PWM
    TIM3->CCMR2 &= ~TIM_CCMR2_CC4S;	//Включаю для 4ого канала вывод ШИМ. Режим захвата и сравнения
    TIM3->CCMR2 &= ~TIM_CCMR2_OC4FE;	//Включаю для 4ого канала вывод ШИМ. Режим захвата и сравнения
    TIM3->CCMR2 |= TIM_CCMR2_OC4PE;	//Режим переодичности ШИМа
    TIM3->CCMR2 |= 6UL << TIM_CCMR2_OC4M_Pos;//(TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1);	//Режим 110
    TIM3->CCMR2 &= ~TIM_CCMR2_OC4CE;	//

    //PWM ON
    TIM3->CCER |= TIM_CCER_CC4E;
    TIM3->CCER |= TIM_CCER_CC4P;
}
