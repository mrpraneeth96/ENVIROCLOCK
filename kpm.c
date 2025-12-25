//kpm.c

#include "rtc_defines.h"

#ifndef _LPC2148_
#include "lpc21xx.h"
#else
#include "lpc214x.h"
#endif

#include "defines.h"
#include "kpm_defines.h"
#include "types.h"
#include "lcd_defines.h"
#include "lcd.h"

u8 kpm_lut[4][4]={{'1','2','3','B'},
									 {'4','5','6','E'},
									 {'7','8','9','='},
									 {'S','0','<','>'}};

void Init_Kpm(void)
{
	//cfg rows as o/p pins @p1.16 to p1.19
	WRITENIBBLE(IODIR1,ROWS,0X0F);
	//cfg rows as I/p pins @p1.20 to p1.23
	//WRITENIBBLE(IODIR1,COLS,0X00);
}

u32 ColScan(void)
{
	return (READNIBBLE(IOPIN1,COLS)<15?0:1);
}

u32 RowCheck(void)
{
	u32 r;
	for(r=0;r<4;r++)
	{
		WRITENIBBLE(IOPIN1,ROWS,~(1<<r));
		if(ColScan()==0)
			break;
	}
	WRITENIBBLE(IOPIN1,ROWS,0x00);
	return r;
}

u32 ColCheck(void)
{
	u32 c;
	for(c=0;c<4;c++)
	{
		if(READBIT(IOPIN1,(COLS+c))==0)
			break;
	}
	return c;
}

u32 KeyScan(void)
{
	u32 r,c;
	u8 keyval;
	//wait until any key is pressed
	while(ColScan());
	//get the row number
	r=RowCheck();
	//get col number 
	c=ColCheck();
	keyval=kpm_lut[r][c];
	return keyval;
}

void ReadNum(u32 *num,u8 *key)
{
	*num=0;
	while(1)
	{
		*key=KeyScan();
		if(*key>='0' && *key<='9')
		{
			*num=(*num*10)+(*key-48);
			CmdLcd(GOTO_LINE2_POS0);
			U32Lcd(*num);
			while(ColScan()==0);
    }
    else
    {
			CharLcd(' ');
			CharLcd(*key);
			while(ColScan()==0);
			break;		
    }    		
	}
}
