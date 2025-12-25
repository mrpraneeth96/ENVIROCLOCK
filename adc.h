//adc.h

#include "types.h"

void Init_ADC(void);
void Read_ADC(u32 chNo,u32 *adcDVal,f32 *eAR);

u32 GetEquivalentTemp(u32);
void DisplayTemperature(u32);
