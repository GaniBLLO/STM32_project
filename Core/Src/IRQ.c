/*
 * timing_file.c
 *
 *  Created on: Jun 13, 2023
 *      Author: Sokolov EvgenII
 */
#include <IRQ.h>
GLOBAL_TIME	TIME = GLOBAL_TIME_DEFAULT;

void delay_time(uint32_t time){

    for (uint32_t i = 0; i < time; i++);
    	//__NOP;
}

uint32_t GetTime(uint32_t timer){
	return timer;
}

void SysTick_Handler(){

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
