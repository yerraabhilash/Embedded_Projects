/*
 * 002_Led_push_blink.c
 *
 *  Created on: Oct 28, 2025
 *      Author: yerra
 */


#include "stm32f411cexx.h"

#define LOW 0
#define BTN_PRESSED LOW

void delay(void)
{
	for(int i=0; i<=500000/2; i++);
}

int main(void)
{
	GPIO_Handle_t GPIOled, GPIOButton;

	GPIOled.pGPIOx = GPIOC;

	GPIOled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIOled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOled.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOC,ENABLE);

	GPIO_Init(&GPIOled);

	GPIOButton.pGPIOx = GPIOB;

	GPIOButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIOButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOButton.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_PIN_PU;

		GPIO_PeriClockControl(GPIOB,ENABLE);

		GPIO_Init(&GPIOButton);

		while(1)
		{
			if(GPIO_ReadFromInputPin(GPIOB,GPIO_PIN_NO_12) == BTN_PRESSED)
			{
				delay();
				GPIO_ToggleOutputPin(GPIOC,GPIO_PIN_NO_14);

			}
		}

return 0;

}
