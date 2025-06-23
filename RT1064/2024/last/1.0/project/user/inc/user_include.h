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
	
	float chassis_dx;                          //当前底盘所处x坐标
	float chassis_dy;                          //当前底盘所处y坐标
	float Omega;                               //当前底盘偏航角
	
	float set_Omega;                           //设定的偏航角	
	
	float Vtx;                                 //底盘x轴方向上的速度
	float Vty;                                 //底盘y轴方向上的速度
	
	
	float Vx;                                  //正运动学解出的x轴方向上的速度
	float Vy;                                  //正运动学解出的y轴方向上的速度
	
	float Vw[4];                               //逆运动学解出的四个轮子的转速
	
	float atx;                                 //用于传递目标x坐标用于位置pid
	float aty;                                 //用于传递目标y坐标用于位置pid
	

	
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
   volatile float   Kp[10];             // 比例常数 Proportional Const  【0-3】为四个轮子增量式pid的参数
   volatile float   Ki[10];             // 积分常数 Integral Const			  【4、5】是x，y方向上位置pid的参数
   volatile float   Kd[10];             // 微分常数 Derivative Const			【6】是陀螺仪yaw位置式pid的参数
   volatile float      Error1[10];         // Error[n-1]										【7、8】图片与摄像头中心位置式pid的参数
   volatile float      Error2[10];         // Error[n-2]
   volatile float      iError[10];         // Error[n]
	
	 volatile float integral[10];
}PID;    

typedef struct
{
    bool FUZZY_USED;   //是否使用模糊PID
 
    float max_e;    // e  \in [-max_e,max_e]
    float max_ec;   // ec \in [-max_ec,max_ec]
    float max_kp;   // kp \in kp0+[-max_kp,max_kp] kp0-max_kp>0
    float max_ki;
    float max_kd;
 
    uint8 rule_kp[7][7];  //模糊规则表
    uint8 rule_ki[7][7];   
    uint8 rule_kd[7][7];
		
		float d_kp[4],d_ki[4],d_kd[4];
}fuzzy_pid_st;

typedef struct
{
	volatile int16 encoder[4];            //编码器记录的脉冲数
	volatile int16 rc_encoder[4];
	volatile float speed[4];							//使用编码器测算出的速度
	volatile float distance[4];           //编码器记录的里程
	volatile float distance_road;
	volatile int16 set_pwm[4];						//增量式输出的pwm
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
extern uint8 bin_image[120][188];//图像数组
#endif
