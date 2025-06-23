#ifndef _IMAGE_H
#define _IMAGE_H
#include "user_include.h"

//��ɫ����  ��Ϊ������������ɫ���Ĳ�������ֱ�ӷ�����
#define uesr_RED     0XF800    //��ɫ
#define uesr_GREEN   0X07E0    //��ɫ
#define uesr_BLUE    0X001F    //��ɫ


//�궨��
#define image_h	120//ͼ��߶�
#define image_w	188//ͼ����

#define white_pixel	255
#define black_pixel	0

#define bin_jump_num	1//�����ĵ���
#define border_max	image_w-2 //�߽����ֵ
#define border_min	1	//�߽���Сֵ	


#define L 2
#define W 3

extern void image_process(void); //ֱ�����жϻ�ѭ������ô˳���Ϳ���ѭ��ִ����

void judge_point_L_W(void);
void judge_cross(void);
void judge_round(void);
uint8 judge_cross_round_road_L_R(void);
void judge_Scattered_card(void);
void judge_endline(void);
void judge_obstacle(void);
void thwartwise(uint8(*image)[image_w]);
void judge_ramp(void);

#endif /*_IMAGE_H*/

