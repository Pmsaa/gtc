#include "sw_ft.h"

#define LOG_TAG "drv.io"
#define LOG_OUTPUT_LEVEL LOG_INFO
#include "log.h"

uint8_t ft1_count = 0;
uint8_t ft2_count = 0;
uint8_t ft3_count = 0;
uint8_t ft4_count = 0;
static uint8_t ft_count[DEV_FT_NUM] = {0};
int32_t io_device_register(io_device_t io_dev, const char *name)
{
	device_assert(io_dev != NULL);
	
	((device_t)io_dev)->type = DEVICE_IO;
	
	io_dev->get_data = NULL;
	io_dev->get_state = NULL;
	
	for(uint8_t i=0; i<4; i++)
	{
		io_dev->io_info.ft[i] = DEV_IO_DOWN;
	}
	
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
	// In order to avoid signal fluctuations, 
	// only more than three consecutive levels of the same level will change state
	for(uint8_t i=0; i<4; i++)
	{
		if(io_dev->io_info.ft[i] == DEV_IO_DOWN)
		{
			switch(i)
			{
				case 0:
					if(HAL_GPIO_ReadPin(FT1_PORT, FT1_PIN) == DEV_IO_HIGH)
						ft_count[i] += 1;
					else if(ft_count[i] != 0)
						ft_count[i] = 0;
					break;
				case 1:
					if(HAL_GPIO_ReadPin(FT2_PORT, FT2_PIN) == DEV_IO_HIGH)
						ft_count[i] += 1;
					else if(ft_count[i] != 0)
						ft_count[i] = 0;
					break;
				case 2:
					if(HAL_GPIO_ReadPin(FT3_PORT, FT3_PIN) == DEV_IO_HIGH)
						ft_count[i] += 1;
					else if(ft_count[i] != 0)
						ft_count[i] = 0;
					break;
				case 3:
					if(HAL_GPIO_ReadPin(FT4_PORT, FT4_PIN) == DEV_IO_HIGH)
						ft_count[i] += 1;
					else if(ft_count[i] != 0)
						ft_count[i] = 0;
					break;
			}
		}
		else
		{
			switch(i)
			{
				case 0:
					if(HAL_GPIO_ReadPin(FT1_PORT, FT1_PIN) == DEV_IO_DOWN)
						ft_count[i] += 1;
					else if(ft_count[i] != 0)
						ft_count[i] = 0;
					break;
				case 1:
					if(HAL_GPIO_ReadPin(FT2_PORT, FT2_PIN) == DEV_IO_DOWN)
						ft_count[i] += 1;
					else if(ft_count[i] != 0)
						ft_count[i] = 0;
					break;
				case 2:
					if(HAL_GPIO_ReadPin(FT3_PORT, FT3_PIN) == DEV_IO_DOWN)
						ft_count[i] += 1;
					else if(ft_count[i] != 0)
						ft_count[i] = 0;
					break;
				case 3:
					if(HAL_GPIO_ReadPin(FT4_PORT, FT4_PIN) == DEV_IO_DOWN)
						ft_count[i] += 1;
					else if(ft_count[i] != 0)
						ft_count[i] = 0;
					break;
			}
		}
		if(ft_count[i] == 2)
		{
			if(io_dev->io_info.ft[i] == DEV_IO_HIGH)
				io_dev->io_info.ft[i] = DEV_IO_DOWN;
			else
				io_dev->io_info.ft[i] =DEV_IO_HIGH;
			ft_count[i] = 0;
		}
	}

	return 0;
}
 
