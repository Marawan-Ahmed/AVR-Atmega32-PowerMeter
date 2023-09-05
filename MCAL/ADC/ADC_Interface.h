#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void ADC_voidInit(void);

void ADC_voidStartConversion(void);

void ADC_voidSetPrescaler(u8 copy_u8Prescaler);

void ADC_voidEnableAutoTrigger(void);
void ADC_voidDisableAutoTrigger(void);
void ADC_voidSetAutoTriggerSource(u8 copy_u8AutoTriggerSource);

void ADC_voidEnableADC(void);
void ADC_voidDisableADC(void);

void ADC_voidEnableADCInterrupt(void);
void ADC_voidDisableADCInterrupt(void);
void ADC_voidClearADCInterruptFlag(void);

u16 ADC_u16GetResultSync(u8 copy_u8Channel);
u8 ADC_u8StartConversionAsync(u8 copy_u8Channel, u16 *copy_u16ptrResult, ptrFunc copy_funcptrNotificationFunc);

// To Do (but not now!)
//u8 ADC_u8StartConversionChainSync();
//u8 ADC_u8StartConversionChainAsynch();

#endif