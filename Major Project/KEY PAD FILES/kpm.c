// kpm.c – Keypad Module Source File
#include "types.h"          // User-defined data types
#include <LPC21xx.h>        // LPC21xx microcontroller definitions
#include "defines.h"        // General project macros
#include "kpm_defines.h"    // Keypad-specific definitions
#include "lcd_defines.h"    // LCD command definitions
#include "lcd.h"            // LCD interface functions

// Lookup table to map keypad rows and columns to characters
u8 kpmLUT[4][4]=
{
    {'7','8','9','/'},
    {'4','5','6','X'},
    {'1','2','3','-'},
    {'C','0','=','+'}
};

// Function to initialize keypad rows and columns
void Init_KPM(void)
{
    WRITENIBBLE(IODIR1,ROWs_4,15); // Configure row pins as GPIO outputs and ground them
    // Column pins remain configured as GPIO inputs by default
}

// Function to check whether any column line is active
u32 ColScan(void)
{
    return (READNIBBLE(IOPIN1,COLs_4)<15)? 0 : 1; // Detect key press on any column
}

// Function to identify the row in which the key is pressed
u32 RowCheck(void)
{
    u32 r;
    for(r=0;r<=3;r++)
    {
        WRITENIBBLE(IOPIN1,ROWs_4,~(1<<r)); // Ground one row at a time
        if(ColScan()==0)                   // Check if key is pressed in this row
        {
            break;
        }			
    }
    WRITENIBBLE(IOPIN1,ROWs_4,0);           // Re-ground all rows after scan
    return r;                               // Return detected row number
}

// Function to identify the column in which the key is pressed
u32 ColCheck(void)
{
    u32 c;
    for(c=0;c<=3;c++)
    {
        if(READBIT(IOPIN1,COL0+c)==0)       // Check which column line is active
        {
            break;
        }
    }
    return c;                               // Return detected column number
}

// Function to scan keypad and return the pressed key value
u32 KeyScan(void)
{
    u32 r,c,keyV;
    while(ColScan());                      // Wait until a key press is detected
    r=RowCheck();                          // Identify row of pressed key
    c=ColCheck();                          // Identify column of pressed key
    keyV=kpmLUT[r][c];                     // Map row and column to key value
    return keyV;                           // Return key value
}

// Function to read a multi-digit number from keypad
void ReadNum(u32 *num,u8 *key)
{
    *num=0;                                // Initialize number to zero
    while(1)
    {
        *key=KeyScan();                   // Read key from keypad
        if(*key>='0' && *key<='9')         // Check if key is a numeric digit
        {
            *num=(*num*10)+(*key-48);      // Convert ASCII to integer and accumulate
            CmdLCD(GOTO_LINE2_POS0);       // Move LCD cursor to second line
            U32LCD(*num);                 // Display number on LCD
            while(ColScan()==0);           // Wait until key is released
        }
        else
        {
            CharLCD(' ');                 // Print space on LCD
            CharLCD(*key);                // Display non-numeric key
            while(ColScan()==0);           // Wait until key is released
            break;                        // Exit loop on non-numeric key
        }
    }
}
