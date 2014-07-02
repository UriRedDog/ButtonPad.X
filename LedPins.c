/*
 * LedPins.c
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

#include "p24fxxxx.h"
#include "Pin.h"
#include "LedPins.h"

static void Set(pLED_t This, LEDState_t newState)
{
    pPin_t anode = This->anode;

    switch(newState)
    {
    case LED_OFF :
        anode->Set(anode, PIN_LOW);
        break;

    case LED_ON :
        anode->Set(anode, PIN_HIGH);
        break;
    }
}


LED_t Red1 =     {&AnodeRed1, Set};
LED_t Green1 =   {&AnodeGreen1, Set};
LED_t Blue1 =    {&AnodeBlue1, Set};

LED_t Red2 =     {&AnodeRed2, Set};
LED_t Green2 =   {&AnodeGreen2, Set};
LED_t Blue2 =    {&AnodeBlue2, Set};

LED_t Red3 =     {&AnodeRed3, Set};
LED_t Green3 =   {&AnodeGreen3, Set};
LED_t Blue3 =    {&AnodeBlue3, Set};

LED_t Red4 =     {&AnodeRed4, Set};
LED_t Green4 =   {&AnodeGreen4, Set};
LED_t Blue4 =    {&AnodeBlue4, Set};

void InitLeds()
{
    Red1.anode->SetMode(Red1.anode, PIN_OUTPUT);
    Red1.Set(&Red1, LED_OFF);
    Red2.anode->SetMode(Red2.anode, PIN_OUTPUT);
    Red2.Set(&Red2, LED_OFF);
    Red3.anode->SetMode(Red3.anode, PIN_OUTPUT);
    Red3.Set(&Red3, LED_OFF);
    Red4.anode->SetMode(Red4.anode, PIN_OUTPUT);
    Red4.Set(&Red4, LED_OFF);

    Green1.anode->SetMode(Green1.anode, PIN_OUTPUT);
    Green1.Set(&Green1, LED_OFF);
    Green2.anode->SetMode(Green2.anode, PIN_OUTPUT);
    Green2.Set(&Green2, LED_OFF);
    Green3.anode->SetMode(Green1.anode, PIN_OUTPUT);
    Green3.Set(&Green3, LED_OFF);
    Green4.anode->SetMode(Green4.anode, PIN_OUTPUT);
    Green4.Set(&Green4, LED_OFF);

    Blue1.anode->SetMode(Blue1.anode, PIN_OUTPUT);
    Blue1.Set(&Blue1, LED_OFF);
    Blue2.anode->SetMode(Blue2.anode, PIN_OUTPUT);
    Blue2.Set(&Blue3, LED_OFF);
    Blue3.anode->SetMode(Blue3.anode, PIN_OUTPUT);
    Blue3.Set(&Blue3, LED_OFF);
    Blue4.anode->SetMode(Blue4.anode, PIN_OUTPUT);
    Blue4.Set(&Blue4, LED_OFF);
}