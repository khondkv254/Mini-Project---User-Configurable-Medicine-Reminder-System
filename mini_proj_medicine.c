#include "mini_proj_header.h"

/* Function to configure medicine reminder times */
void medicine_setup(void)
{
	cmdLCD(CLR_LCD);                 // Clear LCD
	strLCD("MEDICINE SETUP");        // Display title

	menu=1;                          // Initialize menu selection

	cmdLCD(CLR_LCD);

	while(1)
	{
		cmdLCD(GOTO_LINE1_POS0);

		if(menu == 1)
			strLCD("> ADD TIME");    // Menu option to add medicine time
		else
			strLCD("  ADD TIME");

		cmdLCD(GOTO_LINE2_POS0);

		if(menu == 2)
			strLCD("> RESET TIME");  // Menu option to reset all medicine times
		else
			strLCD("  RESET TIME");

		cmdLCD(GOTO_LINE3_POS0);

		if(menu == 3)
			strLCD("> EXIT");        // Menu option to exit medicine setup
		else
			strLCD("  EXIT");

		cmdLCD(GOTO_LINE4_POS0+2);
		strLCD("CHANGE(*)");         // Key '*' used to change menu
		strLCD(" SEL(=)");           // Key '=' used to select option

		key = keyscan();             // Read keypad input

		if(key == '*')
		{
			menu++;                  // Move to next menu item
			if(menu > 3)
				menu = 1;
		}
		else if(key == '=')
		{
			break;                   // Select current menu option
		}
	}

	switch(menu)
	{
		case 1:                      // ADD TIME option

			while(med_cnt < 3)      // Maximum 3 medicine reminders allowed
			{
				hour = 0;
				min  = 0;

				/* -------- SET HOUR -------- */
				TAKE7:
				cmdLCD(CLR_LCD);

				cmdLCD(GOTO_LINE2_POS0);
				charLCD(0);          // Display down arrow custom symbol
				strLCD("(4)");

				cmdLCD(GOTO_LINE1_POS0+14);
				strLCD("(/)>");      // Show next navigation symbol

				cmdLCD(GOTO_LINE2_POS0+14);
				strLCD("(*)");
				charLCD(1);          // Display up arrow custom symbol

				cmdLCD(GOTO_LINE1_POS0+2);
				strLCD("HOUR MED:"); // Show hour setting label
				dispint(med_cnt+1);

				while(1)
				{
					cmdLCD(GOTO_LINE2_POS0+7);

					if(hour < 10)
					{
						charLCD('0');       // Leading zero
						charLCD(hour + 48);
					}
					else
					{
						dispint(hour);
					}

					ch = keyscan();        // Read keypad

					if(ch == '*')
					{
						hour+=2;           // Increase hour
						if(hour > 23)
							hour = 0;
					}
					else if(ch == '4')
					{
						hour--;            // Decrease hour
						if(hour < 0)
							hour = 23;
					}
					else if(ch == '/')
					{
						break;              // Confirm hour
					}
				}

				/* -------- SET MINUTE -------- */
				cmdLCD(CLR_LCD);

				cmdLCD(GOTO_LINE1_POS0);
				strLCD("<(7)");            // Back option

				cmdLCD(GOTO_LINE2_POS0);
				charLCD(0);
				strLCD("(4)");

				cmdLCD(GOTO_LINE2_POS0+14);
				strLCD("(*)");
				charLCD(1);

				if(med_cnt==2)
				{
					cmdLCD(GOTO_LINE4_POS0);
					strLCD("Save & EXIT (=)");  // Last slot option
					cmdLCD(GOTO_LINE1_POS0+5);
					strLCD("MIN MED:");
					dispint(med_cnt+1);
				}
				else
				{
					cmdLCD(GOTO_LINE4_POS0);
					strLCD("SAVE, NEXT SLOT(=)"); // Save and move next slot
					cmdLCD(GOTO_LINE1_POS0+5);
					strLCD("MIN MED:");
					dispint(med_cnt+1);
				}

				while(1)
				{
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
						min+=5;           // Increase minutes by 5
						if(min > 59)
							min = 0;
					}
					else if(ch == '4')
					{
						min--;            // Decrease minute
						if(min < 0)
							min = 59;
					}
					else if(ch =='7')
					{
						goto TAKE7;       // Go back to hour editing
					}
					else if(ch == '=')
					{
						/* Check duplicate medicine time */
						for(i = 0; i < med_cnt; i++)
						{
							if(hour == med[i].HR && min == med[i].MN)
							{
								cmdLCD(CLR_LCD);
								strLCD("SET ANOTHER TIME");
								cmdLCD(GOTO_LINE2_POS0);
								strLCD("FOR MEDICINE:");
								dispint(med_cnt+1);
								delay_sec(1);
								break;
							}
						}

						if(i == med_cnt)   // If time is unique
						{
							med[med_cnt].HR = hour;
							med[med_cnt].MN = min;
							med_cnt++;

							cmdLCD(CLR_LCD);
							strLCD("TIME SAVED");
							delay_sec(1);
							cmdLCD(CLR_LCD);
						}

						/* Show all medicine slots once full */
						if(med_cnt==3)
						{
							cmdLCD(CLR_LCD);

							for(i=0;i<3;i++)
							{
								if(i==1)
									cmdLCD(GOTO_LINE2_POS0);
								else if(i==2)
									cmdLCD(GOTO_LINE3_POS0);

								strLCD("MED ");
								dispint(i+1);
								charLCD(':');

								if(med[i].HR<10)
								{
									charLCD('0');
									dispint(med[i].HR);
								}
								else
									dispint(med[i].HR);

								charLCD(':');

								if(med[i].MN<10)
								{
									charLCD('0');
									dispint(med[i].MN);
								}
								else
									dispint(med[i].MN);
							}

							delay_sec(1);
							cmdLCD(CLR_LCD);
						}

						break;
					}
				}
			}
			break;

		case 2:                   // RESET TIME option

			cmdLCD(CLR_LCD);

			if(med_cnt==0)
			{
				strLCD("NO MED TIME SET"); // If no times configured
				delay_sec(1);
				cmdLCD(CLR_LCD);
			}
			else
			{
				strLCD("RESETTING...");    // Reset medicine schedule

				for(i=0;i<3;i++)
				{
					med[i].HR = 0;
					med[i].MN = 0;
				}

				cmdLCD(CLR_LCD);
				strLCD("ALL TIME RESET");

				med_cnt = 0;

				delay_sec(2);
				cmdLCD(CLR_LCD);
			}
			break;

		case 3:                   // EXIT option

			cmdLCD(CLR_LCD);
			strLCD("EXITED...");
			delay_ms(500);
			cmdLCD(CLR_LCD);

			break;
	}
}
