/*
 * timing_file.c
 *
 *  Created on: Jun 13, 2023
 *      Author: Sokolov EvgenII
 */
#include <IRQ.h>
GLOBAL_TIME	TIME = GLOBAL_TIME_DEFAULT;
static uint32_t TICK = 0;


void delay_time(uint32_t time){

    uint32_t tick_start;
    uint32_t w_8 = time;
    tick_start = GetTick();

    if(w_8 < MAX_TIME)
	w_8 += (uint32_t)(0x1);
    while((GetTick() - tick_start) < w_8 ){
	;
    }
}

uint32_t GetTick(void){
    return TICK;
}

void SysTick_Handler(){

    TICK++;
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
