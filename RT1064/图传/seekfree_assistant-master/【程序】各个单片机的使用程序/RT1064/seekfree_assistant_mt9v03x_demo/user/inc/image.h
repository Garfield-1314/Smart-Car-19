#ifndef _IMAGE_H
#define _IMAGE_H

#include "zf_common_headfile.h"
//颜色定义  因为有先例，连颜色都改不来，我直接放这了
#define uesr_RED     0XF800    //红色
#define uesr_GREEN   0X07E0    //绿色
#define uesr_BLUE    0X001F    //蓝色




//宏定义
#define image_h	MT9V03X_H//输入图像高度
#define image_w	MT9V03X_W//输入图像宽度

#define white_pixel	255
#define black_pixel	0
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#define USED_ROW  image_h  //逆透视输输入图像高度
#define USED_COL  image_w  //逆透视输输入图像宽度

#define image_h_P image_h-4//逆透视输出图像高度
#define image_w_P image_w-4//逆透视输出图像宽度


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
#define bin_jump_num	1//跳过的点数
#define border_max	image_w_P-2 //边界最大值
#define border_min	1	//边界最小值	


typedef struct
{
	uint16 dir_l[10]; 
	uint16 dir_r[10]; 
	uint16 point_l;
	uint16 point_r;
}CDIR;


void image_process(void); //直接在中断或循环里调用此程序就可以循环执行了


#endif /*_IMAGE_H*/

