#include "init.h"

#define LOG_TAG "init"
#define LOG_OUTPUT_LEVEL  LOG_INFO
#include "log.h"




void SystemServiceTask(void *argument)
{

	hw_init();
	sys_init();
	task_init();
	

	for( ; ; )
	{
//		log_i("->log\r\n");
//		log_i("%d\n%d\n%d\n%d\n", chassis_rc.rc_info.ch1, chassis_rc.rc_info.ch2, chassis_rc.rc_info.ch3, chassis_rc.rc_info.ch4);
//		printf("$%d %d %d %d %d %d %d %d %d %d %d %d;", 
//								chassis_rc.rc_info.x2, chassis_rc.rc_info.y2, 
//								chassis_rc.rc_info.x1, chassis_rc.rc_info.y1,
//								chassis_rc.rc_info._e5, chassis_rc.rc_info.g6,
//								chassis_rc.rc_info._h7, chassis_rc.rc_info._f8,
//								chassis_rc.rc_info.a9, chassis_rc.rc_info.b10,
//								chassis_rc.rc_info.c11, chassis_rc.rc_info.d12);
		
		vTaskDelay(500);
	}
}

void hw_init(void)
{
	board_config();
	
}

void sys_init(void)
{
	soft_timer_FreeRTOS_init();
}

void task_init(void)
{
	chassis_init();
}



