
#ifndef _MAIN_H
#define _MAIN_H

#include "cmsis_os.h"

#define wait_delay HAL_Delay

/* Mutex */
osMutexDef(mut_GLCD);
osMutexId mut_GLCD; /* Mutex to control GLCD access */

/* Function Prototypes for Tasks */
void taskGLCD (void const *argument);
void taskInput (void const *argument);
void taskGameLogic (void const *argument);

/* Declare Task IDs */
osThreadId tid_taskGLCD;  /* id of thread: taskGLCD */
osThreadId tid_taskGameLogic;  /* id of thread: taskGreq */
osThreadId tid_taskInput;  /* id of thread: taskMotor */

/* Define Threads */
osThreadDef(taskGLCD, osPriorityNormal, 1, 0);
osThreadDef(taskGameLogic, osPriorityNormal, 1, 0);
osThreadDef(taskInput, osPriorityNormal, 1, 0);

#endif /* _MAIN_H */
