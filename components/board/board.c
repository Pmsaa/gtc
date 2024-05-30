#include "board.h"

#include "os_timer.h"

#define LOG_TAG	"board"
#define LOG_OUTPUT_LEVEL	LOG_INFO
#include "log.h"

extern struct rc_device chassis_rc;

int32_t t12_rx_data_by_uart(uint8_t *buff, uint16_t len)
{
	rc_device_date_update(&chassis_rc, buff);
	return 0;
}

int32_t can_rx_callback(CAN_RxHeaderTypeDef *header, uint8_t *data)
{
	log_i("StdId:%x; DLC:%d.", header->StdId, header->DLC);
	log_i("data:%x %x %x %x %x %x %x %x.", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
	
	return 0;
}

int32_t board_config(void)
{
	usart1_manage_init();
    log_printf("\r\n\r\n"
               "*********** Gantry tracked chassis **************\r\n");
    log_printf("* Copy right: All right reserved.\r\n");
    log_printf("* Release Time: %s.\r\n", __TIME__);
    log_printf("********************************************\r\n");

	soft_timer_init();
	usart3_manage_init();
	can_manage_init();
	
	t12_uart_init(t12_rx_data_by_uart, NULL);
	drv_io_init();

	motor_can_send_register(motor_canstd_send);
	can_fifo0_rx_callback_register(&can_manage, can_rx_callback);
	

	return 0;
}

