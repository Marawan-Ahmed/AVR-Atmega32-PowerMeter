#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TMR0_OVF_MODE				 	0 // (Normal Mode)
#define TMR0_PWM_PHASE_CORRECT_MODE		1
#define TMR0_CTC_MODE					2
#define TMR0_FAST_PWM_MODE				3

#define TMR0_CTC_INTERRUPT_ENABLE		0
#define TMR0_CTC_INTERRUPT_DISABLE		1

#define TMR0_OVF_INTERRUPT_ENABLE		0
#define TMR0_OVF_INTERRUPT_DISABLE		1

/************************************TCCR0*********************************/
// set to 0 when in PWM && 1 to force compare match 
#define TMR_TCCR0_FOC0 		7 
// their values determine mode of operation for timer0
/*
	WGM01	WGM00
	0		0		Normal Mode (OVF)
	0		1		PWM Phase Correct
	1		0		CTC
	1		1		Fast PWM
	0b 1 0 1 1 0 1 1 1
	0b 0 1 0 0 0 0 0 0
*/
#define TMR_TCCR0_WGM00 	6
#define TMR_TCCR0_WGM01		3


// there are some shenangians at these pins, but I won't be tackling them now
#define TMR_TCCR0_COM01		5
#define TMR_TCCR0_COM00		4

/*
	Clock select (with/without prescaler)
		no mask is needed here, thank god!
*/
#define TMR_TCCR0_CS02		2
#define TMR_TCCR0_CS01		1
#define TMR_TCCR0_CS00		0

#define TMR_TCCR0_CS_MASK	0xF8

#define TMR_TCCR0_CS_NO_CLK						0x00
#define TMR_TCCR0_CS_NO_PRESCALER				0x01
#define TMR_TCCR0_CS_DIV_BY_8					0x02
#define TMR_TCCR0_CS_DIV_BY_64					0x03
#define TMR_TCCR0_CS_DIV_BY_256					0x04
#define TMR_TCCR0_CS_DIV_BY_1024				0x05
#define TMR_TCCR0_CS_EXT_CLK_T0_FALLING_EDGE	0x06
#define TMR_TCCR0_CS_EXT_CLK_T0_RISING_EDGE		0x07

// TCNT => for normal mode 
// OCR => write here a value that you want to compare with the one in TCNT

// set to 1 => enable compare match interrupt (NEVER CLEAR THIS NIBBA)
#define TMR_TIMSK_OCIE0		1
// set to 1 => enable overflow counter interrupt (NEVER CLEAR THIS NIBBA)
#define TMR_TIMSK_TOIE		0

// interrupt flags are cleared automatically by hardware
// alternatively, writing 1 in them clears them by software 
#define TMR_TIFR_OCF0		1
#define TMR_TIFR_TOV0		0

// 0 => no effect
// 1 => resets timer/counter0's prescaler
// ## apparently, T0 && T1 share the same prescaler ?! and reseting 
// 	  T0's prescaler will also affect T1 (probably safer to stay away from it)
#define TMR_SFIOR_PSR10		0

/************************************TCCR0*********************************/


#endif