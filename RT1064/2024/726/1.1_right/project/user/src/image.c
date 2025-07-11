
#include "image.h"
#include "user.h"


//-------------------------------------------------------------------------------------------------------------------
//  简介:逆透视

//------------------------------------------------------------------------------------------------------------------
//uint8 ImageUsing[RESULT_ROW][RESULT_COL];
////#define ImageUsed   *PerImg_ip//*PerImg_ip定义使用的图像，ImageUsed为用于巡线和识别的图像 
//void ImagePerspective_Init(uint8 image[USED_ROW][USED_COL]) 
//{
//    static uint8 BlackColor = 0;
//	
//		double change_un_Mat[3][3] ={{0.058456,-0.031578,1.966273},{-0.000924,0.001594,2.115923},{0.000004,-0.000470,0.082075}};
//    for (int i = 0; i < RESULT_COL ;i++) 
//		{
//        for (int j = 0; j < RESULT_ROW ;j++) 
//				{
//            int local_x = (int) ((change_un_Mat[0][0] * i+ change_un_Mat[0][1] * j + change_un_Mat[0][2])
//                    / (change_un_Mat[2][0] * i + change_un_Mat[2][1] * j+ change_un_Mat[2][2]));
//						
//            int local_y = (int) ((change_un_Mat[1][0] * i+ change_un_Mat[1][1] * j + change_un_Mat[1][2])
//                    /	(change_un_Mat[2][0] * i + change_un_Mat[2][1] * j+ change_un_Mat[2][2]));
//						
//            if (local_x>= 0&& local_y >= 0 && local_y < USED_ROW && local_x < USED_COL)
//						{
//                ImageUsing[j][i] = image[local_y][local_x];
//            }
//            else 
//						{
//                ImageUsing[j][i] = BlackColor;          //&PER_IMG[0][0];
//            }
//        }
//    }
////		tft180_displayimage03x(ImageUsing[0], 128, 96);
//}



//-------------------------------------------------------------------------------------------------------------------
//  简介:八邻域图像处理

//------------------------------------------------------------------------------------------------------------------
/*
函数名称：int my_abs(int value)
功能说明：求绝对值
参数说明：
函数返回：绝对值
修改时间：2022年9月8日
备    注：
example：  my_abs( x)；
 */
int my_abs(int value)
{
if(value>=0) return value;
else return -value;
}

int16 limit_a_b(int16 x, int a, int b)
{
    if(x<a) x = a;
    if(x>b) x = b;
    return x;
}

/*
函数名称：int16 limit(int16 x, int16 y)
功能说明：求x,y中的最小值
参数说明：
函数返回：返回两值中的最小值
修改时间：2022年9月8日
备    注：
example：  limit( x,  y)
 */
int16 limit1(int16 x, int16 y)
{
	if (x > y)             return y;
	else if (x < -y)       return -y;
	else                return x;
}


/*变量声明*/
uint8 original_image[image_h][image_w];
uint8 image_thereshold;//图像分割阈值
//------------------------------------------------------------------------------------------------------------------
//  @brief      获得一副灰度图像
//  @since      v1.0 
//------------------------------------------------------------------------------------------------------------------
void Get_image(uint8 tmImage[image_h][image_w])
{
#define use_num		1	//1就是不压缩，2就是压缩一倍	
	uint8 i = 0, j = 0, row = 0, line = 0;
    for (i = 0; i < image_h; i += use_num)          //
    {
        for (j = 0; j <image_w; j += use_num)     //
        {
            original_image[row][line] = tmImage[i][j];//这里的参数填写你的摄像头采集到的图像
			line++;
        }
        line = 0;
        row++;
    }
}
//------------------------------------------------------------------------------------------------------------------
//  @brief     动态阈值
//  @since      v1.0 
//------------------------------------------------------------------------------------------------------------------
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
{
#define GrayScale 256
    uint16 Image_Width  = col;
    uint16 Image_Height = row;
    int X; uint16 Y;
    uint8* data = image;
    int HistGram[GrayScale] = {0};
	
	uint32 Amount = 0;
    uint32 PixelBack = 0;
    uint32 PixelIntegralBack = 0;
    uint32 PixelIntegral = 0;
    int32 PixelIntegralFore = 0;
    int32 PixelFore = 0;
    double OmegaBack=0, OmegaFore=0, MicroBack=0, MicroFore=0, SigmaB=0, Sigma=0; // 类间方差;
    int16 MinValue=0, MaxValue=0;
    uint8 Threshold = 0;
	
	
    for (Y = 0; Y <Image_Height; Y++) //Y<Image_Height改为Y =Image_Height；以便进行 行二值化
    {
        //Y=Image_Height;
        for (X = 0; X < Image_Width; X++)
        {
        HistGram[(int)data[Y*Image_Width + X]]++; //统计每个灰度值的个数信息
        }
    }




    for (MinValue = 0; MinValue < 256 && HistGram[MinValue] == 0; MinValue++) ;        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistGram[MinValue] == 0; MaxValue--) ; //获取最大灰度的值

    if (MaxValue == MinValue)
    {
        return MaxValue;          // 图像中只有一个颜色
    }
    if (MinValue + 1 == MaxValue)
    {
        return MinValue;      // 图像中只有二个颜色
    }

    for (Y = MinValue; Y <= MaxValue; Y++)
    {
        Amount += HistGram[Y];        //  像素总数
    }

    PixelIntegral = 0;
    for (Y = MinValue; Y <= MaxValue; Y++)
    {
        PixelIntegral += HistGram[Y] * Y;//灰度值总数
    }
    SigmaB = -1;
    for (Y = MinValue; Y < MaxValue; Y++)
    {
          PixelBack = PixelBack + HistGram[Y];    //前景像素点数
          PixelFore = Amount - PixelBack;         //背景像素点数
          OmegaBack = (double)PixelBack / Amount;//前景像素百分比
          OmegaFore = (double)PixelFore / Amount;//背景像素百分比
          PixelIntegralBack += HistGram[Y] * Y;  //前景灰度值
          PixelIntegralFore = PixelIntegral - PixelIntegralBack;//背景灰度值
          MicroBack = (double)PixelIntegralBack / PixelBack;//前景灰度百分比
          MicroFore = (double)PixelIntegralFore / PixelFore;//背景灰度百分比
          Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//g
          if (Sigma > SigmaB)//遍历最大的类间方差g
          {
              SigmaB = Sigma;
              Threshold = (uint8)Y;
          }
    }
   return Threshold;
}
//------------------------------------------------------------------------------------------------------------------
//  @brief      图像二值化，这里用的是大津法二值化。
//  @since      v1.0 
//------------------------------------------------------------------------------------------------------------------
uint8 bin_image[image_h][image_w];//图像数组
void turn_to_bin(void)
{
  uint8 i,j;
 image_thereshold = otsuThreshold(original_image[0], image_w, image_h);
  for(i = 0;i<image_h;i++)
  {
      for(j = 0;j<image_w;j++)
      {
          if(original_image[i][j]>image_thereshold)bin_image[i][j] = white_pixel;
          else bin_image[i][j] = black_pixel;
      }
  }
}


/*
函数名称：void get_start_point(uint8 start_row)
功能说明：寻找两个边界的边界点作为八邻域循环的起始点
参数说明：输入任意行数
函数返回：无
修改时间：2022年9月8日
备    注：
example：  get_start_point(image_h-2)
 */
uint8 start_point_l[2] = { 0 };//左边起点的x，y值
uint8 start_point_r[2] = { 0 };//右边起点的x，y值
uint8 get_start_point(uint8 start_row)
{
	uint8 i = 0,l_found = 0,r_found = 0;
	//清零
	start_point_l[0] = 0;//x
	start_point_l[1] = 0;//y

	start_point_r[0] = 0;//x
	start_point_r[1] = 0;//y

		//从中间往左边，先找起点
	for (i = image_w / 2; i > border_min; i--)    
	{
		start_point_l[0] = i;//x
		start_point_l[1] = start_row;//y
		if (bin_image[start_row][i] == 255 && bin_image[start_row][i - 1] == 0)
		{
			//printf("找到左边起点image[%d][%d]\n", start_row,i);
			l_found = 1;
			break;
		}
	}

	for (i = image_w / 2; i < border_max; i++)
	{
		start_point_r[0] = i;//x
		start_point_r[1] = start_row;//y
		if (bin_image[start_row][i] == 255 && bin_image[start_row][i + 1] == 0)
		{
			//printf("找到右边起点image[%d][%d]\n",start_row, i);
			r_found = 1;
			break;
		}
	}

	if(l_found&&r_found)return 1;
	else {
		//printf("未找到起点\n");
		return 0;
	} 
}

/*
函数名称：void search_l_r(uint16 break_flag, uint8(*image)[image_w],uint16 *l_stastic, uint16 *r_stastic,
							uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y,uint8*hightest)

功能说明：八邻域正式开始找右边点的函数，输入参数有点多，调用的时候不要漏了，这个是左右线一次性找完。
参数说明：
break_flag_r			：最多需要循环的次数
(*image)[image_w]		：需要进行找点的图像数组，必须是二值图,填入数组名称即可
					   特别注意，不要拿宏定义名字作为输入参数，否则数据可能无法传递过来
*l_stastic				：统计左边数据，用来输入初始数组成员的序号和取出循环次数
*r_stastic				：统计右边数据，用来输入初始数组成员的序号和取出循环次数
l_start_x				：左边起点横坐标
l_start_y				：左边起点纵坐标
r_start_x				：右边起点横坐标
r_start_y				：右边起点纵坐标
hightest				：循环结束所得到的最高高度
函数返回：无
修改时间：2024年3月31日
备    注：
example：
	search_l_r((uint16)USE_num,image,&data_stastics_l, &data_stastics_r,start_point_l[0],
				start_point_l[1], start_point_r[0], start_point_r[1],&hightest);
 */
#define USE_num	image_h*3	//定义找点的数组成员个数按理说300个点能放下，但是有些特殊情况确实难顶，多定义了一点

 //存放点的x，y坐标
 uint16 points_l[(uint16)USE_num][2] = { {  0 } };//左线    points_l[(uint16)USE_num][0]为x坐标，points_l[(uint16)USE_num][1]为y坐标
uint16 points_r[(uint16)USE_num][2] = { {  0 } };//右线
uint16 dir_r[(uint16)USE_num] = { 0 };//用来存储右边生长方向
uint16 dir_l[(uint16)USE_num] = { 0 };//用来存储左边生长方向
uint16 data_stastics_l = 0;//统计左边找到点的个数
uint16 data_stastics_r = 0;//统计右边找到点的个数
uint8 hightest = 0;//最高点
void search_l_r(uint16 break_flag, uint8(*image)[image_w], uint16 *l_stastic, uint16 *r_stastic, uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y, uint8*hightest)
{

	uint8 i = 0, j = 0;
	//左边变量
	uint8 search_filds_l[8][2] = { {  0 } };
	uint8 index_l = 0;
	uint8 temp_l[8][2] = { {  0 } };
	uint8 center_point_l[2] = {  0 };
	uint16 l_data_statics;//统计左边
	//定义八个邻域
	static int8 seeds_l[8][2] = { {0,  1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,  0},{1, 1}, };
	//{-1,-1},{0,-1},{+1,-1},
	//{-1, 0},	     {+1, 0},
	//{-1,+1},{0,+1},{+1,+1},
	//这个是顺时针

	//右边变量
	uint8 search_filds_r[8][2] = { {  0 } };
	uint8 center_point_r[2] = { 0 };//中心坐标点
	uint8 index_r = 0;//索引下标
	uint8 temp_r[8][2] = { {  0 } };
	uint16 r_data_statics;//统计右边
	//定义八个邻域
	static int8 seeds_r[8][2] = { {0,  1},{1,1},{1,0}, {1,-1},{0,-1},{-1,-1}, {-1,  0},{-1, 1}, };
	//{-1,-1},{0,-1},{+1,-1},
	//{-1, 0},	     {+1, 0},
	//{-1,+1},{0,+1},{+1,+1},
	//这个是逆时针

	l_data_statics = *l_stastic;//统计找到了多少个点，方便后续把点全部画出来
	r_data_statics = *r_stastic;//统计找到了多少个点，方便后续把点全部画出来

	//第一次更新坐标点  将找到的起点值传进来
	center_point_l[0] = l_start_x;//x
	center_point_l[1] = l_start_y;//y
	center_point_r[0] = r_start_x;//x
	center_point_r[1] = r_start_y;//y

		//开启邻域循环
	while (break_flag--)
	{

		//左边
		for (i = 0; i < 8; i++)//传递8F坐标
		{
			search_filds_l[i][0] = center_point_l[0] + seeds_l[i][0];//x
			search_filds_l[i][1] = center_point_l[1] + seeds_l[i][1];//y
		}
		//中心坐标点填充到已经找到的点内
		points_l[l_data_statics][0] = center_point_l[0];//x
		points_l[l_data_statics][1] = center_point_l[1];//y
		l_data_statics++;//索引加一

		//右边
		for (i = 0; i < 8; i++)//传递8F坐标
		{
			search_filds_r[i][0] = center_point_r[0] + seeds_r[i][0];//x
			search_filds_r[i][1] = center_point_r[1] + seeds_r[i][1];//y
		}
		//中心坐标点填充到已经找到的点内
		points_r[r_data_statics][0] = center_point_r[0];//x
		points_r[r_data_statics][1] = center_point_r[1];//y

		index_l = 0;//先清零，后使用
		for (i = 0; i < 8; i++)
		{
			temp_l[i][0] = 0;//先清零，后使用
			temp_l[i][1] = 0;//先清零，后使用
		}

		//左边判断
		for (i = 0; i < 8; i++)
		{
			if (image[search_filds_l[i][1]][search_filds_l[i][0]] == 0 && image[search_filds_l[(i + 1) & 7][1]][search_filds_l[(i + 1) & 7][0]] == 255)
			{
				temp_l[index_l][0] = search_filds_l[(i)][0];
				temp_l[index_l][1] = search_filds_l[(i)][1];
				index_l++;
				dir_l[l_data_statics - 1] = (i);//记录生长方向
			}

			if (index_l)
			{
				//更新坐标点
				center_point_l[0] = temp_l[0][0];//x
				center_point_l[1] = temp_l[0][1];//y
				for (j = 0; j < index_l; j++)
				{
					if (center_point_l[1] > temp_l[j][1])
					{
						center_point_l[0] = temp_l[j][0];//x
						center_point_l[1] = temp_l[j][1];//y
					}
				}
			}

		}
		if ((points_r[r_data_statics][0]== points_r[r_data_statics-1][0]&& points_r[r_data_statics][0] == points_r[r_data_statics - 2][0]
			&& points_r[r_data_statics][1] == points_r[r_data_statics - 1][1] && points_r[r_data_statics][1] == points_r[r_data_statics - 2][1])
			||(points_l[l_data_statics-1][0] == points_l[l_data_statics - 2][0] && points_l[l_data_statics-1][0] == points_l[l_data_statics - 3][0]
				&& points_l[l_data_statics-1][1] == points_l[l_data_statics - 2][1] && points_l[l_data_statics-1][1] == points_l[l_data_statics - 3][1]))
		{
			//printf("三次进入同一个点，退出\n");
			break;
		}
		if (my_abs(points_r[r_data_statics][0] - points_l[l_data_statics - 1][0]) < 2
			&& my_abs(points_r[r_data_statics][1] - points_l[l_data_statics - 1][1] < 2)
			)
		{
			//printf("\n左右相遇退出\n");	
			*hightest = (points_r[r_data_statics][1] + points_l[l_data_statics - 1][1]) >> 1;//取出最高点
			//printf("\n在y=%d处退出\n",*hightest);
			break;
		}
		if ((points_r[r_data_statics][1] < points_l[l_data_statics - 1][1]))
		{
//			printf("\n如果左边比右边高了，左边等待右边\n");	
			continue;//如果左边比右边高了，左边等待右边
		}
		if (dir_l[l_data_statics - 1] == 7
			&& (points_r[r_data_statics][1] > points_l[l_data_statics - 1][1]))//左边比右边高且已经向下生长了
		{
			//printf("\n左边开始向下了，等待右边，等待中... \n");
			center_point_l[0] = points_l[l_data_statics - 1][0];//x
			center_point_l[1] = points_l[l_data_statics - 1][1];//y
			l_data_statics--;
		}
		r_data_statics++;//索引加一

		index_r = 0;//先清零，后使用
		for (i = 0; i < 8; i++)
		{
			temp_r[i][0] = 0;//先清零，后使用
			temp_r[i][1] = 0;//先清零，后使用
		}

		//右边判断
		for (i = 0; i < 8; i++)
		{
			if (image[search_filds_r[i][1]][search_filds_r[i][0]] == 0
				&& image[search_filds_r[(i + 1) & 7][1]][search_filds_r[(i + 1) & 7][0]] == 255)
			{
				temp_r[index_r][0] = search_filds_r[(i)][0];
				temp_r[index_r][1] = search_filds_r[(i)][1];
				index_r++;//索引加一
				dir_r[r_data_statics - 1] = (i);//记录生长方向
				//printf("dir[%d]:%d\n", r_data_statics - 1, dir_r[r_data_statics - 1]);
			}
			if (index_r)
			{

				//更新坐标点
				center_point_r[0] = temp_r[0][0];//x
				center_point_r[1] = temp_r[0][1];//y
				for (j = 0; j < index_r; j++)
				{
					if (center_point_r[1] > temp_r[j][1])
					{
						center_point_r[0] = temp_r[j][0];//x
						center_point_r[1] = temp_r[j][1];//y
					}
				}

			}
		}


	}


	//取出循环次数
	*l_stastic = l_data_statics;
	*r_stastic = r_data_statics;

}
/*
函数名称：void get_left(uint16 total_L)
功能说明：从八邻域边界里提取需要的边线
参数说明：
total_L	：找到的点的总数
函数返回：无
修改时间：2022年9月25日
备    注：
example： get_left(data_stastics_l );
 */
uint8 l_border[image_h];//左线数组
uint8 r_border[image_h];//右线数组
uint8 center_line[image_h];//中线数组
void get_left(uint16 total_L)
{
	uint8 i = 0;
	uint16 j = 0;
	uint8 h = 0;
	//初始化
	for (i = 0;i<image_h;i++)
	{
		l_border[i] = border_min;//右边线初始化放到最右边，左边线放到最左边，这样八邻域闭合区域外的中线就会在中间，不会干扰得到的数据
	}
	h = image_h - 2;
	//左边
	for (j = 0; j < total_L; j++)
	{
		//printf("%d\n", j);
		if (points_l[j][1] == h)
		{
			l_border[h] = points_l[j][0]+1;
		}
		else continue; //每行只取一个点，没到下一行就不记录
		h--;
		if (h == 0) 
		{
			break;//到最后一行退出
		}
	}
}
/*
函数名称：void get_right(uint16 total_R)
功能说明：从八邻域边界里提取需要的边线
参数说明：
total_R  ：找到的点的总数
函数返回：无
修改时间：2022年9月25日
备    注：
example：get_right(data_stastics_r);
 */
void get_right(uint16 total_R)
{
	uint8 i = 0;
	uint16 j = 0;
	uint8 h = 0;
	for (i = 0; i < image_h; i++)
	{
		r_border[i] = border_max;//右边线初始化放到最右边，左边线放到最左边，这样八邻域闭合区域外的中线就会在中间，不会干扰得到的数据
	}
	h = image_h - 2;
	//右边
	for (j = 0; j < total_R; j++)
	{
		if (points_r[j][1] == h)
		{
			r_border[h] = points_r[j][0] - 1;
		}
		else continue;//每行只取一个点，没到下一行就不记录
		h--;
		if (h == 0)break;//到最后一行退出
	}
}

//定义膨胀和腐蚀的阈值区间
#define threshold_max	255*5//此参数可根据自己的需求调节
#define threshold_min	255*2//此参数可根据自己的需求调节
void image_filter(uint8(*bin_image)[image_w])//形态学滤波，简单来说就是膨胀和腐蚀的思想
{
	uint16 i, j;
	uint32 num = 0;


	for (i = 1; i < image_h - 1; i++)
	{
		for (j = 1; j < (image_w - 1); j++)
		{
			//统计八个方向的像素值
			num =
				bin_image[i - 1][j - 1] + bin_image[i - 1][j] + bin_image[i - 1][j + 1]
				+ bin_image[i][j - 1] + bin_image[i][j + 1]
				+ bin_image[i + 1][j - 1] + bin_image[i + 1][j] + bin_image[i + 1][j + 1];

			if (num >= threshold_max && bin_image[i][j] == 0)
			{

				bin_image[i][j] = 255;//白  可以搞成宏定义，方便更改

			}
			if (num <= threshold_min && bin_image[i][j] == 255)
			{

				bin_image[i][j] = 0;//黑

			}

		}
	}

}

/*
函数名称：void image_draw_rectan(uint8(*image)[image_w])
功能说明：给图像画一个黑框
参数说明：uint8(*image)[image_w]	图像首地址
函数返回：无
修改时间：2022年9月8日
备    注：
example： image_draw_rectan(bin_image);
 */
void image_draw_rectan(uint8(*image)[image_w])
{

	uint8 i = 0;
	for (i = 0; i < image_h; i++)
	{
		image[i][0] = 0;
		image[i][1] = 0;
		image[i][image_w - 1] = 0;
		image[i][image_w - 2] = 0;

	}
	for (i = 0; i < image_w; i++)
	{
		image[0][i] = 0;
		image[1][i] = 0;
		//image[image_h-1][i] = 0;

	}
}

/*
函数名称：void image_process(void)
功能说明：最终处理函数
参数说明：无
函数返回：无
修改时间：2022年9月8日
备    注：
example： image_process();
 */
uint8 center[image_h];
void image_process(void)
{
	uint16 i;
	uint8 hightest = 0;//定义一个最高行，tip：这里的最高指的是y值的最小
	
	Get_image(mt9v03x_image);
	
	turn_to_bin();	
	
/*提取赛道边界*/
	image_filter(bin_image);//滤波
	image_draw_rectan(bin_image);//预处理
	
	data_stastics_l = 0;//清零
	data_stastics_r = 0;//清零
	
if (get_start_point(image_h - 2))//找到起点了，再执行八领域，没找到就一直找
{

	search_l_r((uint16)USE_num, bin_image, &data_stastics_l, &data_stastics_r, start_point_l[0], start_point_l[1], start_point_r[0], start_point_r[1], &hightest);//八邻域爬边线

	
/* 从爬取的边界线内提取边线 ， 这个才是最终有用的边线*/
	get_left(data_stastics_l);
	get_right(data_stastics_r);

/* 处理函数放这里，不要放到if外面去了，不要放到if外面去了，不要放到if外面去了，重要的事说三遍*/
	
//中线or中线与边线的插值做pid的输入量
//dir生长方向用来判断元素
//使用补线,十字路口补边线再求中线
	
	
	judge_point_L_W();
	if(pic_flag.cross_all_flag==0
		&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0
		&&pic_flag.Scattered_card_flag==0
		&&pic_flag.endline_flag==0
		&&flap[0]==0
		&&pic_flag.obstacle_left_flag==0
		&&pic_flag.obstacle_right_flag==0
		&&pic_flag.ramp_flag==0
		&&time.sys_time>5)
	{
		judge_Scattered_card();
		judge_ramp();
		judge_obstacle();
		judge_endline();
		judge_round();
		judge_cross();	
	}
	center_t=0;
	float center_l=0.0,center_r=0.0,center_ct=0.0;
	for (uint8 i = border_min+50; i < image_h-5; i++)
	{
		center_line[i] = (l_border[i] + r_border[i]) >> 1;//求中线
		center_ct+=(float)center_line[i]/(float)(image_h);
		center_l+=(float)l_border[i]/(float)(image_h);
		center_r+=(float)r_border[i]/(float)(image_h);
	}
//	time.cross_card_time=10;
//	pic_flag.round_left_flag=2;
	if(flag.cross_round_card_over!=0)
	{
			if(pic_flag.round_left_flag!=0)
			{		
					center_t=center_r-32.0;
				if(car_system.chassis_dx<=car_system.atx-70)
					center_t=center_l+32.0;
			}
			else if(pic_flag.round_right_flag!=0)
			{
					center_t=center_l+32.0;
				if(car_system.chassis_dx<=car_system.atx-70)
					center_t=center_r-32.0;
			}
			else
			{
				center_t=center_ct;
			}
	}
	else if(pic_flag.obstacle_left_flag!=0||pic_flag.obstacle_right_flag!=0)
	{
		if(pic_flag.obstacle_left_flag!=0)
		{
			center_t=center_r-10;
		}
		else if(pic_flag.obstacle_right_flag!=0)
		{
			center_t=center_l+10;
		}
	}
	else
	{
		center_t=center_ct;
	}
//	printf("centct:%f\tcent:%f\tcenl:%f\tcenr:%f\r\n",center_ct,center_t,center_l,center_r);
}
	tft180_show_gray_image(0, 0,bin_image[0], image_w, image_h, image_w/2, image_h/2, 1);
}
/*
这里是起点（0.0）***************——>*************x值最大
************************************************************
************************************************************
************************************************************
************************************************************
******************假如这是一副图像*************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
y值最大*******************************************(188.120)
*/


CDIR cdir;
PIC_FLAG pic_flag;
float center_t=0.0;
uint8 ldn=0,rdn=0;
void judge_point_L_W()
{
//	uint8 ld[200],rd[200];
	ldn=0,rdn=0;
	uint8 n=0;
	for(n=border_min+5;n<image_h-5;n++)
	{
//		printf("n:%d\tL:%d\tR:%d\r\n",n,l_border[n],r_border[n]);//点的横坐标
		if(abs(l_border[n+1]-l_border[n])>40&&l_border[n+1]<94&&l_border[n]<94)
		{
//			ld[ldn]=n;			
			ldn++;
		}
		if(abs(r_border[n+1]-r_border[n])>40&&r_border[n+1]>96&&r_border[n]>96)
		{
//			rd[rdn]=n;	
			rdn++;		
		}	
	}
	
	n=0;
	for(n=border_min+5;n<image_h-5;n++)
	{
		if(ldn!=0)
		{
			if(l_border[n]<border_min+10)
				cdir.point_l[n]=L;
			else
				cdir.point_l[n]=W;
		}
		else
			cdir.point_l[n]=W;
		
		if(rdn!=0)
		{
			if(r_border[n]>border_max-10)
				cdir.point_r[n]=L;
			else
				cdir.point_r[n]=W;
		}
		else
			cdir.point_r[n]=W;
	}
	

//	n=0;
//	for(n=border_min+5;n<image_h-5;n++)
//	{
//		printf("n:%d\tcL:%d\tcR:%d\r\n",n,cdir.point_l[n],cdir.point_r[n]);//点是否为丢线的点
//	}
}

void judge_cross()
{
	uint8 n=0;
	cdir.L_L_NUM=0;
	cdir.R_L_NUM=0;
	uint8 DL[10],DR[10];
	pic_flag.cross_left_POI_flag=0;
	pic_flag.cross_right_POI_flag=0;
	pic_flag.round_left_DIR_flag=0;
	pic_flag.round_right_DIR_flag=0;
	pic_flag.cross_left_DIRN_flag=0;
	pic_flag.cross_right_DIRN_flag=0;
	pic_flag.cross_POIL_NUM_flag=0;
	pic_flag.cross_POIR_NUM_flag=0;
	pic_flag.cross_all_flag=0;
	uint8 l=0,r=0;
	ldn=0,rdn=0;
	for(n=border_min+5;n<image_h-5;n++)
	{
		if(l_border[n]==2)
		{
			l++;
		}
		if(r_border[n]==185)
		{
			r++;
		}
		
		if(abs(l_border[n+1]-l_border[n])>5&&l_border[n+1]<94&&l_border[n]<94)
		{
			ldn++;
		}
		if(abs(r_border[n+1]-r_border[n])>5&&r_border[n+1]>96&&r_border[n]>96)
		{
			rdn++;		
		}	
		
//		printf("n：%d\tDil：%d\tDir：%d\r\n",n,dir_l[n],dir_r[n]);
		
		switch(dir_l[n])
		{
			case 0:DL[0]++;break;
			case 1:DL[1]++;break;
			case 2:DL[2]++;break;
			case 3:DL[3]++;break;
			case 4:DL[4]++;break;
			case 5:DL[5]++;break;
			case 6:DL[6]++;break;
			case 7:DL[7]++;break;
		}
		switch(dir_r[n])
		{
			case 0:DR[0]++;break;
			case 1:DR[1]++;break;
			case 2:DR[2]++;break;
			case 3:DR[3]++;break;
			case 4:DR[4]++;break;
			case 5:DR[5]++;break;
			case 6:DR[6]++;break;
			case 7:DR[7]++;break;
		}
		
		
		if(dir_l[n]==4&&(dir_l[n+1]==5||dir_l[n+1]==6))
		{
			pic_flag.cross_left_DIR_flag++;
		}
		if(dir_r[n]==4&&(dir_r[n+1]==5||dir_r[n+1]==6))
		{
			pic_flag.cross_right_DIR_flag++;
		}
	}
	
	for(n=border_min+5;n<image_h-5;n++)
	{
		if(ldn!=0)
		{
			if(l_border[n]<border_min+10)
				cdir.point_l[n]=L;
			else
				cdir.point_l[n]=W;
		}
		else
			cdir.point_l[n]=W;
		
		if(rdn!=0)
		{
			if(r_border[n]>border_max-10)
				cdir.point_r[n]=L;
			else
				cdir.point_r[n]=W;
		}
		else
			cdir.point_r[n]=W;
		
		if(cdir.point_l[n]==L)
		{
			cdir.L_L_NUM++;
		}
		if(cdir.point_r[n]==L)
		{
			cdir.R_L_NUM++;
		}
	}
	
	
	if(DL[6]>=10)
	{
		pic_flag.cross_left_DIRN_flag++;
	}
	if(DR[6]>=10)
	{
		pic_flag.cross_right_DIRN_flag++;
	}

	if(cdir.L_L_NUM>20&&ldn>=1)
	{
		pic_flag.cross_POIL_NUM_flag++;
	}
	if(cdir.R_L_NUM>20&&rdn>=1)
	{	
		pic_flag.cross_POIR_NUM_flag++;
	}
	
	int x1=abs(l_border[image_h-5]-l_border[border_min+50]);
	int y1=abs((image_h-5)-(border_min+50));
	
	int x2=abs(r_border[image_h-5]-r_border[border_min+50]);
	int y2=abs((image_h-5)-(border_min+50));
	
	double angleL=atan((double)x1/(double)y1);
	double angleR=atan((double)x2/(double)y2);
	
//	printf("angleL:%lf\tangleR:%lf\r\n",angleL,angleR);
	
	if(angleL!=0&&angleR!=0)
	{
		pic_flag.cross_angle_L_flag++;
		pic_flag.cross_angle_R_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);
	}
	
	if(pic_flag.cross_left_DIR_flag!=0&&pic_flag.cross_right_DIR_flag!=0
		&&pic_flag.cross_left_DIRN_flag!=0&&pic_flag.cross_right_DIRN_flag!=0
		&&(pic_flag.cross_POIL_NUM_flag!=0&&pic_flag.cross_POIR_NUM_flag!=0)
		&&(l>20&&r>20)
		&&flap[0]==0)
	{
		pic_flag.cirque_num++;
		flap[0]=1;
		pic_flag.cross_all_flag++;
		pic_flag.endline_flag=0;
		pic_flag.round_left_flag=0;
		pic_flag.round_right_flag=0;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
//	printf("%d,%d\r\n",pic_flag.cross_left_POI_flag,pic_flag.cross_right_POI_flag);
//	printf("%d,%d\r\n",pic_flag.cross_POIL_NUM_flag,pic_flag.cross_POIR_NUM_flag);
}



void judge_round()
{
	uint8 n=0;
	cdir.L_L_NUM=0;
	cdir.R_L_NUM=0;
	uint8 DL[10],DR[10];
	pic_flag.round_left_DIR_flag=0;
	pic_flag.round_right_DIR_flag=0;
	pic_flag.round_left_DIRN_flag=0;
	pic_flag.round_right_DIRN_flag=0;
	pic_flag.round_POIL_NUM_flag=0;
	pic_flag.round_POIR_NUM_flag=0;
	pic_flag.round_angle_L_flag=0;
	pic_flag.round_angle_R_flag=0;
//	pic_flag.round_left_flag_num=0;
//	pic_flag.round_right_flag_num=0;
	pic_flag.round_left_flag=0;
	pic_flag.round_right_flag=0;
	
		
	for(n=border_min+5;n<image_h-5;n++)
	{
		if(cdir.point_l[n]==L)
		{
			cdir.L_L_NUM++;
		}
		if(cdir.point_r[n]==L)
		{
			cdir.R_L_NUM++;
		}
//		
//	printf("n：%d\tDil：%d\tDir：%d\r\n",n,dir_l[n],dir_r[n]);
//		
		
		switch(dir_l[n])
		{
			case 0:DL[0]++;break;
			case 1:DL[1]++;break;
			case 2:DL[2]++;break;
			case 3:DL[3]++;break;
			case 4:DL[4]++;break;
			case 5:DL[5]++;break;
			case 6:DL[6]++;break;
			case 7:DL[7]++;break;
		}
		switch(dir_r[n])
		{
			case 0:DR[0]++;break;
			case 1:DR[1]++;break;
			case 2:DR[2]++;break;
			case 3:DR[3]++;break;
			case 4:DR[4]++;break;
			case 5:DR[5]++;break;
			case 6:DR[6]++;break;
			case 7:DR[7]++;break;
		}
		
		if(dir_l[n]==2&&(dir_l[n+1]==3||dir_l[n+1]==4))
		{
			pic_flag.round_left_DIR_flag++;
//			gpio_set_level(F_beer,GPIO_HIGH);	
		}
		if(dir_r[n]==2&&(dir_r[n+1]==3||dir_r[n+1]==4))
		{
			pic_flag.round_right_DIR_flag++;
		}
	}
	
	if(DL[2]>7&&DL[1]>3)
	{
		pic_flag.round_left_DIRN_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	if(DR[2]>7&&DR[1]>3)
	{
		pic_flag.round_right_DIRN_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	
	
	if(cdir.L_L_NUM>25&&cdir.R_L_NUM<10&&ldn==1&&rdn==0)
	{
		pic_flag.round_POIL_NUM_flag++;
	}
	if(cdir.R_L_NUM>25&&cdir.L_L_NUM<10&&rdn==1&&ldn==0)
	{	
		pic_flag.round_POIR_NUM_flag++;
	}
	
	
	if(pic_flag.round_left_DIR_flag!=0&&pic_flag.round_left_DIRN_flag!=0&&flap[0]==0)
	{
//		flap[0]=1;
		pic_flag.round_left_flag_num+=4;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}	
	else
	{
		if(pic_flag.round_left_flag_num>0)
			pic_flag.round_left_flag_num--;
//		if(pic_flag.round_right_flag_num>0)
//			pic_flag.round_right_flag_num--;
	}
	
	if(pic_flag.round_right_DIR_flag!=0&&pic_flag.round_right_DIRN_flag!=0&&flap[0]==0)
	{
//		flap[0]=1;
		pic_flag.round_right_flag_num+=4;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	else
	{
//		if(pic_flag.round_left_flag_num>0)
//			pic_flag.round_left_flag_num--;
		if(pic_flag.round_right_flag_num>0)
			pic_flag.round_right_flag_num--;
	}

	int x1=abs(l_border[image_h-5]-l_border[border_min+5]);
	int y1=abs((image_h-5)-(border_min+50));
	
	int x2=abs(r_border[image_h-5]-r_border[border_min+5]);
	int y2=abs((image_h-5)-(border_min+50));
	
	double angleL=atan((double)x1/(double)y1);
	double angleR=atan((double)x2/(double)y2);
	
	

	if(angleL==0&&angleR!=0)
	{
		pic_flag.round_angle_L_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	if(angleR==0&&angleL!=0)
	{
		pic_flag.round_angle_R_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	
	if(pic_flag.round_angle_L_flag!=0&&pic_flag.round_POIL_NUM_flag!=0&&pic_flag.round_left_flag_num>=4)
	{
		pic_flag.round_left_flag_num=0;
		pic_flag.round_left_flag++;
		pic_flag.endline_flag=0;
		pic_flag.cross_all_flag=0;
		pic_flag.round_right_flag=0;
		flap[0]=1;
		pic_flag.cirque_num++;
		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	else if(pic_flag.round_angle_R_flag!=0&&pic_flag.round_POIR_NUM_flag!=0&&pic_flag.round_right_flag_num>=4)
	{
		pic_flag.round_right_flag_num=0;
		pic_flag.round_right_flag++;
		pic_flag.endline_flag=0;
		pic_flag.cross_all_flag=0;
		pic_flag.round_left_flag=0;
		flap[0]=1;
		pic_flag.cirque_num++;
		gpio_set_level(F_beer,GPIO_HIGH);	
	}
}

uint8 judge_cross_round_road_L_R(void)
{
	uint8 L_L=0,R_L=0;
	uint8 n=0;
	uint8 revalue;
	
	n=0;
	for(n=border_min+5;n<image_h-5;n++)
	{
		if(l_border[n]<border_min+10)
			L_L++;
		if(r_border[n]>border_max-10)
			R_L++;
	}
		
	if(pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0&&pic_flag.cross_all_flag!=0)
	{
		if(L_L>R_L)
			revalue = L_C;
		else
			revalue = R_C;
	}
	else if(pic_flag.round_left_flag!=0&&pic_flag.round_right_flag==0&&pic_flag.cross_all_flag==0)
	{
		revalue = L_C;
	}
	else if(pic_flag.round_left_flag==0&&pic_flag.round_right_flag!=0&&pic_flag.cross_all_flag==0)
	{
		revalue = R_C;
	}
	
	//	printf("revalue:%d\r\n",revalue);
	
	pic_flag.R_OR_L=revalue;
	return revalue;
}


void judge_Scattered_card()
{
	pic_flag.Scattered_card_flag=0;
	if(obj.x!=0&&obj.y!=0&&flap[0]==0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0&&pic_flag.cross_all_flag==0)	
	{
//		gpio_set_level(F_beer,GPIO_HIGH);	
		if(obj.y>=20&&obj.y<=130&&obj.c>=40&&obj.c<=170)
			time.Scattered_time++;
		if(obj.y!=0&&flap[0]==0&&time.Scattered_time>30&&pic_flag.endline_flag==0)
		{
//			gpio_set_level(F_beer,GPIO_HIGH);	
			pic_flag.Scattered_card_flag++;
			pic_flag.endline_flag=0;
			pic_flag.cross_all_flag=0;
			pic_flag.round_left_flag=0;
			pic_flag.round_right_flag=0;
			flap[0]=1;
			tft180_show_string(0, 120, "Scattered");
			
			time.Scattered_time=0;
			if(obj.x<=70&&new_omega==0)
			{
				car_system.set_Omega=88;
				flag.L_R_omega=L_O;
				new_omega++;
			}
			else if(obj.x>=90&&new_omega==0)
			{
				car_system.set_Omega=-88;
				flag.L_R_omega=R_O;
				new_omega++;
			}
		}
	}
	else
	{
		if(flap[0]==0)
			pic_flag.Scattered_card_flag=0;
		time.Scattered_time=0;
	}	
}

void judge_endline()
{
	pic_flag.endline_flag=0;
	uint16 end_line=0;
	for (uint8 i = border_min+10; i < border_min+50; i++)
	{
		for(uint8 n=l_border[i];n<r_border[i];n++)
		{
			if(bin_image[i][n]==black_pixel&&bin_image[i][n+1]==white_pixel)
			{
				end_line++;
			}
		}
	}
	if(end_line>50&&pic_flag.cirque_num>=2)
	{
		flag.keep_omega=OK;
		car_system.set_Omega=0;
		gyroscope963ra.yaw=0;
		pic_flag.endline_flag++;
		pic_flag.cross_all_flag=0;
		pic_flag.round_left_flag=0;
		pic_flag.round_right_flag=0;
		flap[0]=1;
		car_system.Vtx=0;
		car_system.Vty=0;
//		gpio_set_level(F_beer,GPIO_HIGH);
	}
//	printf("end_line:%d\r\n",end_line);
}

void judge_obstacle()
{
	uint8 DL[10],DR[10];
	uint16 white_num=0,black_num=0;
	uint16 wide=0;
	pic_flag.obstacle_left_flag=0;
	pic_flag.obstacle_right_flag=0;
	pic_flag.obstacle_POIL_flag=0;
	pic_flag.obstacle_POIR_flag=0;
	pic_flag.obstacle_POI_NUM_flag=0;
	pic_flag.obstacle_color_flag=0;
	pic_flag.obstacle_angle_flag=0;
	uint8 n=0;
	for(n=border_min+20-1;n<70;n++)
	{
		wide+=(r_border[n]-l_border[n]);
		for(uint8 i=l_border[n];i<r_border[n];i++)
		{
			if(bin_image[n][i]==white_pixel)
			{
				white_num++;
			}
			else 
				black_num++;
		}
		
//		printf("n:%d\tL:%d\tR:%d\r\n",n,l_border[n],r_border[n]);//点的横坐标
		if(abs(l_border[n+1]-l_border[n])>8&&l_border[n+1]<94&&l_border[n]<94)
		{
			pic_flag.obstacle_POIL_flag++;
//			gpio_set_level(F_beer,GPIO_HIGH);
		}
		if(abs(r_border[n+1]-r_border[n])>8&&r_border[n+1]>96&&r_border[n]>96)
		{
			pic_flag.obstacle_POIR_flag++;
//			gpio_set_level(F_beer,GPIO_HIGH);
		}	
	}
	
	wide=wide/50;
//	printf("wide:%d\r\n",wide);
	
	if(white_num<4000&&white_num>3000)
	{
		pic_flag.obstacle_color_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);
	}
//	printf("white_num:%d\rblack_num:%d\r\n",white_num,black_num);
	
	int x1=abs(l_border[image_h-5]-l_border[border_min+50]);
	int y1=abs((image_h-5)-(border_min+50));
	
	int x2=abs(r_border[image_h-5]-r_border[border_min+50]);
	int y2=abs((image_h-5)-(border_min+50));
	
	double angleL=atan((double)x1/(double)y1);
	double angleR=atan((double)x2/(double)y2);
	
	if(angleL!=0&&angleR!=0)
	{
		pic_flag.obstacle_angle_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);
	}
//	printf("L:%lf\tR:%lf\r\n",angleL,angleR);
	
	if((cdir.L_L_NUM<10&&ldn==0)&&(cdir.R_L_NUM<10&&rdn==0))
	{
		pic_flag.obstacle_POI_NUM_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);
	}
	
	if(pic_flag.obstacle_POIL_flag>=1&&pic_flag.obstacle_POI_NUM_flag!=0&&pic_flag.obstacle_angle_flag!=0&&pic_flag.obstacle_color_flag!=0&&wide<80)
	{
//		pic_flag.obstacle_left_flag++;
		gpio_set_level(F_beer,GPIO_HIGH);
	}
	else if(pic_flag.obstacle_POIR_flag>=1&&pic_flag.obstacle_POI_NUM_flag!=0&&pic_flag.obstacle_angle_flag!=0&&pic_flag.obstacle_color_flag!=0&&wide<80)
	{
//		pic_flag.obstacle_right_flag++;
		gpio_set_level(F_beer,GPIO_HIGH);
	}
}

uint8 center_l=0,center_r=0;
void thwartwise(uint8(*image)[image_w])
{
	center_l=0;
	center_r=0;
	for(uint8 i=80;i<image_h;i++)
	{
		if(image[i][20]==white_pixel)
		{
			center_l++;
		}
		if(image[i][image_w-20]==white_pixel)
		{
			center_r++;
		}
	}
//	printf("center_l:%d\tcenter_r:%d\r\n",center_l,center_r);
}

void judge_ramp()
{
	uint8 n=0;
	uint8 l=0,r=0;
	int16 wides=0;
	float wide=0;
	pic_flag.ramp_wide_flag=0;
	pic_flag.ramp_POI_NUM_flag=0;
	pic_flag.ramp_flag=0;
	for(n=border_min+20-1;n<50;n++)
	{
		if(l_border[n]>=30&&r_border[n]<=158)
			wides+=(r_border[n]-l_border[n]);
	}
	n=0;
	for(n=border_min+5;n<50;n++)
	{
		if(l_border[n]<=5)
		{
			l++;
		}
		if(r_border[n]>=183)
		{
			r++;
		}
	}
	
//	printf("l:%d\tr:%d\r\n",l,r);
	if(l==0&&r==0&&ldn==0&&rdn==0)
	{
		pic_flag.ramp_POI_NUM_flag++;
	}
	wide=wides/30;
//	printf("wide:%f\r\n",wide);
	if(wide>85&&wide<120)
	{
		pic_flag.ramp_wide_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);
	}
	
	if(center_t>=47.5-3&&center_t<=47.5+3)
	{
		if(pic_flag.ramp_POI_NUM_flag!=0&&pic_flag.ramp_wide_flag!=0)
		{
			gyroscope963ra.yaw=0;
			flap[0]=1;
			gpio_set_level(F_beer,GPIO_HIGH);		
//			pic_flag.ramp_flag++;
		}
	}
	
}
