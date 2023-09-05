#pragma once
#ifndef ACS712_H_
#define ACS712_H_

/******************************CONFIG*******************************/

#define ACS712_ADC_CHANNEL		ADC_CHANNAL_0
#define ACS712_ADC_PRESCALER	ADC_DIV_64

/*
	ACS712 Current Sensor comes in three editions:
		ACS712-05B => Sensor Sensitivity = 185 mv/A
		ACS712-20A => Sensor Sensitivity = 100 mv/A
		ACS712-30A => Sensor Sensitivity =  66 mv/A
*/

#define ACS712_SENSITIVITY		66UL

/****************************INTERFACE******************************/

void ACS712_voidInit(void);
u16 ACS712_u16GetCurrentReading(void);

#endif