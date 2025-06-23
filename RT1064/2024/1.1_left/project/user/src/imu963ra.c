#include "IMU963RA.h"

GYROSCOPE gyroscope963ra;
float gyro[3];

void user_imu963ra_init(void)
{
	imu963ra_init();
}


struct RC_Para imu963_Para = {0, 0 , 0.5}; // µÍÍ¨ÂË²¨Ëã×Ó
RC_Filter_pt RC_imu963 = &imu963_Para;

void get_imu963ra_data(void)
{
	imu963ra_get_gyro();
	
	gyroscope963ra.gyro_y=imu963ra_gyro_transition(imu963ra_gyro_y);
	
	if(flag.gyroscope_zero_init==OK)
	{
		gyroscope963ra.gyro_y=gyroscope963ra.gyro_y-gyroscope963ra.yawz;
		gyro[0] = rcHpFiter(gyroscope963ra.gyro_y ,0.5);
		gyro[1] = Sliding_Window_Filtering(1,gyro[0]);
		gyroscope963ra.yaw-=(gyro[1]/100);
		car_system.Omega = gyroscope963ra.yaw;
	}else;
}

void imu963ra_zero_init(void)
{
	for(uint16 i=0;i<500;i++)
	{
		gyroscope963ra.yawzero+=gyroscope963ra.gyro_y;
		system_delay_ms(10);
	}
	gyroscope963ra.yawz=gyroscope963ra.yawzero/500;
	flag.gyroscope_zero_init=OK;
	gpio_set_level(F_beer,GPIO_HIGH);
}

