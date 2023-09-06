#include "../../LIB/Bit_Math.h"
#include "../../LIB/STD_Types.h"
#include "EXTI_Registers.h"
#include "EXTI_Private.h"
#include "EXTI_Interface.h"
#include "EXTI_CFG.h"

/** Global Array of Ptr to ISR Functions */
void (*EXTI_CallBack[3])(void) = {NULL, NULL, NULL};

void EXTI_voidInit(void)
{
	#if (EXTI_LINE == EXTI_GICR_INT0)

		#if (EXTI_SENSE_MODE == EXTI_SENSE_LOW_LEVEL)
			
			CLR_BIT(MCUCR, EXTI_MCUCR_ISC00); 
			CLR_BIT(MCUCR, EXTI_MCUCR_ISC01);

		#elif (EXTI_SENSE_MODE == EXTI_SENSE_ANY_CHANGE)

			SET_BIT(MCUCR, EXTI_MCUCR_ISC00);
			CLR_BIT(MCUCR, EXTI_MCUCR_ISC01);

		#elif (EXTI_SENSE_MODE == EXTI_SENSE_FALLING_EDGE) 

			CLR_BIT(MCUCR, EXTI_MCUCR_ISC00);
			SET_BIT(MCUCR, EXTI_MCUCR_ISC01);

		#elif (EXTI_SENSE_MODE == EXTI_SENSE_RISING_EDGE) 

			SET_BIT(MCUCR, EXTI_MCUCR_ISC00);
			SET_BIT(MCUCR, EXTI_MCUCR_ISC01);

		#endif
		
	#elif (EXTI_LINE == EXTI_GICR_INT1)
		
		#if (EXTI_SENSE_MODE == EXTI_SENSE_LOW_LEVEL)
			
			CLR_BIT(MCUCR, EXTI_MCUCR_ISC10); 
			CLR_BIT(MCUCR, EXTI_MCUCR_ISC11);

		#elif (EXTI_SENSE_MODE == EXTI_SENSE_ANY_CHANGE)

			SET_BIT(MCUCR, EXTI_MCUCR_ISC10);
			CLR_BIT(MCUCR, EXTI_MCUCR_ISC11);

		#elif (EXTI_SENSE_MODE == EXTI_SENSE_FALLING_EDGE) 

			CLR_BIT(MCUCR, EXTI_MCUCR_ISC10);
			SET_BIT(MCUCR, EXTI_MCUCR_ISC11);

		#elif (EXTI_SENSE_MODE == EXTI_SENSE_RISING_EDGE) 

			SET_BIT(MCUCR, EXTI_MCUCR_ISC10);
			SET_BIT(MCUCR, EXTI_MCUCR_ISC11);

		#endif
		
	#elif (EXTI_LINE == EXTI_GICR_INT2) // 1 rising 0 falling
	
		#if (EXTI_SENSE_MODE == EXTI_SENSE_FALLING_EDGE) 
			
			CLR_BIT(MCUCSR, EXTI_MCUCSR_ISC2);
			
		#elif (EXTI_SENSE_MODE == EXTI_SENSE_RISING_EDGE) 
			
			SET_BIT(MCUCSR, EXTI_MCUCSR_ISC2);
			
		#endif
	
	#endif
}

void EXTI_voidSetSignalSenseMode(u8 copy_u8SenseMode, u8 copy_u8Line)
{
	switch (copy_u8Line)
	{
		case EXTI_GICR_INT0: SET_INT0_SENSE_MODE() break;
		case EXTI_GICR_INT1: SET_INT1_SENSE_MODE() break;
		case EXTI_GICR_INT2: SET_INT2_SENSE_MODE() break;
	}
}

void EXTI_voidDisableInterrupt(u8 copy_u8Line)
{
	if ((copy_u8Line == EXTI_GICR_INT0) || (copy_u8Line == EXTI_GICR_INT1) || (copy_u8Line == EXTI_GICR_INT2)) 
		CLR_BIT(GICR, copy_u8Line);
}
void EXTI_voidEnableInterrupt(u8 copy_u8Line)
{
	if ((copy_u8Line == EXTI_GICR_INT0) || (copy_u8Line == EXTI_GICR_INT1) || (copy_u8Line == EXTI_GICR_INT2)) 
		SET_BIT(GICR, copy_u8Line);
}

void EXTI_voidClearFlag(u8 copy_u8Line)
{
	if ((copy_u8Line == EXTI_GIFR_INT0) || (copy_u8Line == EXTI_GIFR_INT1) || (copy_u8Line == EXTI_GIFR_INT2)) 
		CLR_BIT(GIFR, copy_u8Line);
}

void EXTI_voidSetCallBack(void (*copy_ptrvoidCallBack)(void), u8 copy_u8Line)
{
	if (copy_ptrvoidCallBack != NULL)
		EXTI_CallBack[copy_u8Line] = copy_ptrvoidCallBack;
}


void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	if(EXTI_CallBack[0] != NULL)
	{
		EXTI_CallBack[0](); 
		EXTI_voidClearFlag(EXTI_GICR_INT0);
	}
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if(EXTI_CallBack[1] != NULL)
	{
		EXTI_CallBack[1]();
		EXTI_voidClearFlag(EXTI_GICR_INT1);
	}
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if( EXTI_CallBack[2] != NULL )
	{
		EXTI_CallBack[2]();
		EXTI_voidClearFlag(EXTI_GICR_INT2);
	}
}