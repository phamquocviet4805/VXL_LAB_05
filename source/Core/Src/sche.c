/*
 * sche.c
 *
 *  Created on: Oct 27, 2025
 *      Author: admin
 */

#include "sche.h"
#include "main.h"
#include "timer.h"

unsigned char Error_Code_G;
sTask SCH_tasks_G[SCH_MAX_TASKS];
int size = 0;

void SCH_Init(void){
	unsigned char i;
	for(i = 0; i < SCH_MAX_TASKS; i++){
		SCH_Delete_Task(i);
	}
	Error_Code_G = 0;
}

unsigned char SCH_Add_Task(void (*pFunction)(), uint32_t delay, uint32_t period)
{
	unsigned char i = 0;

    while ((i < SCH_MAX_TASKS) && (SCH_tasks_G[i].pTask != 0) && (delay >= SCH_tasks_G[i].Delay)) {
        delay -= SCH_tasks_G[i].Delay;
        i++;
    }

    for (int j = SCH_MAX_TASKS - 1; j > i; j--) {
        SCH_tasks_G[j] = SCH_tasks_G[j - 1];
    }

    SCH_tasks_G[i].pTask  = pFunction;
    SCH_tasks_G[i].Delay  = delay;
    SCH_tasks_G[i].Period = period;
    SCH_tasks_G[i].RunMe  = 0;

    if(i < SCH_MAX_TASKS - 1){
    	SCH_tasks_G[i + 1].Delay -= delay;
    }

    return i;
}

void SCH_Dispatch_Tasks(void)
{
	//Check if the first task is ready to run
    if (SCH_tasks_G[0].RunMe > 0) {
        (*SCH_tasks_G[0].pTask)();  //Execute the task function
        SCH_tasks_G[0].RunMe--;
        //Handle completed tasks
        if (SCH_tasks_G[0].Period == 0){ //If the task is one-shot
        	SCH_Delete_Task(0);
            SCH_tasks_G[SCH_MAX_TASKS - 1].pTask = 0;
        } else { 						//If the task is periodic
        	//After a task finishes, all subsequent tasks are shifted forward to maintain the order of execution
            void (*f)() = SCH_tasks_G[0].pTask;
            uint32_t p  = SCH_tasks_G[0].Period;
            SCH_Delete_Task(0);
            SCH_Add_Task(f, p, p);		//Add it back to array with delay = period
        }
    }
}

void SCH_Update(void) {
	//Check if the first task slot is empty
    if (SCH_tasks_G[0].pTask == 0) return;

    //If the first task’s delay reaches zero
    if (SCH_tasks_G[0].Delay == 0) {
        SCH_tasks_G[0].RunMe++;

        if (SCH_tasks_G[0].Period)
            SCH_tasks_G[0].Delay = SCH_tasks_G[0].Period;
    } else {
        SCH_tasks_G[0].Delay--;
    }
}

unsigned char SCH_Delete_Task(uint32_t index)
{
    if (index >= SCH_MAX_TASKS) {
        return RETURN_ERROR;
    }

    if ((index + 1 < SCH_MAX_TASKS) && (SCH_tasks_G[index + 1].pTask != 0)) {
        SCH_tasks_G[index + 1].Delay += SCH_tasks_G[index].Delay;
    }

    for (uint32_t i = index; i < SCH_MAX_TASKS - 1; i++) {
          SCH_tasks_G[i] = SCH_tasks_G[i + 1];
    }

    SCH_tasks_G[SCH_MAX_TASKS - 1].pTask  = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].Delay  = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].Period = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].RunMe  = 0;
    SCH_tasks_G[SCH_MAX_TASKS - 1].TaskID = 0;

    return RETURN_NORMAL;
}

void SCH_Go_To_Sleep(void)
{
	// To do
}

unsigned char Last_error_code_G = 0;
unsigned int Error_tick_count_G = 0;

void SCH_Report_Status(void)
{
#ifdef SCH_REPORT_ERRORS

    if (Error_Code_G != Last_error_code_G) {
        Error_port = 255 - Error_Code_G;

        Last_error_code_G = Error_Code_G;

        if (Error_Code_G != 0) {
            Error_tick_count_G = 60000;
        } else {
            Error_tick_count_G = 0;
        }
    } else {
        if (Error_tick_count_G != 0) {
            if (--Error_tick_count_G == 0) {
                Error_Code_G = 0;
            }
        }
    }
#endif
}


