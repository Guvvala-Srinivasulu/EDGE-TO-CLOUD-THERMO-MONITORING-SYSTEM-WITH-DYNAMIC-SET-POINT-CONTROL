#ifndef RTCDEFINES_H
#define RTCDEFINES_H

#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)

#define PREINT_VAL ((int)((PCLK / 32768) - 1))
#define PREFRAC_VAL (PCLK - ((PREINT_VAL+1)*32768))

#define RTC_enable (1<<0) 
#define RTC_reset  (1<<1)  
#define RTC_osc (1<<4)

//interrupt
#define AH_BUZZER 5

#endif


