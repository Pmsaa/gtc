#ifndef __CHASSIS_TASK_H
#define __CHASSIS_TASK_H

#include "sbus.h"
#include "drv_io.h"
#include "motor.h"
#include "sw_ft.h"

struct chassis
{
	struct motor_device motor[2];
	struct io_device chassis_io;
};


void chassis_init(void);

#endif // __CHASSIS_TASK_H
