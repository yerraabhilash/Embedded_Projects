/*
 * 003_Source_External.c
 *
 *  Created on: Oct 29, 2025
 *      Author: Abhilash
 *      i Am writeing code for the using files
 */
#include <stdint.h>

void main(void)
{
	uint32_t *AHB1ENR_R = (uint32_t)(0x40023830); // accessing the RCC base address with ENR(peripheral clock enAble register)
	uint32_t *MODER_R = (uint32_t)(0x40020000); // AccesSing the GPIOA regIster with MOder register offset is moder
	uint32_t *ODR_R = (uint32_t)(0x40020014); // AccesSing the ODR register

	*AHB1ENR_R |= (1<<0); //selected GPIOA left shifting process
	*MODER_R &=  ~(0X03 << 10); // Selected with output gpioa port and clear the bits
	*MODER_R |= 0XFFFFFF4F;
	*ODR_R |= (1 << 5);
	/*while(1)
	{
		*ODR_R |= (1>>5);
	}
*/
}
