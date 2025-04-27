#include<lpc21xx.h>
#include"can_header.h"

extern unsigned char rev_gear;

void ext_handler(void) __irq
{
    rev_gear=1;      // external interupt for gear on
	EXTINT=1;          //clear extint buff
	VICVectAddr=0;   // end of interuppt
}

void ext_config(void)
{
   VICIntSelect=0;   // selecting interuppt as IRQ
   VICVectCntl0=14|(1<<5);    //assigning slot0 to ext interuppt
   VICVectAddr0=(unsigned int)ext_handler;  
   VICIntEnable=1<<14; // enable interuppt
}

void en_ext(void)
{
  PINSEL1|=1;  // SELECTING P0.16 PIN AS EXT INTERUPPT
	EXTMODE=1;    // edge trigged 
	EXTPOLAR=0;  //active low interuppt
}