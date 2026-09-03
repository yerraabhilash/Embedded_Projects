/*
 * stm32f411cexx.h
 *
 *  Created on: Oct 17, 2025
 *      Author: yerra
 *      What is Device Header file and what it contains ?
This is a header file ('C' header file in our case) which contains Microcontroller specific details such as
1) The base addresses of various memories present in the microcontroller such as (Flash, SRAMI, SRAM2, ROM,etc)
2) The base addresses of various bus domains such as (AHBx domain, APBx domain)
3) Base addresses of various peripherals present in different bus domains of the microcontroller
4) Clock management macros (i.e clock enable and clock disable macros)
5) IRQ definitions
6) Peripheral Register definition structures
7) Peripheral register bit definitions
8) Other useful microcontroller configuration macros
 */

#ifndef INC_STM32F411CEXX_H_
#define INC_STM32F411CEXX_H_

#include <stdint.h>
#include <stddef.h>

#define __vol   volatile
#define __weak  __attribute__((weak))


/****************************************START:Processor specification details**********************************************
 * Arm cotex Mx processor NVIC ISERx register addresses
 * this is not find in reference manual you can find in cortex m4 generic user guied
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
 * calculation of priority register
 */
#define NVIC_PR_BASE_ADDR  ((__vol uint32_t*)0xE000E400)

/*
 * ARM cortex Mx processor number of priority  bits implemented in priority register
 * st have 4
 */
#define NO_PR_BITS_IMPLEMENTED      4
/*
 * Base addresses of Flash and SRAM memories
 */

#define FLASH_BASEADDR    0x08000000U          /***** you can find the base in reference manual page no 42********/
#define SRAM_BASEADDR     0x20000000U          /***** you can find the base in reference manual page no 42********/
#define SRAM              SRAM_BASEADDR
//#define SRAM1_BASEADDR 0x20000000U //112kb add and find SRAM2 by claculator
//#define SRAM2_BASEADDR 0x20001C00U //16KB add and you if applicable SRAM3 also
#define SYSTEM_ROM_BASEADDR 0x1FFF0000U


/*
 * APBX AND AHBX bus peripherals address
 */
#define PERIPH_BASEADDR       0x40000000U        /***** starting of the bus addresses start in reference manual P39 ********/
#define AHB1PERIPH_BASEADDR   0x40020000U        /***** starting of the bus addresses start in reference manual P39 ********/
#define AHB2PERIPH_BASEADDR   0x50000000U        /***** starting of the bus addresses start in reference manual P39 ********/
#define APB1PERIPH_BASEADDR   PERIPH_BASEADDR    /***** starting of the bus addresses start in reference manual P39 ********/
#define APB2PERIPH_BASEADDR   0x40010000U        /***** starting of the bus addresses start in reference manual P39 ********/

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
	__vol uint32_t MODER;      /* GPIO port mode Register     Address offset: 0x00         */
	__vol uint32_t OTYPER;     /* GPIO port mode Register     Address offset: 0x04         */
	__vol uint32_t OSPEEDR;    /* GPIO port mode Register     Address offset: 0x08         */
	__vol uint32_t PUPDR;      /* GPIO port mode Register     Address offset: 0x0C         */
	__vol uint32_t IDR;        /* GPIO port mode Register     Address offset: 0x10         */
	__vol uint32_t ODR;        /* GPIO port mode Register     Address offset: 0x14         */
	__vol uint32_t BSRR;       /* GPIO port mode Register     Address offset: 0x18         */
	__vol uint32_t LCKR;       /* GPIO port mode Register     Address offset: 0x1C         */
	__vol uint32_t AFR[2];  /* AFR[0] GPIO Alternative function Low Register AFR[1] GPIO Alternative function High Register*/

}GPIO_RegDef_t;

/*************************** RCC Peripheral Register defination *********************
 * Structure calculate the memory size each veriable alloted 4 byte becouse uint32_t takes 4 byte of memory
 *
 */

typedef struct{
	__vol uint32_t CR;              /* RCC clock register Register     Address offset: 0x00    */
	__vol uint32_t PLLCFGR;         /* RCC clock register Register     Address offset: 0x04    */
	__vol uint32_t CFGR;            /* RCC clock register Register     Address offset: 0x08    */
	__vol uint32_t CIR;             /* RCC clock register Register     Address offset: 0x0C    */
	__vol uint32_t AHB1RSTR;        /* RCC clock register Register     Address offset: 0x10    */
	__vol uint32_t AHB2RSTR;        /* RCC clock register Register     Address offset: 0x14    */
	__vol uint32_t RESERVEDD0;      /* RCC clock register Register     Address offset: 0x18    */
	__vol uint32_t RESERVEDD1;      /* RCC clock register Register     Address offset: 0x1C    */
	__vol uint32_t APB1RSTR;        /* RCC clock register Register     Address offset: 0x20    */
	__vol uint32_t APB2RSTR;        /* RCC clock register Register     Address offset: 0x14    */
	__vol uint32_t RESERVEDD2;      /* RCC clock register Register     Address offset: 0x28    */
	__vol uint32_t RESERVEDD3;      /* RCC clock register Register     Address offset: 0x2C    */
	__vol uint32_t AHB1ENR;         /* RCC clock register Register     Address offset: 0x30    */
	__vol uint32_t AHB2ENR;         /* RCC clock register Register     Address offset: 0x34    */
	__vol uint32_t RESERVEDD4;      /* RCC clock register Register     Address offset: 0x38    */
	__vol uint32_t RESERVEDD5;      /* RCC clock register Register     Address offset: 0x3C    */
	__vol uint32_t APB1ENR;         /* RCC clock register Register     Address offset: 0x40    */
	__vol uint32_t APB2ENR;         /* RCC clock register Register     Address offset: 0x44    */
	__vol uint32_t RESERVEDD6;      /* RCC clock register Register     Address offset: 0x48    */
	__vol uint32_t RESERVEDD7;      /* RCC clock register Register     Address offset: 0x4C    */
	__vol uint32_t AHB1LPENR;       /* RCC clock register Register     Address offset: 0x50    */
	__vol uint32_t AHB2LPENR;       /* RCC clock register Register     Address offset: 0x54    */
	__vol uint32_t RESERVEDD8;      /* RCC clock register Register     Address offset: 0x58    */
	__vol uint32_t RESERVEDD9;      /* RCC clock register Register     Address offset: 0x5C    */
	__vol uint32_t APB1LPENR;       /* RCC clock register Register     Address offset: 0x60    */
	__vol uint32_t APB2LPENR;       /* RCC clock register Register     Address offset: 0x64    */
	__vol uint32_t RESERVEDD10;     /* RCC clock register Register     Address offset: 0x68    */
	__vol uint32_t RESERVEDD11;     /* RCC clock register Register     Address offset: 0x6C    */
	__vol uint32_t BDCR;            /* RCC clock register Register     Address offset: 0x70    */
	__vol uint32_t CSR;             /* RCC clock register Register     Address offset: 0x74    */
	__vol uint32_t RESERVEDD12;     /* RCC clock register Register     Address offset: 0x78    */
	__vol uint32_t RESERVEDD13;     /* RCC clock register Register     Address offset: 0x7C    */
	__vol uint32_t SSCGR;           /* RCC clock register Register     Address offset: 0x80    */
	__vol uint32_t PLLI2SCFGR;      /* RCC clock register Register     Address offset: 0x84    */
	__vol uint32_t RESERVEDD14;     /* RCC clock register Register     Address offset: 0x88    */
	__vol uint32_t DCKCFGR;         /* RCC clock register Register     Address offset: 0x8C    */

}RCC_RegDef_t;

/*
 * Peripheral register definItion for EXTI EXTERNAL INTERRUPT
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
 * peripherals register definition structure for SPI
 */
typedef struct
{
	__vol uint32_t CR1;
	__vol uint32_t CR2;
	__vol uint32_t SR;
	__vol uint32_t DR;
	__vol uint32_t CRCPR;
	__vol uint32_t RXCRCR;
	__vol uint32_t TXCRCR;
	__vol uint32_t I2SCFRGR;
	__vol uint32_t I2SPR;
}SPI_RegDef_t;


/*
 * peripheral register definition structure for i2c
 */
typedef struct
{
	__vol uint32_t CR1;      /*!< TODO,   Address  */
	__vol uint32_t CR2;      /*!< TODO,   Address  */
	__vol uint32_t OAR1;      /*!< TODO,   Address  */
	__vol uint32_t OAR2;      /*!< TODO,   Address  */
	__vol uint32_t DR;      /*!< TODO,   Address  */
	__vol uint32_t SR1;      /*!< TODO,   Address  */
	__vol uint32_t SR2;      /*!< TODO,   Address  */
	__vol uint32_t CCR;      /*!< TODO,   Address  */
	__vol uint32_t TRISE;      /*!< TODO,   Address  */
	__vol uint32_t FLTR;      /*!< TODO,   Address  */
}I2C_RegDef_t;

/*
 * USART Registe defination structure
 */
typedef struct
{
	__vol uint32_t SR;      /*!< TODO,   Address  */
	__vol uint32_t DR;      /*!< TODO,   Address  */
	__vol uint32_t BRR;      /*!< TODO,   Address  */
	__vol uint32_t CR1;      /*!< TODO,   Address  */
	__vol uint32_t CR2;      /*!< TODO,   Address  */
	__vol uint32_t CR3;      /*!< TODO,   Address  */
	__vol uint32_t GTPR;      /*!< TODO,   Address  */

}USART_RegDef_t;






/*
 * Peripherals definition (Peripherals base addresses type casted to xxx_RegDef_t)
 */

#define GPIOA     ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB     ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC     ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD     ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE     ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH     ((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC       ((RCC_RegDef_t*)RCC_BASEADDR)

#define EXTI      ((EXTI_RegDef_t*)EXTI_BASEADDR)

#define SYSCFG    ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)


#define SPI1      ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2      ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3      ((SPI_RegDef_t*)SPI3_BASEADDR)


#define I2C1      ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2      ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3      ((I2C_RegDef_t*)I2C3_BASEADDR)

#define USART1      ((USART_RegDef_t*)USART1_BASEADDR)
#define USART2      ((USART_RegDef_t*)USART2_BASEADDR)
#define USART6      ((USART_RegDef_t*)USART6_BASEADDR)

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
#define USART2_PCLK_EN()    (RCC->APB1ENR |= (1 << 17))
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
#define USART2_PCLK_DI()    (RCC->APB1ENR &= ~(1 << 17))
#define USART6_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 5))

/*
 * Clock dESABLE Macros for SYSCFGx Peripherals
 */

#define SYSCFG_PCLK_DI()    (RCC->APB2ENR &= &(1 << 14))


/*
 * Macros to reset GPIOx peripherals
 *
 * do... while... condition zero loop:
 * this technique  in c  programming  to execute multiple c statement using c macro
 */
#define GPIOA_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 0));  (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 1));  (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 2));  (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 3));  (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 4));  (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOH_REG_RESET()      do{(RCC->AHB1RSTR |= (1 << 7));  (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)


/*
 * Macros to reset SPIx peripherals
 *
 * do... while... condition zero loop:
 * this technique  in c  programming  to execute multiple c statement using c macro
 */
#define SPI1_REG_RESET()      do{(RCC->APB2ENR |= (1 << 12));  (RCC->APB2ENR &= ~(1 << 12)); }while(0)
#define SPI2_REG_RESET()      do{(RCC->APB1ENR |= (1 << 14));  (RCC->APB1ENR &= ~(1 << 14)); }while(0)
#define SPI3_REG_RESET()      do{(RCC->APB1ENR |= (1 << 15));  (RCC->APB1ENR &= ~(1 << 15)); }while(0)



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

// this numbers find in nvic Vector table for STM32F411xC/E position(IRQ number)
#define IRQ_NO_EXTI0               6
#define IRQ_NO_EXTI1               7
#define IRQ_NO_EXTI2               8
#define IRQ_NO_EXTI3               9
#define IRQ_NO_EXTI4               10
#define IRQ_NO_EXTI9_5             23
#define IRQ_NO_EXTI15_10           40

#define IRQ_NO_SPI1                35
#define IRQ_NO_SPI2                36
#define IRQ_NO_SPI3                51
#define IRQ_NO_SPI4                84
#define IRQ_NO_SPI5                85


#define IRQ_NO_I2C1_EV             31
#define IRQ_NO_I2C1_ER             32




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
#define FLAG_RESET       RESET
#define FLAG_SET         SET


/**************************************************************************************
 * Bit Position definItion for peripherals
***************************************************************************************/

/*
 * Bit position definition of SPI_CR1
 */
#define SPI_CR1_CPHA            0
#define SPI_CR1_CPOL            1
#define SPI_CR1_MSTR            2
#define SPI_CR1_BR              3
#define SPI_CR1_SPE             6
#define SPI_CR1_LSBFIRST        7
#define SPI_CR1_SSI             8
#define SPI_CR1_SSM             9
#define SPI_CR1_RXONLY          10
#define SPI_CR1_DFF             11
#define SPI_CR1_CRCNEXT         12
#define SPI_CR1_CRCEN           13
#define SPI_CR1_BIDIOE          14
#define SPI_CR1_BIDIMODE        15

/*
 * Bit position definition of SPI_CR2
 */
#define SPI_CR2_RXDMAEN     0
#define SPI_CR2_TXDMAEN     1
#define SPI_CR2_SSOE        2
#define SPI_CR2_FRF         4
#define SPI_CR2_ERRIE       5
#define SPI_CR2_RXNEIE      6
#define SPI_CR2_TXEIE       7


/*
 * Bit position definition of SPI_CR2
 */
#define SPI_SR_RXNE    0
#define SPI_SR_TXE     1
#define SPI_SR_CHSIDE  2
#define SPI_SR_UDR     3
#define SPI_SR_CRCEER  4
#define SPI_SR_MODF    5
#define SPI_SR_OVR     6
#define SPI_SR_BSY     7
#define SPI_SR_FRE     8


/******************************************************
 * BIT Position definition I2C peripheral
 *********************************************************/
/*
 * Bit position definition I2c_CR1
 */
#define I2C_CR1_PE           0
#define I2C_CR1_NOSTRETCH    7
#define I2C_CR1_START        8
#define I2C_CR1_STOP         9
#define I2C_CR1_ACK          10
#define I2C_CR1_SWRST        15

/*
 * BIT position definition I2C_CR
 */
#define I2C_CR2_FREQ           0
#define I2C_CR2_ITERREN        8
#define I2C_CR2_ITEVTEN        9
#define I2C_CR2_ITBUFEN        10

/*
 * bIT POSITION definition I2C_OAR1
 */
#define I2C_OAR1_ADD0          0
#define I2C_OAR1_ADD71         1
#define I2C_OAR1_ADD98         8
#define I2C_OAR1_ADDMODE       15

/*
 * BIT position definition I2C_SR1
 */
#define I2C_SR1_SB            0
#define I2C_SR1_ADDR          1
#define I2C_SR1_BTF           2
#define I2C_SR1_ADD10         3
#define I2C_SR1_STOPF         4
#define I2C_SR1_RXNE          6
#define I2C_SR1_TXE           7
#define I2C_SR1_BERR          8
#define I2C_SR1_ARLO          9
#define I2C_SR1_AF           10
#define I2C_SR1_OVR          11
#define I2C_SR1_TIMEOUT      14

/*
 * BIT position definition I2C_SR2
 */
#define I2C_SR2_MSL           0
#define I2C_SR2_BUSY          1
#define I2C_SR2_TRA           2
#define I2C_SR2_GENCALL       4
#define I2C_SR2_DUALF         7

/*
 * BIT position definition I2C_CCR
 */
#define I2C_CCR_CCR           0
#define I2C_CCR_DUTY          14
#define I2C_CCR_FS            15


/*
 * GPIO alternative function modes
 */

#define AF00        0
#define AF01        1
#define AF02        2
#define AF03        3
#define AF04        4
#define AF05        5
#define AF06        6
#define AF07        7
#define AF08        8
#define AF09        9
#define AF10        10
#define AF11        11
#define AF12        12
#define AF13        13
#define AF14        14
#define AF15        15



/******************************************************
 * BIT Position definition USART peripheral
 *********************************************************/





#include "stm32f411cexx_gpio_driver.h"
#include "stm32f411cexx_spi_driver.h"
#include "stm32f411cexx_i2c_driver.h"
#include "stm32f411cexx_usart_driver.h"
#include "stm32f411cexx_rcc_driver.h"






#endif /* INC_STM32F411CEXX_H_ */
