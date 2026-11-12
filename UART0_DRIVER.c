#include"header.h"
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)

void uart0_init(unsigned int baud){
	unsigned int result=0,pclk;

	if(VPBDIV==0){
		pclk=15000000;
	}else if(VPBDIV==1){
		pclk=60000000;
	}else if(VPBDIV==2){
		pclk=30000000;
	}

	result=pclk/(16*baud);

	PINSEL0|=0X05;
	U0LCR=0X83;
	U0DLL=(result&0xFF);
	U0DLM=((result>>8)&0xFF);
	U0LCR=0X03;
}

void uart0_tx(unsigned char data){
	U0THR=data;
	while(THRE==0);
}

unsigned char uart0_rx(void){
	while(RDR==0);
	return U0RBR;
}

void uart0_str(char *p){
	while(*p){
		uart0_tx(*p);
		p++;
	}
}

int uart0_char_int(char *p){
	int num=0,i=0;
	while(p[i]){
		 num=num*10+p[i]-48;
		 i++;
	}
	return num;
}

void uart0_int(int num){
	int rev=0;
	if(num==0){
		uart0_str("00");
		return;
	}

	if(num<0){
		num=-num;
		uart0_str("-");
	}

	while(num){
	   rev=(rev*10)+num%10;
	   num/=10;
	}

	while(rev){
		uart0_tx(rev%10+48);
		rev/=10;
	}
}

void uart0_float(float num){
	int a=0;

	if(num==0){
		uart0_str("00");
		return;
	}

	if(num<0){
		num=-num;
		uart0_tx('-');
	}

	a=num;
	uart0_int(a);

	a=(num-a)*10000;
	uart0_tx('.');
	uart0_int(a);
}
