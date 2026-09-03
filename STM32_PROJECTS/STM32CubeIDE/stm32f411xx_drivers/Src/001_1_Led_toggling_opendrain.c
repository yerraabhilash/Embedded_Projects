/*
 * 001_1_Led_toggling_opendrain.c
 *
 *  Created on: 11-Apr-2026
 *      Author: yerra
 */


#include "stm32f411cexx.h"

/*
 * open drain configuration with external pull up resister
 *
 * in this configuration internal led is connected anode is connected to the vcc and cathode is connected to the ground
 * then input 0 it is turn ON because the pin is connected to the ground
 * input is 1 in open drain it is floating
 */


void delay(void)
{
	for(uint32_t i =0; i<500000;i++);

}

int main(void)
{
	GPIO_Handle_t Gpioled, gpiobtn;

	Gpioled.pGPIOx = GPIOC;
	Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	Gpioled.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpioled.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Gpioled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	Gpioled.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_Init(&Gpioled);

	gpiobtn.pGPIOx = GPIOA;
	gpiobtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	gpiobtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	gpiobtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpiobtn.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_PIN_PU;
	GPIO_Init(&gpiobtn);





	while(1)
	{
		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) == RESET)
		{
			GPIO_ToggleOutputPin(GPIOC,GPIO_PIN_NO_13);
			delay();
		}


	}


}
