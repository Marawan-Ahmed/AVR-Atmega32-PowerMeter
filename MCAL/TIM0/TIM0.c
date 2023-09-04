/*
 * Timer0.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Marawan Ahmed
 */


#include <avr/interrupt.h>
#include <avr/io.h>
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_Math.h"

#define TIM0_MODE_NORMAL	0
#define TIM0_MODE_CTC 		1
#define TIM0_MODE_PWM_PHASE	2
#define TIM0_MODE_FAST_PWM	3

#include "TIM0.h"

ptrFunc_Iv_Ov Global_ISR_TIM0_OVF_ptr = NULL;
ptrFunc_Iv_Ov Global_ISR_TIM0_CM_ptr = NULL;


void TIM0_voidInit(void){
	#if TIM0_MODE == TIM0_MODE_NORMAL
		CLR_BIT(TCCR0, WGM00);
		CLR_BIT(TCCR0, WGM01);
	#elif TIM0_MODE == TIM0_MODE_CTC
		CLR_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);
	#elif TIM0_MODE == TIM0_MODE_CTC
		SET_BIT(TCCR0, WGM00);
		CLR_BIT(TCCR0, WGM01);
	#else
		SET_BIT(TCCR0, WGM00);
		SET_BIT(TCCR0, WGM01);
	#endif
}



void TIM0_voidSetPreValue(u8 Copy_u8CounterStartValue){
	TCNT0 = Copy_u8CounterStartValue;
}

void TIM0_voidTimerStart(u8 Copy_u8Prescalar){
	TCCR0 &= 0b11111000;
	TCCR0 |= Copy_u8Prescalar;
}

void TIM0_voidOVFINTControl(u8 Copy_u8INTcontrol){
	if (Copy_u8INTcontrol == TIM0_INT_ENABLE){
		SET_BIT(TIMSK, TOIE0);
	}
	else{
		CLR_BIT(TIMSK, TOIE0);
	}
}

void TIM0_voidSetCompareMatch(u8 Copy_u8CompareMatchValue, u8 Copy_u8OC0PinAction){
	switch(Copy_u8OC0PinAction){
		case TIM0_OC0_TGL:
			SET_BIT(TCCR0, COM00);
			CLR_BIT(TCCR0, COM01);
			break;

		case TIM0_OC0_CLR:
			CLR_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
			break;

		case TIM0_OC0_SET:
			SET_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
			break;

		default:
			CLR_BIT(TCCR0, COM00);
			CLR_BIT(TCCR0, COM01);
			break;
	}
	OCR0 = Copy_u8CompareMatchValue;
}

void TIM0_voidSetCompareMatchValue(u8 Copy_u8CompareMatchValue){
	OCR0 = Copy_u8CompareMatchValue;
}


void TIM0_voidSetCompareMatchINTControl(u8 Copy_u8INTControl){
	if (Copy_u8INTControl == TIM0_INT_ENABLE){
		SET_BIT(TIMSK, OCIE0);
	}
	else{
		CLR_BIT(TIMSK, OCIE0);
	}
}

void TIM0_voidTimerStop (void){
	TCCR0 &= 0b11111000;

}

void INT_voidOVFCallback(ptrFunc_Iv_Ov Copy_pfTIM0OVF){
	Global_ISR_TIM0_OVF_ptr = Copy_pfTIM0OVF;
}
void INT_voidCompareMatchCallback(ptrFunc_Iv_Ov Copy_pfTIM0CompareMatch){
	Global_ISR_TIM0_CM_ptr = Copy_pfTIM0CompareMatch;

}

void TIM0_voidPWMGenerator(u8 Copy_u8DutyCycle, u8 Copy_u8C0PinAction){
	#if TIM0_MODE == TIM0_MODE_FAST_PWM
		if(Copy_u8C0PinAction == TIM0_OC0_SET_CMP_CLR_OVF){
			SET_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
			OCR0 = 256 - (Copy_u8DutyCycle * 256)/100;

		}
		else{
			CLR_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
			OCR0 = (Copy_u8DutyCycle * 256)/100;

		}

	#elif TIM0_MODE == TIM0_MODE_PWM_PHASE
		if(Copy_u8C0PinAction == TIM0_OC0_SET_UP_CLR_DOWN){
			SET_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
			OCR0 = (510 - (Copy_u8DutyCycle * 510)/100)/2;

		}
		else{
			CLR_BIT(TCCR0, COM00);
			SET_BIT(TCCR0, COM01);
			OCR0 = (Copy_u8DutyCycle * 510)/100/2;

		}

	#endif
}




ISR(TIMER0_OVF_vect){
	if(Global_ISR_TIM0_OVF_ptr != NULL){
		Global_ISR_TIM0_OVF_ptr();
	}
}

ISR(TIMER0_COMP_vect){
	if(Global_ISR_TIM0_CM_ptr != NULL){
		Global_ISR_TIM0_CM_ptr();
	}
}


