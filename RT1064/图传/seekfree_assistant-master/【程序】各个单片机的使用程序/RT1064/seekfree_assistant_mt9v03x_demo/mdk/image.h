#ifndef _IMAGE_H
#define _IMAGE_H
#include "zf_common_headfile.h"


//��ɫ����  ��Ϊ������������ɫ���Ĳ�������ֱ�ӷ�����
#define uesr_RED     0XF800    //��ɫ
#define uesr_GREEN   0X07E0    //��ɫ
#define uesr_BLUE    0X001F    //��ɫ




//�궨��
#define image_h	MT9V03X_H//ͼ��߶�
#define image_w	MT9V03X_W//ͼ����

#define white_pixel	255
#define black_pixel	0

#define USED_ROW   MT9V03X_H  //����͸��ͼ������
#define USED_COL   MT9V03X_W
#define RESULT_ROW MT9V03X_H-4//���ͼ����
#define RESULT_COL MT9V03X_W-4


#define image_h_P MT9V03X_H-4
#define image_w_P MT9V03X_W-4

#define bin_jump_num	1//�����ĵ���
#define border_max	image_w-2 //�߽����ֵ
#define border_min	1	//�߽���Сֵ	
//extern uint8 original_image[image_h][image_w];
//extern uint8 bin_image[image_h][image_w];//ͼ������








void image_process(void); //ֱ�����жϻ�ѭ������ô˳���Ϳ���ѭ��ִ����

void ImagePerspective_Init(uint8 image[USED_ROW][USED_COL]) ;

typedef struct
{
	uint16 dir_l[10]; 
	uint16 dir_r[10]; 
	uint16 point_l;
	uint16 point_r;
}CDIR;

extern uint8 ImageUsing[RESULT_ROW][RESULT_COL];
extern uint8 bin_image[image_h][image_w];
#endif /*_IMAGE_H*/

