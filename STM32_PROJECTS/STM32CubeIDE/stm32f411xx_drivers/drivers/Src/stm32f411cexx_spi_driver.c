/*
 * stm32f411cexx_spi_driver.c
 *
 *  Created on: 20-Dec-2025
 *      Author: yerra
 */
#include "stm32f411cexx_spi_driver.h"


static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);




/***************************************************************
 * @fn            SPI_Clock configuration
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
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	 if(EnorDi == ENABLE)
	 {
		 if(pSPIx == SPI1)
		 {
			SPI1_PCLK_EN();
		 }
		 else if(pSPIx == SPI2)
		 {
			SPI2_PCLK_EN();
		 }
		 else if(pSPIx == SPI3)
		 {
			SPI3_PCLK_EN();
		 }
	 }
	 else {
		 //1000
		 if(pSPIx == SPI1)
		 {
			SPI1_PCLK_DI();
		 }
		 else if(pSPIx == SPI2)
		 {
			SPI2_PCLK_DI();
		 }
		 else if(pSPIx == SPI3)
		 {
			SPI3_PCLK_DI();
		 }
	 }
}

/***************************************************************
 * @fn                SPI initialization
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

void SPI_Init(SPI_Handle_t *pSPIHandle)
{

	//peripheral clock enable

	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	//First lets configure the SPI_CR! register

	uint32_t tempreg = 0;

	//1. Configure the device mode CR1->MSTR
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	//2. Configure the Bus config  CR1->BIDIMODE (full duplex or half duplex and simplex
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//BIDI mode should be cleared
		tempreg &= ~(1<<SPI_CR1_BIDIMODE);

	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//BD mode should be set
		tempreg |= (1<<SPI_CR1_BIDIMODE);

	}else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		//BIDI mode should be  cleared
		tempreg &= ~(1 << SPI_CR1_BIDIMODE);
		//RXONLY bit must be set
		tempreg |= (1 << SPI_CR1_RXONLY);
	}

	//3. Configure the the spi serial clock speed (baud rate)  CR1->BR[2:0]
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	//j4. Configure DFF CR1->DFF (data format 8 or 16)
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	//5. Configure the CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	//6. Configure the CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	//7. configure the software slave management CR1-SSM (by default it was enable
	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 = tempreg; //saved above details in CR1 register using assignment operator

}




/***************************************************************
 * @fn            - SPI DeInit
 *
 * @brief         -
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]      -
 *
 * @return        -0 or 1
 *
 * @note          -none
 */

void SPI_DeInit(SPI_RegDef_t *pSPIx){

	 if(pSPIx == SPI1)
	 {
		SPI1_REG_RESET();
	 }
	 else if(pSPIx == SPI2)
	 {
		SPI2_REG_RESET();
	 }
	 else if(pSPIx == SPI3)
	 {
		SPI3_REG_RESET();
	 }

}


uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

/***************************************************************
 * @fn            SPI_SendData
 *
 * @brief         -
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          - This is Blocking call
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)   // this called blocking calls in interrupt we didn't use
	{
		//Wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET); //SPI_GetFlagStatus = 0 which means    0 == 0 → TRUE(Loop continues (waiting)

		//2. Check the DFF bit in CR1
		if((pSPIx->CR1 & (1 << SPI_CR1_DFF)))
		{
			//16 bit DFF
			//1. Load the data into  the DR
			pSPIx->DR = *((uint16_t*)pTxBuffer);
			Len--;
			Len--;
			(uint16_t*)pTxBuffer++;
		}else
		{
			//8bit_DFF
			pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}
}





/***************************************************************
 * @fn            SPI_ReceiveDate
 *
 * @brief         - when enter into the function length is 0  exit the function
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		//Wait until RXNE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);

		//2. Check the DFF bit in CR1
		if((pSPIx->CR1 & (1 << SPI_CR1_DFF)))
		{
			//16 bit DFF
			//1. Load the data from DR to Rxbuffer address
			*((uint16_t*)pRxBuffer) = pSPIx->DR;
			Len--;
			Len--;
			(uint16_t*)pRxBuffer++;
		}else
		{
			//8bit_DFF
			*(pRxBuffer) = pSPIx->DR;
			Len--;
			pRxBuffer++;
		}
	}
}



/***************************************************************
 * @fn            SPE (SPI Enable)
 *
 * @brief         - 1 -> Peripheral Enable other wise Disable
 *                    you can tranfer the data using the SPI firstly enable this bit in CR1->SPE ==set
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */
void  SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	//
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);

	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}


/***************************************************************
 * @fn            SPI == Internal Slave Select(This bit is set, when NSS pin input is replaced with the value from SSI
 *
 * @brief         - when enter into the function length is 0  exit the function
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	// internally NSS is connected to the +VDD
	//other wise MODF error (mode foult error) will set and MSTR is disable
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);

	}else
	{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

/***************************************************************
 * @fn            SSOE - Software Slave Output Enable
 *
 * @brief         - For Master:
NSS output will be enable when SSOE = 1(Software Slave Output Enable)
when SSOE = 1
NSS=0;, when SPE=1 (NSS Pulled to low automatically when yu enable  the peripheral)
NSS = 1, when SPE=0;
 *
 * @parm[in]      -
 * @parm[in]      -
 * @parm[in]
 *
 * @return        -0 or 1
 *
 * @note          -none
 */
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	//
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);

	}else
	{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}


/*
 * IRQ configuration and IsR Handling
 */

/***************************************************************
 * @fn            SPI_IRQInterrupt configuration
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
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
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
			//ICER1
			*NVIC_ICER1 |=(1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96)
		{
			//ICER2
			*NVIC_ICER3 |=(1 << (IRQNumber % 64));
		}
	}

}


/***************************************************************
 * @fn            SPI_IRQ priority configuration
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

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
	//priority
	//first find out hte ipr register you can find in Device generic user in arm cortexm4

	uint32_t iprx = IRQNumber / 4;
	uint32_t iprx_selection = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_selection) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + (iprx)) |= (IRQPriority << shift_amount);
}



/***************************************************************
 * @fn            SPI_IRQhanling
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
 *

void SPI_IRQHandling(uint8_t PinNumber)
{
	//clear the EXTI pr register corresponding to the pin Number
	if(EXTI->PR & (1 << PinNumber))
	{
		//clear
		EXTI->PR |= (1 << PinNumber);
	}

}
*/

/***************************************************************
 * @fn            SPI_SEND AND RECEIVE IN INTERRUPT MODE
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

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t state = pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_RX)
	{
		//1. Save the TX buffer address and Len information in some Global veriable
		pSPIHandle->pRxBuffer = pTxBuffer;
		pSPIHandle->TxLen = Len;

		//2. Mark the SPI state as busy in transmission so that no matter code can take over same SPI peripherals until transmission is over
		pSPIHandle->TxState = SPI_BUSY_IN_TX;

		//3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);

		//4. Data Transmission will be handle by the code (will implement later)

	}

	return state;
}


/***************************************************************
 * @fn            SPI_SEND AND RECEIVE IN INTERRUPT MODE
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
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t state = pSPIHandle->RxState;

	if(state != SPI_BUSY_IN_RX)
	{
		//1. Save the RX buffer address and Len information in some Global veriable
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen = Len;

		//2. Mark the SPI state as busy in transmission so that no matter code can take over same SPI peripherals until transmission is over
		pSPIHandle->RxState = SPI_BUSY_IN_RX;

		//3. Enable the RXNEIE control bit to get interrupt whenever TXE flag is set in SR
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);

		//4. Data Transmission will be handle by the code (will implement later)

	}

	return state;
}



/***************************************************************
 * @fn            - SPI Interrupt handling code
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
void SPI_IRQHandling(SPI_Handle_t *pHandle)
{
	//todo
	uint8_t temp1, temp2;
	//first lets check the TXE
	temp1 = pHandle->pSPIx->SR & ( 1 << SPI_SR_TXE);
	temp2 = pHandle->pSPIx->CR2 & ( 1 << SPI_CR2_TXEIE);

	if(temp1 && temp2)    // if temp 1 and 2 both are true
	{
		//handle TXE_____when the txe interrupt occurred
		spi_txe_interrupt_handle(pHandle);
	}

	//first lets check the RXnE
	temp1 = pHandle->pSPIx->SR & ( 1 << SPI_SR_RXNE);
	temp2 = pHandle->pSPIx->CR2 & ( 1 << SPI_CR2_RXNEIE);

	if(temp1 && temp2)
	{
		//handle RXE
		spi_rxne_interrupt_handle(pHandle);
	}

	//first lets check the OVR
	temp1 = pHandle->pSPIx->SR & ( 1 << SPI_SR_OVR);
	temp2 = pHandle->pSPIx->CR2 & ( 1 << SPI_CR2_ERRIE);

	if(temp1 && temp2)
	{
		//handle TXE
		spi_ovr_err_interrupt_handle(pHandle);
	}

}


/*
 * Sum Helper function implementation
 */

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{

	//2. Check the DFF bit in CR1
	if((pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF)))
	{
		//16 bit DFF
		//1. Load the data into  the DR
		pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		pSPIHandle->TxLen--;
		(uint16_t*)pSPIHandle->pTxBuffer++;
	}else
	{
		//8bit_DFF
		pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
		pSPIHandle->TxLen--;
        pSPIHandle->pTxBuffer++;
	}

	if(! pSPIHandle->TxLen)
	{
		//TxLen is zero, so close the spi communication and inform the application that TX is Over

		//this prevents interrupt from setting up of TXE flag
		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
	}
}


static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{

	//2. Check the DFF bit in CR1
	if((pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF)))
	{
		//16 bit DFF
		//1. Load the data into  the DR
		*((uint16_t*)pSPIHandle->pRxBuffer) = (uint16_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->pRxBuffer--;
		pSPIHandle->pRxBuffer--;
	}else
	{
		//8bit_DFF
		*(pSPIHandle->pRxBuffer) = (uint8_t) pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->pRxBuffer--;
	}

	if(! pSPIHandle->RxLen)
	{
		//Reception is completed

		//lets turn off the rxneie interrupt
		SPI_CloseReception(pSPIHandle);

		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
	}
}


static  void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;
	//1. clear the ovr flag
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle->pSPIx->DR;
		temp = pSPIHandle->pSPIx->DR;
	}
	(void)temp;

	//2. inform the application
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);

}




void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	//
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);
	pSPIHandle->pTxBuffer = NULL;
	pSPIHandle->TxLen = 0;
	pSPIHandle->TxState = SPI_READY;
}
void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
	//
	//lets turn off the rxneie interrupt
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
	pSPIHandle->pRxBuffer = NULL;
	pSPIHandle->RxLen = 0;
	pSPIHandle->RxState = SPI_READY;
}


void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	uint8_t temp;
	temp = pSPIx->DR;
	temp = pSPIx->SR;
	(void)temp;
}


__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv)
{
	//This is a week implementation. the application may override this function.



}











