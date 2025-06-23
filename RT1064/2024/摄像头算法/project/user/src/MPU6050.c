#include "MPU6050.h"


MPU6050 mpu6050;

extern int16 mpu6050_gyro_x,mpu6050_gyro_y,mpu6050_gyro_z;               // хЩжАмсбщргйЩ╬щ      gyro (мсбщрг)
extern int16 mpu6050_acc_x,mpu6050_acc_y,mpu6050_acc_z;  

void user_mpu6050_init()
{
	mpu6050_init();
}

float gyro,gyroL,gyroH;
void get_mpu6050_gyro_acc()
{
	mpu6050_get_gyro();
	
	mpu6050.gyro_z=(float)mpu6050_gyro_z/16.4f;

}

