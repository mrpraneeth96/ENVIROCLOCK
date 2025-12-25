//rtc.h

#ifndef rtc_h

#define rtc_h

#include"types.h"

void Init_Rtc(void);
void getRTCtimeInfo(u32 *,u32 *,u32 *);
void DisplayRTCtimeInfo(u32 ,u32 ,u32 );
void getRTCdateInfo(u32 *,u32 *,u32 *);
void DisplayRTCdateInfo(u32 ,u32 ,u32 );

void SetRTCtimeInfo(u32,u32,u32);
void SetRTCdateInfo(u32,u32,u32);

void getRTCdayInfo(u32 *);
void DisplayRTCdayInfo(u32);
void SetRTCday(u32);

void RingAlarm(void);
void ScanAlarm(void);


void edit_info(void);
void set_alarm(void);
void sethour(void);
void setmin(void);
void setsec(void);
void setdate(void);
void setmonth(void);
void setyear(void);
void setday(void);

#endif
