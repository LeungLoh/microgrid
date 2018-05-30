#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
  
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟

	
	//上拉输入为了保证在无信号是电压为高电平
	//下拉输入为了保证在无信号是电压为低电平
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2,3,4

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0

}

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(S1==0||S2==0||S3==0||S4==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(S1==0)return S1_PRES;
		else if(S2==0)return S2_PRES;
		else if(S3==0)return S3_PRES;
		else if(S4==1)return S4_PRES;
	}else if(S1==1&&S2==1&&S3==1&&S4==0)key_up=1; 	    
 	return 0;// 无按键按下
}
