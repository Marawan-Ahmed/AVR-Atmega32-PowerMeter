#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

void DIO_voidSetPinDirection(u8 copy_u8PortName, u8 copy_u8PinNum, u8 copy_u8PinDir);
void DIO_voidSetPinValue(u8 copy_u8PortName, u8 copy_u8PinNum, u8 copy_u8PinVal);
u8 DIO_u8GetPinValue(u8 copy_u8PortName, u8 copy_u8PinNum);
void DIO_voidTogglePin(u8 copy_u8PortName, u8 copy_u8PinNum);
void DIO_voidConfigurePinPullUpRes(u8 copy_u8PortName, u8 copy_u8PinNum, u8 copy_u8PinPullUpStatus);

void DIO_voidSetPortValue(u8 copy_u8PortName, u8 copy_u8PortVal);
void DIO_voidSetPortDirection(u8 copy_u8PortName, u8 copy_u8PortDir);
u8 DIO_u8GetPortValue(u8 copy_u8PortName);
void DIO_voidTogglePort(u8 copy_u8PortName);
void DIO_voidConfigurePortPullUpRes(u8 copy_u8PortName, u8 copy_u8PortPullUpStatus);

#endif
