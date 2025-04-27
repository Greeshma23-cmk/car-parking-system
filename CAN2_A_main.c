#include<lpc21xx.h>
#include"can_header.h"
#define LED1 (1<<17)
#define LED2 (1<<18)
#define BUZZ (1<<7)


unsigned char rev_gear;
 unsigned char flag;
 CAN2 VA;
 CAN2 V1;

int main()
{
	
	IODIR0=(1<<7)|(1<<17)|(1<<18);
	IOSET0|=LED1|LED2;
	IOCLR0|=BUZZ;
  uart0_init(9600);
	can2_init();
	ext_config();
	en_ext();
	configA();
	 enA();
	V1.dlc=2;
	
	while(1)
	{
		  if(rev_gear)
			{
				rev_gear=0;
				IOCLR0|=LED2;
				IOSET0|=BUZZ;
		    uart0_tx_string("\r\nReverse Gear is ON");
			  V1.id=0x0FE;
				V1.rtr=1;
				can2_tx(V1);
			
			
			 while(1)
			 {
				 if(rev_gear)
				{
					rev_gear=0;
					IOCLR0=BUZZ;
				 IOSET0|=LED2;
				uart0_tx_string("\r\nReverse gear OFF");
				V1.id=0xFF;
				V1.dlc=0;
				V1.rtr=1;
				can2_tx(V1);
					break;
			 }
     		
					
					if(flag)
          {
             flag=0;
           if(VA.byteA>400)
					  {
					 	 IOCLR0=BUZZ;
            }
          else if(VA.byteA<=100)
					{
             IOSET0=BUZZ;
					}
          else if(VA.byteA>=300 && VA.byteA<=400)
					{   
						  IOSET0=BUZZ;
						  IOCLR0=LED1;
						  delay_ms(500);
						IOCLR0=BUZZ;
						IOSET0=LED1;
					}
					else if(VA.byteA>=200 && VA.byteA<=299)
					{   
						  IOSET0=BUZZ;
						  IOCLR0=LED1;
						   delay_ms(200);
						IOCLR0=BUZZ;
						IOSET0=LED1;
					}
          else if(VA.byteA>=100 && VA.byteA<=199)
					{   
						  IOSET0=BUZZ;
						  IOCLR0=LED1;
						   delay_ms(50);
						IOCLR0=BUZZ;
						IOSET0=LED1;
					}
       }
		 }
	 }
  }
}
