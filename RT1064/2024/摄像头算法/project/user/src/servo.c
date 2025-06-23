#include "servo.h"


void servo_init()
{
	pwm_init(PWM2_MODULE0_CHA_C6,50,0);
	pwm_init(PWM2_MODULE0_CHB_C7,50,0);
	pwm_init(PWM2_MODULE2_CHA_C10,50,0);
	pwm_init(PWM2_MODULE2_CHB_C11,50,0);
	
	pwm_set_duty(PWM2_MODULE0_CHA_C6,700);
	pwm_set_duty(PWM2_MODULE0_CHB_C7,650);
	pwm_set_duty(PWM2_MODULE2_CHA_C10,895);
	pwm_set_duty(PWM2_MODULE2_CHB_C11,760);
}