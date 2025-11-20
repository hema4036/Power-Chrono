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
![photo_2025-11-20_19-20-31](https://github.com/user-attachments/assets/c4f0fc81-de09-4c8e-afe9-2a918c10e87d)
2.External Interrupt Raised
![photo_2025-11-20_19-25-50](https://github.com/user-attachments/assets/8179781e-db04-4727-9e01-2126cfc6c300)
When external interrupt is triggered, normal mode stops.
3.Edit Menu Displayed
![photo_2025-11-20_19-26-09](https://github.com/user-attachments/assets/a3f633f9-7dae-4bd4-b58b-336c2f58f9bf)
4.Edit RTC Menu (if user selects option 1)
![photo_2025-11-20_19-26-26](https://github.com/user-attachments/assets/e5b1196d-fa80-4040-ae9b-2260b6a31426)
User can change Hour, Minute, Second, Day, Date, Month, Year
5.Edit Device ON/OFF Time (if user selects option 2)
![photo_2025-11-20_19-26-47](https://github.com/user-attachments/assets/8baff4cb-ffa4-46dd-9451-5c2df1c97863)
User can set ON TIME and OFF TIME.
6.If switch is pressed it displayed on ON/OFF Time
![photo_2025-11-20_19-27-11](https://github.com/user-attachments/assets/6e5772de-a9fb-4ddf-adbb-ffdfe5af9739)
LCD shows the configured ON and OFF times.
7.When ON time is set,Alarm Symbol Displayed
![photo_2025-11-20_19-27-20](https://github.com/user-attachments/assets/f41bc2c4-d696-4d22-beb8-4c9d82f271ac)
When ON time is set, alarm symbol (▲) appears like mobile alarm.
8.Device Turns ON Automatically
![photo_2025-11-20_19-28-53](https://github.com/user-attachments/assets/94d5ea28-25d4-448f-a28a-10fca606c06e)
When RTC reaches ON time → device status becomes ON.
9.Device Turns OFF Automatically
![photo_2025-11-20_19-28-32](https://github.com/user-attachments/assets/87634f75-cc34-4cfc-8741-fcf558362040)
When RTC reaches OFF time → device status becomes OFF.


