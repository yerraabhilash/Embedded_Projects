/*
 * stm32f411cexx.h
 *
 *  Created on: Oct 17, 2025
 *      Author: yerra
 */

#ifndef INC_STM32F411CEXX_H_
#define INC_STM32F411CEXX_H_

#include <stdint.h>
#define __vol  volatile


/*
 * Processor specification details
 * Arm cotex Mx processor NVIC ISERx register addresses
 */

#define NVIC_ISER0       ((__vol uint32_t*)0xE000E100)
#define NVIC_ISER1       ((__vol uint32_t*)0xE000E104)
#define NVIC_ISER2       ((__vol uint32_t*)0xE000E108)
#define NVIC_ISER3       ((__vol uint32_t*)0xE000E10C)

/*
 * ARM cortex Mx processor NVIC ICERx register Addresses
 */
#define NVIC_ICER0       ((__vol uint32_t*)0xE000E180)
#define NVIC_ICER1       ((__vol uint32_t*)0xE000E184)
#define NVIC_ICER2       ((__vol uint32_t*)0xE000E188)
#define NVIC_ICER3       ((__vol uint32_t*)0xE000E18C)


/*
 * ARM cortex Mx processor NVIC ICERx register Addresses
 */
#define NVIC_PR_BASE_ADDR  ((__vol uint32_t*)0xE000E400)


#define NO_PR_BITS_IMPLEMENTED      4
/*
 * Base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR 0x08000000U
#define SRAM_BASEADDR  0x20000000U
//#define SRAM1_BASEADDR 0x20000000U //112kb add and find SRAM2 by claculator
//#define SRAM2_BASEADDR 0x20001C00U //16KB add and you if applicable SRAM3 also
#define SYSTEM_ROM_BASEADDR 0x1FFF0000U

/*
 * APBX AND AHBX bus peripherals address
 */
#define PERIPH_BASEADDR       0x40000000U
#define AHB1PERIPH_BASEADDR   0x40020000U
#define AHB2PERIPH_BASEADDR   0x50000000U
#define APB1PERIPH_BASEADDR   PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR   0x40010000U

/*
 * base address of  peripherals which are hanging on AHB1 bus
 * TOO : complete for all other peripherals
 */

#define GPIOA_BASEADDR      (AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR      (AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR      (AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR      (AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR      (AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOH_BASEADDR      (AHB1PERIPH_BASEADDR + 0x1C00)

#define RCC_BASEADDR        (AHB1PERIPH_BASEADDR + 0x3800)
/*
 * base address of  peripherals which are hanging on APB1 bus
 * TOO : complete for all other peripherals
 */

#define I2C1_BASEADDR      (APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR      (APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR      (APB1PERIPH_BASEADDR + 0x5C00)

#define SPI2_BASEADDR      (APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_BASEADDR      (APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR    (APB1PERIPH_BASEADDR + 0x4400)


/*
 * base address of  peripherals which are hanging on APB2 bus
 * TOO : complete for all other peripherals
 */

#define EXTI_BASEADDR      (APB2PERIPH_BASEADDR + 0x3C00)
#define SPI1_BASEADDR      (APB2PERIPH_BASEADDR + 0x3000)
#define SYSCFG_BASEADDR    (APB2PERIPH_BASEADDR + 0x3800)
#define USART1_BASEADDR    (APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR    (APB2PERIPH_BASEADDR + 0x1400)



/******************* peripheral register defination *********************/
/*
 * Note: Registers of a peripheral are specific to MCU
 * eg: Number of Register of SPI peripherals of STM32F411XX family of MCUs be different (more or less)
 * Compare to number of registers of SPI peripherals of STM32f411
 * please check the device RM
 */

typedef struct{
	__vol uint32_t MODER;     /* GPIO port mode Register     Address offset: 0x00         */
	__vol uint32_t OTYPER;    /* TODO                        Address offset: 0x04         */
	__vol uint32_t OSPEEDR;     /* GPIO port mode Register     Address offset: 0x08         */
	__vol uint32_t PUPDR;     /* GPIO port mode Register     Address offset: 0x0C         */
	__vol uint32_t IDR;     /* GPIO port mode Register     Address offset: 0x00         */
	__vol uint32_t ODR;     /* GPIO port mode Register     Address offset: 0x00         */
	__vol uint32_t BSRR;     /* GPIO port mode Register     Address offset: 0x00         */
	__vol uint32_t LCKR;     /* GPIO port mode Register     Address offset: 0x00         */
	__vol uint32_t AFR[2];   /* AFR[0] GPIO Alternative function Low Register     AFR[1] GPIO Alternative function High Register    */

}GPIO_RegDef_t;

/*************************** RCC Peripheral Register defination *********************
 * Structure calculate the memory size each veriable alloted 4 byte becouse uint32_t takes 4 byte of memory
 *
 */

typedef struct{
	__vol uint32_t CR;
	__vol uint32_t PLLCFGR;
	__vol uint32_t CFGR;
	__vol uint32_t CIR;
	__vol uint32_t AHB1RSTR;
	__vol uint32_t AHB2RSTR;
	__vol uint32_t RESERVEDD0;
	__vol uint32_t RESERVEDD1;
	__vol uint32_t APB1RSTR;
	__vol uint32_t APB2RSTR;
	__vol uint32_t RESERVEDD2;
	__vol uint32_t RESERVEDD3;
	__vol uint32_t AHB1ENR;
	__vol uint32_t AHB2ENR;
	__vol uint32_t RESERVEDD4;
	__vol uint32_t RESERVEDD5;
	__vol uint32_t APB1ENR;
	__vol uint32_t APB2ENR;
	__vol uint32_t RESERVEDD6;
	__vol uint32_t RESERVEDD7;
	__vol uint32_t AHB1LPENR;
	__vol uint32_t AHB2LPENR;
	__vol uint32_t RESERVEDD8;
	__vol uint32_t RESERVEDD9;
	__vol uint32_t APB1LPENR;
	__vol uint32_t APB2LPENR;
	__vol uint32_t RESERVEDD10;
	__vol uint32_t RESERVEDD11;
	__vol uint32_t BDCR;
	__vol uint32_t CSR;
	__vol uint32_t RESERVEDD12;
	__vol uint32_t RESERVEDD13;
	__vol uint32_t SSCGR;
	__vol uint32_t PLLI2SCFGR;
	__vol uint32_t RESERVEDD14;
	__vol uint32_t DCKCFGR;

}RCC_RegDef_t;

/*
 * Peripheral register defination for EXTI
 */


typedef struct{
	__vol uint32_t IMR;     /*Interrupt mask register                 Address offset: 0x00         */
	__vol uint32_t EMR;    /* Event mask register                     Address offset: 0x04         */
	__vol uint32_t RTSR;     /*Rising trigger selection register      Address offset: 0x08         */
	__vol uint32_t FTSR;     /*falling trigger selection register     Address offset: 0x0C         */
	__vol uint32_t SWIER;     /* software interrupt event register    Address offset: 0x10         */
	__vol uint32_t PR;     /* Pending register                        Address offset: 0x14        */
}EXTI_RegDef_t;

/*
 * Peripheral register defination structure for SYSCFG
 */

typedef struct
{
	__vol uint32_t  MEMRMP;
	__vol uint32_t  PMC;
	__vol uint32_t  EXTICR[4];
	uint32_t RESERVED1[2];
	__vol uint32_t  CMPCR;
	uint32_t RESERVED2[2];
	__vol uint32_t  CFGR;


}SYSCFG_RegDef_t;



/*
 * Peripherals defination (Peripherals base addresses typecasted to xxx_RegDef_t)
 */

#define GPIOA  ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB  ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC  ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD  ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE  ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH  ((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC    ((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI   ((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG    ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)

/*
 * Clock Enable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_EN()    (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()    (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()    (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()    (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()    (RCC->AHB1ENR |= (1 << 4))
#define GPIOH_PCLK_EN()    (RCC->AHB1ENR |= (1 << 7))

/*
 * Clock Enable for I2C peripheral
 */

#define I2C1_PCLK_EN()    (RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()    (RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()    (RCC->APB1ENR |= (1 << 23))


/*
 * Clock Enabel for SPIx peripherals
 */
#define SPI1_PCLK_EN()    (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()    (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()    (RCC->APB1ENR |= (1 << 15))


/*
 * Clock Enable for UARTx Peripherals
 */

#define USART1_PCLK_EN()    (RCC->APB2ENR |= (1 << 4))
#define USART6_PCLK_EN()    (RCC->APB2ENR |= (1 << 5))

/*
 * Clock Enable Macros for SYSCFGx Peripherals
 */

#define SYSCFG_PCLK_EN()    (RCC->APB2ENR |= (1 << 14))


/*
 * Clock Desable Macros for GPIOx peripherals
 */

#define GPIOA_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 7))

/*
 * Clock desable for I2C peripheral
 */

#define I2C1_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 23))


/*
 * Clock Desabel for SPIx peripherals
 */
#define SPI1_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 15))


/*
 * Clock Desable for UARTx Peripherals
 */

#define USART1_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 4))
#define USART6_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 5))

/*
 * Clock dESABLE Macros for SYSCFGx Peripherals
 */

#define SYSCFG_PCLK_DI()    (RCC->APB2ENR &= &(1 << 14))


/*
 * Macros to reset GPIOx peripherals
 */
#define GPIOA_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 0));  (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 1));  (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 2));  (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 3));  (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 4));  (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOH_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 7));  (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)



/*
 * This macro is a C preprocessor macro that converts a GPIO peripheral base address (like GPIOA, GPIOB, etc.) into a numeric code (0, 1, 2, …).
 * It is commonly used in STM32 microcontroller drivers—especially when enabling peripheral clocks in RCC.
 * return port code for given GPIOx base address
 * To understand it more easily, imagine it as a function:

uint8_t GPIO_BASEADDR_TO_CODE(uint32_t x)
{
    if(x == GPIOA) return 0;
    else if(x == GPIOB) return 1;
    else if(x == GPIOC) return 2;
    else if(x == GPIOD) return 3;
    else if(x == GPIOE) return 4;
    else if(x == GPIOH) return 5;
    else return 0; // default
}
 */


#define GPIO_BASEADDR_TO_CODE(x)        ( (x == GPIOA) ? 0:\
		                                  (x == GPIOB) ? 1:\
				                          (x == GPIOC) ? 2:\
					                      (x == GPIOD) ? 3:\
		                                  (x == GPIOE) ? 4:\
				                          (x == GPIOH) ? 5:0)

/*
 * IRQ(Interrupt Request) Number of STM32F411CE
 * NOTE: Update these macros with valid values according to your MCU
 * TODO: you may complete this list for other peripherals
 */

#define IRQ_NO_EXTI0               6
#define IRQ_NO_EXTI1               7
#define IRQ_NO_EXTI2               8
#define IRQ_NO_EXTI3               9
#define IRQ_NO_EXTI4               10
#define IRQ_NO_EXTI9_5             23
#define IRQ_NO_EXTI15_10           40


/*
 * IRQ PRIORITY macros ALL THE POSIBLE
 */

#define NVIC_IRQ_PRI0       0
#define NVIC_IRQ_PRI1       1
#define NVIC_IRQ_PRI2       2
#define NVIC_IRQ_PRI3       3
#define NVIC_IRQ_PRI4       4
#define NVIC_IRQ_PRI5       5
#define NVIC_IRQ_PRI6       6
#define NVIC_IRQ_PRI7       7
#define NVIC_IRQ_PRI8       8
#define NVIC_IRQ_PRI9       9
#define NVIC_IRQ_PRI10      10
#define NVIC_IRQ_PRI11      11
#define NVIC_IRQ_PRI12      12
#define NVIC_IRQ_PRI13      13
#define NVIC_IRQ_PRI14      14
#define NVIC_IRQ_PRI15      15
#define NVIC_IRQ_PRI16      16
#define NVIC_IRQ_PRI17      17



/*
 * Some Generic Macros
 */
#define ENABLE           1
#define DISABLE          0
#define SET              ENABLE
#define RESET            DISABLE
#define GPIO_PIN_SET     SET
#define GPIO_PIN_RESET   RESET


#include "stm32f411cexx_gpio_driver.h"









#endif /* INC_STM32F411CEXX_H_ */
