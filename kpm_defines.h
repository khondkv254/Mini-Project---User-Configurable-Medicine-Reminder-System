#include "typedef.h"

/* Row pin definitions for keypad matrix */
#define R0 16
#define R1 17
#define R2 18
#define R3 19

/* Column pin definitions for keypad matrix */
#define C0 20
#define C1 21
#define C2 22
#define C3 23

/* Initializes keypad pins for scanning */
void initKPM(void);

/* Scans keypad columns to detect key press */
u32 colscan(void);

/* Checks which row is active after key press */
u32 rowcheck(void);

/* Checks which column is active after key press */
u32 colcheck(void);

/* Performs complete keypad scan and returns pressed key */
u32 keyscan(void);

/* Reads numeric value entered from keypad */
u32 readnum(void);
