#ifndef  ADC_H
#define  ADC_H

#include "msp430f5529.h"

#define NUM 11 //�������� �����涨�������λ������һ�£���ӦΪ���� 

extern float ad1,ad2,ad3,ad4;


void ADC_Init(void);
void filter(void); //��ֵ�˲�
void ad_ave(int n); //��ֵ�˲�

#endif