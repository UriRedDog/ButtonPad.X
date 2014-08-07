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



void TestLED()
{
  Red1C1.Set(&Red1C1, LED_ON);
  Red2C1.Set(&Red2C1, LED_ON);
  Red3C1.Set(&Red3C1, LED_ON);
  Red4C1.Set(&Red4C1, LED_ON);

  Green1C1.Set(&Green1C1, LED_ON);
  Green2C1.Set(&Green2C1, LED_ON);
  Green3C1.Set(&Green3C1, LED_ON);
  Green4C1.Set(&Green4C1, LED_ON);

  Blue1C1.Set(&Blue1C1, LED_ON);
  Blue2C1.Set(&Blue2C1, LED_ON);
  Blue3C1.Set(&Blue3C1, LED_ON);
  Blue4C1.Set(&Blue4C1, LED_ON);
}





//#endif

