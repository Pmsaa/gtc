#include "motor.h"
#include "drv_can.h"

#define LOG_TAG "drv.motor"
#define LOG_OUTPUT_LEVEL LOG_INFO 
#include "log.h"

static fn_can_send motor_can_send = NULL;

int32_t motor_register(motor_device_t motor_dev, const char* name)
{
	device_assert(motor_dev != NULL);
	device_assert(name != NULL);
	
	motor_dev->parent.type = DEVICE_MOTOR;
	motor_dev->get_date = NULL;
	
	device_init(&(motor_dev->parent), name);
	
	return E_OK;
}


void motor_can_send_register(fn_can_send fn)
{
	device_assert(fn != NULL);
	motor_can_send = fn;
}

motor_data_t motor_get_data(motor_device_t motor_dev)
{
	device_assert(motor_dev != NULL);
	return &(motor_dev->data);
}

int32_t motor_set_speed(motor_device_t motor_dev, int16_t speed_rate)
{
	device_assert(motor_dev != NULL);
	motor_dev->speed_rate = speed_rate;
	return E_OK;
}

int32_t motor_set_can_send_flag(motor_device_t motor_dev, uint8_t flag)
{
	device_assert(motor_dev != NULL);
	motor_dev->can_send_flag = flag;
	return E_OK;
}


struct can_msg motor_msg[2];

void motor_fill_data_output(void)
{
	struct device *object;
	list_t *node = NULL;
	struct device_information *information;
	motor_device_t motor_dev;
	uint8_t node_id;
	
	memset(&motor_msg, 0, sizeof(motor_msg));
	
	information = get_device_information();
	
	for(node = information->object_list.next;
		node != &(information->object_list);
		node = node->next)
	{
		object = list_entry(node, struct device, list);
		motor_dev = (motor_device_t)object;
		if(motor_dev->parent.type == DEVICE_MOTOR)
		{
			node_id = motor_dev->node_id;
			motor_msg[node_id - 1].id = 0x600+node_id;
			
			memset(&motor_msg[node_id - 1].data, 0, sizeof(motor_msg[node_id - 1].data));
			motor_msg[node_id - 1].data[0] = 0x2b;
			motor_msg[node_id - 1].data[4] = motor_dev->speed_rate;
			
			motor_msg[node_id - 1].len = 8;
			
			if(motor_dev->can_send_flag == 1)
			{
				motor_can_send(motor_msg[node_id-1]);
				motor_dev->can_send_flag = 0;
			}
		}
	}
}

int32_t motor_canstd_send(struct can_msg msg) 
{
	can_std_transmit(msg.id, msg.data, msg.len);
	return E_OK;
}
