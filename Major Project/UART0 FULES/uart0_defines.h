#define UART_INT_ENABLE 1

#define TXD 0
#define RXD 1

//BAUD RATE CALCULATION & DIVISOR
#define FOSC      12000000   //Hz
#define CCLK  	  5*FOSC
#define PCLK  	  CCLK/4
#define BAUD  	  9600
#define DIVISOR   (PCLK/(16 * BAUD))
