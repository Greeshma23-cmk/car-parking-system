/* CAN2 driver*/
#include<lpc21xx.h>
#include"can_header.h"
unsigned int *ptr= (unsigned int*)0xE0038000;

void can2_init(void)
{
   PINSEL1|=0X00014000;  // SELECT P0.24 AS TX AND P0.23 AS RX
	 VPBDIV=1;   // SET PCLK=60MHZ
	 C2MOD=1;    //ENABLE RESET MODE
	 C2BTR=0X001C001D; // SET BAUD AT 125KBPS
	// C2MOD=0;  // DISABLE RESET MODE




ptr[0]= 0X20FE20FF; // 0FE=ID FOR GEAR ON AND 0FF=ID FOR GEAR OFF AND 2 FOR CAN CONTROLLER NUMBER
SFF_sa=0;
SFF_GRP_sa=0X4;
EFF_sa=EFF_GRP_sa=0x4;
ENDofTable=0x4;
AFMR=0;
C2MOD=0;   // cancel resetmode

}

#define TCS ((C2GSR>>3)&1)  

void can2_tx(CAN2 v)
{
    C2TID1=v.id;
		C2TFI1=v.dlc<<16;
 		if(v.rtr==0)    //IF DATA FRAME
		{
		   C2TDA1=v.byteA;
			 C2TDB1=v.byteB;
		}
    else
   C2TFI1|=(1<<30);	// IF REMOTE FRAME
   C2CMR=1|(1<<5);   // TO START TRANSMISSION AND SELECT TX BUFFER 1 FOR TRANSMISSION
    while(TCS==0);    // waiting for data frame to transmit
}


#define RBS (C2GSR&1)

void can2_rx(CAN2 *p)
{
	  while(RBS==0);
	  p->id=C2RID; // RECEIVE ID
	  p->dlc=(C2RFS>>16)&0x0f; // receive dlc
	  p->rtr=(C2GSR>>30)&1;
	  if(p->rtr==0)
		{
			 p->byteA=C2RDA;
			p->byteB=C2RDA;
		}
		C2CMR=(1<<2); // to release rx 
}		
			



 	 
    

