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



