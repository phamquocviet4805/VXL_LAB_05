/*
 * timer.c
 *
 *  Created on: Oct 12, 2025
 *      Author: admin
 */

#include "main.h"
#include "input_reading.h"
#include "timer.h"
#include "led_display.h"

#define N0_OF_BUTTONS 3
#define NUM_OF_TIMER 2

int TIMER_CYCLE = 10;

int redDuration = 5000;
int amberDuration = 2000;
int greenDuration = 3000;
int blinkDuration = 250;

int flagNormalMode = 0;
int flagModifyMode = 0;

int blinkTimer = 0;
int timer[NUM_OF_TIMER] = {0, 0};
int timerFlag[NUM_OF_TIMER] = {0, 0};
int blinkFlag = 0;

void setTimer(int index, int duration){
	if(index < 0 || index >= NUM_OF_TIMER) return;
	timer[index] = duration / TIMER_CYCLE ;
	timerFlag[index] = 0;
}

void timerRun(){
	for(int i = 0; i < NUM_OF_TIMER; i++){
		if(timer[i] > 0){
			timer[i]--;
			if(timer[i] == 0)
				timerFlag[i] = 1;
		}
	}
}

void modifyRun(){
	if(blinkTimer > 0){
		blinkTimer--;
		if(blinkTimer == 0)
			blinkFlag = 1;
	}
}

void setDurationRed(int duration){ redDuration = duration; }

void setDurationAmber(int duration){ amberDuration = duration; }

void setDurationGreen(int duration){ greenDuration = duration; }

void setFlagNormalMode(int state){ flagNormalMode = state; }

void setFlagModifyMode(int state){ flagModifyMode = state; }

void setTimerFlag(int index, int state){ timerFlag[index] = state; }

void resetBlinkFlag(){ blinkTimer = blinkDuration / TIMER_CYCLE; blinkFlag = 0; }


int getDurationRed(){ return redDuration; }

int getDurationAmber(){ return amberDuration; }

int getDurationGreen(){ return greenDuration; }

int getTimerFlag(int index){ return timerFlag[index]; }

int getBlinkFlag(){ return blinkFlag; }

int getTimer(int index){ return timer[index]; }

void initTimer(){
	setTimer(0, getDurationRed());
	setTimer(1, getDurationGreen());
	blinkTimer = blinkDuration / TIMER_CYCLE;
}

void resetTimerAndFlag(){
	setTimer(0, getDurationRed());
	setTimer(1, getDurationGreen());
	resetBlinkFlag();
}

void initFlag(){
	flagNormalMode = 1;
	flagModifyMode = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if(htim->Instance == TIM2) {
        button_reading();
        if(flagNormalMode){
            timerRun();
        }
        else{
        	modifyRun();
        }
    }
}
