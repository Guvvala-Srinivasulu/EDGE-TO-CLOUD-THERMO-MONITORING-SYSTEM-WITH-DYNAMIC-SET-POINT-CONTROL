#include <lpc214x.h>
#include "delay.h"
#include "defines.h"
#include "lcd.h"
#define input 0
#define output 1
#define DHT11 4	//DHT11 data pin connected to P0.4
extern unsigned char humidity_integer, humidity_decimal, temp_integer, temp_decimal, checksum;
void dht11_request(void)
{
	WRITEBIT(IODIR0,DHT11,output);	// Configure DHT11 pin as output (P0.4 used here)
	WRITEBIT(IOPIN0,DHT11,0); // Make DHT11 pin LOW for minimum 18 seconds
	delay_ms(20);
	WRITEBIT(IOPIN0,DHT11,1); // Make DHT11 pin HIGH and wait for response
}

void dht11_response(void)
{
	WRITEBIT(IODIR0,DHT11,input);	// Configure DHT11 pin as input 
	while(READBIT(IOPIN0,DHT11) == 1); // Wait till response is HIGH 
	while(READBIT(IOPIN0,DHT11) == 0); // Wait till response is LOW 
	while(READBIT(IOPIN0,DHT11) == 1); // Wait till response is HIGH  & This is end of response
}

unsigned char dht11_data(void)
{
	unsigned char count;
	unsigned char data = 0;
	for(count = 0; count<8 ; count++)	// 8 bits of data 
	{
		while(READBIT(IOPIN0,DHT11) == 0);	// Wait till response is LOW 
		delay_us(30);	// delay greater than 24 usec 
		if (READBIT(IOPIN0,DHT11)) // If response is HIGH, 1 is received 
			data = ( (data<<1) | 0x01 );
		else	// If response is LOW, 0 is received 
			data = (data<<1);
		while(READBIT(IOPIN0,DHT11));	// Wait till response is HIGH (happens if 1 is received)
	}
	return data;
}

void DTH_11(void)
{
	dht11_request();
		dht11_response();
		humidity_integer = dht11_data();
		humidity_decimal = dht11_data();
		temp_integer = dht11_data();
		temp_decimal = dht11_data();
		checksum = dht11_data();
		if( (humidity_integer + humidity_decimal + temp_integer + temp_decimal) != checksum )
			StrLCD("Checksum Error\r\n");
		else
		{
			CmdLCD(0x80);
			StrLCD("H : ");
			S32LCD(humidity_integer);
			CharLCD('.');
			S32LCD(humidity_decimal);
			StrLCD(" % RH ");
			CmdLCD(0xC0);
			StrLCD("T : ");
			S32LCD(temp_integer);
			CharLCD('.');
			S32LCD(temp_decimal);
			CharLCD(223);
			StrLCD("C");
		}
}
