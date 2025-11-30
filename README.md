# PowerChrono – The Future of Time-Driven Energy Automation
PowerChrono is an intelligent, time-based power management system designed to automate electrical devices using a real-time clock (RTC).
It helps industries and smart systems reduce energy waste by turning devices ON/OFF automatically according to scheduled timings.
This project is built using the LPC2148 ARM7 microcontroller, a 16×2 LCD, 4×4 Keypad, and External Interrupt for editing operations.

# Features
1.Displays real-time clock (RTC): Hour, Minute, Second, Day, Date, Month, Year
2.Allows user to edit RTC values using a keypad
3.Allows user to set Device ON Time and OFF Time
4.Automatically turns ON and OFF the device based on given ON and OFF timings
5.Supports External Interrupt to open an Edit Menu
6.Includes input validation (day, month, hours, leap year, etc.)
7.User-friendly menu system on LCD
8.Clean modular Embedded C code with drivers for:
  LCD
  Keypad
  RTC
  Interrupts

# Block Diagram
<img width="961" height="519" alt="Block Diagram" src="https://github.com/user-attachments/assets/62d0e07e-8566-4279-a3ad-a24392f481a5" />

# Hardware Requirements
1.LPC2148 ARM7 Microcontroller
2.16×2 LCD Display
3.4×4 Matrix Keypad
4.RTC (Internal of LPC2148)
5.LED/Relay (Device Control)
6.Push Button (External Interrupt)
7.USB-UART/DB9 Cable
8.Power Supply

# Software Requirements
1.Embedded C Programming
2.Keil uVision or any ARM compiler
3.Flash Magic for flashing code
4.Proteus(optional) for simulation

# Project Workflow
1.Initialize LCD, Keypad, RTC, GPIO, and External Interrupt.Continuously read RTC values.Display current Date & Time on LCD
2.External Interrupt Raised,When external interrupt is triggered, normal mode stops.
3.Edit Menu Displayed like
        1. E.TIME   3.EXIT 
        2. E.ONOFF TIME
4.Edit RTC Menu (if user selects option 1),User can change Hour, Minute, Second, Day, Date, Month, Year
        1.H 2.M 3.S 4.Day 
        5.d 6.M 7.Y 8.E 
5.Edit Device ON/OFF Time (if user selects option 2),User can set ON TIME and OFF TIME.
        1. D.Ontime   3.Exit 
        2. D.Offtime
6.If user is selected the option 3,control goed back to Main (Display current Date & Time on LCD). 
7.When ON time is set,Alarm Symbol Displayed,alarm symbol appears like mobile alarm.
8.Device Turns ON Automatically,When RTC reaches ON time, device status becomes ON.
9.Device Turns OFF Automatically,When RTC reaches OFF time, device status becomes OFF.


