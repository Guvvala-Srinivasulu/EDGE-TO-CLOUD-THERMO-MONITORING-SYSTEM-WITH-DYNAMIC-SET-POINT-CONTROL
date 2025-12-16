#ifndef _LPC2148_
#include <lpc21xx.h>          // Header file for LPC21xx series
#else
#include <lpc214x.h>          // Header file for LPC214x series
#endif

#include "kpm.h"              // Keypad module definitions
#include "delay.h"            // Delay function declarations
#include "eint_defines.h"     // External interrupt definitions
#include "eint.h"             // External interrupt function prototypes
#include "major.h"            // Main project definitions
#include "pin_connect_block.h"// Pin function configuration utilities

extern u32 flag_int;          // Global flag set by external interrupt

// Function to initialize external interrupt configuration
void Init_EINT(void)
{
    CfgPortPinFunc(0,14,EINT0_0_1); // Configure P0.14 as external interrupt pin
    VICIntEnable |= 1<<EINT1_VIC_CHN0; // Enable EINT1 interrupt in VIC
    VICVectCntl1 = (1<<5) | EINT1_VIC_CHN0; // Assign interrupt channel and enable slot
    VICVectAddr1 = (u32)eint0_isr; // Set ISR address for external interrupt
    EXTMODE = 1<<1;              // Configure EINT1 as edge-triggered interrupt
}

// External interrupt service routine
void eint0_isr(void) __irq
{
    flag_int = 1;                // Set interrupt flag
    EXTINT = 1<<1;               // Clear external interrupt flag
    VICVectAddr = 0;             // Acknowledge interrupt to VIC
}
