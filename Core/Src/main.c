/*
 * main.c
 *
 *  Created on: Mar 23, 2023
 *      Author: Sokolov EvgenII
 */

/******************Includes*********************/

#include "stm32f103xb.h"
#include "RCC.h"
//#include "SPI_Functions.h"
//#include "LCD_1602.h"

#define Enable_RTOS	0

#if Enable_RTOS
    #include "FreeRTOS.h"
    #include "task.h"
    #include "queue.h"
#endif


/************Functions declaration**************/

uint32_t GetTime(void);
void SysTick_Handler(void);
void Sys_clock(void);
void GPIO_init(void);
void ILI_9341_init();
void RCC_init();
//void I2C_init();
//void LCD_init();
//void delay_time();
//void vLed_Task(void *argument);
//void init_dma();

//void WriteToUART();
//void MCO(void);
//void SPI_init(void);

/*********************MAIN**********************/

int main(){
    Sys_clock();
//    GPIO_init();
    RCC_init();
    ILI_9341_init();
//    I2C_init();
//    LCD_init();
//    init_dma();

//    SPI_init();
//    uint8_t	vector[2] = {0xFF, 0xC3};

    while(1){
//    	SPI_Transmit(SPI1, vector, 4, 100);
//        GPIOC->BSRR |= GPIO_BSRR_BS13;
    }

}

//void init_dma(){
//
//    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
//
//    DMA1_Channel7->CPAR = (uint32_t)&USART2->DR;
//    DMA1_Channel7->CPAR = (uint32_t)buffer;
//
//    USART2->CR3		|= USART_CR3_DMAT;
//}
//
//void WriteToUART(){
//
//    DMA1_Channel7->CCR &= ~DMA_CCR_EN;
//    DMA1_Channel7->CNDTR = (sizeof(buffer)-1);
//    DMA1->IFCR = DMA_IFCR_CGIF4;
//    DMA1_Channel7->CCR |= DMA_CCR_EN;
//}



void GPIO_init(){

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;				//Тактирование
    GPIOC->CRH &= ~GPIO_CRH_CNF13;					//обнуление регистра CNF
    GPIOC->CRH |= GPIO_CRH_MODE13_0;				//настройка для push-pull
}

//void vLed_Task(void *argument){
//
//    while(1){
//
//		GPIOC->BSRR |= GPIO_BSRR_BS13;
//		vTaskDelay(1000);
//		GPIOC->BSRR |= GPIO_BSRR_BR13;
//		vTaskDelay(1000);
//    }
//}
//



