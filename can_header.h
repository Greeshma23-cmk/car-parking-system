


typedef struct can2
{
  unsigned int id;
  unsigned int dlc;
  unsigned int rtr;
  unsigned int byteA;
  unsigned int byteB;
  }CAN2;
  
	extern void can2_init(void);
	extern void can2_rx(CAN2 *p);
	extern void can2_tx(CAN2 v);
	
	extern void ext_config(void);
	extern void en_ext(void);
	
	extern void configA(void);
	extern void enA(void);
	
	extern void uart0_init(unsigned int baud);
	extern void uart0_tx(unsigned char data);
	extern void uart0_tx_string(char *ptr);
	extern void uart0_tx_integer(int num);
	extern void uart0_tx_hex(int num);
	
	extern void delay_ms(unsigned int ms);
	extern int distance(void);
	
	extern void configB(void);
	extern void enB(void);