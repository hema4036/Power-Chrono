//lcd_defines.h
//HD44780 Commands 
#ifndef LCD_DEFINES_H
#define LCD_DEFINES_H

// LCD COMMANDS
#define CLEAR_LCD            0x01    // Clear entire display and return cursor to home position
#define RET_CUR_HOME         0x02    // Return cursor to home without clearing display
#define SHIFT_CUR_RIGHT      0x06    // Cursor moves right after each character write
#define SHIFT_CUR_LEFT       0x07    // Cursor moves left after each character write
#define DSP_OFF              0x08    // Display OFF (cursor and display both off)
#define DSP_ON_CUR_OFF       0x0c    // Display ON, cursor OFF
#define DSP_ON_CUR_ON        0x0E    // Display ON, cursor ON 
#define DSP_ON_CUR_BLINK     0x0F    // Display ON, cursor blinking
#define SHIFT_DISP_LEFT      0x10    // Shift the entire display to the left 
#define SHIFT_DISP_RIGHT     0x14    // Shift the entire display to the right

// LCD Mode Selection Commands
#define MODE_8BIT_1LINE      0x30    // 8-bit interface, 1-line mode
#define MODE_4BIT_1LINE      0x20    // 4-bit interface, 1-line mode
#define MODE_8BIT_2LINE      0x38    // 8-bit interface, 2-line mode
#define MODE_4BIT_2LINE      0x28    // 4-bit interface, 2-line mode

// DDRAM line starting addresses
#define GOTO_LINE1_POS0      0x80     // Set DDRAM address to start of line 1
#define GOTO_LINE2_POS0      0xC0     // Set DDRAM address to start of line 2
#define GOTO_LINE3_POS0      0x94     // For 20x4 LCD: Line 3 starting address
#define GOTO_LINE4_POS0      0xD4     // For 20x4 LCD: Line 4 starting address
#define GOTO_CGRAM_START     0x40     // Set CGRAM address (for custom characters)


// LCD PIN CONFIGURATION

#define LCD_MODE 8   // LCD Interface Mode Selection     Using 8-bit LCD mode
#define LCD_DATA 8   //@p0.8(d0) to p0.15(d7)
#define LCD_RS   16  //p0.16
#define LCD_RW   17  //p0.17
#define LCD_EN   18  //p0.18 
#endif //LCD_DEFINES_H

