#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"
#include "../../MCAL/ADC/ADC.h"
#include "ACS712.h"

void ACS712_voidInit(void)
{
	ADC_voidInit(ACS712_ADC_PRESCALER);
}

u16 ACS712_u16GetCurrentReading(void)
{
	u16 Local_u16DigitalValue = 0;
	u16 Local_u16AnalogValue = 0;
	u16 Local_u16CurrentReading = 0;
	/**Get Sensor Reading*/
	Local_u16DigitalValue = ADC_u16GetResultSync(ACS712_ADC_CHANNEL);
	
	/**Convert it from V to mV*/
	Local_u16AnalogValue = ((Local_u16DigitalValue * 5000UL) / 1024);
	
	/**Convert it from mV to mA*/
	// I = (V - 2.5) / sensitivity;
	Local_u16CurrentReading = (Local_u16AnalogValue - 2500) / ACS712_SENSITIVITY;
	
	/**Return in mA*/
	return Local_u16CurrentReading;
}
