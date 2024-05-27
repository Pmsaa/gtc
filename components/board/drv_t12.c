/****************************************************************************
 *  Copyright (C) 2020 RoboMaster.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "usart.h"
#include "drv_t12.h"

extern UART_HandleTypeDef huart2;

int UART_Receive_DMA_No_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint32_t Size);

t12_rx_callback_t t12_rx_callback = NULL;
t12_rx_callback_t t12_forword_callback = NULL;

static uint8_t t12_uart_rx_buff[T12_RX_BUFFER_SIZE];

void t12_uart_init(t12_rx_callback_t rx_fn,
                    t12_rx_callback_t forword_fn)
{
    UART_Receive_DMA_No_IT(&huart2, t12_uart_rx_buff, T12_RX_BUFFER_SIZE);

    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
    t12_rx_callback = rx_fn;
    t12_forword_callback = forword_fn;
}

/**
  * @brief  uart idle interupt
  * @param
  * @retval error code
  */
uint32_t t12_uart_rx_data_handle(UART_HandleTypeDef *huart)
{
    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
    {
        /* clear idle it flag avoid idle interrupt all the time */
        __HAL_UART_CLEAR_IDLEFLAG(huart);

        /* clear DMA transfer complete flag */
        __HAL_DMA_DISABLE(huart->hdmarx);

        /* handle dbus data dbus_buf from DMA */
        if ((T12_RX_BUFFER_SIZE - huart->hdmarx->Instance->CNDTR) == T12_DATA_LEN)
        {
            if (t12_rx_callback != NULL)
            {
                t12_rx_callback(t12_uart_rx_buff, T12_DATA_LEN);
            }

            if (t12_forword_callback != NULL)
            {
                t12_forword_callback(t12_uart_rx_buff, T12_DATA_LEN);
            }
        }

        /* restart dma transmission */
//        __HAL_DMA_SET_COUNTER(huart->hdmarx, T12_RX_BUFFER_SIZE);
		huart->hdmarx->Instance->CNDTR = (uint16_t)T12_RX_BUFFER_SIZE;
        __HAL_DMA_ENABLE(huart->hdmarx);
    }
    return 0;
}

/**
  * @brief  t12 uart dma configration
  * @param
  * @retval error code
  */
int UART_Receive_DMA_No_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint32_t Size)
{
    uint32_t tmp = 0;

    tmp = huart->RxState;
    if (tmp == HAL_UART_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0))
        {
            return HAL_ERROR;
        }

        /* Process Locked */
        __HAL_LOCK(huart);

        huart->pRxBuffPtr = pData;
        huart->RxXferSize = Size;

        huart->ErrorCode = HAL_UART_ERROR_NONE;

        /* Enable the DMA Stream */
        HAL_DMA_Start(huart->hdmarx, (uint32_t)&huart->Instance->DR,
                      (uint32_t)pData, Size);

        /* Enable the DMA transfer for the receiver request by setting the DMAR bit
        in the UART CR3 register */
        SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);

        /* Process Unlocked */
        __HAL_UNLOCK(huart);

        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}
