#ifndef __MOTOR_H
#define __MOTOR_h

#include "stm32f1xx_hal.h"
#include "device.h"

typedef struct motor_data *motor_data_t;
typedef struct motor_device *motor_device_t;


enum motor_state
{
	motor_stop,
	motor_forward,
	motor_backward,
	motor_brake
};

struct motor_data
{

	uint16_t target_speed_rate;
	uint16_t node_id;
	uint16_t baud;
	uint16_t heart_rate;
	uint8_t control_mode;
	uint8_t running_direction;
	uint16_t max_rpm_value;
	uint16_t min_rpm_value;
	uint16_t IN1_6A;
	uint16_t IN1_6B;
	uint16_t avoidance_time;
	uint8_t avoidanc4_direction;
	uint8_t OUT12;
	uint8_t OUT34;
	uint16_t brake_delay;
	uint16_t turn_light;
	uint16_t voltage;
	uint16_t current;
	uint16_t tempure;
	uint16_t speed_rpm;
	uint16_t round_cnt;
	enum motor_state state;
};

struct can_msg
{
	uint32_t id : 29;
	uint32_t ide : 1;
	uint32_t rtr : 1;
	uint32_t rsv : 1;
	uint32_t len : 8;
	uint32_t priv : 8;
	uint32_t hdr : 8;
	uint32_t reserved : 8;
	uint8_t data[8];
};

struct motor_device
{
	struct device parent;
	struct motor_data data;
	
	uint8_t node_id;
	
	int32_t speed_rate;
	int8_t can_send_flag;
	
	void (*get_date)(motor_device_t, uint8_t*);
};

typedef int32_t (*fn_can_send)(struct can_msg);

int32_t motor_register(motor_device_t motor_dev, const char* name);
void motor_can_send_register(fn_can_send fn);

motor_data_t motor_get_data(motor_device_t motor_dev);

int32_t motor_set_speed(motor_device_t motor_dev, int16_t speed_rate);
int32_t motor_set_can_send_flag(motor_device_t motor_dev, uint8_t flag);

void motor_fill_data_output(void);
int32_t motor_canstd_send(struct can_msg msg);

void motor_set_control_mode(void);

#endif // __MOTOR_H
