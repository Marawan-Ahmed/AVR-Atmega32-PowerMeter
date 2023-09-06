#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define EXTI_INT0 0
#define EXTI_INT1 1
#define EXTI_INT2 2

#define EXTI_MCUCR_ISC00 0
#define EXTI_MCUCR_ISC01 1
#define EXTI_MCUCR_ISC10 2
#define EXTI_MCUCR_ISC11 3

#define EXTI_MCUCSR_ISC2 6

#define EXTI_GICR_INT1 7
#define EXTI_GICR_INT0 6
#define EXTI_GICR_INT2 5

#define EXTI_GIFR_INT1 7
#define EXTI_GIFR_INT0 6
#define EXTI_GIFR_INT2 5

#define EXTI_SENSE_FALLING_EDGE 0
#define EXTI_SENSE_RISING_EDGE  1
#define EXTI_SENSE_LOW_LEVEL    2
#define EXTI_SENSE_ANY_CHANGE   3

void EXTI_voidInit(void);
void EXTI_voidSetSignalSenseMode(u8 copy_u8SenseMode, u8 copy_u8Line);
void EXTI_voidDisableInterrupt(u8 copy_u8Line);
void EXTI_voidEnableInterrupt(u8 copy_u8Line);
void EXTI_voidClearFlag(u8 copy_u8Line);
void EXTI_voidSetCallBack(void (*copy_ptrvoidCallBack)(void) , u8 copy_u8Line);

#endif