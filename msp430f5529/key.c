#include "key.h"
#include "delay.h"
#include "timer.h"

void KEY_Init(void)
{
  P3DIR &= ~(BIT5+BIT6);
  P3REN |= BIT5+BIT6;  
  P3OUT |= BIT5+BIT6;  
}


void KEY_0()
{
   if((P3IN&BIT5)==0)
   {
     delay_ms(100);
     if( (P3IN&BIT5)==0)
     {
           
     }   
    }  
}

void KEY_1()
{
   if((P3IN&BIT6)==0)
   {
     delay_ms(100);
     if( (P3IN&BIT6)==0)
     {
           
     }   
    }  
}