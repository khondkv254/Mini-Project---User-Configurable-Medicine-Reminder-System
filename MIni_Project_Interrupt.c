#include<lpc21xx.h>
#include "typedef.h"
#include "Mini_Project_Interrupt.h"
extern rtc_menu_flag,med_ack_flag,alarm_active;
void init_EXTINT(void)
{
	PINSEL0 = (PINSEL0 &~(EINT0_INPUT_PIN))|(EINT0_INPUT_PIN)|
						(PINSEL0 &~(EINT1_INPUT_PIN))|(EINT1_INPUT_PIN);
	VICIntSelect = 0;
	VICIntEnable = 1<<EINT0_VIC_CHNO|
								 1<<EINT1_VIC_CHNO;
	VICVectCntl0 = (1<<5)|EINT0_VIC_CHNO;
	VICVectAddr0 = (u32)eint0_isr;
	VICVectCntl1 = (1<<5)|EINT1_VIC_CHNO;
	VICVectAddr1 = (u32)eint1_isr;
	EXTINT = 0;
	EXTMODE = (1<<0)|(1<<1);
	EXTPOLAR = 0;
	IODIR0 |=1<<STATUS_LED0;
	IOSET0 |=1<<STATUS_LED0;
}
void eint0_isr(void) __irq
{
		rtc_menu_flag = 1; 
    EXTINT = 1<<0; 
    VICVectAddr = 0; 
}

void eint1_isr(void) __irq
{
		med_ack_flag =1;
		alarm_active=0;
		IOSET0|=1<<STATUS_LED0;
		EXTINT=1<<1; 
    VICVectAddr = 0;
}
