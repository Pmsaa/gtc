#ifndef __BOARD_H
#define __BOARD_H

#include "sys.h"

#include "drv_uart.h"
#include "drv_t12.h"
#include "sbus.h"

#include "can.h"
#include "drv_can.h"

#include "drv_io.h"

int32_t t12_rx_data_by_uart(uint8_t *buff, uint16_t len);

int32_t board_config(void);


#endif // __BOARD_H
