#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define S1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����s1
#define S2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����s2
#define S3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//��ȡ����s3
#define S4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����s4(WK_UP) 


#define S1_PRES 	1	//KEY0����,�������ϵ�KEY2
#define S2_PRES 	2	//KEY0����,�������ϵ�KEY3
#define S3_PRES 	3	//KEY0����,�������ϵ�KEY4
#define S4_PRES   4	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
