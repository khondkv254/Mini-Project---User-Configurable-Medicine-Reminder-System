#include "Delay.h"

/* Base data pin position for LCD data lines */
#define LCD 8

/* LCD control pins */
#define RS 16   /* Register Select pin */
#define RW 18   /* Read/Write control pin */
#define EN 17   /* Enable pin */

/* LCD command definitions */
#define CLR_LCD 0X01              /* Clear LCD display */
#define RET_CUR_HOME 0x02         /* Return cursor to home position */
#define DISP_OFF 0x08             /* Turn display OFF */
#define DISP_ON 0x0C              /* Turn display ON (cursor OFF) */
#define DISP_ON_CUR_ON 0x0E       /* Display ON with cursor visible */
#define DISP_ON_CUR_BLINK 0x0F    /* Display ON with blinking cursor */

/* LCD mode configuration commands */
#define MODE_8BIT_LINE1 0X30      /* 8-bit mode single line */
#define MODE_8BIT_LINE2 0X38      /* 8-bit mode two lines */
#define MODE_4BIT_LINE1 0X20      /* 4-bit mode single line */
#define MODE_4BIT_LINE2 0X28      /* 4-bit mode two lines */

/* LCD cursor positioning commands */
#define GOTO_LINE1_POS0 0X80      /* Move cursor to line 1 position 0 */
#define GOTO_LINE2_POS0 0XC0      /* Move cursor to line 2 position 0 */
#define GOTO_LINE3_POS0 0X94      /* Move cursor to line 3 position 0 */
#define GOTO_LINE4_POS0 0XD4      /* Move cursor to line 4 position 0 */

/* Cursor and display shift commands */
#define SHIFT_CUR_RIGHT 0X06      /* Move cursor right */
#define SHIFT_CUR_LEFT 0x10       /* Move cursor left */
#define SHIFT_DISP_RIGHT 0X14     /* Shift display right */
#define GOTO_CGRAM 0x40           /* Access CGRAM for custom characters */
#define LEFT_SHIFT_DISP 0x18      /* Shift entire display left */
#define RIGHT_SHIFT_DISP 0x1C     /* Shift entire display right */

/* Initializes LCD module */
void initLCD(void);

/* Sends command to LCD */
void cmdLCD(u8);

/* Writes raw data to LCD */
void writeLCD(u8);

/* Displays single character on LCD */
void charLCD(u8);

/* Displays string on LCD */
void strLCD(u8 *);

/* Displays integer value on LCD */
void dispint(u32);

/* Creates custom character in CGRAM */
void cust_char(u8*,u8);
