#include "chassis_task.h"

#include "FreeRTOS.h"
#include "task.h"


#define LOG_TAG "chassis"
#define LOG_OUTPUT_LEVEL LOG_INFO
#include "log.h"

osThreadId_t chassisTaskHandle = NULL;
const osThreadAttr_t chassTask_attr = {
	.name = "chassisTask",
	.stack_size = 512,
	.priority = osPriorityNormal,
};

void chassisTask(void *pvParameters);

struct chassis chassis;
struct rc_device chassis_rc;
struct io_device chassis_io;

rc_info_t p_rc_info;
struct caterpillar catp;

float vx, vy, vw;

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

	caterpillar_set_speed(&catp, 0, 0, 0);
	catp.param.wheel_tread = CATERPILLAR_TREAD;

	rc_device_register(&chassis_rc, "t12");
	io_device_register(&chassis_io, "kg");
	
	chassisTaskHandle = osThreadNew(chassisTask, NULL, &chassTask_attr);
}

void chassis_set_speed(void)
{

	vx = (float)(((float)(p_rc_info->y1) / 720.0f) * 1.0f); 	// SET RPM
	vy = 0;
	vw = (float)(((float)(p_rc_info->x2) / 720.0f) * 1.0f);

	caterpillar_set_speed(&catp, vx, vy, vw);
	caterpillar_calculate(&catp);
	log_i("%d  %d", catp.caterpillar_rpm[0], catp.caterpillar_rpm[1]);
//	for(uint8_t i=0; i<2; i++)
//	{
//		motor_set_speed(&chassis.motor[i], catp.caterpillar_rpm[i]);
//	}
//	motor_fill_data_output();
}

void chassisTask(void *pvParameters)
{
	log_i("chassisTask");
	
	p_rc_info = rc_device_get_info(&chassis_rc);
	
	for(;;)
	{
		if(rc_device_get_state(&chassis_rc, RC_E5_UP) == E_OK)
		{
			// Use the remote control to control the tracks on both sides
			vx = (float)(((float)(p_rc_info->y1) / 720.0f) * 1.0f); 	// SET RPM
			vy = 0;
			vw = (float)(((float)(p_rc_info->x2) / 720.0f) * 1.0f);
			caterpillar_set_speed(&catp, vx, vy, vw);
			caterpillar_calculate(&catp);

			for(uint8_t i=0; i<2; i++)
			{
				motor_set_speed(&chassis.motor[i], catp.caterpillar_rpm[i]);
			}
			motor_fill_data_output();
			log_i("%d  %d", catp.caterpillar_rpm[0], catp.caterpillar_rpm[1]);
		}

// -----------------------------------------------------------------------------------------------
		if(rc_device_get_state(&chassis_rc, RC_E5_DOWN) == E_OK)
		{
			// Use the foot pedals to control the tracks on both sides
			// FT1 -> forward	FT2 -> backward		FT3 -> right		FT4 -> left
			io_device_get_state(&chassis_io);
			vx = vy = vw = 0;
			if(chassis_io.io_info.ft[0] == DEV_IO_HIGH)
			{
				if(chassis_io.io_info.ft[1] == DEV_IO_HIGH)
				{
					vx = vy = vw = 0;
				} else {
					vx = FOOT_PEDALS_SPEED; 	// SET RPM
				}
			}
			
			if(chassis_io.io_info.ft[1] == DEV_IO_HIGH)
			{
				if(chassis_io.io_info.ft[0] == DEV_IO_HIGH)
				{
					vx = vy = vw = 0;
				} else {
					vx = -FOOT_PEDALS_SPEED;
				}
			}
			
			if(chassis_io.io_info.ft[2] == DEV_IO_HIGH)
			{
				if(chassis_io.io_info.ft[3] == DEV_IO_HIGH)
				{
					vx = vy = vw = 0;
				} else {
					vw = FOOT_PEDALS_SPEED;
				}
			}
			if(chassis_io.io_info.ft[3] == DEV_IO_HIGH)
			{
				if(chassis_io.io_info.ft[2] == DEV_IO_HIGH)
				{
					vx = vy = vw = 0;
				} else {
					vw = -FOOT_PEDALS_SPEED;
				}
			}
			caterpillar_set_speed(&catp, vx, vy, vw);
			caterpillar_calculate(&catp);
//			for(uint8_t i=0; i<2; i++)
//			{
//				motor_set_speed(&chassis.motor[i], catp.caterpillar_rpm[i]);
//			}
//			motor_fill_data_output();
			log_i("%d  %d", catp.caterpillar_rpm[0], catp.caterpillar_rpm[1]);
		}
		
// ------------------------------------------------------------------------------------------------
		osDelay(100);
	}
}


