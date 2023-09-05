#include "../../LIB/STD_Types.h"
#include "../../LIB/Bit_Math.h"
#include "TIMER_Register.h"
#include "TIMER_Private.h"
#include "TIMER_CFG.h"
#include "TIMER_Interface.h"

static ptrFunc TMR_ptrFuncCallBack[16] = {NULL};
	


void TMR0_voidInit(void)
{
	#if (TMR0_MODE_OF_OPERATION == TMR0_OVF_MODE)
		
		CLR_BIT(TCCR0, TMR_TCCR0_WGM00);
		CLR_BIT(TCCR0, TMR_TCCR0_WGM01);
		
		#if (TMR0_OVF_INTERRUPT_STATUS == TMR0_OVF_INTERRUPT_ENABLE)
			
			SET_BIT(TIMSK, TMR_TIMSK_TOIE);
		
		#elif (TMR0_OVF_INTERRUPT_STATUS == TMR0_OVF_INTERRUPT_DISABLE)
			
			//CLR_BIT(TIMSK, TMR_TIMSK_TOIE);
			
		#else 
			
			// do a #error/#pragma or sth
		
		#endif
			
	#elif (TMR0_MODE_OF_OPERATION == TMR0_PWM_PHASE_CORRECT_MODE)
		
		SET_BIT(TCCR0, TMR_TCCR0_WGM00);
		CLR_BIT(TCCR0, TMR_TCCR0_WGM01);
		
		// requires continuation
	
	#elif (TMR0_MODE_OF_OPERATION == TMR0_CTC_MODE)
		
		CLR_BIT(TCCR0, TMR_TCCR0_WGM00);
		SET_BIT(TCCR0, TMR_TCCR0_WGM01);
		
		#if (TMR0_CTC_INTERRUPT_STATUS == TMR0_CTC_INTERRUPT_ENABLE)
			
			SET_BIT(TIMSK, TMR_TIMSK_OCIE0);
		
		#elif (TMR0_CTC_INTERRUPT_STATUS == TMR0_CTC_INTERRUPT_DISABLE)
			
			//CLR_BIT(TIMSK, TMR_TIMSK_OCIE0);
			
		#else 
			
			// do a #error/#pragma or sth
		
		#endif
			
	#elif (TMR0_MODE_OF_OPERATION == TMR0_FAST_PWM_MODE)
		
		SET_BIT(TCCR0, TMR_TCCR0_WGM00);
		SET_BIT(TCCR0, TMR_TCCR0_WGM01);
		
		// requires continuation
	
	#else
	
		// do a #error/#pragma or sth

	#endif
	
	#if (TMR0_CS_MODE == TMR_TCCR0_CS_NO_CLK)
		
		CLR_BIT(TCCR0, TMR_TCCR0_CS02);
		CLR_BIT(TCCR0, TMR_TCCR0_CS01);
		CLR_BIT(TCCR0, TMR_TCCR0_CS00);

	#elif (TMR0_CS_MODE == TMR_TCCR0_CS_NO_PRESCALER)
		
		CLR_BIT(TCCR0, TMR_TCCR0_CS02);
		CLR_BIT(TCCR0, TMR_TCCR0_CS01);
		SET_BIT(TCCR0, TMR_TCCR0_CS00);
	
	#elif (TMR0_CS_MODE == TMR_TCCR0_CS_DIV_BY_8)
		
		CLR_BIT(TCCR0, TMR_TCCR0_CS02);
		SET_BIT(TCCR0, TMR_TCCR0_CS01);
		CLR_BIT(TCCR0, TMR_TCCR0_CS00);
	
	#elif (TMR0_CS_MODE == TMR_TCCR0_CS_DIV_BY_64)
		
		CLR_BIT(TCCR0, TMR_TCCR0_CS02);
		SET_BIT(TCCR0, TMR_TCCR0_CS01);
		SET_BIT(TCCR0, TMR_TCCR0_CS00);
	
	#elif (TMR0_CS_MODE == TMR_TCCR0_CS_DIV_BY_256)
		
		SET_BIT(TCCR0, TMR_TCCR0_CS02);
		CLR_BIT(TCCR0, TMR_TCCR0_CS01);
		CLR_BIT(TCCR0, TMR_TCCR0_CS00);
	
	#elif (TMR0_CS_MODE == TMR_TCCR0_CS_DIV_BY_1024)
	
		SET_BIT(TCCR0, TMR_TCCR0_CS02);
		CLR_BIT(TCCR0, TMR_TCCR0_CS01);
		SET_BIT(TCCR0, TMR_TCCR0_CS00);
	
	#elif (TMR0_CS_MODE == TMR_TCCR0_CS_EXT_CLK_T0_FALLING_EDGE)
		
		SET_BIT(TCCR0, TMR_TCCR0_CS02);
		SET_BIT(TCCR0, TMR_TCCR0_CS01);
		CLR_BIT(TCCR0, TMR_TCCR0_CS00);
	
	#elif (TMR0_CS_MODE == TMR_TCCR0_CS_EXT_CLK_T0_RISING_EDGE)
		
		SET_BIT(TCCR0, TMR_TCCR0_CS02);
		SET_BIT(TCCR0, TMR_TCCR0_CS01);
		SET_BIT(TCCR0, TMR_TCCR0_CS00);
	
	#else
		
		// do a #error/#pragma or sth
	
	#endif
}

void TMR0_voidSetOVF(u8 copy_u8PreloadVal)
{
	TCNT0 = copy_u8PreloadVal;
}

void TMR0_voidSetPrescaler(u8 copy_u8Prescaler)
{
	switch (copy_u8Prescaler)
	{
		case TMR_TCCR0_CS_NO_CLK:
				CLR_BIT(TCCR0, TMR_TCCR0_CS02);
				CLR_BIT(TCCR0, TMR_TCCR0_CS01);
				CLR_BIT(TCCR0, TMR_TCCR0_CS00);
				break;
				
		case TMR_TCCR0_CS_NO_PRESCALER:
				CLR_BIT(TCCR0, TMR_TCCR0_CS02);
				CLR_BIT(TCCR0, TMR_TCCR0_CS01);
				SET_BIT(TCCR0, TMR_TCCR0_CS00);
				break;
		case TMR_TCCR0_CS_DIV_BY_8:
				CLR_BIT(TCCR0, TMR_TCCR0_CS02);
				SET_BIT(TCCR0, TMR_TCCR0_CS01);
				CLR_BIT(TCCR0, TMR_TCCR0_CS00);
				break;
		case TMR_TCCR0_CS_DIV_BY_64:
				CLR_BIT(TCCR0, TMR_TCCR0_CS02);
				SET_BIT(TCCR0, TMR_TCCR0_CS01);
				SET_BIT(TCCR0, TMR_TCCR0_CS00);
				break;
		case TMR_TCCR0_CS_DIV_BY_256:
				SET_BIT(TCCR0, TMR_TCCR0_CS02);
				CLR_BIT(TCCR0, TMR_TCCR0_CS01);
				CLR_BIT(TCCR0, TMR_TCCR0_CS00);
				break;
		case TMR_TCCR0_CS_DIV_BY_1024:
				SET_BIT(TCCR0, TMR_TCCR0_CS02);
				CLR_BIT(TCCR0, TMR_TCCR0_CS01);
				SET_BIT(TCCR0, TMR_TCCR0_CS00);
				break;
		case TMR_TCCR0_CS_EXT_CLK_T0_FALLING_EDGE:
				SET_BIT(TCCR0, TMR_TCCR0_CS02);
				SET_BIT(TCCR0, TMR_TCCR0_CS01);
				CLR_BIT(TCCR0, TMR_TCCR0_CS00);
				break;
		case TMR_TCCR0_CS_EXT_CLK_T0_RISING_EDGE:
				SET_BIT(TCCR0, TMR_TCCR0_CS02);
				SET_BIT(TCCR0, TMR_TCCR0_CS01);
				SET_BIT(TCCR0, TMR_TCCR0_CS00);
				break;
	}
	
}



void TMR0_voidSetCTC(u8 copy_u8PreloadVal)
{
	OCR0 = copy_u8PreloadVal;
}

u8 TMR_u8GetCounterValue(void)
{
	return TCNT0;
}


void TMR_voidCallBack(ptrFunc copy_ptrFuncISR, u8 copy_u8VectorID)
{

	if (copy_ptrFuncISR != NULL)
		TMR_ptrFuncCallBack[copy_u8VectorID] = copy_ptrFuncISR;

}

void __vector_11 (void)	__attribute__((signal));
void __vector_11 (void)
{
	if (TMR_ptrFuncCallBack[TMR0_OVF_VECTOR_ID] != NULL)
		TMR_ptrFuncCallBack[TMR0_OVF_VECTOR_ID]();
}

void __vector_10 (void)	__attribute__((signal));
void __vector_10 (void)
{
	if (TMR_ptrFuncCallBack[TMR0_CTC_VECTOR_ID] != NULL)
		TMR_ptrFuncCallBack[TMR0_CTC_VECTOR_ID]();
}

void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	if (TMR_ptrFuncCallBack[TMR1_OVF_VECTOR_ID] != NULL)
		TMR_ptrFuncCallBack[TMR1_OVF_VECTOR_ID]();
}

void __vector_8 (void) __attribute__((signal));
void __vector_8 (void)
{
	if (TMR_ptrFuncCallBack[TMR1_CTCB_VECTOR_ID] != NULL)
		TMR_ptrFuncCallBack[TMR1_CTCB_VECTOR_ID]();
}

void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	if (TMR_ptrFuncCallBack[TMR1_CTCA_VECTOR_ID] != NULL)
		TMR_ptrFuncCallBack[TMR1_CTCA_VECTOR_ID]();
}

void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if (TMR_ptrFuncCallBack[TMR1_ICU_VECTOR_ID] != NULL)
		TMR_ptrFuncCallBack[TMR1_ICU_VECTOR_ID]();
}

void __vector_5 (void) __attribute__((signal)) ;
void __vector_5 (void)
{
	if (TMR_ptrFuncCallBack[TMR2_OVF_VECTOR_ID] != NULL)
		TMR_ptrFuncCallBack[TMR2_OVF_VECTOR_ID]();
}

/*TIMER2 CTC Mode ISR*/
void __vector_4 (void) __attribute__((signal));
void __vector_4 (void)
{
	if (TMR_ptrFuncCallBack[TMR2_CTC_VECTOR_ID] != NULL)
		TMR_ptrFuncCallBack[TMR2_CTC_VECTOR_ID]();
}

/* static int ceil(f32 num) {
    u32 inum = (u32)num;
    if (num == (f32)inum) {
        return inum;
    }
    return inum + 1;
} */

u8 TMR0_u8CTCCalculateOCRMilliSec(u32 *copy_u8FlagCounterMax, u8 copy_u8RequiredTimeInMilliSec)
{
	u64 local_u64Temp = (copy_u8RequiredTimeInMilliSec * 8000000UL) / 1000; // do not forget converting ms to sec
	
	//u8 local_u8RequiredTimeTemp = copy_u8RequiredTimeInMilliSec;
	/*u16 local_u16LoopScale = 1000;
	while (local_u8RequiredTimeTemp)
	{
		if (local_u8RequiredTimeTemp % local_u16LoopScale !)
	}*/
	
	if (copy_u8RequiredTimeInMilliSec >= 10) // apply counter for time longer than or equal 10ms
	{
		if (copy_u8RequiredTimeInMilliSec < 10000) // less than 10sec
		{
			local_u64Temp /= 1000;
			(*copy_u8FlagCounterMax) = 1000;
		}
		else // more than 10 sec
		{
			local_u64Temp /= 1000000;
			(*copy_u8FlagCounterMax) = 2000;
		}
	}
	
	if ((local_u64Temp >= 0) && (local_u64Temp <= TMR0_RESOLUTION()))// no prescaler
	{
		TMR0_voidSetPrescaler(TMR_TCCR0_CS_NO_PRESCALER);
		return ((u8)local_u64Temp);
	}
	else if (((local_u64Temp / 8) >= 0) && ((local_u64Temp / 8) <= TMR0_RESOLUTION()))
	{
		TMR0_voidSetPrescaler(TMR_TCCR0_CS_DIV_BY_8);
		return ((u8)(local_u64Temp / 8));
	}
	else if (((local_u64Temp / 64) >= 0) && ((local_u64Temp / 64) <= TMR0_RESOLUTION()))
	{
		TMR0_voidSetPrescaler(TMR_TCCR0_CS_DIV_BY_64);
		
		return ((u8)(local_u64Temp / 64));
	}  
	else if (((local_u64Temp / 256) >= 0) && ((local_u64Temp / 256) <= TMR0_RESOLUTION()))
	{
		TMR0_voidSetPrescaler(TMR_TCCR0_CS_DIV_BY_256);
		return ((u8)(local_u64Temp / 256));
	}
	else if (((local_u64Temp / 1024) >= 0) && ((local_u64Temp / 1024) <= TMR0_RESOLUTION()))
	{
		TMR0_voidSetPrescaler(TMR_TCCR0_CS_DIV_BY_1024);
		return ((u8)(local_u64Temp / 1024));
	}
	
	return 0;
}
