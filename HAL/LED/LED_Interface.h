#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

void LED_voidLEDSingleInit(u8 copy_u8PortName, u8 copy_u8PinNum);
void LED_voidLEDArrayInit(u8 copy_u8PortName);

void LED_voidToggleLEDSingle(u8 copy_u8PortName, u8 copy_u8PinNum);
void LED_voidToggleLEDArray(u8 copy_u8PortName);

void LED_voidTurnSingleLEDOnOff(u8 copy_u8PortName, u8 copy_u8PinNum, u8 copy_u8PinVal);
void LED_voidTurnArrayLEDOnOff(u8 copy_u8PortName, u8 copy_u8PortVal);

#endif