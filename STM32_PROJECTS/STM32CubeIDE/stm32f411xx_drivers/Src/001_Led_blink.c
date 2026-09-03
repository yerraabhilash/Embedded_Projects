/*
 * 001_Led_blink.c
 *
 *  Created on: Oct 23, 2025
 *      Author: yerra
 */
#include "stm32f411cexx.h"

// USE PUSHPULL CONFIGURATION FOR THE OUTPUT PIN


void delay(void)
{
	for(uint32_t i =0; i<500000;i++);

}

int main(void)
{
	GPIO_Handle_t Gpioled;

	Gpioled.pGPIOx = GPIOC;
	Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Gpioled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpioled.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;




	GPIO_Init(&Gpioled);

	while(1)
	{
		GPIO_ToggleOutputPin(GPIOC,GPIO_PIN_NO_13);
		delay();

	}


}


