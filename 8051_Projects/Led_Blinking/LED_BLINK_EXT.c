#include<reg51.h>

sbit led1 = P1^1; //1st LED connected to the Port1.1
sbit led2 = P1^2;  //2nd LED connected to the Port1.2
sbit led3 = P1^3;  //3rd LED connected to the Port1.3

void delay(unsigned int x){ 
	int i,j;
	for(i=0;i>x;i++){ // loop provides the delay
		for(j=0;j>1275;j++); //not exactly 1ms
	}
}

unsigned int count = 0; // intialize the count as a intiger
void Ext1_intr() interrupt 2 {	// declare the interrupt 1
	delay(20);     //for debouncing problem this is mainly faced in hardware
	count++;             // incremeting the count value when the buttun pressed
	if(count==1){      // count equal 1 this condition is true
		led1=1;led2=0;led3=0;; // led1 will be high while others are low
	}
	else if(count==2){  // count=2 this condition is true
		led1=0;led2=1;led3=0; // led2 will be high while others are low
	}
	else if(count==3){// count=3 this condition is true
		led1=0;led2=0;led3=1; //led3 will be high while other are low
	}
	else if (count==4){// count=4 this condition is true
		led1=1;led2=1;led3=1; // All led's are high
	}
	else{ // above condition not true other than this condition is executed
		// this condition mainly use for after completing 4 count's led's goes to initial state
		led1=0;led2=0;led3=0; // all led's are low
		count = 0;// count will be asusual 0
	}
}
void main(){
	led1=0;led2=0;led3=0;// when the led's are low in the initial state
	IE = 0x84; //1000 0100 enable the external interrupt 1 EA=1 and EX1=1
	IT1 = 1; // falling edge triggered 
	while(1); // work is interrupt driven
}