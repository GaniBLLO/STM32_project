/*
 * LCD_1602.c
 *
 *  Created on: 23 июн. 2023 г.
 *      Author: Sokolov EvgenII
 */

#include "stdint.h"
#include "LCD_1602.h"

#define PIN_RS    	(1 << 0)
#define PIN_EN    	(1 << 2)
#define BACKLIGHT 	(1 << 3)

ErrorStatus LCD_SendInternal(uint8_t lcd_addr, uint8_t data, uint8_t flags) {
    uint8_t up = data & 0xF0;
    uint8_t lo = (data << 4) & 0xF0;

    uint8_t data_arr[4];
    data_arr[0] = up|flags|BACKLIGHT|PIN_EN;
    data_arr[1] = up|flags|BACKLIGHT;
    data_arr[2] = lo|flags|BACKLIGHT|PIN_EN;
    data_arr[3] = lo|flags|BACKLIGHT;

    if(!(I2C1->SR2 & I2C_SR2_BUSY)){
    	//ToDo аписать обработку ошибок
    }
    I2C1->CR1 &= ~I2C_CR1_POS;				//См.I2C_Scan()

   	I2C1->CR1 |= I2C_CR1_START;
   	while(!(I2C1->SR1 & I2C_SR1_SB));

	(void)I2C1->SR1;
   	I2C1->DR = address & (uint8_t)(~I2C_OAR1_ADD0);
   	while(!(I2C1->SR1 & I2C_SR1_ADDR) && !(I2C1->SR1 & I2C_SR1_AF));
   		//ToDo добавить счётчик

   	if(I2C1->SR1 &I2C_SR1_ADDR){
   		(void)I2C1->SR1;
   		(void)I2C1->SR2;

   	}
    return SUCCESS;
}

void LCD_SendCommand(uint8_t lcd_addr, uint8_t cmd) {
    LCD_SendInternal(lcd_addr, cmd, 0);
}

void LCD_SendData(uint8_t lcd_addr, uint8_t data) {
    LCD_SendInternal(lcd_addr, data, PIN_RS);
}

void LCD_SendString(uint8_t lcd_addr, char *str) {
    while(*str) {
        LCD_SendData(lcd_addr, (uint8_t)(*str));
        str++;
    }
}

ErrorStatus I2C_Scan(uint8_t address) {
    I2C1->CR1 &= ~I2C_CR1_POS;		/*Этот бит ставится что бы показать,
									 *что след.бит будет принят в регистр -> DR
									 *для его дальнейшего смещения*/

   	I2C1->CR1 |= I2C_CR1_START;		//Генерируем стартовый бит
   	while(!(I2C1->SR1 & I2C_SR1_SB));	//Ждём пока регситр не сгенерирует бит старта. 0 => ждём... 1 = > готово!

	(void)I2C1->SR1;
   	I2C1->DR = address & (uint8_t)(~I2C_OAR1_ADD0);	//В сдвиговый регистр добавляю адрес устройства
//   	do{
//   	    (void)I2C1->SR2;
//   	}
   	while(!(I2C1->SR1 & I2C_SR1_ADDR) && !(I2C1->SR1 & I2C_SR1_AF));

   	if(I2C1->SR1 & I2C_SR1_ADDR){
		I2C1->CR1 |= I2C_CR1_STOP;
   	    (void)I2C1->SR1;
   	    (void)I2C1->SR2;
   	    return SUCCESS;
   	}else{
   		I2C1->CR1 |= I2C_CR1_STOP;
   		I2C1->SR1 &= ~I2C_SR1_AF;
   		return ERROR;
   	}
}

void LCD_Init(uint8_t lcd_addr) {
    // 4-bit mode, 2 lines, 5x7 format
    LCD_SendCommand(lcd_addr, 0b00110000);
    // display & cursor home (keep this!)
    LCD_SendCommand(lcd_addr, 0b00000010);
    // display on, right shift, underline off, blink off
    LCD_SendCommand(lcd_addr, 0b00001100);
    // clear display (optional here)
    LCD_SendCommand(lcd_addr, 0b00000001);
}

ErrorStatus LCD_1602_init(uint8_t address) {
    I2C_Scan(address);
    LCD_Init(address);

    // set address to 0x00
    LCD_SendCommand(address, 0b10000000);
    LCD_SendString(address, " Using 1602 LCD");

    // set address to 0x40
    LCD_SendCommand(address, 0b11000000);
    LCD_SendString(address, "  over I2C bus");
    return SUCCESS;
}
