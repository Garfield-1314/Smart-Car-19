#include "car_system.h"

CAR_SYSTEM car_system;
FLAG flag;

#define Ry 0.09  /*【车轴到车中心线的距离，0.07m】*/
#define Rx 0.10		/*【车轴到车中心线的距离，0.1m】*/

/********************************************************
【麦轮的逆运动学方程解算】
********************************************************/
void F_attitude_solution()
{
	
	car_system.Vw[0] = car_system.Vtx - car_system.Vty - 0*(Rx + Ry);
	car_system.Vw[1] = car_system.Vtx + car_system.Vty + 0*(Rx + Ry);
	car_system.Vw[2] = car_system.Vtx + car_system.Vty - 0*(Rx + Ry);
	car_system.Vw[3] = car_system.Vtx - car_system.Vty + 0*(Rx + Ry);	
/**************************************************************************************/
/*【全向时调用】*/
	if(((flap[0]==1||flap[0]==4||flap[0]==8||flap[0]==10||flap[0]==13||flap[0]==14)&&(pic_flag.cross_all_flag!=0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0))
		||((flap[0]==1||flap[0]==4||flap[0]==8||flap[0]==10||flap[0]==13||flap[0]==14)&&pic_flag.cross_all_flag==0&&pic_flag.round_left_flag!=0&&pic_flag.round_right_flag==0)
		||((flap[0]==1||flap[0]==4||flap[0]==8||flap[0]==10||flap[0]==13||flap[0]==14)&&pic_flag.cross_all_flag==0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag!=0)
		||((flap[0]==1||flap[0]==3)&&pic_flag.Scattered_card_flag!=0)
		||(flap[0]==1||flap[0]==6||flap[0]==8||flap[0]==13)&&pic_flag.endline_flag!=0
		||((flap[0]==1||flap[0]==2||flap[0]==3)&&pic_flag.ramp_flag!=0&&pic_flag.cross_all_flag==0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0))
	{
		car_system.Vtx = PID_dis(4,car_system.atx,car_system.chassis_dx);
		car_system.Vty = PID_dis(5,car_system.aty,car_system.chassis_dy);
		
		car_system.Vw[0] = car_system.Vtx - car_system.Vty - 0*(Rx + Ry);
		car_system.Vw[1] = car_system.Vtx + car_system.Vty + 0*(Rx + Ry);
		car_system.Vw[2] = car_system.Vtx + car_system.Vty - 0*(Rx + Ry);
		car_system.Vw[3] = car_system.Vtx - car_system.Vty + 0*(Rx + Ry);		
		
		
		if(car_system.Vw[0]<=-75)
			car_system.Vw[0]=-75;
		else if(car_system.Vw[0]>=75)
				car_system.Vw[0]=75;
		
		if(car_system.Vw[1]<=-75)
				car_system.Vw[1]=-75;
		else if(car_system.Vw[1]>=75)
				car_system.Vw[1]=75;

		if(car_system.Vw[2]<=-75)
				car_system.Vw[2]=-75;
		else if(car_system.Vw[2]>=75)
				car_system.Vw[2]=75;

		if(car_system.Vw[3]<=-75)
				car_system.Vw[3]=-75;
		else if(car_system.Vw[3]>=75)
				car_system.Vw[3]=75;
	}
/**************************************************************************************/
/**************************************************************************************/
	

	
	if(car_system.Vw[0]<=-75)
			car_system.Vw[0]=-75;
	else if(car_system.Vw[0]>=75)
			car_system.Vw[0]=75;
	
	if(car_system.Vw[1]<=-75)
			car_system.Vw[1]=-75;
	else if(car_system.Vw[1]>=75)
			car_system.Vw[1]=75;

	if(car_system.Vw[2]<=-75)
			car_system.Vw[2]=-75;
	else if(car_system.Vw[2]>=75)
			car_system.Vw[2]=75;

	if(car_system.Vw[3]<=-75)
			car_system.Vw[3]=-75;
	else if(car_system.Vw[3]>=75)
			car_system.Vw[3]=75;
}


/********************************************************
【麦轮的正运动学方程解算】
********************************************************/

void T_attitude_solution()
{
	get_encoder();
	
	car_system.Vx = (car_system.Vw[3] + car_system.Vw[2])/2;
	car_system.Vy = (car_system.Vw[2] - car_system.Vw[0])/2;

	car_system.chassis_dx = (wheel.distance[2]+wheel.distance[3])/2;
	car_system.chassis_dy = (wheel.distance[2]-wheel.distance[0])/2;
	
	car_system.distance = car_system.chassis_dx;
	car_system.distancey = car_system.chassis_dy;
//	car_system.Omega += (car_system.Vw[1]-car_system.Vw[2])/(2*(Rx+Ry));
}


/********************************************************
【用于解决车头锁定问题】
********************************************************/
int16 vw=0;
void Omega_attitude_solution()
{
	vw = 0;
/**************************************************************************************/
	
/*【全向时调用】*/
//	for(uint8 i = 0;i<4;i++)
//	{
//		car_system.Vw[i]=0;
//	}
/**************************************************************************************/
	
/*【先旋后行时调用】*/
//	if(!flag.car_turn_over)
//	{
//		for(uint8 i = 0;i<4;i++)
//			car_system.Vw[i]=0;
//	}
/**************************************************************************************/
	
	vw = PID_dis(6,(int16)car_system.Omega,(int16)car_system.set_Omega);
	
	if(vw>=45)
		vw=45;
	else if(vw<=-45)
		vw=-45;
	
	car_system.Vw[0]+=(int16)vw;
	car_system.Vw[1]-=(int16)vw;
	car_system.Vw[2]+=(int16)vw;
	car_system.Vw[3]-=(int16)vw;
}


void car_attitude()
{
	F_attitude_solution();/*【运行逆运动学方程】*/
	T_attitude_solution();/*【运行正运动学方程】*/
	if(((flap[0]==1)&&pic_flag.cross_all_flag!=0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0)
		||((flap[0]==1)&&pic_flag.cross_all_flag==0&&pic_flag.round_left_flag!=0&&pic_flag.round_right_flag==0)
		||((flap[0]==1)&&pic_flag.cross_all_flag==0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag!=0)
		||flap[0]==0)
	{
		race_speed_solution();
	}
	if(flag.keep_omega==OK)
	{
		Omega_attitude_solution();
	}
//	if(pic_flag.Scattered_card_flag==OK&&flap[0]==4)
//	{
//		round_speed_solution();
//	}
}

/**************************************************************************************/
/*【全向位移时不用调用turn】*/
/**************************************************************************************/

void turn()
{
	flag.keep_omega=OK;	
	if(car_system.set_Omega+1>=car_system.Omega&&car_system.Omega>=car_system.set_Omega-1)
	{
		system_delay_ms(200);
		if(car_system.set_Omega+1>=car_system.Omega&&car_system.Omega>=car_system.set_Omega-1)
		{
			flag.keep_omega=NO;	
			gyroscope963ra.yaw=0;
			car_system.set_Omega=0;		
			system_delay_ms(200);
			if(pic_flag.cross_all_flag!=0||pic_flag.round_left_flag!=0||pic_flag.round_right_flag!=0)
			{
				if(flap[0]==3)
				{
					flap[0]=4;
				}
				else if(flap[0]==9)
				{
					flap[0]=10;			
				}					
				else if(flap[0]==15)
				{
					obj.num=1;
					flap[0]=0;
					car_system.Vtx=55;
					flag.put_over=0;
					flag.cross_round_card_over++;
				}
			}

			if(pic_flag.Scattered_card_flag!=0&&pic_flag.endline_flag==0)
			{
				car_system.atx=0;
				car_system.aty=0;		
				car_system.Vtx=0;
				car_system.Vty=0;		
				if(flap[0]==2)
				{
					flap[0]=3;
//					clean_dis();
				}
				if(flap[0]==8)
				{
					flap[0]=0;
					pic_flag.Scattered_card_flag=0;
					car_system.Vtx=55;
				}
			}
			
			if(pic_flag.endline_flag!=0)
			{
				if(flap[0]==2)
					flap[0]=3;
				if(flap[0]==9)
					flap[0]=10;			
				if(flap[0]==7)
					flap[0]=1;
				if(obj.Scattered_num==0)
				{
					flap[0]=8;
				}
			}
			clean_dis();
			gyroscope963ra.yaw=0;
			car_system.set_Omega=0;
		}
	}
}



/**************************************************************************************/
int16 t_speed_l=0,t_speed_r=0,t_speed_m=0;

void race_speed_solution()/*【赛道行驶PID】*/
{
	t_speed_m=0;
	if(center_t!=0)
	{
		t_speed_m=PID_dis(9,(int)47.5,(int)center_t);
	}
	car_system.Vw[0]=(float)(car_system.Vw[0]-t_speed_m);
	car_system.Vw[2]=(float)(car_system.Vw[2]-t_speed_m);
	
	car_system.Vw[1]=(float)(car_system.Vw[1]+t_speed_m);
	car_system.Vw[3]=(float)(car_system.Vw[3]+t_speed_m);
}


void round_speed_solution()
{
	if(center_r>0)
	{
		pid.Kp[7]=1.25;pid.Kd[7]=0;
		pid.Kp[8]=1.25;pid.Kd[8]=0;
		t_speed_l=PID_dis(7,(int)20,(int)center_l);
		t_speed_r=PID_dis(8,(int)20,(int)center_r);
	}
	car_system.Vw[0]=(float)(car_system.Vw[0]-t_speed_l);
	car_system.Vw[2]=(float)(car_system.Vw[2]-t_speed_l);	

	car_system.Vw[1]=(float)(car_system.Vw[1]-t_speed_r);
	car_system.Vw[3]=(float)(car_system.Vw[3]-t_speed_r);	


}