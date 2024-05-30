#ifndef __SW_FT_H
#define __SW_FT_H

#include "stm32f1xx_hal.h"
#include "device.h"
#include "drv_io.h"

typedef struct io_device *io_device_t;
typedef struct io_info *io_info_t;

#define DEV_IO_HIGH		1
#define DEV_IO_DOWN		0

#define DEV_SW_1		1
#define DEV_SW_2		2
#define DEV_SW_3		3

#define DEV_FT_NUM		4

struct io_info
{
	uint8_t sw1;
	uint8_t sw2;
	uint8_t sw3;

	uint8_t ft1;
	uint8_t ft2;
	uint8_t ft3;
	uint8_t ft4;
	
	uint8_t ft[DEV_FT_NUM]
};

struct io_device
{
	struct device parent;
	struct io_info io_info;
	struct io_info last_io_info;
	uint16_t state;
	void (*get_data)(io_device_t, uint8_t *);
	void (*get_state)(io_device_t);
	
};

int32_t io_device_register(io_device_t io_dev, const char *name);
int32_t io_device_set_bit(io_device_t io_dev, uint8_t sw, uint8_t io_state);
int32_t io_device_clean_bit(io_device_t io_dev);
int32_t io_device_get_state(io_device_t io_dev);


#endif // __SW_FT_H
