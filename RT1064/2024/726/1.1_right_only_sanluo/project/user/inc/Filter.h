#ifndef __FILTER_H
#define __FILTER_H

#include "zf_common_headfile.h"

struct RC_Para
{
    float temp;  //Ôİ´æÖµ,´æ´¢RC_baro
    float value; //ÂË²¨Öµ
    float RC;    //µÍÍ¨ÂË²¨²ÎÊı
};
typedef struct RC_Para *RC_Filter_pt;

float lowV(float com,float iLastData,float dPower);
float averageV(float gyrodata);
float rcHpFiter(float val,float k);
float RCFilter(float value,RC_Filter_pt Filter);
float Sliding_Window_Filtering(int data_channel, float data_stream);
float Low_Pass_Filter(int data_channel, float data_stream);


#endif
