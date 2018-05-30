#include "adc.h"

float ad1,ad2,ad3,ad4;
//ADC初始化
void ADC_Init()
{
   P6SEL |=BIT0+BIT1+BIT2+BIT3;
   REFCTL0 &=~ REFMSTR;
   
   ADC12CTL0 = ADC12ON  + ADC12MSC + ADC12SHT0_8 + ADC12REF2_5V +  ADC12REFON;//采样时间+AD内核开启+内部参考电压开启+内部才考电压设置为2.5V
   ADC12CTL1 = ADC12SHP+ADC12CONSEQ_3+ADC12SSEL_3;         // 使用采样定时器，脉冲取样模式；设置重复序列采样模式；
   ADC12CTL2 = ADC12RES_2 + ADC12REFOUT;    // AD基本配置
   
   ADC12MCTL0 = ADC12INCH_0 + ADC12SREF_1; 
   ADC12MCTL1 = ADC12INCH_1 + ADC12SREF_1;
   ADC12MCTL2 = ADC12INCH_2 + ADC12SREF_1;
   ADC12MCTL3 = ADC12INCH_3 + ADC12SREF_1 +ADC12EOS;
   ADC12CTL0 |= ADC12ENC;                                        // 使能转换位
   ADC12CTL0 |= ADC12SC;                                         // 开始转换
}



//中值滤波
void filter(void) 
{ 
  float ad1_tmp=0,ad2_tmp=0,ad3_tmp=0,ad4_tmp=0;
  float value_buf1[NUM]={0};
  float value_buf2[NUM]={0};
  float value_buf3[NUM]={0};
  float value_buf4[NUM]={0};
  int count,i,j;
  float temp;  
  for(count=0;count<NUM;count++) 
  {
    ad1_tmp =  22.291*(ADC12MEM0*2.5/4095)-0.2;
    ad2_tmp =  ADC12MEM1*2.5/4095;
    ad3_tmp =  ADC12MEM2*2.5/4095;
    ad4_tmp =  ADC12MEM3*2.5/4095;
    
    value_buf1[count] = ad1_tmp; 
    value_buf2[count] = ad2_tmp; 
    value_buf3[count] = ad3_tmp; 
    value_buf4[count] = ad4_tmp;
  } 
  for (j=0;j<NUM-1;j++) 
  {  
    for(i=0;i<NUM-j;i++)
    { 
      if ( value_buf1[i]>value_buf1[i+1] ) 
      { 
        temp = value_buf1[i]; 
        value_buf1[i] = value_buf1[i+1]; 
        value_buf1[i+1] = temp; 
      }
      if ( value_buf2[i]>value_buf2[i+1] ) 
      { 
        temp = value_buf2[i]; 
        value_buf2[i] = value_buf2[i+1]; 
        value_buf2[i+1] = temp; 
      }
      if ( value_buf3[i]>value_buf3[i+1] ) 
      { 
        temp = value_buf3[i]; 
        value_buf3[i] = value_buf3[i+1]; 
        value_buf3[i+1] = temp; 
      }
       if ( value_buf4[i]>value_buf4[i+1] ) 
      { 
        temp = value_buf4[i]; 
        value_buf4[i] = value_buf4[i+1]; 
        value_buf4[i+1] = temp; 
      }
   }
  }
  
  ad1 = value_buf1[(NUM-1)/2]; 
  ad2 = value_buf2[(NUM-1)/2]; 
  ad3 = value_buf3[(NUM-1)/2];
  ad4 = value_buf4[(NUM-1)/2];
}



void ad_ave(int n) //均值滤波
{
    float ad1_tmp=0, ad2_tmp=0, ad3_tmp=0, ad4_tmp=0;
    int  i;
      for(i = 0; i < n; i++)
      {

        ad1_tmp += ADC12MEM0*2.5/4095; 
        ad2_tmp += ADC12MEM1*2.5/4095; 
        ad3_tmp += ADC12MEM2*2.5/4095; 
        ad4_tmp += ADC12MEM3*2.5/4095;
      }
    ad1 = ad1_tmp / n;
    ad2 = ad2_tmp / n;
    ad3 = ad3_tmp / n;
    ad4 = ad4_tmp / n;
}

