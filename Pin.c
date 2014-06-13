
/*
* PIN.c
*
* create global PIN structures using compile time constructors
* The InitNewPIN is called to set TRIS and ADPCFG registers since
* this cannot be accomplished in the compile time constructors.
*/
#include <xc.h>
#include <stdlib.h>

#include "Pin.h"
#include "BitOperations.h"


static PinState_t Get(pPin_t This)
{
  return (*(This->mpLat-1) & This->mMask) ? PIN_HIGH : PIN_LOW;
}

static void Set(pPin_t This, PinState_t newState)
{
  if(newState == PIN_HIGH)
    *This->mpLat |= This->mMask;
  if(newState == PIN_LOW)
    *This->mpLat &= ~This->mMask;
  // we could assert if the newState is not valid, but we will do nothing
}

static void SetMode(pPin_t This, PinMode_t newMode)
{
    if (newMode == PIN_OUTPUT) {
        *(This->mpLat + 1) &= ~This->mMask; // make sure pullup is disabled
        *(This->mpLat - 2) &= ~This->mMask; // set the TRIS to configure pin as an output
    }
    if (newMode == PIN_INPUT) {
        *(This->mpLat + 1) &= ~This->mMask; // make sure pullup is disabled
        *(This->mpLat - 2) |= This->mMask; // set the TRIS to configure pin as an input
    }

    if (newMode == PIN_INPUT_PULLUP) {
        *(This->mpLat - 2) |= This->mMask; // set the TRIS to configure pin as an input
        *(This->mpLat + 1) |= This->mMask;
    }
    // we could assert if the newMode is not valid, but we will do nothing
}

void InitPins()
{
    //  preset all Analog pins as digital.  An ADC object (if used) will reset individual bits
    AD1PCFG = 0xFFFF;




}


// compile time constructors for all pins



Pin_t AnodeRed1 =    {BIT(15), &LATB, SetMode, Set, Get};
Pin_t AnodeGreen1 =  {BIT(14), &LATB, SetMode, Set, Get};
Pin_t AnodeBlue1 =   {BIT(13), &LATB, SetMode, Set, Get};

Pin_t AnodeRed2 =    {BIT(12), &LATB, SetMode, Set, Get};
Pin_t AnodeGreen2 =  {BIT(11), &LATB, SetMode, Set, Get};
Pin_t AnodeBlue2 =   {BIT(10), &LATB, SetMode, Set, Get};

Pin_t AnodeRed3 =    {BIT(9), &LATB, SetMode, Set, Get};
Pin_t AnodeGreen3 =  {BIT(8), &LATB, SetMode, Set, Get};
Pin_t AnodeBlue3 =   {BIT(7), &LATB, SetMode, Set, Get};

Pin_t AnodeRed4 =    {BIT(6), &LATB, SetMode, Set, Get};
Pin_t AnodeGreen4 =  {BIT(5), &LATB, SetMode, Set, Get};
Pin_t AnodeBlue4 =   {BIT(4), &LATB, SetMode, Set, Get};

// pin B0 and B1 are for ICE

// these are non-mappable pins
Pin_t Row1 = {BIT(0), &LATA, SetMode, Set, Get};
Pin_t Row2 = {BIT(1), &LATA, SetMode, Set, Get};
Pin_t Row3 = {BIT(2), &LATA, SetMode, Set, Get};
Pin_t Row4 = {BIT(3), &LATA, SetMode, Set, Get};


Pin_t Col1 = {BIT(7), &LATA, SetMode, Set, Get};
Pin_t Col2 = {BIT(8), &LATA, SetMode, Set, Get};
Pin_t Col3 = {BIT(9), &LATA, SetMode, Set, Get};
Pin_t Col4 = {BIT(10),&LATA, SetMode, Set, Get};

Pin_t PowerPin = {BIT(4), &LATA, SetMode, Set, Get};

// the Cathodes need to be mappable pins and we will map an output compare PWM to each
// the pins do not need an object, we will let the hardware control these
//Pin_t Cathode1 = {BIT(0), &LATC, SetMode, Set, Get};
//Pin_t Cathode2 = {BIT(1), &LATC, SetMode, Set, Get};
//Pin_t Cathode3 = {BIT(2), &LATC, SetMode, Set, Get};
//Pin_t Cathode4 = {BIT(3), &LATC, SetMode, Set, Get};