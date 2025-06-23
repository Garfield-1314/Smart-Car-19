#include "even_solution.h"

uint8 flap[10];
TIME time;
uint8 new_omega=0;
void event()
{
	
	image_process();
	road_element();
	if(pic_flag.cross_all_flag!=0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0&&pic_flag.Scattered_card_flag==0)
	{
		cross_cirque();
	}
	else if(pic_flag.cross_all_flag==0&&(pic_flag.round_left_flag!=0||pic_flag.round_right_flag!=0)&&pic_flag.Scattered_card_flag==0)
	{
		round_cirque();
	}
	else if(pic_flag.Scattered_card_flag!=0
		&&pic_flag.cross_all_flag==0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0)
	{
		Scattered_cirque();
	}
	else if(pic_flag.endline_flag!=0
		&&pic_flag.Scattered_card_flag==0
		&&pic_flag.cross_all_flag==0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0)
	{
		end_event();
	}
	else if(pic_flag.ramp_flag!=0
		&&pic_flag.cross_all_flag==0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0&&pic_flag.Scattered_card_flag==0)
	{
		ramp_event();
	}
	
}

void ramp_event()
{
	if(flap[0]==1)
	{
		go_to_coord();
	}
	if(flap[0]==2)
	{
		go_to_coord();
	}
	if(flap[0]==3)
	{
		go_to_coord();
	}
}

void end_event()
{
	if(flap[0]==1)
	{
		go_to_coord();
	}
	if(flap[0]==2)
	{
		//ÓÒ
		car_system.set_Omega=-90;
		
		//×ó
//		car_system.set_Omega=90;
		turn();
	}
	if(flap[0]==3)
	{
		flag.get_distance=OK;
		micro_distance();
	}
	if(flap[0]==4)
	{
		identify_num_word();
	}
	if(flap[0]==5)
	{
		put_card();
	}
	if(flap[0]==6)
	{
		back_coord();
	}
	if(flap[0]==7)
	{
//		//ÓÒ
		car_system.set_Omega=90;
		
		//×ó
//		car_system.set_Omega=-92;
		turn();
	}
	if(flap[0]==8)
	{
		flag.get_distance=OK;	
//		image_process();
		flap[0]=8;
		car_system.atx=225;
		if(car_system.atx+1>car_system.chassis_dx&&car_system.atx-1<car_system.chassis_dx)
		{
			gpio_set_level(F_beer,GPIO_HIGH);
			flap[0]=99;
			while(1)
			{
				car_system.Vtx=0;
				car_system.Vty=0;		
			}			
		}
	}
	if(flap[0]==13)
	{
		go_to_coord();
	}
	if(flap[0]==14)
	{
		car_system.Vtx=0;
		gyroscope963ra.yaw=0;
		system_delay_ms(1000);
		gyroscope963ra.yaw=0;
		flap[0]=1;
	}
}

void Scattered_cirque()
{
	if(flap[0]==1)
	{
		flag.get_distance=OK;	
		car_system.atx=0;
		car_system.aty=0;
		if(car_system.atx+1>car_system.chassis_dx&&car_system.atx-1<car_system.chassis_dx)
		{
			if(car_system.atx+1>car_system.chassis_dx&&car_system.atx-1<car_system.chassis_dx)
			{
				car_system.atx=0;
				car_system.aty=0;		
				car_system.Vtx=0;
				car_system.Vty=0;		
//				gpio_set_level(F_beer,GPIO_HIGH);
//				printf("Scattered_cirque\r\n");
				flap[0]=2;
				clean_dis();	
				gyroscope963ra.yaw=0;
			}
		}
	}
	if(flap[0]==2)
	{
		turn();
	}
	if(flap[0]==3)
	{
		go_to_coord();
	}
	if(flap[0]==4)
	{
//		if(flag.L_R_omega==L_O)
//		{
//			car_system.Vty=-30;
//			
//		}
//		else if(flag.L_R_omega==R_O)
//		{
//			car_system.Vty=30;
//		}
//		thwartwise(bin_image);
//		if(obj.y>=35&&obj.x>=30&&obj.y<=130)
//		{
			flap[0]=5;
//		}
	}
	if(flap[0]==5)
	{
		micro_distance();
	}
	if(flap[0]==6)
	{
		identify_card();
	}
	if(flap[0]==7)
	{
		get_card();
	}
	if(flap[0]==8)
	{
		if(flag.L_R_omega==L_O)
		{
			car_system.set_Omega=-90;
			new_omega=0;
		}
		else if(flag.L_R_omega==R_O)
		{
			car_system.set_Omega=90;
			new_omega=0;
		}
		turn();
	}
}

void road_element()
{
	if(flap[0]==0)
	{
		car_system.distance=0;
		flag.get_distance=NO;
		flag.keep_omega=NO;
//		judge_road();
	}
}

void cross_cirque()
{
	if(flap[0]==1)
	{
		flag.get_distance=OK;	
		car_system.atx=90;
		car_system.aty=0;
		if(car_system.atx+1>car_system.chassis_dx&&car_system.atx-1<car_system.chassis_dx)
		{
			if(car_system.atx+1>car_system.chassis_dx&&car_system.atx-1<car_system.chassis_dx)
			{
				car_system.atx=0;
				car_system.aty=0;		
				car_system.Vtx=0;
				car_system.Vty=0;	
//				gpio_set_level(F_beer,GPIO_HIGH);
				flap[0]=2;
				clean_dis();	
			}
		}
	}
	if(flap[0]==2)
	{
		gyroscope963ra.yaw=0;
		if(judge_cross_round_road_L_R()==L_C)
		{
			car_system.set_Omega=92;
			flap[0]=3;
		}
		else if(judge_cross_round_road_L_R()==R_C)
		{
			car_system.set_Omega=-92;
			flap[0]=3;
		}
	}
	if(flap[0]==3)
	{		
		turn();
	}
	if(flap[0]==4)
	{
		flag.keep_omega=NO;
		go_to_coord();
	}
	if(flap[0]==5)
	{
		micro_distance();
	}
	if(flap[0]==6)
	{
		identify_card();
		flag.objs=1;
	}
	if(flap[0]==7)
	{
		get_card();
	}
	if(flap[0]==8)
	{	
		go_to_coord();
	}
	if(flap[0]==9)
	{
		if(pic_flag.R_OR_L==L_C)
		{
			switch(turn_num)
			{
				case 0:car_system.set_Omega=-180;break;
				
				case 1:car_system.set_Omega=67.5;break;
				case 2:car_system.set_Omega=67.5;break;
				case 3:car_system.set_Omega=67.5;break;
				case 4:car_system.set_Omega=67.5;break;		
			}
		}
		else if(pic_flag.R_OR_L==R_C)
		{
			switch(turn_num)
			{
				case 0:car_system.set_Omega=180;break;
				
				case 1:car_system.set_Omega=-67.5;break;
				case 2:car_system.set_Omega=-67.5;break;
				case 3:car_system.set_Omega=-67.5;break;
				case 4:car_system.set_Omega=-67.5;break;		
			}
		}
		turn();
	}
	if(flap[0]==10)
	{
		go_to_coord();
	}
	if(flap[0]==11)
	{
		micro_distance();
	}
	if(flap[0]==12)
	{
		identify_num_word();
	}
	if(flap[0]==13)
	{
		go_to_coord();
	}
	if(flap[0]==14)
	{
		back_coord();
	}
	if(flap[0]==15)
	{
		if(pic_flag.R_OR_L==L_C)
		{
			if(flag.put_over==OK)
			{
				car_system.set_Omega=110;
			}
			else
				car_system.set_Omega=-95;
		}
		else if(pic_flag.R_OR_L==R_C)
		{
			if(flag.put_over==OK)
			{
				car_system.set_Omega=-110;
			}
			else
				car_system.set_Omega=95;
		}
//		printf("L_R:%d\tsetOmega:%f\tOmega:%f\r\n",flag.L_R_omega,car_system.set_Omega,car_system.Omega);		
		turn();
	}
	if(flap[0]==16)
	{
		put_card();
	}
	if(flap[0]==17)
	{
		flag.get_distance=OK;	
//		if(flag.objs==0)
//		{
//			car_system.atx=70;
//		}
//		else
//		{
//			
//		}
		switch(turn_num)
		{
			//**********************´ó*********************//
			case 0:car_system.atx=410;break;
			case 1:car_system.atx=340;break;
			case 2:car_system.atx=260;break;
			case 3:car_system.atx=160;break;
			case 4:car_system.atx=100;break;    
			//**********************Ð¡*********************//
//			case 0:car_system.atx=420;break;
//			case 1:car_system.atx=330;break;
//			case 2:car_system.atx=240;break;
//			case 3:car_system.atx=150;break;
//			case 4:car_system.atx=50;break;  			
		}
		car_system.aty=0;
		if(car_system.atx+1>car_system.chassis_dx&&car_system.atx-1<car_system.chassis_dx)
		{
				car_system.atx=0;
				car_system.aty=0;		
				gpio_set_level(F_beer,GPIO_HIGH);
				pic_flag.cross_all_flag=0;
				pic_flag.round_left_flag=0;
				pic_flag.round_right_flag=0;
				pic_flag.Scattered_card_flag=0;
				flag.cross_round_card_over=0;
				turn_num=0;
				flag.objs=0;
				clean_dis();
				flap[0]=0;
		}
	}
}

void clean_dis()
{
		car_system.at_distance=0;
		flag.get_distance=NO;
		for(uint8 n=0;n<4;n++)
		{
			wheel.distance[n]=0;
		}	
}

uint8 turn_num=0;
void go_to_coord()
{	
		static uint8 new_dis=0;
		static uint8 end_dis=0;
		flag.keep_omega=OK;
		flag.get_distance=OK;
		if(pic_flag.cross_all_flag!=0||pic_flag.round_left_flag!=0||pic_flag.round_right_flag!=0)
		{
			if(flap[0]==4)
			{
				car_system.atx=0;
				car_system.aty=0;
			}
			else if(flap[0]==8)
			{
				car_system.atx=35;
				car_system.aty=0;
				if(pic_flag.round_left_flag!=0||pic_flag.round_right_flag!=0)
				{
					car_system.atx=20;
				}
			}
			else if(flap[0]==10)
			{
				car_system.atx=52;
				car_system.aty=0;			
			}
			else if(flap[0]==13)
			{
				if(new_dis==0)
				{
					car_system.atx=car_system.chassis_dx-14;
					car_system.aty=car_system.chassis_dy-10;
					new_dis++;
				}
			}
		}
//		printf("car_system.atx:%f\tcar_system.chassis_dx:%f\r\n",car_system.atx,car_system.chassis_dx);
		if(pic_flag.Scattered_card_flag!=0)
		{
			if(flap[0]==3)
				car_system.atx=-5;
				car_system.aty=0;
		}
		
		if(pic_flag.endline_flag!=0)
		{
			if(flap[0]==1)
			{
				car_system.set_Omega=0;
				switch(end_dis)
				{
					case 0:car_system.atx=-0;car_system.aty=0;break;
					case 1:car_system.atx=-55;car_system.aty=0;break;
					case 2:car_system.atx=-55;car_system.aty=0;break;
//					case 3:car_system.at_distance=-30;break;
				}
			}
			if(flap[0]==13)
			{
				if(new_dis==0)
				{
					car_system.atx=car_system.chassis_dx-14;
					car_system.aty=car_system.chassis_dy-10;
					new_dis++;
				}
			}
				
		}
		
		if(pic_flag.ramp_flag!=0)
		{
				if(flap[0]==1)
				{
					car_system.atx=0;
					car_system.aty=-65;
				}
				if(flap[0]==2)
				{
					car_system.atx=150;
					car_system.aty=-60;
				}
				if(flap[0]==3)
				{
					car_system.atx=150;
					car_system.aty=-10;
				}
		}
		
		
		if(car_system.chassis_dx+1>car_system.atx&&car_system.chassis_dx-1<car_system.atx
			&&car_system.chassis_dy+1>car_system.aty&&car_system.aty>car_system.chassis_dy-1)
		{
			car_system.Vtx=0;
			car_system.Vty=0;		
			if((pic_flag.cross_all_flag!=0||pic_flag.round_left_flag!=0||pic_flag.round_right_flag!=0)
					&&pic_flag.Scattered_card_flag==0&&pic_flag.ramp_flag==0)
			{
				if(flap[0]==4)
				{
					flap[0]=5;
					clean_dis();
				}
				else if(flap[0]==8)
				{
					flap[0]=9;
					clean_dis();
				}			
				else if(flap[0]==10)
				{
					flap[0]=11;
				}
				else if(flap[0]==13)
				{
					flap[0]=16;
				}		
			}
			
			if(pic_flag.Scattered_card_flag!=0
				&&(pic_flag.cross_all_flag==0&&pic_flag.round_left_flag==0&&pic_flag.round_right_flag==0&&pic_flag.ramp_flag==0))
			{
				if(flap[0]==3)
					flap[0]=4;
				clean_dis();
			}
				
			if(pic_flag.endline_flag!=0)
			{
				if(flap[0]==1)
				{
					flap[0]=2;
					end_dis++;			
				}
				else if(flap[0]==13)
				{
					flap[0]=5;
				}
			}
			
			if(pic_flag.ramp_flag!=0)
			{
				if(flap[0]==1)
					flap[0]=2;
				else if(flap[0]==2)
					flap[0]=3;	
				else if(flap[0]==3)
				{
					flap[0]=0;
					pic_flag.ramp_flag=0;
					car_system.Vtx=55;
					clean_dis();
				}
			}
			flag.keep_omega=NO;		
			new_dis=0;
		}
}


void back_coord()
{
		flag.keep_omega=OK;
		flag.get_distance=OK;
		car_system.atx=0;
		car_system.aty=0;		
		if(flag.put_over==OK)
		{
			car_system.atx=20;
			car_system.aty=0;
		}
		if(car_system.chassis_dx+1>car_system.atx&&car_system.chassis_dx-1<car_system.atx
			&&car_system.chassis_dy+1>car_system.aty&&car_system.aty>car_system.chassis_dy-1)
		{
			if(car_system.chassis_dx+1>car_system.atx&&car_system.chassis_dx-1<car_system.atx
			&&car_system.chassis_dy+1>car_system.aty&&car_system.aty>car_system.chassis_dy-1)
			{
				car_system.Vtx=0;
				car_system.Vty=0;
				flap[0]=9;
				clean_dis();
				flag.keep_omega=NO;
				turn_num++;
				if(pic_flag.endline_flag!=0)
				{
					flap[0]=7;
				}
			}
		}	
}

uint16 ax=82,ay=87;
uint8 stime=0;
void micro_distance()
{
	ax=90,ay=91;
//	if(pic_flag.Scattered_card_flag!=0)
//	{
//		ax=84,ay=94;
//	}
	flag.keep_omega=OK;
	pid.Kp[7]=0.58;
	pid.Kp[8]=0.58;
	if(obj.y>0&&obj.y<=220)
	{	
		car_system.Vtx 	= PID_dis(7,(float)ay,(float)obj.y);
		car_system.Vty = PID_dis(8,(float)ax,(float)obj.x);
		if(obj.x<=ax+3&&obj.x>=ax-3&&obj.y<=ay+4&&obj.y>=ay-4)
		{
			system_delay_ms(75);
			if(obj.x<=ax+3&&obj.x>=ax-3&&obj.y<=ay+4&&obj.y>=ay-4)
			{
				flag.keep_omega=NO;
				car_system.Vtx = 0;
				car_system.Vty = 0;
				if(flap[0]==5)
				{
					flap[0]=6;
//					gpio_set_level(F_beer,GPIO_HIGH);
				}
				else if(flap[0]==11)
					flap[0]=12;
				
				if(pic_flag.Scattered_card_flag!=0)
				{
					if(flap[0]==5)
						flap[0]=6;
				}
				if(pic_flag.endline_flag!=0)
				{
					if(flap[0]==3)
						flap[0]=4;
				}
			}
		}
	}
	else if(obj.x==0&&obj.y==0&&flap[0]==11)
	{
		car_system.Vtx = 0;
		car_system.Vty = 0;
	}		
	else if(obj.num==0&&flag.put_over==OK)
	{
		if(pic_flag.endline_flag==0)
			flap[0]=15;
	}
	else if(obj.x==0&&obj.y==0&&time.micro_distance_time>=2)
	{
		if(flap[0]==5)
		{
			if(pic_flag.endline_flag==0)
				flap[0]=15;
		}
		if(pic_flag.Scattered_card_flag==OK)
		{
			if(pic_flag.endline_flag==0)
				flap[0]=8;
		}
	}
	else if(obj.x==0&&obj.y==0)
	{
		car_system.Vtx = 0;
		car_system.Vty = 0;
	}
}

void micro_distance_test()
{
	micro_distance();
}

uint16 label1=0;
void identify_num_word()
{
	obj.label=0;
	obj.label_flag=NO;
	uart_write_byte(UART_4,1);	
	system_delay_ms(200);
	uart_write_byte(UART_4,1);	
//	obj.event=1;
	if(obj.label_flag==OK&&obj.label!=0&&obj.event==1)
	{
		label1=obj.label;
		label_solution(obj.event,label1);
		uart_write_byte(UART_4,1);	
		obj.label=0;
		label1=0;
		obj.label_flag=NO;
	}
}

void identify_card()
{
	obj.label=0;
	obj.label_flag=NO;
	uart_write_byte(UART_4,2);
	system_delay_ms(200);
	uart_write_byte(UART_4,2);
	obj.event=2;
	if(obj.label_flag==OK&&obj.label!=0)
	{
		label1=obj.label;
		label_solution(obj.event,label1);
	  gyroscope963ra.yaw=0;
		flap[0]=7;	
		gpio_set_level(F_beer,GPIO_HIGH);
		uart_write_byte(UART_4,3);
		obj.label=0;
		label1=0;
		uart_write_byte(UART_4,3);
		obj.label_flag=NO;
	}
	else if(obj.x==0&&obj.y==0&&time.identify_card_time>1)
	{
		flap[0]=8;
		obj.label=0;
		label1=0;
		for(int8 n=5;n>=0;n--)
		{
			uart_write_byte(UART_4,1);
			printf("N:%d\tLabel:%d\r\n",n,frame1.frame_label[n]);
		}
	}
}

uint16 label_last;
void label_solution(uint8 event ,uint8 label)
{
	if(pic_flag.Scattered_card_flag==0)
	{
		if(pic_flag.endline_flag==0)
		{
			if(event==2&&label!=0)
			{
				obj.cross_label[obj.num]=label;
				frame1.frame_label[obj.num-1]=(uint16)label;
			}
			else if(event==1)
			{
				if(label!=0)
				{
	//				if(turn_num==0&&label<10)
	//				{
	//					label=label+10;
	//				}
					printf("label:%d\r\n",label-3);
					for(int8 n=5;n>=0;n--)
					{
						printf("N:%d\tLabel:%d\r\n",n,frame1.frame_label[n]);
						if(frame1.frame_label[n]!=0&&frame1.frame_label[n]==label-3)
						{
							label_last=label;
							frame1.at_frame=n;
							frame1.at_frame=n;
							flap[0]=13;break;
						}
						else if(n==0&&label!=0)
						{
							flap[0]=14;
							if(turn_num==4)
							{
								flap[0]=13;
								for(uint8 m=5;m>=0;m--)
								{
									if(frame1.frame_label[m]!=0)
									{
										printf("M:%d\tLabel:%d\r\n",m,frame1.frame_label[m]);
										frame1.at_frame=m;break;
									}
								}
							}
						}
					}
				}
			}
		}
		if(pic_flag.endline_flag!=0)
		{
			if(label!=0)
			{
				for(uint8 n=0;n<3;n++)
				{
					printf("n:%d,num:%d\r\n",n,frame1.Scattered_num[n]);
				}
				switch(label)
				{					
					case 1:if(frame1.Scattered_num[0]!=0)
									{
											frame1.at_frame=0;flap[0]=13;label_last=label;
									}
									else
										flap[0]=6;
									break;
					case 2:if(frame1.Scattered_num[1]!=0)
									{
											frame1.at_frame=2;flap[0]=13;label_last=label;
									}
									else
										flap[0]=6;
									break;
					case 3:if(frame1.Scattered_num[2]!=0)
									{
											frame1.at_frame=5;flap[0]=13;label_last=label;
									}
									else
										flap[0]=6;
									break;
					printf("label:%d,num:%d,at:%d\r\n",label_last,frame1.Scattered_num[label_last-1],frame1.at_frame);
				}
			}
		}
	}
	
	else if(pic_flag.Scattered_card_flag!=0)
	{
		if(event==2)
		{
			switch(label)
			{
				case 1:frame1.Scattered_num[0]++;obj.num=1;break;
				case 2:frame1.Scattered_num[0]++;obj.num=1;break;
				case 3:frame1.Scattered_num[0]++;obj.num=1;break;
				case 4:frame1.Scattered_num[0]++;obj.num=1;break;
				case 5:frame1.Scattered_num[0]++;obj.num=1;break;		
				
				case 6:frame1.Scattered_num[1]++;obj.num=3;break;	
				case 7:frame1.Scattered_num[1]++;obj.num=3;break;				
				case 8:frame1.Scattered_num[1]++;obj.num=3;break;				
				case 9:frame1.Scattered_num[1]++;obj.num=3;break;				
				case 10:frame1.Scattered_num[1]++;obj.num=3;break;	

				case 11:frame1.Scattered_num[2]++;obj.num=6;break;				
				case 12:frame1.Scattered_num[2]++;obj.num=6;break;				
				case 13:frame1.Scattered_num[2]++;obj.num=6;break;				
				case 14:frame1.Scattered_num[2]++;obj.num=6;break;				
				case 15:frame1.Scattered_num[2]++;obj.num=6;break;								
			}
			obj.Scattered_num++;
			printf("%d,%d,%d,%d\r\n",obj.Scattered_num,frame1.Scattered_num[0],frame1.Scattered_num[1],frame1.Scattered_num[2]);
		}
	}
	obj.label=NO;
	obj.event=NO;
	obj.label_flag=OK;
}


void get_card()
{
	car_system.set_Omega=0;
	servo_a_get();
	if(servo.flag[1]!=0)
	{
		flap[0]=6;
		obj.num++;
		if(obj.num>6)
		{
			flap[0]=8;
			obj.label=0;
			label1=0;
			for(int8 n=5;n>=0;n--)
			{
				uart_write_byte(UART_4,1);
				printf("N:%d\tLabel:%d\r\n",n,frame1.frame_label[n]);
			}
		}
		if(pic_flag.Scattered_card_flag!=0)
		{
			obj.num=1;
			flap[0]=8;

		}
		servo.flag[1]=0;
		servo.flag[0]=0;
	}
}

void put_card()
{
	car_system.Vtx=0;
	car_system.Vty=0;
//	gpio_set_level(F_beer,GPIO_HIGH);
	servo_a_put();
	
	if(servo.flag[1]!=0)
	{
		if((pic_flag.cross_all_flag!=0||pic_flag.round_left_flag!=0||pic_flag.round_right_flag!=0)&&pic_flag.endline_flag==0)
		{
			frame1.frame_label[frame1.at_frame]=0;
			obj.num--;
			for(int8 n=5;n>=0;n--)
			{
	//			printf("N:%d\tLabel:%d\r\n",n,frame1.frame_label[n]);
				if(frame1.frame_label[n]!=0&&frame1.frame_label[n]==label_last-3)
				{
					frame1.at_frame=n;
					flap[0]=16;break;
				}
				else if(n==0)
				{
					flap[0]=14;
					if(obj.num==1)
					{
						flap[0]=15;break;
					}
					else if(turn_num==4&&obj.num>1)
					{
	//					flap[0]=16;break;
						for(int8 m=5;m>=0;m--)
						{
							if(frame1.frame_label[m]!=0)
							{
								frame1.at_frame=m;
								flap[0]=16;break;
							}
						};break;
					}			
				}
			}
			if(obj.num==1)
			{
				label_last=0;
				flag.put_over=OK;
				flap[0]=15;
				obj.num=1;
			}
		}
		
		if(pic_flag.endline_flag!=0)
		{
			printf("label:%d,num:%d\r\n",label_last,frame1.Scattered_num[label_last]);
			if(obj.Scattered_num>0)
				obj.Scattered_num--;
			if(frame1.Scattered_num[label_last-1]>0)
				frame1.Scattered_num[label_last-1]--;
			if(frame1.Scattered_num[label_last-1]<=0)
			{
				label_last=0;
				flap[0]=6;
			}
		}
		servo.flag[1]=0;
		servo.flag[0]=0;
	}

}

void round_cirque()
{
	if(flap[0]==1)
	{
		flag.get_distance=OK;	
		car_system.atx=55;
		car_system.aty=0;
		if(car_system.atx+1>car_system.chassis_dx&&car_system.atx-1<car_system.chassis_dx)
		{
			if(car_system.atx+1>car_system.chassis_dx&&car_system.atx-1<car_system.chassis_dx)
			{
				car_system.atx=0;
				car_system.aty=0;		
				gpio_set_level(F_beer,GPIO_HIGH);
				flap[0]=2;
				clean_dis();	
			}
		}
	}
	if(flap[0]==2)
	{
		gyroscope963ra.yaw=0;
		if(judge_cross_round_road_L_R()==L_C)
		{
			car_system.set_Omega=86;
			flap[0]=3;
		}
		else if(judge_cross_round_road_L_R()==R_C)
		{
			car_system.set_Omega=-86;
			flap[0]=3;
		}
	}
	if(flap[0]==3)
	{		
		turn();
	}
	if(flap[0]==4)
	{
		flag.keep_omega=NO;
		go_to_coord();
	}
	if(flap[0]==5)
	{
		micro_distance();
	}
	if(flap[0]==6)
	{
		identify_card();
		flag.objs=1;
	}
	if(flap[0]==7)
	{
		get_card();
	}
	if(flap[0]==8)
	{	
		go_to_coord();
	}
	if(flap[0]==9)
	{
		if(pic_flag.R_OR_L==L_C)
		{
			switch(turn_num)
			{
				case 0:car_system.set_Omega=-90;break;
				
				case 1:car_system.set_Omega=60;break;
				case 2:car_system.set_Omega=60;break;
				case 3:car_system.set_Omega=60;break;
				case 4:car_system.set_Omega=90;break;		
			}
		}
		else if(pic_flag.R_OR_L==R_C)
		{
			switch(turn_num)
			{
				case 0:car_system.set_Omega=90;break;
				
				case 1:car_system.set_Omega=-60;break;
				case 2:car_system.set_Omega=-60;break;
				case 3:car_system.set_Omega=-60;break;
				case 4:car_system.set_Omega=-90;break;		
			}
		}
		turn();
	}
	if(flap[0]==10)
	{
		go_to_coord();
	}
	if(flap[0]==11)
	{
		micro_distance();
	}
	if(flap[0]==12)
	{
		identify_num_word();
	}
	if(flap[0]==13)
	{
		go_to_coord();
	}
	if(flap[0]==14)
	{
		back_coord();
	}
	if(flap[0]==15)
	{
		if(pic_flag.R_OR_L==L_C)
		{
			if(flag.put_over==OK)
			{
				car_system.set_Omega=90;
			}
			else
				car_system.set_Omega=-100;
		}
		else if(pic_flag.R_OR_L==R_C)
		{
			if(flag.put_over==OK)
			{
				car_system.set_Omega=-90;
			}
			else
				car_system.set_Omega=100;
		}
//		printf("L_R:%d\tsetOmega:%f\tOmega:%f\r\n",flag.L_R_omega,car_system.set_Omega,car_system.Omega);		
		turn();
	}
	if(flap[0]==16)
	{
		put_card();
	}
	if(flap[0]==17)
	{
		flag.get_distance=OK;	
		if(flag.objs==0)
		{
			car_system.atx=70;
		}
		else
		{
			switch(turn_num)
			{
				case 0:car_system.atx=230;break;
				case 1:car_system.atx=190;break;
				case 2:car_system.atx=150;break;
				case 3:car_system.atx=120;break;
				case 4:car_system.atx=70;break;
			}
		}
		car_system.aty=0;
		if(car_system.atx+1>car_system.chassis_dx&&car_system.atx-1<car_system.chassis_dx)
		{
			if(car_system.atx+1>car_system.chassis_dx&&car_system.atx-1<car_system.chassis_dx)
			{
				car_system.atx=0;
				car_system.aty=0;		
				gpio_set_level(F_beer,GPIO_HIGH);
				pic_flag.cross_all_flag=0;
				pic_flag.round_left_flag=0;
				pic_flag.round_right_flag=0;
				pic_flag.Scattered_card_flag=0;
				flag.cross_round_card_over=0;
				turn_num=0;
				flag.objs=0;
				clean_dis();
				flap[0]=0;
				flap[0]=0;
				clean_dis();	
			}
		}
	}
}