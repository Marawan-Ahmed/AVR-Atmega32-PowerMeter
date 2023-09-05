#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"
#include "ACS712.h"

void ACS712_voidInit(void)
{
	ADC_voidInit();
}

f32 ACS712_f32GetCurrentReading(void)
{
	u16 Local_u16DigitalValue = 0;
	f32 Local_f32AnalogValue = 0;
	f32 Local_f32InputValue = 0;
	
	/**Get Sensor Reading*/
	Local_u16DigitalValue = ADC_u16GetResultSync(ACS712_ADC_CHANNEL);
	
	/**Convert it from V to mV*/
	Local_f32AnalogValue = ((Local_u16DigitalValue * 5) / 1024.0);
	
	/**Convert it from mV to mA*/
	// I = (V - 2.5) / sensitivity;
	Local_f32InputValue = ((Local_f32AnalogValue - 2.5) / ACS712_SENSITIVITY);
	
	/**Return in mA*/
	return Local_f32InputValue;
}
