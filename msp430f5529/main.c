/***********2017�����A*******/
/*
��Ŀ���������
ʱ�䣺2017-8-9
IO�����������
spwm:1.2,1.3,1.4
ad:  6.0,6.1,6.2,6.3
����2.4
5110:2.0,2.2,2.3,2.6,2.7
������

��ʱ��ʹ�������
��ʱ��0����3·spwm
��ʱ��1
��ʱ��2�����ж�
��ʱ��B
*/
/****************************/
#include "msp430f5529.h"
#include "sysclk_4M.h"
#include "timer.h"
#include "nokia_5110.h"
#include "adc.h"
#include "key.h"
#include "PID.h"
#include "uart.h"


void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  ucsclk_Init(16);
  Timer0_Init();
  ADC_Init();
  LCD_init();
  //Uart_int();
  //PID_Parameter_Init(&voltage,10,0.01,0.1,0);
  __enable_interrupt();
  while(1)
  {
     //filter();//��ֵ�˲�    
     //MOD = PID_Calc(&voltage,ad1);
  }
}
