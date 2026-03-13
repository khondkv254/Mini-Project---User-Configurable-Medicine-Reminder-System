#include<lpc21xx.h>
#include "typedef.h"
#include "Mini_Project_Interrupt.h"
#include "rtc_defines.h"
#include "lcd_define.h"
#include "kpm_defines.h"
#include "Delay.h"
#include "DRIVER.h"
#include "Medicine.h"

#define MAX 3
u8 rtc_menu_flag,med_ack_flag,alarm_active;
s32 hour,min,sec,date,month,day,year;
s16 i,ip;
typedef struct
{
	u8 HR;
	u8 MN;
}MED_TIME;
MED_TIME med[MAX];

int main()
{
	init_EXTINT();
	initRTC();
	initLCD();
	initKPM();
	init_DRIVER();
	while(1)
	{
		display_RTC();
		check_medicine_alarm();
	}
}
