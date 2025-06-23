#include "IMU660RA.h"

extern int16 imu660ra_gyro_x, imu660ra_gyro_y, imu660ra_gyro_z;            // ÈýÖáÍÓÂÝÒÇÊý¾Ý   gyro (ÍÓÂÝÒÇ)
extern int16 imu660ra_acc_x, imu660ra_acc_y, imu660ra_acc_z;  
extern float gyro,gyroL,gyroH;

IMU660RA imu660ra;

void get_imu660ra_data()
{
	imu660ra_get_gyro();

	imu660ra.gyro_z=(float)imu660ra_gyro_z/16.4f;
	
	gyro = imu660ra.gyro_z+imu660ra.yawz;

	gyro = averageV(gyro);

	imu660ra.yaw-=(gyro/100);//0.96
}

void imu660ra_zero_init()
{
	for(uint16 i=0;i<100;i++)
	{
		imu660ra.yawz+=imu660ra.gyro_z/100;
		system_delay_ms(10);
	}
	imu660ra.yawz=imu660ra.yawz/100;
}
