//miniproject.c

#include<LPC21xx.h>
#include"types.h"
#include"LCD.h"
#include"LCD_defines.h"
#include"kpm.h"
#include"delay.h"
#include"pin_select.h"
#include"Interrupt.h"
#include"RTC.h"   
#include"LCD.h"
#include"LCD_defines.h"


#define LED 4      // LED connected to P0.4
#define ONOFF 20   // ON/OFF button pin P0.20

// Custom CGRAM pattern (24 bytes i.e, 3 characters)
u8 D_On_Time_CGRAM[24]={0x0e,0x1f,0x1f,0x1f,0x1f,0x0e,0x0a,0x0a,
                        0x0e,0x11,0x11,0x11,0x15,0x0e,0x0a,0x0a,
                        0x04,0x0e,0x0e,0x0e,0x1f,0x04,0x00,0x04};

u32 Interrupt_Flag=0;   // Set by EINT0 ISR when switch is pressed

// Global RTC variables
static s32 hour,minute,second,date,month,year,day;
// Device ON/OFF time storage
u32 D_On_Time_Hour=0,D_On_Time_Minute=0,D_Off_Time_Hour=0,D_Off_Time_Minute=0;
int main()
{
	Init_RTC();   // Initialize Real-Time Clock
	
	InitLCD();    // Initialize LCD in required mode
 
	InitKPM();    // Initialize keypad module
 
	IODIR0|=(1<<LED);   // Configure P0.4 as output
 
	IOCLR0=(1<<LED);    // LED initially OFF
 
	DOM=1;    // Default date: 1
  MONTH=1;   // Default month: January
  YEAR=1000;  // Default year: 1000
 
	CfgPortPinFun(0,1,PIN_FUNC4);   // Configure P0.1 as EINT0 function
 
	VICIntSelect=0;    // Select IRQ mode
  VICIntEnable=1<<EINT0_VIC_CHNO;  // Enable EINT0 interrupt
  VICVectCntl0=((1<<5)|EINT0_VIC_CHNO);   // Enable slot + channel
  VICVectAddr0= (u32) eint0_isr;        // Assign ISR address
	
 EXTINT=0;      // Clear any pending external interrupts
 EXTMODE=1<<0;  // Set EINT0 to edge-triggered mode 
 EXTPOLAR=0;     // Trigger on falling edge
	
 while(1)
 {
	 // Read current RTC values
	 GetRTCTimeInfo(&hour,&minute,&second);
	 GetRTCDateInfo(&date,&month,&year);
	 GetRTCDay(&day);
	 
	 // Display time, date, day on LCD
	 DisplayRTCTime(hour,minute,second);
	 DisplayRTCDate(date,month,year);
	 DisplayRTCDay(day);
	 
	 CmdLCD(GOTO_LINE1_POS0+11);   // Move cursor to print "DEV:"
	 StrLCD("DEV:");
	 BuildCgram(D_On_Time_CGRAM,24);  // Load CGRAM characters
	 CmdLCD(GOTO_LINE1_POS0+15);     // Position to display symbol
	 CharLCD(1);                // Print CGRAM character 1
	 IOCLR0=(1<<LED);           // Keep LED OFF normally
	 
	 // Check if interrupt flag set ? user wants to edit ON/OFF time
	 if(Interrupt_Flag)
	 {
		 edit();               // Function to modify  RTC and ON/OFF time
		 Interrupt_Flag=0;     // Clear flag
	 }
	 
	 if(((IOPIN0>>ONOFF)&1)==0)   // Show ON/OFF times if ONOFF button is pressed
	 {
		 CmdLCD(CLEAR_LCD);
		 CmdLCD(GOTO_LINE1_POS0);
		 StrLCD("ON TIME =");
		 U32LCD(D_On_Time_Hour);
		 CharLCD(':');
		 U32LCD(D_On_Time_Minute);
		 
		 CmdLCD(GOTO_LINE2_POS0);
		 StrLCD("OFF TIME =");
		 U32LCD(D_Off_Time_Hour);
		 CharLCD(':');
		 U32LCD(D_Off_Time_Minute);
		 
		 delay_s(3);
		 CmdLCD(CLEAR_LCD);
	}
	 
  if((D_On_Time_Hour>0)||(D_On_Time_Minute>0))  // If ON TIME is set (not 00:00)
  {
		BuildCgram(D_On_Time_CGRAM,24);
		CmdLCD(GOTO_LINE1_POS0+9); 
		CharLCD(2);                 // Show ON-time symbol
  }
	
  if((HOUR==D_On_Time_Hour) && (MIN==D_On_Time_Minute))  // If current time matches ON TIME
	{
		while(1)
		{
			BuildCgram(D_On_Time_CGRAM,24);
			CmdLCD(GOTO_LINE1_POS0+15); 
			CharLCD(0);     // Show ON symbol
			
			IOSET0|=1<<LED;  // Turn LED ON
			
			 // Continuously update displayed RTC values
			GetRTCTimeInfo(&hour,&minute,&second);
			GetRTCDateInfo(&date,&month,&year);
			GetRTCDay(&day);
			DisplayRTCTime(hour,minute,second);
			DisplayRTCDate(date,month,year);
			DisplayRTCDay(day);
			
			// Stop loop when OFF TIME matches current time
			if((HOUR==D_Off_Time_Hour) &&(MIN==D_Off_Time_Minute))
				break;
		}
   }
  }
}
