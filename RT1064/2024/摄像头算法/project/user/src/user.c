#include "user.h"

void user_system_init()
{
	tft180_init();/*【TFT显示屏初始化】*/
	
//	user_uart_init();/*【用户串口初始化用于pc通讯】*/
//	
//	openart1_uart_init();/*【openart1串口初始化用于openart通讯】*/
	
	mt9v03x_init();/*【总钻风摄像头初始化】*/

//	imu963ra_init();/*【imu963ra初始化】*/

//	motor_init();/*【电机初始化】*/
//	
//	servo_init();
	
//	user_gpio_init();/*【开关初始化】*/
//	
//	been_init();
//	
//	inc_pid_init();/*【增量式pid初始化】*/
//	dis_pid_init();/*【位置式pid初始化】*/
//	
//	user_pit_init();/*【中断初始化初始化】*/
//	
//	read_boma();

//	Fuzzy2_init();
//	
//	if(gpio.boma[0]==0)
//		fuzzy_t.FUZZY_USED=1;/*【模糊pid开启】*/
//	else
//		fuzzy_t.FUZZY_USED=0;/*【关闭模糊pid】*/

//	system_delay_ms(200);
//	imu963ra_zero_init();/*【陀螺仪零漂初始化】*/
//	system_delay_ms(100);
//	imu963ra_set_zero();
}

void imu963ra_set_zero()
{
	imu963ra.yaw=0;/*【陀螺仪数值清零】*/
	car_system.Omega=0;/*【车身偏航角清零】*/
	imu963ra.vx=0;
	imu963ra.vy=0;
	imu963ra.dx=0;
	imu963ra.dy=0;
}

void user_pit_init(void)
{
	interrupt_set_priority(PIT_IRQn,2);
	pit_ms_init(PIT_CH0,10);
	pit_ms_init(PIT_CH1,1000);
	pit_ms_init(PIT_CH2,10);
	pit_ms_init(PIT_CH3,10);
}


