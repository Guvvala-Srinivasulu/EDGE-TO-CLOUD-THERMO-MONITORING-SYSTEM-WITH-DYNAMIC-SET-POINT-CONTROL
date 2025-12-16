#include"lcd.h"
#include"LCD_defines.h"
#include"delay.h"
/*u8 cgramlut[16]=
{
	0x1d,0x05,0x05,0x1f,0x14,0x14,0x17,0x00,
	0x15,0x15,0x15,0x1f,0x04,0x04,0x04,0x00
}; */
main()
{
Init_LCD();

/*CharLCD('A');
StrLCD("v24he11s12_ARM");
CmdLCD(GOTO_LINE2_POS0);
U32LCD(123456790);
delay_ms(1000);
CmdLCD(CLEAR_LCD);
S32LCD(-654321);
delay_ms(1000);
CmdLCD(CLEAR_LCD);
F32LCD(-65.123456,3);*/
CmdLCD(GOTO_LINE2_POS0);
F32LCD(123.456789,3);
/*delay_ms(1000);
CmdLCD(CLEAR_LCD);
BuildCGRAM(cgramlut,16);
CharLCD(0);
CharLCD(1);*/
while(1);
}
