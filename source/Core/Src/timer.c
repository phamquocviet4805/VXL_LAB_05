/*
 * timer.c
 *
 *  Created on: Oct 27, 2025
 *      Author: admin
 */

#include "timer.h"
#include "main.h"

#define TIMER_CYCLE 10;



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim){
	if(htim->Instance == TIM2){

	}
}
