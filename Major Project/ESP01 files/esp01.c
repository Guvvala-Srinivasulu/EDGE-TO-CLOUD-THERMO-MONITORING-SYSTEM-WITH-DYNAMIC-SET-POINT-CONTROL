#include <string.h>      // String handling functions
#include "uart0.h"       // UART communication functions
#include "delay.h"       // Software delay functions
#include "lcd.h"         // LCD control functions

extern char buff[200];   // UART receive buffer
extern unsigned char i;  // Buffer index variable

// Function to initialize ESP-01 module and connect to Wi-Fi access point
void esp01_connectAP()
{
    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // Move cursor to first line
    StrLCD("AT");        // Display AT command on LCD
    delay_ms(1000);      // Delay for command stability
    UART0_Str("AT\r\n"); // Send AT command to ESP module
    i=0; memset(buff,'\0',200); // Clear buffer and reset index
    while(i<4);          // Wait for response
    delay_ms(500);       // Delay after response
    buff[i] = '\0';      // Null terminate received string
    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // Move cursor to first line
    StrLCD(buff);        // Display response on LCD
    delay_ms(2000);      // Display delay
    if(strstr(buff,"OK"))// Check AT command response
    {
        CmdLCD(0xC0);    // Move cursor to second line
        StrLCD("OK");   // Display OK
        delay_ms(1000);        
    }
    else
    {
        CmdLCD(0xC0);    // Move cursor to second line
        StrLCD("ERROR");// Display error
        delay_ms(1000);        
        return;          // Exit on error
    }

    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // First line
    StrLCD("ATE0");     // Display echo disable command
    delay_ms(1000);      // Delay
    UART0_Str("ATE0\r\n");// Disable echo
    i=0; memset(buff,'\0',200); // Reset buffer
    while(i<4);          // Wait for response
    delay_ms(500);       // Delay
    buff[i] = '\0';      // Null terminate
    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // First line
    StrLCD(buff);        // Show response
    delay_ms(2000);      // Delay
    if(strstr(buff,"OK"))// Check response
    {
        CmdLCD(0xC0);    // Second line
        StrLCD("OK");   // Display OK
        delay_ms(1000);        
    }
    else
    {
        CmdLCD(0xC0);    // Second line
        StrLCD("ERROR");// Display error
        delay_ms(1000);        
        return;          // Exit on error
    }

    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // First line
    StrLCD("AT+CIPMUX");// Display command
    delay_ms(1000);      // Delay
    UART0_Str("AT+CIPMUX=0\r\n"); // Set single connection mode
    i=0; memset(buff,'\0',200); // Reset buffer
    while(i<4);          // Wait for response
    delay_ms(500);       // Delay
    buff[i] = '\0';      // Null terminate
    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // First line
    StrLCD(buff);        // Show response
    delay_ms(2000);      // Delay
    if(strstr(buff,"OK"))// Check response
    {
        CmdLCD(0xC0);    // Second line
        StrLCD("OK");   // Display OK
        delay_ms(1000);        
    }
    else
    {
        CmdLCD(0xC0);    // Second line
        StrLCD("ERROR");// Display error
        delay_ms(1000);        
        return;          // Exit on error
    }

    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // First line
    StrLCD("AT+CWQAP"); // Display disconnect command
    delay_ms(1000);      // Delay
    UART0_Str("AT+CWQAP\r\n"); // Disconnect from AP
    i=0; memset(buff,'\0',200); // Reset buffer
    while(i<4);          // Wait for response
    delay_ms(1500);      // Delay
    buff[i] = '\0';      // Null terminate
    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // First line
    StrLCD(buff);        // Show response
    delay_ms(2000);      // Delay
    if(strstr(buff,"OK"))// Check response
    {
        CmdLCD(0xC0);    // Second line
        StrLCD("OK");   // Display OK
        delay_ms(1000);        
    }
    else
    {
        CmdLCD(0xC0);    // Second line
        StrLCD("ERROR");// Display error
        delay_ms(1000);        
        return;          // Exit on error
    }

    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // First line
    StrLCD("AT+CWJAP"); // Display Wi-Fi join command
    delay_ms(1000);      // Delay
    UART0_Str("AT+CWJAP=\"Airtel5\",\"11111119\"\r\n"); // Connect to Wi-Fi
    i=0; memset(buff,'\0',200); // Reset buffer
    while(i<4);          // Wait for response
    delay_ms(2500);      // Delay
    buff[i] = '\0';      // Null terminate
    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // First line
    StrLCD(buff);        // Show response
    delay_ms(2000);      // Delay
    if(strstr(buff,"WIFI CONNECTED")) // Check Wi-Fi connection
    {
        CmdLCD(0xC0);    // Second line
        StrLCD("OK");   // Display OK
        delay_ms(1000);        
    }
    else
    {
        CmdLCD(0xC0);    // Second line
        StrLCD("ERROR");// Display error
        delay_ms(1000);        
        return;          // Exit on error
    }
}

// Function to send sensor data to ThingSpeak cloud platform
void esp01_sendToThingspeak(char val,int field)
{
    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // First line
    StrLCD("AT+CIPSTART");// Display TCP start command
    delay_ms(1000);      // Delay
    UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n"); // Open TCP connection
    i=0; memset(buff,'\0',200); // Reset buffer
    while(i<5);          // Wait for response
    delay_ms(2500);      // Delay
    buff[i] = '\0';      // Null terminate
    CmdLCD(0x01);        // Clear LCD
    CmdLCD(0x80);        // First line
    StrLCD(buff);        // Show response
    delay_ms(2000);      // Delay
    if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED")) // Check TCP status
    {
        CmdLCD(0xC0);    // Second line
        StrLCD("OK");   // Display OK
        delay_ms(1000);

        CmdLCD(0x01);    // Clear LCD
        CmdLCD(0x80);    // First line
        StrLCD("AT+CIPSEND");// Display send command
        delay_ms(1000);  
        UART0_Str("AT+CIPSEND=49\r\n"); // Set data length
        i=0; memset(buff,'\0',200); // Reset buffer
        delay_ms(500);   // Wait for prompt

        if(field==1) UART0_Str("GET /update?api_key=OZHUWW8P3F7ED3Y1&field1="); // Field 1 update
        if(field==2) UART0_Str("GET /update?api_key=OZHUWW8P3F7ED3Y1&field2="); // Field 2 update
        if(field==3) UART0_Str("GET /update?api_key=OZHUWW8P3F7ED3Y1&field3="); // Field 3 update
        UART0_Int(val);  // Send data value
        UART0_Str("\r\n\r\n"); // End HTTP request
        delay_ms(10000);// Wait for response
        buff[i] = '\0';  // Null terminate
        CmdLCD(0x01);    // Clear LCD
        CmdLCD(0x80);    // First line
        StrLCD(buff);    // Show response
        delay_ms(2000);  

        if(strstr(buff,"SEND OK")) // Check data transmission
        {
            CmdLCD(0x01); 
            StrLCD("DATA UPDATED"); // Data sent successfully
            delay_ms(1000);            
        }
        else
        {
            CmdLCD(0x01);
            StrLCD("DATA NOT UPDATED"); // Data send failed
            delay_ms(1000);    
        }
    }
    else
    {
        CmdLCD(0xC0);
        StrLCD("ERROR"); // TCP connection error
        delay_ms(1000);        
        return;
    }
}
