/*
 * THIS CODE FOR LCD DISPLAY 16X2
 * BUT I DON'T HAVE ONE
 */


#include<string.h>

#include "stm32f411cexx.h"


void delay(void);
void Lcd_cmd(char cmd);
void GPIO_Init_Config(void);
void LCD_Init(void);
void Lcd_Print_Char(char str);
void Lcd_Clear(void);
void Lcd_Print_String(char *st);


void ms_delay(int ms)
	{
	    for(uint32_t i = 0; i < ms * 80000; i++);
	}




void Lcd_Cmd(char cmd)
{
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_2, GPIO_PIN_RESET); // RS = 0 → Command mode

    // Send upper nibble first
    GPIO_WriteToOutputPort(GPIOB, cmd);
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_0, GPIO_PIN_SET);   // EN = 1
    ms_delay(1);
    GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_0, GPIO_PIN_RESET); // EN = 0

}


void GPIO_Init_Config(void)
{
	GPIO_Handle_t LCD_En, LCD_RS, LCD_PB0, LCD_PB1, LCD_PB2, LCD_PB3, LCD_PB4, LCD_PB5,  LCD_PB6,  LCD_PB7;

	memset(&LCD_En,0,sizeof(LCD_En));
	memset(&LCD_RS,0,sizeof(LCD_RS));
	memset(&LCD_PB4,0,sizeof(LCD_PB0));
	memset(&LCD_PB4,0,sizeof(LCD_PB1));
	memset(&LCD_PB4,0,sizeof(LCD_PB2));
	memset(&LCD_PB4,0,sizeof(LCD_PB3));
	memset(&LCD_PB4,0,sizeof(LCD_PB4));
	memset(&LCD_PB5,0,sizeof(LCD_PB5));
	memset(&LCD_PB6,0,sizeof(LCD_PB6));
	memset(&LCD_PB7,0,sizeof(LCD_PB7));

	LCD_En.pGPIOx = GPIOA;
	LCD_En.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	LCD_En.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LCD_En.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	LCD_En.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	LCD_En.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&LCD_En);

	LCD_RS.pGPIOx = GPIOA;
	LCD_RS.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	LCD_RS.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LCD_RS.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	LCD_RS.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	LCD_RS.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOA,ENABLE);
	GPIO_Init(&LCD_RS);

	LCD_PB4.pGPIOx = GPIOB;
		LCD_PB4.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
		LCD_PB4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
		LCD_PB4.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
		LCD_PB4.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
		LCD_PB4.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
		GPIO_PeriClockControl(GPIOB,ENABLE);
		GPIO_Init(&LCD_PB0);

	LCD_PB4.pGPIOx = GPIOB;
	LCD_PB4.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	LCD_PB4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LCD_PB4.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	LCD_PB4.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	LCD_PB4.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOB,ENABLE);
	GPIO_Init(&LCD_PB1);

	LCD_PB6.pGPIOx = GPIOB;
	LCD_PB6.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	LCD_PB6.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LCD_PB6.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	LCD_PB6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	LCD_PB6.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOB,ENABLE);
	GPIO_Init(&LCD_PB2);

	LCD_PB5.pGPIOx = GPIOB;
	LCD_PB5.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	LCD_PB5.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LCD_PB5.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	LCD_PB5.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	LCD_PB5.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOB,ENABLE);
	GPIO_Init(&LCD_PB3);

	LCD_PB6.pGPIOx = GPIOB;
	LCD_PB6.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	LCD_PB6.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LCD_PB6.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	LCD_PB6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	LCD_PB6.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOB,ENABLE);
	GPIO_Init(&LCD_PB4);

	LCD_PB6.pGPIOx = GPIOB;
	LCD_PB6.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	LCD_PB6.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LCD_PB6.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	LCD_PB6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	LCD_PB6.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOB,ENABLE);
	GPIO_Init(&LCD_PB5);

	LCD_PB6.pGPIOx = GPIOB;
	LCD_PB6.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	LCD_PB6.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LCD_PB6.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	LCD_PB6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	LCD_PB6.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOB,ENABLE);
	GPIO_Init(&LCD_PB6);


	LCD_PB7.pGPIOx = GPIOB;
	LCD_PB7.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	LCD_PB7.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LCD_PB7.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	LCD_PB7.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	LCD_PB7.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_PeriClockControl(GPIOB,ENABLE);
	GPIO_Init(&LCD_PB7);

}

void LCD_Init(void)
{
    ms_delay(100);

    Lcd_Cmd(0x28);
    ms_delay(5);

    Lcd_Cmd(0x0C);
    ms_delay(5);

    Lcd_Cmd(0x06);
    ms_delay(5);

    Lcd_Cmd(0x01);
    ms_delay(5);

    Lcd_Cmd(0x80);
    ms_delay(5);

}


void Lcd_Clear(void)
{
	Lcd_Cmd(0x01);
	ms_delay(5);
}



void Lcd_Print_Char(char str)
{
	GPIO_WriteToOutputPin(GPIOA,GPIO_PIN_NO_2, GPIO_PIN_SET);

	GPIO_WriteToOutputPort(GPIOB, str);
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_0, GPIO_PIN_SET);
	ms_delay(1);
	GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_NO_0, GPIO_PIN_RESET);

}

void Lcd_Print_String(char *st)
{
	int i;
	for( i=0; st[i] != '\0'; i++){
		Lcd_Print_Char(st[i]);
	}
}

int main(void)
{

	//int test_var = 0;
	//char d5,d4,d3,d2,d1;


GPIO_Init_Config();

LCD_Init();
ms_delay(1000);

Lcd_Clear();

ms_delay(50);

Lcd_Print_String("Hello");
Lcd_Cmd(0xC0);
Lcd_Print_String("World");

while(1);

/*
{
			d5 = test_var%10 + '0';
			d4 = (test_var/10)%10 + '0';
			d3 = (test_var/100)%10 + '0';
			d2 = (test_var/1000)%10 + '0';
			d1 = (test_var/10000) + '0';

			Lcd_Set_Cursor(2,7);
			Lcd_Print_Char(d1);
			Lcd_Print_Char(d2);
			Lcd_Print_Char(d3);
			Lcd_Print_Char(d4);
			Lcd_Print_Char(d5);
			ms_delay(500);
			test_var++;

}

*/
return 0;

}
