#include <LPC21xx.H>

typedef unsigned int u32;
typedef unsigned char u8;
typedef signed int s32;
typedef signed char s8;

extern void delay_sec(unsigned int);
extern void delay_ms(unsigned int);
extern void delay_uc(unsigned int);

/////////////LCD/////////////
extern void lcd_init(void);
extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_str(char *);
extern void lcd_int(int);
extern void lcd_float(float);
//////////////////////////////

//////////UART0///////////////
extern void uart0_init(unsigned int);
extern void uart0_tx(unsigned char);
extern unsigned char uart0_rx(void);
extern void uart0_str(char *);
extern void uart0_float(float);
extern void uart0_int(int);

////////////UART0 Interrupt//////
extern void config_uart0(void);


///////////EINT Interrupt/////////
extern void config_eint0(void);
extern void config_eint1(void);
extern void config_eint2(void);

////SPI0//////////
extern void spi0_init(void);
extern u8 spi0(u8 data);

/////I2C/////////
extern void i2c_init(void);
extern u8 i2c_read(u8,u8);
extern void i2c_write(u8,u8,u8);

///CAN1 INTERRUPT//////////
extern void config_can1(void);

////////ADC///////////////////
extern void adc_init(void);
extern u32 adc_read(u8);


///CAN//////////
typedef struct CAN1_FRAME{
	u32 id;
	u8 rtr;
	u8 dlc;
	u8 ff;
	u32 byteA;
	u32 byteB;
}CAN1;

extern void can1_init(void);
extern void can1_tx(CAN1);
extern void can1_rx(CAN1 *);


////PROJECT//////////
extern void ultrasonic_init(void);
extern u32 ultrasonic_read(void);
