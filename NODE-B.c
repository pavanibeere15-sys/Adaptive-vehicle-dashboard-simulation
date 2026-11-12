#include "header.h"
#define LEFT_LED  (1<<17)
#define RIGHT_LED (1<<18)
#define HEAD_LED  (1<<19)

CAN1 r1;
u8 flag;

u32 speed=0;
u32 fuel=0;
u32 temperature=0;
u8 status=0;

u8 sensor_received=0;
u8 status_received=0;

int main(){
    IODIR0 |= LEFT_LED | RIGHT_LED | HEAD_LED;
    IOSET0 = LEFT_LED | RIGHT_LED | HEAD_LED;

    /* Initialize UART and CAN */
    uart0_init(9600);
    can1_init();

    /* Configure CAN receive interrupt */
	config_vic_for_can1();

    uart0_str("\r\n================================");
    uart0_str("\r\n     VEHICLE MONITORING SYSTEM");
    uart0_str("\r\n================================");

    while(1){
        /* Check CAN receive interrupt */

        if(flag){
            flag = 0;
            /* Frame 1: Sensor information */
            if(r1.id == 0x123){
                speed = r1.byteA & 0xFF;
                fuel = (r1.byteA >> 8) & 0xFF;
                temperature = (r1.byteA >> 16) & 0xFF;
                sensor_received = 1;
            }else if(r1.id == 0x124){  /* Frame 2: Indicator information */
                status = r1.byteA & 0xFF;
                status_received = 1;
            }

            /* Display after receiving both frames */
            if(sensor_received && status_received){
                uart0_str("\r\n-------------------------------");

                uart0_str("\r\nVehicle Speed : ");
                uart0_int(speed);
                uart0_str(" km/hr");

                uart0_str("\r\nFuel Level    : ");
                uart0_int(fuel);
                uart0_str(" %");

                uart0_str("\r\nEngine Temp   : ");
                uart0_int(temperature);
                uart0_str(" C");

                uart0_str("\r\nLeft Indicator  : ");

                if(status & 1)
                    uart0_str("ON");
                else
                    uart0_str("OFF");

                uart0_str("\r\nRight Indicator : ");

                if(status & 2)
                    uart0_str("ON");
                else
                    uart0_str("OFF");

                uart0_str("\r\nHeadlight       : ");

                if(status & 4)
                    uart0_str("ON");
                else
                    uart0_str("OFF");

                uart0_str("\r\n-------------------------------");

                sensor_received = 0;
                status_received = 0;
            }
        }

        /* Left indicator blinking */

        if(status & 1){
            IOCLR0 = LEFT_LED;
            delay_ms(500);
            IOSET0 = LEFT_LED;
            delay_ms(500);
        }else{
            IOSET0 = LEFT_LED;
        }

        /* Right indicator blinking */
        if(status & 2){
            IOCLR0 = RIGHT_LED;
            delay_ms(500);
            IOSET0 = RIGHT_LED;
            delay_ms(500);
        }else{
            IOSET0 = RIGHT_LED;
        }

        /* Headlight control */

        if(status & 4)
            IOCLR0 = HEAD_LED;
        else
            IOSET0 = HEAD_LED;
    }
}

