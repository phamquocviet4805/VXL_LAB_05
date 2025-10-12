/*
 * timer.c
 *
 *  Created on: Oct 12, 2025
 *      Author: admin
 */

#include "main.h"
#include "input_reading.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if(htim->Instance == TIM2) {
        button_reading();
    }
}
