#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

#define SET_INT0_SENSE_MODE() 	switch (copy_u8SenseMode) 					\
								{											\
									case EXTI_SENSE_FALLING_EDGE: 			\
										CLR_BIT(MCUCR, EXTI_MCUCR_ISC00);	\
										SET_BIT(MCUCR, EXTI_MCUCR_ISC01);	\
										break;								\
									case EXTI_SENSE_RISING_EDGE	: 			\
										SET_BIT(MCUCR, EXTI_MCUCR_ISC00);	\
										SET_BIT(MCUCR, EXTI_MCUCR_ISC01);	\
										break;								\
									case EXTI_SENSE_LOW_LEVEL	: 			\
										CLR_BIT(MCUCR, EXTI_MCUCR_ISC00); 	\
										CLR_BIT(MCUCR, EXTI_MCUCR_ISC01);	\
										break;								\
									case EXTI_SENSE_ANY_CHANGE	: 			\
										SET_BIT(MCUCR, EXTI_MCUCR_ISC00);	\
										CLR_BIT(MCUCR, EXTI_MCUCR_ISC01);	\
										break;								\
								}
								
								
#define SET_INT1_SENSE_MODE()	switch (copy_u8SenseMode)					\
								{											\
									case EXTI_SENSE_FALLING_EDGE:			\
									CLR_BIT(MCUCR, EXTI_MCUCR_ISC10);		\
									SET_BIT(MCUCR, EXTI_MCUCR_ISC11);		\
									break;									\
									case EXTI_SENSE_RISING_EDGE	:			\
									SET_BIT(MCUCR, EXTI_MCUCR_ISC10);		\
									SET_BIT(MCUCR, EXTI_MCUCR_ISC11);		\
									break;									\
									case EXTI_SENSE_LOW_LEVEL	:			\
									CLR_BIT(MCUCR, EXTI_MCUCR_ISC10);		\
									CLR_BIT(MCUCR, EXTI_MCUCR_ISC11);		\
									break;									\
									case EXTI_SENSE_ANY_CHANGE	:			\
									SET_BIT(MCUCR, EXTI_MCUCR_ISC10);		\
									CLR_BIT(MCUCR, EXTI_MCUCR_ISC11);		\
									break;									\
								}
								
								
#define SET_INT2_SENSE_MODE()	switch (copy_u8SenseMode)					\
								{											\
									case EXTI_SENSE_FALLING_EDGE:			\
									CLR_BIT(MCUCSR, EXTI_MCUCSR_ISC2);		\
									break;									\
									case EXTI_SENSE_RISING_EDGE	:			\
									SET_BIT(MCUCSR, EXTI_MCUCSR_ISC2);		\
									break;									\
								}		

#endif