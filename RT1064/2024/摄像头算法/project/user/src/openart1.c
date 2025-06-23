#include "openart1.h"

PICTURE picture;

void openart1_uart_init()
{
	uart_init(UART_1,115200,UART1_TX_B12,UART1_RX_B13);       // ��ʼ������1 ������115200 ��������ʹ��B12 ��������ʹ��B13 ��������openart1ͨ�š�
	uart_rx_interrupt(UART_1,1);  
}

uint8 openart1_uart_data;
void openart1_uart_rx_interrupt_handler (void)
{ 
	uart_query_byte(UART_1,&openart1_uart_data);
	openart1_uart_Rece_Prepare(openart1_uart_data);
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
            if(data==0xAA)                            //֡ͷ
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
            if(data==0x05||data==0xa4)                            //������
            {
                state=3;
                openart1_uart_receive_buf[2]=data;

            }else state = 0;
            break;
        case 3:                                      
             if(data<20)     //��Ч���ݰ���󳤶�50
            {
                state=4;
                openart1_uart_receive_buf[3]=data;                    //���ݳ���
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
				
//						/*���������ݵĴ���д���*/
//				QRnum[0]=(uint16)openart1_uart_receive_buf[4];
						color[0]=(uint16)openart1_uart_receive_buf[4];
						rcx=(uint16)openart1_uart_receive_buf[5];
						rcy=(uint16)openart1_uart_receive_buf[6];
				
                for (uint8 i = 0; i < 10; i++)   
                    openart1_uart_receive_buf[i] = 0;   
            break; 
        default:    state = 0;  
            break;  
    } 
}  