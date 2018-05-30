#ifndef  ADC_H
#define  ADC_H

#include "msp430f5529.h"

#define NUM 11 //采样次数 和上面定义的数组位数保持一致，且应为奇数 

extern float ad1,ad2,ad3,ad4;


void ADC_Init(void);
void filter(void); //中值滤波
void ad_ave(int n); //均值滤波

#endif