/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define led_Pin GPIO_PIN_13
#define led_GPIO_Port GPIOC
#define spi_cs_Pin GPIO_PIN_4
#define spi_cs_GPIO_Port GPIOA
#define jd3_Pin GPIO_PIN_4
#define jd3_GPIO_Port GPIOC
#define jd4_Pin GPIO_PIN_5
#define jd4_GPIO_Port GPIOC
#define jd1_Pin GPIO_PIN_0
#define jd1_GPIO_Port GPIOB
#define jd2_Pin GPIO_PIN_1
#define jd2_GPIO_Port GPIOB
#define oled_dc_Pin GPIO_PIN_2
#define oled_dc_GPIO_Port GPIOB
#define oled_res_Pin GPIO_PIN_10
#define oled_res_GPIO_Port GPIOB
#define oled_cs1_Pin GPIO_PIN_11
#define oled_cs1_GPIO_Port GPIOB
#define oled_cs2_Pin GPIO_PIN_12
#define oled_cs2_GPIO_Port GPIOB
#define kg1_Pin GPIO_PIN_4
#define kg1_GPIO_Port GPIOB
#define kg2_Pin GPIO_PIN_5
#define kg2_GPIO_Port GPIOB
#define kg3_Pin GPIO_PIN_6
#define kg3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
