/*
 * ADC.c
 *
 *  Created on: Aug 22, 2023
 *      Author: Mostafa Sayed
 */

#include "ADC.h"

void ADC_voidInit(u8 copy_u8Prescaler)
{

	/*	Select Voltage Reference								*/

	#if	(ADC_REF_VOLT == ADC_AVCC)
		
		SET_BIT(ADMUX, REFS0);
		CLR_BIT(ADMUX, REFS1);
	
	#elif (ADC_REF_VOLT == ADC_AREF)
		
		CLR_BIT(ADMUX, REFS0);
		CLR_BIT(ADMUX, REFS1);
	
	#elif (ADC_REF_VOLT == ADC_2.56_V)
		
		SET_BIT(ADMUX, REFS0);
		SET_BIT(ADMUX, REFS1);
	
	#endif

	/* Select Adjustment 										*/
	#if (ADC_ADJUST == ADC_RIGHT_ADJUST)
		
		CLR_BIT(ADMUX, ADLAR);
		
	#elif (ADC_ADJUST == ADC_LEFT_ADJUST)
		
		SET_BIT(ADMUX, ADLAR);
		
	#endif

	/**/
	// Enable Triggering MODE
	#if (ADC_TRIGGER == AUTOTRIGGED_OFF)
	
		CLR_BIT(ADCSRA, ADATE);
		
	#else
		SET_BIT(ADCSRA, ADATE);
		// Select Triggering Source
		#if (TRIGGER_SOURCE == FREE_RUNNING)
		
			CLR_BIT(SFIOR, ADTS0);
			CLR_BIT(SFIOR, ADTS1);
			CLR_BIT(SFIOR, ADTS2);
			
		#elif (TRIGGER_SOURCE == ANALOG_COMPARATOR)
		
		    SET_BIT(SFIOR, ADTS0);
			CLR_BIT(SFIOR, ADTS1);
			CLR_BIT(SFIOR, ADTS2);
			
		#elif (TRIGGER_SOURCE == EXT_INT_0)
		
			CLR_BIT(SFIOR, ADTS0);
			SET_BIT(SFIOR, ADTS1);
			CLR_BIT(SFIOR, ADTS2);
			
		#elif (TRIGGER_SOURCE == TIMER0_COMP_MATCH)
		
			SET_BIT(SFIOR, ADTS0);
			SET_BIT(SFIOR, ADTS1);
			CLR_BIT(SFIOR, ADTS2);
			
		#elif (TRIGGER_SOURCE == TIMER0_OVF)
		
			CLR_BIT(SFIOR, ADTS0);
			CLR_BIT(SFIOR, ADTS1);
			SET_BIT(SFIOR, ADTS2);
			
		#elif (TRIGGER_SOURCE == TIMER_COMP_MATCH)
		
			SET_BIT(SFIOR, ADTS0);
			CLR_BIT(SFIOR, ADTS1);
			SET_BIT(SFIOR, ADTS2);
			
		#elif (TRIGGER_SOURCE == TIMER1_OVF)
		
			CLR_BIT(SFIOR, ADTS0);
			SET_BIT(SFIOR, ADTS1);
			SET_BIT(SFIOR, ADTS2);
			
		#elif (TRIGGER_SOURCE == TIMER1_CAP_EVENT)
		
			SET_BIT(SFIOR, ADTS0);
			SET_BIT(SFIOR, ADTS1);
			SET_BIT(SFIOR, ADTS2);
			
		#endif
		
	#endif

	// enable ADC (must be at the end)	
	SET_BIT(ADCSRA, ADEN);
}

u16 ADC_u16GetResultSync(u8 copy_u8Channel)
{
	// TO DO: verify channel && ptr passed
	
	u16 copy_u16Result = 0;
	// select channel
	ADMUX &= ADC_ADMUX_CHANNEL_MASK;
	ADMUX |= copy_u8Channel;
	
	// start conversion
	ADC_voidStartConversion();
	
	// polling until conversion is done OR ADC times out
	u32 local_u32TimeOutCounter = 0;
	
	while ((GET_BIT(ADCSRA, ADIF) == 0) && (local_u32TimeOutCounter < ADC_TIME_OUT_LIMIT))
		local_u32TimeOutCounter++;
	
	// return error code if ADC timed out
	if (local_u32TimeOutCounter == ADC_TIME_OUT_LIMIT)
		return 0; // will edit this later
	
	//_delay_ms(10);
	
	// clear interrupt flag
	ADC_voidClearADCInterruptFlag();
	
	#if (ADC_ADJUST == ADC_RIGHT_ADJUST)
		
		copy_u16Result = ((u16)ADCL | (u16)(ADCH << 8));

	#elif (ADC_ADJUST == ADC_LEFT_ADJUST)
		
		copy_u16Result = ADCH;
		
	#endif
	
	return copy_u16Result;
}

void ADC_voidStartConversion(void)
{
	SET_BIT(ADCSRA, ADC_ADCSRA_ADSC);
}

void ADC_voidDisable(void)
{
	/*	Turn off ADC Module	(Turn off after use to save power)	*/
	CLR_BIT(ADCSRA, ADEN);
}

void ADC_voidEnable(void)
{
	SET_BIT(ADCSRA, ADEN);
}

void ADC_voidSetAutoTriggerSource(u8 copy_u8AutoTriggerSource)
{
	#if (TRIGGER_SOURCE == FREE_RUNNING)
		
		CLR_BIT(SFIOR, ADTS0);
		CLR_BIT(SFIOR, ADTS1);
		CLR_BIT(SFIOR, ADTS2);
		
	#elif (TRIGGER_SOURCE == ANALOG_COMPARATOR)
		
		SET_BIT(SFIOR,ADTS0);
		CLR_BIT(SFIOR,ADTS1);
		CLR_BIT(SFIOR,ADTS2);
		
	#elif (TRIGGER_SOURCE == EXT_INT_0)
		
		CLR_BIT(SFIOR,ADTS0);
		SET_BIT(SFIOR,ADTS1);
		CLR_BIT(SFIOR,ADTS2);
		
	#elif (TRIGGER_SOURCE == TIMER0_COMP_MATCH)
		
		SET_BIT(SFIOR,ADTS0);
		SET_BIT(SFIOR,ADTS1);
		CLR_BIT(SFIOR,ADTS2);
		
	#elif (TRIGGER_SOURCE == TIMER0_OVF)
		
		CLR_BIT(SFIOR,ADTS0);
		CLR_BIT(SFIOR,ADTS1);
		SET_BIT(SFIOR,ADTS2);
		
	#elif (TRIGGER_SOURCE == TIMER_COMP_MATCH)
		
		SET_BIT(SFIOR,ADTS0);
		CLR_BIT(SFIOR,ADTS1);
		SET_BIT(SFIOR,ADTS2);
		
	#elif (TRIGGER_SOURCE == TIMER1_OVF)
		
		CLR_BIT(SFIOR,ADTS0);
		SET_BIT(SFIOR,ADTS1);
		SET_BIT(SFIOR,ADTS2);
		
	#elif (TRIGGER_SOURCE == TIMER1_CAP_EVENT)
		
		SET_BIT(SFIOR,ADTS0);
		SET_BIT(SFIOR,ADTS1);
		SET_BIT(SFIOR,ADTS2);
		
	#endif
}

void ADC_voidSetPrescaler(u8 copy_u8Prescaler)
{
	
	ADCSRA &= ADC_PRESCALER_MASK;
	
	switch (copy_u8Prescaler)
	{
		case ADC_DIV_2  :	ADCSRA |= ADC_DIV_2;	break;
		case ADC_DIV_4  :	ADCSRA |= ADC_DIV_4;	break;
		case ADC_DIV_8  :	ADCSRA |= ADC_DIV_8;	break;
		case ADC_DIV_16 :	ADCSRA |= ADC_DIV_16;	break;
		case ADC_DIV_32 :	ADCSRA |= ADC_DIV_32;	break;
		case ADC_DIV_64 :	ADCSRA |= ADC_DIV_64;	break;
		case ADC_DIV_128:	ADCSRA |= ADC_DIV_128;	break;
	}		
}

void ADC_voidEnableADCInterrupt(void)
{
	SET_BIT(ADCSRA, ADIE);
}

void ADC_voidDisableADCInterrupt(void)
{
	CLR_BIT(ADCSRA, ADIE);
}

void ADC_voidEnableAutoTrigger(void)
{
	SET_BIT(ADCSRA, ADATE);
}

void ADC_voidDisableAutoTrigger(void)
{
	CLR_BIT(ADCSRA, ADATE);
}

void ADC_voidClearADCInterruptFlag(void)
{
	SET_BIT(ADCSRA, ADIF);
}

void ADC_voidStartConversion(void)
{
	SET_BIT(ADCSRA, ADSC);
}

