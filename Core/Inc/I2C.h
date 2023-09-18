/*
 * I2C.h
 *
 *  Created on: 20 июн. 2023 г.
 *      Author: Sokolov EvgenII
 */
#include "stm32f1xx.h"
#ifndef INC_I2C_H_
#define INC_I2C_H_

struct{
	uint8_t		address;
	uint8_t		*data_buffer;
	uint16_t	data_size;
	ErrorStatus	(*init);
};

void I2C_init();

#endif /* INC_I2C_H_ */
