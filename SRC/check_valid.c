// check_valid.h                            

#include"LCD.h"
#include"LCD_defines.h"
#include"delay.h"
#include"types.h"

// Validate Hour (0–23)
int check_hour(u32 hour)  
{
   CmdLCD(CLEAR_LCD);       // Clear LCD before showing any message
   if(hour>23)              // Check if hour is above valid limit    
   {
   StrLCD("Invalid Hour");   // Display error message
   delay_s(1);               // Wait for 1 second
   CmdLCD(CLEAR_LCD);        // Clear LCD again
   return 0;                 // Return invalid
 }
 return 1;                   // Valid hour
}

// Validate Minute (0–59)
int check_minute(u32 minute)       
{
  CmdLCD(CLEAR_LCD);         // Clear LCD
  if(minute>59)              // Invalid minute check
  {
    StrLCD("Invalid MIN");   // Show error
    delay_s(1);              // Wait
    CmdLCD(CLEAR_LCD);        // Clear LCD
    return 0;                 // Invalid
  }
  return 1;                 // Valid minute
}

// Validate Second (0–59)
int check_second(u32 second)
{ 
  CmdLCD(CLEAR_LCD);        // Clear LCD
  if(second>59)             // Check invalid seconds
  {
    StrLCD("Invalid SEC");  // Show message  
    delay_s(1);
    CmdLCD(CLEAR_LCD);      
    return 0;                // Invalid
  }
  return 1;                  // Valid second
}

// Validate Day (0–6) (Assuming 0=Sun, 6=Sat)
int check_day(u32 day)
{
	CmdLCD(CLEAR_LCD);
  if(day>6)              // Day should be within 0–6
  {
    StrLCD("Invalid Day");
    delay_s(1);
    CmdLCD(CLEAR_LCD);
    return 0;
  }
  return 1;
}

// Validate Date based on Month & Year
int check_date(u32 date,u32 month,u32 year)
{ 
	CmdLCD(CLEAR_LCD);
  if(date==0)          // Date cannot be zero
  {
    StrLCD("Date cant zero");
    delay_s(1);
    CmdLCD(CLEAR_LCD);
     return 0;
  }
	
	// -------- Handle February --------
  if(month == 2)
  {
		// Leap year check
    if(((year%4==0) && (year % 100 != 0)) || (year % 400 == 0))
    {
      if(date>29)      // Max date = 29 in leap year
				{
					StrLCD("You may choose");
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD("upto 29 only");
					delay_s(1);
					CmdLCD(CLEAR_LCD);
					return 0;
				}
    }
    else 
			{
      if(date>28)     // Max date = 28 in normal year
				{            
					StrLCD("You may choose");
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD("upto 28 only");
					delay_s(1);
					CmdLCD(CLEAR_LCD);
					return 0;
				}
			}
	}
	
	// -------- Handle 31-day months --------
	else if(((month%2) && (month<8)) ||     // 1,3,5,7
		((month%2==0) && (month>=8)))          // 8,10,12
	{
    if(date>31)
			{
				StrLCD("You may choose");
				CmdLCD(GOTO_LINE2_POS0);
				StrLCD("upto 31 only");
				delay_s(1);
				CmdLCD(CLEAR_LCD);
				return 0;
			}
	} 
	
	 // -------- Handle 30-day months -------
	else      
		{
			if(date>30)
				{
					StrLCD("You may choose");
					CmdLCD(GOTO_LINE2_POS0);
					StrLCD("upto 30 only");
					delay_s(1);
					CmdLCD(CLEAR_LCD);
					return 0;
				}
		}
		return 1;         // Valid date
}

// Validate Month and Adjust Date Pointer
int check_month(u32 month,u32 year,u32 *date)
{
	CmdLCD(CLEAR_LCD);
	if(month==0)     // Month cannot be zero
		{
			StrLCD("month cant zero");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			return 0;
		}     
		if(month>12)    // Wrong month entry (>12)
			{
				StrLCD("Invalid month");
				delay_s(1);
				CmdLCD(CLEAR_LCD);
				return 0;
			}
		// -------- February Handling --------
		else if(month==2)
			{
				// Leap year check
					if(((year%4==0) && (year % 100 != 0)) || (year % 400 == 0))
						{
							if(*date>29)      // Max 29
								{
									StrLCD("Previous date is");
									CmdLCD(GOTO_LINE2_POS0);
									StrLCD("Changed to 29");
									*date=29;
								}
						}
					else
					  { 
								if(*date>28)    // Max 28
									{
										StrLCD("Previous date is");
										CmdLCD(GOTO_LINE2_POS0);
										StrLCD("Changed to 28");
										*date=28;
									}
							}
			}
		// -------- 30-day months --------	
		else if(((month%2==0) && (month<8)) ||   // 4,6
			((month%2) && (month>8)))              // 9,11
			{
				if(*date>30)                         // Max 30
					{
						StrLCD("Previous date is");
						CmdLCD(GOTO_LINE2_POS0);
						StrLCD("Changed to 30");
						*date=30;
					}
			}
			return 1;                               // Valid month
}

// Validate Year and Adjust Date If February
int check_year(u32 year,u32 month,u32 *date)
{
	CmdLCD(CLEAR_LCD);
  if(year==0)                // Year cannot be zero
	{
      StrLCD("year cant zero");
			delay_s(1);
			CmdLCD(CLEAR_LCD);
			return 0;
	}
	else if(year>4095)        // RTC limit (12-bit year)
	{
		StrLCD("Invalid year");
		delay_s(1);
		CmdLCD(CLEAR_LCD);
		return 0;
	}
	 // -------- If leap year and month is Feb --------
  else if((((year%4==0) && (year % 100 != 0)) || (year % 400 == 0)) && (month==2))
	{
		if(*date>29)   // Set to 29
		{
			StrLCD("Previous date is");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("Changed to 29");
			*date=29;
		}
  }
	// -------- Non-leap year, Feb --------
  else if(!(((year%4==0) && (year % 100 != 0)) || (year % 400 == 0)) && (month==2))
  {
		if(*date>28)    // Set to 28
    {
			StrLCD("Previous date is");
			CmdLCD(GOTO_LINE2_POS0);
			StrLCD("Changed to 28");
			*date=28;
		}
  } 
  return 1;       // Valid year
}
