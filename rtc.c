//rtc.c

#include "rtc_defines.h"

#ifndef _LPC2148_
#include "lpc21xx.h"
#else
#include "lpc214x.h"
#endif

#include "types.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "defines.h"

s8 days[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
extern s32 alhr,almin,alflag;

void Init_Rtc(void)
{
        //RESET RTC
        CCR=(1<<1);
				#ifndef _LPC2148_
        PREINT=PREINT_VAL;
        PREFRAC=PREFRAC_VAL;
				CCR=1<<0;
				#else
				CCR|=((1<<0)|(1<<4));
        #endif
}

void SetRTCtimeInfo(u32 hour,u32 min,u32 sec)
{
        HOUR=hour;
        MIN=min;
        SEC=sec;
}

void SetRTCdateInfo(u32 date,u32 month,u32 year)
{
        DOM=date;
        MONTH=month;
        YEAR=year;
}

void SetRTCday(u32 day)
{
        DOW=day;
}

void getRTCtimeInfo(u32 *hour,u32 *min,u32 *sec)
{
        *hour=HOUR;
        *min=MIN;
        *sec=SEC;
}

void DisplayRTCtimeInfo(u32 hour,u32 min,u32 sec)
{
        CmdLcd(GOTO_LINE1_POS0);
        CharLcd(((hour/10)+48));
        CharLcd((hour%10)+48);
        CharLcd(':');
        CharLcd((min/10)+48);
        CharLcd((min%10)+48);
        CharLcd(':');
        CharLcd((sec/10)+48);
        CharLcd((sec%10)+48);
}

void getRTCdateInfo(u32 *date,u32 *month,u32 *year)
{
        *date=DOM;
        *month=MONTH;
        *year=YEAR;
}

void DisplayRTCdateInfo(u32 date,u32 month,u32 year)
{
        CmdLcd(GOTO_LINE2_POS0);
        CharLcd((date/10)+48);
        CharLcd((date%10)+48);
        CharLcd('/');
        CharLcd((month/10)+48);
        CharLcd((month%10)+48);
        CharLcd('/');
        U32Lcd(year);
}

void getRTCdayInfo(u32 *day)
{
        *day=DOW;
}

void DisplayRTCdayInfo(u32 day)
{
        CmdLcd(GOTO_LINE1_POS0+10);
        StrLcd(days[day]);
}

void ScanAlarm(void)
{
	if(alhr==HOUR && almin==MIN)
		alflag=1;
	else if((alhr==HOUR)&&((almin+1)&&MIN))
	{
		almin=-1;
		alhr=-1;
	}
	else
	{
		WRITEBIT(IOPIN0,5,0);
		alflag=0;
	}
}
void RingAlarm(void)
{
	  WRITEBIT(IOPIN0,5,1);
}
