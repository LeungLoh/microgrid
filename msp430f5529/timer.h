#ifndef TIMER_H_
#define TIMER_H_

#include "msp430f5529.h"
#include "common.h"
#include "delay.h"


#define deadtime 20 //����ʱ��

#define TA0_PRECISON 1000u     //����ռ�ձȾ��ȣ�100������Ϊ1%��1000u�򾫶�Ϊ0.1%������ռ�ձ� duty �βδ��룬��ռ�ձ�Ϊ duty/FTM_PRECISON
#define TA1_PRECISON 1000u     //����ռ�ձȾ��ȣ�100������Ϊ1%��1000u�򾫶�Ϊ0.1%������ռ�ձ� duty �βδ��룬��ռ�ձ�Ϊ duty/FTM_PRECISON
#define TA2_PRECISON 1000u     //����ռ�ձȾ��ȣ�100������Ϊ1%��1000u�򾫶�Ϊ0.1%������ռ�ձ� duty �βδ��룬��ռ�ձ�Ϊ duty/FTM_PRECISON
#define TB_PRECISON  1000u     //����ռ�ձȾ��ȣ�100������Ϊ1%��1000u�򾫶�Ϊ0.1%������ռ�ձ� duty �βδ��룬��ռ�ձ�Ϊ duty/FTM_PRECISON


extern float MOD;

void Timer0_Init(void);
void Timer1_Init(void);
void Timer2_Init(void);
#endif