#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


// timer init (0 && 2)
// normal mode/overflow mode (0 && 2)
// CTC (0 && 2)
// callback

#define TMR_TICK_TIME()						(CLK_CPU * TMR0_CS_MODE)

#define TMR0_RESOLUTION()					((1<<8) - 1)

/*
	Timer Resolution
		8  => Timer 0 && Timer 2
		16 => Timer 1 
*/
#define TMR_OVF_TIME(RESOLUTION)			(CLK_CPU * TMR0_CS_MODE * (2 << RESOLUTION))

/**
	here's the idea:
		take the time from user in ns
		check if time%Tovf == 0 => divide them (int division) and the returned number of 
								   overflows will be your condition in the ISR
		else if != 0 && time < Tovf =>  preload value = Tovf - time (no count variable needed)
		else if != 0 && time > Tovf =>	preload value = Tovf - (time%Tovf)
										divide them (int division) and the returned number #+ 1# 
										of overflows will be your condition in the ISR
*/

#define TMR0_OVF_VECTOR_ID		11
#define TMR0_CTC_VECTOR_ID		10

#define TMR1_OVF_VECTOR_ID		9
#define TMR1_CTCB_VECTOR_ID		8
#define TMR1_CTCA_VECTOR_ID		7
#define TMR1_ICU_VECTOR_ID		6

#define TMR2_OVF_VECTOR_ID		5
#define TMR2_CTC_VECTOR_ID		4

u8 TMR0_u8CTCCalculateOCRMilliSec(u32 *copy_u8FlagCounterMax, u8 copy_u8RequiredTimeInMilliSec);
void TMR0_voidSetPrescaler(u8 copy_u8Prescaler);

void TMR0_voidInit(void);
void TMR0_voidSetOVF(u8 copy_u8PreloadVal);
void TMR0_voidSetCTC(u8 copy_u8PreloadVal);
u8 TMR_u8GetCounterValue(void);

void TMR_voidCallBack(ptrFunc copy_ptrFuncISR, u8 copy_u8VectorID);

#endif