//lcd.c

#include "rtc_defines.h"

#ifndef _LPC2148_
#include "lpc21xx.h"
#else
#include "lpc214x.h"
#endif

#include "types.h"
#include "defines.h"
#include "lcd_defines.h"
#include "delay.h"
#include "string.h"


void WriteLcd(u8 byte)
{
	 IOCLR0=1<<LCD_RW;
	 WRITEBYTE(IOPIN0,LCD_DATA,byte);
	 IOSET0=1<<LCD_EN;
	 delay_us(1);
	 IOCLR0=1<<LCD_EN;
	 delay_ms(2);
}

void CmdLcd(u8 byte)
{
	IOCLR0=1<<LCD_RS;
	WriteLcd(byte);
}

void Init_Lcd()
{
	IODIR0|=((0XFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
	delay_ms(15);
	CmdLcd(0x30);
	delay_ms(4);
	delay_us(100);
	CmdLcd(0x30);
	delay_us(100);
	CmdLcd(0x30);
	CmdLcd(MODE_8BIT_2LINE);
	CmdLcd(DISP_ON_CUR_OFF);
	CmdLcd(CLEAR_LCD);
	CmdLcd(SHIFT_CUR_RIGHT);
}

void CharLcd(u8 ch)
{
	IOSET0=1<<LCD_RS;
	WriteLcd(ch);
}

void StrLcd(s8 *str)
{
	while(*str)
		CharLcd(*str++);
}

void U32Lcd(u32 num)
{
	s32 i=0;
	u8 a[10];
	if(num==0)
		CharLcd('0');
	else
	{
			while(num>0)
			{
				a[i++]=(num%10)+48;
				num/=10;
			}
		for(--i;i>=0;i--)
			CharLcd(a[i]);
	}
}

void F32Lcd(f32 fnum,u32 nDP)
{
	u32 num,i;
	if(fnum<0.0)
	{
		CharLcd('-');
		fnum=-fnum;
	}
	num=fnum;
	U32Lcd(num);
	CharLcd('.');
	for(i=0;i<nDP;i++)
	{
		fnum=(fnum-num)*10;
		num=fnum;
		CharLcd(num+48);
	}
}

u16 Udef_Strlen(s8 *str)
{
	u16 i=0;
	while(str[i++]);
	return i-1;
}

void Scroll_Lcd(s8 *str1,u16 GOTO_SPECIFIED_LINE)
{
	s8 ch,str2[]="               ";
	u16 l,i;
	l=Udef_Strlen(str1);
	if(l<16)
	{
		strncat(str1,str2,16-l);
		l=Udef_Strlen(str1);
	}
	while(1)
	{
		CmdLcd(GOTO_SPECIFIED_LINE);
		for(i=0;i<16;i++)
				CharLcd(str1[i]);
		delay_ms(100);
		ch=str1[0];
		memmove(str1,str1+1,l);
		str1[l]=ch;
	}
}

void BuildCgram(u8 *p,u8 nBytes)
{
	u32 i;
	//point to cgram start
	CmdLcd(GOTO_CGRAM_START);
	//select data reg
	IOSET0=1<<LCD_RS;
	
	for(i=0;i<nBytes;i++)
	{
		//write to cgram vi data reg
		WriteLcd(p[i]);
	}
	//point back to ddram start/display
	CmdLcd(GOTO_LINE1_POS0);
}
