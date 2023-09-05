#pragma once
#ifndef VSEN_H_
#define VSEN_H_

/******************************CONFIG*******************************/

#define VSEN_ADC_CHANNEL		ADC_CHANNAL_1
#define VSEN_ADC_PRESCALER		ADC_DIV_64

/*
	Voltage Sensing using voltage divider:
		Vin = Vout * ((R1 + R2) / (R2))
		where,
		R1 = 30kohm
		R2 = 7.5kohm
*/

#define VSEN_R1		30000UL
#define VSEN_R2		 7500UL

/****************************INTERFACE******************************/

void VSEN_voidInit(void);
u16  VSEN_u16GetVoltageReading(void);

#endif