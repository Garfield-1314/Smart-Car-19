#ifndef _IMAGE_H
#define _IMAGE_H
#include "user.h"


//颜色定义  因为有先例，连颜色都改不来，我直接放这了
#define uesr_RED     0XF800    //红色
#define uesr_GREEN   0X07E0    //绿色
#define uesr_BLUE    0X001F    //蓝色


//宏定义
#define image_h	120//图像高度
#define image_w	188//图像宽度

#define white_pixel	255
#define black_pixel	0

#define bin_jump_num	1//跳过的点数
#define border_max	image_w-2 //边界最大值
#define border_min	1	//边界最小值	


#define L 2
#define W 3

extern void image_process(void); //直接在中断或循环里调用此程序就可以循环执行了

void judge_point_L_W(void);
void judge_round(void);
void go_straight(void);
void show_image(void);


#endif /*_IMAGE_H*/

