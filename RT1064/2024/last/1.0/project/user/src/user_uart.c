#include "user_uart.h"

void user_uart_init()
{
	uart_init(UART_8,115200,UART8_TX_D16,UART8_RX_D17);				// 初始化串口8 波特率115200 发送引脚使用D16 接收引脚使用D17 【用于与上位机通信】
	uart_rx_interrupt(UART_8,6);
}


uint8 uart8_data;
void uart8_rx_interrupt_handler (void)
{ 
	uart_query_byte(UART_8,&uart8_data);
	uart8_Rece_Prepare(uart8_data);
}


/*【联合体，用来接收浮点数的，可使用这个通过上位机（串口助手）发送pid参数，并储存在flash中调用】*/
union Wheel_K_data
{
	uint8 K[4];
	float KP;
};
union Wheel_K_data Wheel_K_data;

union Wheel_I_data
{
	uint8 I[4];
	float KI;
};
union Wheel_I_data Wheel_I_data;


uint8 uart8_send_buf[50],uart8_receive_buf[50];
void uart8_Rece_Prepare(uint8 data)
{
	static uint8 _data_len=0;
	static uint8 state=0;
	static uint8 F_cnt=0;
   
    switch(state)
        {
        case 0:
            if(data==0xAA)                            //帧头
            {
                state=1;
                uart8_receive_buf[0]=data;

            }else state = 0;
            break;
        case 1:
            if(data==0x29||data==0x30)                            //id
            {
                state=2;
                uart8_receive_buf[1]=data;

            }else state = 0;
            break;
        case 2:
            if(data==0x05||data==0xa4)                            //功能码
            {
                state=3;
                uart8_receive_buf[2]=data;

            }else state = 0;
            break;
        case 3:                                      
             if(data<50)     //有效数据包最大长度20
            {
                state=4;
                uart8_receive_buf[3]=data;                    //数据长度
                _data_len=data;
                F_cnt = 0;
            }else state = 0;
            break;
        case 4:
            if(_data_len>0)
            {                      
                _data_len--;
                uart8_receive_buf[4+F_cnt++]=data;
                if(_data_len==0)    state = 5;
            }else state = 0;   
            break;
   
        case 5:
            state = 0;            
                uart8_receive_buf[4+F_cnt++]=data;
                uart8_receive_buf[4+F_cnt++]='\n';
				
				
				
							/*【接收数据的代码写这里】*/
										
				
                for (uint8 i = 0; i < 50; i++)   
                    uart8_receive_buf[i] = 0;   
            break; 
        default:    state = 0;  
            break;  
    } 
}  

uint8 BUFF[50];
/*
 匿名v7通信协议：
 入口值：需要发送的数据
 返回值：无
*/
void ano7(int16 data1,int16 data2,int16 data3,int16 data4)
{
	int i;
	uint8 F_sumcheck=0;
	uint8 F_addcheck=0;
	uint8 F_cnt=0;
	BUFF[F_cnt++]=0xAA;//帧头
	BUFF[F_cnt++]=0xFF;//目标地址
	BUFF[F_cnt++]=0XF1;//功能码
	BUFF[F_cnt++]=8;//数据长度
	BUFF[F_cnt++]=F_byte0(data1);//数据内容,小段模式，低位在前
	BUFF[F_cnt++]=F_byte1(data1);//需要将字节进行拆分，调用上面的宏定义即可。
	BUFF[F_cnt++]=F_byte0(data2);
	BUFF[F_cnt++]=F_byte1(data2);	
	BUFF[F_cnt++]=F_byte0(data3);
	BUFF[F_cnt++]=F_byte1(data3);
	BUFF[F_cnt++]=F_byte0(data4);
	BUFF[F_cnt++]=F_byte1(data4);
  BUFF[3] = F_cnt-4;
  for(i=0;i<BUFF[3]+4;i++) 
	{
		F_sumcheck+=BUFF[i];
		F_addcheck+=F_sumcheck;
	}
  BUFF[F_cnt++]=F_sumcheck;	
	BUFF[F_cnt++]=F_addcheck;	
  uart_write_buffer(UART_8,BUFF,F_cnt);
}


uint8 BUFFS[50];
void put_angle(uint8 even,uint16 servo1PWM,uint16 servo2PWM,uint16 servo3PWM,uint16 servo4PWM,uint16 servo5PWM)
{
	int i;
	uint8 F_sumcheck=0;
	uint8 F_addcheck=0;
	uint8 F_cnt=0;
	BUFFS[F_cnt++]=0xAA;//帧头
	BUFFS[F_cnt++]=0x30;//目标地址
	BUFFS[F_cnt++]=even;//功能码
	BUFFS[F_cnt++]=10;//数据长度
	BUFFS[F_cnt++]=F_byte0(servo1PWM);//数据内容,小段模式，低位在前
	BUFFS[F_cnt++]=F_byte1(servo1PWM);//需要将字节进行拆分，调用上面的宏定义即可。
	BUFFS[F_cnt++]=F_byte0(servo2PWM);
	BUFFS[F_cnt++]=F_byte1(servo2PWM);	
	BUFFS[F_cnt++]=F_byte0(servo3PWM);
	BUFFS[F_cnt++]=F_byte1(servo3PWM);
	BUFFS[F_cnt++]=F_byte0(servo4PWM);
	BUFFS[F_cnt++]=F_byte1(servo4PWM);
	BUFFS[F_cnt++]=F_byte0(servo5PWM);
	BUFFS[F_cnt++]=F_byte1(servo5PWM);
  BUFFS[3] = F_cnt-4;
  for(i=0;i<BUFFS[3]+4;i++) 
	{
		F_sumcheck+=BUFFS[i];
		F_addcheck+=F_sumcheck;
	}
  BUFFS[F_cnt++]=F_sumcheck;	
	BUFFS[F_cnt++]=F_addcheck;	
	uart_write_buffer(UART_8,BUFFS,F_cnt);
}
