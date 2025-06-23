#include "user.h"

void user_system_init()
{
	user_imu963ra_init();
	
	motor_init();
	
	servo_init();
	
	Fuzzy_init();
	
	pid_init();
	
	user_gpio_init();
	
	mt9v03x_init();
	
	tft180_init();
	
	MXC_uart_init();
	
	openart2_uart_init();
	
	user_uart_init();
	
	user_pit_init();
	
	servo_a_keep();
	
	imu963ra_zero_init();
}

void user_pit_init()
{
	interrupt_set_priority(PIT_IRQn,2);
	pit_ms_init(PIT_CH0,10);
	pit_ms_init(PIT_CH1,10);
	pit_ms_init(PIT_CH2,10);
	pit_ms_init(PIT_CH3,100);
}
