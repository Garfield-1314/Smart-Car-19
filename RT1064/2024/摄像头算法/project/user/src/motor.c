#include "motor.h"

WHEEL wheel;

#define line_num 1024   /*【编码器线数】*/


struct RC_Para Encoder1_Para = {0, 0, 0.25}; // 低通滤波算子
struct RC_Para Encoder2_Para = {0, 0, 0.25};
struct RC_Para Encoder3_Para = {0, 0, 0.25};
struct RC_Para Encoder4_Para = {0, 0, 0.25};

RC_Filter_pt RC_Encoder1 = &Encoder1_Para;
RC_Filter_pt RC_Encoder2 = &Encoder2_Para;
RC_Filter_pt RC_Encoder3 = &Encoder3_Para;
RC_Filter_pt RC_Encoder4 = &Encoder4_Para;

void encoder_init(void)/*【编码器初始化函数】*/
{
	encoder_quad_init(QTIMER3_ENCODER2,QTIMER3_ENCODER2_CH1_B18,QTIMER3_ENCODER2_CH2_B19);
	encoder_quad_init(QTIMER2_ENCODER1,QTIMER2_ENCODER1_CH1_C3,QTIMER2_ENCODER1_CH2_C25);
	encoder_quad_init(QTIMER1_ENCODER1,QTIMER1_ENCODER1_CH1_C0,QTIMER1_ENCODER1_CH2_C1);
	encoder_quad_init(QTIMER1_ENCODER2,QTIMER1_ENCODER2_CH1_C2,QTIMER1_ENCODER2_CH2_C24);
}

extern float xx,yy;
void get_encoder(void)
{
	/*【读取编码器脉冲】*/
	wheel.encoder[0]=encoder_get_count(QTIMER3_ENCODER2);encoder_clear_count(QTIMER3_ENCODER2); 
	wheel.encoder[1]=-encoder_get_count(QTIMER2_ENCODER1);encoder_clear_count(QTIMER2_ENCODER1); 
	wheel.encoder[2]=encoder_get_count(QTIMER1_ENCODER1);encoder_clear_count(QTIMER1_ENCODER1); 
	wheel.encoder[3]=-encoder_get_count(QTIMER1_ENCODER2);encoder_clear_count(QTIMER1_ENCODER2); 	

	/*【使用RC滤波】*/
	wheel.rc_encoder[0]=(int16)RCFilter(wheel.encoder[0], RC_Encoder1);
	wheel.rc_encoder[1]=(int16)RCFilter(wheel.encoder[1], RC_Encoder2);
	wheel.rc_encoder[2]=(int16)RCFilter(wheel.encoder[2], RC_Encoder3);
	wheel.rc_encoder[3]=(int16)RCFilter(wheel.encoder[3], RC_Encoder4);
	
	/*【不使用RC滤波】*/
//	wheel.rc_encoder[0]=wheel.encoder[0];
//	wheel.rc_encoder[1]=wheel.encoder[1];
//	wheel.rc_encoder[2]=wheel.encoder[2];
//	wheel.rc_encoder[3]=wheel.encoder[3];
	
	/*【测速】*/
	for(uint8 i=0;i<4;i++)
	{
		wheel.speed[i]=(((float)wheel.rc_encoder[i]/line_num)*100*3/7)*PI*6.3;/*【3/7为齿轮比，6.3为车轮直径】*/
//		if(flag[3]!=0)
//			wheel.distance_road+=wheel.speed[i]/4/100;
	}
	
	/*【记录里程】*/
	if(!flag1.stop_encoder||flag[1]==1||flag[1]==4)
	{
		for(uint8 i=0;i<4;i++)
		{
				wheel.distance[i] = wheel.distance[i]+wheel.speed[i]/100;/*【除以100化为x厘米每秒】*/
		}
	}
}

/*【电机初始化】*/
void motor_init(void)
{
	encoder_init();
	
	gpio_init(D15,GPO,GPIO_LOW,GPO_PUSH_PULL);
	gpio_init(D14,GPO,GPIO_LOW,GPO_PUSH_PULL);
	gpio_init(D1,GPO,GPIO_HIGH,GPO_PUSH_PULL);
	gpio_init(D0,GPO,GPIO_HIGH,GPO_PUSH_PULL);
	
	pwm_init(PWM1_MODULE0_CHB_D13,10000,0);
	pwm_init(PWM1_MODULE0_CHA_D12,10000,0);
	pwm_init(PWM2_MODULE3_CHB_D3,10000,0);
	pwm_init(PWM2_MODULE3_CHA_D2,10000,0);
	
	
}



