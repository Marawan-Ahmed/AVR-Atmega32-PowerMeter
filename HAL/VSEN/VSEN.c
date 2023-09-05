#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"
#include "../../MCAL/ADC/ADC.h"
#include "VSEN.h"


void VSEN_voidInit(void)
{
	ADC_voidInit(VSEN_ADC_PRESCALER);
}

u16  VSEN_u16GetVoltageReading(void)
{
	u16 Local_u16DigitalValue = 0;
	u16 Local_u16AnalogValue = 0;
	u16 Local_u16InputValue = 0;
	
	/**Get Sensor Reading*/
	Local_u16DigitalValue = ADC_u16GetResultSync(VSEN_ADC_CHANNEL);
	
	/**Convert it from V to mV*/
	Local_u16AnalogValue = ((Local_u16DigitalValue * 5000UL) / 1024UL);
	
	/**Calculate Vin in mV*/
	// Vin = Vout * ((R1 + R2) / (R2))
	Local_u16InputValue = Local_u16AnalogValue * (((VSEN_R1) / (VSEN_R2)) + 1) ;

	/**Return Vin in mV*/
	return Local_u16InputValue;
}