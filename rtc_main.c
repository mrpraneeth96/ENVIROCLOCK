//rtc_main.c

#include "rtc_defines.h"

#ifndef _LPC2148_
#include "lpc21xx.h"
#else
#include "lpc214x.h"
#endif

#include "adc.h"
#include "adc_defines.h"
#include "types.h"
#include "rtc.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "kpm_defines.h"
#include "kpm.h"
#include "interrupt.h"
#include "defines.h"

u32 hour,min,sec,day,date,month,year,adcVal,temp;
s32 alhr=-1,almin=-1,alflag;
f32 eAr;
u8 cgramLUT[24]=
{
	0x00,0x04,0x0E,0x15,0x04,0x04,0x04,0x00,
	0x00,0x04,0x04,0x04,0x15,0x0E,0x04,0x00,
	0x0A,0x04,0x0E,0x15,0x17,0x11,0x0E,0x00
};



main()
{
        Init_Rtc();
        Init_Lcd();
				Init_Kpm();
				Init_ADC();
				Init_Interrupt();
				Init_Alm_Interrupt();
	    SetRTCtimeInfo(8,30,30);
        SetRTCdateInfo(31,03,2004);
        SetRTCday(5);
				WRITEBIT(IODIR0,5,1);	//alarm indiction pin
				BuildCgram(cgramLUT,24);
				CmdLcd(CLEAR_LCD);
        while(1)
        {
				getRTCtimeInfo(&hour,&min,&sec);
                DisplayRTCtimeInfo(hour,min,sec);
                getRTCdayInfo(&day);
                DisplayRTCdayInfo(day);
                getRTCdateInfo(&date,&month,&year);
                DisplayRTCdateInfo(date,month,year);
				Read_ADC(1,&adcVal,&eAr);
				temp=GetEquivalentTemp(adcVal);
				DisplayTemperature(temp);
				if(alflag)
				{
					CmdLcd(GOTO_LINE1_POS0+14);
					CharLcd(2);	
				}
				else
				{
					CmdLcd(GOTO_LINE1_POS0+14);
					CharLcd(' ');
					
				}
				ScanAlarm();
		}
}
