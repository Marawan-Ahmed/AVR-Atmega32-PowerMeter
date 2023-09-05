#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"
#include "VSEN.h"


void VSEN_voidInit(void)
{
	ADC_voidInit();
}

f32  VSEN_f32GetVoltageReading(void)
{
	u16 Local_u16DigitalValue = 0;
	f32 Local_f32AnalogValue = 0;
	f32 Local_f32InputValue = 0;
	
	/**Get Sensor Reading*/
	Local_u16DigitalValue = ADC_u16GetResultSync(VSEN_ADC_CHANNEL);
	
	/**Convert it from V to mV*/
	Local_f32AnalogValue = ((Local_u16DigitalValue * 5) / 1024.0);
	
	/**Calculate Vin in mV*/
	// Vin = Vout * ((R1 + R2) / (R2))
	Local_f32InputValue = Local_f32AnalogValue * (((VSEN_R1) / (VSEN_R2)) + 1) ;

	/**Return Vin in mV*/
	return Local_f32InputValue;
}