/*
 * timing_file.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Sokolov EvgenII
 */
#include "stm32f103xb.h"

#ifndef INC_TIMING_FILE_H_
#define INC_TIMING_FILE_H_

typedef struct{
	uint32_t	ms;
	uint32_t	sec;
	uint32_t	min;
	uint32_t	hr;
}GLOBAL_TIME;

#define GLOBAL_TIME_DEFAULT {0,0,0,0};

void delay_time(uint32_t time);

#endif /* INC_TIMING_FILE_H_ */
