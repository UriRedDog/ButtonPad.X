/*
 * Test.c
 * The test routines will light each LED in sequence, and cycle though
 * these for some period of time.
 *
 * testing switches will requier user input by pressing the
 * switch that has an led in the on state.
 *
 * NOTE:  this is not a unit test.  This is a runtime startup test.
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "pps.h"
#include "libpic30.h"

#include "Pin.h"
#include "LedPins.h"
#include "Switch.h"
#include "Timer.h"
#include "test.h"

//#ifdef UNIT_TEST

// create an array of the LEDs for test purposes
static pLED_t LedArray[12] =
{
    &Red1,
    &Red2,
    &Red3,
    &Red4,

    &Green1,
    &Green2,
    &Green3,
    &Green4,

    &Blue1,
    &Blue2,
    &Blue3,
    &Blue4
};

void TestLED() {
    int loopcount = 5;
    int i;
    pLED_t pLed;
    while (loopcount--) {
        pLed = LedArray[0];
        for (i = 0; i < 12; i++) {
            pLed->Set(pLed, LED_ON);
            pLed++;
            __delay32(5000);
        }

        pLed = LedArray[0];
        for (i = 0; i < 12; i++) {
            pLed->Set(pLed, LED_OFF);
            pLed++;
            __delay32(5000);
        }
    }
}





//#endif

