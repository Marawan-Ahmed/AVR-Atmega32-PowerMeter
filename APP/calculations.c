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
	
	TMR0_voidInit();
	TMR_voidCallBack(CALC_voidPeriodicFunc, TMR0_OVF_VECTOR_ID);
	TMR0_voidSetOVF(64);
}

void CALC_voidPeriodicFunc(void)
{
	static u16 Local_u16Count =0;
	//enter this condition every SMAPLING_PERIOD_mS 
	if(Local_u16Count == 3907){ ////////////////////?????????????????????????????????
		LED_voidToggleLEDSingle(DIO_PORTD, DIO_PIN7);
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