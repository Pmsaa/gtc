#include "sw_ft.h"

#define LOG_TAG "drv.io"
#define LOG_OUTPUT_LEVEL LOG_INFO
#include "log.h"

int32_t io_device_register(io_device_t io_dev, const char *name)
{
	device_assert(io_dev != NULL);
	
	((device_t)io_dev)->type = DEVICE_IO;
	
	io_dev->get_data = NULL;
	io_dev->get_state = NULL;
	
	device_init(&(io_dev->parent), name);
	return 0;
}

int32_t io_device_set_bit(io_device_t io_dev, uint8_t sw, uint8_t io_state)
{
	if(sw == 1)
	{
		HAL_GPIO_WritePin(SW1_PORT, SW1_PIN, io_state);
		io_dev->io_info.sw1 = io_state;
	}else if(sw == 2)
	{
		HAL_GPIO_WritePin(SW2_PORT, SW2_PIN, io_state);
		io_dev->io_info.sw2 = io_state;
	}else if(sw == 3)
	{
		HAL_GPIO_WritePin(SW3_PORT, SW3_PIN, io_state);
		io_dev->io_info.sw3 = io_state;
	}
	return 0;
}

int32_t io_device_clean_bit(io_device_t io_dev)
{
	HAL_GPIO_WritePin(SW1_PORT, SW1_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SW2_PORT, SW2_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SW3_PORT, SW3_PIN, GPIO_PIN_RESET);
	
	io_dev->io_info.sw1 = 0;
	io_dev->io_info.sw2 = 0;
	io_dev->io_info.sw3 = 0;
	
	return 0;
}

int32_t io_device_get_state(io_device_t io_dev)
{
	io_dev->io_info.ft1 = HAL_GPIO_ReadPin(FT1_PORT, FT1_PIN);
	io_dev->io_info.ft2 = HAL_GPIO_ReadPin(FT2_PORT, FT2_PIN);
	io_dev->io_info.ft3 = HAL_GPIO_ReadPin(FT3_PORT, FT3_PIN);
	io_dev->io_info.ft4 = HAL_GPIO_ReadPin(FT4_PORT, FT4_PIN);
	return 0;
}
 
