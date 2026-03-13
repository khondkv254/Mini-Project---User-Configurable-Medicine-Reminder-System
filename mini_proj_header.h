#include <lpc21xx.h>
#include "rtc_defines.h"
#include "lcd_define.h"
#include "kpm_defines.h"
#include "typedef.h"
#include "Delay.h"

/* Maximum number of medicine reminder slots */
#define MAX 3

/* External Interrupt 0 configuration */
#define EINT0_INPUT_PIN 0x0000000C   /* Pin select bits for EINT0 */
#define EINT0_VIC_CHNO 14            /* VIC channel number for EINT0 */
#define STATUS_LED0 18               /* GPIO pin connected to status LED */

/* External Interrupt 1 configuration */
#define EINT1_INPUT_PIN 0x000000C0   /* Pin select bits for EINT1 */
#define EINT1_VIC_CHNO 15            /* VIC channel number for EINT1 */

/* Switch pin number */
#define SW1 3

/* Structure to store medicine reminder time */
typedef struct
{
	u8 HR;   /* Medicine hour */
	u8 MN;   /* Medicine minute */
}MED_TIME;

/* RTC time and date variables */
extern s32 hour,min,sec,date,month,day,year;

/* Loop index variables */
extern s16 i,ip;

/* System state flags */
extern u8 rtc_menu_flag,med_ack_flag,alarm_active;

/* Variables used for reminder logic and menu navigation */
extern u8 remind_counter,menu,key,med_cnt,flag;

/* Array storing medicine schedule times */
extern MED_TIME med[MAX];

/* Array storing weekday names */
extern u8 Week[][4];

/* Custom LCD characters for arrow symbols */
extern u8 up_arrows[8];
extern u8 down_arrows[8];

/* Variable used to store keypad character */
extern u8 ch;

/* Displays RTC time, date, and medicine reminders */
void rtc_display(void);

/* Handles RTC configuration menu */
void rtc_menu(void);

/* Handles medicine time setup menu */
void medicine_setup(void);

/* Initializes external interrupts */
void initEXTINT(void);

/* ISR for external interrupt 0 (menu entry) */
void eint0_isr(void) __irq;

/* ISR for external interrupt 1 (medicine acknowledgment) */
void eint1_isr(void) __irq;

/* Displays arrow indicators on LCD during menu navigation */
void arrowset(void);
