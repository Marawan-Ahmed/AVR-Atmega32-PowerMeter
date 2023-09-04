/*
 * Timer0.h
 *
 *  Created on: Aug 23, 2023
 *      Author: Marawan Ahmed
 */

#ifndef TIM0_H
#define TIM0_H


/*******************cfg*****************/
/****************select mode***************/
#define TIM0_MODE	TIM0_MODE_FAST_PWM

/*******************Prescalar********************/
#define TIM0_TIMER_STOPED		0
#define TIM0_NO_PRE				1
#define TIM0_PRE_DIV_8			2
#define TIM0_PRE_DIV_64			3
#define TIM0_PRE_DIV_256		4
#define TIM0_PRE_DIV_1024		5
#define TIM0_EXT_FALLING		6
#define TIM0_EXT_RISING			7

/*******************Interupt control**********/
#define TIM0_INT_ENABLE			1
#define TIM0_INT_DISABLE		0

/**************CO0 Pin Action(NORMAL CTC)**************/
#define TIM0_OC0_IN_OUT			0
#define TIM0_OC0_TGL			1
#define TIM0_OC0_CLR			2
#define TIM0_OC0_SET			3

/**************CO0 Pin Action(FAST PWM)**************/
#define TIM0_OC0_SET_CMP_CLR_OVF	1
#define TIM0_OC0_CLR_CMP_SET_OVF	2

/**************CO0 Pin Action(phase PWM)**************/
#define TIM0_OC0_SET_UP_CLR_DOWN	1
#define TIM0_OC0_CLR_UP_SET_DOWN	2
/***************************APIs********************************/

void TIM0_voidInit(void);
void TIM0_voidSetPreValue(u8 Copy_u8CounterStartValue);
void TIM0_voidTimerStart(u8 Copy_u8Prescalar);
void TIM0_voidOVFINTControl(u8 Copy_u8INTcontrol);

void TIM0_voidSetCompareMatch(u8 Copy_u8CompareMatchValue, u8 Copy_u8OC0PinAction);
void TIM0_voidSetCompareMatchValue(u8 Copy_u8CompareMatchValue);
void TIM0_voidSetCompareMatchINTControl(u8 Copy_u8INTControl);
void TIM0_voidTimerStop (void);

void INT_voidOVFCallback(ptrFunc_Iv_Ov Copy_pfTIM0OVF);
void INT_voidCompareMatchCallback(ptrFunc_Iv_Ov Copy_pfTIM0CompareMatch);

void TIM0_voidPWMGenerator(u8 Copy_u8DutyCycle, u8 Copy_u8C0PinAction);

#endif /* MCAL_TIMER0_TIMER0_H_ */
