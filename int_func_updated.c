//interrupt_func.c

#include "rtc_defines.h"

#ifndef _LPC2148_
#include "lpc21xx.h"
#else
#include "lpc214x.h"
#endif

#include "pin_function_defines.h"
#include "pin_connect_block.h"
#include "kpm_defines.h"
#include "kpm.h"
#include "lcd.h"
#include "lcd_defines.h"
#include "delay.h"
#include "types.h"
#include "rtc.h"
#include "defines.h"

#define DELAY delay_ms(200)

extern u32 hour,min,sec,day,date,month,year;
extern s32 alhr,almin,alflag;
extern u8 cgramLUT[16];
u8 keyval,flag;

s32 Read_Digits(char *s,int maximum,int minimum,int digits,char* emsg)
{
	int num=0,flag=0;
	char str[]="     ";
	CmdLcd(CLEAR_LCD);
	while(1)
	{
		CmdLcd(GOTO_LINE1_POS0);
		StrLcd(s);
		keyval=KeyScan();
		while(ColScan()==0);
		DELAY;
		if((keyval>='0' && keyval<='9'))
		{
				flag=1;
				num=(num*10)+(keyval-48);
				CmdLcd(GOTO_LINE2_POS0);
				U32Lcd(num);
				if(num>maximum || num<minimum)
				{
						flag=0;
						CmdLcd(GOTO_LINE1_POS0);
						StrLcd(emsg);
						delay_s(1);
						num=0;
						CmdLcd(CLEAR_LCD);
				}
				/*else
				{
						if(KeyScan()=='=')
						{
							while(ColScan()==0);
							return num;
						} 
				} */
    	}
	   else if(keyval=='=' && flag==1)
	   {
		   return 1;
	   }
		else if(keyval=='B'  && num<digits+1)
		{
			num=num/10;
			CmdLcd(GOTO_LINE2_POS0);
			StrLcd(str);
			CmdLcd(GOTO_LINE2_POS0);
			U32Lcd(num);
		}
		else if(keyval=='E')
		{
			CmdLcd(CLEAR_LCD);
			return -1;
		}
	}
}


void sethour(void)
{
	static int hour=0;
	hour=Read_Digits("EDIT HOUR",23,0,99,"HOUR RANGE(0-23)");
	if(hour!=-1)
		HOUR=hour;
}
void setmin(void)
{
	static int min=0;
	min=Read_Digits("EDIT MINUTES",59,0,99,"MIN RANGE(0-59)");
	if(min!=-1)
		MIN=min;
}

void setsec(void)
{
	static int sec=0;
	sec=Read_Digits("EDIT SECONDS",59,0,99,"SEC RANGE(0-59)");
	if(sec!=-1)
		SEC=sec;
}
void setdate(void)
{
	static int date=0;
	date=Read_Digits("EDIT DATE",31,1,99,"DATE RANGE(1-31)");
	if(date!=-1)
		DOM=date;
}
void setmonth(void)
{
	static int mon=0;
	mon=Read_Digits("EDIT MONTH",12,1,99,"MON RANGE(1-12)");
	if(mon!=-1)
		MONTH=mon;
}
void setyear(void)
{
	static int year=0;
	year=Read_Digits("EDIT YEAR",4095,0,9999,"YEAR(0-4095)");
	if(year!=-1)
		YEAR=year;
}
void setday(void)
{
	static int day=0;
	day=Read_Digits("EDIT DAY",6,0,9,"DAY RANGE(0-6)");
	if(day!=-1)
		DOW=day;
}


void edit_info()
{
	u32 disp=1,flag=0;
	BuildCgram(cgramLUT,16);
	while(1)
	{
		if(disp==1)
		{					
							 CmdLcd(CLEAR_LCD);
							 CmdLcd(GOTO_LINE1_POS0);
							 StrLcd("1.EDIT HOUR");
							 CmdLcd(GOTO_LINE1_POS0+15);
							 CharLcd(0);
							 CmdLcd(GOTO_LINE2_POS0);
							 StrLcd("2.EDIT MINUTES");
							 CmdLcd(GOTO_LINE2_POS0+15);
							 CharLcd(1);
		}
			        
		else if(disp==2)
			{
							 CmdLcd(CLEAR_LCD);
							 CmdLcd(GOTO_LINE1_POS0);
							 StrLcd("3.EDIT SECONDS");
							 CmdLcd(GOTO_LINE1_POS0+15);
							 CharLcd(0);
							 CmdLcd(GOTO_LINE2_POS0);
							 StrLcd("4.EDIT DATE");
							 CmdLcd(GOTO_LINE2_POS0+15);
							 CharLcd(1);
			}
		else if(disp==3)
			{
				       CmdLcd(CLEAR_LCD);
							 CmdLcd(GOTO_LINE1_POS0);
							 StrLcd("5.EDIT MONTH");
							 CmdLcd(GOTO_LINE1_POS0+15);
							 CharLcd(0);
							 CmdLcd(GOTO_LINE2_POS0);
							 StrLcd("6.EDIT YEAR");
							 CmdLcd(GOTO_LINE2_POS0+15);
							 CharLcd(1);
			}
		else if(disp==4)
			{
				       CmdLcd(CLEAR_LCD);
							 CmdLcd(GOTO_LINE1_POS0);
							 StrLcd("7.EDIT DAY");
							 CmdLcd(GOTO_LINE1_POS0+15);
							 CharLcd(0);
							 CmdLcd(GOTO_LINE2_POS0);
							 StrLcd("E.EXIT");
							 CmdLcd(GOTO_LINE2_POS0+15);
							 CharLcd(1);
			}
		keyval=KeyScan();
		while(ColScan()==0);
     	DELAY;
		switch(keyval)
			{
					case'1':sethour();
									break;
					case'2':setmin();
									break;
					case'3':setsec();
									break;
					case'4':setdate();
									break;
					case'5':setmonth();
									break;
					case'6':setyear();
									break;
					case'7':setday();
									break;
					case '<' : disp--;
							   if(disp<1)
							      disp=1;
							   break;
					case '>':	disp++;
								if(disp>4)
									disp=4;
								break;
					case'E':flag=1;
									CmdLcd(CLEAR_LCD);
									break;
			}
			if(flag)
				break;
	}
}

s32 setalarmhour(void)
{
	int hour=0;
	CmdLcd(GOTO_LINE2_POS0);
	while(1)
	{
		keyval=KeyScan();
		while(ColScan()==0);
		DELAY;
		if((keyval>='0') && (keyval<='9'))
		{
				hour=(hour*10)+(keyval-48);
				CmdLcd(GOTO_LINE2_POS0);
				if(hour>99)
					hour=hour/10;
				U32Lcd(hour);
		}
		else if ((hour<24)&&(keyval=='='))
		{
				alhr=hour;
				return 1;
		}
		else if(keyval=='B' && hour>0)
		{
				hour=hour/10;
				CmdLcd(GOTO_LINE2_POS0);
			  	StrLcd("HH");
						if(!hour)
						{
							CmdLcd(GOTO_LINE2_POS0);
							StrLcd("HH");	
						}
						else
						{
						CmdLcd(GOTO_LINE2_POS0);
						U32Lcd(hour);	
						}
		}
		else if(keyval=='E')
			return 0;
	}
}
void setalarmmin(void)
{
	int min=0;
	if(alhr<10)
	{
		CmdLcd(GOTO_LINE2_POS0);
		CharLcd((alhr/10)+48);
		CharLcd((alhr%10)+48);
	}
	while(1)
	{
		keyval=KeyScan();
		while(ColScan()==0);
		DELAY;
		if((keyval>='0') && (keyval<='9'))
		{
				min=(min*10)+(keyval-48);
				CmdLcd(GOTO_LINE2_POS0+3);
				if(min>99)
					min=min/10;
				U32Lcd(min);
		}
		else if ((min<60) && (keyval=='='))
		{
				alflag=1;
				almin=min;
				break;
		}
		else if((min>0) && (keyval=='B'))
		{
				min=min/10;
				CmdLcd(GOTO_LINE2_POS0+3);
			  	StrLcd("MM");
				if(!min)
				{
					CmdLcd(GOTO_LINE2_POS0+3);
					StrLcd("MM");
				}
				else
				{
			  	CmdLcd(GOTO_LINE2_POS0+3);
				U32Lcd(min);
				}
		}
		else if(keyval=='E')
		{
			CmdLcd(CLEAR_LCD);
			break;
		}
	}
}

void set_alarm(void)
{
		CmdLcd(CLEAR_LCD);
		CmdLcd(GOTO_LINE1_POS0);
		StrLcd("SET ALARM");
	 	CmdLcd(GOTO_LINE2_POS0);
	  	StrLcd("HH:MM");
	  	if(setalarmhour())
		{
			delay_ms(100);
			setalarmmin();
		}
		CmdLcd(CLEAR_LCD);
}

