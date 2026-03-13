#include "rtc_defines.h"
#include "lcd_define.h"
#include<lpc21xx.h>

// Array to hold names of days of the week
u8 week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

/*
Initialize the Real-Time Clock (RTC)
This function disables the RTC, sets the prescaler values, 
and then enables the RTC.
*/
void initRTC(void) 
{
  // Disable and reset the RTC
	CCR = RTC_RESET;
	
	#ifndef _LPC2148
  
  // Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
	PREFRAC = PREFRAC_VAL;
  
  // Enable the RTC
	CCR = RTC_ENABLE; 

	#else
  // Enable the RTC with external clock source
	CCR = RTC_ENABLE | RTC_CLKSRC;	
	#endif 
}

/*
Get the current RTC time
hour Pointer to store the current hour
minute Pointer to store the current minute
second Pointer to store the current second
*/
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;
}

/*
Display the RTC time on LCD
hour value (0-23)
minute value (0-59)
second value (0-59) seperated by ':'
*/
void DisplayRTCTime(u32 hour, u32 minute, u32 second)
{
	cmdLCD(GOTO_LINE1_POS0);
	charLCD(hour/10+48);
	charLCD(hour%10+48);
	charLCD(':');
	charLCD(minute/10+48);
	charLCD(minute%10+48);
	charLCD(':');
	charLCD(second/10+48);		
	charLCD(second%10+48);	
}

/*
Get the current RTC date
day Pointer to store the current date (1-31)
month Pointer to store the current month (1-12)
year Pointer to store the current year (four digits)
*/
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

/*
Display the RTC date on LCD
Day of month (1-31)
Month (1-12)
Year (four digits) and seperated by '/'
*/
void DisplayRTCDate(u32 date, u32 month, u32 year)
{
	cmdLCD(GOTO_LINE2_POS0);
	charLCD(date/10+48);
	charLCD(date%10+48);
	charLCD('/');
	charLCD(month/10+48);
	charLCD(month%10+48);
	charLCD('/');
	dispint(year);
}

/*
Set the RTC time
Hour to set (0-23)
Minute to set (0-59)
Second to set (0-59)
*/
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
	HOUR = hour;
	MIN = minute;
	SEC = second;
}

/*
Set the RTC date
day of month to set (1-31)
month to set (1-12)
year to set (four digits)
*/
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;
}

/*
Get the current day of the week
dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
*/
void GetRTCDay(s32 *dow)
{
	*dow = DOW; 
}

/*
Display the current day of the week on LCD
dow (Day of Week) (0=Sunday, ..., 6=Saturday)
*/
void DisplayRTCDay(u32 dow)
{
	cmdLCD(GOTO_LINE1_POS0+10);
	strLCD(week[dow]);
  
}

/*
Set the day of the week in RTC
Day of Week to set (0=Sunday, ..., 6=Saturday)
*/
void SetRTCDay(u32 dow)
{
	DOW = dow;
}
/* Displays navigation arrows and keypad hints on LCD */
void arrowset(void)
{
	cmdLCD(CLR_LCD);                 // Clear LCD screen

	cmdLCD(GOTO_LINE1_POS0);         // Move cursor to line 1 start
	strLCD("<(7)");                  // Show back navigation key

	cmdLCD(GOTO_LINE2_POS0);         // Move cursor to line 2 start
	charLCD(0);                      // Display custom down arrow
	strLCD("(4)");                   // Show decrement key

	cmdLCD(GOTO_LINE1_POS0+14);      // Move cursor near end of line 1
	strLCD("(/)>");                  // Show next navigation key

	cmdLCD(GOTO_LINE2_POS0+14);      // Move cursor near end of line 2
	strLCD("(*)");                   // Show increment key
	charLCD(1);                      // Display custom up arrow
}

/* Reads RTC time/date/day and displays them on LCD */
void display_RTC(void)
{
	GetRTCTimeInfo(&hour,&min,&sec);     // Read current time from RTC
	DisplayRTCTime(hour,min,sec);        // Display time on LCD

	GetRTCDateInfo(&date,&month,&year);  // Read current date from RTC
	DisplayRTCDate(date,month,year);     // Display date on LCD

	GetRTCDay(&day);                     // Read weekday from RTC
	DisplayRTCDay(day);                  // Display weekday on LCD
}
