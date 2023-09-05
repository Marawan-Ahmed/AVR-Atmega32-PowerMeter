#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

typedef enum DIO_returnTypeState
{
	DIO_OK,
	DIO_PORT_ARG_UNDEFINED,
	DIO_PIN_NO_ARG_OUT_OF_BOUNDS,
	DIO_PIN_VAL_ARG_OUT_OF_BOUNDS,
	DIO_PIN_DIR_ARG_OUT_OF_BOUNDS,
	DIO_PORT_VAL_ARG_OUT_OF_BOUNDS,
	DIO_PORT_DIR_ARG_OUT_OF_BOUNDS,
	DIO_PIN_PU_ARG_OUT_OF_BOUNDS,
	DIO_PULL_UP_STATUS_VAL_OUT_OF_RANGE
} DIO_returnTypeState;

typedef enum DIO_functionCallID
{
	DIO_SET_PIN_DIR,
	DIO_SET_PIN_VALUE,
	DIO_GET_PIN_VALUE,
	
} DIO_functionID;

static void DIO_voidDebugAndTest(); // led pattern for each error state + steady led for DIO_OK


#endif