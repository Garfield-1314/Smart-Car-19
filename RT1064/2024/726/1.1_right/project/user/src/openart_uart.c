#include "openart_uart.h"

void openart1_uart_init()
{
	uart_init(UART_1,115200,UART1_TX_B12,UART1_RX_B13);       // 初始化串口1 波特率115200 发送引脚使用B12 接收引脚使用B13 【用于与openart1通信】
	uart_rx_interrupt(UART_1,1);  
}

void MXC_uart_init()
{
	uart_init(UART_1,115200,UART1_TX_B12,UART1_RX_B13);       // 初始化串口1 波特率115200 发送引脚使用B12 接收引脚使用B13 【用于与openart1通信】
	uart_rx_interrupt(UART_1,1);  
}

uint8 openart1_uart_data;
void openart1_uart_rx_interrupt_handler(void)
{ 
	uart_query_byte(UART_1,&openart1_uart_data);
	openart1_uart_Rece_Prepare(openart1_uart_data);
}

uint8 MCX_uart_data;
void MCX_uart_rx_interrupt_handler(void)
{
	uart_query_byte(UART_1,&MCX_uart_data);
	MCX_uart_Rece_Prepare(MCX_uart_data);
}

OBJ obj;
uint8 MXC_send_buf[20],MXC_uart_receive_buf[20];
void MCX_uart_Rece_Prepare (uint8 data)
{ 
	static uint8 state=0;
  
	    switch(state)
     {
        case 0:
            if(data==0XAA)                            //帧头
            {
                state=1;
                MXC_uart_receive_buf[0]=data;
            }else state = 0;
            break;
						
        case 1:MXC_uart_receive_buf[1]=data;state=2;break;
			
				case 2:MXC_uart_receive_buf[2]=data;state=3;break;
								
				case 3:MXC_uart_receive_buf[3]=data;state=4;
						if(MXC_uart_receive_buf[1]==0)
						{
							obj.x0=MXC_uart_receive_buf[2];break;
						}else state=0; break;
								
				case 4:MXC_uart_receive_buf[4]=data;state=5;break;
								
				case 5:MXC_uart_receive_buf[5]=data;state=6;
						if(MXC_uart_receive_buf[1]==0)
						{
							obj.y0=MXC_uart_receive_buf[4];break;
						}else state=0;break;
								
				case 6:MXC_uart_receive_buf[6]=data;state=7;
						if(MXC_uart_receive_buf[1]==0)
						{
							obj.x1=MXC_uart_receive_buf[6];break;
						}else state=0;break;
					
				case 7:MXC_uart_receive_buf[7]=data;state=8;break;

						
				case 8:MXC_uart_receive_buf[8]=data;state=9;
						if(MXC_uart_receive_buf[1]==0)
						{
							obj.y1=MXC_uart_receive_buf[8];break;
						}else state=0;break;
						
				case 9:MXC_uart_receive_buf[9]=data;state=10;break;
						
				case 10:MXC_uart_receive_buf[10]=data;state=11;
						obj.x=(obj.x1+obj.x0)/2;
						obj.y=(obj.y1+obj.y0)/2;
						obj.c=(obj.x1-obj.x0)*2+(obj.y1-obj.y0)*2;
					for(uint8 i=0;i<11;i++)
					{
						MXC_uart_receive_buf[i]=0;
					}break;
        default:    state = 0;  
            break;  
    } 
}


uint16 color[2];
uint8 openart1_send_buf[20],openart1_uart_receive_buf[20];
void openart1_uart_Rece_Prepare(uint8 data)
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
                openart1_uart_receive_buf[0]=data;

            }else state = 0;
            break;
        case 1:
            if(data==0x29||data==0x30)                            //id
            {
                state=2;
                openart1_uart_receive_buf[1]=data;

            }else state = 0;
            break;
        case 2:
            if(data==0x05||data==0xa4)                            //功能码
            {
                state=3;
                openart1_uart_receive_buf[2]=data;

            }else state = 0;
            break;
        case 3:                                      
             if(data<20)     //有效数据包最大长度50
            {
                state=4;
                openart1_uart_receive_buf[3]=data;                    //数据长度
                _data_len=data;
                F_cnt = 0;
            }else state = 0;
            break;
        case 4:
            if(_data_len>0)
            {                      
                _data_len--;
                openart1_uart_receive_buf[4+F_cnt++]=data;
                if(_data_len==0)    state = 5;
            }else state = 0;   
            break;
   
        case 5:
            state = 0;            
                openart1_uart_receive_buf[4+F_cnt++]=data;
                openart1_uart_receive_buf[4+F_cnt++]='\n';
				
//						/*【接收数据的代码写这里】*/
//				QRnum[0]=(uint16)openart1_uart_receive_buf[4];
//						color[0]=(uint16)openart1_uart_receive_buf[4];
//						rcx=(uint16)openart1_uart_receive_buf[5];
//						rcy=(uint16)openart1_uart_receive_buf[6];
				
                for (uint8 i = 0; i < 10; i++)   
                    openart1_uart_receive_buf[i] = 0;   
            break; 
        default:    state = 0;  
            break;  
    } 
}  


void openart2_uart_init()
{
	uart_init(UART_4,115200,UART4_TX_C16,UART4_RX_C17);				// 初始化串口4 波特率115200 发送引脚使用C16 接收引脚使用C17 【用于与上位机通信】
	uart_rx_interrupt(UART_4,4);  
}

uint8 openart2_uart_data;
void openart2_uart_rx_interrupt_handler(void)
{ 
	uart_query_byte(UART_4,&openart2_uart_data);
	openart2_uart_Rece_Prepare(openart2_uart_data);
}

uint16 m1,m2;
uint8 openart2_send_buf[20],openart2_uart_receive_buf[20];
void openart2_uart_Rece_Prepare(uint8 data)
{
	static uint8 num=0;
	static uint8 _data_len=0;
	static uint8 state=0;
	static uint8 F_cnt=0;
//  obj.label_flag=NO;
    switch(state)
        {
        case 0:
            if(data==0xAA)                            //帧头
            {
                state=1;
                openart2_uart_receive_buf[0]=data;

            }else state = 0;
            break;
        case 1:
            if(data==0x29||data==0x30)                            //id
            {
                state=2;
                openart2_uart_receive_buf[1]=data;

            }else state = 0;
            break;
        case 2:
            if(data==0x05||data==0xa4)                            //功能码
            {
                state=3;
                openart2_uart_receive_buf[2]=data;

            }else state = 0;
            break;
        case 3:                                      
             if(data<50)     //有效数据包最大长度50
            {
                state=4;
                openart2_uart_receive_buf[3]=data;                    //数据长度
                _data_len=data;
                F_cnt = 0;
            }else state = 0;
            break;
        case 4:
            if(_data_len>0)
            {                      
                _data_len--;
                openart2_uart_receive_buf[4+F_cnt++]=data;
                if(_data_len==0)    state = 5;
            }else state = 0;   
            break;
   
        case 5:
            state = 0;            
                openart2_uart_receive_buf[4+F_cnt++]=data;
                openart2_uart_receive_buf[4+F_cnt++]='\n';
							
							/*【接收数据的代码写这里】*/
								obj.event=(uint16)openart2_uart_receive_buf[4];
								m1=(uint16)openart2_uart_receive_buf[5];
								m2=(uint16)openart2_uart_receive_buf[6];
								num++;
								if(num==2)
								{
									obj.label=m1+m2;
									obj.label_flag=OK;
									num=0;
								}
                for (uint8 i = 0; i < 20; i++)   
                    openart2_uart_receive_buf[i] = 0;   
            break; 
        default:    state = 0;  
            break;  
    } 
}  