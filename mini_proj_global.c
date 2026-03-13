#include "mini_proj_header.h"

/* Variables to store RTC time and date values */
s32 hour,min,sec,date,month,day,year;

/* General loop/index variables */
s16 i,ip;

/* Flag to enter RTC menu when interrupt occurs */
u8 rtc_menu_flag=0;

/* Flag to indicate medicine acknowledgment by user */
u8 med_ack_flag=0;

/* Indicates medicine alarm is currently active */
u8 alarm_active=0;

/* Custom character pattern for upward arrow on LCD */
u8 up_arrows[8] =  {0x04,0x0E,0x15,0x04,0x04,0x04,0x04,0x00};

/* Custom character pattern for downward arrow on LCD */
u8 down_arrows[8] = {0x04,0x04,0x04,0x04,0x15,0x0E,0x04,0x00};

/* Counter used for reminder timing */
u8 remind_counter=0;

/* Prevents multiple alarm triggers within the same second */
u8 alarm_triggered=0;

/* Menu navigation and keypad variables */
u8 menu,key,med_cnt,flag,ch;

/* Structure array to store medicine reminder times */
MED_TIME med[MAX];

/* Weekday names used for RTC day display */
u8 Week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
