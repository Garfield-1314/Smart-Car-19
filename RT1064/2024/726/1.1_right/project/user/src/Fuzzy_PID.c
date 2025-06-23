#include "Fuzzy_PID.h"

/************************************************************************
 * @brief 模糊pid（自适应pid）
 * @note  NULL
 *
 * @param 
 * @param 
 * @return  
 *
 *************************************************************************/



//#define FUZZY_SEG_NUMS 7   //7个模糊子集
 
// NB NM NS ZO PS PM PB
// 0  1  2  3  4  5  6
 
fuzzy_pid_st fuzzy_t;
 
void Fuzzy_init()
{
	fuzzy_t.max_e=200;
	fuzzy_t.max_ec=400;
	fuzzy_t.max_kp=10;
	fuzzy_t.max_ki=5;
	fuzzy_t.max_kd=0;
	
	uint8 NB=0,NM=1,NS=2,ZO=3,PS=4,PM=5,PB=6;
	uint8  Kp_rule_list[7][7] = { {PB,PB,PB,PM,PM,ZO,ZO},        //kp规则表
																{PB,PB,PB,PM,PS,ZO,ZO},
																{PB,PM,PM,PS,ZO,NS,NM},
																{PM,PM,PS,ZO,NS,NM,NM},
																{PS,PS,ZO,NS,NM,NM,NM},
																{ZO,ZO,NS,NM,NM,NB,NB},
																{ZO,ZO,NS,NM,NB,NB,NB} };

	uint8  Ki_rule_list[7][7] = { {NB,NB,NM,NM,NS,ZO,ZO},     //ki规则表
																{NB,NM,NM,NS,NS,ZO,ZO},
																{NB,NM,NS,NS,ZO,PS,PS},
																{NM,NM,NS,ZO,PS,PS,PM},
																{NM,NS,ZO,PS,PS,PM,PB},
																{ZO,ZO,PS,PM,PM,PB,PB},
																{ZO,ZO,PS,PM,PM,PB,PB} };
	
	uint8  Kd_rule_list[7][7] = { {PS,NS,NS,NB,NB,NM,PS},     //kd规则表
																{PS,NS,NB,NM,NM,NS,ZO},
																{ZO,NS,NS,NM,NM,NS,ZO},
																{ZO,NS,NM,NS,NS,NS,ZO},
																{ZO,ZO,ZO,ZO,ZO,ZO,ZO},
																{PB,NS,PS,PS,PS,PS,PB},
																{PB,PB,PM,PM,PS,PS,PB} };
	for(uint8 i=0;i<FUZZY_SEG_NUMS;i++)
	{
		for(uint8 n=0;n<FUZZY_SEG_NUMS;n++)
		{
			fuzzy_t.rule_kp[i][n]=Kp_rule_list[i][n];
			fuzzy_t.rule_ki[i][n]=Ki_rule_list[i][n];
			fuzzy_t.rule_kd[i][n]=Kd_rule_list[i][n];
		}
	}
	
	fuzzy_t.FUZZY_USED=OK;
	
}
/************************************************************************
 * @brief 模糊化
 * @note  NULL
 *
 * @param val  输入变量
 * @param max  输入变量的基本论域为 [-max,max]
 * @return  percent 变量的模糊占比
 *
 *************************************************************************/
void fuzzification(float val, float max, float* percent)  //模糊化
{
    float interval[FUZZY_SEG_NUMS];
 
    float seg_len = 2 * max / (FUZZY_SEG_NUMS - 1);
    for (int i = 0; i < FUZZY_SEG_NUMS; i++)
    {
        percent[i] = 0;                    // percent赋初值
        interval[i] = -max + i * seg_len;  //分段点的值 NB NM NS ZO PS PM PB 的值
    }
    if (val <= interval[0])  // <= 0
    {
        percent[0] = 1;
        return;
    }
    else if (val <= interval[1])  //  [0,1]
    {
        percent[1] = (val - interval[0]) / seg_len;
        percent[0] =1- percent[1];
        return;
    }
    else if (val <= interval[2])  // [1,2]
    {
        percent[2] = (val - interval[1]) / seg_len;
        percent[1] = 1 - percent[2];
        return;
    }
    else if (val <= interval[3])  // [2,3]
    {
        percent[3] = (val - interval[2]) / seg_len;
        percent[2] = 1 - percent[3];
        return;
    }
    else if (val <= interval[4])  // [3,4]
    {
        percent[4] = (val - interval[3]) / seg_len;
        percent[3] = 1 - percent[4];
        return;
    }
    else if (val <= interval[5])  // [4,5]
    {
        percent[5] = (val - interval[4]) / seg_len;
        percent[4] = 1 - percent[5];
        return;
    }
    else if (val <= interval[6])  // [5,6]
    {
        percent[6] = (val - interval[5]) / seg_len;
        percent[5] = 1 - percent[6];
        return;
    }
    else                          // >6
    {
        percent[6] = 1 ;
        return;
    }
}
/************************************************************************
 * @brief 根据模糊规则表，将e和ec映射为响应的控制参数：kp ki kd
 * @note  NULL
 *
 * @param percent_e[7]  误差e的模糊占比
 * @param percent_ec[7] 误差微分ec的模糊占比
 * @param rule[7][7]    误差规则表
 * @return  percent_out 对于的参数的模糊占比
 *
 *************************************************************************/
void fuzzy_rule(const float *percent_e, const float* percent_ec, const uint8_t rule[FUZZY_SEG_NUMS][FUZZY_SEG_NUMS], float* percent_out)  //模糊规则表映射
{
    for (int i = 0; i < FUZZY_SEG_NUMS; i++)
    {
        percent_out[i] = 0;                    // percent赋初值
    }
    for (int i = 0; i < FUZZY_SEG_NUMS; i++)   // e
    {
        for (int j = 0; j < FUZZY_SEG_NUMS; j++)  //ec
        {
            if (percent_e[i] == 0 || percent_ec[j] == 0)
                continue;
            uint8_t index = rule[i][j];
            percent_out[index] += percent_e[i] * percent_ec[j];
        }
    }
}
/************************************************************************
 * @brief 去模糊化，模糊化相反的过程
 * @note  NULL
 *
 * @param percent[7]  输入变量的模糊占比
 * @param max  输入变量的基本论域为 [-max,max]
 * @return  val 输出变量的真值
 *
 *************************************************************************/
float de_fuzzification(float max, float* percent)  //去模糊化
{
    float val=0;
    float interval[FUZZY_SEG_NUMS];
    float seg_len = 2 * max / (FUZZY_SEG_NUMS - 1);
    for (int i = 0; i < FUZZY_SEG_NUMS; i++)
    {
        interval[i] = -max + i * seg_len;  //分段点的值 NB NM NS ZO PS PM PB 的值
 
        val += percent[i] * interval[i];
    }
    return val;
}
 
/* 浮点数绝对值 */
float abs_1f(float val)
{
    return (val > 0 ? val : -val);
}
/* 浮点数符号 */
float sign_1f(float val)
{
    return (val > 0 ? 1.0f : -1.0f);
}
/* 浮点数限幅 */
float limit_abs1f(float val, float limit)
{
    if (abs_1f(val) > limit)
        return (sign_1f(val) * limit);
    else
        return val;
}
 
/* PID控制器 */
void PID_control(uint8 wheel)
{
		fuzzy_t.FUZZY_USED=true;
    /* 根据模糊规则表计算kp ki kd */
    if (fuzzy_t.FUZZY_USED == true)
    {
        float percent_e[7];
        float percent_ec[7];
        float percent_kp[7];
        float percent_ki[7];
        float percent_kd[7];
 
 
        /* e和ec模糊化 */
        fuzzification(pid.iError[wheel],fuzzy_t.max_e, percent_e);
        fuzzification(pid.Error2[wheel],fuzzy_t.max_ec, percent_ec);
       
        /* 根据模糊规则计算参数 */
        fuzzy_rule(percent_e, percent_ec,fuzzy_t.rule_kp, percent_kp);
        fuzzy_rule(percent_e, percent_ec,fuzzy_t.rule_ki, percent_ki);
        fuzzy_rule(percent_e, percent_ec,fuzzy_t.rule_kd, percent_kd);
 
        /* kp ki kd 去模糊化*/
        fuzzy_t.d_kp[wheel] = de_fuzzification(fuzzy_t.max_kp, percent_kp);
        fuzzy_t.d_ki[wheel] = de_fuzzification(fuzzy_t.max_ki, percent_ki);
        fuzzy_t.d_kd[wheel] = de_fuzzification(fuzzy_t.max_kd, percent_kd);
 
        pid.Kp[wheel] += fuzzy_t.d_kp[wheel]/100;
        pid.Ki[wheel] += fuzzy_t.d_ki[wheel]/100;
				for(uint8 i=0;i<4;i++)
				{
					fuzzy_t.d_kp[i]=0;
					fuzzy_t.d_ki[i]=0;
				}
				if(pid.Kp[wheel]<=0)
					pid.Kp[wheel]=0;
				if(pid.Ki[wheel]<=0)
					pid.Ki[wheel]=0;
        //pid.Kp[wheel] += fuzzy_t.d_kp[wheel];
    }
		
}