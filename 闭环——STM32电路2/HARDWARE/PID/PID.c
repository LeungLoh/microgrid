#include"PID.h"

#include"string.h"
#include"math.h"

float pid_in;              // PID Feedback (Input)
float pid_out;             // PID Response (Output)  

float pid_in_1;            // PID Feedback (Input) 
float pid_out_1;           // PID Response (Output)  

float pid_in_2;            // PID Feedback (Input) 
float pid_out_2;           // PID Response (Output)  


float Result=0,LastResult=0;		 // ����PID�ļ�����
float Result_1=0,LastResult_1=0;	 // ����PID�ļ�����
float Result_2=0,LastResult_2=0;	 // ����PID�ļ�����

PID voltage;                         // �����ṹ��
PID current;                         // �����ṹ��
PID blance;                          // �����ṹ��
//��ʼ������
void PID_Parameter_Init(PID *pp,float setpoint,float Proportion,float Integral, float Derivative)
{    
    memset( pp,0,sizeof(PID));	     // ��ʼ���ṹ�� ȫ����ʼ��Ϊ0

    pp->SetPoint=setpoint;           // �趨Ŀ�� Desired Value      
    pp->Proportion=Proportion;       // �������� Proportional Const  
    pp->Integral=Integral;           // ���ֳ��� Integral Const
    pp->Derivative=Derivative;       // ΢�ֳ��� Derivative Const  
}

/*PID���㺯��--------------------------------------------------------------------------------------*/ 
float PID_Calc(PID *pp, float NextPoint )  
{  	
    float Error;
    unsigned char flag_max=0,flag_min=0;

    Error = pp->SetPoint - NextPoint;          // ƫ�� 
    if(Result>MAX)                             // ֻ�ۼӸ�ƫ��                      
    {   
        if(Error>=0)
        {
            Error=0;
        }
        flag_max=1;         
    }
    if(Result<MIN)                             // ֻ�ۼ���ƫ�� 
    {
        if(Error<=0)
        {
           Error=0;
        }
        flag_min=1; 
    }    
    //PID����   
    Result=LastResult
	      +(float)pp->Proportion  * (Error-pp->LastError)                       // ������
	      +(float)pp->Integral    *  Error	                                    // ������ 
              +(float)pp->Derivative  * (Error-2*(pp->LastError)+pp->PrevError);    // ΢����
   
    pp->PrevError=pp->LastError;		               // �򵥸�ֵ����
    pp->LastError= Error; 				       // �򵥸�ֵ����
    LastResult= Result;					       // �򵥸�ֵ����	     
    if(flag_max)
    {   
        flag_max=0;
        return MAX;
    }
    if(flag_min)
    {
        flag_min=0;
    return MIN;
    }
    else
    {
        return Result;
   }
}

/*PID���㺯��1--------------------------------------------------------------------------------------*/ 
float PID_Calc_1(PID *pp, float NextPoint)  
{  	
    float Error;
    unsigned char flag_max=0,flag_min=0;

    Error = pp->SetPoint - NextPoint;              // ƫ�� 
    if(Result_1>MAX_1)                             // ֻ�ۼӸ�ƫ��                      
    {   
        if(Error>=0)
        {
            Error=0;
        }
        flag_max=1;         
    }
    if(Result_1<MIN_1)                             // ֻ�ۼ���ƫ�� 
    {
        if(Error<=0)
        {
           Error=0;
        }
        flag_min=1; 
    }    
    //PID����   
    Result_1=LastResult_1
	      +(float)pp->Proportion  * (Error-pp->LastError)                       // ������
	      +(float)pp->Integral    *  Error	                                    // ������ 
	      +(float)pp->Derivative  * (Error-2*(pp->LastError)+pp->PrevError);    // ΢����
   
    pp->PrevError=pp->LastError;		       // �򵥸�ֵ����
    pp->LastError= Error; 			       // �򵥸�ֵ����
    LastResult_1= Result_1;			       // �򵥸�ֵ����	     
    if(flag_max)
    {   
        flag_max=0;
        return MAX_1;
    }
    if(flag_min)
    {
        flag_min=0;
    return MIN_1;
    }
    else
    {
        return Result_1;
   }
}

/*PID���㺯��--------------------------------------------------------------------------------------*/ 
float PID_Calc_2(PID *pp, float NextPoint)  
{  	
    float Error;
    unsigned char flag_max=0,flag_min=0;

    Error = pp->SetPoint - NextPoint;              // ƫ�� 
    if(Result_2>MAX_2)                             // ֻ�ۼӸ�ƫ��                      
    {   
        if(Error>=0)
        {
            Error=0;
        }
        flag_max=1;         
    }
    if(Result_2<MIN_2)                             // ֻ�ۼ���ƫ�� 
    {
        if(Error<=0)
        {
           Error=0;
        }
        flag_min=1; 
    }    
    //PID����   
    Result_2=LastResult_2
	      +(float)pp->Proportion  * (Error-pp->LastError)                       // ������
	      +(float)pp->Integral    *  Error	                                    // ������ 
	      +(float)pp->Derivative  * (Error-2*(pp->LastError)+pp->PrevError);    // ΢����
   
    pp->PrevError=pp->LastError;		       // �򵥸�ֵ����
    pp->LastError= Error; 			       // �򵥸�ֵ����
    LastResult_2= Result_2;			       // �򵥸�ֵ����	     
    if(flag_max)
    {   
        flag_max=0;
        return MAX_2;
    }
    if(flag_min)
    {
        flag_min=0;
    return MIN_2;
    }
    else
    {
        return Result_2;
   }
}

