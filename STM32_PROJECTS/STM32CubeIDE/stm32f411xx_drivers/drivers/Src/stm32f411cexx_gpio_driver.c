/*
 * stm32f411cexx_gpio_driver.c
 *
 *  Created on: Oct 17, 2025
 *      Author: yerra
 */

#include "stm32f411cexx_gpio_driver.h"


/*
 * Peripheral clock Setup
 */
/***************************************************************
 * @fn            GPIO_Init
 *
 * @brief         -This function enable or disable peripheral clock for the given GPIO port
 *
 * @parm[in]      - base addres of the gpio peripherals
 * @parm[in]      - Enable disable Macros
 * @parm[in]
 *
 * @return        -none
 *
 * @note          -none
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	 if(EnorDi == ENABLE)
	 {
		 if(pGPIOx == GPIOA)
		 {
			GPIOA_PCLK_EN();
		 }
		 else if(pGPIOx == GPIOB)
		 {
			GPIOB_PCLK_EN();
		 }
		 else if(pGPIOx == GPIOC)
		 {
			GPIOC_PCLK_EN();
		 }
		 else if(pGPIOx == GPIOD)
		 {
			GPIOD_PCLK_EN();
		 }
		 else if(pGPIOx == GPIOE)
		 {
			GPIOE_PCLK_EN();
		 }
		 else if(pGPIOx == GPIOH)
		 {
			GPIOH_PCLK_EN();
		 }
	 }
	 else {
		 //1000
		 if(pGPIOx == GPIOA)
				 {
					GPIOA_PCLK_DI();
				 }
				 else if(pGPIOx == GPIOB)
				 {
					GPIOB_PCLK_DI();
				 }
				 else if(pGPIOx == GPIOC)
				 {
					GPIOC_PCLK_DI();
				 }
				 else if(pGPIOx == GPIOD)
				 {
					GPIOD_PCLK_DI();
				 }
				 else if(pGPIOx == GPIOE)
				 {
					GPIOE_PCLK_DI();
				 }
				 else if(pGPIOx == GPIOH)
				 {
					GPIOH_PCLK_DI();
				 }
	 }

}
/*
 * GPIO Init and DeInit
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp=0; //temp.register

	//Enable the peripheral clock
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);


	//1.  Configure the mode of the gpio pin

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)  //this will deside the non interrupt and interrupt
	{
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));  //output, pin5 (1 x (2 x 5))
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // clearing the bit position
		pGPIOHandle->pGPIOx->MODER |= temp;// Setting the Bit position
		temp = 0;

	}else
	{
		//this part will code (interrupt _mode)
		// 1. (FALLING EDGE AND RISING EDGE SELECTION TRIGGER REGISTER)

		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			//Configure the FTSR
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// Clear  the Corresponding RTSR bit
			EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			//Configure the RTSR(RISING TRIGGER SELECTION REGISTER)
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// Clear  the Corresponding RTSR bit
			EXTI->RTSR &= ~( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			//Configure the RFT(RISING AND FALLING )
			//Configure the RTSR
			EXTI->FTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// Clear  the Corresponding RTSR bit
			EXTI->RTSR |= ( 1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}

		//2. configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

		/* 3. Enable the EXTI interrupt  delivery using IMR(Interrupt mask register)
		Purpose: The EXTI_IMR determines which external interrupt lines can generate an interrupt request to the NVIC (Nested Vectored Interrupt Controller).
		🔹 Bit-level control: Each bit in the register corresponds to one EXTI line.
		If a bit is set to 1, the interrupt request from that line is unmasked (enabled).
		If a bit is 0, the interrupt request is masked (disabled).
		*/
		EXTI->IMR |= 1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	}

	temp=0;

	// 2.  configure the speed

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2* pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // clearing the bit position
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;

	// 3. configure the push pull setting
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdcontrol << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // clearing the bit position
	pGPIOHandle->pGPIOx->PUPDR |= temp;


	temp = 0;

	// 4. configure the output type
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clearing the bit position
	pGPIOHandle->pGPIOx->OTYPER |= temp;


	temp = 0;


	//5. configure the alternate function

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		//configure the alternative registers.
		uint8_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2 )); //clearing the bits
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2 ));
	}

}



void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){

			 if(pGPIOx == GPIOA)
			 {
				GPIOA_REG_RESET();
			 }
			 else if(pGPIOx == GPIOB)
			 {
				GPIOB_REG_RESET();
			 }
			 else if(pGPIOx == GPIOC)
			 {
				GPIOC_REG_RESET();
			 }
			 else if(pGPIOx == GPIOD)
			 {
				GPIOD_REG_RESET();
			 }
			 else if(pGPIOx == GPIOE)
			 {
				GPIOE_REG_RESET();
			 }
			 else if(pGPIOx == GPIOH)
			 {
				GPIOH_REG_RESET();
			 }


}
/*
 * Data Read and Write
 */

/***************************************************************
 * @fn            READFromInputpin
 *
 * @brief         -
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	//every address have value
	uint8_t value;
	value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x00000001); // it right shifted to the first bit and read and remaining bit masked by the AND gate
	                // example pin8 (value  >> 8) & 0x000000001
	return value;

}

/*
 * Data Read and Write
 */

/***************************************************************
 * @fn            READFromInputport
 *
 * @brief         -
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
    value = (uint16_t) pGPIOx->IDR;
	return value;

}

/*
 * Data Read and Write
 */

/***************************************************************
 * @fn            GPIO_WriteToOutputPin
 *
 * @brief         -
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if(Value == GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1 << PinNumber);
	}else
	{
		//Write 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

/***************************************************************
 * @fn            GPIO_WriteToOutputPort
 *
 * @brief         -
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;

}

/***************************************************************
 * @fn            GPIO_ToggleOutputPin
 *
 * @brief         -
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	//pGPIOx->ODR = pGPIOx->ODR ^ (1 << PinNumber);
	 pGPIOx->ODR ^= (1 << PinNumber);

}
/*
 * IRQ configuration and IsR Handling
 */

/***************************************************************
 * @fn            GPIO_IRQInterrupt configuration
 *
 * @brief         - IT is communication between the peripheral to the arm cortex
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	//Configure the irq numbers
	if(EnorDi == ENABLE)
	{

		if(IRQNumber <= 31)
		{
			//program ISER0 Register
			*NVIC_ISER0 |=(1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber < 64)
		{
			//program ISER1 Register 32 to 63
			*NVIC_ISER1 |=(1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			//program ISER2 Register 64 to 95
			*NVIC_ISER3 |=(1 << (IRQNumber % 64));
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			//ICER0 Register
			*NVIC_ICER0 |=(1 << IRQNumber);
		}
		else if (IRQNumber > 31 && IRQNumber < 64)
		{
			//ICER1 Register
			*NVIC_ICER1 |=(1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			//ICER2 Register
			*NVIC_ICER3 |=(1 << (IRQNumber % 64));
		}
	}

}
/***************************************************************
 * @fn            GPIO_IRQ priority configuration
 *
 * @brief         - 👉 NVIC = Interrupt controller
 *                  It decides which interrupt is more important
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	//priority
	//first find out hte ipr register you can find in Device generic user in arm cortexm4

	uint32_t iprx = IRQNumber / 4;
	uint32_t iprx_selection = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_selection) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}

/***************************************************************
 * @fn            GPIO_IRQhanling
 *
 * @brief         -
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */

void GPIO_IRQHandling(uint8_t PinNumber)
{
	//clear the EXTI pr register corresponding to the pin Number
	if(EXTI->PR & (1 << PinNumber))
	{
		//clear
		EXTI->PR |= (1 << PinNumber);
	}

}

