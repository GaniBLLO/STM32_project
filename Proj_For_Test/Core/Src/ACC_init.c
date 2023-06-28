/*
 * ACC_init.c
 *
 *  Created on: Jun 28, 2023
 *      Author: Sokolov EvgenII
 */

#include "ACC_init.h"

#define ACC_ADDR	0x18 << 1
#define com_READ	0x31
#define com_WRITE	0x30



void ACC_init(I2C_HandleTypeDef *i2c){

    ACC_init_addr(ACC_ADDR, i2c);
    ACC_setting(ACC_ADDR, i2c);
}

void ACC_init_addr (uint8_t address, I2C_HandleTypeDef *i2c){
    HAL_StatusTypeDef result;

    for(;;){
	result = HAL_I2C_IsDeviceReady(i2c, address, 1, 200);
	    if(result == HAL_OK)
		break;
	}

    uint8_t command_arr[1];
    uint8_t receive_arr[1];

    command_arr[0] = 0xF;

    HAL_I2C_Master_Transmit(i2c, address, command_arr, sizeof(command_arr), 10);
    HAL_I2C_Master_Receive(i2c, address, receive_arr, sizeof(receive_arr), 10);

    GPIOC->BSRR |= GPIO_BSRR_BR13;
    HAL_Delay(1000);
    GPIOC->BSRR |= GPIO_BSRR_BS13;

}

void ACC_setting(uint8_t address, I2C_HandleTypeDef *i2c){

    uint8_t command_arr[1];
    command_arr[0] = 0x20;
    uint8_t receive_arr[0];
    HAL_I2C_Master_Transmit(i2c, address, command_arr, sizeof(command_arr), 100);
    HAL_I2C_Master_Receive(i2c, address, receive_arr, sizeof(receive_arr), 100);
}



