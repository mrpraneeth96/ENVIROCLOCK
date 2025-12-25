//rtc_defines.h

#define _LPC2148_

#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)

#define PREINT_VAL ((int)((PCLK/32768)-1))
#define PREFRAC_VAL (PCLK - ((PREINT_VAL+1)*32768))
