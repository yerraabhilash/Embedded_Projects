/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "stm8s.h"

#define LED GPIOC, GPIO_PIN_7


void delay(void) //Function Definition 
{
int i=0,j=0;
for (i=0; i<=200; i++)
  {
		for (j=0; j<120; j++) // Nop = Fosc/4
_asm("nop"); //Perform no operation 
  //assembly code <span style="white-space:pre"> </span>
	}
}


void main()
{
	
	GPIO_Init(LED, GPIO_MODE_OUT_PP_HIGH_FAST);
	
	while (1)
	{
		GPIO_WriteReverse(LED);
		delay();
	}
}