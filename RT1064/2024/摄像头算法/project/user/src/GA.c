#include "GA.h"

#define Population_Num 100							//【种群数量】
#define Population_Gen  12							//【基因长度】
#define Iterative_Num 1000							//【迭代次数】
#define Variation_Probability 90				//【变异概率】
#define Cross_Probability  0            //【基因交叉概率】  【暂时不能使用，交换过程存在问题】!!!!



uint16 Get_sign_max(float a[],uint16 n)
{
	uint8 j,i;
	float max=a[0];
	for(j=0;j<n;j++)
	{
		if(max<a[j])
		{
			max=a[j];
			i=j;
		}
	}
  return i;
}

uint16 Get_sign_min(float a[],uint16 n)
{
	uint8 j,i;
	float min=a[0];
	for(j=0;j<n;j++)
	{
		if(min>a[j])
		{
			min=a[j];
			i=j;
		}
	}
  return i;
}

float Get_max(float a[],uint16 n)
{
	uint8 j,i;
	float max=a[0];
	for(j=0;j<n;j++)
	{
		if(max<a[j])
		{
			max=a[j];
			i=j;
		}
	}
  return max;
}

float Get_min(float a[],uint16 n)
{
	uint8 j,i;
	float min=a[0];
	for(j=0;j<n;j++)
	{
		if(min>a[j])
		{
			min=a[j];
			i=j;
		}
	}
  return min;
}



uint16 Init_Population[Population_Num][Population_Gen];     //【储存种群的二维矩阵】
uint16 Pictrue_coord[12][2];								//【基因序列（坐标点）】
uint16 Coord[40][2];

void dis_solution()
{
	float dis[12];
	uint16 dist[12];
	uint8 xmin,ymin;
	uint8 choose_dis[12];

		Coord[0][0]=picture.rx[0];
		Coord[0][1]=picture.ry[0];
		Coord[1][0]=picture.rx[1];
		Coord[1][1]=picture.ry[1];
		Coord[2][0]=picture.rx[2];
		Coord[2][1]=picture.ry[2];
		Coord[3][0]=picture.rx[3];
		Coord[3][1]=picture.ry[3];
		Coord[4][0]=picture.rx[4];
		Coord[4][1]=picture.ry[4];
		Coord[5][0]=picture.rx[5];
		Coord[5][1]=picture.ry[5];
		Coord[6][0]=picture.rx[6];
		Coord[6][1]=picture.ry[6];
		Coord[7][0]=picture.rx[7];
		Coord[7][1]=picture.ry[7];
		Coord[8][0]=picture.rx[8];
		Coord[8][1]=picture.ry[8];
		Coord[9][0]=picture.rx[9];
		Coord[9][1]=picture.ry[9];
		Coord[10][0]=picture.rx[10];
		Coord[10][1]=picture.ry[10];
		Coord[11][0]=picture.rx[11];
		Coord[11][1]=picture.ry[11];
	for(uint8 i=0;i<Population_Gen;i++)
	{
		dist[i]=(Coord[i][0]+Coord[i][1]);
		//printf("dist[%d]=%d\r\n",i,dist[i]);
	}
	uint8 minsum=Get_sign_min(dist,Population_Gen);
	printf("minsum=%d\r\n",minsum);
	uint8 cx=Coord[minsum][0],cy=Coord[minsum][1];
	Coord[minsum][0]=Coord[0][0];Coord[minsum][1]=Coord[0][1];
	Coord[0][0]=cx;Coord[0][1]=cy;
	for(uint8 i=0;i<Population_Gen-1;i++)
	{
		for(uint8 n=i;n<Population_Gen;n++)
		{
			float s = pow(Coord[i][0]-Coord[n][0],2)+pow(Coord[i][1]-Coord[n][1],2);
			if(s!=0)
			{
				dis[n] = s;
			}
			else
				dis[n] = 0XFF;
		}
		choose_dis[i+1]=Get_sign_min(dis,Population_Gen);
		uint8 x=Coord[i+1][0],y=Coord[i+1][1];
		Coord[i+1][0]=Coord[choose_dis[i+1]][0];Coord[i+1][1]=Coord[choose_dis[i+1]][1];
		Coord[choose_dis[i+1]][0]=x;Coord[choose_dis[i+1]][1]=y;
	}
//	for(uint8 i=0;i<12;i++)
//	{
//		printf("%d,%d\r\n",Coord[i][0],Coord[i][1]);
//	}
}

void coord_text()
{
	for(uint8 i=0;i<Population_Gen;i++)
	{
		Pictrue_coord[i][0]=Coord[i][0];
		Pictrue_coord[i][1]=Coord[i][1];
	}
//	for(uint8 i=0;i<12;i++)
//	{
//		printf("%d,%d\r\n",Pictrue_coord[i][0],Pictrue_coord[i][1]);
//	}
}

uint16 create_random_number(uint8 n)             //【生成随机数】
{
	//srand(car_system.time);
	uint16 num = rand()%n;
  return num;
}

void Population_init()                     //【生成不重复随机出并初始化种群】
{
	uint8 n,m,flag=0;  
	uint16 num[12],rnum;
	for(uint16 i=0;i<Population_Num;i++)
	{
		n=0;
		for(uint8 j=0;j<12;j++)
		{
			num[j]=12;
		}
		
		while(n<12)
		{
			rnum = create_random_number(12);
			flag=0;
			for(m=0;m<n;m++)
			{
				if(num[m]==rnum)
				{
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				Init_Population[i][n]=rnum;
				//printf("Init_Population[%d][%d]=%d\r\n",i,n,Init_Population[i][n]);
				num[n++]=rnum;
			}
		}
	}
	for(uint8 i=0;i<Population_Gen;i++)
	{
		Init_Population[0][i]=i;
		//printf("Init_Population[%d][%d]=%d\r\n",0,i,Init_Population[0][i]);
	}
}


uint16 route[Population_Num][Population_Gen];						 //【用于储存每个个体状况】
float distance[Population_Num];                          //【储存基因长度】
float fitness[Population_Num];                           //【储存适应度】
uint16 fitsignmax,fitsignmin,dissignmin;
float fitmax,fitmin,dismin;
	
void Get_Fitness(uint8 flag)
{
		/******************************************************
		************【将每代情况放入route中为迭代做准备】*******
		******************************************************/
		for(uint16 n=0;n<Population_Num;n++)
		{
			if(flag==0)
			{
				for(uint8 m=0;m<Population_Gen;m++)
				{
					route[n][m]=Init_Population[n][m];
					//printf("route[%d][%d]=%d\r\n",n,m,route[n][m]);
				}
			}
			/******************************************************
			***************【具体迭代，计算基因长度】***************
			******************************************************/
			for(uint8 j=0;j<Population_Gen;j++)
			{
				//printf("route[%d][%d]=%d\r\n",n,j,route[n][j]);
				distance[n]=distance[n]+sqrt(pow(Pictrue_coord[route[n][j]][0]-Pictrue_coord[route[n][j+1]][0],2)+pow(Pictrue_coord[route[n][j]][1]-Pictrue_coord[(uint16)route[n][j+1]][1],2));	
			}
			//printf("distance[%d]=%f\r\n",n,distance[n]);
			distance[n]=1/distance[n];//【由于基因是取最长的继承，但是路程是取短的，所以进行取反处理】
			fitness[n]=distance[n];
			//printf("fitness[%d]=%f\r\n",fitness[n]);
		}		
		dissignmin = fitsignmax = Get_sign_max(fitness,Population_Num);
		fitsignmin = Get_sign_min(fitness,Population_Num);
		fitmax=Get_max(fitness,Population_Num);
		fitmin=Get_min(fitness,Population_Num);
		dismin=Get_max(distance,Population_Num);
		//printf("fitsignmin=%d,fitsignmax=%d,fitmin=%f,fitmax=%f\r\n",fitsignmin,fitsignmax,fitmin,fitmax);	
}

float fit1[Population_Num],fit2[Population_Num],fit3[Population_Num];
void choose_pop()
{
	/******************************************************
	************【选择步骤，选择继承下一代的个体】**********
	******************************************************/
	
	/************【归一化处理，方便后续轮盘赌】************/
	float sum=0;
	for(uint16 i=0;i<Population_Num;i++)
	{
		fit1[i]=(fitness[i]-fitmin)/(fitmax-fitmin);
		sum+=fit1[i];
		//printf("fit1[%d]=%f\r\n",i,fit1[i]);
	}
	//printf("sum=%f\r\n",sum);
	for(uint16 i=0;i<Population_Num;i++)
	{
		fit2[i]=fit1[i]/sum;
		//printf("fit2[%d]=%f\r\n",i,fit2[i]);
	}

	/**********【生成一个比较矩阵，用来进行轮盘赌】*********/ 

	for(uint16 i=0;i<Population_Num;i++)
	{		
		fit3[i]=0.1;
	}
	
	/***************【轮盘赌挑选出迭代个体】****************/ 
	
	for(uint16 i=0;i<Population_Num;i++)
	{ 
		if(fit2[i]>0.1)
		{
			for(uint8 n=0;n<Population_Gen;n++)
			{
				if(i>0)
				{
					route[i][n]=route[i-1][n];
				}
			}
		}
	}
//	for(uint8 i=0;i<Population_Num;i++)
//	{ 
//		for(uint8 n=0;n<Population_Gen;n++)
//		{
//			printf("route[%d][%d]=%d\r\n",i,n,route[i][n]);
//		}
//	}
}


/******************************************************
******************【父代交换基因】**********************
******************************************************/
uint16 cmember[4];
void cross_pop()
{
	for(uint16 i=0;i<Population_Num-1;i++)
	{
/***************【生成随机数挑选进行基因交换的个体】****************/ 
		uint16 rnum=rand()%100;
/***************【进行基因交换：取中间四个数进行交叉】**************/ 		
		if(rnum<Cross_Probability)
		{
			if(i<Population_Num-2)
			{
				//printf("%d与%d\r\n",i,i+1);//具体进行基因交换的个体编号
				cmember[0]=route[i][0];
				cmember[1]=route[i][1];
				cmember[2]=route[i][2];
				cmember[3]=route[i][3];
				for(uint8 n=0;n<Population_Gen-1;n++)
				{
					for(uint8 m=0;m<4;m++)
					{
						if(route[i+1][n]==cmember[m])
						{
							for(uint8 m=n;m<Population_Gen-1;m++)
							{
								route[i+1][m]=route[i+1][m+1];
							}
						}				
					}
				}
				route[i+1][8]=cmember[0];
				route[i+1][9]=cmember[1];
				route[i+1][10]=cmember[2];
				route[i+1][11]=cmember[3];
			}
		}
	}
/*****************【打印基因交换结果】******************/ 
//	for(uint8 s=0;s<Population_Num;s++)
//	{ 
//		for(uint8 b=0;b<Population_Gen;b++)
//		{
//			printf("route[%d][%d]=%d\r\n",s,b,route[s][b]);
//		}
//	}
}


/******************************************************
******************【基因变异过程】**********************
******************************************************/
void Variation()
{
	for(uint16 i=0;i<Population_Num;i++)
	{
		uint16 rnum=rand()%100;
		if(rnum<Variation_Probability)
		{
			uint16 n = rand()%12;
			uint16 m = rand()%12;
			//printf("第%d个体%d与%d\r\n",i,n,m);
			uint16 num=route[i][n];
			route[i][n]=route[i][m];
			route[i][m]=num;
		}
	}
//	for(uint8 s=0;s<Population_Num;s++)
//	{ 
//		for(uint8 b=0;b<Population_Gen;b++)
//		{
//			printf("route[%d][%d]=%d\r\n",s,b,route[s][b]);
//		}
//	}
}

float fit,dis=100;
uint8 signs;
uint16 the_end[Population_Gen];
void Iterative()
{
//	while(dis>70)
//	{
	for(uint16 i=0;i<Iterative_Num;i++)
	{
		Get_Fitness(i);
		choose_pop();
		cross_pop();
		Variation();
		
		if(fitmax>fit)
		{
			fit=fitmax;
			dis=1/dismin;
			signs=fitsignmax;
			for(uint8 m=0;m<Population_Gen;m++)
			{
				the_end[m]=route[signs][m];
			}
		}
	}
//	printf("迭代次数：%d,fitmax=%f,dis=%f\r\n",Iterative_Num,fit,dis);
	for(uint8 m=0;m<Population_Gen;m++)
	{
		the_end[m]=route[signs][m];
		Coord[m][0]=Pictrue_coord[the_end[m]][0];
		Coord[m][1]=Pictrue_coord[the_end[m]][1];
	}
//}
}

void run_GA()
{
	dis_solution();
//	coord_text();
//	Population_init();	
//	Iterative();
//	for(uint8 m=0;m<Population_Gen;m++)
//	{
//		printf("%d,%d\r\n",Coord[m][0],Coord[m][1]);
//	}
}
