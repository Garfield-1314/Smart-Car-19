#include "even_solution.h"

void even_solution()
{
	if(flag[1]==0)
	{
		goto_coord();
	}
	if(flag[1]==1)
	{
		see_rect();
	}
	if(flag[1]==2)
	{
		juge_pictrue();
	}
	if(flag[1]==3)
	{
		pikup();
	}
	if(flag[1]==4)
	{
		goto_destination();
	}
}


uint8 i=0;
void goto_coord()
{
//	car_system.coord_y[0]=0;car_system.coord_x[0]=0;
//	car_system.coord_y[1]=rx[1];car_system.coord_x[1]=ry[1];
//	car_system.coord_y[2]=rx[2];car_system.coord_x[2]=ry[2];
//	car_system.coord_y[3]=rx[3];car_system.coord_x[3]=ry[3];
//	car_system.coord_y[4]=rx[4];car_system.coord_x[4]=ry[4];
//	car_system.coord_y[5]=rx[5];car_system.coord_x[5]=ry[5];
//	car_system.coord_y[6]=rx[6];car_system.coord_x[6]=ry[6];
//	car_system.coord_y[7]=rx[7];car_system.coord_x[7]=ry[7];
//	car_system.coord_y[8]=rx[8];car_system.coord_x[8]=ry[8];
//	car_system.coord_y[9]=rx[9];car_system.coord_x[9]=ry[9];
//	car_system.coord_y[10]=rx[10];car_system.coord_x[10]=ry[10];
//	car_system.coord_y[11]=rx[11];car_system.coord_x[11]=ry[11];
//	car_system.coord_y[12]=rx[12];car_system.coord_x[12]=ry[12];
//	car_system.coord_y[14]=0;car_system.coord_x[14]=0;
	
	car_system.coord_y[0]=0;car_system.coord_x[0]=0;
	car_system.coord_y[1]=1;car_system.coord_x[1]=3;
	
	car_system.coord_y[2]=5;car_system.coord_x[2]=6;
	car_system.coord_y[3]=6;car_system.coord_x[3]=9;
	car_system.coord_y[4]=5;car_system.coord_x[4]=12;
	car_system.coord_y[5]=5;car_system.coord_x[5]=17;
	car_system.coord_y[6]=17;car_system.coord_x[6]=17;
	car_system.coord_y[7]=16;car_system.coord_x[7]=14;
	car_system.coord_y[8]=12;car_system.coord_x[8]=14;
	car_system.coord_y[9]=12;car_system.coord_x[9]=9;
	car_system.coord_y[10]=14;car_system.coord_x[10]=5;
	car_system.coord_y[11]=21;car_system.coord_x[11]=6;
	car_system.coord_y[12]=-10;car_system.coord_x[12]=50;
	car_system.coord_y[13]=0;car_system.coord_x[13]=0;
	car_system.coord_y[14]=0;car_system.coord_x[14]=0;
	////////////////////////////////////////////////////////
	//【a4坐标向实际坐标的转化】
	////////////////////////////////////////////////////////
	for(uint8 n=1;n<12;n++)
	{
		if(car_system.coord_x[n]!=0)
		{
			car_system.coord_x[n]=car_system.coord_x[n]*20;
		}
		if(car_system.coord_y[n]!=0)
		{
			car_system.coord_y[n]=(-car_system.coord_y[n])*20-10+35;
		}
	}
	////////////////////////////////////////////////////////
	//【更新坐标】
	////////////////////////////////////////////////////////
	if((car_system.coord_x[i]!=0||car_system.coord_y[i]!=0)||i==0)
	{
		if((int)car_system.chassis_dx == (int)(car_system.coord_x[i]) && (int)car_system.chassis_dy==(int)(car_system.coord_y[i])&&flag[0]==0)
		{
			if(i>=2)
			{
				flag[1]=1;
				flag[2]=0;
			}
			else
				flag[1]=0;
			
			flag[0]=1;
			i++;
			if(car_system.coord_x[i]!=0||car_system.coord_y[i]!=0)
			{
				car_system.atx=car_system.coord_x[i];
				car_system.aty=car_system.coord_y[i];
			}
			if(i>12)
			{
				if(i>=13)
				{
					car_system.atx=-10;
					car_system.aty=-20;
				}
				flag[1]=0;
			}
		}
	}
}

void see_rect()
{
	uart_write_byte(UART_1,0x01);
	if(rx[0]!=0&&ry[0]!=0)
	{	
		car_system.Vtx = PID_dis(7,60,ry[0]);
		car_system.Vty = PID_dis(8,80,rx[0]);

		if(rx[0]<=82&&rx[0]>=78&&ry[0]>=58&&ry[0]<=62)
		{
			car_system.Vtx = 0;
			car_system.Vty = 0;
			flag[1]=2;
			flag[2]=0;
			uart_write_byte(UART_1,0x02);
		}
		else
		{
			flag[1]=1;
			uart_write_byte(UART_1,0x01);
		}
	}
}


uint8 picture_num=0;
void juge_pictrue()
{
	uart_write_byte(UART_1,0x02);
	if(picture!=0)
	{
		gpio_set_level(F_beer,GPIO_HIGH);
		picture_num++;
//		switch(picture_num)
//		{
//			case 1:car_system.destinationx=10;car_system.destinationy=2;break;
//			case 2:car_system.destinationx=0;car_system.destinationy=-17;break;
//			case 3:car_system.destinationx=10;car_system.destinationy=-37;break;
//			case 4:car_system.destinationx=27;car_system.destinationy=-30;break;	
//			case 5:car_system.destinationx=10;car_system.destinationy=2;break;
//			default:car_system.destinationx=0;car_system.destinationy=-17;break;
//		}
//		car_system.destinationx=car_system.destinationx*20-10;
//		car_system.destinationy=car_system.destinationy*20-10+25;
			picture=0;
			flag[1]=3;
			flag[2]=0;
		uart_write_byte(UART_1,0x01);
	}
	else
	{
		flag[1]=2;
		uart_write_byte(UART_1,0x02);
	}
		
}

void pikup()
{
	uart_write_byte(UART_1,0x01);
	gpio_set_level(F_beer,GPIO_LOW);
	Set_cds5516_angle2(0,470,0,800);
	system_delay_ms(1500);
	Set_cds5516_angle2(0,150,0,800);
	system_delay_ms(1500);
	flag[1]=4;
}

void goto_destination()
{
//	if((int)car_system.chassis_dx == (int)(car_system.destinationx) && (int)car_system.chassis_dy==(int)(car_system.destinationy))
//	{
//		gpio_set_level(B23,GPIO_LOW);
//		flag[1]=0;
//	}
//	else
//		flag[1]=4;
	flag[1]=0;
}