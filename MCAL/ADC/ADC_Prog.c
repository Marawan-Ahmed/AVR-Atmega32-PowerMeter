#include "../../LIB/STD_Types.h"
#include "../../LIB/Bit_Math.h"
#include "ADC_Register.h"
#include "ADC_Private.h"
#include "ADC_CFG.h"
#include "ADC_Interface.h"
#include <util/delay.h>

static u16 *ADC_u16ptrADCResult = NULL;
static ptrFunc ADC_funcPtr_ISR = NULL;

void ADC_voidInit(void)
{
	
	// set vref
	#if (ADC_REFV == ADC_REFV_SEL_AVCC)
	
		#define VREF  5000UL
		SET_BIT(ADMUX, ADC_ADMUX_REFS0);
		CLR_BIT(ADMUX, ADC_ADMUX_REFS1);
	
	#elif (ADC_REFV == ADC_REFV_SEL_2_56V)
	
		#define VREF  2560UL
		SET_BIT(ADMUX, ADC_ADMUX_REFS0);
		SET_BIT(ADMUX, ADC_ADMUX_REFS1);
	
	#elif (ADC_REFV == ADC_REFV_SEL_AREF)
	
		#define VREF  ADC_AREF_VALUE
		CLR_BIT(ADMUX, ADC_ADMUX_REFS0);
		CLR_BIT(ADMUX, ADC_ADMUX_REFS1);

	#endif 
	
	// register adjust
	#if (ADC_ADJUST_RESULT == ADC_LEFT_ADJUST)
		
		SET_BIT(ADMUX, ADC_ADMUX_ADLAR);
		
	#elif (ADC_ADJUST_RESULT == ADC_RIGHT_ADJUST)
		
		CLR_BIT(ADMUX, ADC_ADMUX_ADLAR);
		
	#endif
	
	// prescaler
	ADCSRA &= ADC_ADCSRA_PRESCALER_MASK;
	
	#if (ADC_PRESCALER == ADC_PRESCALER_2)
		
		ADCSRA |= ADC_PRESCALER_2;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_4)
		
		ADCSRA |= ADC_PRESCALER_4;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_8)
		
		ADCSRA |= ADC_PRESCALER_8;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_16)
		
		ADCSRA |= ADC_PRESCALER_16;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_32)
		
		ADCSRA |= ADC_PRESCALER_32;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_64)
		
		ADCSRA |= ADC_PRESCALER_64;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_128)
		
		ADCSRA |= ADC_PRESCALER_128;
		
	#endif
	
	// auto trigger source
	SET_BIT(ADCSRA, ADC_ADCSRA_ADATE);
	
	SFIOR &= ADC_SFIOR_MASK;
	
	#if (ADC_AUTO_TRIGGER_SOURCE == ADC_FREE_RUNNING)
		
		SFIOR |= ADC_FREE_RUNNING;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_ANALOG_COMPARATOR)
		
		SFIOR |= ADC_ANALOG_COMPARATOR;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_EXTI0)
		
		SFIOR |= ADC_EXTI0;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_TIM0_CTC_MATCH)
		
		SFIOR |= ADC_TIM0_CTC_MATCH;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_TIM0_OVF)
		
		SFIOR |= ADC_TIM0_OVF;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_TIM1_CTC_MATCH_B)
		
		SFIOR |= ADC_TIM1_CTC_MATCH_B;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_TIM1_OVF)
		
		SFIOR |= ADC_TIM1_OVF;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_TIM1_ICU)
		
		SFIOR |= ADC_TIM1_ICU;
		
	#endif
	
	// enable ADC (must be at the end)
	#if (ADC_STATUS == ADC_ENABLE)
	
	SET_BIT(ADCSRA, ADC_ADCSRA_ADEN);
	
	#elif (ADC_STATUS == ADC_DISABLE)
	
	CLR_BIT(ADCSRA, ADC_ADCSRA_ADEN);
	
	#endif
	
	// enable ADC interrupt (must be at the end)
	#if (ADC_INT_STATUS == ADC_INT_ENABLE)
		
		SET_BIT(ADCSRA, ADC_ADCSRA_ADEN);
		
	#endif
}

void ADC_voidSetAutoTriggerSource(u8 copy_u8AutoTriggerSource)
{
	#if (ADC_AUTO_TRIGGER_SOURCE == ADC_FREE_RUNNING)
		
		SFIOR |= ADC_FREE_RUNNING;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_ANALOG_COMPARATOR)
		
		SFIOR |= ADC_ANALOG_COMPARATOR;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_EXTI0)
		
		SFIOR |= ADC_EXTI0;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_TIM0_CTC_MATCH)
		
		SFIOR |= ADC_TIM0_CTC_MATCH;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_TIM0_OVF)
		
		SFIOR |= ADC_TIM0_OVF;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_TIM1_CTC_MATCH_B)
		
		SFIOR |= ADC_TIM1_CTC_MATCH_B;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_TIM1_OVF)
		
		SFIOR |= ADC_TIM1_OVF;
		
	#elif (ADC_AUTO_TRIGGER_SOURCE == ADC_TIM1_ICU)
		
		SFIOR |= ADC_TIM1_ICU;
		
	#endif
}

void ADC_voidSetPrescaler(u8 copy_u8Prescaler)
{
	
	ADCSRA &= ADC_ADCSRA_PRESCALER_MASK;
	
	#if (ADC_PRESCALER == ADC_PRESCALER_2)
		
		ADCSRA |= ADC_PRESCALER_2;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_4)
		
		ADCSRA |= ADC_PRESCALER_4;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_8)
		
		ADCSRA |= ADC_PRESCALER_8;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_16)
		
		ADCSRA |= ADC_PRESCALER_16;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_32)
		
		ADCSRA |= ADC_PRESCALER_32;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_64)
		
		ADCSRA |= ADC_PRESCALER_64;
		
	#elif (ADC_PRESCALER == ADC_PRESCALER_128)
		
		ADCSRA |= ADC_PRESCALER_128;
		
	#endif
	
}

void ADC_voidEnableADC(void)
{
	SET_BIT(ADCSRA, ADC_ADCSRA_ADEN);
}

void ADC_voidDisableADC(void)
{
	CLR_BIT(ADCSRA, ADC_ADCSRA_ADEN);
}

void ADC_voidEnableADCInterrupt(void)
{
	SET_BIT(ADCSRA, ADC_ADCSRA_ADIE);
}

void ADC_voidDisableADCInterrupt(void)
{
	CLR_BIT(ADCSRA, ADC_ADCSRA_ADIE);
}

void ADC_voidEnableAutoTrigger(void)
{
	SET_BIT(ADCSRA, ADC_ADCSRA_ADATE);
}

void ADC_voidDisableAutoTrigger(void)
{
	CLR_BIT(ADCSRA, ADC_ADCSRA_ADATE);
}

void ADC_voidClearADCInterruptFlag(void)
{
	SET_BIT(ADCSRA, ADC_ADCSRA_ADIF);
}

void ADC_voidStartConversion(void)
{
	SET_BIT(ADCSRA, ADC_ADCSRA_ADSC);
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
	
	while ((GET_BIT(ADCSRA, ADC_ADCSRA_ADIF) == 0) && (local_u32TimeOutCounter < ADC_TIME_OUT_LIMIT))
		local_u32TimeOutCounter++;
	
	// return error code if ADC timed out
	if (local_u32TimeOutCounter == ADC_TIME_OUT_LIMIT)
		return 0; // will edit this later
	
	_delay_ms(10);
	
	// clear interrupt flag
	ADC_voidClearADCInterruptFlag();
	
	#if (ADC_ADJUST_RESULT == ADC_RIGHT_ADJUST)
		
		copy_u16Result = ((u16)ADCL | (u16)(ADCH << 8));

	#elif (ADC_ADJUST_RESULT == ADC_LEFT_ADJUST)
		
		copy_u16Result = ADCH;
		
	#endif
	
	return copy_u16Result; // will edit this later
}

u8 ADC_u8StartConversionAsync(u8 copy_u8Channel, u16 *copy_u16ptrResult, ptrFunc copy_funcptrNotificationFunc)
{
	// TO DO: verify channel && ptrs passed
	
	// store the addresses of callBackISR + ptr to result passed by user
	ADC_u16ptrADCResult = copy_u16ptrResult;
	ptrFunc ADC_funcPtr_ISR = copy_funcptrNotificationFunc;
	
	// start conversion
	ADC_voidStartConversion();
	
	// select channel
	ADMUX &= ADC_ADMUX_CHANNEL_MASK;
	ADMUX |= copy_u8Channel;
	
	// enable ADC interrupt
	ADC_voidEnableADCInterrupt();
	
	return 1;
}

// TO DO: Chain conversion functions (not a priority tho)

// ADC conversion complete (Asynchronous)
void __vector_16 (void)  __attribute__((signal)) ;
void __vector_16 (void)
{
	#if (ADC_MODE == ADC_SINGLE_CONVERSION_MODE)
		
		// get result
		#if (ADC_ADJUST_RESULT == ADC_RIGHT_ADJUST)
		
			(*ADC_u16ptrADCResult) = (ADCL | (ADCH << 8));

		#elif (ADC_ADJUST_RESULT == ADC_LEFT_ADJUST)
		
			(*ADC_u16ptrADCResult) = ADCH;
		
		#endif
		
		// call user ISR
		ADC_funcPtr_ISR();
		
		// disable interrupt
		ADC_voidDisableADCInterrupt();
		
	#elif (ADC_MODE == ADC_FREE_RUNNING_MODE)
		
		// this is more related to chain-thingy
		
		/* // get result
		#if (ADC_ADJUST_RESULT == ADC_RIGHT_ADJUST)
		
			(*ADC_u16ptrADCResult) = (ADCL | (ADCH << 8));

		#elif (ADC_ADJUST_RESULT == ADC_LEFT_ADJUST)
		
			(*ADC_u16ptrADCResult) = ADCH;
		
		#endif
		
		// call user ISR
		ADC_funcPtr_ISR();
		
		// if:   chain is finished => disable interrupts
		// else: increment chain index => startConversion(); again 
		
		// disable interrupt
		ADC_voidDisableADCInterrupt(); */
		
	#endif
}