#include "car_attitude.h"

#define Ry 0.09  /*【车轴到车中心线的距离，0.07m】*/
#define Rx 0.10		/*【车轴到车中心线的距离，0.1m】*/

CAR_SYSTEM car_system;
//float vw[4];

/********************************************************
【麦轮的逆运动学方程解算】
********************************************************/
void F_attitude_solution()
{
/**************************************************************************************/
/*【全向时调用】*/
//	car_system.Vtx = PID_dis(4,car_system.atx,car_system.chassis_dx);
//	car_system.Vty = PID_dis(5,car_system.aty,car_system.chassis_dy);
//	
//	car_system.Vw[0] = car_system.Vtx - car_system.Vty - car_system.Omega*(Rx + Ry);
//	car_system.Vw[1] = car_system.Vtx + car_system.Vty + car_system.Omega*(Rx + Ry);
//	car_system.Vw[2] = car_system.Vtx + car_system.Vty - car_system.Omega*(Rx + Ry);
//	car_system.Vw[3] = car_system.Vtx - car_system.Vty + car_system.Omega*(Rx + Ry);		
/**************************************************************************************/
	
/*【先旋后行时调用】*/
	if(flag[1]==0)
		car_system.Vtx = PID_dis(4,(float)car_system.at_distance,(float)car_system.distance);
	
	if(flag[1]==4)
	{
		car_system.Vtx = PID_dis(4,(float)car_system.atx,(float)car_system.chassis_dx);
		car_system.Vty = PID_dis(5,(float)car_system.aty,(float)car_system.chassis_dy);
	}
/**************************************************************************************/
	
	car_system.Vw[0] = car_system.Vtx - car_system.Vty - 0*(Rx + Ry);
	car_system.Vw[1] = car_system.Vtx + car_system.Vty + 0*(Rx + Ry);
	car_system.Vw[2] = car_system.Vtx + car_system.Vty - 0*(Rx + Ry);
	car_system.Vw[3] = car_system.Vtx - car_system.Vty + 0*(Rx + Ry);	
	
	if(car_system.Vw[0]<=-45)
			car_system.Vw[0]=-45;
	else if(car_system.Vw[0]>=45)
			car_system.Vw[0]=45;
	
	if(car_system.Vw[1]<=-45)
			car_system.Vw[1]=-45;
	else if(car_system.Vw[1]>=45)
			car_system.Vw[1]=45;

	if(car_system.Vw[2]<=-45)
			car_system.Vw[2]=-45;
	else if(car_system.Vw[2]>=45)
			car_system.Vw[2]=45;

	if(car_system.Vw[3]<=-45)
			car_system.Vw[3]=-45;
	else if(car_system.Vw[3]>=45)
			car_system.Vw[3]=45;
}


/********************************************************
【麦轮的正运动学方程解算】
********************************************************/

void T_attitude_solution()
{
	car_system.Vx = (car_system.Vw[3] + car_system.Vw[2])/2;
	car_system.Vy = (car_system.Vw[2] - car_system.Vw[0])/2;

	car_system.chassis_dx = (wheel.distance[2]+wheel.distance[3])/2;
	car_system.chassis_dy = (wheel.distance[2]-wheel.distance[0])/2;
	
	car_system.distance = car_system.chassis_dx;
//	car_system.Omega += (car_system.Vw[1]-car_system.Vw[2])/(2*(Rx+Ry));
	car_system.Omega = imu963ra.yaw;
}


/********************************************************
【用于解决车头锁定问题】
********************************************************/
//void Omega_attitude_solution()
//{
////	for(uint8 i=0;i<4;i++)
////		car_system.Vw[i]=0;

//	
//	car_system.set_Omega=0;
//	vw[0] = vw[2] = -PID_dis(6,car_system.set_Omega,car_system.Omega);
//	vw[1] = vw[3] = PID_dis(6,car_system.set_Omega,car_system.Omega);
//			
//	car_system.Vw[0]+=(float)vw[0];
//	car_system.Vw[1]+=(float)vw[1];
//	car_system.Vw[2]+=(float)vw[2];
//	car_system.Vw[3]+=(float)vw[3];
//}
//FLAG flag1;
int16 vw=0;
void Omega_attitude_solution()
{
/**************************************************************************************/
	
/*【全向时调用】*/
//		for(uint8 i = 0;i<4;i++)
//		car_system.Vw[i]=0;
/**************************************************************************************/
	
/*【先旋后行时调用】*/
	if(!flag1.car_turn_over&&flag[1]!=1&&flag[1]!=4)
	{
		for(uint8 i = 0;i<4;i++)
			car_system.Vw[i]=0;
	}
/**************************************************************************************/
	
	vw = PID_dis(6,(int16)car_system.Omega,(int16)car_system.set_Omega);
	
	car_system.Vw[0]+=(int16)vw;
	car_system.Vw[1]-=(int16)vw;
	car_system.Vw[2]+=(int16)vw;
	car_system.Vw[3]-=(int16)vw;
}


void car_move_dot()
{
	if(flag1.car_turn_over||flag[1]==1||flag[1]==4)
		F_attitude_solution();/*【运行逆运动学方程】*/
	Omega_attitude_solution();
	T_attitude_solution();/*【运行正运动学方程】*/

}

/**************************************************************************************/
/*【全向位移时不用调用turn】*/
/**************************************************************************************/
float x_t,y_t;
float xlast=0,ylast=0;
void turn(uint8 i)
{
//	float x_t,y_t;
	if(flag1.new_omega)/*【做判断，到达目的地后只会进行一次角度更新】*/
	{
		car_system.Omega=car_system.Omega/180*PI;/*【角度值转化为弧度值】：90度》》》》PI/2*/
		/*【常识坐标轴方案】【这两个公式用于坐标变换】【将目标点相对于场地的坐标变化为相对与的车身坐标】*/
		x_t=(x[i+1]-xlast)*cos(car_system.Omega)+(y[i+1]-ylast)*sin(car_system.Omega);
		y_t=(y[i+1]-ylast)*cos(car_system.Omega)-(x[i+1]-xlast)*sin(car_system.Omega); 
		car_system.set_Omega=-(float)(atan2(x_t,y_t)*180/PI)+car_system.Omega*180/PI;
		/*【完全运动学方案】*/
//		x_t=(y[i+1]-y[i])*cos(car_system.Omega)+(x[i+1]-x[i])*sin(car_system.Omega);
//		y_t=(x[i+1]-x[i])*cos(car_system.Omega)-(y[i+1]-y[i])*sin(car_system.Omega); 
//		car_system.set_Omega=(float)(atan2(x_t,y_t)*180/PI)-car_system.Omega*180/PI;/*【弧度值转化为角度值做旋转】*/
	
		flag1.new_omega=0;			/*【更新完毕角度置0】*/
		car_system.distance=0;/*【清0用于记录下一里程】*/
		for(uint8 n=0;n<4;n++)
			wheel.distance[n]=0;
	}
	if(car_system.set_Omega-0.75<=car_system.Omega&&car_system.set_Omega+0.75>=car_system.Omega)
	{
		system_delay_ms(100);
		if(car_system.set_Omega-0.75<=car_system.Omega&&car_system.set_Omega+0.75>=car_system.Omega)
		{
			flag1.stop_encoder=0;	/*【允许记录里程】*/
			flag1.car_turn_over=1;	/*【旋转完毕标志位置1】*/
			flag1.car_move_dot=1;	/*【旋转完毕允许移动】*/
			car_system.at_distance=sqrt((y[i+1]-y[i])*(y[i+1]-y[i])+(x[i+1]-x[i])*(x[i+1]-x[i]));/*【计算两点直线距离】*/
		}
	}
}
