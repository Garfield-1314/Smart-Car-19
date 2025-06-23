#include "IMU963RA.h"

IMU963RA imu963ra;
float yaw[2];
float accx[2],accy[2];
void get_imu963ra_data(void)
{
//	imu963ra_get_acc();
	imu963ra_get_gyro();
//	imu963ra_get_mag();
	
//	imu963ra.acc_x=imu963ra_acc_transition(imu963ra_acc_x);
//	imu963ra.acc_y=imu963ra_acc_transition(imu963ra_acc_y);
//	imu963ra.acc_z=imu963ra_acc_transition(imu963ra_acc_z);
	
//	imu963ra.gyro_x=imu963ra_gyro_transition(imu963ra_gyro_x);
//	imu963ra.gyro_y=imu963ra_gyro_transition(imu963ra_gyro_y);
	imu963ra.gyro_z=imu963ra_gyro_transition(imu963ra_gyro_z);
	
//	imu963ra.mag_x=imu963ra_mag_transition(imu963ra_mag_x);
//	imu963ra.mag_y=imu963ra_mag_transition(imu963ra_mag_y);
//	imu963ra.mag_z=imu963ra_mag_transition(imu963ra_mag_z);
	
	imu963ra.gyro_z=imu963ra.gyro_z-imu963ra.yawz;
//	imu963ra.acc_x=imu963ra.acc_x-imu963ra.accxz;
//	imu963ra.acc_y=imu963ra.acc_y-imu963ra.accyz;
	
//	imu963ra.vx=0;imu963ra.vy=0;
	
	
//	imu963ra.vy+=imu963ra.acc_y/100*100;
	
//	imu963ra.dx+=imu963ra.vx;
//	imu963ra.dy+=imu963ra.vy;

	yaw[0] = rcHpFiter(imu963ra.gyro_z,0.404);
	yaw[1] = Sliding_Window_Filtering(1,yaw[0]);
	imu963ra.yaw+=(yaw[1]/100)+0.000019;
	car_system.Omega = imu963ra.yaw;
	
//	accx[0] = rcHpFiter2(imu963ra.acc_x,0.6);
//	accx[1] = Sliding_Window_Filtering2(1,accx[0]);
//	imu963ra.vx+=accx[1]*10*10/1000;
//	
//	accy[0] = rcHpFiter3(imu963ra.acc_y,0.6);
//	accy[1] = Sliding_Window_Filtering3(1,accy[0]);
//	imu963ra.vy+=accy[1]*10*10/1000;
}

void imu963ra_zero_init()
{
	for(uint16 i=0;i<1000;i++)
	{
		imu963ra.yawzero+=imu963ra.gyro_z;
//		imu963ra.accxzero+=imu963ra.acc_x;
//		imu963ra.accyzero+=imu963ra.acc_y;
		system_delay_ms(1);
	}
	imu963ra.yawz=imu963ra.yawzero/1000;
//	imu963ra.accxz=imu963ra.accxzero/1000;
//	imu963ra.accyz=imu963ra.accyzero/1000;
}

//void imu963ra_v_zero_init()
//{
//	for(uint16 i=0;i<1000;i++)
//	{
//		imu963ra.yawzero+=imu963ra.gyro_z;
//		imu963ra.accxzero+=imu963ra.acc_x;
//		imu963ra.accyzero+=imu963ra.acc_y;
//		system_delay_ms(1);
//	}
//}