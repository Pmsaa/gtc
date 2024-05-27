#include "chassis_task.h"

#include "FreeRTOS.h"
#include "task.h"


#define LOG_TAG "chassis_task"
#define LOG_OUTPUT_LEVEL LOG_INFO
#include "log.h"

TaskHandle_t chassisTaskHandle = NULL;
void chassisTask(void *pvParameters);

struct chassis chassis;

struct rc_device chassis_rc;
struct io_device chassis_kg;


void chassis_init(void)
{
	char motor_name[2][10] = {0};
	uint8_t name_len = strlen("motor");
	
	for(uint8_t i=0; i<2; i++)
	{
		memcpy(&motor_name[i], "motor", name_len);
		chassis.motor[i].node_id = 0x01 + i;
		chassis.motor[i].can_send_flag = 0;
		chassis.motor[i].speed_rate = 0;
	}
	
	memcpy(&motor_name[0][name_len], "_MR\0", 4);
	memcpy(&motor_name[1][name_len], "_ML\0", 4);
	
	for(uint8_t i=0; i<2; i++)
	{
		motor_register(&chassis.motor[i], motor_name[i]);
	}
	motor_can_send_register(motor_canstd_send);

	rc_device_register(&chassis_rc, "t12");
	io_device_register(&chassis_kg, "kg");
	
	xTaskCreate(chassisTask, "chassisTask", 512, NULL, 5, &chassisTaskHandle);
}


void chassisTask(void *pvParameters)
{
	int16_t speed_rate = 0;
	
	for(;;)
	{
		speed_rate += 1;
		for(uint8_t i=0; i<2; i++)
		{
			motor_set_speed(&chassis.motor[i], speed_rate);
			motor_set_can_send_flag(&chassis.motor[i], 1);
			motor_fill_data_output();			
		}
		
		vTaskDelay(500);
	}
}


