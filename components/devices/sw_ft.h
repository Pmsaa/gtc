#ifndef __SW_FT_H
#define __SW_FT_H

#include "stm32f1xx_hal.h"
#include "device.h"
#include "drv_io.h"

typedef struct io_device *io_device_t;
typedef struct io_info *io_info_t;



struct io_info
{
	uint8_t sw1;
	uint8_t sw2;
	uint8_t sw3;
	
	uint8_t ft1;
	uint8_t ft2;
	uint8_t ft3;
	uint8_t ft4;
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


#endif // __SW_FT_H
