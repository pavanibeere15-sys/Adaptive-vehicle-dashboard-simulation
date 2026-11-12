#include"header.h"
#define TCS ((C1GSR>>3)&1)
#define RBS (C1GSR&1)

extern u8 flag;
extern CAN1 r1;

void can1_init(){
	//VPBDIV=1;//set pclk to 60MHz
	PINSEL1|=0X40000;//P0.25-->RD1
	C1MOD=1;//Select reset mode
	C1BTR=0X001C001D;//125 kbps baudrate

	AFMR=2;//Accept all message

	C1MOD=0;//release reset mode

}

void can1_tx(CAN1 v){
	C1TID1=v.id;
	C1TFI1=v.dlc<<16;//set dlc=8,rtr=0,ff=0(standard version)
	if(v.rtr==0){
		C1TDA1=v.byteA;
		C1TDB1=v.byteB;
	}else{
		C1TFI1|=(1<<30);//rtr=1
	}
	C1CMR=0X21;//select Txbuff & start transmission
	while(TCS==0);
}


void can1_rx(CAN1 *v){
	while(RBS==0);//waiting for receive data/remote frame
	v->id=C1RID;
	v->dlc=((C1RFS>>16)&0XF);//extract dlc
	v->rtr=((C1RFS>>30)&1);//extract rtr
	v->ff=((C1RFS>>31)&1);//extract ff
	if(v->rtr==0){
		v->byteA=C1RDA;
		v->byteB=C1RDB;
	}
	C1CMR=(1<<2);//release rxbuff

}

void CAN1_Rx_Handler(void) __irq{
	r1.id=C1RID;	
	r1.dlc=(C1RFS>>16)&0xF;//extract dlc
	r1.rtr=(C1RFS>>30)&1;//extract rtr
	r1.ff=(C1RFS>>31)&1;//extract frame format
	if(r1.rtr==0){//if data-frame
		r1.byteA=C1RDA;
		r1.byteB=C1RDB;
	}
	C1CMR=(1<<2);//imp
	flag=1;//further used in main func
	VICVectAddr=0;
}

void config_vic_for_can1(void){
	VICVectCntl5=26|(1<<5);
	VICVectAddr5=(u32)CAN1_Rx_Handler;
	VICIntEnable=(1<<26);//En CAN1 Rx intr in VIC peri
	C1IER=1;//En CAN1 Rx intr only
}


