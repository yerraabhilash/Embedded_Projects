#include<reg51.h>
#include <string.h>
#define data_pins P2
sbit rs = P3^0;
sbit en = P3^1;
//_Bool LED_BUILTIN @P3^3: 5 ; //TO WRITE OUTPUT

void delay(unsigned int x);
void cmd(unsigned char a);
void lcd_init();
void print(unsigned char *s);
void str(unsigned char a);

void delay(unsigned int x){
	unsigned int i,j;
	for(i=0;i<x;i++){
		for (j=0;j<500;j++);
	}
}
void cmd(unsigned char a){
	rs=0;
	data_pins = a;
	en = 1;
	delay(10);
	en = 0;
}
void lcd_init(){
	cmd(0x38);
	cmd(0x0c);
	cmd(0x01);
	cmd(0x80);
	//cmd(0x0f);
}
void print(unsigned char *s){
		while(*s){
			str(*s++);
		}
}
/* void print(unsigned char *s){
	unsigned int i,len;
	len=strlen(s);
	for(i=0;i<len;i++){
		str(s[i]);
	}
} 
*/
void str(unsigned char b){
	data_pins = b; //to send the data to the registers
	rs = 1; // it is on data ragister
	en = 1;  //execute the instruction 
	delay(10);  //
	en = 0; // after 1 we again make it 0
}
void main(){
	lcd_init();
	//cmd(0x80); // cursor to the bigining
	//cmd(0x07);
	print("  NEVER ");
	cmd(0xc0); //force cursor to the 2 nd line
	print("ENDING STORY");

}
/*
Scroll(char *str) {
    int i, len = 0;
    char *ptr = str;

    // Calculate string length
    while (*ptr++) len++;

    for (i = 0; i < len; i++) {
        cmd(0x80);  // Move to the first line
        print(&str[i]);  // Display substring
        print(" ");  // Add a space after the substring for smooth scrolling
        delay(300);    // Delay for visible scrolling
        cmd(0x01);  // Clear the display
    }
}
*/