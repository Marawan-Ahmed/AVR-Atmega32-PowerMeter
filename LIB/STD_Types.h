#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char          	u8 ;
typedef unsigned short int     	u16;
typedef unsigned long int     	u32;
typedef unsigned long long     	u64;

typedef signed char            	s8 ;
typedef signed short int       	s16;
typedef signed long int        	s32;
typedef signed   long long  	s64;

typedef float                  	f32;
typedef double                 	f64;
//typedef long double         	f80;


typedef void (*ptrFunc_Iv_Ov) (void);


#define NULL	((volatile void*) 0LL)

typedef enum

{
	true = 1,
	false = 0
} bool;

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

#endif


