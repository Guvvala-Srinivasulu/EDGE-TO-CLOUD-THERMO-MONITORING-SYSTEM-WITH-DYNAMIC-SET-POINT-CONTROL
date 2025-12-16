
#include<lpc214x.h>
#include "rtc_defines.h"
#include "rtc.h"

void RTC_Init(void) 
{
  // Disable and reset the RTC
	/*#ifndef _LPC2148_
	CCR = RTC_RESET;*/
	// Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
//	CCR = RTC_ENABLE; 
  /*#else*/
	CCR = RTC_reset;
  // Enable the RTC
	CCR = RTC_enable|RTC_osc; 
	//#endif 
	MIN=1; //Initialized minutes

}

void set_rtc(void)
{
}

