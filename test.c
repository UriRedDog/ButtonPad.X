/*
 * Test.c
 *
 * Copyright (c) <2014> <David Thedens, Eric Summers>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * power system is a switch which turns on a FET or enables SHDWN on a LDO
 * to sustatin power.
 * CPU then sets a bit which drives another FET to keep power enabled.
 * after some period of inactivity, the program will drive the pin low which will
 * remove bias or cause SHDWN to go low, or it could place the CPU into low power
 * the only power draw will be the power FET or LDO leakage current or sleep current

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
static pLED_t LedArray[12] ={
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

void TestLED()
{
  int loopcount = 5;
  int i;
  pLED_t pLed;
  while (loopcount--)
  {
    pLed = LedArray[0];
    for (i = 0; i < 12; i++)
    {
      pLed->Set(pLed, LED_ON);
      pLed++;
      __delay32(5000);
    }

    pLed = LedArray[0];
    for (i = 0; i < 12; i++)
    {
      pLed->Set(pLed, LED_OFF);
      pLed++;
      __delay32(5000);
    }
  }
}





//#endif

