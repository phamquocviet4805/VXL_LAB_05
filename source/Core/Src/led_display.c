/*
 * led_display.c
 *
 *  Created on: Oct 12, 2025
 *      Author: admin
 */
#include "led_display.h"
#include "main.h"
#include "timer.h"
#include <math.h>

static GPIO_TypeDef* const RED_GPIO[2]  = { LED_RED_1_GPIO_Port, LED_RED_2_GPIO_Port };
static uint16_t RED_PIN [2]       		= { LED_RED_1_Pin, LED_RED_2_Pin };
static GPIO_TypeDef* const AMB_GPIO[2]  = { LED_YEL_1_GPIO_Port, LED_YEL_2_GPIO_Port };
static uint16_t AMB_PIN [2]      	  	= { LED_YEL_1_Pin, LED_YEL_2_Pin };
static GPIO_TypeDef* const GRN_GPIO[2]  = { LED_GRN_1_GPIO_Port, LED_GRN_2_GPIO_Port };
static uint16_t GRN_PIN[2]       		= { LED_GRN_1_Pin, LED_GRN_2_Pin };

enum trafficLight {RED, AMBER, GREEN};
enum trafficLight trafficState[2];

int displayNum[2];

void resetState(){
	trafficState[0] = RED;
	trafficState[1] = GREEN;
}

void trafficInit(void) {
	trafficState[0] = RED;
	trafficState[1] = GREEN;
	trafficDisplay();
	displaySegLed();
	displayLED7SEG_MODE(1);
}

void trafficAllOff(void) {
    for (int i = 0; i < 2; ++i) {
        HAL_GPIO_WritePin(RED_GPIO[i], RED_PIN[i], GPIO_PIN_RESET);
        HAL_GPIO_WritePin(AMB_GPIO[i], AMB_PIN[i], GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GRN_GPIO[i], GRN_PIN[i], GPIO_PIN_RESET);
    }
}

void trafficSetRoad(int road, int r_on, int a_on, int g_on) {
    if (road < 0 || road > 1) return;
    HAL_GPIO_WritePin(RED_GPIO[road], RED_PIN[road], r_on ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(AMB_GPIO[road], AMB_PIN[road], a_on ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GRN_GPIO[road], GRN_PIN[road], g_on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void trafficModifyMode(int color) {
    for (int i = 0; i < 2; ++i) {
        switch (color) {
            case 1: HAL_GPIO_TogglePin(RED_GPIO[i], RED_PIN[i]); break;			//RED
            case 2: HAL_GPIO_TogglePin(AMB_GPIO[i], AMB_PIN[i]); break;			//AMBER
            case 3: HAL_GPIO_TogglePin(GRN_GPIO[i], GRN_PIN[i]); break;			//GREEN
            default: break;
        }
    }
}

void displayLED7SEG_MODE(int number) {
	GPIO_PinState arr[4];

    int num = number & 0x0F;

    for (int i = 3; i >= 0; --i) {
        arr[i] = ((num & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        num >>= 1;
    }

    HAL_GPIO_WritePin(LED_SEG1_A_GPIO_Port, LED_SEG1_A_Pin, arr[3]);
    HAL_GPIO_WritePin(LED_SEG1_B_GPIO_Port, LED_SEG1_B_Pin, arr[2]);
    HAL_GPIO_WritePin(LED_SEG1_C_GPIO_Port, LED_SEG1_C_Pin, arr[1]);
    HAL_GPIO_WritePin(LED_SEG1_D_GPIO_Port, LED_SEG1_D_Pin, arr[0]);
}

void displayLED7SEG_LR(int number) {
    if (number < 0) number = 0;
    if (number > 99) number = 99;

    // Divide number into 2 part
    int divPart = number / 10;
    int modPart = number % 10;

    // CONVERT TO BINARY AND STORE INTO ARRAY
    GPIO_PinState arr_1[4];
    GPIO_PinState arr_2[4];

    // USING (&) BIT OPERATION
    for (int i = 3; i >= 0; --i) {
        arr_1[i] = ((divPart & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        divPart >>= 1;
        arr_2[i] = ((modPart & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        modPart >>= 1;
    }

    // Display
    HAL_GPIO_WritePin(LED_SEG4_A_GPIO_Port, LED_SEG4_A_Pin, arr_1[3]);
    HAL_GPIO_WritePin(LED_SEG4_B_GPIO_Port, LED_SEG4_B_Pin, arr_1[2]);
    HAL_GPIO_WritePin(LED_SEG4_C_GPIO_Port, LED_SEG4_C_Pin, arr_1[1]);
    HAL_GPIO_WritePin(LED_SEG4_D_GPIO_Port, LED_SEG4_D_Pin, arr_1[0]);

    HAL_GPIO_WritePin(LED_SEG5_A_GPIO_Port, LED_SEG5_A_Pin, arr_2[3]);
    HAL_GPIO_WritePin(LED_SEG5_B_GPIO_Port, LED_SEG5_B_Pin, arr_2[2]);
    HAL_GPIO_WritePin(LED_SEG5_C_GPIO_Port, LED_SEG5_C_Pin, arr_2[1]);
    HAL_GPIO_WritePin(LED_SEG5_D_GPIO_Port, LED_SEG5_D_Pin, arr_2[0]);
}

void displayLED7SEG_TB(int number) {
    if (number < 0) number = 0;
    if (number > 99) number = 99;

    int divPart = number / 10;
    int modPart = number % 10;

    // CONVERT TO BINARY
    GPIO_PinState arr_1[4];
    GPIO_PinState arr_2[4];

    for (int i = 3; i >= 0; --i) {
        arr_1[i] = ((divPart & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        divPart >>= 1;
        arr_2[i] = ((modPart & 1) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        modPart >>= 1;
    }

    HAL_GPIO_WritePin(LED_SEG2_A_GPIO_Port, LED_SEG2_A_Pin, arr_1[3]);
    HAL_GPIO_WritePin(LED_SEG2_B_GPIO_Port, LED_SEG2_B_Pin, arr_1[2]);
    HAL_GPIO_WritePin(LED_SEG2_C_GPIO_Port, LED_SEG2_C_Pin, arr_1[1]);
    HAL_GPIO_WritePin(LED_SEG2_D_GPIO_Port, LED_SEG2_D_Pin, arr_1[0]);

    HAL_GPIO_WritePin(LED_SEG3_A_GPIO_Port, LED_SEG3_A_Pin, arr_2[3]);
    HAL_GPIO_WritePin(LED_SEG3_B_GPIO_Port, LED_SEG3_B_Pin, arr_2[2]);
    HAL_GPIO_WritePin(LED_SEG3_C_GPIO_Port, LED_SEG3_C_Pin, arr_2[1]);
    HAL_GPIO_WritePin(LED_SEG3_D_GPIO_Port, LED_SEG3_D_Pin, arr_2[0]);
}

void trafficDisplay(){
	switch(trafficState[0]){
	case RED:
		trafficSetRoad(0, 1, 0, 0);
		break;
	case AMBER:
		trafficSetRoad(0, 0, 1, 0);
		break;
	case GREEN:
		trafficSetRoad(0, 0, 0, 1);
		break;
	default: break;
	}

	switch(trafficState[1]){
	case RED:
		trafficSetRoad(1, 1, 0, 0);
		break;
	case AMBER:
		trafficSetRoad(1, 0, 1, 0);
		break;
	case GREEN:
		trafficSetRoad(1, 0, 0, 1);
		break;
	default: break;
	}
}

void displaySegLed(){
	displayLED7SEG_TB(round((getTimer(0) - 1) / 100) + 1);
	displayLED7SEG_LR(round((getTimer(1) - 1) / 100) + 1);
}

void trafficProcessing(){
	if(getTimerFlag(0) == 1){
		switch(trafficState[0]){
		case RED:
			setTimer(0, getDurationGreen());
			displayNum[0] = getDurationGreen() / 1000;
			trafficState[0] = GREEN;
			break;
		case AMBER:
			setTimer(0, getDurationRed());
			displayNum[0] = getDurationRed() / 1000;
			trafficState[0] = RED;
			break;
		case GREEN:
			setTimer(0, getDurationAmber());
			displayNum[0] = getDurationAmber() / 1000;
			trafficState[0] = AMBER;
			break;
		default: break;
		}
	}

	if(getTimerFlag(1) == 1){
		switch(trafficState[1]){
		case RED:
			setTimer(1, getDurationGreen());
			displayNum[1] = getDurationGreen() / 1000;
			trafficState[1] = GREEN;
			break;
		case AMBER:
			setTimer(1, getDurationRed());
			displayNum[1] = getDurationRed() / 1000;
			trafficState[1] = RED;
			break;
		case GREEN:
			setTimer(1, getDurationAmber());
			displayNum[1] = getDurationAmber() / 1000;
			trafficState[1] = AMBER;
			break;
		default: break;
		}
	}

	trafficDisplay();
	displaySegLed();
}

void blinkLed(int mode){
	if(getBlinkFlag() == 1){
		trafficModifyMode(mode);
		resetBlinkFlag();
	}
}




