#include "mini_proj_header.h"

/* Function to display RTC menu and handle user selection */
void rtc_menu(void)
{
	rtc_menu_flag = 0;      // Clear menu flag set by interrupt
	menu=1;                 // Start menu selection from option 1

	cmdLCD(CLR_LCD);        // Clear LCD display

	while(1)
	{
		cmdLCD(GOTO_LINE1_POS0);

		if(menu == 1)
			strLCD("> EDIT RTC");          // Option to edit RTC time/date
		else
			strLCD("  EDIT RTC");

		cmdLCD(GOTO_LINE2_POS0);

		if(menu == 2)
			strLCD("> MEDICINE SETUP");    // Option to configure medicine reminder
		else
			strLCD("  MEDICINE SETUP");

		cmdLCD(GOTO_LINE3_POS0+2);
		strLCD("CHANGE (*)");              // '*' key used to move between menu items

		cmdLCD(GOTO_LINE4_POS0+2);
		strLCD("SELECT (=)");              // '=' key used to select menu option

		key = keyscan();                   // Read keypad input

		if(key == '*')
		{
			menu++;                        // Move to next menu option

			if(menu > 2)
				menu = 1;
		}
		else if(key == '=')
		{
			break;                         // Confirm selected option
		}
	}

	switch(menu)
	{
		case 1:
			cmdLCD(CLR_LCD);

			/* -------- SET HOUR -------- */
			TAKE1:
			cmdLCD(CLR_LCD);

			cmdLCD(GOTO_LINE2_POS0);
			charLCD(0);
			strLCD("(4)");

			cmdLCD(GOTO_LINE1_POS0+14);
			strLCD("(/)>");

			cmdLCD(GOTO_LINE2_POS0+14);
			strLCD("(*)");
			charLCD(1);

			cmdLCD(GOTO_LINE1_POS0+6);
			strLCD("HOUR");

			while(1)
			{
				cmdLCD(GOTO_LINE1_POS0);
				charLCD(' ');

				cmdLCD(GOTO_LINE2_POS0+7);

				if(hour < 10)
				{
					charLCD('0');
					charLCD(hour + 48);
				}
				else
				{
					dispint(hour);
				}

				ch = keyscan();

				if(ch == '*')
				{
					hour+=2;                // Increase hour
					if(hour > 23)
						hour = 0;
				}
				else if(ch == '4')
				{
					hour--;                 // Decrease hour
					if(hour < 0)
						hour = 23;
				}
				else if(ch == '/')
				{
					break;                  // Confirm hour
				}
			}

			/* -------- SET MINUTE -------- */
			TAKE2:
			arrowset();

			cmdLCD(GOTO_LINE1_POS0+5);
			strLCD("MINUTE");

			while(1)
			{
				cmdLCD(GOTO_LINE1_POS0);
				cmdLCD(GOTO_LINE2_POS0+7);

				if(min < 10)
				{
					charLCD('0');
					charLCD(min + 48);
				}
				else
				{
					dispint(min);
				}

				ch = keyscan();

				if(ch == '*')
				{
					min+=5;                 // Increase minute
					if(min > 59)
						min = 0;
				}
				else if(ch == '4')
				{
					min--;                  // Decrease minute
					if(min < 0)
						min = 59;
				}
				else if(ch == '/')
				{
					break;
				}
				else if(ch=='7')
				{
					goto TAKE1;             // Go back to hour edit
				}
			}

			/* -------- SET SECOND -------- */
			TAKE3:
			arrowset();

			cmdLCD(GOTO_LINE1_POS0+5);
			strLCD("SECOND");

			while(1)
			{
				cmdLCD(GOTO_LINE1_POS0);
				cmdLCD(GOTO_LINE2_POS0+7);

				if(sec < 10)
				{
					charLCD('0');
					charLCD(sec + 48);
				}
				else
				{
					dispint(sec);
				}

				ch = keyscan();

				if(ch == '*')
				{
					sec+=5;                 // Increase seconds
					if(sec > 59)
						sec = 0;
				}
				else if(ch == '4')
				{
					sec--;                  // Decrease seconds
					if(sec < 0)
						sec = 59;
				}
				else if(ch=='7')
				{
					goto TAKE2;             // Go back to minute edit
				}
				else if(ch=='/')
				{
					SetRTCTimeInfo(hour,min,sec);   // Save time in RTC

					/* -------- SET WEEK DAY -------- */
					TAKE4:
					arrowset();

					cmdLCD(GOTO_LINE1_POS0+6);
					strLCD("WEEK DAY");

					while(1)
					{
						cmdLCD(GOTO_LINE2_POS0+7);
						strLCD(Week[i]);

						ch = keyscan();

						if(ch == '*')
						{
							i++;
							if(i > 6)
								i = 0;
						}
						else if(ch == '4')
						{
							i--;
							if(i < 0)
								i = 6;
						}
						else if(ch == '7')
						{
							goto TAKE3;
						}
						else if(ch == '/')
						{
							SetRTCDay(i);   // Save weekday

							/* -------- SET DATE -------- */
							TAKE5:
							arrowset();

							cmdLCD(GOTO_LINE1_POS0+6);
							strLCD("DATE");

							while(1)
							{
								cmdLCD(GOTO_LINE2_POS0+7);

								if(date < 10)
								{
									charLCD('0');
									charLCD(date + 48);
								}
								else
								{
									dispint(date);
								}

								ch = keyscan();

								if(ch == '*')
								{
									date+=5;
									if(date > 31)
										date = 1;
								}
								else if(ch == '4')
								{
									date--;
									if(date < 1)
										date = 31;
								}
								else if(ch == '7')
								{
									goto TAKE4;
								}
								else if(ch == '/')
								{
									break;
								}
							}

							/* -------- SET MONTH -------- */
							TAKE6:
							arrowset();

							cmdLCD(GOTO_LINE1_POS0+6);
							strLCD("MONTH");

							while(1)
							{
								cmdLCD(GOTO_LINE2_POS0+7);

								if(month < 10)
								{
									charLCD('0');
									charLCD(month + 48);
								}
								else
								{
									dispint(month);
								}

								ch = keyscan();

								if(ch == '*')
								{
									month+=2;
									if(month > 12)
										month = 1;
								}
								else if(ch == '4')
								{
									month--;
									if(month < 1)
										month = 12;
								}
								else if(ch == '7')
								{
									goto TAKE5;
								}
								else if(ch == '/')
								{
									year=2000;
									break;
								}
							}

							/* -------- SET YEAR -------- */
							cmdLCD(CLR_LCD);

							cmdLCD(GOTO_LINE1_POS0);
							strLCD("<(7)");

							cmdLCD(GOTO_LINE2_POS0);
							charLCD(0);
							strLCD("(4)");

							cmdLCD(GOTO_LINE1_POS0+6);
							strLCD("YEAR");

							cmdLCD(GOTO_LINE2_POS0+14);
							strLCD("(*)");
							charLCD(1);

							cmdLCD(GOTO_LINE3_POS0);
							strLCD("Save & Exit (=)");

							while(1)
							{
								cmdLCD(GOTO_LINE2_POS0+6);
								dispint(year);

								ch = keyscan();

								if(ch == '*')
								{
									year+=5;
									if(year > 2099)
										year = 2000;
								}
								else if(ch == '4')
								{
									year--;
									if(year < 2000)
										year = 2099;
								}
								else if(ch == '7')
								{
									goto TAKE6;
								}
								else if(ch == '=')
								{
									SetRTCDateInfo(date,month,year); // Save date
									cmdLCD(CLR_LCD);
									return;
								}
							}
						}
					}
				}
			}

		case 2:
			medicine_setup();     // Open medicine setup menu
			break;
	}
}
