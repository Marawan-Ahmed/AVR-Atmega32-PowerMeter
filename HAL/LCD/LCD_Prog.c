#include "../../LIB/Bit_Math.h"
#include "../../MCAL/DIO/DIO_CFG.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LCD_CFG.h"
#include "LCD_Private.h"
#include "LCD_Interface.h"
#include <util/delay.h>

void LCD_voidInitDisplay(void)
{
	DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_CTRL_RS, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_CTRL_RW, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT, LCD_CTRL_EN, DIO_PIN_OUTPUT);
	
	#if (LCD_MODE_OF_OPERATION == LCD_4BIT_MODE)
		DIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN0, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN1, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN2, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection(LCD_DATA_PORT, LCD_DATA_PIN3, DIO_PIN_OUTPUT);
	#elif (LCD_MODE_OF_OPERATION == LCD_8BIT_MODE)
		DIO_voidSetPortDirection(LCD_DATA_PORT, DIO_PORT_OUTPUT);
	#endif
	_delay_ms(35);
	#if (LCD_MODE_OF_OPERATION == LCD_4BIT_MODE)
		LCD_voidSendCMD(0b000010000);
		_delay_us(50);
		LCD_voidSendCMD(0b000010000);
		_delay_us(50);
	#endif
	LCD_voidSendCMD(LCD_CMD_FUNCTION_SET);
	_delay_us(50);
	
	#if (LCD_MODE_OF_OPERATION == LCD_4BIT_MODE)
		LCD_voidSendCMD(0b000000000);
		_delay_us(50);
	#endif
	LCD_voidSendCMD(LCD_CMD_DISPLAY_ON_OFF);
	_delay_us(50);
	
	#if (LCD_MODE_OF_OPERATION == LCD_4BIT_MODE)
		LCD_voidSendCMD(0b000000000);
		_delay_ms(2);
	#endif
	LCD_voidSendCMD(LCD_CMD_DISPLAY_CLR);
	_delay_ms(2);
	
	#if (LCD_MODE_OF_OPERATION == LCD_4BIT_MODE)
		LCD_voidSendCMD(0b000000000);
		_delay_us(50);
	#endif
	LCD_voidSendCMD(LCD_CMD_ENTRY_MODE_SET);
	_delay_us(50);
}

void LCD_voidSendCMD(u8 copy_u8Command)
{
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_CTRL_RS, DIO_PIN_LOW);
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_CTRL_RW, DIO_PIN_LOW);
	DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8Command);
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_CTRL_EN, DIO_PIN_HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_CTRL_EN, DIO_PIN_LOW);
}

void LCD_voidClrDisplay(void)
{
	LCD_voidSendCMD(LCD_CMD_DISPLAY_CLR);
	_delay_ms(2);
}

void LCD_voidReturnHome(void)
{
	LCD_voidSendCMD(LCD_CMD_RETURN_HOME);
	_delay_ms(1);  
}

void LCD_voidDisplayChar(u8 copy_u8Char)
{
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_CTRL_RS, DIO_PIN_HIGH); // data
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_CTRL_RW, DIO_PIN_LOW); // Write
	DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8Char);
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_CTRL_EN, DIO_PIN_HIGH); // EN rising edge
	_delay_us(1);
	DIO_voidSetPinValue(LCD_CTRL_PORT, LCD_CTRL_EN, DIO_PIN_LOW); // EN rising edge
	_delay_ms(10);
}

void LCD_voidDisplayStr(const u8 *copy_u8Str)
{
	if (copy_u8Str == NULL)
		return;
	
	u8 local_u8Iterator;
	for (local_u8Iterator = 0; copy_u8Str[local_u8Iterator] != '\0'; local_u8Iterator++)
		LCD_voidDisplayChar(copy_u8Str[local_u8Iterator]);
}

void LCD_voidDisplayInt(u32 copy_u32Number)
{
	u8 local_u8NumAsCharArr[10];
	u8 local_u8NumDigits = 0;
	
	u32 local_u32ReversedNum = 0;
	
	s8 local_s8Iterator;
	
	// reversing the number so that it will be stored in order
	while (copy_u32Number)
	{
		local_u32ReversedNum = (local_u32ReversedNum * 10) + (copy_u32Number % 10);
		copy_u32Number /= 10;
		local_u8NumDigits++;
	}
	
	for (local_s8Iterator = 0; local_s8Iterator < local_u8NumDigits; local_s8Iterator++)
	{
		local_u8NumAsCharArr[local_s8Iterator] = (local_u32ReversedNum % 10) + '0';
		local_u32ReversedNum /= 10;
	}
	local_u8NumAsCharArr[local_u8NumDigits] = '\0';
	
	LCD_voidDisplayStr(local_u8NumAsCharArr);
}

void LCD_voidSetCursorPosition(u8 copy_u8XPosition, u8 copy_u8YPosition)
{
	switch (copy_u8YPosition)
	{
		case LCD_LINE1: LCD_voidSendCMD(0x80 + copy_u8XPosition); break;
		case LCD_LINE2: LCD_voidSendCMD(0xC0 + copy_u8XPosition); break;
	}
}

