#ifndef __DRV_CAN_H
#define __DRV_CAN_H

#include "stm32f1xx_hal.h"
#include "fifo.h"

typedef int32_t (*can_stdmsg_rx_callback_t)(CAN_RxHeaderTypeDef *header, uint8_t *data);

#define CAN_TX_FIFO_UNIT_NUM (256)
#define CAN_TX_FIFO_SIZE (CAN_TX_FIFO_UNIT_NUM * sizeof(struct can_std_msg))

typedef struct can_manage_obj *can_manage_obj_t;

struct can_manage_obj
{
	CAN_HandleTypeDef *hcan;
	fifo_t tx_fifo;
	uint8_t *tx_fifo_buffer;
	uint8_t is_sending;
	can_stdmsg_rx_callback_t can_rec_callback;
};

struct can_std_msg
{
	uint32_t std_id;
	uint8_t dlc;
	uint8_t data[8];
};

extern struct can_manage_obj can_manage;

void can_manage_init(void);
uint32_t can_std_transmit(uint16_t std_id, uint8_t *data, uint16_t len);
int32_t can_fifo0_rx_callback_register(can_manage_obj_t m_obj, can_stdmsg_rx_callback_t fun);
uint32_t can_msg_bytes_send(CAN_HandleTypeDef *can, uint16_t std_id, uint8_t *data, uint16_t len);

#endif // __DRV_CAN_H
