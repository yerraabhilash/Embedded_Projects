/*
 * stm32f411cexx_rcc_driver.h
 *
 *  Created on: 26-Feb-2026
 *      Author: yerra
 */

#ifndef INC_STM32F411CEXX_RCC_DRIVER_H_
#define INC_STM32F411CEXX_RCC_DRIVER_H_


#include "stm32f411cexx.h"


//this returm apb1 colck value
uint32_t RCC_GetPCLK1Value(void);

//This REruturn APB2 value
uint32_t RCC_GetPCLK2Value(void);


uint32_t RCC_GetPLLOutputClk();

#endif /* INC_STM32F411CEXX_RCC_DRIVER_H_ */
