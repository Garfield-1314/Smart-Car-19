/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
*  
* RT1064DVL6A ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"

// ���µĹ��̻��߹����ƶ���λ�����ִ�����²���
// ��һ�� �ر��������д򿪵��ļ�
// �ڶ��� project->clean  �ȴ��·�����������

// �������ǿ�Դ����ֲ�ÿչ���

#include "user_include.h"

void flag_init()
{
	flag.keep_omega=NO;
	obj.num=1;
	printf("flap��%d\tobj.num:%d\r\n",flap[0],obj.num);		
}

int main(void)
{
    clock_init(SYSTEM_CLOCK_600M);  //����ɾ��
    debug_init();                   //���Զ˿ڳ�ʼ��
		system_delay_ms(500);
	
	  user_system_init();
    // �˴���д�û����� ���������ʼ�������
    
//	motor_text();
    // �˴���д�û����� ���������ʼ�������
		car_system.Vtx=60;
		flag_init();
//	servo.pwm[3]=frame1.frame_pwm[5];
//		frame_test();
    while(1)
    {
//			servo_a_put();
			read_key();
//			
			tft180_show_uint(0,65,obj.x,3);tft180_show_uint(40,64,obj.y,3);tft180_show_uint(80,64,obj.c,3);
			tft180_show_uint(80,84,time.sys_time,3);
			tft180_show_uint(80,120,obj.label-3,3);

			event();	
//			
    }
}



