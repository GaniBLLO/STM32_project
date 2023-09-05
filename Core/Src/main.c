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
#include "LCD_1602.h"

#define Enable_RTOS	0

#define ADD_ADC_IN0			0x0C+0x0d20*(0x4C-1)
#define DMA_BUFF_SIZE     10
#define ADDR     0x37
#if Enable_RTOS
    #include "FreeRTOS.h"
    #include "task.h"
    #include "queue.h"
#endif


/************Functions declaration**************/

void Sys_clock(void);
void GPIO_init(void);
void TIMx_init(void);
void RCC_init();
void ADC_Init();
//INIT_STATUS ILI_9341_init();
void I2C_init();
ErrorStatus LCD_1602_init(void);
//void SPI_init(void);



uint8_t err = 0;
volatile uint16_t buff[DMA_BUFF_SIZE] = {0};


/*********************MAIN**********************/

int main(){
    RCC_init();
    Sys_clock();
    GPIO_init();
    ADC_Init();
    TIMx_init();
    I2C_init();

    if(LCD_1602_init() != SUCCESS){
    	err = 0x1;
    }
//    if(ILI_9341_init() != OK){
	//TODO ERR!
//    }
//    LCD_init();
//    init_dma();

//    SPI_init();
//    uint8_t	vector[2] = {0xFF, 0xC3};

    while(1){
//    	if(ADC1->SR & ADC_SR_EOC){
//    		ADC1->DR;
//    	}
//	GPIOC->BSRR |= GPIO_BSRR_BR13;
//	delay_time(50);
//	GPIOC->BSRR |= GPIO_BSRR_BS13;
//	delay_time(250);
	for(int i = 0; i < TIM3->ARR; ++i){
	    TIM3->CCR4 = i;
	    delay_time(1);
	}
	for(int i = TIM3->ARR; i > 0; --i){
	    TIM3->CCR4 = i;
	    delay_time(1);
	}
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

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;			//Тактирование GPIOA
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;			//Тактирование GPIOB
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;			//Тактирование GPIOAC
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;			//Вкл. тактирование алтернативной функции

    GPIOC->CRH &= ~GPIO_CRH_CNF13;				//обнуление регистра CNF
    GPIOC->CRH |= GPIO_CRH_MODE13_0;			//настройка для push-pull
}

void ADC_DMA_Init(void){
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;		//Вкл. тактирование DMA

    DMA1_Channel1->CCR &= ~DMA_CCR_EN;  	//Отключение 1ого канала

    DMA1_Channel1->CCR |= DMA_CCR_TCIE; 	//Включение прерывания при полной передачи данных
    //DMA1_Channel1->CCR |= DMA_CCR_HTIE;  	//Включение прерывания при передачи полвоины данных
    DMA1_Channel1->CCR  |= DMA_CCR_TEIE;  	//Включение прерываня из-за ошибки передачи
    DMA1_Channel1->CCR  &= ~DMA_CCR_DIR;  	//Чтения данных из переферии
    DMA1_Channel1->CCR |= DMA_CCR_CIRC;  	//Включение кольцевого буфера
    DMA1_Channel1->CCR &= ~DMA_CCR_PINC;  	//Адрес переферии неизменный => не инкрементируется
    DMA1_Channel1->CCR |= DMA_CCR_MINC;  	//Инкрементирование адреса памяти
    DMA1_Channel1->CCR &= ~DMA_CCR_PSIZE;  	//Задал размерность данных 8бит для переферии
    DMA1_Channel1->CCR &= ~DMA_CCR_MSIZE;  	//Задал размерность данных 8бит для пкамяти
    DMA1_Channel1->CCR &= ~DMA_CCR_PL_1;  	//Задал приоритетность TODO проверить работу приоритетности

    DMA1_Channel1->CNDTR = DMA_BUFF_SIZE;			//задал количество данных
    DMA1_Channel1->CPAR = (uint32_t)&(ADC1->DR);		//Указатель на адрес в ADC_IN0
    DMA1_Channel1->CMAR = (uint32_t)buff;			//Буфер для данных

    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    DMA1_Channel1->CCR |= DMA_CCR_EN;  				//Включение 1ого канала
}


void ADC_Init(){
    //RCC
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

    ADC1->CR1 = 0x0;					//todo Проверить, действительно ли регистры очистились
    ADC1->CR1 |= ADC_CR1_SCAN;			//Вкл. режима сканирования
    ADC1->CR1 |= (0x6 << ADC_CR1_DUALMOD_Pos);	//todo Узнать на что влияет

    ADC1->CR2 |= ADC_CR2_ADON;			//Вкл. АЦП
    ADC1->CR2 |= ADC_CR2_CONT;			//Режим непрерывного преобразования
    ADC1->CR2 |= ADC_CR2_CAL;			//Включить калибровку. Рек. перед включение ацп
    ADC1->CR2 |= ADC_CR2_DMA;			//Включение DMA
    while(ADC1->CR2 & ADC_CR2_CAL);

    ADC1->CR2 &= ~ADC_CR2_ALIGN;		//Выравнивнивание данных по правому краю regular
    ADC1->CR2 |= ADC_CR2_EXTSEL;		//Вкл. преобразование программно
    ADC1->CR2 &= ~ADC_CR2_EXTTRIG;		//Отключение преобраз. по внешнему переключению.

    ADC1->SMPR2 |= ADC_SMPR2_SMP0;		//Сэмплирование(обработка сигнала) 239.5 канала 0 PA0
    ADC1->SMPR2 |= ADC_SMPR2_SMP1;		//Сэмплирование(обработка сигнала) 239.5 канала 1 PA1

    ADC1->SQR1 |= (0x1 << ADC_SQR1_L_Pos);	//Задаю кол-во преобразований
    ADC1->SQR3 |= ADC_SQR3_SQ1;			//Выполняет преобразование в 1 канале
    ADC1->SQR3 |= ADC_SQR3_SQ2;			//Выполняет преобразование в 2 канале

    ADC_DMA_Init();
}
