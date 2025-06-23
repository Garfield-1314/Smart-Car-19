#ifndef __SERVO_H
#define __SERVO_H

#include "user_include.h"

void 	servo_init(void);
void servo_give(uint16 pwm1,uint16 pwm2,uint16 pwm3,uint16 pwm4);
void servo_a_keep(void);
void servo_a_get(void);
void servo_a_put(void);
void Frame1_init(void);
void Frame2_init(void);

void frame_test(void);
#endif
