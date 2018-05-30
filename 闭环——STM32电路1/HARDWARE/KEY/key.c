#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
  
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��

	
	//��������Ϊ�˱�֤�����ź��ǵ�ѹΪ�ߵ�ƽ
	//��������Ϊ�˱�֤�����ź��ǵ�ѹΪ�͵�ƽ
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_3|GPIO_Pin_2;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

}

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(S1==0||S2==0||S3==0||S4==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(S1==0)return S1_PRES;
		else if(S2==0)return S2_PRES;
		else if(S3==0)return S3_PRES;
		else if(S4==1)return S4_PRES;
	}else if(S1==1&&S2==1&&S3==1&&S4==0)key_up=1; 	    
 	return 0;// �ް�������
}
