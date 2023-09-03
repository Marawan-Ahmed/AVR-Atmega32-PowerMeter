/*
 * ADC.c
 *
 *  Created on: Aug 22, 2023
 *      Author: Mostafa Sayed
 */

#include "ADC.h"

void ADC_voidInit	(u8 Copy_u8Prescaler)
{

	/*	Select Voltage Reference								*/

	#if		ADC_REF_VOLT == ADC_AVCC
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
	#elif	ADC_REF_VOLT == ADC_AREF
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
	#elif	ADC_REF_VOLT == ADC_2.56_V
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
	#endif

	/* Select Adjustment 										*/
		#if ADC_ADJUST == ADC_RIGHT_ADJUST
			CLR_BIT(ADMUX,ADLAR);
		#elif ADC_ADJUST == ADC_LEFT_ADJUST
			SET_BIT(ADMUX,ADLAR);
		#endif

	/**/
	// Enable Triggering MODE
	#if ADC_TRIGGER == AUTOTRIGGED_OFF
		CLR_BIT(ADCSRA,ADATE);
	#else
		SET_BIT(ADCSRA,ADATE);
		// Select Triggering Source
		#if TRIGGER_SOURCE == FREE_RUNNING
			CLR_BIT(SFIOR,ADTS0);
			CLR_BIT(SFIOR,ADTS1);
			CLR_BIT(SFIOR,ADTS2);
		#elif TRIGGER_SOURCE == ANALOG_COMPARATOR
		    SET_BIT(SFIOR,ADTS0);
			CLR_BIT(SFIOR,ADTS1);
			CLR_BIT(SFIOR,ADTS2);
		#elif TRIGGER_SOURCE == EXT_INT_0
			CLR_BIT(SFIOR,ADTS0);
			SET_BIT(SFIOR,ADTS1);
			CLR_BIT(SFIOR,ADTS2);
		#elif TRIGGER_SOURCE == TIMER0_COMP_MATCH
			SET_BIT(SFIOR,ADTS0);
			SET_BIT(SFIOR,ADTS1);
			CLR_BIT(SFIOR,ADTS2);
		#elif TRIGGER_SOURCE == TIMER0_OVF
			CLR_BIT(SFIOR,ADTS0);
			CLR_BIT(SFIOR,ADTS1);
			SET_BIT(SFIOR,ADTS2);
		#elif TRIGGER_SOURCE == TIMER_COMP_MATCH
			SET_BIT(SFIOR,ADTS0);
			CLR_BIT(SFIOR,ADTS1);
			SET_BIT(SFIOR,ADTS2);
		#elif TRIGGER_SOURCE == TIMER1_OVF
			CLR_BIT(SFIOR,ADTS0);
			SET_BIT(SFIOR,ADTS1);
			SET_BIT(SFIOR,ADTS2);
		#elif TRIGGER_SOURCE == TIMER1_CAP_EVENT
			SET_BIT(SFIOR,ADTS0);
			SET_BIT(SFIOR,ADTS1);
			SET_BIT(SFIOR,ADTS2);
		#endif
	#endif

	/*	Select Conversion Speed									*/
		ADCSRA &= 0b11111000;
		ADCSRA |= Copy_u8Prescaler;

	/*	Turn on ADC Module	(Turn off after use to save power)	*/
	SET_BIT(ADCSRA,ADEN);

}
u16  ADC_u8GetDigital		(u8 Copy_u8Channel)
{
	u16 data = 0;
	/* Select Channel 	*/
	ADMUX &= 0b11100000;
	ADMUX |= Copy_u8Channel;
	/*	Start Conversion	*/
	if( AUTOTRIGGED_OFF == ADC_TRIGGER){
			// Start Conversion
			SET_BIT(ADCSRA,ADSC);
	   }

	/* Wait for Conversion */
	while(GET_BIT(ADCSRA,ADIF) == 0);
	SET_BIT(ADCSRA,ADIF);

	/* Load the Word */
	data = ADC;

	return data;
}
void ADC_voidDisable()
{
	/*	Turn off ADC Module	(Turn off after use to save power)	*/
	CLR_BIT(ADCSRA,ADEN);
}
