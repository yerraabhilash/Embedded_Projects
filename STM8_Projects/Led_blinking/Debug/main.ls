   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.13.2 - 04 Jun 2024
   3                     ; Generator (Limited) V4.6.4 - 15 Jan 2025
  63                     ; 11 void delay(void) //Function Definition 
  63                     ; 12 {
  65                     	switch	.text
  66  0000               _delay:
  68  0000 5204          	subw	sp,#4
  69       00000004      OFST:	set	4
  72                     ; 13 int i=0,j=0;
  76                     ; 14 for (i=0; i<=200; i++)
  78  0002 5f            	clrw	x
  79  0003 1f01          	ldw	(OFST-3,sp),x
  81  0005               L33:
  82                     ; 16 		for (j=0; j<120; j++) // Nop = Fosc/4
  84  0005 5f            	clrw	x
  85  0006 1f03          	ldw	(OFST-1,sp),x
  87  0008               L14:
  88                     ; 17 _asm("nop"); //Perform no operation 
  91  0008 9d            nop
  93                     ; 16 		for (j=0; j<120; j++) // Nop = Fosc/4
  95  0009 1e03          	ldw	x,(OFST-1,sp)
  96  000b 1c0001        	addw	x,#1
  97  000e 1f03          	ldw	(OFST-1,sp),x
 101  0010 9c            	rvf
 102  0011 1e03          	ldw	x,(OFST-1,sp)
 103  0013 a30078        	cpw	x,#120
 104  0016 2ff0          	jrslt	L14
 105                     ; 14 for (i=0; i<=200; i++)
 107  0018 1e01          	ldw	x,(OFST-3,sp)
 108  001a 1c0001        	addw	x,#1
 109  001d 1f01          	ldw	(OFST-3,sp),x
 113  001f 9c            	rvf
 114  0020 1e01          	ldw	x,(OFST-3,sp)
 115  0022 a300c9        	cpw	x,#201
 116  0025 2fde          	jrslt	L33
 117                     ; 20 }
 120  0027 5b04          	addw	sp,#4
 121  0029 81            	ret
 147                     ; 23 void main()
 147                     ; 24 {
 148                     	switch	.text
 149  002a               _main:
 153                     ; 26 	GPIO_Init(LED, GPIO_MODE_OUT_PP_HIGH_FAST);
 155  002a 4bf0          	push	#240
 156  002c 4b80          	push	#128
 157  002e ae500a        	ldw	x,#20490
 158  0031 cd0000        	call	_GPIO_Init
 160  0034 85            	popw	x
 161  0035               L75:
 162                     ; 30 		GPIO_WriteReverse(LED);
 164  0035 4b80          	push	#128
 165  0037 ae500a        	ldw	x,#20490
 166  003a cd0000        	call	_GPIO_WriteReverse
 168  003d 84            	pop	a
 169                     ; 31 		delay();
 171  003e adc0          	call	_delay
 174  0040 20f3          	jra	L75
 187                     	xdef	_main
 188                     	xdef	_delay
 189                     	xref	_GPIO_WriteReverse
 190                     	xref	_GPIO_Init
 209                     	end
