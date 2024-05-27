/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for systemService */
osThreadId_t systemServiceHandle;
const osThreadAttr_t systemService_attributes = {
  .name = "systemService",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void systemLedTask(void * pvParameters);

TaskHandle_t systemledHandle = NULL;
/* USER CODE END FunctionPrototypes */

void SystemServiceTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of systemService */
  systemServiceHandle = osThreadNew(SystemServiceTask, NULL, &systemService_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  
  
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  xTaskCreate(systemLedTask, "systemled", 128, NULL, 1, &systemledHandle);
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_SystemServiceTask */
/**
  * @brief  Function implementing the systemService thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_SystemServiceTask */
__weak void SystemServiceTask(void *argument)
{
  /* USER CODE BEGIN SystemServiceTask */
  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(led_GPIO_Port, led_Pin);
	  vTaskDelay(100);
  }
  /* USER CODE END SystemServiceTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void systemLedTask(void * pvParameters)
{
	for(;;)
	{
		HAL_GPIO_TogglePin(led_GPIO_Port, led_Pin);
		vTaskDelay(500);
	}
}
/* USER CODE END Application */

