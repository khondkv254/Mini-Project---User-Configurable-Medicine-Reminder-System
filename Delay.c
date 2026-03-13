#include "types.h"
#include "Delay.h"

/*
---------------------------------------------------
Function Name : delay_us
Description   : Generates delay in microseconds.
Argument      : us ? number of microseconds to delay
Method        : Software loop delay. 
                Loop count multiplied by 12 because
                approximately 12 CPU cycles execute 
                one loop iteration.
---------------------------------------------------
*/
void delay_us(u32 us)
{
	for(us *= 12; us > 0; us--);
}

/*
---------------------------------------------------
Function Name : delay_ms
Description   : Generates delay in milliseconds.
Argument      : ms ? number of milliseconds to delay
Method        : Uses a software loop where each 
                millisecond is approximated using
                12000 loop iterations based on CPU
                clock frequency.
---------------------------------------------------
*/
void delay_ms(u32 ms)
{
	for(ms *= 12000; ms > 0; ms--);
}

/*
---------------------------------------------------
Function Name : delay_sec
Description   : Generates delay in seconds.
Argument      : sec ? number of seconds to delay
Method        : Uses a large loop count based on 
                processor clock cycles to create
                approximately one second delay.
---------------------------------------------------
*/
void delay_sec(u32 sec)
{
	for(sec *= 12000000; sec > 0; sec--);
}
