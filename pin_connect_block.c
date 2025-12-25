//pin_connect_block.c

#ifndef _LPC2148_
#include "lpc21xx.h"
#else
#include "lpc214x.h"
#endif

#include "types.h"

void CfgPortPinFun(u32 portno,u32 pinno,u32 pinfun)
{
	if(portno==0)
	{
		if(pinno<16)
			PINSEL0|=((PINSEL0&~(3<<pinno)) | (pinfun<<(pinno*2)));
		else if((pinno>15) && (pinno<32))
			PINSEL1|=((PINSEL1&~(3<<(pinno-16))) | (pinfun<<((pinno-16)*2)));
	}
	/*else if(portno==1)
	{
	}
	*/	
}
