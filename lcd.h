//lcd.h

#include"types.h"

void Init_Lcd(void);
void CmdLcd(u8);
void WriteLcd(u8);
void CharLcd(u8);
void StrLcd(s8*);
void U32Lcd(u32);
void F32Lcd(f32,u32);
void BuildCgram(u8*,u8);
u16 Udef_Strlen(s8 *);
void Scroll_Lcd(s8 *,u16);
