#ifndef __PID_H
#define __PID_H	  


#include"string.h"


//APB2��Ƶ72e6����Ƶ��15K���ȣ�72e6/15e3=2400
//Ҳ����˵4800��Ӧ���ռ�ձ�
//MAXȡռ�ձ�0.95��Ӧֵ����4800*0.95=4560
#define  MAX  0.98
#define  MIN  0.2

#define  MAX_1   100
#define  MIN_1  -100

#define  MIN_2  -100
#define  MAX_2   100	 


//����ṹ��
typedef struct  
{  
    float SetPoint;      // �趨Ŀ�� Desired Value  
    float Proportion;    // �������� Proportional Const  
    float Integral;      // ���ֳ��� Integral Const 
    float Derivative; 	 // ΢�ֳ��� Derivative Const
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
