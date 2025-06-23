#include "user.h"

void user_system_init()
{
	tft180_init();/*��TFT��ʾ����ʼ����*/
	
//	user_uart_init();/*���û����ڳ�ʼ������pcͨѶ��*/
//	
//	openart1_uart_init();/*��openart1���ڳ�ʼ������openartͨѶ��*/
	
	mt9v03x_init();/*�����������ͷ��ʼ����*/

//	imu963ra_init();/*��imu963ra��ʼ����*/

//	motor_init();/*�������ʼ����*/
//	
//	servo_init();
	
//	user_gpio_init();/*�����س�ʼ����*/
//	
//	been_init();
//	
//	inc_pid_init();/*������ʽpid��ʼ����*/
//	dis_pid_init();/*��λ��ʽpid��ʼ����*/
//	
//	user_pit_init();/*���жϳ�ʼ����ʼ����*/
//	
//	read_boma();

//	Fuzzy2_init();
//	
//	if(gpio.boma[0]==0)
//		fuzzy_t.FUZZY_USED=1;/*��ģ��pid������*/
//	else
//		fuzzy_t.FUZZY_USED=0;/*���ر�ģ��pid��*/

//	system_delay_ms(200);
//	imu963ra_zero_init();/*����������Ư��ʼ����*/
//	system_delay_ms(100);
//	imu963ra_set_zero();
}

void imu963ra_set_zero()
{
	imu963ra.yaw=0;/*����������ֵ���㡿*/
	car_system.Omega=0;/*������ƫ�������㡿*/
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


