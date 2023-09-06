/*
 * main.c
 *
 * Created: 9/5/2023 3:10:20 PM
 *  Author: Ahmed
 */ 

//#include <avr/io.h>
//#include <avr/interrupt.h>


#include "../LIB/BIT_Math.h"
#include "../LIB/STD_Types.h"
#include <util/delay.h>
#include "../MCAL/DIO/DIO_Prog.c"
#include "../MCAL/ADC/ADC_Prog.c"
#include "../MCAL/TIMER/TIMER_Prog.c"
#include "../MCAL/EXTI/EXTI_Prog.c"
#include "../HAL/LCD/LCD_Prog.c"
#include "../HAL/VSEN/VSEN.c"
#include "../HAL/ACS712/ACS712.c"
#include "../APP/calculations.c"




int main(void)
{
	CALC_voidInit();
	
	LCD_voidInitDisplay();

	f32 local_f32Temp = 0;
	
    while(true)
    {
        
		if (is_updated == true)
		{
			switch (Global_u8DisplayFlag)
			{
				case DISP_I:
					local_f32Temp = CALC_f64GetInstCurrent_mA();
					LCD_voidDisplayStr("I = ");
					_delay_ms(1);
					DISP_voidDisplayOnLCD(local_f32Temp);
					_delay_ms(1);
					LCD_voidDisplayStr(" A");
					_delay_ms(1);
					break;
				case DISP_V:
					local_f32Temp = CALC_f64GetInstVoltage_mV();
					LCD_voidDisplayStr("V = ");
					_delay_ms(1);
					DISP_voidDisplayOnLCD(local_f32Temp);
					_delay_ms(1);
					LCD_voidDisplayStr(" V");
					_delay_ms(1);
					break;
				case DISP_P:
					local_f32Temp = CALC_f64GetInstPower_mW();
					LCD_voidDisplayStr("P = ");
					_delay_ms(1);
					DISP_voidDisplayOnLCD(local_f32Temp);
					_delay_ms(1);
					LCD_voidDisplayStr(" W");
					_delay_ms(1);
					break;
				case DISP_E:
					local_f32Temp = CALC_f64GetEnergy_mJ();
					LCD_voidDisplayStr("E = ");
					_delay_ms(1);
					DISP_voidDisplayOnLCD(local_f32Temp);
					_delay_ms(1);
					LCD_voidDisplayStr(" W.s");
					_delay_ms(1);
					break;
			}
			is_updated = false;
		}
    }
}
