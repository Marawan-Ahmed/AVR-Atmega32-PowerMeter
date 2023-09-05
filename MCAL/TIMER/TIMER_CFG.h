#ifndef TIMER_CFG_H_
#define TIMER_CFG_H_

/*
	MCU Frequency (in MHz)
*/

#define F_CPU		8000000UL


/*
	CPU Periodic Time (in us)
*/

#define CLK_CPU		12.5			// 1/F_CPU 


/*
	Timer 0 Modes of Operation Options
		TMR0_OVF_MODE (Normal Mode)
		TMR0_PWM_PHASE_CORRECT_MODE
		TMR0_CTC_MODE
		TMR0_FAST_PWM_MODE
*/

#define TMR0_MODE_OF_OPERATION	TMR0_OVF_MODE


/*
	Timer 0 Clock Selection Options
		TMR_TCCR0_CS_NO_CLK					
		TMR_TCCR0_CS_NO_PRESCALER			
		TMR_TCCR0_CS_DIV_BY_8				
		TMR_TCCR0_CS_DIV_BY_64				
		TMR_TCCR0_CS_DIV_BY_256				
		TMR_TCCR0_CS_DIV_BY_1024			
		TMR_TCCR0_CS_EXT_CLK_T0_FALLING_EDGE
		TMR_TCCR0_CS_EXT_CLK_T0_RISING_EDGE
*/

#define TMR0_CS_MODE	TMR_TCCR0_CS_DIV_BY_8


/*
	Timer 0 CTC Interrupt Options
		TMR0_CTC_INTERRUPT_ENABLE
		TMR0_CTC_INTERRUPT_DISABLE
*/

#define TMR0_CTC_INTERRUPT_STATUS	TMR0_CTC_INTERRUPT_ENABLE	


/*
	Timer 0 OVF Interrupt Options
		TMR0_OVF_INTERRUPT_ENABLE
		TMR0_OVF_INTERRUPT_DISABLE
*/

#define TMR0_OVF_INTERRUPT_STATUS	TMR0_OVF_INTERRUPT_ENABLE



#endif