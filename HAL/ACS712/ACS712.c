#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"
#include "../../MCAL/ADC/ADC.h"
#include "ACS712.h"

void ACS712_voidInit(void)
{
	ADC_voidInit(ASC712_ADC_CHANNEL);
}

u16 ACS712_u16GetCurrentReading(void)
{
	/**Get Sensor Reading*/
	
	
	/**Convert it from V to mV*/
	
	
	/**Convert it from mV to mA*/
	
	
	/**Return in mA*/
}
