#include "types.h"   // Contains user-defined data types such as u32
#include "delay.h"   // Header file for delay function declarations

/*-------------------------------------------------
 Function Name : delay_ms
 Description   : Generates a blocking delay in milliseconds
 Argument      : dlyms - delay time in milliseconds
 Note          : Delay is generated using a software loop
--------------------------------------------------*/
void delay_ms(u32 dlyms)
{
    dlyms *= 12000;        // Calibrate loop count for 1 ms delay
    while(dlyms--);       // Busy-wait loop
}

/*-------------------------------------------------
 Function Name : delay_us
 Description   : Generates a blocking delay in microseconds
 Argument      : dlyus - delay time in microseconds
 Note          : Suitable for short time delays only
--------------------------------------------------*/
void delay_us(u32 dlyus)
{
    dlyus *= 12;           // Calibrate loop count for 1 µs delay
    while(dlyus--);       // Busy-wait loop
}

/*-------------------------------------------------
 Function Name : delay_s
 Description   : Generates a blocking delay in seconds
 Argument      : dlys - delay time in seconds
 Note          : Uses a long busy-wait loop; CPU remains occupied
--------------------------------------------------*/
void delay_s(u32 dlys)
{
    dlys *= 12000000;      // Calibrate loop count for 1 second delay
    while(dlys--);        // Busy-wait loop
}
