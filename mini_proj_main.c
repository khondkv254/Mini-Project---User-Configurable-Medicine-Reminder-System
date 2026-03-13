/******************************************************************************
Project Title : USER-CONFIGURABLE MEDICINE REMINDER SYSTEM

Author           : KUNAL VIJAY KHOND
Start Date       : 7/MAR/2026
Submission Date  : 13/MAR/2026


Project Aim :
								To develop a User-Configurable Medicine Reminder System that allows users
							to set medicine timings and receive automatic alerts at scheduled times.


Project Objective :
							1. Display real-time clock (RTC) time on LCD.	
							2. Allow user configuration of medicine timings.
							3. Monitor stored medicine schedules continuously.
							4. Generate alerts when medicine time occurs.


Project Scope :
								This system helps users remember to take medicines on time. The user can
							configure medicine timings through a keypad interface. When the RTC time
							matches a stored schedule, the system generates alerts through LCD and
							buzzer until the user acknowledges the reminder.

Area of Usage :
							• Home healthcare monitoring
							• Hospitals and clinics
							• Elderly patient assistance systems
							• Personal medication management


Software Used :
							• Keil uVision IDE (Embedded C Development)
							• Proteus Simulation (optional hardware simulation)
							• Flash Magic (Program uploading to LPC2148)
							• Debugger (Keil built-in debugger)


Hardware Components :
							• LPC2148 ARM7 Microcontroller
							• 16x2 LCD Display
							• 4x4 Matrix Keypad
							• Buzzer (Alert indication)
							• Active-Low Push Buttons
							• External Interrupt Switches (SW1, SW2)
							• Resistor Pack
							• CMOS Battery for RTC Backup
							• USB-UART Converter / DB-9 Serial Cable
							• Crystal Oscillator (12 MHz)



Technical Skills Utilized :
							• ARM7 LPC2148 Microcontroller Programming
							• Real Time Clock (RTC) Configuration
							• External Interrupt Handling (EINT0, EINT1)
							• LCD Driver Development
							• Keypad Matrix Scanning Driver
							• Embedded C Programming
							• Time-based Event Monitoring
							• Menu-driven User Interface Design
							• Alarm/Reminder System Implementation


--------------------------------PROJECT WORK FLOW----------------------------------------------

1. System Initialization
   - Initialize External Interrupts (EINT0 and EINT1).
   - Initialize RTC module.
   - Initialize LCD display.
   - Initialize Keypad driver.
   - Load custom LCD characters (navigation arrows).

2. Normal Operation Mode
   - System continuously reads RTC time.
   - Current Time, Date, and Day are displayed on LCD.
   - If no medicine schedule exists, the system works as a digital clock.

3. Enter Configuration Mode
   - Press Switch-1 (EINT0) to enter the configuration menu.
   - LCD displays:
        > EDIT RTC
        > MEDICINE SETUP

4. RTC Editing Mode
   - User can modify:
        • Hour
        • Minute
        • Second
        • Weekday
        • Date
        • Month
        • Year
   - Updated values are stored into RTC registers.

5. Medicine Schedule Setup
   - User can configure up to three medicine reminders.
   - Each reminder contains:
        • Hour
        • Minute
   - These values are stored in controller memory.

6. Continuous Monitoring
   - System continuously compares RTC time with stored medicine schedules.

7. Alert Generation
   - When current RTC time matches a stored schedule:
        • LCD displays "TAKE MEDICINE"
        • Buzzer produces alert sound
        • LED indicator activates
        • Reminder repeats periodically.

8. User Acknowledgment
   - User presses Switch-2 (EINT1).
   - System stops buzzer immediately.
   - LCD displays confirmation message:
        "MEDICINE TAKEN"
        "STAY HEALTHY"

9. Timeout Condition
   - If user does not acknowledge within defined time,
     the system automatically stops the buzzer and
     returns to monitoring mode.

10. Continuous Operation
   - System continues checking RTC time for the next medicine schedule.

------------------------------------------------------------------------------

KEYPAD NAVIGATION GUIDE

Keypad Button Usage:

(*)  ? Increase value / move forward in menu
(4)  ? Decrease value
(/)  ? Confirm and move to next parameter
(7)  ? Go back to previous parameter
(=)  ? Save selection / Exit menu

Example:
• Press (*) to increase hour or minute value.
• Press (4) to decrease the value.
• Press (/) to move to the next field (Hour ? Minute ? Second).
• Press (7) to return to the previous setting.
• Press (=) to save the configuration and exit.

------------------------------------------------------------------------------
******************************************************************************/
#include "mini_proj_header.h"

/*
Main Function
-------------
This is the entry point of the User-Configurable Medicine Reminder System.
It initializes all required peripherals and continuously runs the main
application loop for RTC display and menu handling.
*/

int main()
{
	/* Initialize External Interrupts (EINT0, EINT1) */
	initEXTINT();

	/* Initialize Real Time Clock module */
	initRTC();

	/* Initialize LCD display */
	initLCD();

	/* Initialize Keypad driver */
	initKPM();

	/* Load custom character for down arrow into LCD CGRAM */
	cust_char(down_arrows,0);

	/* Load custom character for up arrow into LCD CGRAM */
	cust_char(up_arrows,1);

	/* Main program loop runs continuously */
	while(1)
	{
		/* Display current RTC time, date, and reminders */
		rtc_display();

		/* Check if menu interrupt flag is set */
		if(rtc_menu_flag)
		{
			/* Enter RTC configuration menu */
			rtc_menu();
		}
	}
}
