/*
 * timing_file.c
 *
 *  Created on: Jun 13, 2023
 *      Author: Sokolov EvgenII
 */
#include <IRQ.h>
GLOBAL_TIME	TIME = GLOBAL_TIME_DEFAULT;
static uint32_t TICK = 0;


void delay_time(uint32_t time){

    uint32_t tick_start;
    uint32_t w_8 = time;
    tick_start = GetTick();

    if(w_8 < MAX_TIME)
	w_8 += (uint32_t)(0x1);
    while((GetTick() - tick_start) < w_8 );
}

uint32_t GetTick(void){
    return TICK;
}

void SysTick_Handler(){
    TICK++;
}

void TIM3_IRQHandler(void){
    if(TIM3->SR & TIM_SR_UIF)
	TIM3->SR &= ~TIM_SR_UIF;
    TIME.ms++;
    if(TIME.ms == 1000){
	    TIME.ms = 0;
	    TIME.sec++;
    }
    else if(TIME.ms > 1001){
	    //todo ERR!
    }
    if(TIME.sec == 60){
	    TIME.sec = 0;
	    TIME.min++;
    }
    if(TIME.min == 60){
	    TIME.min = 0;
	    TIME.hr++;
    }
}

void DMA1_Channel1_IRQHandler(void){

    extern uint16_t buff[4];
    if(DMA1->ISR & DMA_ISR_TCIF1){		//Если прерывание после удачной передачи данных
	DMA1->IFCR = DMA_IFCR_CGIF1;		//Снимаю флаг успешной передачи
	TIM3->CCR4 = (uint32_t)buff[0];
	GPIOC->BSRR |= GPIO_BSRR_BS13;
    }
    if(DMA1->ISR & DMA_ISR_TEIF1){		//Если прерывание после неудачной передачи данных
	DMA1->IFCR = DMA_IFCR_CTEIF1;		//Снятие флага об ошибке передачи todo выполнить обработку ошибки
    }
}
