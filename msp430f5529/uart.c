#include "msp430f5529.h"
#include "uart.h"

unsigned char Rx_Byte='0';
unsigned char Rx_flag=0;

void Uart_int(void)
{
  P3SEL = BIT3+BIT4;                        // P3.3,4 = USCI_A1 TXD/RXD
    
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA0BR0 = 0x03;                           // 9600 (see User's Guide)
  UCA0BR1 = 0x00;                           //
  UCA0MCTL |= UCBRS_3+UCBRF_0;              // Modulation UCBRSx=6, UCBRFx=0
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A1 RX interrupt
}
void put_string(unsigned char *str)
{
    while (*str)                                //*str>0x20
    {
        while (!(UCA0IFG&UCTXIFG));                // USCI_A1 TX buffer ready?
        UCA0TXBUF = *(str++);                     // *(str++) -> UCA0TXBUF
    }                  
}

void put_char(unsigned char c)
{
    while (!(UCA0IFG&UCTXIFG));                // USCI_A1 TX buffer ready?
    UCA0TXBUF = c;                            // C-> UCA1TXBUF
}

unsigned char get_char(void)
{
    Rx_flag=0;
    while (!Rx_flag);                          // USCI_A1 RX buffer ready?
    return UCA0RXBUF;                          // UCA0RXBUF -> char   
}

unsigned char get_key(void)
{
    return Rx_Byte;
}

void put_float(float x,int n)       //x为要显示的浮点型数据，n为小数位数
{
    unsigned char i=1,j=0,k=0;
    int array[10];
    while(x>=10.0)                  //计小数点位置   
    {   
        i++;   
        x/=10;   
    }   
    for(j=0;j<n+i+1;j++)            //小数点占1位   
    {   
       if(j==i)   
       {   
          array[i]=-2;                //－2＋48=46为小数点的ascii   
          continue;   
       }   
       array[j]=(int)x;   
       x-=array[j];   
       x*=10.0;   
    }
    for(k=0;k<n+i+1;k++)
        put_char(array[k]+'0');
    put_char('\r');
    put_char('\n');
}

void get_string(unsigned char *str,unsigned char num)
{
    while(num--)
    {
        Rx_flag=0;
        while (!Rx_flag);                     // USCI_A1 RX buffer ready?
            *(str++) = UCA0RXBUF;             // UCA1RXBUF -> *(str++)
    }                          
}
void Uart_test(void)
{
    put_string("Hello World");
    //put_string("READY");
    //put_char('w');
}

// USCI  A1  ISR
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0(void)
{
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
    {
      if(UCA0RXBUF=='a')
      {
        P1OUT^=BIT0;
        put_string("HELLO WORLD");
      }
      break;
    }
  case 4:                                       // Vector 4 - TXIFG
    {
      break; 
    }                            
  default: break;
  } 
}

