#ifndef __CAR_ATTITUDE_H
#define __CAR_ATTITUDE_H

#include "user.h"

void F_attitude_solution(void);
void T_attitude_solution(void);
void Omega_attitude_solution(void);
void car_move_dot(void);
void turn(uint8 i);
#endif


/*
			Y
			*
			*
			*
			*
-X**********X
			*
			*
			*
			*
			-Y
*/


/*【完全运动学方案】*/
/*
			X
			*
			*
			*
			*
Y**********-Y
			*
			*
			*
			*
			-X
*/



/*【重要点】
*陀螺仪yaw偏航角需逆时针方向为正
*两种方案所给目标点的坐标数值相同，但是符号会有所不同
*采用全向方案时无需调用turn(uint8 i)函数,如需要实现旋转功能可以调用(但必须使用完全运动学方案)
*采用先旋转后行进的策略时，推荐使用trun(uint8 i)加常识坐标系方案
*具体全向和先旋后行代码需要在F_attitude_solution()中启用和注释
*角度单位均为度，里程单位为cm*/