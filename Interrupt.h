//Interrupt.h
#ifndef INTERRUPT_H
#define INTERRUPT_H
#define EINT0_VIC_CHNO 14   // External Interrupt 0 assigned to VIC channel number 14

void eint0_isr(void) __irq;  // __irq tells the compiler that this function is an interrupt service routine
void edit(void);            //funtion prototype for edit() function

#endif //INTERRUPT_H
