#include "user_flash.h"

#define PID_FLASH_FAN    (126)
#define WHEEL_FLASH_PAGE	 (FLASH_PAGE_0)

void PID_flash_updata(uint8 wheel,float KP,float KI)
{
	if(KP>0&&KI>0&&wheel>=10)
	{
		//flash_buffer_clear();
		wheel=wheel-10;
		switch(wheel)
		{
			case 0:flash_union_buffer[0].float_type=KP;flash_union_buffer[1].float_type=KI;break;
			case 1:flash_union_buffer[2].float_type=KP;flash_union_buffer[3].float_type=KI;break;
			case 2:flash_union_buffer[4].float_type=KP;flash_union_buffer[5].float_type=KI;break;
			case 3:flash_union_buffer[6].float_type=KP;flash_union_buffer[7].float_type=KI;break;
		}
		flash_write_page_from_buffer(PID_FLASH_FAN, WHEEL_FLASH_PAGE);
		KP=0;
		KI=0;
	}
}

void read_pid_data()
{
		flash_buffer_clear();
		flash_read_page_to_buffer(126,0);   
		printf("wheel=%d\tKP=%f\tKI=%f\r\n",0,flash_union_buffer[0].float_type,flash_union_buffer[1].float_type);
		printf("wheel=%d\tKP=%f\tKI=%f\r\n",1,flash_union_buffer[2].float_type,flash_union_buffer[3].float_type);
		printf("wheel=%d\tKP=%f\tKI=%f\r\n",2,flash_union_buffer[4].float_type,flash_union_buffer[5].float_type);
		printf("wheel=%d\tKP=%f\tKI=%f\r\n",3,flash_union_buffer[6].float_type,flash_union_buffer[7].float_type);
	  
}
