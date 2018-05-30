#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"


void Adc_Init(void);
u16  Get_Adc(u16 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
u32 Get_Adc_Squ(u8 ch);
 
#endif 
