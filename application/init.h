#ifndef __INIT_H
#define __INIT_H

#include "FreeRTOS.h"
#include "task.h"

#include "board.h"
#include "os_timer.h"

#include "chassis_task.h"



void hw_init(void);
void sys_init(void);
void task_init(void);

#endif // __INIT_H

