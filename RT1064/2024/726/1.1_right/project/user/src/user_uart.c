#include "user_uart.h"

void user_uart_init()
{
	uart_init(UART_8,115200,UART8_TX_D16,UART8_RX_D17);				// ��ʼ������8 ������115200 ��������ʹ��D16 ��������ʹ��D17 ����������λ��ͨ�š�
	uart_rx_interrupt(UART_8,6);
}


uint8 uart8_data;
void uart8_rx_interrupt_handler (void)
{ 
	uart_query_byte(UART_8,&uart8_data);
	uart8_Rece_Prepare(uart8_data);
}


/*�������壬�������ո������ģ���ʹ�����ͨ����λ�����������֣�����pid��������������flash�е��á�*/
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
            if(data==0xAA)                            //֡ͷ
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
            if(data==0x05||data==0xa4)                            //������
            {
                state=3;
                uart8_receive_buf[2]=data;

            }else state = 0;
            break;
        case 3:                                      
             if(data<50)     //��Ч���ݰ���󳤶�20
            {
                state=4;
                uart8_receive_buf[3]=data;                    //���ݳ���
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
				
				
				
							/*���������ݵĴ���д���*/
										
				
                for (uint8 i = 0; i < 50; i++)   
                    uart8_receive_buf[i] = 0;   
            break; 
        default:    state = 0;  
            break;  
    } 
}  

uint8 BUFF[50];
/*
 ����v7ͨ��Э�飺
 ���ֵ����Ҫ���͵�����
 ����ֵ����
*/
void ano7(int16 data1,int16 data2,int16 data3,int16 data4)
{
	int i;
	uint8 F_sumcheck=0;
	uint8 F_addcheck=0;
	uint8 F_cnt=0;
	BUFF[F_cnt++]=0xAA;//֡ͷ
	BUFF[F_cnt++]=0xFF;//Ŀ���ַ
	BUFF[F_cnt++]=0XF1;//������
	BUFF[F_cnt++]=8;//���ݳ���
	BUFF[F_cnt++]=F_byte0(data1);//��������,С��ģʽ����λ��ǰ
	BUFF[F_cnt++]=F_byte1(data1);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
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
	BUFFS[F_cnt++]=0xAA;//֡ͷ
	BUFFS[F_cnt++]=0x30;//Ŀ���ַ
	BUFFS[F_cnt++]=even;//������
	BUFFS[F_cnt++]=10;//���ݳ���
	BUFFS[F_cnt++]=F_byte0(servo1PWM);//��������,С��ģʽ����λ��ǰ
	BUFFS[F_cnt++]=F_byte1(servo1PWM);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
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
