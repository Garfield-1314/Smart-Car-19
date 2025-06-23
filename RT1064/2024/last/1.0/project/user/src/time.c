#include "time.h"

void sys_time(void)
{
	static uint8 ms100_1;
	ms100_1++;
	if(ms100_1%5==0)
	{
		gpio_set_level(F_beer,GPIO_LOW);	
	}
	if(ms100_1==10)
	{
		ms100_1=0;
		time.sys_time++;
		printf("flap£º%d\r\n",flap[0]);		
		printf("time.cross_card_time:%d\r\n",time.cross_card_time);
	}
}

void card_identify_time_solution(void)
{
	static uint8 ms100_2;
	ms100_2++;
	if(ms100_2==10)
	{
		ms100_2=0;
		if(flap[0]==5||flap[0]==11)
		{
			if(obj.y<30||obj.x<30||obj.y>130)
				time.micro_distance_time++;
			else
				time.micro_distance_time=0;
		}
		else
		{
			time.micro_distance_time=0;
		}
		
		if(flap[0]==6&&(obj.y<30||obj.x<30||obj.y>130))
		{
			time.identify_card_time++;
		}
		else
		{
			time.identify_card_time=0;						
		}
		obj.y0=0;obj.x0=0;obj.y1=0;obj.x1=0;obj.y=0;obj.x=0;obj.c=0;
	}
}

void cross_round_card_over_solution(void)
{
	static uint8 ms100_3;
	ms100_3++;
	if(ms100_3==10)
	{
		ms100_3=0;
		if(flag.cross_round_card_over!=0)
		{
			time.cross_card_time++;
			if(pic_flag.cross_all_flag!=0)
			{
				switch(turn_num)
				{
					case 0:if(time.cross_card_time>6)
					{
						pic_flag.cross_all_flag=0;
						pic_flag.round_left_flag=0;
						pic_flag.round_right_flag=0;
						pic_flag.Scattered_card_flag=0;
						flag.cross_round_card_over=0;
						time.cross_card_time=0;
						turn_num=0;
					}break;
					case 1:if(time.cross_card_time>5)
					{
						pic_flag.cross_all_flag=0;
						pic_flag.round_left_flag=0;
						pic_flag.round_right_flag=0;
						pic_flag.Scattered_card_flag=0;
						flag.cross_round_card_over=0;
						time.cross_card_time=0;
						turn_num=0;
					}break;
					case 2:if(time.cross_card_time>4)
					{
						pic_flag.cross_all_flag=0;
						pic_flag.round_left_flag=0;
						pic_flag.round_right_flag=0;
						pic_flag.Scattered_card_flag=0;
						flag.cross_round_card_over=0;
						time.cross_card_time=0;
						turn_num=0;
					}break;
					case 3:if(time.cross_card_time>3)
					{
						pic_flag.cross_all_flag=0;
						pic_flag.round_left_flag=0;
						pic_flag.round_right_flag=0;
						pic_flag.Scattered_card_flag=0;
						flag.cross_round_card_over=0;
						time.cross_card_time=0;
						turn_num=0;
					}break;			
					case 4:if(time.cross_card_time>1)
					{
						pic_flag.cross_all_flag=0;
						pic_flag.round_left_flag=0;
						pic_flag.round_right_flag=0;
						pic_flag.Scattered_card_flag=0;
						flag.cross_round_card_over=0;
						time.cross_card_time=0;
						turn_num=0;
					}break;						
				}
			}
			else if(pic_flag.round_left_flag!=0||pic_flag.round_right_flag!=0)
			{
				if(time.Line_time>0)
					time.Line_time--;
				switch(turn_num)
				{
					case 0:if(time.cross_card_time>7)
					{
						pic_flag.cross_all_flag=0;
						pic_flag.round_left_flag=0;
						pic_flag.round_right_flag=0;
						pic_flag.Scattered_card_flag=0;
						flag.cross_round_card_over=0;
						time.cross_card_time=0;
						turn_num=0;
					}break;
					case 1:if(time.cross_card_time>6)
					{
						pic_flag.cross_all_flag=0;
						pic_flag.round_left_flag=0;
						pic_flag.round_right_flag=0;
						pic_flag.Scattered_card_flag=0;
						flag.cross_round_card_over=0;
						time.cross_card_time=0;
						time.cross_card_time=0;
						turn_num=0;
					}break;
					case 2:if(time.cross_card_time>5)
					{
						pic_flag.cross_all_flag=0;
						pic_flag.round_left_flag=0;
						pic_flag.round_right_flag=0;
						pic_flag.Scattered_card_flag=0;
						flag.cross_round_card_over=0;
						time.cross_card_time=0;
						turn_num=0;
					}break;
					case 3:if(time.cross_card_time>4)
					{
						pic_flag.cross_all_flag=0;
						pic_flag.round_left_flag=0;
						pic_flag.round_right_flag=0;
						pic_flag.Scattered_card_flag=0;
						flag.cross_round_card_over=0;
						time.cross_card_time=0;
						turn_num=0;
					}break;			
					case 4:if(time.cross_card_time>2)
					{
						pic_flag.cross_all_flag=0;
						pic_flag.round_left_flag=0;
						pic_flag.round_right_flag=0;
						pic_flag.Scattered_card_flag=0;
						flag.cross_round_card_over=0;
						time.cross_card_time=0;
						turn_num=0;
					}break;		
				}
			}
			else
			{
				time.cross_card_time=0;
				flag.cross_round_card_over=0;
			}
		}
		else
		{
				time.cross_card_time=0;
				flag.cross_round_card_over=0;
		}
	}
}

void Scattered_card_time_solution()
{
//	static uint8 ms100_4;
//	ms100_4++;
//	if(ms100_4==10)
//	{
//		ms100_4=0;
//		if(flag.Scattered_card_EN==NO)
//		{
//			if(pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0&&pic_flag.cross_all_flag==0)
//			{
//				time.Scattered_time++;
//				uint8 s=0;
//				switch(turn_num)
//				{
//					case 0:s=6;break;
//					case 1:s=5;break;
//					case 2:s=4;break;
//					case 3:s=3;break;
//					case 4:s=2;break;
//				}
//				if(time.Scattered_time==s)
//					flag.Scattered_card_EN=OK;
//			}
//		}
//	}
}

void obstacle_time_solution()
{
	static uint8 ms100_5;
	ms100_5++;
	if(ms100_5==1)
	{
		ms100_5=0;
		if(pic_flag.obstacle_left_flag!=0||pic_flag.obstacle_right_flag!=0)
		{
			time.obstacle_time++;
			if(time.obstacle_time>20)
			{
				pic_flag.obstacle_left_flag=0;
				pic_flag.obstacle_right_flag=0;
			}
		}
		else
			time.obstacle_time=0;
	}
}