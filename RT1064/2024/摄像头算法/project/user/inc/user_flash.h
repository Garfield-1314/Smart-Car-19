#ifndef __USER_FLASH_H
#define __USER_FLASH_H

#include "user.h"

//void flash_text(void);
void PID_flash_updata(uint8 wheel,float KP,float KI);
void read_pid_data(void);
#endif