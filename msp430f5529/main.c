/***********2017年电赛A*******/
/*
题目：三相逆变
时间：2017-8-9
IO口配置情况：
spwm:1.2,1.3,1.4
ad:  6.0,6.1,6.2,6.3
捕获：2.4
5110:2.0,2.2,2.3,2.6,2.7
按键：

定时器使用情况：
定时器0产生3路spwm
定时器1
定时器2捕获中断
定时器B
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
     //filter();//中值滤波    
     //MOD = PID_Calc(&voltage,ad1);
  }
}
