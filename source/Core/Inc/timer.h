/*
 * timer.h
 *
 *  Created on: Oct 12, 2025
 *      Author: admin
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

void setTimer(int index, int duration_ms);
void timerRun(void);

void setDurationRed(int duration_ms);
void setDurationAmber(int duration_ms);
void setDurationGreen(int duration_ms);

void setFlagNormalMode(int state);
void setFlagModifyMode(int state);

int getDurationRed(void);
int getDurationAmber(void);
int getDurationGreen(void);
int getTimer(int index);

int  getTimerFlag(int index);
void setTimerFlag(int index, int state);

int getBlinkFlag(void);
void resetBlinkFlag(void);

void initTimer(void);
void initFlag(void);

void resetTimerAndFlag();

#endif /* INC_TIMER_H_ */
