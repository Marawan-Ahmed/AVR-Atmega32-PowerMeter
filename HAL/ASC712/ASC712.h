#pragma once
#ifndef ASC712_H_
#define ASC712_H_

/*******************************CONFIG******************************/

#define ASC712_ADC_CHANNEL		ADC_CHANNAL_0
#define ASC712_ADC_PRESCALER	ADC_DIV_64

/****************************INTERFACE******************************/

void ASC712_voidInit(void);
u16 ASC712_u16GetCurrentReadingDC(void);
u16 ASC712_u16GetCurrentReadingAC(void);

#endif