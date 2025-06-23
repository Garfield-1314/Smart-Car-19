#include "location.h"

void Run_Dis()
{
	for(uint8 i=0;i<12;i++)
	{
		Pictrue_coord[i][1]=picture.ry[i];
	}
	
	Pictrue_coord[0][1]=picture.ry[0];
	Pictrue_coord[1][1]=picture.ry[1];
	Pictrue_coord[2][1]=picture.ry[2];
	Pictrue_coord[3][1]=picture.ry[3];
	Pictrue_coord[4][1]=picture.ry[4];
	Pictrue_coord[5][1]=picture.ry[5];
	Pictrue_coord[6][1]=picture.ry[6];
	Pictrue_coord[7][1]=picture.ry[7];
	Pictrue_coord[8][1]=picture.ry[8];
	Pictrue_coord[9][1]=picture.ry[9];
	Pictrue_coord[10][1]=picture.ry[10];
	Pictrue_coord[11][1]=picture.ry[11];
	
	Pictrue_coord[0][1]=1;
	Pictrue_coord[1][1]=1;
	Pictrue_coord[2][1]=1;
	Pictrue_coord[3][1]=2;
	Pictrue_coord[4][1]=3;
	Pictrue_coord[5][1]=4;
	Pictrue_coord[6][1]=4;
	Pictrue_coord[7][1]=6;
	Pictrue_coord[8][1]=7;
	Pictrue_coord[9][1]=12;
	Pictrue_coord[10][1]=12;
	Pictrue_coord[11][1]=12;
	for(uint8 i=0;i<12;i++)
	{
		for(uint8 n=i+1;n<12;n++)
		{
			if(Pictrue_coord[i][1]>Pictrue_coord[n][1])
			{
				uint8 f=Pictrue_coord[i][1];
				Pictrue_coord[i][1]=Pictrue_coord[n][1];
				Pictrue_coord[n][1]=f;
			}
		}
	}
	for(uint8 i=0;i<12;i++)
	{
		for(uint8 n=i+1;n<11;n++)
		{
			if(Pictrue_coord[i][1]==Pictrue_coord[n][1])
			{
					Pictrue_coord[n][1]=0;
			}
		}
	}
//	for(uint8 i=0;i<12;i++)
//	{
//		printf("%d\r\n",Pictrue_coord[i][1]);
//	}
}

void coord_solution(uint8 num,uint8 coordy)
{
	if(coordy!=0)
	{
		num=num*3;
		Coord[num][0]=1;Coord[num][1]=coordy;
		Coord[num+1][0]=27;Coord[num+1][1]=coordy;
		Coord[num+2][0]=1;Coord[num+2][1]=coordy;
	}
}


uint8 i=0,tnt=0;
int x[40],y[40];
void coord_get()
{
	for(uint8 i=0;i<12;i++)
	{
		coord_solution(i,Pictrue_coord[i][1]);
	}
	while(i<40)
	{
		if(Coord[i][1]!=0&&Coord[i][0]!=0)
		{
			x[tnt]=Coord[i][1]*20;
			y[tnt]=(-Coord[i][0])*20-10+35;
			tnt++;
		}
		i++;
	}

	for(uint8 i=0;i<40;i++)
	{
		printf("%d,%d\r\n",y[i],x[i]);
	}
}

void go_out()
{
	car_system.atx=50;
	car_system.aty=-5;
	if(((int)car_system.chassis_dx == car_system.atx) && ((int)car_system.chassis_dy==car_system.aty))
	{
		flag[1]=1;
		printf("%d\r\n",flag[1]);
	}
	else
		flag[1]=0;
}


uint8 flap=0;
void goto_coord()
{
	if(x[flap]!=0&&y[flap]!=0)
	{
		car_system.atx=x[flap];
		car_system.aty=y[flap];
	}
	else if(x[flap]==0&&y[flap]==0)
	{
		flag[1]=4;
	}
	if(((int)car_system.chassis_dx == car_system.atx) && ((int)car_system.chassis_dy==car_system.aty))
		flap++;
}

uint8 flap2=0;
void go_back()
{
	if(flap2==0)
	{
		car_system.atx=50;
		car_system.aty=-5;
	}
	if(flap2==1)
	{
		car_system.atx=0;
		car_system.aty=-5;
	}
	if(((int)car_system.chassis_dx == car_system.atx) && ((int)car_system.chassis_dy==car_system.aty))
	{
		flap2=1;
	}
}
