/*
 * main.c
 *
 *  Created on: Mar 23, 2023
 *      Author: Sokolov EvgenII
 */

/******************Includes*********************/

#include "stm32f103xb.h"
#include "timing_file.h"
#include "RCC.h"
#include "LCD_1602.h"

#define Enable_RTOS	1


#if Enable_RTOS
    #include "FreeRTOS.h"
    #include "task.h"
    #include "queue.h"
#endif


/************Functions declaration**************/

void RCC_init();
void I2C_init();
//void LCD_init();
//void delay_time();
void vLed_Task(void *argument);
void init_dma();
void MCO();
void WriteToUART();
void GPIO_init();


char buffer[] = "Hello, World!\r\n";

/*********************MAIN**********************/

int main(){


    //Sys_clock();
    RCC_init();
    I2C_init();
//    LCD_init();
//    init_dma();
    GPIO_init();

    xTaskCreate( vLed_Task, "Toggle_Led_PC13", 32, NULL, 1, NULL);

    vTaskStartScheduler();
    while(1){


    }

}

void init_dma(){

    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    DMA1_Channel7->CPAR = (uint32_t)&USART2->DR;
    DMA1_Channel7->CPAR = (uint32_t)buffer;

    USART2->CR3		|= USART_CR3_DMAT;
}

void WriteToUART(){

    DMA1_Channel7->CCR &= ~DMA_CCR_EN;
    DMA1_Channel7->CNDTR = (sizeof(buffer)-1);
    DMA1->IFCR = DMA_IFCR_CGIF4;
    DMA1_Channel7->CCR |= DMA_CCR_EN;
}


void MCO(){

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;		//Включение тактирование шины APB2, где есть вывод MCO

    GPIOA->CRH &= ~GPIO_CRH_CNF8_0;

    RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;
}

void Sys_clock(){

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void GPIO_init(){

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;	//Тактирование
    GPIOC->CRH &= ~GPIO_CRH_CNF13;	//обнуление регистра CNF
    GPIOC->CRH |= GPIO_CRH_MODE13_0;	//настройка для push-pull
}

void vLed_Task(void *argument){

    while(1){
	GPIOC->BSRR |= GPIO_BSRR_BS13;
	vTaskDelay(1000);
	GPIOC->BSRR |= GPIO_BSRR_BR13;
	vTaskDelay(1000);
    }
}
