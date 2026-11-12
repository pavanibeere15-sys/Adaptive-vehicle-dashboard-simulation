#include"header.h"
extern u8 left_flag;
extern u8 right_flag;
extern u8 head_flag; 

////////////////////////////////////
void EINT0_Handler(void)__irq{
	   left_flag^=1;
		 right_flag=0;
	   EXTINT=1;
	   VICVectAddr=0;
}

void config_eint0(void){
	PINSEL1|=1;
	EXTMODE=7;
	EXTPOLAR=0;
	
	VICIntSelect=0;
	VICVectCntl0=14|(1<<5);
	VICVectAddr0=(u32)EINT0_Handler;
	VICIntEnable=1<<14;	
}

//////////////////////////////////
void EINT1_Handler(void)__irq{
	   right_flag^=1;
		 left_flag=0;
	   EXTINT=2;
	   VICVectAddr=0;
}

void config_eint1(void){
	PINSEL0|=0x20000000;
	EXTMODE=7;
	EXTPOLAR=0;
	
	VICIntSelect=0;
	VICVectCntl1=15|(1<<5);
	VICVectAddr1=(u32)EINT1_Handler;
	VICIntEnable=1<<15;	
}

/////////////////////////////////////////
void EINT2_Handler(void)__irq{
	   head_flag^=1;
	   EXTINT=4;
	   VICVectAddr=0;
}

void config_eint2(void){
	PINSEL0|=0xA0000000;
	EXTMODE=7;
	EXTPOLAR=0;
	
	VICIntSelect=0;
	VICVectCntl2=16|(1<<5);
	VICVectAddr2=(u32)EINT2_Handler;
	VICIntEnable=1<<16;	
}
///////////////////////////////////////
