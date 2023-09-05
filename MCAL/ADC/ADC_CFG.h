#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/** These values will be used for initialization and can be 
	configured later.
 */
 
 /**
	Set this macro as the desired value of AREF Voltage
	if it will be used (in millivolt (mV))
 */
 
#define ADC_AREF_VALUE 5000UL

/**
	Reference Voltage Configuration Options
		ADC_REFV_SEL_AREF	=> AREF
		ADC_REFV_SEL_AVCC 	=> AVCC
		ADC_REFV_SEL_2_56V  => Internal 2.56V
*/

#define ADC_REFV	ADC_REFV_SEL_AREF

/**
	Register Adjust Result Options
		ADC_LEFT_ADJUST
		ADC_RIGHT_ADJUST
*/

#define ADC_ADJUST_RESULT ADC_RIGHT_ADJUST


/**
	Prescaler Options
		ADC_PRESCALER_2	
		ADC_PRESCALER_4	
		ADC_PRESCALER_8	
		ADC_PRESCALER_16
		ADC_PRESCALER_32
		ADC_PRESCALER_64
		ADC_PRESCALER_128
*/
#define ADC_PRESCALER ADC_PRESCALER_64


/**
	Prescaler Options
		ADC_FREE_RUNNING      
		ADC_ANALOG_COMPARATOR 
		ADC_EXTI0             
		ADC_TIM0_CTC_MATCH        
		ADC_TIM0_OVF          
		ADC_TIM1_CTC_MATCH_B
		ADC_TIM1_OVF          
        ADC_TIM1_ICU 
*/		

#define ADC_AUTO_TRIGGER_SOURCE ADC_FREE_RUNNING


/**
	ADC Mode Options
		ADC_FREE_RUNNING		// keeps reading the same ADC channel with a delay window in-between (interrupt must be enabled)
		ADC_SINGLE_CONVERSION	// reads it once then close ADC all-together
*/

#define ADC_MODE				ADC_SINGLE_CONVERSION_MODE


/**
	ADC Interrupt Options
		ADC_INT_ENABLE 
		ADC_INT_DISABLE
*/

#define ADC_INT_STATUS 			ADC_INT_DISABLE


/**
	Enable/Disable ADC Options
		ADC_ENABLE
		ADC_DISABLE
*/

#define ADC_STATUS	ADC_ENABLE

#endif