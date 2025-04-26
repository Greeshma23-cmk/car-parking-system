/*reverse gear.c*/

#include<LPC21XX.H>
#include"header.h"
#define sw1 ((IOPIN0>>14)&1)
#define buzzer (1<<21)   //p0.21
#define LED (1<<17)      //p0.17

CAN1 v1,t,t1;
u32 flag,c=0,flag1=0;
int main()
{
		
	can2_init();
	uart0_init(9600);
	config_vic();
	en_int();

	t.id=0x45;                         //for remote frame
	t.rtr=1;
	t.dlc=4;	 
	//for data frame
	t1.id=0x23;
	t1.rtr=0;
	t1.dlc=4;
	t1.byteA=0x44332211;

	IODIR0=buzzer|LED;
	IOCLR0=buzzer;
	IOSET0=LED;
	uart0_tx_string("welcome\r\n");
	while(1)
	{
		if(sw1==0)
		{
			while(sw1==0);
			c^=1;
			uart0_tx_integer(c);
			uart0_tx_string("\r\n");
			if(c)
			{  
			    flag1=1;
			    uart0_tx_string("remote frame transmited\r\n");
				can2_tx(t);											
				
			}
			else
			{
				flag1=0;
				can2_tx(t1);											
				uart0_tx_string("data frame transmited\r\n"); 
			}
		}

		if(flag==1)
		{
		    flag=0;
			if(flag1==1)
			{
			uart0_tx_string("frame received\r\n");
			if((v1.byteA<=400) && (v1.byteA>=300))
			{
				uart0_tx_string("400-300\r\n");
				IOSET0=buzzer;
				IOCLR0=LED;
				delay_ms(1000);
				IOCLR0=buzzer;
				IOSET0=LED;
				delay_ms(1000);
			}
			if((v1.byteA<=299) && (v1.byteA>=200))
			{
				uart0_tx_string("299-200\r\n");
				IOSET0=buzzer;
				IOCLR0=LED;
				delay_ms(500);
				IOCLR0=buzzer;
				IOSET0=LED;
				delay_ms(500);
			}
			if((v1.byteA<=199) && (v1.byteA>=100))
			{
				uart0_tx_string("199-100\r\n");
				IOSET0=buzzer;
				IOCLR0=LED;
				delay_ms(100);
				IOCLR0=buzzer;
				IOSET0=LED;
				delay_ms(100);
			}
			if((v1.byteA<=99) && (v1.byteA>=50))
			{
				uart0_tx_string("99-50\r\n");
				IOSET0=buzzer;
				IOCLR0=LED;
				delay_ms(50);
				IOCLR0=buzzer;
				IOSET0=LED;	
				delay_ms(50);

			}
			if((v1.byteA<=50))
			{
				uart0_tx_string("50\r\n");
				IOSET0=buzzer;
				IOCLR0=LED;
			 }
			 else
			 {
			     IOCLR0=buzzer;
				 IOSET0=LED;
			 }
			}
		}
	} 
}


#include<LPC21XX.H>
#include"header.h"
extern CAN1 v1;
extern u32 flag;
__irq void can2_rx_Handler(void)
{
  v1.id=C2RID;
  v1.dlc= (C2RFS>>16)&0x0f;
  v1.rtr=(C2RFS>>30)&1;
  if(v1.rtr==0)
  {
     v1.byteA=C2RDA;
	 v1.byteB=C2RDB;
  }
  C2CMR=(1<<2);
  flag=1;
  VICVectAddr=0;
}
void config_vic(void)
{
   VICIntSelect=0;
   VICVectCntl0=27|(1<<5);
   VICVectAddr0=(u32)can2_rx_Handler;
   VICIntEnable|=(1<<27);
}
void en_int(void)
{
   C2IER=1;
}


#include<LPC21XX.H>
#include"header.h" 
//#include<stdio.h>
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)

void uart0_init(u32 baud)
{
  u32 pclk,res;
  int a[]={15,60,30,15,15};
  pclk=a[VPBDIV]*1000000;
  res=pclk/(16*baud);

  PINSEL0|=5;        //p0.0 tx and p0.1 rx
  U0LCR=0x83;		 // 8N1 DLAB=1;
  U0DLL=res&0xFF;		//lower byte
  U0DLM=(res>>8)&0xFF;  //upper byte
   U0LCR=0x03;         //DLAB=0;
}

void uart0_tx(u8 data)
{
  U0THR=data;
  while(THRE==0);
}

u8 uart0_rx(void)
{
   while(RDR==0);
   return U0RBR;
}

void uart0_tx_string(char *ptr)
{
  while(*ptr)
  {
     U0THR=*ptr;
	 while(THRE==0);
	 ptr++;
   }
}

void uart0_hex(u8 ascii)
 {
    u8 i;  
    uart0_tx(0+48);
	uart0_tx('x');

    i=(ascii>>4)&0x0F;
	uart0_tx(i+48);
	i=(ascii&0x0F);
	if(i>9)
	{
	   i=i-9;
	   uart0_tx(64+i); 	  
	}
	else
	   uart0_tx(i+48);

 }
 
void uart0_rx_string(char *ptr,u8 len)
{
   s32 i;
   for(i=0;i<len;i++)
   {
      while(RDR==0);
	  ptr[i]=U0RBR;
	  if(ptr[i]=='\r')
	      break;
	}
	ptr[i]='\0';
}

void uart0_tx_integer(int num)
{
  int len,i,j;
  char s[10],t;
  //sprintf(a,"%d",num);
  if(num==0)
  {
      uart0_tx('0');
       return;
  }          
   for(i=0;num;num=num/10,i++)
      s[i]=(num%10)+48;
	s[i]='\0';
    for(len=0;s[len]!='\0';len++);

    for(i=0,j=len-1; i<j ;i++,j--)
	 {
         t=s[i];
		 s[i]=s[j];
		 s[j]=t;
	   }

  uart0_tx_string(s);
}

void uart0_tx_float(float f)
{
  int n;
  if(f==0)
  {
     uart0_tx_string("0.00");
	 return;
   }
   n=f;
   uart0_tx_integer(n);
   n=(f-n)*100;
   uart0_tx('.');
   uart0_tx_integer(n);
}
	  
#include<LPC21XX.H>
void delay_ms(unsigned int ms)
{
  int a[]={15,60,30,15,15};
  unsigned int pclk;
  pclk=a[VPBDIV]*1000;

  T0PC=0;
  T0PR=pclk-1;
  T0TC=0;
  T0TCR=1;
  while(T0TC<ms);
  T0TCR=0;
}
void delay_s(unsigned int s)
{
  int a[]={15,60,30,15,15};
  unsigned int pclk;
  pclk=a[VPBDIV]*1000000;

  T0PC=0;
  T0PR=pclk-1;
  T0TC=0;
  T0TCR=1;
  while(T0TC<s);
  T0TCR=0;
}


typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;

typedef struct CAN1_MSG
{
   u32 id;
   u32 byteA;
   u32 byteB;
   u8 rtr;
   u8 dlc;
}CAN1;
 
extern void delay_ms(u32);
extern void delay_s(u32);
extern void lcd_data(u8);
extern void lcd_cmd(u8);
extern void lcd_int(void);
extern void lcd_string(char *);
extern void lcd_atoi(int);
extern void lcd_atof(float);
extern void lcd_cgram(void);
extern void uart0_init(u32 baud);
extern void uart0_tx(u8 data);
extern u8 uart0_rx(void);
extern void uart0_tx_string(char *ptr);
extern void uart0_hex(u8 ascii);
extern void uart0_rx_string(char *,u8 );
extern u8 spi0(u8 data);
extern void spi0_init(void);
extern u16 read_mcp3204(u8 ch_num);
extern void uart0_tx_integer(int num);
extern void uart0_tx_float(float f);
extern void i2c_byte_write_frame(u8 sa,u8 mr, u8 data);
extern u8 i2c_byte_read_frame(u8 sa, u8 mr);
extern void i2c_init(void);
extern void can1_init(void);
extern void can1_tx(CAN1 v);
extern void can2_init(void);
extern void can2_tx(CAN1 v);
extern void config_vic(void);
extern void en_int(void);
#define CS0 (1<<7)


#include<LPC21XX.H>
#include"header.h"

#define TCS ((C2GSR>>3)&1)
#define RBS (C2GSR&1)
void can2_init(void)
{
   VPBDIV=1;
   PINSEL1|=0x14000;
   C2MOD=1;
   C2BTR=0x001C001D;
   AFMR=2;
   C2MOD=0;
}
void can2_tx(CAN1 v)
{
  C2TID1=v.id;
  C2TFI1=v.dlc<<16;
  if(v.rtr==0)
  {
    C2TDA1=v.byteA;
	C2TDB1=v.byteB;
  }
  else
    C2TFI1|=(1<<30);

  C2CMR=1|(1<<5);
  while(TCS==0);
}
void can2_rx(CAN1 *ptr)
{
   while(RBS==0);
   ptr->id=C2RID;
   ptr->dlc=(C2RFS>>16)&0x0F;
   ptr->rtr=(C2RFS>>30)&1;
   if(ptr->rtr==0)
   {
      ptr->byteA=C2RDA;
	  ptr->byteB=C2RDB;
   }
   C2CMR=(1<<2);	    			//releasing the receiver  buffer
}															 














