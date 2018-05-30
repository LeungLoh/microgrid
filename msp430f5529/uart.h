#ifndef  UART_H
#define  UART_H
#include <msp430f5529.h>

extern unsigned char Rx_Byte;
extern unsigned char Rx_flag;
extern float testdata;
void Uart_int(void);
void put_string(unsigned char *str);
void put_char(unsigned char c);
unsigned char get_char(void);
unsigned char get_key(void);
void put_float(float x,int n) ;
void get_string(unsigned char *str,unsigned char num);
void Uart_test(void);




#endif