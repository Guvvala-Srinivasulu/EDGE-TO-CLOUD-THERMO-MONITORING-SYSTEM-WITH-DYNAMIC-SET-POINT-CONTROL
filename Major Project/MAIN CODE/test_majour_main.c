#include <lpc21xx.h>        // LPC21xx microcontroller register definitions
#include "lcd.h"            // LCD driver functions
#include "uart0.h"          // UART0 communication functions
#include "dht11.h"          // DHT11 temperature and humidity sensor functions
#include "esp01.h"          // ESP8266 Wi-Fi module functions
#include "rtc.h"            // Real Time Clock functions
#include "i2c.h"            // I2C protocol functions
#include "eint.h"           // External interrupt functions
#include "delay.h"          // Delay utility functions
#include "kpm.h"            // Keypad module functions
#include "types.h"          // User-defined data types
#include "major.h"          // Project-specific definitions
#include "i2c_eeprom.h"     // I2C EEPROM functions
#include "i2c_defines.h"    // I2C EEPROM definitions

unsigned char humidity_integer, humidity_decimal, temp_integer, temp_decimal, checksum; // Sensor data variables
u8 p,q;                     // Set-point values from EEPROM
char buff[200];             // UART receive buffer
u32 min;                    // Minute tracking variable
unsigned char i;            // Buffer index variable
u32 flag_int;               // External interrupt flag

int main()
{
    init_i2c();             // Initialize I2C communication
    Init_LCD();             // Initialize LCD
    RTC_Init();             // Initialize RTC
    InitUART0();            // Initialize UART0
    RTC_Init();             // Re-initialize RTC
    Init_EINT();            // Initialize external interrupt
    Init_KPM();             // Initialize keypad module
    esp01_connectAP();      // Connect ESP01 to Wi-Fi access point
    min = MIN;              // Store current minute value

    while(1)
    {
        p = i2c_eeprom_read(I2C_EEPROM_SA,0x00); // Read temperature set-point from EEPROM
        q = i2c_eeprom_read(I2C_EEPROM_SA,0x02); // Read humidity set-point from EEPROM
        CmdLCD(0xD4);        // Move LCD cursor to specific position

        if(flag_int == 1)   // Check if external interrupt occurred
        {
            flag_int = 0;   // Clear interrupt flag
            setting_point(); // Update set-point using keypad
        }

        DTH_11();           // Read temperature and humidity from DHT11 sensor

        if(MIN == min)      // Check periodic data upload condition
        {
            esp01_sendToThingspeak(temp_integer,1); // Send temperature to ThingSpeak
            delay_s(1);     // Delay between transmissions
            esp01_sendToThingspeak(humidity_integer,2); // Send humidity to ThingSpeak
            min += 3;       // Update next transmission interval
        }

        if(flag_int == 1)   // Check interrupt again
        {
            flag_int = 0;   // Clear interrupt flag
            setting_point(); // Update set-point
        }

        if(MIN == 59)       // Check minute rollover condition
        {
            min = 0;        // Reset minute counter
        }

        if((temp_integer >= p) || (humidity_integer >= q)) // Check threshold violation
        {
            Buzzer();       // Activate buzzer alert
            esp01_sendToThingspeak(temp_integer,1); // Send temperature alert
            delay_ms(1000);
            esp01_sendToThingspeak(humidity_integer,2); // Send humidity alert
            delay_ms(1000);
            esp01_sendToThingspeak(p,3); // Send set-point value
        }
    }
}
