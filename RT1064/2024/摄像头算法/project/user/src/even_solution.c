#include "even_solution.h"

uint8 i=0;
uint8 flag[10];
void even_solution()
{
	if(flag[1]==0)
	{
		coord_dis();
		move();
	}
	if(flag[1]==1)
	{
		micro_distance();
	}
	if(flag[1]==2)
	{
		get_obj();
	}
	if(flag[1]==3)
	{
		put_obj();
	}
	if(flag[1]==4)
	{
		back_to_coord();
	}
}


int16 x[20],y[20];

void coord_dis()
{
	x[0]=0;y[0]=0;
	
////////////////////////1
	
	x[1]=15;y[1]=60;
	
	switch(color[1])
	{
		case 1:x[2]=90;y[2]=100;break;  //ºì¿ò
		case 2:x[2]=85;y[2]=0;break;  //»Æ¿ò
		case 3:x[2]=90;y[2]=65;break;  //À¶¿ò
	}
	
////////////////////////2
	
	x[3]=40;y[3]=105;
	
	switch(color[1])
	{
		case 1:x[4]=90;y[4]=100;break;  //ºì¿ò
		case 2:x[4]=85;y[4]=0;break;  //»Æ¿ò
		case 3:x[4]=90;y[4]=65;break;  //À¶¿ò
	}
	
////////////////////////3
	
	x[5]=35;y[5]=115;
	
	switch(color[1])
	{
		case 1:x[6]=90;y[6]=100;break;  //ºì¿ò
		case 2:x[6]=85;y[6]=0;break;  //»Æ¿ò
		case 3:x[6]=90;y[6]=65;break;  //À¶¿ò
	}

////////////////////////4
	
	x[7]=15;y[7]=65;
	
	switch(color[1])
	{
		case 1:x[8]=90;y[8]=100;break;  //ºì¿ò
		case 2:x[8]=85;y[8]=0;break;  //»Æ¿ò
		case 3:x[8]=90;y[8]=65;break;  //À¶¿ò
	}
	
////////////////////////5
	
	x[9]=17;y[9]=90;
	
	switch(color[1])
	{
		case 1:x[10]=90;y[10]=100;break;  //ºì¿ò
		case 2:x[10]=85;y[10]=0;break;  //»Æ¿ò
		case 3:x[10]=90;y[10]=65;break;  //À¶¿ò
	}
	
////////////////////////6

	x[11]=17;y[11]=98;
	
	switch(color[1])
	{
		case 1:x[12]=90;y[12]=100;break;  //ºì¿ò
		case 2:x[12]=85;y[12]=0;break;  //»Æ¿ò
		case 3:x[12]=90;y[12]=65;break;  //À¶¿ò
	}
	
////////////////////////7

	x[13]=-10;y[13]=50;
	
	switch(color[1])
	{
		case 1:x[14]=90;y[14]=100;break;  //ºì¿ò
		case 2:x[14]=85;y[14]=0;break;  //»Æ¿ò
		case 3:x[14]=90;y[14]=65;break;  //À¶¿ò
	}

////////////////////////8

	x[15]=-10;y[15]=90; 
	
	switch(color[1])
	{
		case 1:x[16]=90;y[16]=100;break;  //ºì¿ò
		case 2:x[16]=85;y[16]=0;break;  //»Æ¿ò
		case 3:x[16]=90;y[16]=65;break;  //À¶¿ò
	}

////////////////////////9

	x[17]=-10;y[17]=100;
	
	switch(color[1])
	{
		case 1:x[18]=90;y[18]=100;break;  //ºì¿ò
		case 2:x[18]=85;y[18]=0;break;  //»Æ¿ò
		case 3:x[18]=90;y[18]=65;break;  //À¶¿ò
	}

////////////////////////10
	x[19]=-30;y[19]=-30;
}


uint16 rcx,rcy;
uint16 ax=70,ay=25;
void micro_distance()
{
	pid.Kp[7]=0.50;
	pid.Kp[8]=0.50;
	if(rcx!=0&&rcy!=0)
	{	
		car_system.Vtx = PID_dis(7,(float)ay,(float)rcy);
		car_system.Vty = PID_dis(8,(float)ax,(float)rcx);
		if(rcx<=ax+5&&rcx>=ax-5&&rcy<=ay+5&&rcy>=ay-5)
		{
			car_system.Vtx = 0;
			car_system.Vty = 0;
			flag[1]=2;
			car_system.er_x=-(float)car_system.chassis_dx;
			car_system.er_y=-(float)car_system.chassis_dy;
			color[1]=color[0];
			coord_dis();
			color[1]=0;
			for(uint8 n=0;n<4;n++)
					wheel.distance[n]=0;
		}
		else
			flag[1]=1;
	}
	else
	{
		car_system.Vtx = 0;
		car_system.Vty = 0;
	}
	if(stime>50)
	{
		rcy=0;
		rcx=0;
		stime=0;
	}
}

void go_coord()
{
	if(flag1.car_move_dot==1)
	{
		if((car_system.at_distance>car_system.distance-1&&car_system.at_distance<car_system.distance+1))
		{
			system_delay_ms(100);
			if((car_system.at_distance>car_system.distance-1&&car_system.at_distance<car_system.distance+1))
			{
				if(flag1.car_turn_over==1)
				{				
					flag1.car_turn_over=0;
					flag1.new_omega=1;						
					system_delay_ms(200);
					flag1.move_i++;
					xlast=x[flag1.move_i];
					ylast=y[flag1.move_i];
					flag1.car_move_dot=0;
					flag1.stop_encoder=1;
					if(flag1.move_i==1||flag1.move_i==3||flag1.move_i==5||flag1.move_i==7||flag1.move_i==9||flag1.move_i==11||flag1.move_i==13||flag1.move_i==15||flag1.move_i==17)
					{                                                                                                                                 
						flag[1]=1;
					}
					if(flag1.move_i==2||flag1.move_i==4||flag1.move_i==6||flag1.move_i==8||flag1.move_i==10||flag1.move_i==12||flag1.move_i==14||flag1.move_i==16||flag1.move_i==18)
					{
						flag[1]=3;
					}
					for(uint8 n=0;n<4;n++)
						wheel.distance[n]=0;
				}
			}
		}
	}
}

void back_to_coord()
{
//	printf("%f\t%f\t%f\t%f\r\n",car_system.er_x,car_system.er_y,car_system.chassis_dx,car_system.chassis_dy);
	car_system.atx=car_system.er_x;
	car_system.aty=car_system.er_y;
	if(car_system.atx>=car_system.chassis_dx-0.7&&car_system.atx<=car_system.chassis_dx+0.7&&
		car_system.aty>=car_system.chassis_dy-0.7&&car_system.aty<=car_system.chassis_dy+0.7)
	{
		system_delay_ms(100);
		if(car_system.atx>=car_system.chassis_dx-0.7&&car_system.atx<=car_system.chassis_dx+0.7&&
		car_system.aty>=car_system.chassis_dy-0.7&&car_system.aty<=car_system.chassis_dy+0.7)
		{
			for(uint8 n=0;n<4;n++)
				wheel.distance[n]=0;
			flag[1]=0;
			system_delay_ms(500);
			car_system.atx=0;
			car_system.aty=0;
			car_system.er_x=0;
			car_system.er_y=0;
		}
	}
	
}

void move()
{
	coord_dis();
	turn(flag1.move_i);
	go_coord();
}

void get_obj()
{
	pwm_set_duty(PWM1_MODULE0_CHA_D12,0);
	pwm_set_duty(PWM1_MODULE0_CHB_D13,0);
	pwm_set_duty(PWM2_MODULE3_CHA_D2,0);
	pwm_set_duty(PWM2_MODULE3_CHB_D3,0);
//	gpio_set_level(B16,1);
	system_delay_ms(1000);
//	pwm_set_duty(PWM2_MODULE0_CHA_C6,390);//600=90
	system_delay_ms(1000);
//	pwm_set_duty(PWM2_MODULE0_CHA_C6,600);
	system_delay_ms(2000);
//	pwm_set_duty(PWM2_MODULE0_CHA_C6,390);//600=90
	flag[1]=4;
	

}

void put_obj()
{
	pwm_set_duty(PWM1_MODULE0_CHA_D12,0);
	pwm_set_duty(PWM1_MODULE0_CHB_D13,0);
	pwm_set_duty(PWM2_MODULE3_CHA_D2,0);
	pwm_set_duty(PWM2_MODULE3_CHB_D3,0);
//	gpio_set_level(B16,0);
	system_delay_ms(3000);
	flag[1]=4;
}