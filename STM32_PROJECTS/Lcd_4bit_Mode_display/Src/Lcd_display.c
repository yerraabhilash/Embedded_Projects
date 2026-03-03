
#include<string.h>
#include<stdio.h>

#include "stm32f411cexx.h"


#define LCD_PORT   GPIOB
#define LCD_EN     GPIO_PIN_NO_13
#define LCD_RS     GPIO_PIN_NO_0
#define LCD_DB4    GPIO_PIN_NO_5
#define LCD_DB5    GPIO_PIN_NO_6
#define LCD_DB6    GPIO_PIN_NO_7
#define LCD_DB7    GPIO_PIN_NO_8


static void mdelay(uint32_t cnt);
static void udelay(uint32_t cnt);
void GPIO_Init_Config(void);
void LCD_Set_Bit(char data_bit);
void Lcd_Cmd(char cmd);
void LCD_Init(void);
void Lcd_Print_Char(char str);
void Lcd_Clear(void);
void Lcd_Set_Cursor(uint8_t row, uint8_t column);
void Lcd_Print_String(char *st);
void Lcd_Enable(void);


static void mdelay(uint32_t cnt)
{
	for(uint32_t i=0 ; i < (cnt * 1000); i++);
}

static void udelay(uint32_t cnt)
{
	for(uint32_t i=0 ; i < (cnt * 1); i++);

}




void LCD_Set_Bit(char data_bit)
{
	if(data_bit & 0x01){
		GPIO_WriteToOutputPin(LCD_PORT,LCD_DB4,GPIO_PIN_SET);
	}else{
		GPIO_WriteToOutputPin(LCD_PORT,LCD_DB4,GPIO_PIN_RESET);
	}

	if(data_bit & 0x02){
		GPIO_WriteToOutputPin(LCD_PORT,LCD_DB5,GPIO_PIN_SET);
	}else{
		GPIO_WriteToOutputPin(LCD_PORT,LCD_DB5,GPIO_PIN_RESET);
	}

	if(data_bit & 0x04){
		GPIO_WriteToOutputPin(LCD_PORT,LCD_DB6,GPIO_PIN_SET);
	}else{
		GPIO_WriteToOutputPin(LCD_PORT,LCD_DB6,GPIO_PIN_RESET);
	}

	if(data_bit & 0x08){
		GPIO_WriteToOutputPin(LCD_PORT,LCD_DB7,GPIO_PIN_SET);
	}else{
		GPIO_WriteToOutputPin(LCD_PORT,LCD_DB7,GPIO_PIN_RESET);
	}
}


void Lcd_Cmd(char cmd)
{
    GPIO_WriteToOutputPin(LCD_PORT, LCD_RS, GPIO_PIN_RESET); // RS = 0 → Command mode

    // Send upper nibble first
    LCD_Set_Bit(cmd >> 4);
    Lcd_Enable();

    // Send lower nibble
    LCD_Set_Bit(cmd & 0x0F);
    Lcd_Enable();
}

void GPIO_Init_Config(void)
{
	GPIO_Handle_t Lcd_data;

	memset(&Lcd_data,0,sizeof(Lcd_data));

	Lcd_data.pGPIOx = LCD_PORT;
	Lcd_data.GPIO_PinConfig.GPIO_PinNumber = LCD_RS;
	Lcd_data.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Lcd_data.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	Lcd_data.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Lcd_data.GPIO_PinConfig.GPIO_PinPuPdcontrol = GPIO_NO_PUPD;
	GPIO_Init(&Lcd_data);

	Lcd_data.GPIO_PinConfig.GPIO_PinNumber = LCD_EN;
	GPIO_Init(&Lcd_data);


	Lcd_data.GPIO_PinConfig.GPIO_PinNumber = LCD_DB4;
	GPIO_Init(&Lcd_data);

	Lcd_data.GPIO_PinConfig.GPIO_PinNumber = LCD_DB5;
	GPIO_Init(&Lcd_data);

	Lcd_data.GPIO_PinConfig.GPIO_PinNumber = LCD_DB6;
	GPIO_Init(&Lcd_data);

	Lcd_data.GPIO_PinConfig.GPIO_PinNumber = LCD_DB7;
	GPIO_Init(&Lcd_data);


	GPIO_WriteToOutputPin(LCD_PORT, LCD_RS, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_PORT, LCD_EN, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_PORT, LCD_DB4,GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_PORT, LCD_DB5,GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_PORT, LCD_DB6,GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_PORT, LCD_DB7,GPIO_PIN_RESET);

}

void LCD_Init(void)
{
	GPIO_WriteToOutputPin(LCD_PORT, LCD_RS, GPIO_PIN_RESET);

   //1.  Ensures internal controller is ready before configuration
	LCD_Set_Bit(0x00);
	mdelay(50);

	Lcd_Cmd(0x03);      // 2. Switch to 8-bit mode (Command 0x30/0x3) - Only upper nibble sent (8-bit)
    mdelay(5);

    Lcd_Cmd(0x03);      // 3. Repeat Command 0x30/0x3 (Mandatory for some LCDs)
    udelay(150);

    Lcd_Cmd(0x03);     // 4. Repeat Command 0x30/0x3 (Mandatory for some LCDs)

    Lcd_Cmd(0x02);     // 5. Set to 4-bit mode (Command 0x20/0x2) - Only upper nibble sent (8-bit)

     Lcd_Cmd(0x28);    // 0x28 → 4-bit mode, 2 display lines, 5x8 dot font
     Lcd_Cmd(0x0E);    // 0x0E → Display ON, Cursor ON, Blink OFF
     Lcd_Clear();      // Clears DDRAM and returns cursor to home position
     Lcd_Cmd(0x06);    // 0x06 → Cursor moves right, no display shift
     udelay(150);      // Short delay for command processing stabilization

}


void Lcd_Enable(void)
{
    GPIO_WriteToOutputPin(LCD_PORT, LCD_EN, GPIO_PIN_SET);   // EN = 1
    udelay(10);
    GPIO_WriteToOutputPin(LCD_PORT, LCD_EN, GPIO_PIN_RESET); // EN = 0
	udelay(100);
}

void Lcd_Clear(void)
{
	Lcd_Cmd(0x01);
	mdelay(5);
}


void Lcd_Set_Cursor(uint8_t row, uint8_t column)
{
  column--;
  if(row == 1)   // Set cursor to 1st row address and add index
  {
      Lcd_Cmd((column |= 0x80));
  }else if (row == 2) // Set cursor to 2nd row address and add index
  {
      Lcd_Cmd((column |= 0xC0));
  }
}


void Lcd_Print_Char(char str)
{
	char Upper_Nibble, Lower_Nibble;
	Upper_Nibble = str & 0xF0;
	Lower_Nibble = str & 0x0F;
	GPIO_WriteToOutputPin(LCD_PORT,LCD_RS, GPIO_PIN_SET);

	LCD_Set_Bit(Upper_Nibble >> 4);
	Lcd_Enable();

	LCD_Set_Bit(Lower_Nibble & 0x0F);
	Lcd_Enable();
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

	mdelay(20);
	Lcd_Set_Cursor(1,1);
	Lcd_Print_String("  DISPLAY TEST");

	mdelay(500);
	Lcd_Set_Cursor(2,1);
	Lcd_Print_String("..BY ABHILASH...");
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
		mdelay(1000);
		test_var++;

	}
	*/
return 0;

}


