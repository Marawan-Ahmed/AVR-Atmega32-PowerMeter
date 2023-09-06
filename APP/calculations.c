#include "../LIB/BIT_Math.h"
#include "../LIB/STD_Types.h"

#include <math.h>
#include <avr/interrupt.h>

#include "calculations.h"

u32	Global_u32SampleCount; //used for True RMS

f64	Global_f64InstVoltage_mv;

f64	Global_f64InstCurrent_mA;

f64	Global_f64InstPower_mW;

f64	Global_f64Energy_mJ;

void CALC_voidInit(void)
{
	//Initialize Voltage and Current readings
	ACS712_voidInit();
	VSEN_voidInit();
	
	//setup the timer interrupt to run every multiple of 1mS
	sei();
	
	// initialize external interrupt
	EXTI_voidInit();
	EXTI_voidSetSignalSenseMode(EXTI_SENSE_RISING_EDGE, EXTI_GICR_INT0);
	EXTI_voidEnableInterrupt(EXTI_GICR_INT0);
	EXTI_voidSetCallBack(ISR_INT0, EXTI_INT0);
	EXTI_voidSetSignalSenseMode(EXTI_SENSE_RISING_EDGE, EXTI_GICR_INT1);
	EXTI_voidEnableInterrupt(EXTI_GICR_INT1);
	EXTI_voidSetCallBack(ISR_INT1, EXTI_INT1);
	
	TMR0_voidInit();
	TMR_voidCallBack(CALC_voidPeriodicFunc, TMR0_OVF_VECTOR_ID);
	TMR0_voidSetOVF(64);
}

void CALC_voidPeriodicFunc(void)
{
	static u16 Local_u16Count =0;
	//enter this condition every SMAPLING_PERIOD_mS 
	if(Local_u16Count == 3907){ ////////////////////?????????????????????????????????
		
		is_updated = true;
		LCD_voidClrDisplay();
		
		//read inst volt
		Global_f64InstVoltage_mv = VSEN_f32GetVoltageReading();
		//read inst current
		Global_f64InstCurrent_mA = ACS712_f32GetCurrentReading();
	
		Global_f64InstPower_mW = Global_f64InstVoltage_mv * Global_f64InstCurrent_mA; 
		Global_f64Energy_mJ += Global_f64InstPower_mW; 
		
		Local_u16Count = 0;
		TMR0_voidSetOVF(64);
	}

	Local_u16Count++;
}

void CALC_voidReset(void)
{
	Global_f64Energy_mJ = 0;
}

f64 CALC_f64GetInstVoltage_mV(void)	
{
	return Global_f64InstVoltage_mv;
}

f64 CALC_f64GetInstCurrent_mA(void)
{
	return Global_f64InstCurrent_mA;
}

f64 CALC_f64GetInstPower_mW(void)
{
	return Global_f64InstPower_mW;
}

f64 CALC_f64GetEnergy_mJ(void)
{
	return Global_f64Energy_mJ;
}

// reset
void ISR_INT0(void)
{
	Global_f64InstVoltage_mv = 0;
	
	Global_f64InstCurrent_mA = 0;
	
	Global_f64InstPower_mW = 0;
	
	Global_f64Energy_mJ = 0;
	
}

void ISR_INT1(void)
{
	Global_u8DisplayFlag += 1;
	
	if (Global_u8DisplayFlag > 3)
		Global_u8DisplayFlag = 0;
}

void DISP_voidDisplayOnLCD(f32 Copy_f32Result)
{
	s32 Displayed = 0 , Decimal = 1;
	u8 counter = 0;
	if(Copy_f32Result < 0)
	{
		LCD_voidDisplayChar('-');
		Copy_f32Result = -1 * Copy_f32Result;
	}
	Displayed = (u32) (Copy_f32Result);
	LCD_voidDisplayInt(Displayed);
	for(counter = 0 ; counter < DECIMAL ; counter++)
	{
		Decimal *= 10;
	}
	LCD_voidDisplayChar('.');
	Displayed = (u32) (Copy_f32Result * Decimal) % Decimal;
	LCD_voidDisplayInt(Displayed);
}