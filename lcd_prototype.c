#include "types.h"
#include "Delay.h"
#include "lcd_define.h"
#include <lpc21xx.h>

/* Writes 8-bit data or command to LCD */
void writeLCD(u8 data)
{
	IOCLR0 = 1<<RW; // Set RW=0 to select write operation
	IOPIN0 = ((IOPIN0 &~(0xFF<<LCD))|(data<<LCD)); // Place data on LCD data pins
	IOSET0 = 1<<EN; // Generate enable pulse (EN=1)
	delay_us(1); // Short delay for LCD timing
	IOCLR0 = 1<<EN; // EN=0 to latch data into LCD
	delay_ms(2); // Wait for LCD to process command/data
}

/* Sends command/instruction to LCD */
void cmdLCD(u8 ch)
{
	IOCLR0 = 1<<RS; // RS=0 selects instruction register
	writeLCD(ch); // Send command to LCD
}

/* Displays a single character on LCD */
void charLCD(u8 ch)
{
	IOSET0 = 1<<RS; // RS=1 selects data register
	writeLCD(ch); // Send character data to LCD
}

/* Initializes LCD in 8-bit, 2-line display mode */
void initLCD(void)
{
	IODIR0 |= 0xFF<<LCD; // Configure LCD data pins as output
	IODIR0 |= 0x7<<RS; // Configure RS, RW, EN pins as output

	cmdLCD(MODE_8BIT_LINE1); // Initialize LCD
	delay_ms(15);

	cmdLCD(MODE_8BIT_LINE1); // Repeat initialization sequence
	delay_ms(5);

	cmdLCD(MODE_8BIT_LINE1);
	delay_us(100);

	cmdLCD(MODE_8BIT_LINE1);
	cmdLCD(MODE_8BIT_LINE2); // Set 8-bit mode with 2 display lines
	cmdLCD(DISP_ON); // Turn display ON
	cmdLCD(CLR_LCD); // Clear LCD display
}

/* Displays a string on LCD until null character */
void strLCD(u8 *p)
{
	while(*p)
	{
		charLCD(*p); // Print character
		p++; // Move to next character
	}
}

/* Creates a custom character in CGRAM location */
void cust_char(u8 *p,u8 nb)
{
	s32 i;
	cmdLCD(GOTO_CGRAM + (nb * 8)); // Select CGRAM location
	for(i=0;i<8;i++)
	{
		charLCD(p[i]); // Write pattern data
	}
	cmdLCD(GOTO_LINE1_POS0); // Return cursor to line 1
}

/* Displays integer number on LCD */
void dispint(u32 var)
{
	s32 i=0,arr[10];

	do
	{
		arr[i++]=(var%10)+48; // Convert digit to ASCII
		var/=10; // Extract next digit
	}
	while(var);

	for(--i;i>=0;i--)
	{
		charLCD(arr[i]); // Print digits in correct order
	}
}
