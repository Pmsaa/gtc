#ifndef __CHASSIS_TASK_H
#define __CHASSIS_TASK_H

#include "sbus.h"
#include "drv_io.h"
#include "board.h"
#include "sw_ft.h"
#include "caterpillar.h"

#define FOOT_PEDALS_SPEED	0.35	

struct chassis
{
	struct motor_device motor[2];
	struct io_device chassis_io;
};


void chassis_init(void);
void chassis_set_speed(void);

#endif // __CHASSIS_TASK_H
