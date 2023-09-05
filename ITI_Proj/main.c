/*
 * main.c
 *
 * Created: 9/5/2023 3:10:20 PM
 *  Author: Ahmed
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


#include "../LIB/BIT_Math.h"
#include "../LIB/STD_Types.h"
#include "../MCAL/TIM0/TIM0.c"
#include "../MCAL/ADC/ADC_Prog.c"
#include "../MCAL/DIO/DIO_Prog.c"

#include "../HAL/LED/LED_Prog.c"
#include "../HAL/LCD/LCD_Prog.c"
#include "../HAL/VSEN/VSEN.c"
#include "../HAL/ACS712/ACS712.c"
#include "../APP/calculations.c"
#include <util/delay.h>



int main(void)
{
	LED_voidLEDSingleInit(DIO_PORTD, DIO_PIN7);

	CALC_voidInit();
	
	LCD_voidInitDisplay();

	f32 local_u32Current = ACS712_f32GetCurrentReading();
	f32 local_f32Voltage = VSEN_f32GetVoltageReading();
	f64 local_f64Temp = 3.3;

    while(true)
    {
        local_f32Voltage = (u32)CALC_f64GetRMSVoltage_mV(); 
		LCD_voidDisplayInt(local_f32Voltage);
		_delay_ms(10);
		LCD_voidClrDisplay();
    }
}