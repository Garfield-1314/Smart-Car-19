#include "servo.h"

SERVO servo;
FRAME frame1;
//FRAME frame2;

void Frame1_init()
{
	frame1.frame_pwm[0]=820;
	frame1.frame_pwm[1]=654;
	frame1.frame_pwm[2]=484;
	frame1.frame_pwm[3]=326;
	frame1.frame_pwm[4]=986;
	frame1.frame_pwm[5]=1157;
	
	
	for(uint8 i=0;i<6;i++)
	{
		frame1.frame_label[i]=0;
	}
}

void Frame2_init()
{
//	frame2.frame_pwm[0]=826;
//	frame2.frame_pwm[1]=490;
//	frame2.frame_pwm[2]=1157;
//	
//	
//	for(uint8 i=0;i<3;i++)
//	{
//		frame2.frame_label[i]=0;
//	}
}

void frame_test()
{
//	servo.pwm[0]=830;
//	servo.pwm[1]=750;
//	servo.pwm[2]=850;
//	servo.pwm[3]=frame2.frame_pwm[2];	
}

void servo_init()
{
	pwm_init(PWM2_MODULE2_CHB_C11,50,0);
	pwm_init(PWM2_MODULE2_CHA_C10,50,0);
	pwm_init(PWM2_MODULE0_CHB_C7,50,0);
	pwm_init(PWM2_MODULE0_CHA_C6,50,0);
	
	Frame1_init();
	Frame2_init();
	
	servo.pwm[0]=820;
	servo.pwm[1]=750;
	servo.pwm[2]=850;
	servo.pwm[3]=826;
}

void servo_give(uint16 pwm1,uint16 pwm2,uint16 pwm3,uint16 pwm4)
{
	pwm_set_duty(PWM2_MODULE2_CHB_C11,pwm1);
	pwm_set_duty(PWM2_MODULE2_CHA_C10,pwm2);
	pwm_set_duty(PWM2_MODULE0_CHB_C7,pwm3);
	pwm_set_duty(PWM2_MODULE0_CHA_C6,pwm4);
}

void servo_a_keep()
{
	servo.pwm[0]=830;
	servo.pwm[1]=750;
	servo.pwm[2]=850;
//	servo.pwm[3]=servo.pwm[3]=frame1.frame_num[obj.num-1];
//	if(frame1.at_frame)
}

void servo_a_get()
{	
	servo.pwm[3]=frame1.frame_pwm[obj.num-1];	
	system_delay_ms(1000);
	if(pic_flag.Scattered_card_flag!=0)
	{
		servo.pwm[0]=520;servo.pwm[1]=250;servo.pwm[2]=1230;servo.pwm[3]=frame1.frame_pwm[obj.num-1];	
	}
	else 
	{
		servo.pwm[0]=526;servo.pwm[1]=250;servo.pwm[2]=1234;servo.pwm[3]=frame1.frame_pwm[obj.num-1];	
	}
//	system_delay_ms(1000);
	system_delay_ms(500);
	flag.citie=OK;	
//	system_delay_ms(1000);
	system_delay_ms(500);
	servo.pwm[0]=600;servo.pwm[1]=250;servo.pwm[2]=1250;servo.pwm[3]=frame1.frame_pwm[obj.num-1];		
	system_delay_ms(500);
	servo.pwm[0]=800;servo.pwm[1]=400;servo.pwm[2]=530;servo.pwm[3]=frame1.frame_pwm[obj.num-1];		
	system_delay_ms(800);
	servo.pwm[0]=800;servo.pwm[1]=680;servo.pwm[2]=530;servo.pwm[3]=frame1.frame_pwm[obj.num-1];	
	system_delay_ms(900);
	flag.citie=NO;
	system_delay_ms(500);
	servo_a_keep();
}

void servo_a_put()
{
	servo.pwm[3]=frame1.frame_pwm[frame1.at_frame];	
	system_delay_ms(1000);
	servo.pwm[0]=700;servo.pwm[1]=960;servo.pwm[2]=534;servo.pwm[3]=frame1.frame_pwm[frame1.at_frame];	
	system_delay_ms(500);
	flag.citie=OK;
//	system_delay_ms(1000);
	system_delay_ms(500);
	servo.pwm[0]=780;servo.pwm[1]=760;servo.pwm[2]=450;servo.pwm[3]=frame1.frame_pwm[frame1.at_frame];	
	system_delay_ms(500);
	servo.pwm[0]=600;servo.pwm[1]=450;servo.pwm[2]=1250;servo.pwm[3]=frame1.frame_pwm[frame1.at_frame];	
	system_delay_ms(1000);
	flag.citie=NO;	
	system_delay_ms(300);
	servo_a_keep();
}

