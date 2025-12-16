#ifndef EINT_H

#define EINT_H


void Init_EINT(void);

void eint0_isr(void) __irq;

//void eint1_isr(void) __irq;


#endif
