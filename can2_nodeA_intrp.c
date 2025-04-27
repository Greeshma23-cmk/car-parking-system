#include"can_header.h"
#include<lpc21xx.h>

extern unsigned char flag;
extern CAN2 VA;
void rxA_handler(void) __irq
{
   flag=1;
   VA.id=C2RID;
   VA.dlc=(C2RFS>>16)&0x0f;
   VA.rtr=(C2RFS>>30)&1;
   if(VA.rtr==0)
   {
      VA.byteA=C2RDA;
	  VA.byteB=C2RDB;
   }
   C2CMR=(1<<2);
   VICVectAddr=0;
 }
 
 void configA(void)
 {
   VICIntSelect=0;
   VICVectCntl2=27|(1<<5);
   VICVectAddr2=(unsigned int)rxA_handler;
   VICIntEnable|=(1<<27);
 }
 
 void enA(void)
 { 
    C2IER=1;   //enable rx interupt
}
 
 