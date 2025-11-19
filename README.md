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
1.Initialize LCD, Keypad, RTC, GPIO, and External Interrupt.
2.Continuously read RTC values.
3.Display current Date & Time on LCD.
4.Compare current time with:
5.Device ON time and Device OFF time
7.Turn the device ON/OFF automatically.
8.If user presses the interrupt switch, show the Edit Menu.
9.Allow user to modify:
  RTC Time/Date
  Device ON time
  Device OFF time
10.Validate user inputs before updating.
11.Resume normal operation after editing.

