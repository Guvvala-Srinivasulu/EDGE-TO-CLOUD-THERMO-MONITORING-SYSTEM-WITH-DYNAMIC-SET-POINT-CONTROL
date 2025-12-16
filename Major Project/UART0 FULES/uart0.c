#include <LPC21xx.H>  /* LPC21xx definitions         */
#include "uart0_defines.h"
#include "uart0.h"

#include "types.h"

extern char buff[200];
extern unsigned char i;

void UART0_isr(void) __irq
{
  char ch,dummy;
  if((U0IIR & 0x04)) //check if receive interrupt
  {
		ch = U0RBR;	/* Read to Clear Receive Interrupt */
		if(i<200)
			buff[i++] = ch; 
  }
  else
  {
      dummy=U0IIR; //Read to Clear transmit interrupt
  
  }
   VICVectAddr = 0; /* dummy write */
}

void InitUART0 (void) /* Initialize Serial Interface       */ 
{  
            		
  //PINSEL0 = 0x00000005; /* Enable RxD0 and TxD0              */
  
PINSEL0=(PINSEL0&~(3<<(2*TXD)))|(1<<(2*TXD));	
PINSEL0=(PINSEL0&~(3<<(2*RXD)))|(1<<(2*RXD));	

U0LCR = 0x83;         /* 8 bits, no Parity, 1 Stop bit     */
  U0DLL = DIVISOR;           /* 9600 Baud Rate @ CCLK/4 VPB Clock  */
	U0DLM = DIVISOR>>8;
  U0LCR = 0x03;         /* DLAB = 0  */
  
  #if UART_INT_ENABLE > 0

  VICIntSelect = 0x00000000; // IRQ
  VICVectAddr0 = (unsigned)UART0_isr;
  VICVectCntl0 = 0x20 | 6; /* UART0 Interrupt *///here enable the slot as slot(cntl0 and addr0) 0 for uart interrupt surce
  VICIntEnable|=1 << 6;   /* Enable UART0 Interrupt */
 
  U0IER = 0x03;       /* Enable UART0 RX and THRE Interrupts */   
             
  #endif
						
}

void UART0_Tx(char ch)  /* Write character to Serial Port    */  
{ 
	U0THR = ch;
	while(((U0LSR>>5)&1)==0);
  //while (!(U0LSR & 0x20));                
}

char UART0_Rx(void)    /* Read character from Serial Port   */
{  
	while(((U0LSR>>0)&1)==0);	
 // while (!(U0LSR & 0x01));
  return (U0RBR);
}

void UART0_Str(char *s)
{
   while(*s)
       UART0_Tx(*s++);
}

void UART0_Int(unsigned int n)
{
  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};
  int i=0;
  if(n==0)
  {
    UART0_Tx('0');
		return;
  }
  else
  {
     while(n>0)
	 {
	   a[i++]=(n%10)+48;
	   n=n/10;
	 }
	 --i;
	 for(;i>=0;i--)
	 {
	   UART0_Tx(a[i]);
	 }
   }
}

void UART0_Float(float f)
{
  int x;
  float temp;
  x=f;
  UART0_Int(x);
  UART0_Tx('.');
  temp=(f-x)*100;
  x=temp;
  UART0_Int(x);
}


								
