#ifndef EXTI_CFG_H_
#define EXTI_CFG_H_

/*
 Options :-

 	EXTI_GICR_INT0
		||
	EXTI_GICR_INT1
		||
	EXTI_GICR_INT2

 */

#define EXTI_LINE   EXTI_GICR_INT0

/*
 Options :-

 	EXTI_SENSE_FALLING_EDGE
		||
	EXTI_SENSE_RISING_EDGE 
		||				
	EXTI_SENSE_LOW_LEVEL
		||					
	EXTI_SENSE_ANY_CHANGE

 */



#define EXTI_SENSE_MODE  EXTI_SENSE_ANY_CHANGE

		
#endif