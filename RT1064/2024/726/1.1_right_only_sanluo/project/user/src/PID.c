#include "PID.h"
 
PID pid;
/********************************************************
��λ��ʽpid������ʼ����
********************************************************/
void dis_pid_init()
{
	pid.Kp[4]=3.0;  pid.Ki[4]=0;  pid.Kd[4]=0.0001;//x����
	pid.Kp[5]=3.0;  pid.Ki[5]=0;  pid.Kd[5]=0.0001;//y����

	pid.Kp[6]=1.3;  pid.Ki[6]=0;  pid.Kd[6]=0;//������
	
	pid.Kp[7]=0.35;  pid.Ki[5]=0;  pid.Kd[5]=0;
	pid.Kp[8]=0.35;  pid.Ki[5]=0;  pid.Kd[5]=0;
	
	pid.Kp[9]=1.75;  pid.Ki[9]=0;  pid.Kd[9]=0;//����
}

/********************************************************
������ʽpid������ʼ����
********************************************************/
void inc_pid_init()
{
//	pid.Kp[0]=25;  pid.Ki[0]=4.631;  pid.Kd[0]=0;
//	pid.Kp[1]=20;  pid.Ki[1]=5.0;  pid.Kd[0]=0;
//	pid.Kp[2]=25;  pid.Ki[2]=5.76;  pid.Kd[0]=0;
//	pid.Kp[3]=28;  pid.Ki[3]=4.731;  pid.Kd[0]=0;
	
	pid.Kp[0]=30;  pid.Ki[0]=4.631;  pid.Kd[0]=0;
	pid.Kp[1]=25;  pid.Ki[1]=5.3;  pid.Kd[0]=0;
	pid.Kp[2]=30;  pid.Ki[2]=5.76;  pid.Kd[0]=0;
	pid.Kp[3]=33;  pid.Ki[3]=4.731;  pid.Kd[0]=0;
}
 

void pid_init()
{
	inc_pid_init();
	dis_pid_init();
}

/********************************************************
������ʽpid��
��CurrentPointΪʵ��ֵ��
��SetPointΪĿ��ֵ��
********************************************************/
int16	output[8] = {0,0,0,0,0,0,0,0};
int16 IncPIDCalc(uint8 wheel,int16 CurrentPoint,int16 SetPoint) 
{
  
  pid.iError[wheel]=SetPoint-CurrentPoint;                                     // ���㵱ǰ���
  output[wheel]+=pid.Kp[wheel] * (pid.iError[wheel]-pid.Error1[wheel])                  // P
         +pid.Ki[wheel] * pid.iError[wheel]                                   // I
         +pid.Kd[wheel] * (pid.iError[wheel]-2*pid.Error1[wheel]+pid.Error2[wheel]);  // D
             
  pid.Error2[wheel]=pid.Error1[wheel];                          // �洢�������´μ���
  pid.Error1[wheel]=pid.iError[wheel];										
		
  return(output[wheel]);                                    // ��������ֵ
}

/********************************************************
��λ��ʽpid��
********************************************************/

int16 PID_dis(uint8 wheel,int16 CurrentPoint,int16 SetPoint)
{
	
	pid.iError[wheel]=CurrentPoint-SetPoint;
	

	pid.integral[wheel] += pid.iError[wheel];


	output[wheel] = pid.Kp[wheel] * pid.iError[wheel] + pid.Ki[wheel] * pid.integral[wheel] + pid.Kd[wheel] * (pid.iError[wheel] - pid.Error1[wheel]);


	pid.Error1[wheel] = pid.iError[wheel];
	
	return output[wheel];
}


void speed_control()
{
/********************************************************
��������ת�ٶ��޷���
********************************************************/	
/*Fuzzy	PID*/
	PID_control(0);
	PID_control(1);
	PID_control(2);
	PID_control(3);
/***********/
	if(car_system.Vw[0]<=-100)
			car_system.Vw[0]=-100;
	else if(car_system.Vw[0]>=100)
			car_system.Vw[0]=100;
	
	if(car_system.Vw[1]<=-100)
			car_system.Vw[1]=-100;
	else if(car_system.Vw[1]>=100)
			car_system.Vw[1]=100;

	if(car_system.Vw[2]<=-100)
			car_system.Vw[2]=-100;
	else if(car_system.Vw[2]>=100)
			car_system.Vw[2]=100;

	if(car_system.Vw[3]<=-100)
			car_system.Vw[3]=-100;
	else if(car_system.Vw[3]>=100)
			car_system.Vw[3]=100;
	
/********************************************************
������pid�����
********************************************************/
	
	for(uint8 i=0;i<4;i++)
	{
		wheel.set_pwm[i]=IncPIDCalc(i,(int)wheel.speed[i],car_system.Vw[i]);
	}
	
/********************************************************
������ת�жϡ�
********************************************************/
	if(wheel.set_pwm[0]<0)
		gpio_set_level(D15,GPIO_LOW);
	else
		gpio_set_level(D15,GPIO_HIGH);	
	
	if(wheel.set_pwm[1]<0)
		gpio_set_level(D14,GPIO_LOW);
	else
		gpio_set_level(D14,GPIO_HIGH);
	
	if(wheel.set_pwm[2]<0)
		gpio_set_level(D1,GPIO_HIGH);
	else
		gpio_set_level(D1,GPIO_LOW);

	if(wheel.set_pwm[3]<0)
		gpio_set_level(D0,GPIO_HIGH);
	else
		gpio_set_level(D0,GPIO_LOW);
/********************************************************
��������º��pwm��
********************************************************/	
	
	pwm_set_duty(PWM1_MODULE0_CHB_D13,abs(wheel.set_pwm[0]));
	pwm_set_duty(PWM1_MODULE0_CHA_D12,abs(wheel.set_pwm[1]));
	pwm_set_duty(PWM2_MODULE3_CHB_D3,abs(wheel.set_pwm[2]));
	pwm_set_duty(PWM2_MODULE3_CHA_D2,abs(wheel.set_pwm[3]));
	
}

void motor_text()
{
	gpio_set_level(D15,GPIO_HIGH);
	gpio_set_level(D14,GPIO_HIGH);
	gpio_set_level(D1,GPIO_LOW);
	gpio_set_level(D0,GPIO_LOW);
	
	pwm_set_duty(PWM1_MODULE0_CHB_D13,5000);
	pwm_set_duty(PWM1_MODULE0_CHA_D12,5000);
	pwm_set_duty(PWM2_MODULE3_CHB_D3,5000);
	pwm_set_duty(PWM2_MODULE3_CHA_D2,5000);
}

