
#include "types.h"

void CmdLCD(u8 cmdByte);
void CharLCD(u8 asciiVal);
void WriteLCD(u8 byte);
void Init_LCD(void);
void StrLCD(char *str);
void StrLCDn(s8 *str);
void U32LCD(u32 n);
void S32LCD(s32 num);
void F32LCD(f32,u32);
void BuildCGRAM(u8 *p,u8 nBytes);


