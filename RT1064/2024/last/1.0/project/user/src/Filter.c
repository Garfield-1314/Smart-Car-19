#include "Filter.h"

/**********************************************/
//ƽ��ֵ�˲�
/**********************************************/
float data_sum[12];
float averageV(float gyrodata)
{
	float sum = 0;
	for(int i=0; i<11; i++)
	{
		data_sum[i]=data_sum[i+1];
		sum = sum + data_sum[i];
	}
	data_sum[11] = gyrodata;
	sum = sum + data_sum[11];
	
	return(sum/12);
}


/**********************************************/
//rc��ͨ�˲����ɹ��˸�Ƶ�ź�
/**********************************************/

float lastVal;//�ϴμ���ֵ
float rcHpFiter(float val,float k)
{
    lastVal=((float)val*k+lastVal*(1-k));
    //    return -(val-rcPara->lVal);//�˲����
    //return -(val-lVal);//���ֱ�ӷ����˲�������˲���ͼ���ǵ�ת�ģ����ĵ�ͼ��һЩ���ϣ���Ҫ��ͼ���پ������
	return lastVal;
}
 
/**********************************************/
//RC��ͨ�˲����ɹ��˵�Ƶ�ź�
/**********************************************/
float RCFilter(float value,RC_Filter_pt Filter)
{
    Filter->temp = value;
    Filter->value = (1 - Filter->RC) * Filter->value + Filter->RC * Filter->temp;
//	temp = RC * value + (1 - RC) * temp;
    return Filter->value;
}


float lowV(float com,float iLastData,float dPower)
{    
    float iData;                             
    iData = ( com * dPower ) + ( 1 - dPower ) * iLastData; //����
    iLastData = iData;                                     //������������
    return iData;                                         //��������
}

// **************************************
// ????
// **************************************
#define Window_Size 8
#define Channel_Number 1
float Sliding_Window_Filtering(int data_channel, float data_stream)
{
		
	data_channel = data_channel -1;
	
	/* ???????? */
	static float Filter_Window[Channel_Number][Window_Size] = {0};
	
	/* ?????????? */
	for(int i = 0; i < Window_Size-1; i++){
		Filter_Window[data_channel][i] = Filter_Window[data_channel][i+1];	// ?????
	}
	Filter_Window[data_channel][Window_Size-1] = data_stream;	// ?????

	/* ?????? */
	float Sum = 0;
	for(int i = 0; i < Window_Size; i++){
		Sum += Filter_Window[data_channel][i];
	}
	
	/* ??????? */
	return Sum / Window_Size;
}

// **************************************
// ????
// **************************************
const float fc = 1.0f;    //????
const float Ts = 0.001f;    //????
const float pi = 3.14159f;  //p
float alpha =(2.0 * pi * fc * Ts) / (2.0 * pi * fc * Ts + 1);     //????

float Low_Pass_Filter(int data_channel, float data_stream)
{
  static float out_last[Channel_Number] = {0}; //??????
  float out;
	
	data_channel = data_channel -1;

  /***************** ???????,?? out_last ?? ******************/
  static char fisrt_flag = 1;
  if (fisrt_flag == 1)
  {
    fisrt_flag = 0;
    out_last[data_channel] = data_stream;
  }

  /*************************** ???? *********************************/
  out = out_last[data_channel] + alpha * (data_stream - out_last[data_channel]);
  out_last[data_channel] = out;

  return out;
}
