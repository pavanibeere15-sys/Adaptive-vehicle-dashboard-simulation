#include "header.h"
CAN1 m1,m2;

u8 left_flag=0;
u8 right_flag=0;
u8 head_flag=0;

int main(){
    u32 speed_adc,temp_adc;
    u32 fuel_distance;
    u8 speed,fuel,temperature;
    u8 status;

    adc_init();
    ultrasonic_init();
    can1_init();
   	config_eint0();
		config_eint1();
		config_eint2();
		while(1){
        /* Read vehicle speed */
        speed_adc = adc_read(1);
        speed = (speed_adc * 120)/1023;
        
			/* Read engine temperature */
        temp_adc = adc_read(2);
        temperature = (temp_adc * 330)/1023;
			
        /* Read fuel level */
        fuel_distance = ultrasonic_read();
        if(fuel_distance >= 30)
            fuel=0;
        else
            fuel=((30-fuel_distance)*100)/30;

        /* CAN Frame 1 - Sensor Information */
        m1.id = 0x123;
        m1.rtr = 0;
        m1.dlc = 8;
        m1.byteA = speed |(fuel << 8) |(temperature << 16);
        m1.byteB = 0;
				
        can1_tx(m1);

        /* CAN Frame 2 - Indicator Status */
        status = left_flag |(right_flag << 1) |(head_flag << 2);
        m2.id = 0x124;
        m2.rtr = 0;
        m2.dlc = 1;

        m2.byteA=status;
        m2.byteB=0;
        can1_tx(m2);
    }
}
