#include "../LIB/BIT_Math.h"
#include "../LIB/STD_Types.h"

#include <math.h>
#include <avr/interrupt.h>

#include "calculations.h"


u32	Global_u32SampleCount; //used for True RMS

f64	Global_f64InstVoltage_mv;
//f64	Global_f64SumVoltage_mv; //used for True RMS
//f64	Global_f64RMSVoltage_mv; //used for True RMS

f64	Global_f64InstCurrent_mA;
//f64	Global_f64SumCurrent_mA; //used for True RMS
//f64	Global_f64RMSCurrent_mA; //used for True RMS

f64	Global_f64InstPower_mW;
//f64	Global_f64SumPower_mA; //used for True RMS
//f64	Global_f64RMSPower_mA; //used for True RMS

f64	Global_f64Energy_mJ;

void CALC_voidInit(void){
	//Initialize Voltage and Current readings
	ACS712_voidInit();
	VSEN_voidInit();
	
	//setup the timer interrupt to run every multiple of 1mS
	TIM0_voidInit();
	TIM0_voidTimerStart(TIM0_PRE_DIV_8);

	sei();
	TIM0_voidOVFINTControl(TIM0_INT_ENABLE);
	INT_voidOVFCallback(CALC_voidPeriodicFunc);
	TIM0_voidSetPreValue(232); ////////////////////?????????????????????????????????
}

void CALC_voidPeriodicFunc(void){
	static u16 Local_u16Count =0;
	//enter this condition every SMAPLING_PERIOD_mS 
	if(Local_u16Count == 4 * SMAPLING_PERIOD_mS){ ////////////////////?????????????????????????????????
		//read inst volt
		Global_f64InstVoltage_mv = VSEN_f32GetVoltageReading();
		//read inst current
		Global_f64InstCurrent_mA = ACS712_f32GetCurrentReading();
/*
		//Claculating RMS Values
		Global_f64SumVoltage_mv += Global_f64InstVoltage_mv * Global_f64InstVoltage_mv; //Calculate Voltage Sum Square across SMAPLING_COUNT samples
		Global_f64SumCurrent_mA += Global_f64InstCurrent_mA * Global_f64InstCurrent_mA; //Calculate Current Sum Square across SMAPLING_COUNT samples
		Global_u32SampleCount++;

		if (Global_u32SampleCount == SMAPLING_COUNT){
			Global_f64RMSVoltage_mv = sqrt(Global_f64SumVoltage_mv)/Global_u32SampleCount; 	//Calculate Voltage Root Mean Square across SMAPLING_COUNT samples
			Global_f64RMSCurrent_mA = sqrt(Global_f64SumCurrent_mA)/Global_u32SampleCount; 	//Calculate Current Root Mean Square across SMAPLING_COUNT samples
			Global_u32SampleCount = 0; 													   	//Reset Sampling
			LED_voidToggleLEDSingle(DIO_PORTD, DIO_PIN7);
		}	
*/		
		Global_f64InstPower_mW = Global_f64InstVoltage_mv * Global_f64InstCurrent_mA / 1000; //Power(mJ) = (Volt(mV) * Current(mA))/1000
//		Global_f64RMSPower_mA = Global_f64SumVoltage_mv * Global_f64RMSCurrent_mA / 1000;
		Global_f64Energy_mJ += (Global_f64RMSPower_mA * SMAPLING_PERIOD_mS)/1000; // energy = power * time , since this is calculated every ms time = 1/1000
		
		Local_u16Count = 0;
		TIM0_voidSetPreValue(232);
	}

	Local_u16Count++;
}

void CALC_voidReset(void){
	Global_f64Energy_mJ = 0;
}

f64 CALC_f64GetInstVoltage_mV(void)	{
	return Global_f64RMSVoltage_mv;
}

f64 CALC_f64GetInstCurrent_mA(void){
	return Global_f64RMSCurrent_mA;
}

f64 CALC_f64GetInstPower_mW(void){
	return Global_f64InstPower_mW;
}

f64 CALC_f64GetEnergy_mJ(void){
	return Global_f64Energy_mJ;
}

/*
f64 CALC_f64GetRMSVoltage_mV(void)	{
	return Global_f64RMSVoltage_mv;
}

f64 CALC_f64GetRMSCurrent_mA(void){
	return Global_f64RMSCurrent_mA;
}

f64 CALC_f64GetRMSPower_mW(void){
	return Global_f64RMSPower_mA;
}

*/


