/*
 * timer.c
 *
 *  Created on: Oct 27, 2025
 *      Author: admin
 */

#include "timer.h"
#include "sche.h"
#include "main.h"

#define TIMER_CYCLE 10;

uint32_t sysTimeTicks = 0;

int timer_check = 100;
int check_flag = 0;

uint32_t getSysTick(){
	return sysTimeTicks;
}

void Timer_Init(){
	setTimerCheck(1000);
}

void setTimerCheck(int duration){
	timer_check = duration / TIMER_CYCLE ;
	check_flag = 0;
}

int getCheckFlag(void) {
	return check_flag;
}

void timer_run(void){
	if(timer_check > 0){
		timer_check--;
		if(timer_check == 0){
			check_flag = 1;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim){
	if(htim->Instance == TIM2){
		SCH_Update();
	}
}
