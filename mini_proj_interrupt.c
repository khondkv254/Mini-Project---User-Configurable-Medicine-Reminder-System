#include "mini_proj_header.h"

/* Initialize External Interrupts and configure VIC controller */
void initEXTINT(void)
{
	/* Configure pins as EINT0 and EINT1 using PINSEL0 */
	PINSEL0 = (PINSEL0 &~(EINT0_INPUT_PIN))|(EINT0_INPUT_PIN)|
						(PINSEL0 &~(EINT1_INPUT_PIN))|(EINT1_INPUT_PIN);

	/* Select IRQ type interrupts (not FIQ) */
	VICIntSelect = 0;

	/* Enable EINT0 and EINT1 interrupts in VIC */
	VICIntEnable = 1<<EINT0_VIC_CHNO |
								 1<<EINT1_VIC_CHNO;

	/* Configure vector slot 0 for EINT0 interrupt */
	VICVectCntl0 = (1<<5)|EINT0_VIC_CHNO;
	VICVectAddr0 = (u32)eint0_isr;

	/* Configure vector slot 1 for EINT1 interrupt */
	VICVectCntl1 = (1<<5)|EINT1_VIC_CHNO;
	VICVectAddr1 = (u32)eint1_isr;

	/* Clear any pending external interrupt flags */
	EXTINT = 0;

	/* Configure EINT0 and EINT1 as edge triggered interrupts */
	EXTMODE = (1<<0)|(1<<1);

	/* Configure interrupts as falling edge triggered */
	EXTPOLAR = 0;

	/* Configure status LED pin as output */
	IODIR0 |=1<<STATUS_LED0;

	/* Turn OFF LED initially */
	IOSET0 |=1<<STATUS_LED0;
}

/* ISR for EINT0 – used to open RTC menu */
void eint0_isr(void) __irq
{
	rtc_menu_flag = 1;   // Set flag to enter RTC menu

	EXTINT = 1<<0;       // Clear EINT0 interrupt flag

	VICVectAddr = 0;     // Inform VIC that ISR execution is complete
}

/* ISR for EINT1 – used to acknowledge medicine reminder */
void eint1_isr(void) __irq
{
	med_ack_flag =1;     // Set medicine acknowledgement flag

	alarm_active=0;      // Stop active alarm

	IOSET0|=1<<STATUS_LED0; // Turn OFF LED indicator

	EXTINT=1<<1;         // Clear EINT1 interrupt flag

	VICVectAddr = 0;     // Inform VIC that ISR execution is complete
}
