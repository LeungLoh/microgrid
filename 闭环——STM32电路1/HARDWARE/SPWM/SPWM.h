#ifndef	SPWM_H
#define SPWM_H

#include "sys.h"

void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM2_Int_Init(u16 arr,u16 psc);
extern float Period_percent; 
extern u32 AD_Result;
extern float temp0,temp1,temp2,temp3;  //4·adc
#endif


