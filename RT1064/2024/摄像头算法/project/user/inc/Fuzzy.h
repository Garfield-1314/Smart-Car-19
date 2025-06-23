#ifndef __FUZZY_H
#define __FUZZY_H

#include "user.h"

#define FUZZY_SEG_NUMS 7   //7个模糊子集
void Fuzzy2_init(void);
void fuzzification(float val, float max, float* percent);  //模糊化
void fuzzy_rule(const float *percent_e, const float* percent_ec, const uint8_t rule[FUZZY_SEG_NUMS][FUZZY_SEG_NUMS], float* percent_out);  //模糊规则表映射
float de_fuzzification(float max, float* percent);  //去模糊化
void PID_control(uint8 wheel);
#endif