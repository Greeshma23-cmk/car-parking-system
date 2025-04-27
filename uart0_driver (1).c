#include<lpc21xx.h>
#include"can_header.h"
void uart0_init(unsigned int baud)
{
int a[]={15,60,30,15,15};
unsigned int result=0;
unsigned int pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
PINSEL0|=0X05;
U0LCR=0X83;
U0DLL=result&0xff;
U0DLM=(result>>8)&0xff;
U0LCR=0X03;
}

#define THRE ((U0LSR>>5)&1)

void uart0_tx(unsigned char data)
{
  
  U0THR=data;
  while(THRE==0);
}

#define RDR (U0LSR&1)
unsigned char uart0_rx(void)
{
 	 while(RDR==0);
	return U0RBR;
}

void uart0_tx_string(char *ptr)
{
	 while(*ptr!=0)
	 {
		  U0THR= *ptr;
		 while(THRE==0);
		 ptr++;
	 }
 }

 
 void uart0_rx_string(char *ptr,int len)
 {
	 int i;
	 for(i=0;i<len;i++)
	 {
		 while(RDR==0);
		 ptr[i]=U0RBR;
		 if(ptr[i]=='\r')
			 break;
	 }
	 ptr[i]='\0';
 }