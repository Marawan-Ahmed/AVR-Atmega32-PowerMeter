#include "../../LIB/Bit_Math.h"
#include "../../LIB/STD_Types.h"
#include "DIO_Registers.h"
#include "DIO_Private.h"
#include "DIO_CFG.h"
#include "DIO_Interface.h"

void DIO_voidSetPinDirection(u8 copy_u8PortName, u8 copy_u8PinNum, u8 copy_u8PinDir)
{
	if ((copy_u8PortName < DIO_PORTA) || (copy_u8PortName > DIO_PORTD))
		return; // DIO_PORT_ARG_UNDEFINED
	
	if ((copy_u8PinNum < DIO_PIN0) || (copy_u8PinNum > DIO_PIN7))
		return; // DIO_PIN_NO_ARG_OUT_OF_BOUNDS
	
	if ((copy_u8PinDir != DIO_PIN_OUTPUT) && (copy_u8PinDir != DIO_PIN_INPUT))
		return; // DIO_PIN_DIR_ARG_OUT_OF_BOUNDS
	
	switch (copy_u8PortName)
	{
		case DIO_PORTA: copy_u8PinDir == DIO_PIN_OUTPUT ? 
						SET_BIT(DDRA, copy_u8PinNum) : CLR_BIT(DDRA, copy_u8PinNum); 
						break;
		case DIO_PORTB: copy_u8PinDir == DIO_PIN_OUTPUT ? 
						SET_BIT(DDRB, copy_u8PinNum) : CLR_BIT(DDRB, copy_u8PinNum); 
						break;
		case DIO_PORTC: copy_u8PinDir == DIO_PIN_OUTPUT ? 
						SET_BIT(DDRC, copy_u8PinNum) : CLR_BIT(DDRC, copy_u8PinNum); 
						break;
		case DIO_PORTD: copy_u8PinDir == DIO_PIN_OUTPUT ? 
						SET_BIT(DDRD, copy_u8PinNum) : CLR_BIT(DDRD, copy_u8PinNum); 
						break;
	}
	
	return; // DIO_OK
}

void DIO_voidSetPinValue(u8 copy_u8PortName, u8 copy_u8PinNum, u8 copy_u8PinVal)
{
	if ((copy_u8PortName < DIO_PORTA) || (copy_u8PortName > DIO_PORTD))
		return; // DIO_PORT_ARG_UNDEFINED
	
	if ((copy_u8PinNum < DIO_PIN0) || (copy_u8PinNum > DIO_PIN7))
		return; // DIO_PIN_NO_ARG_OUT_OF_BOUNDS
	
	if ((copy_u8PinVal != DIO_PIN_HIGH) && (copy_u8PinVal != DIO_PIN_LOW))
		return; // DIO_PIN_VAL_ARG_OUT_OF_BOUNDS
	
	switch (copy_u8PortName)
	{
		case DIO_PORTA: copy_u8PinVal == DIO_PIN_HIGH ? 
						SET_BIT(PORTA, copy_u8PinNum) : CLR_BIT(PORTA, copy_u8PinNum); 
						break;
		case DIO_PORTB: copy_u8PinVal == DIO_PIN_HIGH ?  
						SET_BIT(PORTB, copy_u8PinNum) : CLR_BIT(PORTB, copy_u8PinNum); 
						break;
		case DIO_PORTC: copy_u8PinVal == DIO_PIN_HIGH ? 
						SET_BIT(PORTC, copy_u8PinNum) : CLR_BIT(PORTC, copy_u8PinNum); 
						break;
		case DIO_PORTD: copy_u8PinVal == DIO_PIN_HIGH ? 
						SET_BIT(PORTD, copy_u8PinNum) : CLR_BIT(PORTD, copy_u8PinNum); 
						break;
	}
	
	return; // DIO_OK
}

u8 DIO_u8GetPinValue(u8 copy_u8PortName, u8 copy_u8PinNum)
{
	if ((copy_u8PortName < DIO_PORTA) || (copy_u8PortName > DIO_PORTD))
		return DIO_PORT_ARG_UNDEFINED; // DIO_PORT_ARG_UNDEFINED
	
	if ((copy_u8PinNum < DIO_PIN0) || (copy_u8PinNum > DIO_PIN7))
		return DIO_PIN_NO_ARG_OUT_OF_BOUNDS; // DIO_PIN_NO_ARG_OUT_OF_BOUNDS
	
	switch (copy_u8PortName)
	{
		case DIO_PORTA: return (GET_BIT(PINA, copy_u8PinNum));
		case DIO_PORTB: return (GET_BIT(PINB, copy_u8PinNum));
		case DIO_PORTC: return (GET_BIT(PINC, copy_u8PinNum));
		case DIO_PORTD: return (GET_BIT(PIND, copy_u8PinNum));
	}
}

void DIO_voidTogglePin(u8 copy_u8PortName, u8 copy_u8PinNum)
{
	if ((copy_u8PortName < DIO_PORTA) || (copy_u8PortName > DIO_PORTD))
		return; // DIO_PORT_ARG_UNDEFINED
	
	if ((copy_u8PinNum < DIO_PIN0) || (copy_u8PinNum > DIO_PIN7))
		return; // DIO_PIN_NO_ARG_OUT_OF_BOUNDS
	
	switch (copy_u8PortName)
	{
		case DIO_PORTA: TOG_BIT(PORTA, copy_u8PinNum); break;
		case DIO_PORTB: TOG_BIT(PORTB, copy_u8PinNum); break;
		case DIO_PORTC: TOG_BIT(PORTC, copy_u8PinNum); break;
		case DIO_PORTD: TOG_BIT(PORTD, copy_u8PinNum); break;
	}
	
	return; // DIO_OK
}

void DIO_voidSetPortDirection(u8 copy_u8PortName, u8 copy_u8PortDir)
{
	if ((copy_u8PortName < DIO_PORTA) || (copy_u8PortName > DIO_PORTD))
		return; // DIO_PORT_ARG_UNDEFINED
	
	if ((copy_u8PortDir < DIO_PORT_INPUT) || (copy_u8PortDir > DIO_PORT_OUTPUT))
		return; // DIO_PORT_DIR_ARG_OUT_OF_BOUNDS
	
	switch (copy_u8PortName)
	{
		case DIO_PORTA: SET_PORT_TO_VAL(DDRA, DIO_PORT_OUTPUT); break;
		case DIO_PORTB: SET_PORT_TO_VAL(DDRB, DIO_PORT_OUTPUT); break;
		case DIO_PORTC: SET_PORT_TO_VAL(DDRC, DIO_PORT_OUTPUT); break;
		case DIO_PORTD: SET_PORT_TO_VAL(DDRD, DIO_PORT_OUTPUT); break;
	}
	
	return; // DIO_OK
}

void DIO_voidSetPortValue(u8 copy_u8PortName, u8 copy_u8PortVal)
{
	if ((copy_u8PortName < DIO_PORTA) || (copy_u8PortName > DIO_PORTD))
		return; // DIO_PORT_ARG_UNDEFINED
	
	if ((copy_u8PortVal < DIO_PORT_LOW) || (copy_u8PortVal > DIO_PORT_HIGH))
		return; // DIO_PORT_VAL_ARG_OUT_OF_BOUNDS
	
	switch (copy_u8PortName)
	{
		case DIO_PORTA: SET_PORT_TO_VAL(PORTA, copy_u8PortVal); break;
		case DIO_PORTB: SET_PORT_TO_VAL(PORTB, copy_u8PortVal); break;
		case DIO_PORTC: SET_PORT_TO_VAL(PORTC, copy_u8PortVal); break;
		case DIO_PORTD: SET_PORT_TO_VAL(PORTD, copy_u8PortVal); break;
	}
	
	return; // DIO_OK
}

u8 DIO_u8GetPortValue(u8 copy_u8PortName)
{
	if ((copy_u8PortName < DIO_PORTA) || (copy_u8PortName > DIO_PORTD))
		return DIO_PORT_ARG_UNDEFINED; // DIO_PORT_ARG_UNDEFINED
	
	switch (copy_u8PortName)
	{
		case DIO_PORTA: return (PINA);
		case DIO_PORTB: return (PINB);
		case DIO_PORTC: return (PINC);
		case DIO_PORTD: return (PIND);
	}
}

void DIO_voidTogglePort(u8 copy_u8PortName)
{
	if ((copy_u8PortName < DIO_PORTA) || (copy_u8PortName > DIO_PORTD))
		return; // DIO_PORT_ARG_UNDEFINED
	
	switch (copy_u8PortName)
	{
		case DIO_PORTA: TOG_PORT(PORTA); break;
		case DIO_PORTB: TOG_PORT(PORTB); break;
		case DIO_PORTC: TOG_PORT(PORTC); break;
		case DIO_PORTD: TOG_PORT(PORTD); break;
	}
	
	return; // DIO_OK
}

 
void DIO_voidConfigurePinPullUpRes(u8 copy_u8PortName, u8 copy_u8PinNum, u8 copy_u8PinPullUpStatus)
{
	if ((copy_u8PortName < DIO_PORTA) || (copy_u8PortName > DIO_PORTD))
		return; // DIO_PORT_ARG_UNDEFINED
	
	if ((copy_u8PinNum < DIO_PIN0) || (copy_u8PinNum > DIO_PIN7))
		return; // DIO_PIN_NO_ARG_OUT_OF_BOUNDS
	
	if ((copy_u8PinPullUpStatus != DIO_PIN_PULLUP_ENABLED) && (copy_u8PinPullUpStatus != DIO_PIN_PULLUP_DISABLED))
		return; // DIO_PIN_PU_ARG_OUT_OF_BOUNDS
	
	switch (copy_u8PinPullUpStatus)
	{
		case DIO_PIN_PULLUP_ENABLED:
				DIO_voidSetPinDirection(copy_u8PortName, copy_u8PinNum, DIO_PIN_INPUT);
				DIO_voidSetPinValue(copy_u8PortName, copy_u8PinNum, DIO_PIN_HIGH);
				break;
		case DIO_PIN_PULLUP_DISABLED:
				DIO_voidSetPinValue(copy_u8PortName, copy_u8PinNum, DIO_PIN_LOW);
				break;
	}
	
	return; // DIO_OK
} 
 
void DIO_voidConfigurePortPullUpRes(u8 copy_u8PortName, u8 copy_u8PortPullUpStatus)
{
	if ((copy_u8PortName < DIO_PORTA) || (copy_u8PortName > DIO_PORTD))
		return; // DIO_PORT_ARG_UNDEFINED
	
	if ((copy_u8PortPullUpStatus != DIO_PORT_PULLUP_ENABLED) && (copy_u8PortPullUpStatus != DIO_PORT_PULLUP_DISABLED))
		return; // DIO_PIN_PU_ARG_OUT_OF_BOUNDS
	
	switch (copy_u8PortPullUpStatus)
	{
		case DIO_PORT_PULLUP_ENABLED:
				DIO_voidSetPortDirection(copy_u8PortName, DIO_PORT_INPUT);
				DIO_voidSetPortValue(copy_u8PortName, DIO_PORT_HIGH);
				break;
		case DIO_PORT_PULLUP_DISABLED:
				DIO_voidSetPortValue(copy_u8PortName, DIO_PORT_LOW);
				break;
	}
	
	return; // DIO_OK
} 

void DIO_void_DisableAllPullUpResistance(void)
{
	SET_BIT(SFIOR, 2);
}
