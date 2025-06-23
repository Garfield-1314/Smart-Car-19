#ifndef __USER_INCLUDE_H
#define __USER_INCLUDE_H

#include "user_include.h"

#include "zf_common_headfile.h"

#include "user.h"
#include "motor.h"
#include "Filter.h"
#include "IMU963RA.h"
#include "car_system.h"
#include "Fuzzy_PID.h"
#include "PID.h"
#include "gpio.h"
#include "openart_uart.h"
#include "image.h"
#include "user_uart.h"
#include "even_solution.h"
#include "math.h"
#include "servo.h"
#include "time.h"

#define OK 1
#define NO 0

#define L_O 1
#define R_O 2

#define L_C 1
#define R_C 2

typedef struct
{
	uint16 sys_time;
	uint16 micro_distance_time;
	uint16 identify_card_time;
	uint16 cross_card_time;
	uint16 Scattered_time;
	uint16 Scattered_en_time;
	uint16 obstacle_time;
	uint16 Line_time;
}TIME;

typedef struct
{
	float speed;
	
	float distance;
	
	float distancey;	
	
	float at_distance;
	
	float chassis_dx;                          //��ǰ��������x����
	float chassis_dy;                          //��ǰ��������y����
	float Omega;                               //��ǰ����ƫ����
	
	float set_Omega;                           //�趨��ƫ����	
	
	float Vtx;                                 //����x�᷽���ϵ��ٶ�
	float Vty;                                 //����y�᷽���ϵ��ٶ�
	
	
	float Vx;                                  //���˶�ѧ�����x�᷽���ϵ��ٶ�
	float Vy;                                  //���˶�ѧ�����y�᷽���ϵ��ٶ�
	
	float Vw[4];                               //���˶�ѧ������ĸ����ӵ�ת��
	
	float atx;                                 //���ڴ���Ŀ��x��������λ��pid
	float aty;                                 //���ڴ���Ŀ��y��������λ��pid
	

	
}CAR_SYSTEM;


typedef struct
{
	uint8 gyroscope_zero_init;
	
	uint8 L_R_omega;
	
	uint8 get_distance;

	uint8 keep_omega;
	
//	uint8 round_left[3];
//	
//	uint8 round_right[3];
//	
//	uint8 cross_round_left[2];
//	
//	uint8 cross_round_right[2];
	
	uint8 identify_card;
		
	uint8 identify_num_word;
	
	uint8 citie;
	
	uint8 put_over;
	
	uint8 get_card_ok;
	
	uint8 cross_round_card_over;
		
	uint8 Scattered_card_EN;
	
	uint8 put_Scattered_card;
	
	uint8 cirque_num;
}FLAG;

typedef struct
{
	uint8 cross_left_POI_flag;
	uint8 cross_right_POI_flag;
	uint8 cross_left_POIN_flag;
	uint8 cross_right_POIN_flag;
	
	uint8 cross_left_DIR_flag;
	uint8 cross_right_DIR_flag;
	uint8 cross_left_DIRN_flag;
	uint8 cross_right_DIRN_flag;

	uint8 cross_angle_L_flag;
	uint8 cross_angle_R_flag;
	
	uint8 cross_POIL_NUM_flag;
	uint8 cross_POIR_NUM_flag;
	
	uint8 cross_all_flag;
	
	uint8 round_left_POI_flag;
	uint8 round_right_POI_flag;
	uint8 round_left_POIN_flag;
	uint8 round_right_POIN_flag;
	
	uint8 round_left_DIR_flag;	
	uint8 round_right_DIR_flag;
	uint8 round_left_DIRN_flag;
	uint8 round_right_DIRN_flag;

	uint8 round_angle_L_flag;
	uint8 round_angle_R_flag;

	uint8 round_POIL_NUM_flag;
	uint8 round_POIR_NUM_flag;
	
	uint8 round_left_flag;
	uint8 round_left_flag_num;
	uint8 round_right_flag;
	uint8 round_right_flag_num;
	
	uint8 R_OR_L;
	
	uint8 Scattered_card_flag;
	
	uint8 endline_flag;
	
	uint8 cirque_num;
	
	uint8 obstacle_POIL_flag;
	uint8 obstacle_POIR_flag;
	uint8 obstacle_POI_NUM_flag;
	uint8 obstacle_angle_flag;
	uint8 obstacle_color_flag;
	uint8 obstacle_left_flag;
	uint8 obstacle_right_flag;
	
	uint8 ramp_wide_flag;
	uint8 ramp_POI_NUM_flag;
	uint8 ramp_flag;
}PIC_FLAG;

typedef struct
{
	uint8 dir_l[10]; 
	uint8 dir_r[10]; 
	uint8 point_l[200];
	uint8 point_r[200];
	uint8 L_L_NUM;
	uint8 R_L_NUM;
}CDIR;

typedef struct 
{
	 volatile int16  speed; 
   volatile float   Kp[10];             // �������� Proportional Const  ��0-3��Ϊ�ĸ���������ʽpid�Ĳ���
   volatile float   Ki[10];             // ���ֳ��� Integral Const			  ��4��5����x��y������λ��pid�Ĳ���
   volatile float   Kd[10];             // ΢�ֳ��� Derivative Const			��6����������yawλ��ʽpid�Ĳ���
   volatile float      Error1[10];         // Error[n-1]										��7��8��ͼƬ������ͷ����λ��ʽpid�Ĳ���
   volatile float      Error2[10];         // Error[n-2]
   volatile float      iError[10];         // Error[n]
	
	 volatile float integral[10];
}PID;    

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
	volatile int16 encoder[4];            //��������¼��������
	volatile int16 rc_encoder[4];
	volatile float speed[4];							//ʹ�ñ�������������ٶ�
	volatile float distance[4];           //��������¼�����
	volatile float distance_road;
	volatile int16 set_pwm[4];						//����ʽ�����pwm
}WHEEL;


typedef struct
{
	uint8 boma[2]; 
	uint8 key[4];
}GPIO;


typedef struct
{
	float gyro_x;
	float gyro_y;
	float gyro_z;
	
	float acc_x;
	float acc_y;
	float acc_z;
	
	float yaw;	

	float yawzero;
	float yawz;
	
}GYROSCOPE;

typedef struct
{
	uint8 label_flag;
	
	uint16 event;
	
	int16 label;
	
	uint8 x;
	uint8 y;
	uint8 x0;
	uint8 y0;
	uint8 x1;
	uint8 y1;
	
	uint16 c;
	
	uint8 cross_label[20];
	
	uint8 round_label[20];
	
	uint8 mess_label[20];

	uint8 num;
	
	uint8 Scattered_num;
}OBJ;

typedef struct
{
	uint16 pwm[4];
}SERVO;

typedef struct
{
	uint8 num[10];
	uint16 frame_pwm[10];
	uint16 frame_label[10];
	uint16 frame_label_nam[16];
	uint8 at_frame;
	int8 at_frame_num[2];	
	uint8 Scattered_num[3];
}FRAME;

extern CAR_SYSTEM car_system;
extern FLAG flag;
extern WHEEL wheel;
extern PID pid;
extern fuzzy_pid_st fuzzy_t;
extern GPIO gpio;
extern GYROSCOPE gyroscope963ra;

extern uint8 center_l,center_r;
extern float center_t;

extern uint8 flap[10];

extern OBJ obj;
extern PIC_FLAG pic_flag;

extern uint8 stime;
extern uint8 turn_num;
extern SERVO servo;
extern TIME time;

extern FRAME frame1;
extern uint8 new_omega;
extern uint16 label_last;
extern uint8 center_l,center_r;
extern float center_ct;
extern uint8 bin_image[120][188];//ͼ������
#endif
