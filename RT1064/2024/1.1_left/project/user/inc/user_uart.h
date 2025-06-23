#ifndef __user_uart_h
#define __user_uart_h

#include "user_include.h"


#define F_byte0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )
#define F_byte1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define F_byte2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define F_byte3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
	
void user_uart_init(void);
void put_angle(uint8 even,uint16 servo1PWM,uint16 servo2PWM,uint16 servo3PWM,uint16 servo4PWM,uint16 servo5PWM);
void uart8_Rece_Prepare(uint8 data);
void uart8_rx_interrupt_handler(void);
void ano7(int16 data1,int16 data2,int16 data3,int16 data4);

float h_to_f(int hex);
#endif