/*
 * ACC_init.h
 *
 *  Created on: Jun 28, 2023
 *      Author: Sokolov EvgenII
 */

#ifndef INC_ACC_INIT_H_
#define INC_ACC_INIT_H_

#include "main.h"

void ACC_init(I2C_HandleTypeDef *i2c);
void ACC_init_addr (uint8_t address, I2C_HandleTypeDef *i2c);
void ACC_setting(uint8_t address, I2C_HandleTypeDef *i2c);



#endif /* INC_ACC_INIT_H_ */
