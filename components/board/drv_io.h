#ifndef __DRV_IO_H
#define __DRV_IO_H

#include "stm32f1xx_hal.h"

#define SW1_PIN		GPIO_PIN_4
#define SW1_PORT	GPIOB

#define SW2_PIN		GPIO_PIN_5
#define SW2_PORT	GPIOB

#define SW3_PIN		GPIO_PIN_6
#define SW3_PORT	GPIOB

#define FT1_PIN		GPIO_PIN_0
#define FT1_PORT	GPIOB

#define FT2_PIN		GPIO_PIN_1
#define FT2_PORT	GPIOB

#define FT3_PIN		GPIO_PIN_4
#define FT3_PORT	GPIOC

#define FT4_PIN		GPIO_PIN_5
#define FT4_PORT	GPIOC


void drv_io_init(void);

#endif // __DRV_IO_H
