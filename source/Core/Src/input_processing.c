/*
 * input_processing.c
 *
 *  Created on: Oct 12, 2025
 *      Author: admin
 */
//INCLUDE
#include "main.h"
#include "input_reading.h"
#include "led_display.h"
#include "timer.h"

//DEFINE
#define N0_OF_BUTTONS 3

//PRIVATE VARIABLES
enum ButtonState {
    BUTTON_RELEASED,
    BUTTON_PRESSED,
    BUTTON_PRESSED_MORE_THAN_1_SECOND
};

enum Color {
    RED = 1,
    AMBER = 2,
    GREEN = 3
};

enum MODE { MODE_1_NORMAL , MODE_2_RED_MODIFY , MODE_3_AMBER_MODIFY , MODE_4_GREEN_MODIFY };

static enum MODE currMode = MODE_1_NORMAL;
static enum ButtonState buttonPrevState[N0_OF_BUTTONS] = { BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED };
static enum ButtonState buttonCurrState[N0_OF_BUTTONS] = { BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED };

int increaseCounter = 1; //counter for increasing duration

//FUNCTION
void increateButton(){
	if(increaseCounter >= 99)
		return;
	++increaseCounter;
}

void resetIcrCnt(){
	increaseCounter = 1;
}

void fsm_for_input_processing(void) {
	for(int i = 0; i < N0_OF_BUTTONS ; ++i){
		if(is_button_pressed(i) == 1){
			buttonPrevState[i] = buttonCurrState[i];
			buttonCurrState[i] = BUTTON_PRESSED;
		}else{
			buttonPrevState[i] = buttonCurrState[i];
			buttonCurrState[i] = BUTTON_RELEASED;
		}

	}
	switch(currMode){
		case MODE_1_NORMAL: //====================== MODE 1 NORMAL MODE ==============================================================
			setFlagNormalMode(1);
			setFlagModifyMode(0);
			trafficProcessing(); //Handle normal traffic light
			displayLED7SEG_MODE(1); //Display mode

			//IF BUTTON 1 IS PRESSED -> NEXT MODE
			if(buttonCurrState[0] == BUTTON_RELEASED && buttonPrevState[0] == BUTTON_PRESSED){
				trafficAllOff();
				resetIcrCnt();
				currMode = MODE_2_RED_MODIFY;
			}
			break;
		case MODE_2_RED_MODIFY: //====================== MODE 2 MODIDY RED LED ==============================================================
			setFlagNormalMode(0); // Set flag  = 0 ( Mean turn off Normal mode )
			setFlagModifyMode(1);	// Set flag  = 1 ( Mean change state to Modify Mode )
			//Display 2-2 segment led for counting
			displayLED7SEG_TB(increaseCounter);
			displayLED7SEG_LR(increaseCounter);
			displayLED7SEG_MODE(2); //Display mode
			blinkLed(RED); //Blink 2 two modifying 1.RED 2.AMBER 3.GREEN

			//IF BUTTON 2 IS PRESSED -> INCREASE COUNTER
			if(buttonCurrState[1] == BUTTON_RELEASED && buttonPrevState[1] == BUTTON_PRESSED){
				increateButton(); // counter++
			}

			//IF BUTTON 3 IS PRESSED -> CONFIRM MODIFY & NEXT MODE
			if(buttonCurrState[2] == BUTTON_RELEASED && buttonPrevState[2] == BUTTON_PRESSED){
				setDurationRed(increaseCounter * 1000); // duration  = counter * 1000
				trafficAllOff();
				resetIcrCnt(); // counter reset to 0
				resetTimerAndFlag(); // reset to INIT state in Normal Mode
				calLed(RED); // Calculate duration with priority red - green = amber
				currMode = MODE_3_AMBER_MODIFY;

			}

			//IF BUTTON 1 IS PRESSED -> NEXT MODE
			if(buttonCurrState[0] == BUTTON_RELEASED && buttonPrevState[0] == BUTTON_PRESSED){
				trafficAllOff();
				resetIcrCnt();
				currMode = MODE_3_AMBER_MODIFY;
			}
			break;
		case MODE_3_AMBER_MODIFY: //====================== MODE 3 MODIDY AMBERLED ==============================================================
			setFlagNormalMode(0);
			setFlagModifyMode(1);
			//Display 2-2 segment led for counting
			displayLED7SEG_TB(increaseCounter);
			displayLED7SEG_LR(increaseCounter);
			displayLED7SEG_MODE(3);
			blinkLed(AMBER); //Blink 2 two modifying 1.RED 2.AMBER 3.GREEN

			//IF BUTTON 2 IS PRESSED -> INCREASE COUNTER
			if(buttonCurrState[1] == BUTTON_RELEASED && buttonPrevState[1] == BUTTON_PRESSED){
				increateButton(); // Increase counter
			}

			//IF BUTTON 3 IS PRESSED -> CONFIRM MODIFY & NEXT MODE
			if(buttonCurrState[2] == BUTTON_RELEASED && buttonPrevState[2] == BUTTON_PRESSED){
				setDurationAmber(increaseCounter * 1000);
				trafficAllOff();
				resetIcrCnt();
				resetTimerAndFlag();
				calLed(AMBER); // Calculate duration with priority red - green = amber
				currMode = MODE_4_GREEN_MODIFY;

			}

			//IF BUTTON 1 IS PRESSED -> NEXT MODE
			if(buttonCurrState[0] == BUTTON_RELEASED && buttonPrevState[0] == BUTTON_PRESSED){
				trafficAllOff();
				resetIcrCnt();
				currMode = MODE_4_GREEN_MODIFY;
			}
			break;
		case MODE_4_GREEN_MODIFY: //====================== MODE 4 MODIDY GREEN LED ==============================================================
			setFlagNormalMode(0);
			setFlagModifyMode(1);
			//Display 2-2 segment led for counting
			displayLED7SEG_TB(increaseCounter);
			displayLED7SEG_LR(increaseCounter);
			displayLED7SEG_MODE(4); //Display mode
			blinkLed(GREEN); //Blink 2 two modifying 1.RED 2.AMBER 3.GREEN

			//IF BUTTON 2 IS PRESSED -> INCREASE COUNTER
			if(buttonCurrState[1] == BUTTON_RELEASED && buttonPrevState[1] == BUTTON_PRESSED){
				increateButton();
			}

			//IF BUTTON 3 IS PRESSED -> CONFIRM MODIFY & NEXT MODE
			if(buttonCurrState[2] == BUTTON_RELEASED && buttonPrevState[2] == BUTTON_PRESSED){
				setDurationGreen(increaseCounter * 1000);
				trafficAllOff();
				resetIcrCnt();
				resetTimerAndFlag();
				resetState();
				calLed(GREEN); // Calculate duration with priority red - green = amber
				currMode = MODE_1_NORMAL;
			}

			//IF BUTTON 1 IS PRESSED -> NEXT MODE
			if(buttonCurrState[0] == BUTTON_RELEASED && buttonPrevState[0] == BUTTON_PRESSED){
				trafficAllOff();
				resetIcrCnt();
				resetTimerAndFlag();
				resetState();
				currMode = MODE_1_NORMAL;
			}
			break;
		default:
			currMode = MODE_1_NORMAL;
			break;
	}

}





