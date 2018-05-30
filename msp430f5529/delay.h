#ifndef  DELAY_H
#define  DELAY_H

#include "msp430f5529.h"

#define CPU_F 1000000UL

#define delay_us(x) __delay_cycles(x*CPU_F/100000) 

#define delay_ms(x) __delay_cycles(x*CPU_F/100)

#endif