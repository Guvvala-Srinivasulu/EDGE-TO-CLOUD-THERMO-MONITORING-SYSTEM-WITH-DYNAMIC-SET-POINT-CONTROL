// major.c – Application control and setting functions
#include <LPC214x.h>         // LPC214x microcontroller register definitions
#include "defines.h"         // Common project macros
#include "types.h"           // User-defined data types
#include "lcd.h"             // LCD interface functions
#include "lcd_defines.h"     // LCD command definitions
#include "kpm.h"             // Keypad module functions
#include "delay.h"           // Delay utility functions
#include "i2c_eeprom.h"      // I2C EEPROM functions
#include "i2c_defines.h"     // I2C EEPROM address definitions

#define BUZZ 6               // Buzzer connected to P0.6

u8 settemp, sethum;          // Variables to store temperature and humidity set-points

/********************************* setting temperature limit *******************************/
void setting_temperature(void)
{ 
    u8 key=0, count=0;       // Key value and digit counter
    settemp = 0;             // Reset temperature set-point
    count = 0;               // Reset digit count
    CmdLCD(CLEAR_LCD);       // Clear LCD
    StrLCD("Set Temp Setpt");// Display temperature setting message
    CmdLCD(GOTO_LINE2_POS0); // Move cursor to second line
    StrLCD("00 press '='");  // Prompt user input
    while(KeyScan() != 0);   // Wait for key release

    while(1)
    {
        key = KeyScan();     // Read key from keypad
        if(key >= '0' && key <= '9' && count < 2) // Accept only two digits
        {
            settemp = (settemp * 10) + (key - '0'); // Update set-point value
            CmdLCD(GOTO_LINE2_POS0 + count);        // Position cursor
            CharLCD(key);                           // Display digit
            count++;                                // Increment digit count
            while(ColScan()== 0);                   // Wait for key release
        }
        else if((key == 'C' || key == 'c') && count > 0) // Handle backspace
        {
            count--;                                // Decrement digit count
            settemp = settemp / 10;                 // Remove last digit
            CmdLCD(GOTO_LINE2_POS0 + count);        
            CharLCD('0');                           // Clear digit
            CmdLCD(GOTO_LINE2_POS0 + count);        
            while(ColScan() == 0);                  // Wait for key release
        }
        else if(key == '=' || count >= 2)           // Confirm input
        {
            break;                                  // Exit loop
        }
    }

    i2c_eeprom_write(I2C_EEPROM_SA,0x00,settemp); // Store temperature set-point in EEPROM

    CmdLCD(CLEAR_LCD);       // Clear LCD
    StrLCD("  Setting Temp  ");
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("    Updated     ");
    delay_ms(100);           // Short delay
    CmdLCD(CLEAR_LCD);       // Clear LCD
}

/********************************* setting humidity limit *******************************/
void setting_humidity(void)
{
    u8 key=0, count=0;       // Key value and digit counter
    sethum = 0;              // Reset humidity set-point
    count = 0;               // Reset digit count
    CmdLCD(CLEAR_LCD);       // Clear LCD
    StrLCD("Set Humi point");// Display humidity setting message
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("00 press '='");  // Prompt user input
    while(KeyScan() != 0);   // Wait for key release

    while(1)
    {
        key = KeyScan();     // Read key from keypad
        if(key >= '0' && key <= '9' && count < 2) // Accept only two digits
        {
            sethum = (sethum * 10) + (key - '0'); // Update set-point value
            CmdLCD(GOTO_LINE2_POS0 + count);
            CharLCD(key);                         // Display digit
            count++;
            while(ColScan() == 0);                // Wait for key release
        }
        else if((key == 'C' || key == 'c') && count > 0) // Handle backspace
        {
            count--;
            sethum = sethum / 10;
            CmdLCD(GOTO_LINE2_POS0 + count);
            CharLCD('0');
            CmdLCD(GOTO_LINE2_POS0 + count);
            while(ColScan() == 0);
        }
        else if(key == '=' || count >= 2)         // Confirm input
        {
            break;
        }
    }

    i2c_eeprom_write(I2C_EEPROM_SA,0x02,sethum); // Store humidity set-point in EEPROM

    CmdLCD(CLEAR_LCD);
    StrLCD("Setting Humidity");
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("    Updated     ");
    delay_s(1);
    CmdLCD(CLEAR_LCD);
}

/********************************* choice make option *******************************/
void setting_point(void)
{
    u8 option=0;             // Menu option variable

start_loop:
    CmdLCD(CLEAR_LCD);       
    CmdLCD(GOTO_LINE1_POS0);
    StrLCD("1.SET TEMP");    // Display menu option 1
    CmdLCD(GOTO_LINE2_POS0);
    StrLCD("2.SET HUM 3.EXIT"); // Display menu options

    while(1)
    {
        option = KeyScan();  // Read user option
        while(ColScan()==0);// Wait for key release

        switch(option)
        {
            case '1':
                setting_temperature(); // Call temperature setting
                goto start_loop;
            case '2':
                setting_humidity();    // Call humidity setting
                goto start_loop;
            case '3':
                CmdLCD(CLEAR_LCD);
                StrLCD("EXITING MENU....");
                CmdLCD(0x01);
                return;                // Exit menu
            default:
                CmdLCD(CLEAR_LCD);
                CmdLCD(GOTO_LINE1_POS0);
                StrLCD("INVALID KEY");
                delay_s(1);
                goto start_loop;
        }
    }
}

/********************************* Buzzer *******************************/
void Buzzer(void)
{
    u32 j;
    IODIR0 |= 1<<BUZZ;       // Configure buzzer pin as output

    for(j=0; j<10; j++)      // Generate warning alert
    {
        CmdLCD(0x01);
        IOSET0 = 1<<BUZZ;    // Turn buzzer ON
        StrLCD("!!!!WARNING!!!!");
        delay_s(1);
        IOCLR0 = 1<<BUZZ;    // Turn buzzer OFF
        delay_ms(500);
    }
    CmdLCD(0x01);            // Clear LCD after alert
}
