/*******************************************************************************
//
//
//						* �� �� �� �� ��
//              ----------------------------------------------------------------
//							����SPWM��
//
//
//						* �� �� �� �� ��
//              ----------------------------------------------------------------
//							TIM1��TIM2��ʱ����Ƶ�ʺ�Ԥ��Ƶϵ��
// 
//
//						* �� �� �� �� ��
//              ----------------------------------------------------------------
//							����õ���ʱ���Զ���װ��ֵ
//							��ʼ���ṹ����ڲ���
//							ͨ����ʱ�����жϷ������޸�ռ�ձ�
//
//
//						* �� �� �� ʽ ��
//              ----------------------------------------------------------------
//							���Ҳ���Ƶ�ʣ� 
//							PWmƵ��/400=25Hz
//
//							�Զ���װ������ֵ�� 
//							TimerPeriod = (SystemCoreClock / pfreq) - 1; 
//
//							PWMռ�ձȱ仯���ӣ�
//							Period_percent = ((SystemCoreClock / freq) - 1) / 32767.0;
//
//
//							 
//              ----------------------------------------------------------------
 *******************************************************************************/

#define  __SPWM
#include "stm32f10x.h"
#include "SPWM.h"
#include "adc.h"
#include "math.h"
#include "PID.h"

#define Sample_NUM 360

float Period_percent; 		//PWMռ�ձȱ仯���ӣ������޸�����

const u32 spwm_A[360]={
2000,
2033,
2066,
2099,
2133,
2166,
2199,
2232,
2264,
2297,
2330,
2363,
2395,
2427,
2460,
2492,
2524,
2556,
2587,
2619,
2650,
2681,
2712,
2742,
2773,
2803,
2833,
2863,
2892,
2921,
2950,
2979,
3007,
3035,
3062,
3090,
3117,
3143,
3170,
3196,
3221,
3247,
3271,
3296,
3320,
3344,
3367,
3390,
3412,
3434,
3455,
3477,
3497,
3517,
3537,
3556,
3575,
3593,
3611,
3629,
3645,
3662,
3678,
3693,
3708,
3722,
3736,
3749,
3762,
3774,
3785,
3796,
3807,
3817,
3826,
3835,
3844,
3851,
3858,
3865,
3871,
3877,
3882,
3886,
3890,
3893,
3895,
3897,
3899,
3900,
3900,
3900,
3899,
3897,
3895,
3893,
3890,
3886,
3882,
3877,
3871,
3865,
3858,
3851,
3844,
3835,
3826,
3817,
3807,
3796,
3785,
3774,
3762,
3749,
3736,
3722,
3708,
3693,
3678,
3662,
3645,
3629,
3611,
3593,
3575,
3556,
3537,
3517,
3497,
3477,
3455,
3434,
3412,
3390,
3367,
3344,
3320,
3296,
3271,
3247,
3221,
3196,
3170,
3143,
3117,
3090,
3062,
3035,
3007,
2979,
2950,
2921,
2892,
2863,
2833,
2803,
2773,
2742,
2712,
2681,
2650,
2619,
2587,
2556,
2524,
2492,
2460,
2427,
2395,
2363,
2330,
2297,
2264,
2232,
2199,
2166,
2133,
2099,
2066,
2033,
2000,
1967,
1934,
1901,
1867,
1834,
1801,
1768,
1736,
1703,
1670,
1637,
1605,
1573,
1540,
1508,
1476,
1444,
1413,
1381,
1350,
1319,
1288,
1258,
1227,
1197,
1167,
1137,
1108,
1079,
1050,
1021,
993,
965,
938,
910,
883,
857,
830,
804,
779,
753,
729,
704,
680,
656,
633,
610,
588,
566,
545,
523,
503,
483,
463,
444,
425,
407,
389,
371,
355,
338,
322,
307,
292,
278,
264,
251,
238,
226,
215,
204,
193,
183,
174,
165,
156,
149,
142,
135,
129,
123,
118,
114,
110,
107,
105,
103,
101,
100,
100,
100,
101,
103,
105,
107,
110,
114,
118,
123,
129,
135,
142,
149,
156,
165,
174,
183,
193,
204,
215,
226,
238,
251,
264,
278,
292,
307,
322,
338,
355,
371,
389,
407,
425,
444,
463,
483,
503,
523,
545,
566,
588,
610,
633,
656,
680,
704,
729,
753,
779,
804,
830,
857,
883,
910,
938,
965,
993,
1021,
1050,
1079,
1108,
1137,
1167,
1197,
1227,
1258,
1288,
1319,
1350,
1381,
1413,
1444,
1476,
1508,
1540,
1573,
1605,
1637,
1670,
1703,
1736,
1768,
1801,
1834,
1867,
1901,
1934,
1967

}; 											//ռ�ձ�Ϊ:(32767-spwm[i])/32767 = 1-��period*spwm[i])/period



const u32 spwm_B[360]={
3645,
3629,
3611,
3593,
3575,
3556,
3537,
3517,
3497,
3477,
3455,
3434,
3412,
3390,
3367,
3344,
3320,
3296,
3271,
3247,
3221,
3196,
3170,
3143,
3117,
3090,
3062,
3035,
3007,
2979,
2950,
2921,
2892,
2863,
2833,
2803,
2773,
2742,
2712,
2681,
2650,
2619,
2587,
2556,
2524,
2492,
2460,
2427,
2395,
2363,
2330,
2297,
2264,
2232,
2199,
2166,
2133,
2099,
2066,
2033,
2000,
1967,
1934,
1901,
1867,
1834,
1801,
1768,
1736,
1703,
1670,
1637,
1605,
1573,
1540,
1508,
1476,
1444,
1413,
1381,
1350,
1319,
1288,
1258,
1227,
1197,
1167,
1137,
1108,
1079,
1050,
1021,
993,
965,
938,
910,
883,
857,
830,
804,
779,
753,
729,
704,
680,
656,
633,
610,
588,
566,
545,
523,
503,
483,
463,
444,
425,
407,
389,
371,
355,
338,
322,
307,
292,
278,
264,
251,
238,
226,
215,
204,
193,
183,
174,
165,
156,
149,
142,
135,
129,
123,
118,
114,
110,
107,
105,
103,
101,
100,
100,
100,
101,
103,
105,
107,
110,
114,
118,
123,
129,
135,
142,
149,
156,
165,
174,
183,
193,
204,
215,
226,
238,
251,
264,
278,
292,
307,
322,
338,
355,
371,
389,
407,
425,
444,
463,
483,
503,
523,
545,
566,
588,
610,
633,
656,
680,
704,
729,
753,
779,
804,
830,
857,
883,
910,
938,
965,
993,
1021,
1050,
1079,
1108,
1137,
1167,
1197,
1227,
1258,
1288,
1319,
1350,
1381,
1413,
1444,
1476,
1508,
1540,
1573,
1605,
1637,
1670,
1703,
1736,
1768,
1801,
1834,
1867,
1901,
1934,
1967,
2000,
2033,
2066,
2099,
2133,
2166,
2199,
2232,
2264,
2297,
2330,
2363,
2395,
2427,
2460,
2492,
2524,
2556,
2587,
2619,
2650,
2681,
2712,
2742,
2773,
2803,
2833,
2863,
2892,
2921,
2950,
2979,
3007,
3035,
3062,
3090,
3117,
3143,
3170,
3196,
3221,
3247,
3271,
3296,
3320,
3344,
3367,
3390,
3412,
3434,
3455,
3477,
3497,
3517,
3537,
3556,
3575,
3593,
3611,
3629,
3645,
3662,
3678,
3693,
3708,
3722,
3736,
3749,
3762,
3774,
3785,
3796,
3807,
3817,
3826,
3835,
3844,
3851,
3858,
3865,
3871,
3877,
3882,
3886,
3890,
3893,
3895,
3897,
3899,
3900,
3900,
3900,
3899,
3897,
3895,
3893,
3890,
3886,
3882,
3877,
3871,
3865,
3858,
3851,
3844,
3835,
3826,
3817,
3807,
3796,
3785,
3774,
3762,
3749,
3736,
3722,
3708,
3693,
3678,
3662

}; 											//ռ�ձ�Ϊ:(32767-spwm[i])/32767 = 1-��period*spwm[i])/period


const u32 spwm_C[360]={
355,
338,
322,
307,
292,
278,
264,
251,
238,
226,
215,
204,
193,
183,
174,
165,
156,
149,
142,
135,
129,
123,
118,
114,
110,
107,
105,
103,
101,
100,
100,
100,
101,
103,
105,
107,
110,
114,
118,
123,
129,
135,
142,
149,
156,
165,
174,
183,
193,
204,
215,
226,
238,
251,
264,
278,
292,
307,
322,
338,
355,
371,
389,
407,
425,
444,
463,
483,
503,
523,
545,
566,
588,
610,
633,
656,
680,
704,
729,
753,
779,
804,
830,
857,
883,
910,
938,
965,
993,
1021,
1050,
1079,
1108,
1137,
1167,
1197,
1227,
1258,
1288,
1319,
1350,
1381,
1413,
1444,
1476,
1508,
1540,
1573,
1605,
1637,
1670,
1703,
1736,
1768,
1801,
1834,
1867,
1901,
1934,
1967,
2000,
2033,
2066,
2099,
2133,
2166,
2199,
2232,
2264,
2297,
2330,
2363,
2395,
2427,
2460,
2492,
2524,
2556,
2587,
2619,
2650,
2681,
2712,
2742,
2773,
2803,
2833,
2863,
2892,
2921,
2950,
2979,
3007,
3035,
3062,
3090,
3117,
3143,
3170,
3196,
3221,
3247,
3271,
3296,
3320,
3344,
3367,
3390,
3412,
3434,
3455,
3477,
3497,
3517,
3537,
3556,
3575,
3593,
3611,
3629,
3645,
3662,
3678,
3693,
3708,
3722,
3736,
3749,
3762,
3774,
3785,
3796,
3807,
3817,
3826,
3835,
3844,
3851,
3858,
3865,
3871,
3877,
3882,
3886,
3890,
3893,
3895,
3897,
3899,
3900,
3900,
3900,
3899,
3897,
3895,
3893,
3890,
3886,
3882,
3877,
3871,
3865,
3858,
3851,
3844,
3835,
3826,
3817,
3807,
3796,
3785,
3774,
3762,
3749,
3736,
3722,
3708,
3693,
3678,
3662,
3645,
3629,
3611,
3593,
3575,
3556,
3537,
3517,
3497,
3477,
3455,
3434,
3412,
3390,
3367,
3344,
3320,
3296,
3271,
3247,
3221,
3196,
3170,
3143,
3117,
3090,
3062,
3035,
3007,
2979,
2950,
2921,
2892,
2863,
2833,
2803,
2773,
2742,
2712,
2681,
2650,
2619,
2587,
2556,
2524,
2492,
2460,
2427,
2395,
2363,
2330,
2297,
2264,
2232,
2199,
2166,
2133,
2099,
2066,
2033,
2000,
1967,
1934,
1901,
1867,
1834,
1801,
1768,
1736,
1703,
1670,
1637,
1605,
1573,
1540,
1508,
1476,
1444,
1413,
1381,
1350,
1319,
1288,
1258,
1227,
1197,
1167,
1137,
1108,
1079,
1050,
1021,
993,
965,
938,
910,
883,
857,
830,
804,
779,
753,
729,
704,
680,
656,
633,
610,
588,
566,
545,
523,
503,
483,
463,
444,
425,
407,
389,
371,
}; 											//ռ�ձ�Ϊ:(32767-spwm[i])/32767 = 1-��period*spwm[i])/period


static u16 SinTab_i = 0;				//��ʾ���Ҳ�ȡ����
u16 AD_Num=0;
u32 AD_Sum=0;
u32 AD_Result;
int i =0;
float temp0,temp1,temp2,temp3;  //4·adc
/*******************************************************
 *	  ��ʱ��3����3·������SPWM��
 *	  channel1 ,channel2 ,channel3 -->PA.7, PB.0, PB.1	
 *		TimerPeriod	  --> �Զ���װ������ֵ
 *		ChannelxPulse --> ռ������ֵ
 ******************************************************/

//��ʱ��1�жϷ������
//���ı�PWMռ�ձ�
void TIM1_UP_IRQHandler(void)   
{      
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) 
    {  
      TIM_ClearITPendingBit(TIM1, TIM_IT_Update); 
			        
			TIM_SetCompare1(TIM1,(u16)(Period_percent*spwm_A[SinTab_i])) ;		//�޸�TIM1ͨ��1��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���1��ֵ
			TIM_SetCompare2(TIM1,(u16)(Period_percent*spwm_B[SinTab_i]));			//�޸�TIM1ͨ��2��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���2��ֵ
			TIM_SetCompare3(TIM1,(u16)(Period_percent*spwm_C[SinTab_i]));			//�޸�TIM1ͨ��3��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���3��ֵ
			//TIM_SetCompare1(TIM1,spwm_A[SinTab_i]) ;		//�޸�TIM1ͨ��1��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���1��ֵ
			//TIM_SetCompare2(TIM1,spwm_B[SinTab_i]);			//�޸�TIM1ͨ��2��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���2��ֵ
			//TIM_SetCompare3(TIM1,spwm_C[SinTab_i]);			//�޸�TIM1ͨ��3��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���3��ֵ
			SinTab_i++;
			
			if(SinTab_i == Sample_NUM)
			{
			  SinTab_i = 0;
			}

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //���TIM1�����жϱ�־	
  
    }          
}  


//TIM3 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef 				 NVIC_InitStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure2,TIM_OCInitStructure3,TIM_OCInitStructure4;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
	/* ����ж����� */
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );                //ʹ��ָ����TIM1�ж�,��������жϣ�����������������ʼ��ʱ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure); 
		
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	       
	
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 PA.7
	TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC2Init(TIM3, &TIM_OCInitStructure2);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
	
	//��ʼ��TIM3 Channel3 PWMģʽ	 PB.0
	TIM_OCInitStructure3.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure3.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure3.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
  TIM_OC3Init(TIM3, &TIM_OCInitStructure3);  //����Tָ���Ĳ�����ʼ������TIM3 OC2	
	
	//��ʼ��TIM3 Channel4 PWMģʽ	PB.1 
	TIM_OCInitStructure4.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure4.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure4.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC4Init(TIM3, &TIM_OCInitStructure4);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
 
 
 
	 TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
	                                                                       
}

//��ʱ��3�жϷ������
//���ı�PWMռ�ձ�
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	 if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
    {  
      TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
			        
			TIM_SetCompare2(TIM3,(u16)(Period_percent*spwm_A[SinTab_i])) ;		//�޸�TIM1ͨ��1��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���1��ֵ
			TIM_SetCompare3(TIM3,(u16)(Period_percent*spwm_B[SinTab_i]));			//�޸�TIM1ͨ��2��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���2��ֵ
			TIM_SetCompare4(TIM3,(u16)(Period_percent*spwm_C[SinTab_i]));			//�޸�TIM1ͨ��3��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���3��ֵ
			SinTab_i++;
			
			if(SinTab_i == Sample_NUM){SinTab_i = 0;}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIM1�����жϱ�־	
  
    }
		
}

//��ʱ��2ͨ��1���벶������

TIM_ICInitTypeDef  TIM2_ICInitStructure;

void TIM2_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef         NVIC_InitStructure;
	TIM_ICInitTypeDef        TIM2_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ��TIM2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;  //PA1 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA1 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);						 //PA1 ����
	
	//��ʼ����ʱ��2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM2���벶�����
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
	
  TIM_Cmd(TIM2,ENABLE ); 	//ʹ�ܶ�ʱ��5
   
}


 
void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM2�����жϷ������
		{
				TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx�����жϱ�־ 
			  Period_percent = PID_Calc(&voltage,temp0);
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET) 
	{ 
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1); 
		SinTab_i=0;                         
	}
}




