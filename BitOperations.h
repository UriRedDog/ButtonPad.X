/* 
 * File:   BitOperations.h
 * Author: dthedens
 *
 * Created on June 12, 2014, 12:08 PM
 */

#ifndef BITOPERATIONS_H
#define	BITOPERATIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BIT(a) (1 <<(a))

/*
 this was shared by AVIX-RT RTOS on the Microchip forums Oct 18 2008
 The macro is setBitField_atomic. Macro onesMask and the inline functions are helpers.

Using setBitField_atomic you can change a number of consecutive bits without the RMW
problem existing since the actual manipulation of the bits is done with a single
write operation from the inline function by the xor present there.

The arguments to the macro are:

r: Register, for instance LATD
v: value to set the bitfield to, can be a variable or a constant
u: upper bit of the bitfield, numbered from 0..15
l: lower bit of the bitfield, numbered from 0..15

The macro is resistant to specifying a higher value for the l bit than the u bit,
so for l and u you just pass the lowest and the highest bitnumber of the field
and the macro does the rest.
 */


static void __attribute__((always_inline))
atomic_xor(unsigned int mask, volatile unsigned int* pVar)
{
    __asm__ __volatile__(" xor %1, [%2], [%0] " : "=r"(pVar) : "r"(mask), "0"(pVar) );
}
 #define onesMask(u,l) (((~0 << (l)) ^ (~0 << (u))) | (1 << (u)) | (1 << (l)))
 #define setBitField_atomic(r,v,u,l) atomic_xor((((v)<<( (u)>(l)?(l):(u) )) ^ (r)) & onesMask(u,l), &r)



#ifdef	__cplusplus
}
#endif

#endif	/* BITOPERATIONS_H */

