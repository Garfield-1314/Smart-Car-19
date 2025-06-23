#ifndef __PID_H
#define __PID_H

#include "user.h"

void inc_pid_init(void);
void dis_pid_init(void);
int16 IncPIDCalc(uint8 wheel,int16 CurrentPoint,int16 SetPoint);
int16 PID_dis(uint8 wheel,int16 CurrentPoint,int16 SetPoint);
void speed_control(void);/*【最内环】*/
void motor_text(void);

void race_speed_solution(void);/*【赛道行驶PID】*/

#endif