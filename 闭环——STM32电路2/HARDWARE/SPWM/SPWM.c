/*******************************************************************************
//
//
//						* 函 数 功 能 ：
//              ----------------------------------------------------------------
//							产生SPWM波
//
//
//						* 入 口 参 数 ：
//              ----------------------------------------------------------------
//							TIM1，TIM2定时器的频率和预分频系数
// 
//
//						* 工 作 过 程 ：
//              ----------------------------------------------------------------
//							计算得到定时器自动重装载值
//							初始化结构体入口参数
//							通过定时器二中断服务函数修改占空比
//
//
//						* 计 算 公 式 ：
//              ----------------------------------------------------------------
//							正弦波的频率： 
//							PWm频率/400=25Hz
//
//							自动重装载周期值： 
//							TimerPeriod = (SystemCoreClock / pfreq) - 1; 
//
//							PWM占空比变化因子：
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

float Period_percent; 		//PWM占空比变化因子，用于修改脉宽

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

}; 											//占空比为:(32767-spwm[i])/32767 = 1-（period*spwm[i])/period



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

}; 											//占空比为:(32767-spwm[i])/32767 = 1-（period*spwm[i])/period


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
}; 											//占空比为:(32767-spwm[i])/32767 = 1-（period*spwm[i])/period


static u16 SinTab_i = 0;				//表示正弦波取样点
u16 AD_Num=0;
u32 AD_Sum=0;
u32 AD_Result;
int i =0;
float temp0,temp1,temp2,temp3;  //4路adc
/*******************************************************
 *	  定时器3产生3路互补的SPWM波
 *	  channel1 ,channel2 ,channel3 -->PA.7, PB.0, PB.1	
 *		TimerPeriod	  --> 自动重装载周期值
 *		ChannelxPulse --> 占空周期值
 ******************************************************/

//定时器1中断服务程序
//查表改变PWM占空比
void TIM1_UP_IRQHandler(void)   
{      
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) 
    {  
      TIM_ClearITPendingBit(TIM1, TIM_IT_Update); 
			        
			TIM_SetCompare1(TIM1,(u16)(Period_percent*spwm_A[SinTab_i])) ;		//修改TIM1通道1的PWM占空比，后者为捕获/比较寄存器1的值
			TIM_SetCompare2(TIM1,(u16)(Period_percent*spwm_B[SinTab_i]));			//修改TIM1通道2的PWM占空比，后者为捕获/比较寄存器2的值
			TIM_SetCompare3(TIM1,(u16)(Period_percent*spwm_C[SinTab_i]));			//修改TIM1通道3的PWM占空比，后者为捕获/比较寄存器3的值
			//TIM_SetCompare1(TIM1,spwm_A[SinTab_i]) ;		//修改TIM1通道1的PWM占空比，后者为捕获/比较寄存器1的值
			//TIM_SetCompare2(TIM1,spwm_B[SinTab_i]);			//修改TIM1通道2的PWM占空比，后者为捕获/比较寄存器2的值
			//TIM_SetCompare3(TIM1,spwm_C[SinTab_i]);			//修改TIM1通道3的PWM占空比，后者为捕获/比较寄存器3的值
			SinTab_i++;
			
			if(SinTab_i == Sample_NUM)
			{
			  SinTab_i = 0;
			}

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //清除TIM1更新中断标志	
  
    }          
}  


//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef 				 NVIC_InitStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure2,TIM_OCInitStructure3,TIM_OCInitStructure4;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
	/* 溢出中断配置 */
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );                //使能指定的TIM1中断,允许更新中断（计数器溢出或软件初始化时�
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	NVIC_Init(&NVIC_InitStructure); 
		
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	       
	
	
	//初始化TIM3 Channel2 PWM模式	 PA.7
	TIM_OCInitStructure2.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure2.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure2.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure2);  //根据T指定的参数初始化外设TIM3 OC2
	
	//初始化TIM3 Channel3 PWM模式	 PB.0
	TIM_OCInitStructure3.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure3.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure3.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
  TIM_OC3Init(TIM3, &TIM_OCInitStructure3);  //根据T指定的参数初始化外设TIM3 OC2	
	
	//初始化TIM3 Channel4 PWM模式	PB.1 
	TIM_OCInitStructure4.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure4.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure4.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM3, &TIM_OCInitStructure4);  //根据T指定的参数初始化外设TIM3 OC2

  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
 
 
 
	 TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	                                                                       
}

//定时器3中断服务程序
//查表改变PWM占空比
void TIM3_IRQHandler(void)   //TIM3中断
{
	 if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
    {  
      TIM_ClearITPendingBit(TIM3, TIM_IT_Update); 
			        
			TIM_SetCompare2(TIM3,(u16)(Period_percent*spwm_A[SinTab_i])) ;		//修改TIM1通道1的PWM占空比，后者为捕获/比较寄存器1的值
			TIM_SetCompare3(TIM3,(u16)(Period_percent*spwm_B[SinTab_i]));			//修改TIM1通道2的PWM占空比，后者为捕获/比较寄存器2的值
			TIM_SetCompare4(TIM3,(u16)(Period_percent*spwm_C[SinTab_i]));			//修改TIM1通道3的PWM占空比，后者为捕获/比较寄存器3的值
			SinTab_i++;
			
			if(SinTab_i == Sample_NUM){SinTab_i = 0;}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIM1更新中断标志	
  
    }
		
}

//定时器2通道1输入捕获配置

TIM_ICInitTypeDef  TIM2_ICInitStructure;

void TIM2_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef         NVIC_InitStructure;
	TIM_ICInitTypeDef        TIM2_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能TIM2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;  //PA1 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA1 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);						 //PA1 下拉
	
	//初始化定时器2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	//初始化TIM2输入捕获参数
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
  TIM_Cmd(TIM2,ENABLE ); 	//使能定时器5
   
}


 
void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM2, ENABLE);  //使能TIMx					 
}
//定时器2中断服务程序
void TIM2_IRQHandler(void)   //TIM2中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
		{
				TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx更新中断标志 
			  Period_percent = PID_Calc(&voltage,temp0);
		}
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET) 
	{ 
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1); 
		SinTab_i=0;                         
	}
}




