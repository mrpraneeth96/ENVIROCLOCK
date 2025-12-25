//interrupt.h

void Init_Interrupt(void);
void eint0_isr(void)__irq;
void Init_Alm_Interrupt(void);
void eint1_isr(void)__irq;
