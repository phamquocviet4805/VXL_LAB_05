/*
 * sche.h
 *
 *  Created on: Oct 27, 2025
 *      Author: admin
 */

#ifndef INC_SCHE_H_
#define INC_SCHE_H_

#include <stdint.h>

typedef struct {
    void (*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
    uint32_t TaskID;
} sTask;

#define SCH_MAX_TASKS 10
#define NO_TASK_ID 0
#define ERROR_SCH_TOO_MANY_TASKS 1
#define ERROR_SCH_CANNOT_DELETE_TASK 2
#define RETURN_CODE_ERROR_DELETE 3
#define RETURN_CODE_SUCCESS_DELETE 4
#define RETURN_NORMAL 9
#define RETURN_ERROR 10



void SCH_Init(void);
unsigned char SCH_Add_Task(void (*pFunction)(), uint32_t delay, uint32_t period);
void SCH_Dispatch_Tasks();
void SCH_Update(void);
unsigned char SCH_Delete_Task(uint32_t task_index);
void SCH_Go_To_Sleep(void);
void SCH_Report_Status(void);

#endif /* INC_SCHE_H_ */
