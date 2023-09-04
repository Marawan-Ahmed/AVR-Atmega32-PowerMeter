#ifndef CALC_H
#define CALC_H
#include "../LIB/STD_Types.h"

#define SMAPLING_PERIOD_mS 	1
#define SMAPLING_COUNT 		1000




void CALC_voidInit(void);

void CALC_voidPeriodicFunc(void);

void CALC_voidReset(void);

f64 CALC_f64GetRMSVoltage_mV(void);

f64 CALC_f64GetRMSCurrent_mA(void);

f64 CALC_f64GetInstPower_mW(void);

f64 CALC_f64GetRMSPower_mW(void);

f64 CALC_f64GetEnergy_mJ(void);

#endif
