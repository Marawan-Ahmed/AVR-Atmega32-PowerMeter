#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX (*(volatile u8*)0x27)
#define ADCSRA (*(volatile u8*)0x26)
#define ADCL (*(volatile u8*)0x24)
#define ADCH (*(volatile u8*)0x25)

#ifndef SFIOR
	#define SFIOR (*(volatile u8*)0x50)
#endif

#endif