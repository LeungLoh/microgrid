#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define S1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键s1
#define S2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键s2
#define S3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键s3
#define S4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键s4(WK_UP) 


#define S1_PRES 	1	//KEY0按下,开发板上的KEY2
#define S2_PRES 	2	//KEY0按下,开发板上的KEY3
#define S3_PRES 	3	//KEY0按下,开发板上的KEY4
#define S4_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)


void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
