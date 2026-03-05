#include <reg51.h>
#include <string.h>

sfr port_1 = 0x90; //we can select the port1 as per google(not exactly)
sbit rs = P2^1;
sbit en = P2^2;

void delay(unsigned int x);
void lcd_cmd(unsigned char a);
void lcd_init();
void lcd_print_char(unsigned char b);
void lcd_print_string(unsigned char *str);

void delay(unsigned int x){
	unsigned int i,j;
	for(i=0;i<x;i++){
		for(j=0;j<125;j++);
	}
}
void lcd_cmd(unsigned char a){
	port_1 = (port_1 & 0x0F)| (a & 0xF0);//
    rs = 0; // command mode
	en = 1;
	delay(50);
	en = 0;
	delay(20);
	
	port_1 = (port_1 & 0x0F) | (a << 4);
	en = 1;
	delay(50);
	en = 0;
	delay(30);
}
void lcd_init(){
	lcd_cmd(0x02);   //4_bit mode
  lcd_cmd(0x28);   //initialize the lcd into 4 bit mode
  lcd_cmd(0x0c);   //display on cursor off
  lcd_cmd(0x80);   //force to the beggining of the 1st row
  lcd_cmd(0x01);   //clear desplay
}
void lcd_print_char(unsigned char b){
	port_1 = (port_1 & 0x0F) | (b & 0XF0);// send the higher nibble first 
	rs = 1;
	en = 1;
	delay(50);
	en=0;
	delay(20);
	
	port_1 = (port_1 & 0x0F) | (b << 4);// lower nibble secound
	en = 1;
	delay(50);
	en = 0;
	delay (20);
}
void lcd_print_string(unsigned char *str){
	while(*str){
		lcd_print_char(*str++);
	}
}
void main(){
	lcd_init();
	lcd_print_string("  WELCOME TO ");
	delay(50);
	lcd_cmd(0xc0);
	lcd_print_string(" MY PROJECT ");

}