#include "car_attitude.h"

#define Ry 0.09  /*�����ᵽ�������ߵľ��룬0.07m��*/
#define Rx 0.10		/*�����ᵽ�������ߵľ��룬0.1m��*/

CAR_SYSTEM car_system;
//float vw[4];

/********************************************************
�����ֵ����˶�ѧ���̽��㡿
********************************************************/
void F_attitude_solution()
{
/**************************************************************************************/
/*��ȫ��ʱ���á�*/
//	car_system.Vtx = PID_dis(4,car_system.atx,car_system.chassis_dx);
//	car_system.Vty = PID_dis(5,car_system.aty,car_system.chassis_dy);
//	
//	car_system.Vw[0] = car_system.Vtx - car_system.Vty - car_system.Omega*(Rx + Ry);
//	car_system.Vw[1] = car_system.Vtx + car_system.Vty + car_system.Omega*(Rx + Ry);
//	car_system.Vw[2] = car_system.Vtx + car_system.Vty - car_system.Omega*(Rx + Ry);
//	car_system.Vw[3] = car_system.Vtx - car_system.Vty + car_system.Omega*(Rx + Ry);		
/**************************************************************************************/
	
/*����������ʱ���á�*/
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
�����ֵ����˶�ѧ���̽��㡿
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
�����ڽ����ͷ�������⡿
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
	
/*��ȫ��ʱ���á�*/
//		for(uint8 i = 0;i<4;i++)
//		car_system.Vw[i]=0;
/**************************************************************************************/
	
/*����������ʱ���á�*/
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
		F_attitude_solution();/*���������˶�ѧ���̡�*/
	Omega_attitude_solution();
	T_attitude_solution();/*���������˶�ѧ���̡�*/

}

/**************************************************************************************/
/*��ȫ��λ��ʱ���õ���turn��*/
/**************************************************************************************/
float x_t,y_t;
float xlast=0,ylast=0;
void turn(uint8 i)
{
//	float x_t,y_t;
	if(flag1.new_omega)/*�����жϣ�����Ŀ�ĵغ�ֻ�����һ�νǶȸ��¡�*/
	{
		car_system.Omega=car_system.Omega/180*PI;/*���Ƕ�ֵת��Ϊ����ֵ����90�ȡ�������PI/2*/
		/*����ʶ�����᷽��������������ʽ��������任������Ŀ�������ڳ��ص�����仯Ϊ�����ĳ������꡿*/
		x_t=(x[i+1]-xlast)*cos(car_system.Omega)+(y[i+1]-ylast)*sin(car_system.Omega);
		y_t=(y[i+1]-ylast)*cos(car_system.Omega)-(x[i+1]-xlast)*sin(car_system.Omega); 
		car_system.set_Omega=-(float)(atan2(x_t,y_t)*180/PI)+car_system.Omega*180/PI;
		/*����ȫ�˶�ѧ������*/
//		x_t=(y[i+1]-y[i])*cos(car_system.Omega)+(x[i+1]-x[i])*sin(car_system.Omega);
//		y_t=(x[i+1]-x[i])*cos(car_system.Omega)-(y[i+1]-y[i])*sin(car_system.Omega); 
//		car_system.set_Omega=(float)(atan2(x_t,y_t)*180/PI)-car_system.Omega*180/PI;/*������ֵת��Ϊ�Ƕ�ֵ����ת��*/
	
		flag1.new_omega=0;			/*��������ϽǶ���0��*/
		car_system.distance=0;/*����0���ڼ�¼��һ��̡�*/
		for(uint8 n=0;n<4;n++)
			wheel.distance[n]=0;
	}
	if(car_system.set_Omega-0.75<=car_system.Omega&&car_system.set_Omega+0.75>=car_system.Omega)
	{
		system_delay_ms(100);
		if(car_system.set_Omega-0.75<=car_system.Omega&&car_system.set_Omega+0.75>=car_system.Omega)
		{
			flag1.stop_encoder=0;	/*�������¼��̡�*/
			flag1.car_turn_over=1;	/*����ת��ϱ�־λ��1��*/
			flag1.car_move_dot=1;	/*����ת��������ƶ���*/
			car_system.at_distance=sqrt((y[i+1]-y[i])*(y[i+1]-y[i])+(x[i+1]-x[i])*(x[i+1]-x[i]));/*����������ֱ�߾��롿*/
		}
	}
}
