// interrupt.c
// Handles External Interrupt (EINT0) and Edit Menu operations
// Includes real-time clock editing, ON/OFF time editing, and input validation.

#include<LPC214x.h>
#include"LCD.h"
#include"LCD_defines.h"
#include"kpm.h"
#include"delay.h"
#include"RTC.h"
#include"types.h"
#include"check_valid.h"

// Global variables

extern u32 Interrupt_Flag;   // Flag set by EINT0 ISR

// Temporary storage for RTC values during editing
u32 hour,minute,second,date,month,year,day,last;  

// Device ON/OFF time variables
extern u32 D_On_Time_Hour,D_On_Time_Minute,D_Off_Time_Hour,D_Off_Time_Minute;

// ISR for External Interrupt 0 (EINT0)
void eint0_isr(void) __irq
{
  Interrupt_Flag=1;   // Set interrupt flag
  EXTINT=1<<0;        // Clear EINT0 interrupt flag
  VICVectAddr=0;      // Acknowledge interrupt completion
}

/*---------------------------------------------------------------
 * edit() - To editing menu
 * Allows user to modify:
 *   1. RTC Date/Time
 *   2. Device ON/OFF time
 *---------------------------------------------------------------*/
void edit(void)
{
	u32 Keyval;
	
	// Notify user
	CmdLCD(CLEAR_LCD);
	StrLCD("Interrupt is Raised");
	delay_s(1);
	
	// Load current RTC time to local variables
	hour=HOUR;  minute=MIN;   second=SEC;
	date=DOM;   month=MONTH;  year=YEAR;  day=DOW;
	
MAIN_MENU:
	/*---------  Main menu  ---------*/
	CmdLCD(CLEAR_LCD);
	CmdLCD(GOTO_LINE1_POS0);
	StrLCD("1.E.TIME");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("2.E.ONOFF TIME");
	CmdLCD(GOTO_LINE1_POS0+10);
	StrLCD("3.EXIT");
	
	while(ColScan());
	Keyval=KeyScan();
	delay_ms(150);
	CmdLCD(CLEAR_LCD);
	
	switch(Keyval)
	{
		/*---- OPTION 1 - EDIT RTC TIME / DATE ----*/
		case '1': 
EDIT_RTC:
		StrLCD("1.H 2.M 3.S 4.Day");
		CmdLCD(GOTO_LINE2_POS0);
		StrLCD("5.d 6.M 7.Y 8.E");
		
		while(ColScan());
		Keyval=KeyScan();
		delay_ms(150);
		CmdLCD(CLEAR_LCD);
		
		switch(Keyval)
		{
			/*------------------- Edit Hour ---------------------*/
			case '1':
EDIT_HOUR:
			  StrLCD("HOUR(0 T0 23)");
			  CmdLCD(GOTO_LINE2_POS0);
			  ReadNum(&hour,&last);
			
   			if(check_hour(hour)==0)
				   goto EDIT_HOUR;

		  	HOUR=hour;
			  goto EDIT_RTC;
				
			/*------------------- Edit Minute -------------------*/
			case '2':
EDIT_MIN: 
			  StrLCD("MIN(0 TO 59)");
			  CmdLCD(GOTO_LINE2_POS0);
			  ReadNum(&minute,&last);

  			if(check_minute(minute)==0)
				    goto EDIT_MIN;
	  	
				MIN=minute;
		  	goto EDIT_RTC;
				
			/*------------------- Edit Second -------------------*/
			case '3':
EDIT_SEC:
   			StrLCD("SEC(0 TO 59)");
   			CmdLCD(GOTO_LINE2_POS0);
        ReadNum(&second,&last);
     
			  if(check_second(second)==0)
					goto EDIT_SEC;
   
				SEC=second;
        goto EDIT_RTC;
				
			/*------------------- Edit Day-of-Week --------------*/
			case '4':
 EDIT_DAY:
			  StrLCD("Day(0 TO 6)");
        CmdLCD(GOTO_LINE2_POS0);
        ReadNum(&day,&last);
       
			  if(check_day(day)==0)
        goto EDIT_DAY;
       
				DOW=day;
        goto EDIT_RTC; 
      
			 /*------------------- Edit Date ----------------------*/
			case '5':
 EDIT_DATE: 
			  StrLCD("Date(1 TO 31)");
        CmdLCD(GOTO_LINE2_POS0);
			  ReadNum(&date,&last);
   
			  if(check_date(date,month,year)==0)
					goto EDIT_DATE;

				DOM=date;
				goto EDIT_RTC;

			/*------------------- Edit Month ---------------------*/
			case '6':
EDIT_MONTH: 
			  StrLCD("Month(1 TO 12)");
        CmdLCD(GOTO_LINE2_POS0);
        ReadNum(&month,&last);
    
			  if(check_month(month,year,&date)==0)
					goto EDIT_MONTH;
        
				MONTH=month;
        goto EDIT_RTC;
				
			/*------------------- Edit Year ----------------------*/	
			case '7': 
EDIT_YEAR: 
			  StrLCD("Year(1 TO 4095)");
        CmdLCD(GOTO_LINE2_POS0);
        ReadNum(&year,&last);
    
			  if(check_year(year,month,&date)==0)
					goto EDIT_YEAR;
   
				YEAR=year;
				goto EDIT_RTC;
				
			/*------- Exit From edit function to RTC menu -------*/	
			case '8':
				CmdLCD(CLEAR_LCD);
			  return ;
			
			/*--------------- Invalid Key ------------------------*/
			default:
				StrLCD("Invalid Key...");
        delay_s(1);
        CmdLCD(CLEAR_LCD);
        goto EDIT_RTC;
	  }
		
		// OPTION 2 FOR EDIT DEVICE ON/OFF TIME
		case '2':
EDIT_ONOFF_TIME:
		  CmdLCD(GOTO_LINE1_POS0);
   		StrLCD("1.D.Ontime");
      CmdLCD(GOTO_LINE2_POS0);
      StrLCD("2. D.Offtime");
      CmdLCD(GOTO_LINE1_POS0+11);
      StrLCD("3.EXIT");
      
		  while(ColScan());
      Keyval=KeyScan();
      delay_ms(150);
   		CmdLCD(CLEAR_LCD);
   
  		switch(Keyval)
      {
				/*--------------- Edit Device ON Time ---------------*/
				case'1':
EDIT_ON_TIME:
				  StrLCD("Edit D_On_Time");
          CmdLCD(GOTO_LINE2_POS0);
          StrLCD("1.H 2.M 3.Back");
				
          while(ColScan());
          Keyval=KeyScan();
          delay_ms(150);
          CmdLCD(CLEAR_LCD);
        
  				switch(Keyval)
          {
						/* ---- Edit Device ON Hour ---- */
						case'1':
EDIT_ON_HOUR:
						  StrLCD("Edit D_On_Hour");
              CmdLCD(GOTO_LINE2_POS0);
              ReadNum(&D_On_Time_Hour,&last);
						
              if(check_hour(D_On_Time_Hour)==0)
								goto  EDIT_ON_HOUR;
							
              CmdLCD(CLEAR_LCD);
              goto EDIT_ON_TIME;
							
						/* ---- Edit Device ON Minute ---- */
						case '2':
EDIT_ON_MIN:
						  StrLCD("Edit D_On_Minute");
						  CmdLCD(GOTO_LINE2_POS0);
						  ReadNum(&D_On_Time_Minute,&last);
						
   						if(check_minute(D_On_Time_Minute)==0)
							  goto  EDIT_ON_MIN;
						  
							CmdLCD(CLEAR_LCD);
						  goto EDIT_ON_TIME;
						
						/* ---- Go to EDIT_ONOFF_TIME Menu ----	*/
						case '3':
              CmdLCD(CLEAR_LCD);
              goto EDIT_ONOFF_TIME;
            
						/*--------------- Invalid Key ------------------------*/
						default:
              StrLCD("Invalid Key..");
              delay_s(1);
              CmdLCD(CLEAR_LCD);
               goto EDIT_ON_TIME;
					}
					
					/*--------------- Edit Device ON Time ---------------*/
	        case '2':
EDIT_OFF_TIME:
					  StrLCD("Edit D_Off_Time");
            CmdLCD(GOTO_LINE2_POS0);
            StrLCD("1.H 2.M 3.Back");
            
					  while(ColScan());
            Keyval=KeyScan();
            delay_ms(150);
            CmdLCD(CLEAR_LCD);
            
					  switch(Keyval)
						{
							/* ---- Edit Device OFF Hour ---- */
							case'1':
EDIT_OFF_HOUR:
							  StrLCD("Edit D_Off_Hour");
							  CmdLCD(GOTO_LINE2_POS0);
                ReadNum(&D_Off_Time_Hour,&last);
               
   							if(check_hour(D_Off_Time_Hour)==0)
                  goto  EDIT_OFF_HOUR;
   
								if(D_On_Time_Hour>D_Off_Time_Hour)  // ON time must be < OFF time
								{
									CmdLCD(CLEAR_LCD);
                  StrLCD("On_Time>OFF_Time");
                  CmdLCD(GOTO_LINE2_POS0);
                  StrLCD("Must be less");
                  delay_s(1);
                  CmdLCD(CLEAR_LCD);
                  goto EDIT_OFF_HOUR;
								}
								
								CmdLCD(CLEAR_LCD);
                goto EDIT_OFF_TIME;
								
							/* ---- Edit Device OFF MINUTE ----	*/
							case '2':     
EDIT_OFF_MIN:
							  StrLCD("Edit D_Off_Minute");
                CmdLCD(GOTO_LINE2_POS0);
                ReadNum(&D_Off_Time_Minute,&last);
                
							  if(check_minute(D_Off_Time_Minute)==0)
									goto  EDIT_OFF_MIN;
                
								// Prevent equal or invalid timings
								if((D_On_Time_Hour==D_Off_Time_Hour)&&
									(D_Off_Time_Minute<=D_On_Time_Minute))
                {
									CmdLCD(CLEAR_LCD);
									StrLCD("On_Tm>=OFF_Tm");
									CmdLCD(GOTO_LINE2_POS0);
									StrLCD("Must be less");
									delay_s(1);
									CmdLCD(CLEAR_LCD);
									goto EDIT_OFF_MIN;
								}
								
								CmdLCD(CLEAR_LCD);
								goto EDIT_OFF_TIME;
							
							/* ---- Go to EDIT_ONOFF_TIME Menu ----	*/
							case '3':
								goto EDIT_ONOFF_TIME;
							
							/*--------------- Invalid Key ------------------------*/
							default:
								StrLCD("Invalid Key..");
							  delay_s(1);
                CmdLCD(CLEAR_LCD);
								goto EDIT_OFF_TIME;
						} 
						
					/*------- Exit From edit function to RTC menu -------*/		
					case '3':   
						CmdLCD(CLEAR_LCD);
            return ;
					
					/*--------------- Invalid Key ------------------------*/
					default:
						StrLCD("Invalid Key..");
            delay_s(1);
					  CmdLCD(CLEAR_LCD);
            goto EDIT_ONOFF_TIME;
			}
			
		/*------- Exit From edit function to RTC menu -------*/		
    case '3':
			CmdLCD(CLEAR_LCD);
      return ;
		
		/*--------------- Invalid Key ------------------------*/
    default: 
			StrLCD("Invalid Key..");
      delay_s(1);
      goto MAIN_MENU;
	}
}
