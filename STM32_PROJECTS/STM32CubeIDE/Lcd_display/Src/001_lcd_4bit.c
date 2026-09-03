/*
 * 001_lcd_4bit.c
 *
 *  Created on: 28-Feb-2026
 *      Author: yerra
 */

#include<string.h>

#include "stm32f411cexx.h"

#include "lcd.h"



int main(void)
{


	lcd_init();

	lcd_print_string("RTC Test...");



	while(1);

	return 0;
}
