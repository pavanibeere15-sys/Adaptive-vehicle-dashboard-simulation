#include"header.h"

void adc_init(void){
	const int a[5]={4,19,9,4,4};
	u32 cclk=0;
	cclk=a[VPBDIV];
	PINSEL1|=0X15400000;
	ADCR=0X00200000 | (cclk<<8);
		
}

#define DONE ((ADDR>>31)&1)
u32 adc_read(u8 ch_num){
	u32 result=0;
	ADCR|=(1<<ch_num);
	ADCR|=(1<<24);	
	while(DONE==0);
	ADCR^=(1<<24);
	ADCR^=(1<<ch_num);
	result=((ADDR>>6)&0x3FF);
	return result;
}
