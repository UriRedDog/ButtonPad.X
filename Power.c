/*
 * Power.c
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
*/

// define power bus pin
// unfortunately this must be defined/declared in Pin.h and Pin.c otherwise we have to duplicate code
// PIN const PowerPin = {BIT2, &LATC, SetMode, Set, Get};

#include "Pin.h"
#include "Power.h"

void PowerManager(PowerState_t state)
{
    PowerPin.SetMode(&PowerPin, PIN_OUTPUT);
    if(state == POWER_ON)
        PowerPin.Set(&PowerPin, PIN_HIGH);
    else
        PowerPin.Set(&PowerPin, PIN_LOW);
}
