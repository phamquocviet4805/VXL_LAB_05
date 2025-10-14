/*
 * led_display.h
 *
 *  Created on: Oct 12, 2025
 *      Author: admin
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#define LED_RED1_ON

void displayLED7SEG_MODE(int number);

void displayLED7SEG_LR(int number);

void displayLED7SEG_TB(int number);

void trafficInit(void);

void trafficAllOff(void);

void trafficSetRoad(int road, int r_on, int a_on, int g_on);

void trafficModifyMode(int color);

void trafficDisplay();

void displaySegLed();

void trafficProcessing(void);

void blinkLed(int mode);

#endif /* INC_LED_DISPLAY_H_ */
