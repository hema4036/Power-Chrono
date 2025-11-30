//kpm.c
#include<LPC21xx.h>
#include"types.h"
#include"defines.h"
#include"LCD.h"
#include"LCD_defines.h"
#include"kpm.h"
#include"delay.h"

// look up table for 4X4 keypad matrix
u32 kpmlut[4][4]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};


void InitKPM(void)     // Initialize keypad module
{
	// Set ROW pins as output
	WRITENIBBLE(IODIR1,ROW0,15);
	// Set COLUMN pins as input
  WRITENIBBLE(IODIR1,COL0,0);
}

u32 ColScan(void)    // Scan columns — returns 0 if any key is pressed, else 1
{
   u32 status;
   status=READNIBBLE(IOPIN1,COL0);
	 
	 // If status < 15 (1111), means a column is pulled low ? key pressed
   return (status<15)?0:1;
}

u32 RowCheck(void) // Check which ROW is active
{
   u32 r;
   for(r=0;r<=3;r++)
   {
		 // Drive one row low at a time
      WRITENIBBLE(IOPIN1,ROW0,~(1<<r));
      
		 if(ColScan()==0)
				break;
	 }
	 
	 // Reset all rows
   WRITENIBBLE(IOPIN1,ROW0,0);
   return r; //return the row value
}

u32 ColCheck(void)   // Check which COLUMN is active
{
   u32 c;
   for(c=0;c<=3;c++)
   {
		 // Check each column line individually
		 if(READBIT(IOPIN1,(COL0+c))==0)
        break;
   }
      return c;
}

u32 KeyScan(void)   // Full key scanning
{
    u32 r,c,keyval;
    while(ColScan());  // Wait until key is released
    delay_ms(20);      // Debounce delay
	
    // Detect row and column	
    r=RowCheck();
    c=ColCheck();
	
	   // Lookup actual key value
    keyval=kpmlut[r][c];
    return keyval;
}
void ReadNum(u32 *num,u32 *lastkey)   // Reads multi-digit number from keypad
{
  u8 keyval; s8 cnt=0;
  *num=0;
   while(1)
   {
		 keyval=KeyScan();
		 delay_ms(150);     // Debounce
		 
		 // If key is 0–9
		 if((keyval>='0') && (keyval<='9'))
     {
			 // Build number
			 *num=(*num*10)+(keyval-48);
       // Wait till key release			 
			 while(ColScan()==0);
			 // Display updated number
			 CmdLCD(GOTO_LINE2_POS0);
			 U32LCD(*num);
			 cnt++;
			 
			 // Limit to 6 digits
			 if(cnt>5)
			 {
				 CmdLCD(GOTO_LINE2_POS0);
				 StrLCD("Limit Exceeds");
				 delay_ms(700);
				 
				 *num/=10; // Remove last digit
				 CmdLCD(GOTO_LINE2_POS0);
				 StrLCD("                ");  // Clear line
				 CmdLCD(GOTO_LINE2_POS0);
				 U32LCD(*num);
			 }
		 }
		 
		 else if((keyval=='B') && (cnt>0))  // Backspace (B)
		 {
			 *num/=10;  // Delete last digit
			 while(ColScan()==0);
			 cnt--;
			 CmdLCD(GOTO_LINE2_POS0+cnt);
			 CharLCD(' ');    // Erase last character
			 CmdLCD(GOTO_LINE2_POS0+cnt);
		 }
		 else if(keyval=='A')   // Enter (A)
		 {
			 while(ColScan()==0);
			 break;   // Finish input
		 }
		 else
		 {
			 while(ColScan()==0);  // Ignore invalid keys
			 continue;
		 }
	 }
}
