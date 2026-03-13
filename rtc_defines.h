#include <lpc21xx.h>

// include LCD header files
#include "lcd_define.h"

/* Global RTC variables used across the project */
extern s32 hour,min,sec,date,month,day,year;

/* System clock and peripheral clock definitions */
#define FOSC 12000000            // Oscillator frequency (12 MHz crystal)
#define CCLK (5*FOSC)            // CPU clock = 5 × FOSC
#define PCLK (CCLK/4)            // Peripheral clock = CCLK / 4

/*
RTC Prescaler Calculation
RTC requires a 32.768 kHz clock to increment once per second.
PREINT and PREFRAC divide the PCLK to generate this frequency.

PREINT  = int (PCLK / 32768) - 1
PREFRAC = PCLK - ((PREINT + 1) * 32768)

Reference: LPC2129/LPC2148 User Manual
*/

#define PREINT_VAL (int) ((PCLK / 32768) - 1)        // Integer prescaler value
#define PREFRAC_VAL (PCLK -((PREINT_VAL + 1) * 32768)) // Fractional prescaler value

/* RTC Control Register (CCR) Bit Definitions */

/* Bit 0 – Enable RTC clock counters */
#define RTC_ENABLE (1<<0)

/* Bit 1 – Reset RTC counters */
#define RTC_RESET (1<<1)

/* Bit 4 – Clock source selection (LPC2148 only)
   1 ? External 32.768 kHz crystal
   0 ? Internal PCLK source */
#define RTC_CLKSRC (1<<4)

/* Weekday definitions used in RTC */
#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6

/* Initialize RTC module */
void initRTC(void);

/* Read current RTC time */
void GetRTCTimeInfo(s32 *,s32 *,s32 *);

/* Display RTC time on LCD */
void DisplayRTCTime(u32,u32,u32);

/* Read current RTC date */
void GetRTCDateInfo(s32 *,s32 *,s32 *);

/* Display RTC date on LCD */
void DisplayRTCDate(u32,u32,u32);

/* Set RTC time */
void SetRTCTimeInfo(u32,u32,u32);

/* Set RTC date */
void SetRTCDateInfo(u32,u32,u32);

/* Get current RTC weekday */
void GetRTCDay(s32 *);

/* Display weekday on LCD */
void DisplayRTCDay(u32);

/* Set RTC weekday */
void SetRTCDay(u32);

/* Display arrow navigation symbols on LCD */
void arrowset(void);

/* Main RTC display function */
void display_RTC(void);

#define _LPC2148

/* Macro to clear and reposition cursor at line 1 */
#define LINE1_POS cmdLCD(GOTO_LINE1_POS0);strLCD(space);cmdLCD(GOTO_LINE1_POS0);

/* Macro to clear and reposition cursor at line 2 */
#define LINE2_POS cmdLCD(GOTO_LINE2_POS0);strLCD(space);cmdLCD(GOTO_LINE2_POS0);
