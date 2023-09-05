#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

/**
	@TODO:
	Change these commands definition depending on the following:
	1. Mode of operation (4-bit or 8-bit)
	2. Line Mode (1 or 2 lines)
	3. Make a shift flag
	4. Make an I/D flag
	5. Data Length (DL) is connected to mode of operation (point 1)
	6. Make a B flag
	7. Make a C flag
	8. Make a D flag
	9. Make an N flag
	10. Make an F flag
	11. Make an S/C flag
	12. Make an R/L flag
*/

/** LCD Mode of Operation */
#define LCD_4BIT_MODE 4
#define LCD_8BIT_MODE 8

/** LCD Line Mode */
#define LCD_1LINE_MODE 1
#define LCD_2LINE_MODE 2

#define LCD_LINE1 1
#define LCD_LINE2 2

/**CG/DDRAM Addresses*/
#define LCD_CGRAM_ADD 0x40
#define LCD_DDRAM_ADD1 0b10000000
#define LCD_DDRAM_ADD2 0b11000000

/** LCD Flags Default Values (can be tinkered with) ##*/
#define LCD_FLAG_SH 0
#define LCD_FLAG_INC_DEC 1
#define LCD_FLAG_DL 1
#define LCD_FLAG_BLINK_ONOFF 1
#define LCD_FLAG_CURSOR_ONOFF 1
#define LCD_FLAG_DISPLAY_ONOFF 1
#define LCD_FLAG_NUM_OF_DISPLAY_LINES 1
#define LCD_FLAG_FONT_OF_CHAR 0 // 0 for 5*7 || 1 for sth else 
#define LCD_FLAG_SHIFT_CURSOR_OR_DISPLAY 0 // 0 for cursor || 1 for display
#define LCD_FLAG_SHIFT_RIGHT_OR_LEFT 1 // 1 for right || 0 for left

/** Setting LCD Commands based on Flags */
#if (LCD_MODE_OF_OPERATION == LCD_8BIT_MODE)
	
	// LCD_CMD_FUNCTION_SET Possibilities
	#if ((LCD_FLAG_NUM_OF_DISPLAY_LINES == 0) && (LCD_FLAG_FONT_OF_CHAR == 0))
		#define LCD_CMD_FUNCTION_SET 0b0000110000 
	#elif ((LCD_FLAG_NUM_OF_DISPLAY_LINES == 0) && (LCD_FLAG_FONT_OF_CHAR == 1))
		#define LCD_CMD_FUNCTION_SET 0b0000110100 
	#elif ((LCD_FLAG_NUM_OF_DISPLAY_LINES == 1) && (LCD_FLAG_FONT_OF_CHAR == 0))
		#define LCD_CMD_FUNCTION_SET 0b0000111000 
	#elif ((LCD_FLAG_NUM_OF_DISPLAY_LINES == 1) && (LCD_FLAG_FONT_OF_CHAR == 1))
		#define LCD_CMD_FUNCTION_SET 0b0000111100 
	#endif
	
	// LCD_CMD_ENTRY_MODE_SET Possibilities
	#if ((LCD_FLAG_INC_DEC == 0) && (LCD_FLAG_SH == 0))
		#define LCD_CMD_ENTRY_MODE_SET 0b0000000100  
	#elif ((LCD_FLAG_INC_DEC == 0) && (LCD_FLAG_SH == 1))
		#define LCD_CMD_ENTRY_MODE_SET 0b0000000101  
	#elif ((LCD_FLAG_INC_DEC == 1) && (LCD_FLAG_SH == 0))
		#define LCD_CMD_ENTRY_MODE_SET 0b0000000110  
	#elif ((LCD_FLAG_INC_DEC == 1) && (LCD_FLAG_SH == 1))
		#define LCD_CMD_ENTRY_MODE_SET 0b0000000111  
	#endif
	
	// LCD_CMD_DISPLAY_ON_OFF Possibilities
	#if ((LCD_FLAG_BLINK_ONOFF == 0) && (LCD_FLAG_CURSOR_ONOFF == 0) && (LCD_FLAG_DISPLAY_ONOFF == 0))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0000001000  
	#elif ((LCD_FLAG_BLINK_ONOFF == 1) && (LCD_FLAG_CURSOR_ONOFF == 0) && (LCD_FLAG_DISPLAY_ONOFF == 0))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0000001001  
	#elif ((LCD_FLAG_BLINK_ONOFF == 0) && (LCD_FLAG_CURSOR_ONOFF == 1) && (LCD_FLAG_DISPLAY_ONOFF == 0))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0000001010
	#elif ((LCD_FLAG_BLINK_ONOFF == 1) && (LCD_FLAG_CURSOR_ONOFF == 1) && (LCD_FLAG_DISPLAY_ONOFF == 0))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0000001011
	#elif ((LCD_FLAG_BLINK_ONOFF == 0) && (LCD_FLAG_CURSOR_ONOFF == 0) && (LCD_FLAG_DISPLAY_ONOFF == 1))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0000001100
	#elif ((LCD_FLAG_BLINK_ONOFF == 1) && (LCD_FLAG_CURSOR_ONOFF == 0) && (LCD_FLAG_DISPLAY_ONOFF == 1))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0000001101
	#elif ((LCD_FLAG_BLINK_ONOFF == 0) && (LCD_FLAG_CURSOR_ONOFF == 1) && (LCD_FLAG_DISPLAY_ONOFF == 1))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0000001110
	#elif ((LCD_FLAG_BLINK_ONOFF == 1) && (LCD_FLAG_CURSOR_ONOFF == 1) && (LCD_FLAG_DISPLAY_ONOFF == 1))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0000001111
	#endif
	
	/** LCD Flags Positions ##*/
	
	// in entry mode set
	#define LCD_SH_PIN 0
	#define LCD_INC_DEC_PIN 1
	
	// in function set
	#define LCD_DL_PIN 4
	#define LCD_NUM_OF_DISPLAY_LINES_PIN 3
	#define LCD_FONT_OF_CHAR_PIN 2 
	
	// in display on/off ctrl
	#define LCD_BLINK_ONOFF_PIN 0
	#define LCD_CURSOR_ONOFF_PIN 1
	#define LCD_DISPLAY_ONOFF_PIN 2
	
	// cursor/display shift 
	#define LCD_SHIFT_CURSOR_OR_DISPLAY_PIN 1 
	#define LCD_SHIFT_RIGHT_OR_LEFT_PIN 0 
	
#elif (LCD_MODE_OF_OPERATION == LCD_4BIT_MODE)
	
	// LCD_CMD_FUNCTION_SET Possibilities
	#if ((LCD_FLAG_NUM_OF_DISPLAY_LINES == 0) && (LCD_FLAG_FONT_OF_CHAR == 0))
		#define LCD_CMD_FUNCTION_SET 0b0000000000 
	#elif ((LCD_FLAG_NUM_OF_DISPLAY_LINES == 0) && (LCD_FLAG_FONT_OF_CHAR == 1))
		#define LCD_CMD_FUNCTION_SET 0b0001000000 
	#elif ((LCD_FLAG_NUM_OF_DISPLAY_LINES == 1) && (LCD_FLAG_FONT_OF_CHAR == 0))
		#define LCD_CMD_FUNCTION_SET 0b0010000000 
	#elif ((LCD_FLAG_NUM_OF_DISPLAY_LINES == 1) && (LCD_FLAG_FONT_OF_CHAR == 1))
		#define LCD_CMD_FUNCTION_SET 0b0011000000 
	#endif
	
	// LCD_CMD_ENTRY_MODE_SET Possibilities
	#if ((LCD_FLAG_INC_DEC == 0) && (LCD_FLAG_SH == 0))
		#define LCD_CMD_ENTRY_MODE_SET 0b0001000000  
	#elif ((LCD_FLAG_INC_DEC == 0) && (LCD_FLAG_SH == 1))
		#define LCD_CMD_ENTRY_MODE_SET 0b0001010000  
	#elif ((LCD_FLAG_INC_DEC == 1) && (LCD_FLAG_SH == 0))
		#define LCD_CMD_ENTRY_MODE_SET 0b0001100000  
	#elif ((LCD_FLAG_INC_DEC == 1) && (LCD_FLAG_SH == 1))
		#define LCD_CMD_ENTRY_MODE_SET 0b0001110000  
	#endif
	
	// LCD_CMD_DISPLAY_ON_OFF Possibilities
	#if ((LCD_FLAG_BLINK_ONOFF == 0) && (LCD_FLAG_CURSOR_ONOFF == 0) && (LCD_FLAG_DISPLAY_ONOFF == 0))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0010000000  
	#elif ((LCD_FLAG_BLINK_ONOFF == 1) && (LCD_FLAG_CURSOR_ONOFF == 0) && (LCD_FLAG_DISPLAY_ONOFF == 0))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0010010000  
	#elif ((LCD_FLAG_BLINK_ONOFF == 0) && (LCD_FLAG_CURSOR_ONOFF == 1) && (LCD_FLAG_DISPLAY_ONOFF == 0))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0010100000
	#elif ((LCD_FLAG_BLINK_ONOFF == 1) && (LCD_FLAG_CURSOR_ONOFF == 1) && (LCD_FLAG_DISPLAY_ONOFF == 0))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0010110000
	#elif ((LCD_FLAG_BLINK_ONOFF == 0) && (LCD_FLAG_CURSOR_ONOFF == 0) && (LCD_FLAG_DISPLAY_ONOFF == 1))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0011000000
	#elif ((LCD_FLAG_BLINK_ONOFF == 1) && (LCD_FLAG_CURSOR_ONOFF == 0) && (LCD_FLAG_DISPLAY_ONOFF == 1))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0011010000
	#elif ((LCD_FLAG_BLINK_ONOFF == 0) && (LCD_FLAG_CURSOR_ONOFF == 1) && (LCD_FLAG_DISPLAY_ONOFF == 1))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0011100000
	#elif ((LCD_FLAG_BLINK_ONOFF == 1) && (LCD_FLAG_CURSOR_ONOFF == 1) && (LCD_FLAG_DISPLAY_ONOFF == 1))
		#define LCD_CMD_DISPLAY_ON_OFF 0b0011110000
	#endif
	
	/** LCD Flags Positions ##*/
	
	// in entry mode set
	#define LCD_SH_PIN 4
	#define LCD_INC_DEC_PIN 5
	
	// in function set
	#define LCD_DL_PIN 6
	#define LCD_NUM_OF_DISPLAY_LINES_PIN 7
	#define LCD_FONT_OF_CHAR_PIN 2 // ?! 
	
	// in display on/off ctrl
	#define LCD_BLINK_ONOFF_PIN 4
	#define LCD_CURSOR_ONOFF_PIN 5
	#define LCD_DISPLAY_ONOFF_PIN 6
	
	// cursor/display shift 
	#define LCD_SHIFT_CURSOR_OR_DISPLAY_PIN 4
	#define LCD_SHIFT_RIGHT_OR_LEFT_PIN 5
	
#endif

/** Commands that do not depend on flags */
#define LCD_CMD_DISPLAY_CLR 0b0000000001
#define LCD_CMD_RETURN_HOME 0b0000000010 // bit D0 is DC


/* TBC
#define LCD_CMD_SET_CGRAM_ADDRESS // dunno if I will use that 
#define LCD_CMD_SET_DDRAM_ADDRESS // dunno if I will use that 
#define LCD_CMD_READ_CGRAM_DATA 0b1000000000 // dunno if I will use that 
#define LCD_CMD_READ_DDRAM_DATA 0b1100000000 // dunno if I will use that 
*/

#endif