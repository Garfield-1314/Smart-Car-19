#ifndef __user_h
#define __user_h
/********************************************************
�����´��ͷ�ļ���
********************************************************/
#include "zf_common_headfile.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "image.h"

#include "motor.h"
#include "MPU6050.h"
#include "IMU660RA.h"
#include "IMU963RA.h"
#include "gpio.h"
#include "servo.h"
#include "openart1.h"
#include "openart2.h"

#include "user_usart.h"
#include "even_solution.h"

#include "Fuzzy.h"
#include "PID.h"
#include "Filter.h"
#include "car_attitude.h"
/********************************************************
�����´�Ŷ��塿
********************************************************/
//#define PI 3.1415926

#define F_beer B11
#define FUZZY_SEG_NUMS 7   //7��ģ���Ӽ�

#define red 2
#define green 3
#define blue 4
#define open 0
#define close 1

/********************************************************
�����´�ź������塿
********************************************************/
void user_system_init(void);
void user_pit_init(void);
void imu963ra_set_zero(void);

/********************************************************
�����´������Ľṹ�塿
********************************************************/

typedef struct
{
	uint8 cross_flag1;
}PIC_FLAG;


typedef struct
{
	uint16 rx;
	uint16 ry;
	
	uint8 x[20];
	uint8 y[20];
	
	int16 Tx[20];
	int16 Ty[20];
}PICTURE;

typedef struct
{
	volatile int16 encoder[4];            //��������¼��������
	volatile int16 rc_encoder[4];
	volatile float speed[4];							//ʹ�ñ�������������ٶ�
	volatile float distance[4];           //��������¼�����
	volatile float distance_road;
	volatile int16 set_pwm[4];						//����ʽ�����pwm
}WHEEL;

typedef struct
{
	float gyro_x;
	float gyro_y;
	float gyro_z;
	
	float acc_x;
	float acc_y;
	float acc_z;
	
	float yaw;
	
	float roll;
	float pitch;
}MPU6050;


typedef struct
{
	float gyro_x;
	float gyro_y;
	float gyro_z;
	
	float acc_x;
	float acc_y;
	float acc_z;
	
	float yaw;
	
	float roll;
	float pitch;
	
	float yawz;
}IMU660RA;


typedef struct
{
	float gyro_x;
	float gyro_y;
	float gyro_z;
	
	float acc_x;
	float acc_y;
	float acc_z;

	float mag_x;
	float mag_y;
	float mag_z;
	
	float yaw;	
	float roll;
	float pitch;
	
	float yawzero;
	float yawz;
	
	float accxzero;
	float accyzero;
	float accxz;
	float accyz;
	float vxzero;
	float vyzero;
	float vxz;
	float vyz;
	float vx;
	float vy;
	float dx;
	float dy;
}IMU963RA;

typedef struct
{
	uint16 time;
	
	int16 speed;
	
	float distance;
	float at_distance;
	
	float chassis_dx;                          //��ǰ��������x����
	float chassis_dy;                          //��ǰ��������y����
	float Omega;                               //��ǰ����ƫ����
	
	float set_Omega;                           //�趨��ƫ����	
	
	float Vtx;                                 //����x�᷽���ϵ��ٶ�
	float Vty;                                 //����y�᷽���ϵ��ٶ�
	
	
	float Vx;                                  //���˶�ѧ�����x�᷽���ϵ��ٶ�
	float Vy;                                  //���˶�ѧ�����y�᷽���ϵ��ٶ�
	
	int16 Vw[4];                               //���˶�ѧ������ĸ����ӵ�ת��
	
	float atx;                                 //���ڴ���Ŀ��x��������λ��pid
	float aty;                                 //���ڴ���Ŀ��y��������λ��pid
	
	float er_x;
	float er_y;
	
}CAR_SYSTEM;

typedef struct
{
	uint8 boma[2]; 
	uint8 key[4];
}GPIO;



/********************************************************
�����´���㷨�Ľṹ�塿
********************************************************/
typedef struct
{
	volatile float Kk;                         //kalman����
	volatile float Eest;                       //�������
	volatile float Eest_last;                  //��һ�ι������
	volatile float Emea;                       //�������
	volatile float Emea_last;                  //��һ�β������
	
	volatile float data;                       //��������
	volatile float data_true;                  //����ֵ
	volatile float data_last;                  //��һ�ι�������
}KALMAN;


typedef struct 
{
	 volatile int16  speed; 
   volatile double   Kp[10];             // �������� Proportional Const  ��0-3��Ϊ�ĸ���������ʽpid�Ĳ���
   volatile double   Ki[10];             // ���ֳ��� Integral Const			  ��4��5����x��y������λ��pid�Ĳ���
   volatile double   Kd[10];             // ΢�ֳ��� Derivative Const			��6����������yawλ��ʽpid�Ĳ���
   volatile int      Error1[10];         // Error[n-1]										��7��8��ͼƬ������ͷ����λ��ʽpid�Ĳ���
   volatile int      Error2[10];         // Error[n-2]
   volatile int      iError[10];         // Error[n]
	
	 volatile float integral[10];
}PID;    

typedef struct
{
	  float temp;  //�ݴ�ֵ,�洢RC_baro
    float value; //�˲�ֵ
    float RC;    //��ͨ�˲�����
	
}RCFILTER;


typedef struct
{
    bool FUZZY_USED;   //�Ƿ�ʹ��ģ��PID
 
    float max_e;    // e  \in [-max_e,max_e]
    float max_ec;   // ec \in [-max_ec,max_ec]
    float max_kp;   // kp \in kp0+[-max_kp,max_kp] kp0-max_kp>0
    float max_ki;
    float max_kd;
 
    uint8 rule_kp[7][7];  //ģ�������
    uint8 rule_ki[7][7];   
    uint8 rule_kd[7][7];
		
		float d_kp[4],d_ki[4],d_kd[4];
}fuzzy_pid_st;
 

typedef struct
{
	uint8 dir_l[10]; 
	uint8 dir_r[10]; 
	uint8 point_l[200];
	uint8 point_r[200];
	uint8 L_L_NUM;
	uint8 R_L_NUM;
}CDIR;

/********************************************************
������ṹ�塿
********************************************************/
typedef struct
{
	uint8 race_move;
	uint8 car_move;
	uint8 car_turn_over;
	uint8 car_move_dot;
	uint8 stop_encoder;
	uint8 round_left[2];
	uint8 new_omega;
	uint8 move_i;
	
	uint8 image_over;
}FLAG;
/********************************************************
�����´���ⲿ���õĶ��塿
********************************************************/
extern WHEEL wheel;
extern IMU963RA imu963ra;
extern CAR_SYSTEM car_system;
extern GPIO gpio;
extern PID pid;
extern  fuzzy_pid_st fuzzy_t;
extern uint16 rcx,rcy;
extern float center_t;
extern CDIR cdir;
extern FLAG flag1;
extern int16 x[20],y[20];

extern uint16 stime;
extern uint8 flag[10];
extern float xlast,ylast;
extern uint16 color[2];
#endif