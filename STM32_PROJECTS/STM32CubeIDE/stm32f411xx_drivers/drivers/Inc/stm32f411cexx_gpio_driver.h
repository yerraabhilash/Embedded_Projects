/*
 * stm32f411cexx_gpio_driver.h
 *
 *  Created on: Oct 17, 2025
 *      Author: yerra
 */

#ifndef INC_STM32F411CEXX_GPIO_DRIVER_H_
#define INC_STM32F411CEXX_GPIO_DRIVER_H_

#include "stm32f411cexx.h"


/*
 * this is Configuration for a GPIO pin
 */

typedef struct{
	uint8_t GPIO_PinNumber;       /*!< possible values from @GPIO_PIN_NUMBER >*/
	uint8_t GPIO_PinMode;         /*!< possible values from @GPIO_PIN_MODES >*/
	uint8_t GPIO_PinSpeed;        /*!< possible values from @GPIO_PIN_SPEED >*/
	uint8_t GPIO_PinPuPdcontrol;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;




/*
 * This is Handle structure for a GPIO pin
 */

typedef struct{
	//pointer to hold the base address of the GPIO peripheral
	GPIO_RegDef_t *pGPIOx; //This holds the base address of the GPIO port to which the pin belongs
    GPIO_PinConfig_t GPIO_PinConfig; //this is holds GPIO pin configuration Setting

}GPIO_Handle_t;


/*
 * @GPIO_PIN_MODES
 * GPIO INPUT pin possible
 */
//NON INTERRUPT MODES
#define GPIO_MODE_IN       0
#define GPIO_MODE_OUT      1
#define GPIO_MODE_ALTFN    2
#define GPIO_MODE_ANALOG   3
// BELOW INTERRUPT MODES
#define GPIO_MODE_IT_FT    4  //FALLING
#define GPIO_MODE_IT_RT    5  //RISING EDGE
#define GPIO_MODE_IT_RFT   6  //RISING EDGE AND FALING EDGE TRIGGER

/*
 * GPIO OUTPUT pin possible
 */
#define GPIO_OP_TYPE_PP    0    // push pull type
#define GPIO_OP_TYPE_OD    1    //output type open drain

/*
 * @GPIO_PIN_SPEED
 * GPIO OUTPUT pin possible output speeds
 */
#define GPIO_SPEED_LOW         0
#define GPIO_SPEED_MEDIUM      1
#define GPIO_SPEED_FAST        2
#define GPIO_SPEED_HIGH        3


/*
 * GPIO pin pull up And pull down configuration macros
 */
#define GPIO_NO_PUPD             0    // NO PULL UP AND PULL DOWN
#define GPIO_PIN_PU              1    // PULL UP
#define GPIO_PIN_PD              2    // PULL DOWN

/*
 * @GPIO_PIN_NUMBER
 * GPIO pin numbers
 */
#define GPIO_PIN_NO_0              0
#define GPIO_PIN_NO_1              1
#define GPIO_PIN_NO_2              2
#define GPIO_PIN_NO_3              3
#define GPIO_PIN_NO_4              4
#define GPIO_PIN_NO_5              5
#define GPIO_PIN_NO_6              6
#define GPIO_PIN_NO_7              7
#define GPIO_PIN_NO_8              8
#define GPIO_PIN_NO_9              9
#define GPIO_PIN_NO_10             10
#define GPIO_PIN_NO_11             11
#define GPIO_PIN_NO_12             12
#define GPIO_PIN_NO_13             13
#define GPIO_PIN_NO_14             14
#define GPIO_PIN_NO_15             15





/**********************************************************************
 *                                APIs Supported by this driver
 *              for more information about the APIs check the function definition
 ************************************************************************/

/*
 * Peripheral clock Setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);


/*
 * GPIO Init and DeInit
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);


/*
 * Data Read and Write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);



/*
 * IRQ configuration and IsR Handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);












#endif /* INC_STM32F411CEXX_GPIO_DRIVER_H_ */
