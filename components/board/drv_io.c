#include "drv_io.h"

void drv_io_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	/* -------------------- SW ----------------------------- */	
	HAL_GPIO_WritePin(SW1_PORT, SW1_PIN | SW2_PIN | SW3_PIN, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = SW1_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SW1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = SW2_PIN;
	HAL_GPIO_Init(SW2_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = SW3_PIN;
	HAL_GPIO_Init(SW3_PORT, &GPIO_InitStruct);

	/* -------------------- FT ----------------------------- */
	GPIO_InitStruct.Pin = FT1_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(FT1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = FT2_PIN;
	HAL_GPIO_Init(FT2_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = FT3_PIN;
	HAL_GPIO_Init(FT3_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = FT4_PIN;
	HAL_GPIO_Init(FT4_PORT, &GPIO_InitStruct);
}
