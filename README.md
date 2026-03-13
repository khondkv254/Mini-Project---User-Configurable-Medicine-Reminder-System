# Mini-Project-User-Configurable-Medicine-Reminder-System
Designed and implemented a User-Configurable Medicine Reminder System using the LPC2148 ARM7 microcontroller and Embedded C. The system displays real-time clock data on an LCD, allows users to set medicine schedules via keypad, and generates alerts through a buzzer when scheduled times match RTC time.

****PROJECT OVERVIEW****

    The User-Configurable Medicine Reminder System is designed to help patients remember their medication schedule.
    The system uses an RTC module to track real-  time and compares it with user-defined medicine schedules.
    When the scheduled time matches the current RTC time:
    LCD displays reminder message
    Buzzer generates alert sound
    LED indicator activates
    User acknowledges the reminder using a switch
    This system is useful for home healthcare monitoring and elderly assistance.

****FEATURES****

Real-Time Clock display on LCD
Menu-driven user interface
RTC editing functionality
Configurable medicine reminders
Continuous schedule monitoring
Buzzer alert for medicine reminder
LCD notification messages
User acknowledgment using external interrupt
Automatic return to monitoring mode

****HARDWARE COMPONENTS****

LPC2148 ARM7 Microcontroller
16x2 LCD Display
4x4 Matrix Keypad
Buzzer
Push Buttons (External Interrupt Switches)
Resistor Pack
CMOS Battery (RTC backup)
Crystal Oscillator (12 MHz)
USB-UART Converter / Serial Cable

****SOFTWARE TOOLS****

Keil uVision IDE
Embedded C Programming
Flash Magic (for program upload)
Proteus (optional simulation)
LPC2148 Peripheral Libraries

****SYSTEM ARCHITECTURE****

The system consists of the following modules:
1.RTC Module
Maintains real-time clock information such as hour, minute, second, date, and year.

2.LCD Display Driver
Displays system information including time, menu options, and reminder messages.

3.Keypad Driver
Used for configuring RTC time and medicine schedules.

4.External Interrupt Module
Handles user inputs using hardware interrupts.

5.Alarm Monitoring System
Continuously compares current time with stored medicine schedules.

6.Alert System
Triggers buzzer and displays reminder message when the scheduled time occurs.


**PROJECT METHODOLOGY**
1. System Initialization

The system initializes all required peripherals:
External Interrupts
RTC Module
LCD Display
Keypad Interface
Custom LCD characters

2. Normal Operation Mode

The system continuously displays the current time and date on the LCD using RTC.
If no medicine schedule exists, the system behaves as a digital clock.

3. Configuration Mode

Pressing Switch 1 (EINT0) enters the configuration menu.
Menu options include:
Edit RTC
Medicine Setup

4. RTC Editing

Users can configure:

Hour
Minute
Second
Date
Month
Year
Weekday
These values are stored in RTC registers.

5. Medicine Schedule Setup

Users can configure up to three medicine reminders.
Each reminder includes:

Hour
Minute
These schedules are stored in controller memory.

6. Continuous Monitoring

The system continuously compares RTC time with stored medicine schedules.

7. Alert Generation

When a scheduled medicine time occurs:
LCD displays "TAKE MEDICINE"
Buzzer generates alert sound
LED indicator activates
Reminder repeats periodically

8. User Acknowledgment

User presses Switch 2 (EINT1) to acknowledge.
System response:
Buzzer stops
LCD displays
MEDICINE TAKEN
STAY HEALTHY

9. Timeout Handling

If the user does not acknowledge the alert within a certain period:
Buzzer stops automatically
System returns to monitoring mode

10. Continuous Operation

The system continues monitoring RTC time for the next scheduled reminder.
Keypad Navigation

**KEY FUNCTION**
(*)	Increase value / Move forward
(4)	Decrease value
(/)	Move to next parameter
(7)	Move to previous parameter
(=)	Save configuration

Example:

Press * to increase hour
Press 4 to decrease value
Press / to move to next field
Press = to save settings


**TECHNICALL SKILL DEMONSTRATION**

Embedded C Programming
ARM7 LPC2148 Microcontroller
Real-Time Clock (RTC)
External Interrupt Handling
LCD Driver Development
Keypad Matrix Scanning
Menu-driven Embedded UI
Alarm and Reminder System Design
Time-based Event Monitoring

**APPLICATION**

Personal medication reminder
Home healthcare systems
Hospital patient monitoring
Elderly care devices
