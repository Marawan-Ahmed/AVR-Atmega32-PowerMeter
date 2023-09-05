#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

// initialize LCD
void LCD_voidInitDisplay(void);

// send command #VIMP
void LCD_voidSendCMD(u8 copy_u8Command);

// special commands
void LCD_voidClrDisplay(void);
void LCD_voidReturnHome(void);
void LCD_voidSetCursorPosition(u8 copy_u8XPosition, u8 copy_u8YPosition);
void LCD_voidCursorBlinkOnOff(u8 copy_u8Flag);
void LCD_voidDisplayOnOff(u8 copy_u8Flag);
void LCD_voidCursorShiftLeft(u8 copy_u8Flag);
void LCD_voidCursorShiftRight(u8 copy_u8Flag);
void LCD_voidDisplayShiftLeft(u8 copy_u8Flag);
void LCD_voidDisplayShiftRight(u8 copy_u8Flag);


// display on LCD
void LCD_voidDisplayChar(u8 copy_u8Char);
void LCD_voidDisplayStr(const u8 *copy_u8Str);
void LCD_voidDisplayInt(u32 copy_u32Number);


// special char shenanigans (will leave them for now)
void LCD_voidSendSpecChar(u8 copy_u8CharIndex, u8 *copy_u8SpecialChar);
void LCD_voidDisplaySpecChar(u8 copy_u8CharIndex);

#endif