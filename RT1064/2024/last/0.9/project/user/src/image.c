
#include "image.h"
#include "user.h"


//-------------------------------------------------------------------------------------------------------------------
//  ���:��͸��

//------------------------------------------------------------------------------------------------------------------
//uint8 ImageUsing[RESULT_ROW][RESULT_COL];
////#define ImageUsed   *PerImg_ip//*PerImg_ip����ʹ�õ�ͼ��ImageUsedΪ����Ѳ�ߺ�ʶ���ͼ�� 
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
//  ���:������ͼ����

//------------------------------------------------------------------------------------------------------------------
/*
�������ƣ�int my_abs(int value)
����˵���������ֵ
����˵����
�������أ�����ֵ
�޸�ʱ�䣺2022��9��8��
��    ע��
example��  my_abs( x)��
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
�������ƣ�int16 limit(int16 x, int16 y)
����˵������x,y�е���Сֵ
����˵����
�������أ�������ֵ�е���Сֵ
�޸�ʱ�䣺2022��9��8��
��    ע��
example��  limit( x,  y)
 */
int16 limit1(int16 x, int16 y)
{
	if (x > y)             return y;
	else if (x < -y)       return -y;
	else                return x;
}


/*��������*/
uint8 original_image[image_h][image_w];
uint8 image_thereshold;//ͼ��ָ���ֵ
//------------------------------------------------------------------------------------------------------------------
//  @brief      ���һ���Ҷ�ͼ��
//  @since      v1.0 
//------------------------------------------------------------------------------------------------------------------
void Get_image(uint8 tmImage[image_h][image_w])
{
#define use_num		1	//1���ǲ�ѹ����2����ѹ��һ��	
	uint8 i = 0, j = 0, row = 0, line = 0;
    for (i = 0; i < image_h; i += use_num)          //
    {
        for (j = 0; j <image_w; j += use_num)     //
        {
            original_image[row][line] = tmImage[i][j];//����Ĳ�����д�������ͷ�ɼ�����ͼ��
			line++;
        }
        line = 0;
        row++;
    }
}
//------------------------------------------------------------------------------------------------------------------
//  @brief     ��̬��ֵ
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
    double OmegaBack=0, OmegaFore=0, MicroBack=0, MicroFore=0, SigmaB=0, Sigma=0; // ��䷽��;
    int16 MinValue=0, MaxValue=0;
    uint8 Threshold = 0;
	
	
    for (Y = 0; Y <Image_Height; Y++) //Y<Image_Height��ΪY =Image_Height���Ա���� �ж�ֵ��
    {
        //Y=Image_Height;
        for (X = 0; X < Image_Width; X++)
        {
        HistGram[(int)data[Y*Image_Width + X]]++; //ͳ��ÿ���Ҷ�ֵ�ĸ�����Ϣ
        }
    }




    for (MinValue = 0; MinValue < 256 && HistGram[MinValue] == 0; MinValue++) ;        //��ȡ��С�Ҷȵ�ֵ
    for (MaxValue = 255; MaxValue > MinValue && HistGram[MinValue] == 0; MaxValue--) ; //��ȡ���Ҷȵ�ֵ

    if (MaxValue == MinValue)
    {
        return MaxValue;          // ͼ����ֻ��һ����ɫ
    }
    if (MinValue + 1 == MaxValue)
    {
        return MinValue;      // ͼ����ֻ�ж�����ɫ
    }

    for (Y = MinValue; Y <= MaxValue; Y++)
    {
        Amount += HistGram[Y];        //  ��������
    }

    PixelIntegral = 0;
    for (Y = MinValue; Y <= MaxValue; Y++)
    {
        PixelIntegral += HistGram[Y] * Y;//�Ҷ�ֵ����
    }
    SigmaB = -1;
    for (Y = MinValue; Y < MaxValue; Y++)
    {
          PixelBack = PixelBack + HistGram[Y];    //ǰ�����ص���
          PixelFore = Amount - PixelBack;         //�������ص���
          OmegaBack = (double)PixelBack / Amount;//ǰ�����ذٷֱ�
          OmegaFore = (double)PixelFore / Amount;//�������ذٷֱ�
          PixelIntegralBack += HistGram[Y] * Y;  //ǰ���Ҷ�ֵ
          PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
          MicroBack = (double)PixelIntegralBack / PixelBack;//ǰ���ҶȰٷֱ�
          MicroFore = (double)PixelIntegralFore / PixelFore;//�����ҶȰٷֱ�
          Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//g
          if (Sigma > SigmaB)//����������䷽��g
          {
              SigmaB = Sigma;
              Threshold = (uint8)Y;
          }
    }
   return Threshold;
}
//------------------------------------------------------------------------------------------------------------------
//  @brief      ͼ���ֵ���������õ��Ǵ�򷨶�ֵ����
//  @since      v1.0 
//------------------------------------------------------------------------------------------------------------------
uint8 bin_image[image_h][image_w];//ͼ������
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
�������ƣ�void get_start_point(uint8 start_row)
����˵����Ѱ�������߽�ı߽����Ϊ������ѭ������ʼ��
����˵����������������
�������أ���
�޸�ʱ�䣺2022��9��8��
��    ע��
example��  get_start_point(image_h-2)
 */
uint8 start_point_l[2] = { 0 };//�������x��yֵ
uint8 start_point_r[2] = { 0 };//�ұ�����x��yֵ
uint8 get_start_point(uint8 start_row)
{
	uint8 i = 0,l_found = 0,r_found = 0;
	//����
	start_point_l[0] = 0;//x
	start_point_l[1] = 0;//y

	start_point_r[0] = 0;//x
	start_point_r[1] = 0;//y

		//���м�����ߣ��������
	for (i = image_w / 2; i > border_min; i--)    
	{
		start_point_l[0] = i;//x
		start_point_l[1] = start_row;//y
		if (bin_image[start_row][i] == 255 && bin_image[start_row][i - 1] == 0)
		{
			//printf("�ҵ�������image[%d][%d]\n", start_row,i);
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
			//printf("�ҵ��ұ����image[%d][%d]\n",start_row, i);
			r_found = 1;
			break;
		}
	}

	if(l_found&&r_found)return 1;
	else {
		//printf("δ�ҵ����\n");
		return 0;
	} 
}

/*
�������ƣ�void search_l_r(uint16 break_flag, uint8(*image)[image_w],uint16 *l_stastic, uint16 *r_stastic,
							uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y,uint8*hightest)

����˵������������ʽ��ʼ���ұߵ�ĺ�������������е�࣬���õ�ʱ��Ҫ©�ˣ������������һ�������ꡣ
����˵����
break_flag_r			�������Ҫѭ���Ĵ���
(*image)[image_w]		����Ҫ�����ҵ��ͼ�����飬�����Ƕ�ֵͼ,�����������Ƽ���
					   �ر�ע�⣬��Ҫ�ú궨��������Ϊ����������������ݿ����޷����ݹ���
*l_stastic				��ͳ��������ݣ����������ʼ�����Ա����ź�ȡ��ѭ������
*r_stastic				��ͳ���ұ����ݣ����������ʼ�����Ա����ź�ȡ��ѭ������
l_start_x				�������������
l_start_y				��������������
r_start_x				���ұ���������
r_start_y				���ұ����������
hightest				��ѭ���������õ�����߸߶�
�������أ���
�޸�ʱ�䣺2024��3��31��
��    ע��
example��
	search_l_r((uint16)USE_num,image,&data_stastics_l, &data_stastics_r,start_point_l[0],
				start_point_l[1], start_point_r[0], start_point_r[1],&hightest);
 */
#define USE_num	image_h*3	//�����ҵ�������Ա��������˵300�����ܷ��£�������Щ�������ȷʵ�Ѷ����ඨ����һ��

 //��ŵ��x��y����
 uint16 points_l[(uint16)USE_num][2] = { {  0 } };//����    points_l[(uint16)USE_num][0]Ϊx���꣬points_l[(uint16)USE_num][1]Ϊy����
uint16 points_r[(uint16)USE_num][2] = { {  0 } };//����
uint16 dir_r[(uint16)USE_num] = { 0 };//�����洢�ұ���������
uint16 dir_l[(uint16)USE_num] = { 0 };//�����洢�����������
uint16 data_stastics_l = 0;//ͳ������ҵ���ĸ���
uint16 data_stastics_r = 0;//ͳ���ұ��ҵ���ĸ���
uint8 hightest = 0;//��ߵ�
void search_l_r(uint16 break_flag, uint8(*image)[image_w], uint16 *l_stastic, uint16 *r_stastic, uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y, uint8*hightest)
{

	uint8 i = 0, j = 0;
	//��߱���
	uint8 search_filds_l[8][2] = { {  0 } };
	uint8 index_l = 0;
	uint8 temp_l[8][2] = { {  0 } };
	uint8 center_point_l[2] = {  0 };
	uint16 l_data_statics;//ͳ�����
	//����˸�����
	static int8 seeds_l[8][2] = { {0,  1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,  0},{1, 1}, };
	//{-1,-1},{0,-1},{+1,-1},
	//{-1, 0},	     {+1, 0},
	//{-1,+1},{0,+1},{+1,+1},
	//�����˳ʱ��

	//�ұ߱���
	uint8 search_filds_r[8][2] = { {  0 } };
	uint8 center_point_r[2] = { 0 };//���������
	uint8 index_r = 0;//�����±�
	uint8 temp_r[8][2] = { {  0 } };
	uint16 r_data_statics;//ͳ���ұ�
	//����˸�����
	static int8 seeds_r[8][2] = { {0,  1},{1,1},{1,0}, {1,-1},{0,-1},{-1,-1}, {-1,  0},{-1, 1}, };
	//{-1,-1},{0,-1},{+1,-1},
	//{-1, 0},	     {+1, 0},
	//{-1,+1},{0,+1},{+1,+1},
	//�������ʱ��

	l_data_statics = *l_stastic;//ͳ���ҵ��˶��ٸ��㣬��������ѵ�ȫ��������
	r_data_statics = *r_stastic;//ͳ���ҵ��˶��ٸ��㣬��������ѵ�ȫ��������

	//��һ�θ��������  ���ҵ������ֵ������
	center_point_l[0] = l_start_x;//x
	center_point_l[1] = l_start_y;//y
	center_point_r[0] = r_start_x;//x
	center_point_r[1] = r_start_y;//y

		//��������ѭ��
	while (break_flag--)
	{

		//���
		for (i = 0; i < 8; i++)//����8F����
		{
			search_filds_l[i][0] = center_point_l[0] + seeds_l[i][0];//x
			search_filds_l[i][1] = center_point_l[1] + seeds_l[i][1];//y
		}
		//�����������䵽�Ѿ��ҵ��ĵ���
		points_l[l_data_statics][0] = center_point_l[0];//x
		points_l[l_data_statics][1] = center_point_l[1];//y
		l_data_statics++;//������һ

		//�ұ�
		for (i = 0; i < 8; i++)//����8F����
		{
			search_filds_r[i][0] = center_point_r[0] + seeds_r[i][0];//x
			search_filds_r[i][1] = center_point_r[1] + seeds_r[i][1];//y
		}
		//�����������䵽�Ѿ��ҵ��ĵ���
		points_r[r_data_statics][0] = center_point_r[0];//x
		points_r[r_data_statics][1] = center_point_r[1];//y

		index_l = 0;//�����㣬��ʹ��
		for (i = 0; i < 8; i++)
		{
			temp_l[i][0] = 0;//�����㣬��ʹ��
			temp_l[i][1] = 0;//�����㣬��ʹ��
		}

		//����ж�
		for (i = 0; i < 8; i++)
		{
			if (image[search_filds_l[i][1]][search_filds_l[i][0]] == 0 && image[search_filds_l[(i + 1) & 7][1]][search_filds_l[(i + 1) & 7][0]] == 255)
			{
				temp_l[index_l][0] = search_filds_l[(i)][0];
				temp_l[index_l][1] = search_filds_l[(i)][1];
				index_l++;
				dir_l[l_data_statics - 1] = (i);//��¼��������
			}

			if (index_l)
			{
				//���������
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
			//printf("���ν���ͬһ���㣬�˳�\n");
			break;
		}
		if (my_abs(points_r[r_data_statics][0] - points_l[l_data_statics - 1][0]) < 2
			&& my_abs(points_r[r_data_statics][1] - points_l[l_data_statics - 1][1] < 2)
			)
		{
			//printf("\n���������˳�\n");	
			*hightest = (points_r[r_data_statics][1] + points_l[l_data_statics - 1][1]) >> 1;//ȡ����ߵ�
			//printf("\n��y=%d���˳�\n",*hightest);
			break;
		}
		if ((points_r[r_data_statics][1] < points_l[l_data_statics - 1][1]))
		{
//			printf("\n�����߱��ұ߸��ˣ���ߵȴ��ұ�\n");	
			continue;//�����߱��ұ߸��ˣ���ߵȴ��ұ�
		}
		if (dir_l[l_data_statics - 1] == 7
			&& (points_r[r_data_statics][1] > points_l[l_data_statics - 1][1]))//��߱��ұ߸����Ѿ�����������
		{
			//printf("\n��߿�ʼ�����ˣ��ȴ��ұߣ��ȴ���... \n");
			center_point_l[0] = points_l[l_data_statics - 1][0];//x
			center_point_l[1] = points_l[l_data_statics - 1][1];//y
			l_data_statics--;
		}
		r_data_statics++;//������һ

		index_r = 0;//�����㣬��ʹ��
		for (i = 0; i < 8; i++)
		{
			temp_r[i][0] = 0;//�����㣬��ʹ��
			temp_r[i][1] = 0;//�����㣬��ʹ��
		}

		//�ұ��ж�
		for (i = 0; i < 8; i++)
		{
			if (image[search_filds_r[i][1]][search_filds_r[i][0]] == 0
				&& image[search_filds_r[(i + 1) & 7][1]][search_filds_r[(i + 1) & 7][0]] == 255)
			{
				temp_r[index_r][0] = search_filds_r[(i)][0];
				temp_r[index_r][1] = search_filds_r[(i)][1];
				index_r++;//������һ
				dir_r[r_data_statics - 1] = (i);//��¼��������
				//printf("dir[%d]:%d\n", r_data_statics - 1, dir_r[r_data_statics - 1]);
			}
			if (index_r)
			{

				//���������
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


	//ȡ��ѭ������
	*l_stastic = l_data_statics;
	*r_stastic = r_data_statics;

}
/*
�������ƣ�void get_left(uint16 total_L)
����˵�����Ӱ�����߽�����ȡ��Ҫ�ı���
����˵����
total_L	���ҵ��ĵ������
�������أ���
�޸�ʱ�䣺2022��9��25��
��    ע��
example�� get_left(data_stastics_l );
 */
uint8 l_border[image_h];//��������
uint8 r_border[image_h];//��������
uint8 center_line[image_h];//��������
void get_left(uint16 total_L)
{
	uint8 i = 0;
	uint16 j = 0;
	uint8 h = 0;
	//��ʼ��
	for (i = 0;i<image_h;i++)
	{
		l_border[i] = border_min;//�ұ��߳�ʼ���ŵ����ұߣ�����߷ŵ�����ߣ�����������պ�����������߾ͻ����м䣬������ŵõ�������
	}
	h = image_h - 2;
	//���
	for (j = 0; j < total_L; j++)
	{
		//printf("%d\n", j);
		if (points_l[j][1] == h)
		{
			l_border[h] = points_l[j][0]+1;
		}
		else continue; //ÿ��ֻȡһ���㣬û����һ�оͲ���¼
		h--;
		if (h == 0) 
		{
			break;//�����һ���˳�
		}
	}
}
/*
�������ƣ�void get_right(uint16 total_R)
����˵�����Ӱ�����߽�����ȡ��Ҫ�ı���
����˵����
total_R  ���ҵ��ĵ������
�������أ���
�޸�ʱ�䣺2022��9��25��
��    ע��
example��get_right(data_stastics_r);
 */
void get_right(uint16 total_R)
{
	uint8 i = 0;
	uint16 j = 0;
	uint8 h = 0;
	for (i = 0; i < image_h; i++)
	{
		r_border[i] = border_max;//�ұ��߳�ʼ���ŵ����ұߣ�����߷ŵ�����ߣ�����������պ�����������߾ͻ����м䣬������ŵõ�������
	}
	h = image_h - 2;
	//�ұ�
	for (j = 0; j < total_R; j++)
	{
		if (points_r[j][1] == h)
		{
			r_border[h] = points_r[j][0] - 1;
		}
		else continue;//ÿ��ֻȡһ���㣬û����һ�оͲ���¼
		h--;
		if (h == 0)break;//�����һ���˳�
	}
}

//�������ͺ͸�ʴ����ֵ����
#define threshold_max	255*5//�˲����ɸ����Լ����������
#define threshold_min	255*2//�˲����ɸ����Լ����������
void image_filter(uint8(*bin_image)[image_w])//��̬ѧ�˲�������˵�������ͺ͸�ʴ��˼��
{
	uint16 i, j;
	uint32 num = 0;


	for (i = 1; i < image_h - 1; i++)
	{
		for (j = 1; j < (image_w - 1); j++)
		{
			//ͳ�ư˸����������ֵ
			num =
				bin_image[i - 1][j - 1] + bin_image[i - 1][j] + bin_image[i - 1][j + 1]
				+ bin_image[i][j - 1] + bin_image[i][j + 1]
				+ bin_image[i + 1][j - 1] + bin_image[i + 1][j] + bin_image[i + 1][j + 1];

			if (num >= threshold_max && bin_image[i][j] == 0)
			{

				bin_image[i][j] = 255;//��  ���Ը�ɺ궨�壬�������

			}
			if (num <= threshold_min && bin_image[i][j] == 255)
			{

				bin_image[i][j] = 0;//��

			}

		}
	}

}

/*
�������ƣ�void image_draw_rectan(uint8(*image)[image_w])
����˵������ͼ��һ���ڿ�
����˵����uint8(*image)[image_w]	ͼ���׵�ַ
�������أ���
�޸�ʱ�䣺2022��9��8��
��    ע��
example�� image_draw_rectan(bin_image);
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
�������ƣ�void image_process(void)
����˵�������մ�����
����˵������
�������أ���
�޸�ʱ�䣺2022��9��8��
��    ע��
example�� image_process();
 */
uint8 center[image_h];
void image_process(void)
{
	uint16 i;
	uint8 hightest = 0;//����һ������У�tip����������ָ����yֵ����С
	
	Get_image(mt9v03x_image);
	
	turn_to_bin();	
	
/*��ȡ�����߽�*/
	image_filter(bin_image);//�˲�
	image_draw_rectan(bin_image);//Ԥ����
	
	data_stastics_l = 0;//����
	data_stastics_r = 0;//����
	
if (get_start_point(image_h - 2))//�ҵ�����ˣ���ִ�а�����û�ҵ���һֱ��
{

	search_l_r((uint16)USE_num, bin_image, &data_stastics_l, &data_stastics_r, start_point_l[0], start_point_l[1], start_point_r[0], start_point_r[1], &hightest);//������������

	
/* ����ȡ�ı߽�������ȡ���� �� ��������������õı���*/
	get_left(data_stastics_l);
	get_right(data_stastics_r);

/* �������������Ҫ�ŵ�if����ȥ�ˣ���Ҫ�ŵ�if����ȥ�ˣ���Ҫ�ŵ�if����ȥ�ˣ���Ҫ����˵����*/
	
//����or��������ߵĲ�ֵ��pid��������
//dir�������������ж�Ԫ��
//ʹ�ò���,ʮ��·�ڲ�������������
	
	
	judge_point_L_W();
	if(pic_flag.cross_all_flag==0
		&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0
		&&pic_flag.Scattered_card_flag==0
		&&pic_flag.endline_flag==0
		&&flap[0]==0
		&&pic_flag.obstacle_left_flag==0
		&&pic_flag.obstacle_right_flag==0
		&&pic_flag.ramp_flag==0
		&&time.sys_time>10)
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
		center_line[i] = (l_border[i] + r_border[i]) >> 1;//������
		center_ct+=(float)center_line[i]/(float)(image_h);
		center_l+=(float)l_border[i]/(float)(image_h);
		center_r+=(float)r_border[i]/(float)(image_h);
	}
//	time.cross_card_time=10;
//	pic_flag.round_left_flag=2;
	if(time.cross_card_time!=0)
	{
		if(pic_flag.round_left_flag!=0)
		{
			center_t=center_r-32.0;
		}
		else if(pic_flag.round_right_flag!=0)
		{
			center_t=center_l+32.0;
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


	
//	for (i = hightest; i < image_h-1; i++)
//	{
//		center_line[i] = (l_border[i] + r_border[i]) >> 1;//������
//		//�������������󣬲����ǲ��߻�����״̬����ȫ�����ʹ��һ����ߣ����������������ܸ����������
//		//��ȻҲ�ж�����ߵ��ҷ������Ǹ��˸о��ܷ�����������
//		tft180_draw_point(center_line[i], i, RGB565_GREEN);//��ʾ����	
//		tft180_draw_point(l_border[i], i, RGB565_RED);//��ʾ�����
//		tft180_draw_point(r_border[i], i, RGB565_RED);//��ʾ�ұ���
//	}
}
/*
��������㣨0.0��***************����>*************xֵ���
************************************************************
************************************************************
************************************************************
************************************************************
******************��������һ��ͼ��*************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
yֵ���*******************************************(188.120)
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
//		printf("n:%d\tL:%d\tR:%d\r\n",n,l_border[n],r_border[n]);//��ĺ�����
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
//		printf("n:%d\tcL:%d\tcR:%d\r\n",n,cdir.point_l[n],cdir.point_r[n]);//���Ƿ�Ϊ���ߵĵ�
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
		
//		printf("n��%d\tDil��%d\tDir��%d\r\n",n,dir_l[n],dir_r[n]);
		
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
		gpio_set_level(F_beer,GPIO_HIGH);	
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
//	printf("n��%d\tDil��%d\tDir��%d\r\n",n,dir_l[n],dir_r[n]);
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
	
	if(DL[2]>8&&DL[1]>3)
	{
		pic_flag.round_left_DIRN_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	else if(DR[2]>8&&DR[1]>3)
	{
		pic_flag.round_right_DIRN_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	
	
	if(cdir.L_L_NUM>30&&cdir.R_L_NUM<10&&ldn==1&&rdn==0)
	{
		pic_flag.round_POIL_NUM_flag++;
	}
	else if(cdir.R_L_NUM>30&&cdir.L_L_NUM<10&&rdn==1&&ldn==0)
	{	
		pic_flag.round_POIR_NUM_flag++;
	}
	
	
	if(pic_flag.round_left_DIR_flag!=0&&pic_flag.round_left_DIRN_flag!=0&&flap[0]==0)
	{
//		flap[0]=1;
		pic_flag.round_left_flag_num+=2;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	else if(pic_flag.round_right_DIR_flag!=0&&pic_flag.round_right_DIRN_flag!=0&&flap[0]==0)
	{
//		flap[0]=1;
		pic_flag.round_right_flag_num+=2;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	else
	{
		if(pic_flag.round_left_flag_num>0)
			pic_flag.round_left_flag_num--;
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
	else if(angleR==0&&angleL!=0)
	{
		pic_flag.round_angle_R_flag++;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	
	if(pic_flag.round_angle_L_flag!=0&&pic_flag.round_POIL_NUM_flag!=0&&pic_flag.round_left_flag_num>5)
	{
		pic_flag.round_left_flag_num=0;
		pic_flag.round_left_flag++;
		pic_flag.endline_flag=0;
		pic_flag.cross_all_flag=0;
		pic_flag.round_right_flag=0;
		flap[0]=1;
		pic_flag.cirque_num++;
//		gpio_set_level(F_beer,GPIO_HIGH);	
	}
	else if(pic_flag.round_angle_R_flag!=0&&pic_flag.round_POIR_NUM_flag!=0&&pic_flag.round_right_flag_num>5)
	{
		pic_flag.round_right_flag_num=0;
		pic_flag.round_right_flag++;
		pic_flag.endline_flag=0;
		pic_flag.cross_all_flag=0;
		pic_flag.round_left_flag=0;
		flap[0]=1;
		pic_flag.cirque_num++;
//		gpio_set_level(F_beer,GPIO_HIGH);	
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
			gpio_set_level(F_beer,GPIO_HIGH);	
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
		
//		printf("n:%d\tL:%d\tR:%d\r\n",n,l_border[n],r_border[n]);//��ĺ�����
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
		pic_flag.obstacle_left_flag++;
		gpio_set_level(F_beer,GPIO_HIGH);
	}
	else if(pic_flag.obstacle_POIR_flag>=1&&pic_flag.obstacle_POI_NUM_flag!=0&&pic_flag.obstacle_angle_flag!=0&&pic_flag.obstacle_color_flag!=0&&wide<80)
	{
		pic_flag.obstacle_right_flag++;
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
			pic_flag.ramp_flag++;
		}
	}
//	if(pic_flag.ramp_POI_NUM_flag!=0&&pic_flag.ramp_wide_flag!=0)
//	{
//		gpio_set_level(F_beer,GPIO_HIGH);		
//	}
	
}
