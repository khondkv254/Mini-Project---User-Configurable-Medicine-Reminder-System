#include "mini_proj_header.h"

/* Variable used to track last reminder second to avoid repeated display */
static int last_sec = -1;

/* External flag used to prevent multiple alarm triggers in same second */
extern u8 alarm_triggered;

/* Function to display RTC time/date and handle medicine reminders */
void rtc_display(void)
{
	GetRTCTimeInfo(&hour,&min,&sec);   // Read current time from RTC

	/* Reset alarm trigger once seconds move away from 0 */
	if(sec!=0)
	{
		alarm_triggered = 0;
	}

	/* Check all configured medicine reminder slots */
	for(ip=0;ip<med_cnt;ip++)
	{
		/* Trigger alarm when hour and minute match and second is 0 */
		if((hour==med[ip].HR)&&(min==med[ip].MN)&&(sec==0)&&(!alarm_triggered))
		{
			alarm_triggered=1;     // Prevent repeated trigger in same second
			alarm_active=1;        // Mark alarm as active

			cmdLCD(CLR_LCD);
			strLCD("TAKE MEDICINE"); // Display medicine reminder

			IOCLR0|=1<<STATUS_LED0;  // Turn ON status LED

			delay_sec(2);

			IOSET0|=1<<STATUS_LED0;  // Turn OFF LED

			cmdLCD(CLR_LCD);
		}
	}

	DisplayRTCTime(hour,min,sec);   // Show current time on LCD

	/* If alarm is active and medicine not acknowledged */
	if((alarm_active) && !(med_ack_flag))
	{
		remind_counter++;            // Increment reminder counter

		/* Show reminder every 10 seconds */
		if((sec % 10 == 0)&&(sec!=last_sec))
		{
			last_sec=sec;

			cmdLCD(CLR_LCD);

			if(sec!=0)               // Avoid repeating message at second 0
			{
				strLCD("TAKE MEDICINE");

				IOCLR0|=1<<STATUS_LED0;  // Turn ON LED indicator

				delay_sec(2);

				IOSET0|=1<<STATUS_LED0;  // Turn OFF LED

				cmdLCD(CLR_LCD);
			}
		}
	}

	/* If user presses acknowledge button */
	if(med_ack_flag)
	{
		if(med_cnt==0)
		{
			cmdLCD(CLR_LCD);
			strLCD("NO MED TIME SET");   // No medicine schedule available
			delay_sec(1);

			med_ack_flag=0;

			cmdLCD(CLR_LCD);
		}
		else
		{
			cmdLCD(CLR_LCD);

			strLCD("MEDICINE TAKEN");   // Confirmation message
			cmdLCD(GOTO_LINE2_POS0);
			strLCD("STAY HEALTHY");

			delay_sec(1);

			med_ack_flag=0;             // Reset acknowledgement flag

			cmdLCD(CLR_LCD);
		}
	}

	GetRTCDateInfo(&date,&month,&year);  // Read date from RTC
	DisplayRTCDate(date,month,year);     // Display date on LCD

	GetRTCDay(&day);                     // Read weekday
	DisplayRTCDay(day);                  // Display weekday
}
