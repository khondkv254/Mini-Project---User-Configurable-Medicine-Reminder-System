#include<lpc21xx.h>
#include "kpm_defines.h"
#include "typedef.h"
#include "lcd_define.h"

/* Lookup table for 4x4 keypad mapping rows and columns to characters */
u8 kpmLUT[4][4]={{'7','8','9','/'},
								 {'4','5','6','*'},
								 {'1','2','3','-'},
								 {'C','0','=','+'}};

/* Initializes keypad by configuring row pins as outputs */
void initKPM(void)
{
	IODIR1 =(IODIR1& ~(0xF<<R0))|(15<<R0);
}

/* Scans keypad columns to detect if any key is pressed */
u32 colscan(void)
{
	if(((IOPIN1>>C0)&15)<15)
	{
		return 0;   // Key press detected
	}
	else
	{
		return 1;   // No key pressed
	}
}

/* Checks which row the pressed key belongs to */
u32 rowcheck(void)
{
	u32 rno;
	for(rno=0;rno<4;rno++)
	{
		IOPIN1 = ((IOPIN1 &~(0xF<<R0))|(~(1<<rno)<<R0)); // Activate one row at a time
		if(colscan()==0)
			break;   // Stop when column detects key press
	}
	IOPIN1 = ((IOPIN1 &~(0xF<<R0))|(0x0<<R0)); // Reset row outputs
	return rno;
}

/* Checks which column the pressed key belongs to */
u32 colcheck(void)
{
	u32 cno;
	for(cno=0;cno<4;cno++)
	{
		if(((IOPIN1>>(C0+cno))&1)==0)  // Detect low column signal
		{
			break;
		}
	}
	return cno;
}

/* Performs complete keypad scan and returns the pressed key */
u32 keyscan(void)
{
	u32 key,rn,cn;

	while(colscan());      // Wait until a key is pressed

	rn=rowcheck();         // Detect row number
	cn=colcheck();         // Detect column number

	key=kpmLUT[rn][cn];    // Fetch key value from lookup table

	while(!colscan());     // Wait until key is released

	return key;
}

/* Reads numeric input from keypad until '=' key is pressed */
u32 readnum(void)
{
	u32 key,res=0;

	while(1)
	{
		key=keyscan();   // Get key from keypad

		if(key>='0' && key<='9')   // If numeric key
		{
			res=(res*10)+(key -'0');   // Form multi-digit number
			charLCD(key);              // Display digit on LCD
		}

		else if(key=='C')   // If clear/backspace key
		{
			if(res>0)
			{
				res/=10;                    // Remove last digit
				cmdLCD(SHIFT_CUR_LEFT);
				charLCD(' ');
				cmdLCD(SHIFT_CUR_LEFT);
			}
		}

		else if(key=='=')   // End input when '=' pressed
		{
			break;
		}
	}

	return res;   // Return final entered number
}
