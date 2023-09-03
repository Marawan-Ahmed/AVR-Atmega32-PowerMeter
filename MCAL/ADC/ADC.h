/*
 * ADC.h
 *
 *  Created on: Aug 22, 2023
 *      Author: Mostafa Sayed
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#include "../../LIB/BIT_Math.h"
#include "../../LIB/STD_Types.h"

/************************** Registers ************************************/

#define ADMUX					(*(volatile u8*)(0x07 + 0x20))
#define REFS1					7
#define REFS0					6
#define ADLAR					5
#define MUX4					4
#define MUX3					3
#define MUX2					2
#define MUX1					1
#define MUX0					0

#define ADCSRA					(*(volatile u8*)(0x06 + 0x20))
#define ADEN					7
#define ADSC					6
#define ADATE					5
#define ADIF					4
#define ADIE					3
#define ADPS2					2
#define ADPS1					1
#define ADPS0					0

#define ADC						(*(volatile u16*)(0x04 + 0x20))

#define SFIOR					(*(volatile u8*)(0x30 + 0x20))
#define ADTS2					7
#define ADTS1					6
#define ADTS0					5

/************************** Macros *********************************/

#define ADC_CHANNAL_0			0
#define ADC_CHANNAL_1			1
#define ADC_CHANNAL_2			2
#define ADC_CHANNAL_3			3
#define ADC_CHANNAL_4			4
#define ADC_CHANNAL_5			5
#define ADC_CHANNAL_6			6
#define ADC_CHANNAL_7			7

#define ADC_DIV_2				1
#define ADC_DIV_4				2
#define ADC_DIV_8				3
#define ADC_DIV_16				4
#define ADC_DIV_32				5
#define ADC_DIV_64				6
#define ADC_DIV_128				7

// Reference Voltage Selection
#define	ADC_AVCC				0				// Internal Vref is turned off
#define	ADC_AREF				1				// Use External Capacitor at AREF
#define	ADC_2_56_V				2				// internal Vref with External Capacitor at AREF

#define ADC_REF_VOLT			ADC_AVCC


//////////////////////////////////

// Adjustment Selection
// Specify Result arrangement

#define ADC_RIGHT_ADJUST 		0                 // Start from ADCL to ADCH
#define ADC_LEFT_ADJUST  		1                 // Start from ADCH to ADCL

#define ADC_ADJUST 		 		ADC_RIGHT_ADJUST

/////////////////////////////////

// Channel Selection refer to table 84 in datasheet


// Auto Triggering Mode ON or OFF
#define AUTOTRIGGED_OFF  		0
#define AUTOTRIGGED_ON    		1

#define ADC_TRIGGER   	   		AUTOTRIGGED_ON

// Auto Triggering Source (Require Enabling Auto Trigger Mode)
#define FREE_RUNNING          	 0           // Conversion is Done Automatically one after another
#define ANALOG_COMPARATOR    	 1           // using Pins AIN0 +ve terminal , AIN1 -ve terminal require separate driver
#define EXT_INT_0            	 2           // External interrupt zero enable triggering
#define TIMER0_COMP_MATCH     	 3           // Trigger on Timer 0 Compare match
#define TIMER0_OVF            	 4           // Trigger on Timer 0 Overflow
#define TIMER_COMP_MATCH      	 5           // Trigger on Timer Compare match
#define TIMER1_OVF            	 6           // Trigger on Timer 1 Overflow
#define TIMER1_CAP_EVENT      	 7           // Trigger on Timer 1 Capture Event

#define  ADC_TRIGGER_SOURCE 	TIMER0_OVF
// Data Register is ADC Register
/* ADC_AVCC		ADC_AREF	ADC_2.56_V	*/

/* 			APIs		*/
void ADC_voidInit			(u8 Copy_u8Prescaler);
u16  ADC_u8GetDigital	    (u8 Copy_u8Channel);
void ADC_voidDisable		(void);



#endif /* MCAL_ADC_ADC_H_ */
