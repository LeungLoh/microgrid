#include "sysclk_4M.h"

void ucsclk_Init (unsigned char frequent)
{ 
  P5SEL |= BIT2+BIT3;                           // Port select XT2
  UCSCTL6 &= ~XT2OFF;                           // Enable XT2 
  UCSCTL6 &= ~XT2BYPASS;                        // XT2ÓÉ¾§Õñ²úÉú
  UCSCTL6 &= ~XT2DRIVE0;                        // Decrease XT2 Drive according to

  UCSCTL3 |= SELREF_5;                          // FLLref = XT2
                                                // Since LFXT1 is not used,
                                                // sourcing FLL with LFXT1 can cause
                                                // XT1OFFG flag to set
  UCSCTL4 |= SELA_2;                            // ACLK=REFO,SMCLK=DCO,MCLK=DCO

   // Loop until XT2 fault flag is cleared
  do
  {
    UCSCTL7 &= ~XT2OFFG;                        // Clear XT1 fault flags
  }while (UCSCTL7&XT2OFFG);                     // Test XT1 fault flag

  __bis_SR_register(SCG0);                      // Disable the FLL control loop
  UCSCTL0 = 0x0000;                             // Set lowest possible DCOx, MODx


switch(frequent)
{
  case 4:
       UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2

                                            
      break;
      
  case 8:
      UCSCTL1 = DCORSEL_4;                       // Set RSELx for DCO = 9.5 MHz
      UCSCTL2 = FLLD_1 + 1;                      // Set DCO Multiplier for 8MHz
                                                 // Set FLL Div = fDCOCLK/2
                                                 // (1 + 1) * 4M = 8MHz
      __delay_cycles(2048);			 //32 x 32 x 8 MHz / 4M Hz = 2048 
                                            
      break;
  
  case 16:
      UCSCTL1 = DCORSEL_5;                       // Set RSELx for DCO = 24 MHz
      UCSCTL2 = FLLD_1 + 3;                      // Set DCO Multiplier for 16MHz
                                                 // Set FLL Div = fDCOCLK/2
                                                 // (3 + 1) * 4M = 16MHz
                                            
      __delay_cycles(4096);			 //32 x 32 x 16 MHz / 4M Hz = 4096 
      break;
   case 20:
      UCSCTL1 = DCORSEL_5;                       // Set RSELx for DCO = 24 MHz
      UCSCTL2 = FLLD_1 + 4;                      // Set DCO Multiplier for 16MHz
                                                 // Set FLL Div = fDCOCLK/2
                                                 // (3 + 1) * 4M = 16MHz
                                            
      __delay_cycles(5120);			 //32 x 32 x 16 MHz / 4M Hz = 4096 
      break;
  case 24:
      UCSCTL1 = DCORSEL_7;                       // Set RSELx for DCO = 24 MHz
      UCSCTL2 = FLLD_1 + 5;                      // Set DCO Multiplier for 16MHz
                                                 // Set FLL Div = fDCOCLK/2
                                                 // (3 + 1) * 4M = 16MHz
                                            
      __delay_cycles(6144);			 //32 x 32 x 16 MHz / 4M Hz = 4096 
      break;
   case 32:
      UCSCTL1 = DCORSEL_7;                       // Set RSELx for DCO = 24 MHz
      UCSCTL2 = FLLD_1 + 7;                      // Set DCO Multiplier for 16MHz
                                                 // Set FLL Div = fDCOCLK/2
                                                 // (3 + 1) * 4M = 16MHz
                                            
      __delay_cycles(8192);			 //32 x 32 x 16 MHz / 4M Hz = 4096 
      break;
   default :break;
  					

}
__bic_SR_register(SCG0);                         // Enable the FLL control loop


  // Loop until XT1,XT2 & DCO stabilizes - in this case loop until XT2 settles
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                                // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                          // Clear fault flags
  }while (SFRIFG1&OFIFG);                       // Test oscillator fault flag

  //UCSCTL6 &= ~XT2DRIVE0;                      // Decrease XT2 Drive according to
                                                // expected frequency

}