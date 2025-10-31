/*
 * timer.h
 *
 *  Created on: Oct 27, 2025
 *      Author: admin
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

void Timer_Init(void);
void timer_run(void);
void setTimerCheck(int duration);
int getCheckFlag(void);

#endif /* INC_TIMER_H_ */
