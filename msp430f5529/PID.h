#ifndef __PID_H
#define __PID_H	  


#include"string.h"


//APB2主频72e6开关频率15K赫兹，72e6/15e3=2400
//也就是说4800对应最大占空比
//MAX取占空比0.95对应值，即4800*0.95=4560
#define  MAX  0.98
#define  MIN  0.2

#define  MAX_1   100
#define  MIN_1  -100

#define  MIN_2  -100
#define  MAX_2   100	 


//定义结构体
typedef struct  
{  
    float SetPoint;      // 设定目标 Desired Value  
    float Proportion;    // 比例常数 Proportional Const  
    float Integral;      // 积分常数 Integral Const 
    float Derivative; 	 // 微分常数 Derivative Const
    float LastError;     // Error[-1]  
    float PrevError;     // Error[-2]   
}PID;

extern PID voltage;
extern PID current;
extern PID blance;

extern float pid_out;             // PID Response (Output)  
extern float pid_in;              // PID Feedback (Input)

extern float pid_out_1;           // PID Response (Output)  
extern float pid_in_1;            // PID Feedback (Input) 

extern float pid_out_2;           // PID Response (Output)  
extern float pid_in_2;            // PID Feedback (Input) 

float PID_Calc(PID *pp, float NextPoint );
float PID_Calc_1(PID *pp, float NextPoint);  
float PID_Calc_2(PID *pp, float NextPoint); 

void PID_Parameter_Init(PID *pp,float setpoint,float Proportion,float Integral, float Derivative);

 
#endif 
