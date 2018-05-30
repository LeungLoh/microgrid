#include"PID.h"

#include"string.h"
#include"math.h"

float pid_in;              // PID Feedback (Input)
float pid_out;             // PID Response (Output)  

float pid_in_1;            // PID Feedback (Input) 
float pid_out_1;           // PID Response (Output)  

float pid_in_2;            // PID Feedback (Input) 
float pid_out_2;           // PID Response (Output)  


float Result=0,LastResult=0;		 // 定义PID的计算结果
float Result_1=0,LastResult_1=0;	 // 定义PID的计算结果
float Result_2=0,LastResult_2=0;	 // 定义PID的计算结果

PID voltage;                         // 声明结构体
PID current;                         // 声明结构体
PID blance;                          // 声明结构体
//初始化参数
void PID_Parameter_Init(PID *pp,float setpoint,float Proportion,float Integral, float Derivative)
{    
    memset( pp,0,sizeof(PID));	     // 初始化结构体 全部初始化为0

    pp->SetPoint=setpoint;           // 设定目标 Desired Value      
    pp->Proportion=Proportion;       // 比例常数 Proportional Const  
    pp->Integral=Integral;           // 积分常数 Integral Const
    pp->Derivative=Derivative;       // 微分常数 Derivative Const  
}

/*PID计算函数--------------------------------------------------------------------------------------*/ 
float PID_Calc(PID *pp, float NextPoint )  
{  	
    float Error;
    unsigned char flag_max=0,flag_min=0;

    Error = pp->SetPoint - NextPoint;          // 偏差 
    if(Result>MAX)                             // 只累加负偏差                      
    {   
        if(Error>=0)
        {
            Error=0;
        }
        flag_max=1;         
    }
    if(Result<MIN)                             // 只累加正偏差 
    {
        if(Error<=0)
        {
           Error=0;
        }
        flag_min=1; 
    }    
    //PID计算   
    Result=LastResult
	      +(float)pp->Proportion  * (Error-pp->LastError)                       // 比例项
	      +(float)pp->Integral    *  Error	                                    // 积分项 
              +(float)pp->Derivative  * (Error-2*(pp->LastError)+pp->PrevError);    // 微分项
   
    pp->PrevError=pp->LastError;		               // 简单赋值运算
    pp->LastError= Error; 				       // 简单赋值运算
    LastResult= Result;					       // 简单赋值运算	     
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

/*PID计算函数1--------------------------------------------------------------------------------------*/ 
float PID_Calc_1(PID *pp, float NextPoint)  
{  	
    float Error;
    unsigned char flag_max=0,flag_min=0;

    Error = pp->SetPoint - NextPoint;              // 偏差 
    if(Result_1>MAX_1)                             // 只累加负偏差                      
    {   
        if(Error>=0)
        {
            Error=0;
        }
        flag_max=1;         
    }
    if(Result_1<MIN_1)                             // 只累加正偏差 
    {
        if(Error<=0)
        {
           Error=0;
        }
        flag_min=1; 
    }    
    //PID计算   
    Result_1=LastResult_1
	      +(float)pp->Proportion  * (Error-pp->LastError)                       // 比例项
	      +(float)pp->Integral    *  Error	                                    // 积分项 
	      +(float)pp->Derivative  * (Error-2*(pp->LastError)+pp->PrevError);    // 微分项
   
    pp->PrevError=pp->LastError;		       // 简单赋值运算
    pp->LastError= Error; 			       // 简单赋值运算
    LastResult_1= Result_1;			       // 简单赋值运算	     
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

/*PID计算函数--------------------------------------------------------------------------------------*/ 
float PID_Calc_2(PID *pp, float NextPoint)  
{  	
    float Error;
    unsigned char flag_max=0,flag_min=0;

    Error = pp->SetPoint - NextPoint;              // 偏差 
    if(Result_2>MAX_2)                             // 只累加负偏差                      
    {   
        if(Error>=0)
        {
            Error=0;
        }
        flag_max=1;         
    }
    if(Result_2<MIN_2)                             // 只累加正偏差 
    {
        if(Error<=0)
        {
           Error=0;
        }
        flag_min=1; 
    }    
    //PID计算   
    Result_2=LastResult_2
	      +(float)pp->Proportion  * (Error-pp->LastError)                       // 比例项
	      +(float)pp->Integral    *  Error	                                    // 积分项 
	      +(float)pp->Derivative  * (Error-2*(pp->LastError)+pp->PrevError);    // 微分项
   
    pp->PrevError=pp->LastError;		       // 简单赋值运算
    pp->LastError= Error; 			       // 简单赋值运算
    LastResult_2= Result_2;			       // 简单赋值运算	     
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

