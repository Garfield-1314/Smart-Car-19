#ifndef __FUZZY_H
#define __FUZZY_H

#include "user.h"

#define FUZZY_SEG_NUMS 7   //7��ģ���Ӽ�
void Fuzzy2_init(void);
void fuzzification(float val, float max, float* percent);  //ģ����
void fuzzy_rule(const float *percent_e, const float* percent_ec, const uint8_t rule[FUZZY_SEG_NUMS][FUZZY_SEG_NUMS], float* percent_out);  //ģ�������ӳ��
float de_fuzzification(float max, float* percent);  //ȥģ����
void PID_control(uint8 wheel);
#endif