#ifndef TIMER_H_
#define TIMER_H_

#include "msp430f5529.h"
#include "common.h"
#include "delay.h"


#define deadtime 20 //死区时间

#define TA0_PRECISON 1000u     //定义占空比精度，100即精度为1%，1000u则精度为0.1%，用于占空比 duty 形参传入，即占空比为 duty/FTM_PRECISON
#define TA1_PRECISON 1000u     //定义占空比精度，100即精度为1%，1000u则精度为0.1%，用于占空比 duty 形参传入，即占空比为 duty/FTM_PRECISON
#define TA2_PRECISON 1000u     //定义占空比精度，100即精度为1%，1000u则精度为0.1%，用于占空比 duty 形参传入，即占空比为 duty/FTM_PRECISON
#define TB_PRECISON  1000u     //定义占空比精度，100即精度为1%，1000u则精度为0.1%，用于占空比 duty 形参传入，即占空比为 duty/FTM_PRECISON


extern float MOD;

void Timer0_Init(void);
void Timer1_Init(void);
void Timer2_Init(void);
#endif