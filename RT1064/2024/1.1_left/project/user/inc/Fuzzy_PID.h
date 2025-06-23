#ifndef __FUZZY_PID_H
#define __FUZZY_PID_H

#include "user_include.h"


#define FUZZY_SEG_NUMS 7   //7个模糊子集
void Fuzzy_init(void);
void PID_control(uint8 wheel);


#endif
