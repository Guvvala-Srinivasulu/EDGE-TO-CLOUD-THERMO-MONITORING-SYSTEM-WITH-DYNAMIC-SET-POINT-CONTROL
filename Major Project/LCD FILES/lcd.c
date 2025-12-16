// lcd.c – LCD Driver Source File
#include <lpc21xx.h>          // LPC21xx register definitions

#include "types.h"            // User-defined data types
#include "defines.h"          // Common project macros
#include "lcd.h"              // LCD function prototypes
#include "delay.h"            // Delay functions
#include "lcd_defines.h"      // LCD pin and command definitions

// Function to write a byte to LCD data pins
void WriteLCD(u8 byte)
{
    IOCLR0 = 1<<LCD_RW;                    // Select write operation
    WRITEBYTE(IOPIN0, LCD_DATA, byte);     // Write data/command byte to LCD
    IOSET0 = 1<<LCD_EN;                    // Enable pulse high
    delay_us(1);                           // Small enable pulse width delay
    IOCLR0 = 1<<LCD_EN;                    // Enable pulse low
    delay_ms(2);                           // Command execution delay
}

// Function to send command to LCD
void CmdLCD(u8 cmdByte)
{
    IOCLR0 = 1<<LCD_RS;                    // Select command register
    WriteLCD(cmdByte);                     // Write command to LCD
}

// Function to initialize LCD in 8-bit mode
void Init_LCD(void)
{
    IODIR0 |= ((0xFF<<LCD_DATA) |           // Configure data pins as output
               (1<<LCD_RS) | (1<<LCD_RW) | (1<<LCD_EN)); // Configure control pins

    delay_ms(15);                           // Power-on initialization delay
    CmdLCD(0x30);                           // Wake-up command
    delay_ms(4);
    delay_us(100);
    CmdLCD(0x30);                           // Repeat wake-up
    delay_us(100);
    CmdLCD(0x30);                           // Final wake-up
    CmdLCD(MODE_8BIT_2LINE);                // Set 8-bit, 2-line mode
    CmdLCD(DSP_ON_CUR_OFF);                 // Display ON, cursor OFF
    CmdLCD(CLEAR_LCD);                      // Clear display
    CmdLCD(SHIFT_CUR_RIGHT);                // Cursor shift right
}

// Function to display a single character on LCD
void CharLCD(u8 asciiVal)
{
    IOSET0 = 1<<LCD_RS;                     // Select data register
    WriteLCD(asciiVal);                     // Write ASCII value to LCD
}

// Function to display a string on LCD
void StrLCD(char *str)
{
    while(*str)                             // Loop until null character
        CharLCD(*str++);                   // Display each character
}

// Function to display fixed-length string on LCD
void StrLCDn(s8 *str)
{
    int n=0;
    while(n<17)                             // Display 16 characters
    {
        n++;
        CharLCD(*str++);                   // Display character
    }
}

// Function to display unsigned 32-bit integer on LCD
void U32LCD(u32 n)
{
    s32 i=0;
    u8 a[10];

    if(n==0)
    {
        CharLCD('0');                      // Display zero
    }
    else
    {
        while(n>0)
        {
            a[i++] = (n%10) + 48;           // Convert digit to ASCII
            n /= 10;                        // Remove last digit
        }
        for(--i; i>=0; i--)
            CharLCD(a[i]);                 // Display digits in correct order
    }
}

// Function to display signed 32-bit integer on LCD
void S32LCD(s32 num)
{
    if(num<0)
    {
        CharLCD('-');                      // Display negative sign
        num = -num;                        // Convert to positive
    }
    U32LCD(num);                           // Display number
}

// Function to display floating-point number on LCD
void F32LCD(f32 fnum, u32 nDP)
{
    u32 num,i;
    if(fnum<0.0)
    {
        CharLCD('-');                      // Display negative sign
        fnum = -fnum;                      // Convert to positive
    }
    num = fnum;                            // Extract integer part
    U32LCD(num);                           // Display integer part
    CharLCD('.');                          // Display decimal point
    for(i=0;i<nDP;i++)
    {
        fnum = (fnum-num)*10;              // Shift decimal
        num = fnum;                        // Extract decimal digit
        CharLCD(num+48);                   // Display decimal digit
    }
}

// Function to build custom characters in CGRAM
void BuildCGRAM(u8 *p, u8 nBytes)
{
    u32 i;
    CmdLCD(GOTO_CGRAM_START);               // Set CGRAM address
    IOSET0 = 1<<LCD_RS;                    // Select data register

    for(i=0;i<nBytes;i++)
    {
        WriteLCD(p[i]);                    // Write custom character data
    }
    CmdLCD(GOTO_LINE1_POS0);                // Return to DDRAM
}
