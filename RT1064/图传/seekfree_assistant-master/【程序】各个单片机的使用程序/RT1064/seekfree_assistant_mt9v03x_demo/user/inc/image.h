#ifndef _IMAGE_H
#define _IMAGE_H

#include "zf_common_headfile.h"
//��ɫ����  ��Ϊ������������ɫ���Ĳ�������ֱ�ӷ�����
#define uesr_RED     0XF800    //��ɫ
#define uesr_GREEN   0X07E0    //��ɫ
#define uesr_BLUE    0X001F    //��ɫ




//�궨��
#define image_h	MT9V03X_H//����ͼ��߶�
#define image_w	MT9V03X_W//����ͼ����

#define white_pixel	255
#define black_pixel	0
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#define USED_ROW  image_h  //��͸��������ͼ��߶�
#define USED_COL  image_w  //��͸��������ͼ����

#define image_h_P image_h-4//��͸�����ͼ��߶�
#define image_w_P image_w-4//��͸�����ͼ����


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#define bin_jump_num	1//�����ĵ���
#define border_max	image_w_P-2 //�߽����ֵ
#define border_min	1	//�߽���Сֵ	


typedef struct
{
	uint16 dir_l[10]; 
	uint16 dir_r[10]; 
	uint16 point_l;
	uint16 point_r;
}CDIR;


void image_process(void); //ֱ�����жϻ�ѭ������ô˳���Ϳ���ѭ��ִ����


#endif /*_IMAGE_H*/

