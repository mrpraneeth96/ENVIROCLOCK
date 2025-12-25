//adc.c

#include "rtc_defines.h"
#ifndef _LPC2148_
#include "lpc21xx.h"
#else
#include "lpc214x.h"
#endif

#include "types.h"
#include "delay.h"
#include "defines.h"
#include "pin_connect_block.h"
#include "pin_function_defines.h"
#include "adc_defines.h"
#include "lcd.h"
#include "lcd_defines.h"



u32 GetEquivalentTemp(u32 adcVal)
{
	f32 voltage,temp;
	voltage=(f32)adcVal*3.3/1024.0;
	temp=voltage*100.0;
	return temp;
}

void DisplayTemperature(u32 temp)
{
	CmdLcd(GOTO_LINE2_POS0+12);
	U32Lcd(temp);
	CharLcd(0xDF);
	CharLcd('C');
}

#ifndef _LPC2148_

void Init_ADC(void)
{
	//cfg ADCR sfr
	ADCR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
	//cfg p0.27 pin as Analog Input pin0 (AIN0)
	CfgPortPinFun(0,27,PIN_FUN2);
}

void Read_ADC(u32 chNo,u32 *adcDVal,f32 *eAR)
{
	//clear any previous channel selection
	ADCR&=0xFFFFFF00;
	//update req channel select,
	//start analog samping & conversion
	ADCR|=1<<chNo|1<<ADC_START_BIT;
	delay_us(3);
	while(((ADDR>>DONE_BIT)&1)==0);
	ADCR&=~(1<<ADC_START_BIT);
	*adcDVal=(ADDR>>RESULT_BITS)&1023;
	*eAR = (*adcDVal * (3.3/1023));
}

#else

void Init_ADC(void)
{
	//cfg ADCR sfr
	AD0CR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
	//cfg p0.27 pin as Analog Input pin0 (AIN0)
	CfgPortPinFun(0,28,PIN_FUN2);
}

void Read_ADC(u32 chNo,u32 *adcDVal,f32 *eAR)
{
	//clear any previous channel selection
	AD0CR&=0xFFFFFF00;
	//update req channel select,
	//start analog samping & conversion
	AD0CR|=1<<chNo|1<<ADC_START_BIT;
	delay_us(3);
	while(((AD0DR0>>DONE_BIT)&1)==0);
	AD0CR&=~(1<<ADC_START_BIT);
	*adcDVal=(AD0DR0>>RESULT_BITS)&1023;
	*eAR = (*adcDVal * (3.3/1023));
}

#endif
