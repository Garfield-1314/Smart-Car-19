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


/*����ȫ�˶�ѧ������*/
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



/*����Ҫ�㡿
*������yawƫ��������ʱ�뷽��Ϊ��
*���ַ�������Ŀ����������ֵ��ͬ�����Ƿ��Ż�������ͬ
*����ȫ�򷽰�ʱ�������turn(uint8 i)����,����Ҫʵ����ת���ܿ��Ե���(������ʹ����ȫ�˶�ѧ����)
*��������ת���н��Ĳ���ʱ���Ƽ�ʹ��trun(uint8 i)�ӳ�ʶ����ϵ����
*����ȫ����������д�����Ҫ��F_attitude_solution()�����ú�ע��
*�Ƕȵ�λ��Ϊ�ȣ���̵�λΪcm*/