
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(REG,BIT) (REG |= (1 << BIT))
#define CLR_BIT(REG,BIT) (REG &= ~(1 << BIT))
#define TOG_BIT(REG,BIT) (REG ^= (1 << BIT))
#define GET_BIT(REG,BIT) ((REG >> BIT) & 1)

#define SET_PORT(Y) ( (Y) = 0xFF )
#define CLR_PORT(Y) ( (Y) = 0x00 )
#define TOG_PORT(Y) ( (Y) ^= 0xFF )

#define SET_PORT_TO_VAL(Y, VAL) ( (Y) = (VAL) )
 
#endif
