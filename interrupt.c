//interrupt.c

 #include "rtc_defines.h"
#ifndef _LPC2148_
#include "lpc21xx.h"
#else
#include "lpc214x.h"
#endif

#include "types.h"
#include "pin_connect_block.h"
#include "pin_function_defines.h"
#include "delay.h"
#include "rtc.h" 
#include "kpm.h"
#include "kpm_defines.h"
#include "lcd.h"
#include "lcd_defines.h"

#define EINT0_VIC_CHNO 14
#define EINT0_VIC_CHN1 15

extern int flag,keyval,alhr,almin,alflag;

void eint1_isr(void)__irq
{
	if((alhr==HOUR)&&(almin==MIN) )		//if alaram is in on condition whenever interrupt raised turns off alarm
	{
			almin=-1;
			alhr=-1;
			alflag=0;
	}
	else
	{
	//this code displays the alaram status 
		CmdLcd(CLEAR_LCD);
		if(almin==-1 && alhr==-1)
		{
			CmdLcd(GOTO_LINE1_POS0);
			StrLcd("ALARM NOT SET");
		}
		else
		{
			CmdLcd(GOTO_LINE1_POS0);
			StrLcd("ALARM SET ");
			CharLcd((alhr/10)+48);
			CharLcd((alhr%10)+48);
			CharLcd(':');
			CharLcd((almin/10)+48);
			CharLcd((almin%10)+48);
		}
		CmdLcd(GOTO_LINE2_POS0);
		StrLcd("S.STOP    E.EXIT");
		while(1)
		{
			keyval=KeyScan();
			while(ColScan()==0);
			//if key E is pressed then control exits from isr
			if(keyval=='E')
			{
				CmdLcd(CLEAR_LCD);
				break;
			}
			//if key S is pressed then alarm turns off and exits from isr
			else if(keyval=='S')
			{
				almin=-1;
				alhr=-1;
				alflag=0;
				CmdLcd(CLEAR_LCD);
				break;
			}
		}
	}
	EXTINT=1<<1;
	//clear eint0 status is in VIC PERIPHERAL
	VICVectAddr=0;
}
void Init_Alm_Interrupt(void)
{
	//config port pin 0.3 as einto funtionality
	CfgPortPinFun(0,3,EINT_0_1);
	//select interrupt type default irq type
	//VICIntSelect=0<<EINT0_VIC_CHNO;
	//enable the interrupt
	VICIntEnable=1<<EINT0_VIC_CHN1;
	//setting interrupt priority
	VICVectCntl1=(1<<5) | EINT0_VIC_CHN1;
	//copying eint1 isr address
	VICVectAddr1=(u32)eint1_isr;
	
	//EXTINT=0;
	//setting mode level triggering 0 edge triggering 1
	EXTMODE=1<<1;
	//if edge trigg 0-falling edge 1-raising edge
	//EXTPOLAR=0;																	 
	
}

void eint0_isr(void)__irq
{
	u32 flag=0;
	while(1)
	{
			CmdLcd(CLEAR_LCD);
			CmdLcd(GOTO_LINE1_POS0);
			StrLcd("1.Edit");
			CmdLcd(GOTO_LINE2_POS0);
			StrLcd("2.Set Alaram");
			CmdLcd(GOTO_LINE1_POS0+8);
			StrLcd("3.Exit");	
				keyval=KeyScan();
				while(ColScan()==0);
				switch(keyval)
				{
				//if key '1' is pressed then control goes to edit_info()
						case '1': keyval=0;
										edit_info();
										break;
										
						case '2': keyval=0;
					            set_alarm();
										break;
						case '3': keyval=0;
										flag=1;
										break;
						default :CmdLcd(CLEAR_LCD);
										CmdLcd(GOTO_LINE1_POS0);
										StrLcd("INVALID INPUT");
										delay_s(1);
				}
				if(flag)
				{
					CmdLcd(CLEAR_LCD);
					break;
				}
	}
	EXTINT=1<<0;
	//clear eint0 status is in VIC PERIPHERAL
	VICVectAddr=0;
}

void Init_Interrupt(void)
{
	//config port pin 0.1 as einto funtionality
	CfgPortPinFun(0,1,EINT_0_1);
	//select interrupt type default irq type
	//VICIntSelect=0<<EINT0_VIC_CHNO;
	//enable the interrupt
	VICIntEnable=1<<EINT0_VIC_CHNO;
	//setting interrupt priority
	VICVectCntl0=(1<<5) | EINT0_VIC_CHNO;
	//coying eint0 isr address
	VICVectAddr0=(u32)eint0_isr;
	
	//EXTINT=0;
	//setting mode level triggering 0 edge triggering 1
	EXTMODE=1<<0;
	//if edge trigg 0-falling edge 1-raising edge
	//EXTPOLAR=0;
	
}
