//pin_connect_block.c
#include "types.h"
#include <LPC21xx.h>

/*
 * Function: CfgPortPinFun
 * -----------------------
 * Configures PINSEL registers for LPC21xx.
 *
 * portNo  : Port number (0 or 1)
 * pinNo   : Pin number within the port (0–31)
 * pinFunc : Function select (0–3)
 *
 * For PORT0:
 *   PINSEL0 ? P0.0  to P0.15
 *   PINSEL1 ? P0.16 to P0.31
 *
 * For PORT1:
 *   PINSEL2 ? P1.16 to P1.31 (only upper 16 pins)
 */
 
void CfgPortPinFun(u32 portNo,u32 pinNo,u32 pinFunc)
{
	if(portNo==0)             // -------- PORT 0 --------
	{
		if(pinNo<=15)           // Configure PINSEL0
		{
			PINSEL0=((PINSEL0&~(3<<(pinNo*2)))|
			         (pinFunc<<(pinNo*2)));
		}
		else if(pinNo>=16 && pinNo<=31)     // Configure PINSEL1
		{
			PINSEL1=((PINSEL1&~(3<<((pinNo-16)*2)))|
			         (pinFunc<<((pinNo-16)*2)));
		}
	}
	/*
	else if(portNo==1)   // -------- PORT 1 --------
	{
   	if(pinNo>=16 && pinNo<=31)    // Only P1.16 to P1.31 are configurable
		{
			PINSEL2=((PINSEL2&~(3<<((pinNo-16)*2)))|
			         (pinFunc<<((pinNo-16)*2)))
		}
		
	}
	*/
}
