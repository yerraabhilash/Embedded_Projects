/*
 * stm32f411cexx_spi_driver.h
 *
 *  Created on: 20-Dec-2025
 *      Author: yerra
 */

#ifndef INC_STM32F411CEXX_SPI_DRIVER_H_
#define INC_STM32F411CEXX_SPI_DRIVER_H_


#include "stm32f411cexx.h"


/*
 * Configuration Structure for SPIx peripherals
 */
typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;

}SPI_Config_t;

/*
 * Handle structure for SPIx peripherals
 */

typedef struct
{
	SPI_RegDef_t   *pSPIx;      /*this holds the base addres of SPIx   */
	SPI_Config_t    SPIConfig;  /*this holds the base addres of SPIx   */
	uint8_t        *pTxBuffer;  /*To store the app. Tx buffer address   */
	uint8_t        *pRxBuffer;  /*To store the app. Rx buffer address   */
	uint32_t        TxLen;      /*To store the tx len   */
	uint32_t        RxLen;      /* To store the Rx len   */
	uint8_t         TxState;    /*To store Tx state   */
	uint8_t         RxState;    /*To store Rx state   */
}SPI_Handle_t;

/*
 * SPI application state
 */
#define SPI_READY           0
#define SPI_BUSY_IN_RX      1
#define SPI_BUSY_IN_TX      2


/*
 * Possible SPI Application events
 */
#define SPI_EVENT_TX_CMPLT   1
#define SPI_EVENT_RX_CMPLT   2
#define SPI_EVENT_OVR_ERR    3
#define SPI_EVENT_CRC_CMPLT  4


/*
 * @SPI_DeviceMode
 * configure this bit in SPI_CR1 -> MSTR (master selection)
 */
#define SPI_DEVICE_MODE_MASTER      1
#define SPI_DEVICE_MODE_SLAVE       0

/*
 * @SPI_BusConfig
 * configure this bit in SPI_CR1 -> BIDIMODE ( Bidirectional data mode enable)
 * which means 0 -> 2 line unidirectional (FULL duplex)
 * 1 -> 1 line bidirectional mode (half duplex)
 * when the select 1 line (bidi-mode, don't use when select 2 line
 * you can configure CR1 -> BIDIOE (output enable in bidirectional mode)
 * 0 -> output disabled (receive only)
 * 1 -> enable (transmit only)
 *
 * when master is generate cock when mosi line enable otherwise below process will do
 * this field is very important when selct 2 line unidirectional
 * configure CR1 -> RXONLY (Receive only)
 * 0-> Fullduplex
 * 1 -> Output disabled(Receive only) (simplex receive only)
 * when the simplex transmit only just disconnect the MISO line
 */

#define SPI_BUS_CONFIG_FD                         1     /**                     FULL DUPLEX             */
#define SPI_BUS_CONFIG_HD                         2     /**                     HALF DUPLEX             */
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY             3     /**                     SIMPLEX RECEIVE ONLY           */



/*
 * @SPI_SclkSpeed
 * bit configure in CR1 -> BR(baud rate) intially 16Mhz in HSI
 */
#define SPI_SCLK_SPEED_DIV2                       0
#define SPI_SCLK_SPEED_DIV4                       1
#define SPI_SCLK_SPEED_DIV8                       2
#define SPI_SCLK_SPEED_DIV16                      3
#define SPI_SCLK_SPEED_DIV32                      4
#define SPI_SCLK_SPEED_DIV64                      5
#define SPI_SCLK_SPEED_DIV128                     6
#define SPI_SCLK_SPEED_DIV256                     7

/*
 * @SPI_DFF
 * by default it should be 0-> 8 bit data frame
 * CR1 -> DFF (data Frame Format)
 */
#define SPI_DFF_8BITS                            0
#define SPI_DFF_16BITS                           1

/*
 * @SPI_CPOL
 * 0->CK to 0 when idle
 *
 */
#define SPI_CPOL_HIGH            1
#define SPI_CPOL_LOW             0



/*
 * @SPI_CPHA
 *  default 0-> first clock transition
 */
#define SPI_CPHA_HIGH            1
#define SPI_CPHA_LOW             0

/*
 * @SPI_SSM
 * by default software slave management disabled
 *  CR1 -> SSM (software slave management enable and disabled)
 */
#define SPI_SSM_EN               1
#define SPI_SSM_DI               0   // by zero default



/*
 * SPI  related status flags definition
 */

#define SPI_TXE_FLAG    (1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG   (1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG   (1 << SPI_SR_BSY)



/***********************************************************************************************************
 *                                               APIs supported by this driver
 *                                  for more information about the APIs check the function definitions
 *******************************************************************************************************************/

/*
 * Peripheral clock Setup
 */
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);


/*
 * GPIO Init and DeInit
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);


/*
 * we implemented blocking and non blocking and interrupt based and DMA based
 * Data Send and Receive
 */
// blocking
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

//Send and receive in interrupt mode
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);



/*
 * IRQ configuration and ISR Handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

/*
 * Other Peripheral control APIs
 */

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

/*
 * flag
 */
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

/*
 * Application call back
 */

void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv);


#endif /* INC_STM32F411CEXX_SPI_DRIVER_H_ */
