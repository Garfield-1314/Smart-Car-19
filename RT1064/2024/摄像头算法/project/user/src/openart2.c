#include "openart2.h"

void openart2_uart_init()
{
	uart_init(UART_4,115200,UART4_TX_C16,UART4_RX_C17);				// ��ʼ������4 ������115200 ��������ʹ��C16 ��������ʹ��C17 ����������λ��ͨ�š�
	uart_rx_interrupt(UART_4,4);  
}

uint8 openart2_uart_data;
void openart2_uart_rx_interrupt_handler(void)
{ 
	uart_query_byte(UART_4,&openart2_uart_data);
	openart2_uart_Rece_Prepare(openart2_uart_data);
}

uint8 openart2_send_buf[50],openart2_uart_receive_buf[50];
void openart2_uart_Rece_Prepare(uint8 data)
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
            if(data==0x05||data==0xa4)                            //������
            {
                state=3;
                openart2_uart_receive_buf[2]=data;

            }else state = 0;
            break;
        case 3:                                      
             if(data<50)     //��Ч���ݰ���󳤶�50
            {
                state=4;
                openart2_uart_receive_buf[3]=data;                    //���ݳ���
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
				
				
				
				
							/*���������ݵĴ���д���*/

				
                for (uint8 i = 0; i < 50; i++)   
                    openart2_uart_receive_buf[i] = 0;   
            break; 
        default:    state = 0;  
            break;  
    } 
}  