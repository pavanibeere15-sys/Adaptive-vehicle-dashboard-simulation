#include"header.h"
#define TRIG (1<<10)
#define ECHO (1<<11)

void ultrasonic_init(void){
      IODIR0|=TRIG;
      IODIR0&=~ECHO;
}

u32 ultrasonic_read(void){
      u32 count=0;

      IOCLR0=TRIG;
      delay_uc(2);
      IOSET0=TRIG;
      delay_uc(10);

      IOCLR0=TRIG;
      while(!(IOPIN0 & ECHO));

      while(IOPIN0 & ECHO){
            count++;
            delay_uc(1);
      }
      return (count/58);
}
