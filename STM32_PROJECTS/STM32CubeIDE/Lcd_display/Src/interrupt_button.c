/*
 * interrupt_button.c
 *
 *  Created on: 01-Dec-2025
 *      Author: yerra
 */


#include<string.h>

#include "stm32f411cexx.h"

volatile int temp=0;

void delay(void)
{
	for(int i =0; i<=50000; i++);
}

int main()
{
    GPIO_Handle_t Button,Led1, Led2, Led3;

    memset(&Button,0,sizeof(Button));
    memset(&Led1,0,sizeof(Led1));
    memset(&Led2,0,sizeof(Led2));
    memset(&Led3,0,sizeof(Led3));

    Button.pGPIOx = GPIOA;
    Button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    Button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    Button.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_PIN_PU;
    Button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIO_PeriClockControl(GPIOA,ENABLE);
    GPIO_Init(&Button);


    Led1.pGPIOx = GPIOA;
    Led1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
    Led1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    Led1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    Led1.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
    Led1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIO_PeriClockControl(GPIOA,ENABLE);
    GPIO_Init(&Led1);


  	Led2.pGPIOx = GPIOA;
    Led2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    Led2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    Led2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    Led2.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
    Led2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIO_PeriClockControl(GPIOA,ENABLE);
    GPIO_Init(&Led2);



    Led3.pGPIOx = GPIOA;
    Led3.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    Led3.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    Led3.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    Led3.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
    Led3.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIO_PeriClockControl(GPIOA,ENABLE);
    GPIO_Init(&Led3);



    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_1, GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_2, GPIO_PIN_RESET);
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_3, GPIO_PIN_RESET);

    GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, NVIC_IRQ_PRI15); //create the priority Optional
    GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);  //i used pb5

while(1);

}

void EXTI0_IRQHandler(void)
{
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_0);
	if(GPIO_ReadFromInputPin(GPIOA,GPIO_PIN_NO_0) == 1){
	temp++;
	}

	if(temp == 1){
    	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_1, GPIO_PIN_SET);
	}
	else if(temp == 2){
		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_2, GPIO_PIN_SET);
	}
	else if(temp == 3){
		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_3, GPIO_PIN_SET);
	}
	else {
		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_1, GPIO_PIN_RESET);
		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_2, GPIO_PIN_RESET);
		GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_3, GPIO_PIN_RESET);

		temp = 0;
	}

}
