#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/* ADC Timeout Limit */
#define ADC_TIME_OUT_LIMIT		69000UL

/* ADC Frequence Range */
#define ADC_FREQ_MIN	50000UL
#define ADC_FREQ_MAX	200000UL

/**************USER-CONFIGURABLE PARAMETERS**************/

/* Enable/Disable ADC */
#define ADC_ENABLE 		1
#define ADC_DISABLE		0

/* Modes of Operation */
#define ADC_FREE_RUNNING_MODE		0 // keeps reading the same ADC channel with a delay window in-between
#define ADC_SINGLE_CONVERSION_MODE	1 // reads it once then close ADC all-together

/* Enable/Disable ADC Interrupt */
#define ADC_INT_ENABLE 	1
#define ADC_INT_DISABLE 0

/* Channels */
#define ADC_CHANNEL_0	0 
#define ADC_CHANNEL_1	1 
#define ADC_CHANNEL_2	2 
#define ADC_CHANNEL_3	3 
#define ADC_CHANNEL_4	4 
#define ADC_CHANNEL_5	5 
#define ADC_CHANNEL_6	6 
#define ADC_CHANNEL_7	7

/* Prescalers */
#define ADC_PRESCALER_2		0x01
#define ADC_PRESCALER_4		0x02
#define ADC_PRESCALER_8		0x03
#define ADC_PRESCALER_16	0x04
#define ADC_PRESCALER_32	0x05
#define ADC_PRESCALER_64	0x06
#define ADC_PRESCALER_128	0x07

/* Reference Voltage */
#define ADC_REFV_SEL_AREF 	0
#define ADC_REFV_SEL_AVCC 	1
#define ADC_REFV_SEL_2_56V 	2

/* Adjust Result Choices */
#define ADC_LEFT_ADJUST 	1
#define ADC_RIGHT_ADJUST	0

/* Auto Trigger Source */
#define ADC_FREE_RUNNING        0x00
#define ADC_ANALOG_COMPARATOR   0x20
#define ADC_EXTI0               0x40
#define ADC_TIM0_CTC_MATCH      0x60
#define ADC_TIM0_OVF            0x80
#define ADC_TIM1_CTC_MATCH_B    0xA0
#define ADC_TIM1_OVF            0xC0
#define ADC_TIM1_ICU            0xE0

/********************************************************/



/************************ADCSRA**************************/

/* ADC enable => 1 to enable */
#define ADC_ADCSRA_ADEN		7

/* start conversion => 1 to start */
#define ADC_ADCSRA_ADSC		6

/* auto trigger enable => 1 to enable */
#define ADC_ADCSRA_ADATE	5

/* interrupt flag (cleared by writing 1) */
#define ADC_ADCSRA_ADIF		4

/* interrupt enable => 1 */
#define ADC_ADCSRA_ADIE 	3

/* ADC prescaler bits (000->111 write values of the prescaler values above) */
#define ADC_ADCSRA_ADPS2	2
#define ADC_ADCSRA_ADPS1	1
#define ADC_ADCSRA_ADPS0	0

/* Prescaler Mask */
#define ADC_ADCSRA_PRESCALER_MASK 0xF8

/********************************************************/


/*************************ADMUX**************************/

/* Reference Voltage Selection */
/**
		00 => AREF
		01 => AVCC
		10 => Reserved
		11 => Internal 2.56V Voltage Reference
*/
#define ADC_ADMUX_REFS1		7		
#define ADC_ADMUX_REFS0 	6

/* left/right adjust */
#define ADC_ADMUX_ADLAR 	5

/* Channel Selection (single channel ONLY---no differential) */
#define ADC_ADMUX_MUX4 	4
#define ADC_ADMUX_MUX3 	3
#define ADC_ADMUX_MUX2 	2
#define ADC_ADMUX_MUX1 	1
#define ADC_ADMUX_MUX0 	0

/* channel selection mask (& with ADMUX then set MUX bits separately using |) */
#define ADC_ADMUX_CHANNEL_MASK 0b11100000

/********************************************************/


/*************************SFIOR**************************/

/* for free running mode (set all to 0) */
#define SFIOR_ADTS0			5
#define SFIOR_ADTS1			6
#define SFIOR_ADTS2			7

/* Sources of Auto Trigger mask (& with SFIOR then set ADTS bits separately using |) */
#define ADC_SFIOR_MASK					0x00011111

/********************************************************/

#endif