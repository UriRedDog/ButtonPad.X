
/*
 * PIN.c
 *
 * create global PIN structures using compile time constructors
 * The InitNewPIN is called to set TRIS and ADPCFG registers since
 * this cannot be accomplished in the compile time constructors.
 *
 * we use the LAT as the base register.  TRIS, PORT, and ODCB are
 * pointer offsets added or subtracted.
*/
#include <xc.h>
#include <stdlib.h>

#include "Pin.h"
#include "BitOperations.h"

#define TRIS_OFFSET 2
#define PORT_OFFSET 1
#define ODC_OFFSET +1

static PinState_t Get(pPin_t This)
{
  return (*This->mPort & This->mMask) ? PIN_HIGH : PIN_LOW;
}

static void Set(pPin_t This, PinState_t newState)
{
  if(newState == PIN_HIGH)
    *This->mLat |= This->mMask;
  if(newState == PIN_LOW)
    *This->mLat &= ~This->mMask;
  // we could assert if the newState is not valid, but we will do nothing
}

static void SetMode(pPin_t This, PinMode_t newMode)
{
    if (newMode == PIN_OUTPUT) {
        *This->mOdc &= ~This->mMask; // make sure pullup is disabled
        *This->mTris &= ~This->mMask; // set the TRIS to configure pin as an output
    }
    if (newMode == PIN_INPUT) {
        *This->mOdc &= ~This->mMask; // make sure pullup is disabled
        *This->mLat |= This->mMask; // set the TRIS to configure pin as an input
    }

    if (newMode == PIN_INPUT_PULLUP) {
        *This->mTris |= This->mMask; // set the TRIS to configure pin as an input
        *This->mOdc |= This->mMask;
    }
    // we could assert if the newMode is not valid, but we will do nothing
}

void InitPins()
{
    //  preset all Analog pins as digital.  An ADC object (if used) will reset individual bits
    AD1PCFG = 0xFFFF;
}


// compile time constructors for all pins



Pin_t AnodeRed1 =    {BIT(15), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};
Pin_t AnodeGreen1 =  {BIT(14), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};
Pin_t AnodeBlue1 =   {BIT(13), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};

Pin_t AnodeRed2 =    {BIT(12), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};
Pin_t AnodeGreen2 =  {BIT(11), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};
Pin_t AnodeBlue2 =   {BIT(10), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};

Pin_t AnodeRed3 =    {BIT(9), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};
Pin_t AnodeGreen3 =  {BIT(8), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};
Pin_t AnodeBlue3 =   {BIT(7), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};

Pin_t AnodeRed4 =    {BIT(6), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};
Pin_t AnodeGreen4 =  {BIT(5), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};
Pin_t AnodeBlue4 =   {BIT(4), &TRISB, &PORTB, &LATB, &ODCB, SetMode, Set, Get};

// pin B0 and B1 are for ICE

// these are non-mappable pins
Pin_t Row1 = {BIT(0), &TRISA, &PORTA, &LATA, &ODCA, SetMode, Set, Get};
Pin_t Row2 = {BIT(1), &TRISA, &PORTA, &LATA, &ODCA, SetMode, Set, Get};
Pin_t Row3 = {BIT(2), &TRISA, &PORTA, &LATA, &ODCA, SetMode, Set, Get};
Pin_t Row4 = {BIT(3), &TRISA, &PORTA, &LATA, &ODCA, SetMode, Set, Get};


Pin_t Col1 = {BIT(7), &TRISA, &PORTA, &LATA, &ODCA, SetMode, Set, Get};
Pin_t Col2 = {BIT(8), &TRISA, &PORTA, &LATA, &ODCA, SetMode, Set, Get};
Pin_t Col3 = {BIT(9), &TRISA, &PORTA, &LATA, &ODCA, SetMode, Set, Get};
Pin_t Col4 = {BIT(10),&TRISA, &PORTA, &LATA, &ODCA, SetMode, Set, Get};

Pin_t PowerPin = {BIT(4), &TRISA, &PORTA, &LATA, &ODCA, SetMode, Set, Get};

// the Cathodes need to be mappable pins and we will map an output compare PWM to each
// the pins do not need an object, we will let the hardware control these
//Pin_t Cathode1 = {BIT(0), &LATC, SetMode, Set, Get};
//Pin_t Cathode2 = {BIT(1), &LATC, SetMode, Set, Get};
//Pin_t Cathode3 = {BIT(2), &LATC, SetMode, Set, Get};
//Pin_t Cathode4 = {BIT(3), &LATC, SetMode, Set, Get};