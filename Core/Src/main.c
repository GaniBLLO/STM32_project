/*
 * main.c
 *
 *  Created on: Mar 23, 2023
 *      Author: Sokolov EvgenII
 */

/******************Includes*********************/

#include "stm32f103xb.h"
#include "RCC.h"
#include "ILI9341.h"
#include "IRQ.h"
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
INIT_STATUS ILI_9341_init();
void RCC_init();
void ADC_Init();
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
    RCC_init();
    Sys_clock();
    GPIO_init();
//    I2C_init();

//    if(ILI_9341_init() != OK){
	//TODO ERR!
//    }
//    ADC_Init();
//    LCD_init();
//    init_dma();

//    SPI_init();
//    uint8_t	vector[2] = {0xFF, 0xC3};

    while(1){
//    	if(ADC1->SR & ADC_SR_EOC){
//    		ADC1->DR;
//    	}
	GPIOC->BSRR |= GPIO_BSRR_BR13;
	delay_time(50);
	GPIOC->BSRR |= GPIO_BSRR_BS13;
	delay_time(250);
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
    GPIOC->CRH &= ~GPIO_CRH_CNF13;				//обнуление регистра CNF
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


void ADC_Init(){
    //RCC
//    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;	т.к тактирование этого пина уже настроен в экрана
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    //GPIO
    /* PA0 -> ADC12_IN0
     * PA1 -> ADC12_IN1 */
    //PA0
    GPIOA->CRL &= ~GPIO_CRL_MODE0;
    GPIOA->CRL &= ~GPIO_CRL_CNF0;
    GPIOA->BSRR = GPIO_BSRR_BR0;
    //PA1
    GPIOA->CRL &= ~GPIO_CRL_MODE1;
    GPIOA->CRL &= ~GPIO_CRL_CNF1;
    GPIOA->BSRR = GPIO_BSRR_BR1;

    ADC1->CR1 = 0x0;				//todo Проверить, действительно ли регистры очистились
    ADC1->CR1 |= ADC_CR1_SCAN;			//Вкл. режима сканирования
    ADC1->CR1 |= (0x6 << ADC_CR1_DUALMOD_Pos);	//todo Узнать на что влияет

    ADC1->CR2 |= ADC_CR2_ADON;			//Вкл. АЦП
    ADC1->CR2 |= ADC_CR2_CONT;			//Режим непрерывного преобразования
    ADC1->CR2 |= ADC_CR2_CAL;			//Включить калибровку. Рек. перед включение ацп
    while(ADC1->CR2 & ADC_CR2_CAL);
    delay_time(2);

    ADC1->CR2 &= ~ADC_CR2_ALIGN;		//Выравнивнивание данных по правому краю regular
    ADC1->CR2 |= ADC_CR2_EXTSEL;		//Вкл. преобразование программно
    ADC1->CR2 &= ~ADC_CR2_EXTTRIG;		//Отключение преобраз. по внешнему переключению.

    ADC1->SMPR2 |= ADC_SMPR2_SMP0;		//Сэмплирование(обработка сигнала) 239.5 канала 0 PA0
    ADC1->SMPR2 |= ADC_SMPR2_SMP1;		//Сэмплирование(обработка сигнала) 239.5 канала 1 PA1

    ADC1->SQR1 |= (0x1 << ADC_SQR1_L_Pos);	//Задаю кол-во преобразований
    ADC1->SQR3 |= ADC_SQR3_SQ1;			//Выполняет преобразование в 1 канале
    ADC1->SQR3 |= ADC_SQR3_SQ2;			//Выполняет преобразование в 2 канале
}
