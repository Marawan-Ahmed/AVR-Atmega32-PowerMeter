#include "../../MCAL/DIO/DIO_CFG.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LED_Private.h"
#include "LED_CFG.h"
#include "LED_Interface.h"

void LED_voidLEDSingleInit(u8 copy_u8PortName, u8 copy_u8PinNum)
{
	DIO_voidSetPinDirection(copy_u8PortName, copy_u8PinNum, DIO_PIN_OUTPUT);
	DIO_voidSetPinValue(copy_u8PortName, copy_u8PinNum, DIO_PIN_LOW);
}
void LED_voidLEDArrayInit(u8 copy_u8PortName)
{
	DIO_voidSetPortDirection(copy_u8PortName, DIO_PORT_OUTPUT);
	DIO_voidSetPortValue(copy_u8PortName, DIO_PORT_LOW);
}

void LED_voidToggleLEDSingle(u8 copy_u8PortName, u8 copy_u8PinNum)
{
	DIO_voidTogglePin(copy_u8PortName, copy_u8PinNum);
}

void LED_voidToggleLEDArray(u8 copy_u8PortName)
{
	DIO_voidTogglePort(copy_u8PortName);
}

void LED_voidTurnSingleLEDOnOff(u8 copy_u8PortName, u8 copy_u8PinNum, u8 copy_u8PinVal)
{
	DIO_voidSetPinValue(copy_u8PortName, copy_u8PinNum, copy_u8PinVal);
}

void LED_voidTurnArrayLEDOnOff(u8 copy_u8PortName, u8 copy_u8PortVal)
{
	DIO_voidSetPortValue(copy_u8PortName, copy_u8PortVal);
}